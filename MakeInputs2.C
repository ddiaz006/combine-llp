#include <iostream>
#include <string>
//ROOT
#include <TFile.h>
#include <TH1F.h>
#include <TROOT.h>

const int ReBin = 10;
//sigma= 5.72e11
const float SF_sig = 3.083; //the lumi
bool rebin=false;
bool scaleSig=true;
TString var="h_cscRechitClusterSize_v";

TH1F* getHisto(TString region, TString Name){
   TFile* f = TFile::Open(Name+region+"_plots.root");
   TH1F* h = (TH1F*)f->Get(var);
   if(rebin) h->Rebin(ReBin);
   if( Name.Contains("BToKPhi") && scaleSig ) h->Scale(SF_sig); 
   return h;
}

void MakeInputs2(TString Type){

  std::vector<TH1F*> histos;

  std::vector< std::pair<TString,TString> > names;

  //map of names, should be one for each pass/fail pair
  names.push_back(std::pair<TString,TString>("Parking_2018Ato","Data"));
  names.push_back(std::pair<TString,TString>("BToKPhi_MuonLLPDecayGenFilter_PhiToPi0Pi0_mPhi0p3_ctau300to1"   ,"Sig_M0p3_ctau1"));
  names.push_back(std::pair<TString,TString>("BToKPhi_MuonLLPDecayGenFilter_PhiToPi0Pi0_mPhi0p3_ctau300to5"   ,"Sig_M0p3_ctau5"));
  names.push_back(std::pair<TString,TString>("BToKPhi_MuonLLPDecayGenFilter_PhiToPi0Pi0_mPhi0p3_ctau300to7"   ,"Sig_M0p3_ctau7"));
  names.push_back(std::pair<TString,TString>("BToKPhi_MuonLLPDecayGenFilter_PhiToPi0Pi0_mPhi0p3_ctau300to10"  ,"Sig_M0p3_ctau10"));
  names.push_back(std::pair<TString,TString>("BToKPhi_MuonLLPDecayGenFilter_PhiToPi0Pi0_mPhi0p3_ctau300to30"  ,"Sig_M0p3_ctau30"));
  names.push_back(std::pair<TString,TString>("BToKPhi_MuonLLPDecayGenFilter_PhiToPi0Pi0_mPhi0p3_ctau300to50"  ,"Sig_M0p3_ctau50"));
  names.push_back(std::pair<TString,TString>("BToKPhi_MuonLLPDecayGenFilter_PhiToPi0Pi0_mPhi0p3_ctau300to70"  ,"Sig_M0p3_ctau70"));
  names.push_back(std::pair<TString,TString>("BToKPhi_MuonLLPDecayGenFilter_PhiToPi0Pi0_mPhi0p3_ctau300to100" ,"Sig_M0p3_ctau100"));
  names.push_back(std::pair<TString,TString>("BToKPhi_MuonLLPDecayGenFilter_PhiToPi0Pi0_mPhi0p3_ctau300to300" ,"Sig_M0p3_ctau300"));
  names.push_back(std::pair<TString,TString>("BToKPhi_MuonLLPDecayGenFilter_PhiToPi0Pi0_mPhi0p3_ctau300to500" ,"Sig_M0p3_ctau500"));
  names.push_back(std::pair<TString,TString>("BToKPhi_MuonLLPDecayGenFilter_PhiToPi0Pi0_mPhi0p3_ctau300to700" ,"Sig_M0p3_ctau700"));

  //std::cout<<names[0].first<<"  "<<names[0].second<<std::endl;
  //make histos/fill histos vector
  for(int i=0; i<names.size(); i++ ) {
    if(Type==""){
      histos.push_back(getHisto("test",names[i].first));
      histos.push_back(getHisto("SR"  ,names[i].first));
    }
    else if(Type=="OOT"){
      histos.push_back(getHisto("testOOT",names[i].first));
      histos.push_back(getHisto("OOT"  ,names[i].first));
    }
    else {std::cout<<"Incorrect Type"<<std::endl; break;}
  }

//  //Write histos to root file
  TFile* fout = new TFile("inputs_csc_"+Type+".root", "RECREATE");
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
