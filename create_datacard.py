from __future__ import print_function, division
import os
import rhalphalib as rl
import numpy as np
import pickle
import uproot
import logging
import sys
from array import array
from collections import OrderedDict
rl.util.install_roofit_helpers()
rl.ParametericSample.PreferRooParametricHist = False
logging.basicConfig(level=logging.DEBUG)
adjust_posdef_yields = False


def get_hist(upfile, name, obs):
    hist_values = upfile[name].values()
    hist_edges = upfile[name].axis().edges()
    hist_uncs = upfile[name].variances()

    return (hist_values, hist_edges, obs.name, hist_uncs)


def symmetrize(effectUp, effectDown):
    envelopeUp = np.maximum(effectUp, effectDown)
    envelopeDown = np.minimum(effectUp, effectDown)
    effectUpSym = np.sqrt(envelopeUp/envelopeDown)
    effectDownSym = np.sqrt(envelopeDown/envelopeUp)
    return effectUpSym, effectDownSym


def create_datacard(inputfile, carddir, nbins, nMCTF, nDataTF, passBinName, failBinName='fail', add_blinded=False, include_ac=False):

    # open uproot file once
    upfile = uproot.open(inputfile)

    regionPairs = [('SR'+passBinName, 'fit'+failBinName)]  # pass, fail region pairs

    regions = [item for t in regionPairs for item in t]  # all regions

    # luminosity unc https://gitlab.cern.ch/hh/naming-conventions#luminosity
    lumi_13TeV_161718 = rl.NuisanceParameter('lumi_13TeV_161718', 'lnN')

    #rescaled axis to be compatible with Bernstein polymial
    #CSC OOT
    msdbins = np.arange(50, 300, 1) #np.array([50,56,62,68,74,88,115,190,200])
    msd = rl.Observable('nrechits', msdbins)
    msdpts = np.arange(50.5, 300.5, 1) #these are midpoints of each bin
    msdscaled = (msdpts-50.5)/250.

#    #DT OOT
#    msdbins = np.array([50,56,62,68,74,84,98,114,120])
#    msd = rl.Observable('nrechits', msdbins)
#    msdpts = np.array([53,59,65,71,79,91,106,117])
#    msdscaled = (msdpts-50.)/70
 
    # Build qcd MC pass+fail model and fit to polynomial
    qcdmodel = rl.Model('qcdmodel')
    qcdpass, qcdfitfail = 0., 0.
    passCh = rl.Channel('passqcdmodel')
    fitfailCh = rl.Channel('fitfailqcdmodel')
    qcdmodel.addChannel(fitfailCh)
    qcdmodel.addChannel(passCh)

    passTempl = get_hist(upfile, 'h_pass_Data', obs=msd)
    fitfailTempl = get_hist(upfile, 'h_fail_Data', obs=msd)

    passCh.setObservation(passTempl[:-1])
    fitfailCh.setObservation(fitfailTempl[:-1])
    qcdpass = passCh.getObservation().sum()
    qcdfitfail = fitfailCh.getObservation().sum()
    qcdeffpass = qcdpass / qcdfitfail

    print ("TF = pass/ fail = ",qcdeffpass)

    # transfer factor
    tf_dataResidual        = rl.BernsteinPoly("CMS_bp_tf_dataResidual_"+passBinName, (nDataTF,), ['nrechits'], limits=(-40, 40))
    tf_dataResidual_params = tf_dataResidual(msdscaled)
    tf_params_pass         = qcdeffpass * tf_dataResidual_params

    # qcd params
    qcdparams = np.array([rl.IndependentParameter('CMS_bp_param_msdbin%d' % i, 0) for i in range(msd.nbins)])

    # build actual fit model now
    model = rl.Model("BPModel")
    for region in regions:
        logging.info('starting region: %s' % region)
        ch = rl.Channel(region)
        model.addChannel(ch)

        if region == 'pass'+passBinName:
            catn = 'Blind_'+passBinName
        elif region == 'SR'+passBinName:
            catn = '_'+passBinName
        elif region == 'fit'+failBinName:
            catn = 'fit_'+failBinName
        else:
            catn = 'Blind_'+failBinName

        if region=='SRBin1':
            tagname='pass'
        else:
            tagname='fail'
        # dictionary of name in datacards -> name in ROOT file
        templateNames = OrderedDict([
            ('bkg' , 'h_%s_Data'%tagname),
            ('data', 'h_%s_Data'%tagname),
            #('vll_300', 'h_%s_VLL300_ctau100'%tagname),
        ])

        templates = {}
        for temp in templateNames:
            templates[temp] = get_hist(upfile, templateNames[temp], obs=msd)

        sNames = [proc for proc in templates.keys() if proc not in ['bkg', 'data']]

        for sName in sNames:
            logging.info('get templates for: %s' % sName)
            # get templates
            templ = templates[sName]
            # don't allow them to go negative
            valuesNominal = np.maximum(templ[0], 0.)
            templ = (valuesNominal, templ[1], templ[2], templ[3])
            stype = rl.Sample.SIGNAL if 'sig' in sName else rl.Sample.BACKGROUND
            sample = rl.TemplateSample(ch.name + '_' + sName, stype, templ)
            sample.setParamEffect(lumi_13TeV_161718, 1.016)
            ch.addSample(sample)

        # data observed
        yields = templates['data'][0]
        data_obs = (yields, msd.binning, msd.name)
        ch.setObservation(data_obs)

    for passChName, failChName in regionPairs:
        logging.info('setting transfer factor for pass region %s, fail region %s' % (passChName, failChName))
        failCh = model[failChName]
        passCh = model[passChName]

        # sideband fail
        initial_qcd = failCh.getObservation().astype(float)  # was integer, and numpy complained about subtracting float from it
        sigmascale = 10  # to scale the deviation from initial
        scaledparams = initial_qcd * (1 + sigmascale/np.maximum(1., np.sqrt(initial_qcd)))**qcdparams

        # add samples
        fail_qcd = rl.ParametericSample(failChName+'_datadriven', rl.Sample.BACKGROUND, msd, scaledparams)
        failCh.addSample(fail_qcd)

        pass_qcd = rl.TransferFactorSample(passChName+'_datadriven', rl.Sample.BACKGROUND, tf_params_pass, fail_qcd)
        passCh.addSample(pass_qcd)

    with open(os.path.join(str(carddir), 'BPModel.pkl'), "wb") as fout:
        pickle.dump(model, fout, 2)  # use python 2 compatible protocol

    logging.info('rendering combine model')
    model.renderCombine(os.path.join(str(carddir), 'BPModel'))


if __name__ == '__main__':

    import argparse
    parser = argparse.ArgumentParser()
    parser.add_argument('--inputfile', default='HHTo4BPlots_Run2_BDTv8p2_0311_syst_Trigv0.root', type=str, dest='inputfile', help='input ROOT file')
    parser.add_argument('--carddir', default='cards', type=str, dest='carddir', help='output card directory')
    parser.add_argument('--nbins', default=7, type=int, dest='nbins', help='number of bins')
    parser.add_argument('--nMCTF', default=0, type=int, dest='nMCTF', help='order of polynomial for TF from MC')
    parser.add_argument('--nDataTF', default=2, type=int, dest='nDataTF', help='order of polynomial for TF from Data')
    parser.add_argument('--passBinName', default='Bin1', type=str, choices=['Bin1', 'Bin2', 'Bin3'], help='pass bin name')
    parser.add_argument('--blinded', action='store_true', help='run on data on SR')
    args = parser.parse_args()
    if not os.path.exists(args.carddir):
        os.mkdir(args.carddir)
    create_datacard(args.inputfile, args.carddir, args.nbins, args.nMCTF, args.nDataTF, args.passBinName, "fail", args.blinded)
