//C++
#include <iostream>
#include <fstream>
#include <map>
#include <stdlib.h>
#include <utility>
//ROOT
#include <TFile.h>
#include <TTree.h>
#include <TGraph.h>
#include <TGraphErrors.h>
#include <TAxis.h>
#include <TCanvas.h>
#include <TStyle.h>
#include <TLatex.h>
#include <TLegend.h>
//LOCAL INCLUDES
#include "CommandLineInput.hh"

struct Limit
{
  double obs;
  double exp0p025;
  double exp0p16;
  double exp0p5;
  double exp0p84;
  double exp0p975;
};


const float lumi = 5;
const float min = 5e-7;
const float max = 0.1;

//exp/obs limit line color
Color_t Color_lim_pi0   = kBlue+2;
Color_t Color_lim_pihad = kRed+2;
//Axis
const float axisTitleSize = 0.06;
const float axisTitleOffset = .8;

const float axisTitleSizeRatioX   = 0.18;
const float axisLabelSizeRatioX   = 0.12;
const float axisTitleOffsetRatioX = 0.94;

const float axisTitleSizeRatioY   = 0.15;
const float axisLabelSizeRatioY   = 0.108;
const float axisTitleOffsetRatioY = 0.32;

//Margins
const float leftMargin   = 0.12;
const float rightMargin  = 0.05;
const float topMargin    = 0.07;
const float bottomMargin = 0.12;

//CMS STANDARD
TString CMSText = "CMS";
//TString extraText   = "";
TString extraText   = "Preliminary";
TString lumiText = "41.6 fb^{-1} (13 TeV)";

bool AddCMS( TCanvas* C )
{
  C->cd();
  float lumix = 0.955;
  float lumiy = 0.945;
  float lumifont = 42;

  float cmsx = 0.25;
  float cmsy = 0.94;
  float cmsTextFont   = 61;  // default is helvetic-bold
  float extrax = cmsx +0.20;
  float extray = cmsy;
  float extraTextFont = 52;  // default is helvetica-italics
  // ratio of "CMS" and extra text size
  float extraOverCmsTextSize  = 0.76;
  float cmsSize = 0.06;
  TLatex latex;
  latex.SetNDC();
  latex.SetTextAngle(0);
  latex.SetTextColor(kBlack);
  float extraTextSize = extraOverCmsTextSize*cmsSize;
  latex.SetTextFont(lumifont);
  latex.SetTextAlign(31);
  latex.SetTextSize(cmsSize);
  latex.DrawLatex(lumix, lumiy,lumiText);

  latex.SetTextFont(cmsTextFont);
  latex.SetTextAlign(31);
  latex.SetTextSize(cmsSize);
  latex.DrawLatex(cmsx, cmsy, CMSText);

  latex.SetTextFont(extraTextFont);
  latex.SetTextAlign(31);
  latex.SetTextSize(extraTextSize);
  latex.DrawLatex(extrax, extray, extraText);
  return true;
};


//bool AddCMS( TCanvas* C );

int main( int argc, char** argv )
{

TString s_region="";
  //-----------------
  //Input File List
  //-----------------
  std::string inputList = ParseCommandLine( argc, argv, "-inputList=" );
  if (  inputList == "" )
    {
      std::cerr << "[ERROR]: please provide an inputList. Use --inputList=" << std::endl;
      return -1;
    }
  std::ifstream ifs ( inputList.c_str(), std::ifstream::in );//input file list


  std::map<float, Limit> mymap_pi0;
  std::map<float, Limit> mymap_pihad;

  std::string fname;
  TString s_fname;
  if( ifs.is_open() )
    {
      while( ifs.good() )
	{
	  ifs >> fname;
          s_fname=fname;
	  if ( ifs.eof() ) break;
	  TFile* fin = new TFile( fname.c_str(), "READ" );
	  if ( fin->IsZombie() ) continue;

          int low = fname.find("ctau");
	  int high = fname.find("/BPModel");
	  std::string ctau = fname.substr( low+4, high-low-4 );
	  float _ctau = atof( ctau.c_str() );

	  TTree* tree = (TTree*)fin->Get("limit");
	  double limit;
	  Limit tmpLimit;
	  double limitSF = 100000000.*(1./5.72E11);
	  tree->SetBranchAddress( "limit", &limit );
	  tree->GetEntry(0);
	  tmpLimit.exp0p025 = limit*limitSF;
	  tree->GetEntry(1);
	  tmpLimit.exp0p16 = limit*limitSF;
	  tree->GetEntry(2);
	  tmpLimit.exp0p5 = limit*limitSF;
	  tree->GetEntry(3);
	  tmpLimit.exp0p84 = limit*limitSF;
	  tree->GetEntry(4);
	  tmpLimit.exp0p975 = limit*limitSF;
	  //tree->GetEntry(5);
	  //tmpLimit.obs = limit*limitSF*xsecMap[_mass].first;
	  tmpLimit.obs = tmpLimit.exp0p5;

	  std::cout << "ctau: " << ctau << "-> " << tmpLimit.exp0p025 << " " << tmpLimit.exp0p16 << " " << tmpLimit.exp0p5 << " " << tmpLimit.exp0p84<< " " 
                    << tmpLimit.exp0p975 << " " << tmpLimit.obs << std::endl;

          if (s_fname.Contains("SigPi0")){
	    if ( mymap_pi0.find( _ctau ) == mymap_pi0.end() )
	      {
	        mymap_pi0[_ctau] = tmpLimit;
	      }
          }
          if (s_fname.Contains("SigPiPlusPiMinus")){
	    if ( mymap_pihad.find( _ctau ) == mymap_pihad.end() )
	      {
	        mymap_pihad[_ctau] = tmpLimit;
	      }
          }
          if(s_fname.Contains("csc")) s_region="CSC";
          if(s_fname.Contains("dt"))  s_region="DT";
	  delete fin;
	}
    }
  else
    {
      std::cerr << "[ERROR] can't open file " << inputList << std::endl;
    }
  std::cout<<"Pi0"<<std::endl;
  for ( auto tmp : mymap_pi0 ){std::cout << "cTau: " << tmp.first << " " << tmp.second.exp0p5 << std::endl;}
  std::cout<<"Pihad"<<std::endl;
  for ( auto tmp : mymap_pihad ){std::cout << "cTau: " << tmp.first << " " << tmp.second.exp0p5 << std::endl;}
  std::cout<<"end line check"<<std::endl;
  TFile* out   = new TFile("out_test.root", "recreate");
//begin lines
//--------------Pi0
  int npoints_pi0 = mymap_pi0.size();
  float x_pi0[npoints_pi0];
  float expL_pi0[npoints_pi0];
  float obsL_pi0[npoints_pi0];

  float xp_pi0[2*npoints_pi0];
  float OneS_pi0[2*npoints_pi0];
  //float TwoS_pi0[2*npoints_pi0];

  int ctr = 0;
  for ( auto tmp : mymap_pi0 )
    {
      x_pi0[ctr]      = tmp.first;
      obsL_pi0[ctr]   = tmp.second.obs;
      expL_pi0[ctr]   = tmp.second.exp0p5;

      xp_pi0[ctr] = tmp.first;
      xp_pi0[2*npoints_pi0-(ctr+1)] = tmp.first;

      OneS_pi0[ctr] = tmp.second.exp0p16;
      OneS_pi0[2*npoints_pi0-(ctr+1)] = tmp.second.exp0p84;

      //TwoS_pi0[ctr] = tmp.second.exp0p025;
      //TwoS_pi0[2*npoints_pi0-(ctr+1)] = tmp.second.exp0p975;

      ctr++;
    }

  TGraph* gObs_pi0 = new TGraph(npoints_pi0, x_pi0, obsL_pi0);
  TGraph* gExp_pi0 = new TGraph(npoints_pi0, x_pi0, expL_pi0);

  TGraph* gOneS_pi0 = new TGraph(2*npoints_pi0, xp_pi0, OneS_pi0);
  //formatting
  gExp_pi0        ->SetLineStyle(9);
  gExp_pi0        ->SetLineWidth(2);
  gExp_pi0        ->SetLineColor(Color_lim_pi0);
  gExp_pi0        ->SetLineWidth(3);
  gExp_pi0        ->SetTitle("");
  gExp_pi0        ->SetMarkerStyle(31);
  gExp_pi0        ->SetMarkerColor(Color_lim_pi0);
  gExp_pi0        ->SetMarkerSize(1);
  gExp_pi0        ->GetXaxis()->SetTitleSize(0.05);
  gExp_pi0        ->GetXaxis()->SetLabelOffset( 0.003);
  gExp_pi0        ->GetXaxis()->SetTitleOffset( 0.95);
  gExp_pi0        ->GetYaxis()->SetTitleSize(0.05);
  gExp_pi0        ->GetYaxis()->CenterTitle(kTRUE);
  gExp_pi0        ->GetYaxis()->SetRangeUser(0,40);
  gExp_pi0        ->SetMaximum(max);
  gExp_pi0        ->SetMinimum(min); //HZ
  //gExp_pi0        ->GetXaxis()->SetLimits(xdwn,xup);
  gObs_pi0        ->GetXaxis()->SetTitle("#Phi proper decay length [mm]");
  gObs_pi0        ->GetYaxis()->SetTitle("95 % CL Upper Limit on BR(B #rightarrow K#Phi)");
  gExp_pi0        ->GetXaxis()->SetTitle("#Phi proper decay length [mm]");
  gExp_pi0        ->GetYaxis()->SetTitle("95 % CL Upper Limit on BR(B #rightarrow K#Phi)");
  gOneS_pi0        ->GetXaxis()->SetTitle("#Phi proper decay length [mm]");
  gOneS_pi0        ->GetYaxis()->SetTitle("95 % CL Upper Limit on BR(B #rightarrow K#Phi)");


  gExp_pi0->SetLineWidth(3);
  gExp_pi0->SetLineStyle(2);
  gObs_pi0->SetLineWidth(2);
  gObs_pi0->SetMarkerSize(0.5);
  gObs_pi0->SetMarkerStyle(20);
  gObs_pi0->SetLineWidth(3);

  gOneS_pi0->SetTitle("");
  gOneS_pi0->SetFillColor(Color_lim_pi0);
  gOneS_pi0->SetFillColorAlpha(Color_lim_pi0, 0.15);;
  gOneS_pi0->SetLineColor(Color_lim_pi0);
  gOneS_pi0->GetXaxis()->SetTitleSize(0.05);
  gOneS_pi0->GetXaxis()->SetLabelOffset( 0.003);
  gOneS_pi0->GetXaxis()->SetTitleOffset( 0.95);
  gOneS_pi0->GetYaxis()->SetTitleSize(0.05);
  gOneS_pi0->GetYaxis()->CenterTitle(kTRUE);
  gOneS_pi0->GetYaxis()->SetRangeUser(0,15);
  gOneS_pi0->SetMaximum(max);
  gOneS_pi0->SetMinimum(min); //HZ
  gOneS_pi0->GetXaxis()->SetLimits(0,1000);
//---------- end Pi0
//--------------Pihad
  int npoints_pihad = mymap_pihad.size();
  float x_pihad[npoints_pihad];
  float expL_pihad[npoints_pihad];
  float obsL_pihad[npoints_pihad];

  float xp_pihad[2*npoints_pihad];
  float OneS_pihad[2*npoints_pihad];
  //float TwoS_pihad[2*npoints_pihad];

  ctr = 0;
  for ( auto tmp : mymap_pihad )
    {
      x_pihad[ctr]      = tmp.first;
      obsL_pihad[ctr]   = tmp.second.obs;
      expL_pihad[ctr]   = tmp.second.exp0p5;

      xp_pihad[ctr] = tmp.first;
      xp_pihad[2*npoints_pihad-(ctr+1)] = tmp.first;

      OneS_pihad[ctr] = tmp.second.exp0p16;
      OneS_pihad[2*npoints_pihad-(ctr+1)] = tmp.second.exp0p84;

      //TwoS_pihad[ctr] = tmp.second.exp0p025;
      //TwoS_pihad[2*npoints_pihad-(ctr+1)] = tmp.second.exp0p975;

      ctr++;
    }

  //TFile* out   = new TFile("out_test.root", "recreate");
  TGraph* gObs_pihad = new TGraph(npoints_pihad, x_pihad, obsL_pihad);
  TGraph* gExp_pihad = new TGraph(npoints_pihad, x_pihad, expL_pihad);

  TGraph* gOneS_pihad = new TGraph(2*npoints_pihad, xp_pihad, OneS_pihad);
  //TGraph* gTwoS_pihad = new TGraph(2*npoints_pihad, xp_pihad, TwoS_pihad);
  //formatting
  gExp_pihad->SetLineWidth(3);
  gExp_pihad->SetLineStyle(2);
  gObs_pihad->SetLineWidth(2);
  gObs_pihad->SetMarkerSize(0.5);
  gObs_pihad->SetMarkerStyle(20);
  gObs_pihad->SetLineWidth(3);

  gOneS_pihad->SetTitle("");
 
  gOneS_pihad->SetFillColor(Color_lim_pihad);
  gOneS_pihad->SetLineColor(Color_lim_pihad);
  gOneS_pihad->SetFillColorAlpha(Color_lim_pihad, 0.15);;
  gOneS_pihad->GetXaxis()->SetTitleSize(0.05);
  gOneS_pihad->GetXaxis()->SetLabelOffset( 0.003);
  gOneS_pihad->GetXaxis()->SetTitleOffset( 0.95);
  gOneS_pihad->GetYaxis()->SetTitleSize(0.05);
  gOneS_pihad->GetYaxis()->CenterTitle(kTRUE);
  gOneS_pihad->GetYaxis()->SetRangeUser(0,15);
  gOneS_pihad->SetMaximum(max);
  gOneS_pihad->SetMinimum(min); //HZ
  gOneS_pihad->GetXaxis()->SetLimits(0,1000);
  //formatting
  gExp_pihad        ->SetLineStyle(9);
  gExp_pihad        ->SetLineWidth(2);
  gExp_pihad        ->SetLineColor(Color_lim_pihad);
  gExp_pihad        ->SetLineWidth(3);
  gExp_pihad        ->SetTitle("");
  gExp_pihad        ->SetMarkerStyle(31);
  gExp_pihad        ->SetMarkerColor(Color_lim_pihad);
  gExp_pihad        ->SetMarkerSize(1);
  gExp_pihad        ->GetXaxis()->SetTitleSize(0.05);
  gExp_pihad        ->GetXaxis()->SetLabelOffset( 0.003);
  gExp_pihad        ->GetXaxis()->SetTitleOffset( 0.95);
  gExp_pihad        ->GetYaxis()->SetTitleSize(0.05);
  gExp_pihad        ->GetYaxis()->CenterTitle(kTRUE);
  gExp_pihad        ->GetYaxis()->SetRangeUser(0,40);
  gExp_pihad        ->SetMaximum(max);
  gExp_pihad        ->SetMinimum(min); //HZ
  //set labels
  gObs_pihad        ->GetXaxis()->SetTitle("#Phi proper decay length [mm]");
  gObs_pihad        ->GetYaxis()->SetTitle("95 % CL Upper Limit on BR(B #rightarrow K#Phi)");
  gExp_pihad        ->GetXaxis()->SetTitle("#Phi proper decay length [mm]");
  gExp_pihad        ->GetYaxis()->SetTitle("95 % CL Upper Limit on BR(B #rightarrow K#Phi)");
  gOneS_pihad        ->GetXaxis()->SetTitle("#Phi proper decay length [mm]");
  gOneS_pihad        ->GetYaxis()->SetTitle("95 % CL Upper Limit on BR(B #rightarrow K#Phi)");
//---------- end Pihad
//end lines
  TCanvas* c = new TCanvas( "c", "c", 2119, 33, 800, 700 );
  c->SetHighLightColor(2);
  c->SetFillColor(0);
  c->SetBorderMode(0);
  c->SetBorderSize(2);
  c->SetLeftMargin( leftMargin );
  c->SetRightMargin( rightMargin );
  c->SetTopMargin( topMargin );
  c->SetBottomMargin( bottomMargin );
  c->SetFrameBorderMode(0);
  c->SetFrameBorderMode(0);
  c->SetLogy();
  c->SetLogx();

  gStyle->SetPaintTextFormat("4.3f");


  //---------Draw
  //gTwoS_pi0->Draw("AF");
  //gObs_pi0->Draw("L");
  gExp_pi0->Draw("AL");
  gExp_pihad->Draw("L");
  gOneS_pi0->Draw("F");
  gOneS_pihad->Draw("F");

  TLegend* leg2 = new TLegend( 0.15, 0.15, 0.5, 0.3, NULL, "brNDC" );
  leg2->SetBorderSize(0);
  leg2->SetLineColor(1);
  leg2->SetLineStyle(1);
  leg2->SetLineWidth(1);
  leg2->SetFillColor(0);
  leg2->SetFillStyle(1001);
  leg2->SetTextSize(0.04);
  leg2->SetNColumns(1);
 
  TLegend* leg3 = new TLegend( 0.5, 0.15, 0.95, 0.3, NULL, "brNDC" );
  leg3->SetBorderSize(0);
  leg3->SetLineColor(1);
  leg3->SetLineStyle(1);
  leg3->SetLineWidth(1);
  leg3->SetFillColor(0);
  leg3->SetFillStyle(1001);
  leg3->SetTextSize(0.04);
  leg3->SetNColumns(1);
  
  leg2->AddEntry( gExp_pi0,   "#Phi #rightarrow  #Pi^{0}#Pi^{0}", "l" );
  leg2->AddEntry( gExp_pihad, "#Phi #rightarrow  #Pi^{+}#Pi^{-}", "l" );
  leg2->Draw("SAME");

  leg3->AddEntry( gOneS_pi0, "#pm 1 s.d. expected", "f" );
  leg3->AddEntry( gOneS_pihad, "#pm 1 s.d. expected", "f" );
  leg3->Draw("SAME");


  //95% CL label
  float cmsx = 0.81;
  float cmsy = 0.63-0.05;
  float cmsSize = 0.04;
  float cmsTextFont = 41;  // default is helvetic-bold
  TLatex latex;
  latex.SetNDC();
  latex.SetTextAngle(0);
  latex.SetTextColor(kBlack);
  latex.SetTextAlign(31);
  latex.SetTextSize(cmsSize);
  latex.SetTextFont(cmsTextFont);
  //latex.DrawLatex(cmsx, cmsy, "95% CL upper limits");

  TLatex latex2;
  cmsx = 0.29;
  cmsy = 0.88;
  latex2.SetNDC();
  latex2.SetTextSize(0.038);
  latex2.SetTextFont(42);
  latex2.DrawLatex(cmsx+0.05, cmsy, "m_{#Phi} = 0.3 GeV; Detector Region: "+s_region);
  TLatex latex3;
  latex3.SetNDC();
  latex3.SetTextSize(0.038);
  latex3.SetTextFont(42);
  AddCMS(c);

  //c->SetLogx();
  c->SaveAs("Limit_bp.pdf");
  c->SaveAs("Limit_bp.C");

  gObs_pi0->GetXaxis()->SetRangeUser(0, 30);
  gObs_pi0->Write("gObs");
  gExp_pi0->GetXaxis()->SetRangeUser(0, 30);
  gExp_pi0->Write("gExp");
  gOneS_pi0->Write("gOneS");

  out->Close();
  return 0;
}


