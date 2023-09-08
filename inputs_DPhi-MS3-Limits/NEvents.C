#include <iostream>
#include<algorithm>
#include "TString.h"
#include "TH1F.h"
#include "TCanvas.h"
#include "THStack.h"
#include "TLegend.h"
#include "TPad.h"
#include "TStyle.h"
#include "TText.h"
#include "TFile.h"
#include <stdio.h>
#include <cstdlib> /* mkdir */

#include <stdlib.h>     /* getenv */


void NEvents(){
 std::vector<TString> paths; 
 paths.push_back("root://cmsxrootd.fnal.gov//store/user/ddiaz/B-Parking/V1p19_7/ParkingBPH1_2018A/ParkingBPH1_2018A.root");
 paths.push_back("root://cmsxrootd.fnal.gov//store/user/ddiaz/B-Parking/V1p19_7/ParkingBPH2_2018A/ParkingBPH2_2018A.root");
 paths.push_back("root://cmsxrootd.fnal.gov//store/user/ddiaz/B-Parking/V1p19_7/ParkingBPH3_2018A/ParkingBPH3_2018A.root");
 paths.push_back("root://cmsxrootd.fnal.gov//store/user/ddiaz/B-Parking/V1p19_7/ParkingBPH4_2018A/ParkingBPH4_2018A.root");
 paths.push_back("root://cmsxrootd.fnal.gov//store/user/ddiaz/B-Parking/V1p19_7/ParkingBPH5_2018A/ParkingBPH5_2018A.root");
 paths.push_back("root://cmsxrootd.fnal.gov//store/user/ddiaz/B-Parking/V1p19_7/ParkingBPH6_2018A/ParkingBPH6_2018A.root");

 paths.push_back("root://cmsxrootd.fnal.gov//store/user/ddiaz/B-Parking/V1p19_7/ParkingBPH1_2018B/ParkingBPH1_2018B.root");
 paths.push_back("root://cmsxrootd.fnal.gov//store/user/ddiaz/B-Parking/V1p19_7/ParkingBPH2_2018B/ParkingBPH2_2018B.root");
 paths.push_back("root://cmsxrootd.fnal.gov//store/user/ddiaz/B-Parking/V1p19_7/ParkingBPH3_2018B/ParkingBPH3_2018B.root");
 paths.push_back("root://cmsxrootd.fnal.gov//store/user/ddiaz/B-Parking/V1p19_7/ParkingBPH4_2018B/ParkingBPH4_2018B.root");
 paths.push_back("root://cmsxrootd.fnal.gov//store/user/ddiaz/B-Parking/V1p19_7/ParkingBPH5_2018B/ParkingBPH5_2018B.root");
 paths.push_back("root://cmsxrootd.fnal.gov//store/user/ddiaz/B-Parking/V1p19_7/ParkingBPH6_2018B/ParkingBPH6_2018B.root");

 paths.push_back("root://cmsxrootd.fnal.gov//store/user/aaportel/B-Parking/V1p19_7/ParkingBPH1_2018C/ParkingBPH1_2018C.root");
 paths.push_back("root://cmsxrootd.fnal.gov//store/user/aaportel/B-Parking/V1p19_7/ParkingBPH2_2018C/ParkingBPH2_2018C.root");
 paths.push_back("root://cmsxrootd.fnal.gov//store/user/aaportel/B-Parking/V1p19_7/ParkingBPH3_2018C/ParkingBPH3_2018C.root");
 paths.push_back("root://cmsxrootd.fnal.gov//store/user/aaportel/B-Parking/V1p19_7/ParkingBPH4_2018C/ParkingBPH4_2018C.root");
 paths.push_back("root://cmsxrootd.fnal.gov//store/user/aaportel/B-Parking/V1p19_7/ParkingBPH5_2018C/ParkingBPH5_2018C.root");

 //paths.push_back("root://cmsxrootd.fnal.gov//store/user/aaportel/B-Parking/V1p19_7/ParkingBPH1_2018D/ParkingBPH1_2018D.root");
 //paths.push_back("root://cmsxrootd.fnal.gov//store/user/aaportel/B-Parking/V1p19_7/ParkingBPH2_2018D/ParkingBPH2_2018D.root");
 //paths.push_back("root://cmsxrootd.fnal.gov//store/user/aaportel/B-Parking/V1p19_7/ParkingBPH3_2018D/ParkingBPH3_2018D.root");
 //paths.push_back("root://cmsxrootd.fnal.gov//store/user/aaportel/B-Parking/V1p19_7/ParkingBPH4_2018D/ParkingBPH4_2018D.root");
 //paths.push_back("root://cmsxrootd.fnal.gov//store/user/aaportel/B-Parking/V1p19_7/ParkingBPH5_2018D/ParkingBPH5_2018D.root");

 double N = 0.0;
 for (int i=0; i<paths.size(); i++){
  TFile* f = TFile::Open(paths[i]);
  TH1F* h = (TH1F*)f->Get("NEvents")->Clone("h");
  N += h->GetBinContent(1);
  f->Close();
 }
 std::cout<<N<<std::endl;
}
