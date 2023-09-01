#include <iostream>
#include <string>
//ROOT
#include <TFile.h>
#include <TH1F.h>
#include <TROOT.h>

const int ReBin = 10;
//sigma= 5.72e11
//Try scaling by 200*(1/Integral())
const float SF_sig = 14.545*100000000.; //the lumi
float SF2 = 40.3458/14.545;
bool rebin=false;
bool scaleSig=true;

TString detector_region = "csc"; //"csc" or "dt" 
TString signalType = "SigPi0_M0p3";  //"SigPi0_M0p3" or "SigPiPlusPiMinus_M0p3"


TH1F* getHisto(TString region, TString Name, TString var){
   TFile* f = TFile::Open(Name+"_"+region+"_plots.root");
   TH1F* h = (TH1F*)f->Get(var);
   if(rebin) h->Rebin(ReBin);
   if( Name.Contains("BToKPhi") && scaleSig ) h->Scale(SF_sig); 
   h->Scale(SF2);
   return h;
}

void MakeInputs(TString Type){
TString var; 
  if      (detector_region == "csc") var="h_cscRechitClusterSize_v";
  else if (detector_region == "dt")  var="h_dtRechitClusterSize_v";
  else    {std::cout<<"bad detector region"<<std::endl;}

  std::vector<TH1F*> histos;

  std::vector< std::pair<TString,TString> > names;

  //map of names, should be one for each pass/fail pair
  if(signalType=="SigPi0_M0p3"){
    names.push_back(std::pair<TString,TString>("Parking_2018","Data"));
    names.push_back(std::pair<TString,TString>("BToKPhi_MuonLLPDecayGenFilter_PhiToPi0Pi0_mPhi0p3_ctau300to1"     ,"SigPi0_M0p3_ctau1"));
    names.push_back(std::pair<TString,TString>("BToKPhi_MuonLLPDecayGenFilter_PhiToPi0Pi0_mPhi0p3_ctau300to3"     ,"SigPi0_M0p3_ctau3"));
    names.push_back(std::pair<TString,TString>("BToKPhi_MuonLLPDecayGenFilter_PhiToPi0Pi0_mPhi0p3_ctau300to5"     ,"SigPi0_M0p3_ctau5"));
    names.push_back(std::pair<TString,TString>("BToKPhi_MuonLLPDecayGenFilter_PhiToPi0Pi0_mPhi0p3_ctau300to7"     ,"SigPi0_M0p3_ctau7"));
    names.push_back(std::pair<TString,TString>("BToKPhi_MuonLLPDecayGenFilter_PhiToPi0Pi0_mPhi0p3_ctau300to10"    ,"SigPi0_M0p3_ctau10"));
    names.push_back(std::pair<TString,TString>("BToKPhi_MuonLLPDecayGenFilter_PhiToPi0Pi0_mPhi0p3_ctau300to30"    ,"SigPi0_M0p3_ctau30"));
    names.push_back(std::pair<TString,TString>("BToKPhi_MuonLLPDecayGenFilter_PhiToPi0Pi0_mPhi0p3_ctau300to50"    ,"SigPi0_M0p3_ctau50"));
    names.push_back(std::pair<TString,TString>("BToKPhi_MuonLLPDecayGenFilter_PhiToPi0Pi0_mPhi0p3_ctau300to70"    ,"SigPi0_M0p3_ctau70"));
    names.push_back(std::pair<TString,TString>("BToKPhi_MuonLLPDecayGenFilter_PhiToPi0Pi0_mPhi0p3_ctau300to100"   ,"SigPi0_M0p3_ctau100"));
    names.push_back(std::pair<TString,TString>("BToKPhi_MuonLLPDecayGenFilter_PhiToPi0Pi0_mPhi0p3_ctau300to300"   ,"SigPi0_M0p3_ctau300"));
    names.push_back(std::pair<TString,TString>("BToKPhi_MuonLLPDecayGenFilter_PhiToPi0Pi0_mPhi0p3_ctau300to500"   ,"SigPi0_M0p3_ctau500"));
    names.push_back(std::pair<TString,TString>("BToKPhi_MuonLLPDecayGenFilter_PhiToPi0Pi0_mPhi0p3_ctau300to700"   ,"SigPi0_M0p3_ctau700"));
    names.push_back(std::pair<TString,TString>("BToKPhi_MuonLLPDecayGenFilter_PhiToPi0Pi0_mPhi0p3_ctau300to1000"  ,"SigPi0_M0p3_ctau1000"));
    names.push_back(std::pair<TString,TString>("BToKPhi_MuonLLPDecayGenFilter_PhiToPi0Pi0_mPhi0p3_ctau300to3000"  ,"SigPi0_M0p3_ctau3000"));
    names.push_back(std::pair<TString,TString>("BToKPhi_MuonLLPDecayGenFilter_PhiToPi0Pi0_mPhi0p3_ctau300to5000"  ,"SigPi0_M0p3_ctau5000"));
    names.push_back(std::pair<TString,TString>("BToKPhi_MuonLLPDecayGenFilter_PhiToPi0Pi0_mPhi0p3_ctau300to7000"  ,"SigPi0_M0p3_ctau7000"));
    names.push_back(std::pair<TString,TString>("BToKPhi_MuonLLPDecayGenFilter_PhiToPi0Pi0_mPhi0p3_ctau300to10000" ,"SigPi0_M0p3_ctau10000"));
  }
  else if (signalType=="SigPiPlusPiMinus_M0p3"){
    names.push_back(std::pair<TString,TString>("Parking_2018","Data"));
    names.push_back(std::pair<TString,TString>("BToKPhi_MuonLLPDecayGenFilter_PhiToPiPlusPiMinus_mPhi0p3_ctau300to1"     ,"SigPiPlusPiMinus_M0p3_ctau1"));
    names.push_back(std::pair<TString,TString>("BToKPhi_MuonLLPDecayGenFilter_PhiToPiPlusPiMinus_mPhi0p3_ctau300to3"     ,"SigPiPlusPiMinus_M0p3_ctau3"));
    names.push_back(std::pair<TString,TString>("BToKPhi_MuonLLPDecayGenFilter_PhiToPiPlusPiMinus_mPhi0p3_ctau300to5"     ,"SigPiPlusPiMinus_M0p3_ctau5"));
    names.push_back(std::pair<TString,TString>("BToKPhi_MuonLLPDecayGenFilter_PhiToPiPlusPiMinus_mPhi0p3_ctau300to7"     ,"SigPiPlusPiMinus_M0p3_ctau7"));
    names.push_back(std::pair<TString,TString>("BToKPhi_MuonLLPDecayGenFilter_PhiToPiPlusPiMinus_mPhi0p3_ctau300to10"    ,"SigPiPlusPiMinus_M0p3_ctau10"));
    names.push_back(std::pair<TString,TString>("BToKPhi_MuonLLPDecayGenFilter_PhiToPiPlusPiMinus_mPhi0p3_ctau300to30"    ,"SigPiPlusPiMinus_M0p3_ctau30"));
    names.push_back(std::pair<TString,TString>("BToKPhi_MuonLLPDecayGenFilter_PhiToPiPlusPiMinus_mPhi0p3_ctau300to50"    ,"SigPiPlusPiMinus_M0p3_ctau50"));
    names.push_back(std::pair<TString,TString>("BToKPhi_MuonLLPDecayGenFilter_PhiToPiPlusPiMinus_mPhi0p3_ctau300to70"    ,"SigPiPlusPiMinus_M0p3_ctau70"));
    names.push_back(std::pair<TString,TString>("BToKPhi_MuonLLPDecayGenFilter_PhiToPiPlusPiMinus_mPhi0p3_ctau300to100"   ,"SigPiPlusPiMinus_M0p3_ctau100"));
    names.push_back(std::pair<TString,TString>("BToKPhi_MuonLLPDecayGenFilter_PhiToPiPlusPiMinus_mPhi0p3_ctau300to300"   ,"SigPiPlusPiMinus_M0p3_ctau300"));
    names.push_back(std::pair<TString,TString>("BToKPhi_MuonLLPDecayGenFilter_PhiToPiPlusPiMinus_mPhi0p3_ctau300to500"   ,"SigPiPlusPiMinus_M0p3_ctau500"));
    names.push_back(std::pair<TString,TString>("BToKPhi_MuonLLPDecayGenFilter_PhiToPiPlusPiMinus_mPhi0p3_ctau300to700"   ,"SigPiPlusPiMinus_M0p3_ctau700"));
    names.push_back(std::pair<TString,TString>("BToKPhi_MuonLLPDecayGenFilter_PhiToPiPlusPiMinus_mPhi0p3_ctau300to1000"  ,"SigPiPlusPiMinus_M0p3_ctau1000"));
    names.push_back(std::pair<TString,TString>("BToKPhi_MuonLLPDecayGenFilter_PhiToPiPlusPiMinus_mPhi0p3_ctau300to3000"  ,"SigPiPlusPiMinus_M0p3_ctau3000"));
    names.push_back(std::pair<TString,TString>("BToKPhi_MuonLLPDecayGenFilter_PhiToPiPlusPiMinus_mPhi0p3_ctau300to5000"  ,"SigPiPlusPiMinus_M0p3_ctau5000"));
    names.push_back(std::pair<TString,TString>("BToKPhi_MuonLLPDecayGenFilter_PhiToPiPlusPiMinus_mPhi0p3_ctau300to7000"  ,"SigPiPlusPiMinus_M0p3_ctau7000"));
    names.push_back(std::pair<TString,TString>("BToKPhi_MuonLLPDecayGenFilter_PhiToPiPlusPiMinus_mPhi0p3_ctau300to10000" ,"SigPiPlusPiMinus_M0p3_ctau10000"));
  }
  else {std::cout<<"bad signalType"<<std::endl;}
  //std::cout<<names[0].first<<"  "<<names[0].second<<std::endl;
  //make histos/fill histos vector
  for(int i=0; i<names.size(); i++ ) {
    if(Type==""){
      histos.push_back(getHisto("test",names[i].first, var));
      histos.push_back(getHisto("SR"  ,names[i].first, var));
    }
    else if(Type=="OOT"){
      histos.push_back(getHisto("testOOT",names[i].first, var));
      histos.push_back(getHisto("OOT"  ,names[i].first, var));
    }
    else {std::cout<<"Incorrect Type"<<std::endl; break;}
  }

//  //Write histos to root file
  TFile* fout = new TFile("inputs_"+detector_region+"_"+signalType+"_"+Type+".root", "RECREATE");
  int index;
  for(int i=0; i<histos.size(); i++){
    index = i/2;
    std::cout<<i<<"  "<<names[index].second<<"   "<<histos[i]->Integral()<<std::endl;
    TString name;
    if( (i+1)%2 == 0) name="h_pass_"+names[index].second;
    else              name="h_fail_"+names[index].second;
    histos[i]->Write(name);   
  }
  fout->Close();
}
