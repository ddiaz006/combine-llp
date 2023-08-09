#include <iostream>
#include <string>
//ROOT
#include <TFile.h>
#include <TH1F.h>
#include <TROOT.h>


//TH1F* SelBin(TH1F* h_in){
//  float x_bins2[n_b2] = {130,140,150,160,170,180,190,200,225,260,300}
//  TH1F* New = new TH1F(h_in->Get)
//
//
//}


void MakeInputs(){
  const int ReBin = 10;
  const float SF_sig = 1.0;
  bool rebin=false;
  bool scaleSig=false;
  TString var="h_cscRechitClusterSize_v";
  //Get Passing (OOT $ SR)
  TFile* f_OOT = TFile::Open("ParkingBPH4_2018AOOT_plots.root");
  TH1F* h_OOT_Pass_Data = (TH1F*)f_OOT->Get(var);
  if(rebin) h_OOT_Pass_Data->Rebin(ReBin);
  
  TFile* f_OOT_Sig_M0p3_ctau300 = TFile::Open("BToKPhi_MuonLLPDecayGenFilter_PhiToPi0Pi0_mPhi0p3_ctau300OOT_plots.root");
  TH1F* h_OOT_Pass_Sig_M0p3_ctau300 = (TH1F*)f_OOT_Sig_M0p3_ctau300->Get(var);
  if(rebin) h_OOT_Pass_Sig_M0p3_ctau300->Rebin(ReBin);
  if(scaleSig) h_OOT_Pass_Sig_M0p3_ctau300->Scale(SF_sig);
  
  TFile* f_SR = TFile::Open("ParkingBPH4_2018ASR_plots.root");
  TH1F* h_SR_Pass_Data = (TH1F*)f_SR->Get(var);
  if(rebin) h_SR_Pass_Data->Rebin(ReBin);
  
  TFile* f_SR_Sig_M0p3_ctau300 = TFile::Open("BToKPhi_MuonLLPDecayGenFilter_PhiToPi0Pi0_mPhi0p3_ctau300SR_plots.root");
  TH1F* h_SR_Pass_Sig_M0p3_ctau300 = (TH1F*)f_SR_Sig_M0p3_ctau300->Get(var);
  if(rebin) h_SR_Pass_Sig_M0p3_ctau300->Rebin(ReBin);
  if(scaleSig) h_SR_Pass_Sig_M0p3_ctau300->Scale(SF_sig);
  
  
  
  //Get Failing (test $ testOOT)
  TFile* f_test = TFile::Open("ParkingBPH4_2018Atest_plots.root");
  TH1F* h_test_Fail_Data = (TH1F*)f_test->Get(var);
  if(rebin) h_test_Fail_Data->Rebin(ReBin);
  
  TFile* f_test_Sig_M0p3_ctau300 = TFile::Open("BToKPhi_MuonLLPDecayGenFilter_PhiToPi0Pi0_mPhi0p3_ctau300test_plots.root");
  TH1F* h_test_Fail_Sig_M0p3_ctau300 = (TH1F*)f_test_Sig_M0p3_ctau300->Get(var);
  if(rebin) h_test_Fail_Sig_M0p3_ctau300->Rebin(ReBin);
  if(scaleSig) h_test_Fail_Sig_M0p3_ctau300->Scale(SF_sig);
  
  TFile* f_testOOT = TFile::Open("ParkingBPH4_2018AtestOOT_plots.root");
  TH1F* h_testOOT_Fail_Data = (TH1F*)f_testOOT->Get(var);
  if(rebin) h_testOOT_Fail_Data->Rebin(ReBin);
  
  TFile* f_testOOT_Sig_M0p3_ctau300 = TFile::Open("BToKPhi_MuonLLPDecayGenFilter_PhiToPi0Pi0_mPhi0p3_ctau300testOOT_plots.root");
  TH1F* h_testOOT_Fail_Sig_M0p3_ctau300 = (TH1F*)f_testOOT_Sig_M0p3_ctau300->Get(var);
  if(rebin) h_testOOT_Fail_Sig_M0p3_ctau300->Rebin(ReBin);
  if(scaleSig) h_testOOT_Fail_Sig_M0p3_ctau300->Scale(SF_sig);
  
  
  TFile* fout = new TFile("inputs_csc.root", "RECREATE");
  h_SR_Pass_Data->Write("h_pass_Data");
  h_test_Fail_Data->Write("h_fail_Data");
  h_SR_Pass_Sig_M0p3_ctau300->Write("h_pass_Sig_M0p3_ctau300");
  h_test_Fail_Sig_M0p3_ctau300->Write("h_fail_Sig_M0p3_ctau300");
  fout->Close();
  
  TFile* fout_OOT = new TFile("inputs_csc_OOT.root", "RECREATE");
  h_SR_Pass_Data->Write("h_pass_Data");
  h_test_Fail_Data->Write("h_fail_Data");
  h_SR_Pass_Sig_M0p3_ctau300->Write("h_pass_Sig_M0p3_ctau300");
  h_test_Fail_Sig_M0p3_ctau300->Write("h_fail_Sig_M0p3_ctau300");
  fout_OOT->Close();
}
