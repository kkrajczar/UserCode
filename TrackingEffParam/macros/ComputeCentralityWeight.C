// Messy macro the compute the centrality weights
// It has grown starting from a single bin by copy-paste
// Should switch to loop based method instead of this
// It defines tons of histos now individually...

#include "hiForest.h"
#include "TStyle.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TH3.h"
#include "TH2.h"
#include "TH1.h"
#include "TNtuple.h"
#include "TMath.h"

#include "TCut.h"
#include <string>

using namespace std;

void ComputeCentralityWeight(
		 const char* infname = "/net/hisrv0001/home/yenjie/scratch/hiForest/prod/production/CMSSW_4_4_2_patch6/test/forest21_simTrack/merged_pthat80_simTrack_v2.root",
                 bool save = false
		 ) {

  gROOT->Reset();
  gROOT->ProcessLine(".x rootlogonChristof.C");
  gROOT->ForceStyle();
  gStyle->SetPalette(1);

  //Define binning	
  const Double_t small = 1e-3;

  std::vector<Double_t> ptBins;
  Double_t pt;
  for(pt =   0  ; pt <   1.0-small; pt +=  0.15) ptBins.push_back(pt); //8 bins
  for(pt =   1.0; pt <   2.2-small; pt +=  0.1) ptBins.push_back(pt); //12 bins
  for(pt =   2.2; pt <   6.0-small; pt +=  0.475) ptBins.push_back(pt); //8 bins
  for(pt =   6.0; pt <  22.-small; pt +=  2. ) ptBins.push_back(pt); // 8 bins
//  Double_t highPtBins[8] = {22.,30.,45.,60.,90.,120.,180.,300.};
//  ptBins.insert(ptBins.end(),highPtBins,highPtBins+8);
  ptBins.push_back(22.);
  ptBins.push_back(30.);
  ptBins.push_back(45.);
  ptBins.push_back(60.);
  ptBins.push_back(90.);
  ptBins.push_back(120.);
  ptBins.push_back(180.);
  ptBins.push_back(300.);

  std::vector<Double_t> etaBins;
  Double_t eta;
  for(eta = -2.4; eta < 2.4-small; eta += 0.2) etaBins.push_back(eta);
  etaBins.push_back(2.4);

  std::vector<Double_t> phiBins;
  Double_t phi;
  for(phi = -TMath::Pi(); phi < TMath::Pi()-small; phi += 0.1) phiBins.push_back(phi);
  phiBins.push_back(TMath::Pi());

  //0-2.5%
  TH1F * hEff_Cent_vs_pPt_pPt_05_num = new TH1F("hEff_Cent_vs_pPt_pPt_05_num","hEff_Cent_vs_pPt_pPt_05_num",ptBins.size()-1, &ptBins[0]);
  TH1F * hEff_Cent_vs_pPt_pPt_05_den = new TH1F("hEff_Cent_vs_pPt_pPt_05_den","hEff_Cent_vs_pPt_pPt_05_den",ptBins.size()-1, &ptBins[0]);
  TH1F * weight_hEff_Cent_vs_pPt_pPt_05_num = new TH1F("weight_hEff_Cent_vs_pPt_pPt_05_num","weight_hEff_Cent_vs_pPt_pPt_05_num",ptBins.size()-1, &ptBins[0]);
  TH1F * weight_hEff_Cent_vs_pPt_pPt_05_den = new TH1F("weight_hEff_Cent_vs_pPt_pPt_05_den","weight_hEff_Cent_vs_pPt_pPt_05_den",ptBins.size()-1, &ptBins[0]);
  //2.5-5%
  TH1F * test_hEff_Cent_vs_pPt_pPt_05_num = new TH1F("test_hEff_Cent_vs_pPt_pPt_05_num","test_hEff_Cent_vs_pPt_pPt_05_num",ptBins.size()-1, &ptBins[0]);
  TH1F * test_hEff_Cent_vs_pPt_pPt_05_den = new TH1F("test_hEff_Cent_vs_pPt_pPt_05_den","test_hEff_Cent_vs_pPt_pPt_05_den",ptBins.size()-1, &ptBins[0]);
  TH1F * weight_test_hEff_Cent_vs_pPt_pPt_05_num = new TH1F("weight_test_hEff_Cent_vs_pPt_pPt_05_num","weight_test_hEff_Cent_vs_pPt_pPt_05_num",ptBins.size()-1, &ptBins[0]);
  TH1F * weight_test_hEff_Cent_vs_pPt_pPt_05_den = new TH1F("weight_test_hEff_Cent_vs_pPt_pPt_05_den","weight_test_hEff_Cent_vs_pPt_pPt_05_den",ptBins.size()-1, &ptBins[0]);

  hEff_Cent_vs_pPt_pPt_05_num->Sumw2();
  hEff_Cent_vs_pPt_pPt_05_den->Sumw2();
  test_hEff_Cent_vs_pPt_pPt_05_num->Sumw2();
  test_hEff_Cent_vs_pPt_pPt_05_den->Sumw2();
  weight_hEff_Cent_vs_pPt_pPt_05_num->Sumw2();
  weight_hEff_Cent_vs_pPt_pPt_05_den->Sumw2();
  weight_test_hEff_Cent_vs_pPt_pPt_05_num->Sumw2();
  weight_test_hEff_Cent_vs_pPt_pPt_05_den->Sumw2();

  HiForest * t = new HiForest(infname);
  t->InitTree();

  //Get AccWeights
  //Read acceptance corr.
  TFile *fAccCorr = TFile::Open("AcceptanceWeights.root");
  TH2D * hSim3D_eta_phi_inclusive = (TH2D*)fAccCorr->Get("hSim3D_eta_phi_clone");
  TH2D * hSim3D_eta_phi_pT_05_14 = (TH2D*)fAccCorr->Get("hSim3D_eta_phi_pT_06_14_clone");
//  TH2D * hSim3D_eta_phi_pT_14_16 = (TH2D*)fAccCorr->Get("hSim3D_eta_phi_pT_14_16_clone");
//  TH2D * hSim3D_eta_phi_pT_16_18 = (TH2D*)fAccCorr->Get("hSim3D_eta_phi_pT_16_18_clone");
  TH2D * hSim3D_eta_phi_pT_14_18 = (TH2D*)fAccCorr->Get("hSim3D_eta_phi_pT_14_18_clone");
  TH2D * hSim3D_eta_phi_pT_18_3 = (TH2D*)fAccCorr->Get("hSim3D_eta_phi_pT_18_3_clone");
  TH2D * hSim3D_eta_phi_pT_3_8 = (TH2D*)fAccCorr->Get("hSim3D_eta_phi_pT_3_8_clone");
  TH2D * hSim3D_eta_phi_pT_8_20 = (TH2D*)fAccCorr->Get("hSim3D_eta_phi_pT_8_20_clone");
  TH2D * hSim3D_eta_phi_pT_20_Inf = (TH2D*)fAccCorr->Get("hSim3D_eta_phi_pT_20_Inf_clone");


  TH1F * test_05_14_num_C1 = new TH1F("test_05_14_num_C1","test_05_14_num_C1",1,0.6,500);
  TH1F * test_14_18_num_C1 = new TH1F("test_14_18_num_C1","test_14_18_num_C1",1,0.6,500);
  TH1F * test_18_3_num_C1 = new TH1F("test_18_3_num_C1","test_18_3_num_C1",1,0.6,500);
  TH1F * test_3_8_num_C1 = new TH1F("test_3_8_num_C1","test_3_8_num_C1",1,0.6,500);
  TH1F * test_8_20_num_C1 = new TH1F("test_8_20_num_C1","test_8_20_num_C1",1,0.6,500);
  TH1F * test_20_Inf_num_C1 = new TH1F("test_20_Inf_num_C1","test_20_Inf_num_C1",1,0.6,500);
  TH1F * test_05_14_den_C1 = new TH1F("test_05_14_den_C1","test_05_14_den_c1",1,0.6,500);
  TH1F * test_14_18_den_C1 = new TH1F("test_14_18_den_C1","test_14_18_den_c1",1,0.6,500);
  TH1F * test_18_3_den_C1 = new TH1F("test_18_3_den_C1","test_18_3_den_C1",1,0.6,500);
  TH1F * test_3_8_den_C1 = new TH1F("test_3_8_den_C1","test_3_8_den_C1",1,0.6,500);
  TH1F * test_8_20_den_C1 = new TH1F("test_8_20_den_C1","test_8_20_den_C1",1,0.6,500);
  TH1F * test_20_Inf_den_C1 = new TH1F("test_20_Inf_den_C1","test_20_Inf_den_C1",1,0.6,500);
  TH1F * test_05_14_num_C2 = new TH1F("test_05_14_num_C2","test_05_14_num_C2",1,0.6,500);
  TH1F * test_14_18_num_C2 = new TH1F("test_14_18_num_C2","test_14_18_num_C2",1,0.6,500);
  TH1F * test_18_3_num_C2 = new TH1F("test_18_3_num_C2","test_18_3_num_C2",1,0.6,500);
  TH1F * test_3_8_num_C2 = new TH1F("test_3_8_num_C2","test_3_8_num_C2",1,0.6,500);
  TH1F * test_8_20_num_C2 = new TH1F("test_8_20_num_C2","test_8_20_num_C2",1,0.6,500);
  TH1F * test_20_Inf_num_C2 = new TH1F("test_20_Inf_num_C2","test_20_Inf_num_C2",1,0.6,500);
  TH1F * test_05_14_den_C2 = new TH1F("test_05_14_den_C2","test_05_14_den_C2",1,0.6,500);
  TH1F * test_14_18_den_C2 = new TH1F("test_14_18_den_C2","test_14_18_den_C2",1,0.6,500);
  TH1F * test_18_3_den_C2 = new TH1F("test_18_3_den_C2","test_18_3_den_C2",1,0.6,500);
  TH1F * test_3_8_den_C2 = new TH1F("test_3_8_den_C2","test_3_8_den_C2",1,0.6,500);
  TH1F * test_8_20_den_C2 = new TH1F("test_8_20_den_C2","test_8_20_den_C2",1,0.6,500);
  TH1F * test_20_Inf_den_C2 = new TH1F("test_20_Inf_den_C2","test_20_Inf_den_C2",1,0.6,500);
  TH1F * test_05_14_num_C3 = new TH1F("test_05_14_num_C3","test_05_14_num_C3",1,0.6,500);
  TH1F * test_14_18_num_C3 = new TH1F("test_14_18_num_C3","test_14_18_num_C3",1,0.6,500);
  TH1F * test_18_3_num_C3 = new TH1F("test_18_3_num_C3","test_18_3_num_C3",1,0.6,500);
  TH1F * test_3_8_num_C3 = new TH1F("test_3_8_num_C3","test_3_8_num_C3",1,0.6,500);
  TH1F * test_8_20_num_C3 = new TH1F("test_8_20_num_C3","test_8_20_num_C3",1,0.6,500);
  TH1F * test_20_Inf_num_C3 = new TH1F("test_20_Inf_num_C3","test_20_Inf_num_C3",1,0.6,500);
  TH1F * test_05_14_den_C3 = new TH1F("test_05_14_den_C3","test_05_14_den_C3",1,0.6,500);
  TH1F * test_14_18_den_C3 = new TH1F("test_14_18_den_C3","test_14_18_den_C3",1,0.6,500);
  TH1F * test_18_3_den_C3 = new TH1F("test_18_3_den_C3","test_18_3_den_C3",1,0.6,500);
  TH1F * test_3_8_den_C3 = new TH1F("test_3_8_den_C3","test_3_8_den_C3",1,0.6,500);
  TH1F * test_8_20_den_C3 = new TH1F("test_8_20_den_C3","test_8_20_den_C3",1,0.6,500);
  TH1F * test_20_Inf_den_C3 = new TH1F("test_20_Inf_den_C3","test_20_Inf_den_C3",1,0.6,500);
  TH1F * test_05_14_num_C4 = new TH1F("test_05_14_num_C4","test_05_14_num_C4",1,0.6,500);
  TH1F * test_14_18_num_C4 = new TH1F("test_14_18_num_C4","test_14_18_num_C4",1,0.6,500);
  TH1F * test_18_3_num_C4 = new TH1F("test_18_3_num_C4","test_18_3_num_C4",1,0.6,500);
  TH1F * test_3_8_num_C4 = new TH1F("test_3_8_num_C4","test_3_8_num_C4",1,0.6,500);
  TH1F * test_8_20_num_C4 = new TH1F("test_8_20_num_C4","test_8_20_num_C4",1,0.6,500);
  TH1F * test_20_Inf_num_C4 = new TH1F("test_20_Inf_num_C4","test_20_Inf_num_C4",1,0.6,500);
  TH1F * test_05_14_den_C4 = new TH1F("test_05_14_den_C4","test_05_14_den_C4",1,0.6,500);
  TH1F * test_14_18_den_C4 = new TH1F("test_14_18_den_C4","test_14_18_den_C4",1,0.6,500);
  TH1F * test_18_3_den_C4 = new TH1F("test_18_3_den_C4","test_18_3_den_C4",1,0.6,500);
  TH1F * test_3_8_den_C4 = new TH1F("test_3_8_den_C4","test_3_8_den_C4",1,0.6,500);
  TH1F * test_8_20_den_C4 = new TH1F("test_8_20_den_C4","test_8_20_den_C4",1,0.6,500);
  TH1F * test_20_Inf_den_C4 = new TH1F("test_20_Inf_den_C4","test_20_Inf_den_C4",1,0.6,500);
  TH1F * test_05_14_num_C5 = new TH1F("test_05_14_num_C5","test_05_14_num_C5",1,0.6,500);
  TH1F * test_14_18_num_C5 = new TH1F("test_14_18_num_C5","test_14_18_num_C5",1,0.6,500);
  TH1F * test_18_3_num_C5 = new TH1F("test_18_3_num_C5","test_18_3_num_C5",1,0.6,500);
  TH1F * test_3_8_num_C5 = new TH1F("test_3_8_num_C5","test_3_8_num_C5",1,0.6,500);
  TH1F * test_8_20_num_C5 = new TH1F("test_8_20_num_C5","test_8_20_num_C5",1,0.6,500);
  TH1F * test_20_Inf_num_C5 = new TH1F("test_20_Inf_num_C5","test_20_Inf_num_C5",1,0.6,500);
  TH1F * test_05_14_den_C5 = new TH1F("test_05_14_den_C5","test_05_14_den_C5",1,0.6,500);
  TH1F * test_14_18_den_C5 = new TH1F("test_14_18_den_C5","test_14_18_den_C5",1,0.6,500);
  TH1F * test_18_3_den_C5 = new TH1F("test_18_3_den_C5","test_18_3_den_C5",1,0.6,500);
  TH1F * test_3_8_den_C5 = new TH1F("test_3_8_den_C5","test_3_8_den_C5",1,0.6,500);
  TH1F * test_8_20_den_C5 = new TH1F("test_8_20_den_C5","test_8_20_den_C5",1,0.6,500);
  TH1F * test_20_Inf_den_C5 = new TH1F("test_20_Inf_den_C5","test_20_Inf_den_C5",1,0.6,500);
  TH1F * test_05_14_num_C6 = new TH1F("test_05_14_num_C6","test_05_14_num_C6",1,0.6,500);
  TH1F * test_14_18_num_C6 = new TH1F("test_14_18_num_C6","test_14_18_num_C6",1,0.6,500);
  TH1F * test_18_3_num_C6 = new TH1F("test_18_3_num_C6","test_18_3_num_C6",1,0.6,500);
  TH1F * test_3_8_num_C6 = new TH1F("test_3_8_num_C6","test_3_8_num_C6",1,0.6,500);
  TH1F * test_8_20_num_C6 = new TH1F("test_8_20_num_C6","test_8_20_num_C6",1,0.6,500);
  TH1F * test_20_Inf_num_C6 = new TH1F("test_20_Inf_num_C6","test_20_Inf_num_C6",1,0.6,500);
  TH1F * test_05_14_den_C6 = new TH1F("test_05_14_den_C6","test_05_14_den_C6",1,0.6,500);
  TH1F * test_14_18_den_C6 = new TH1F("test_14_18_den_C6","test_14_18_den_C6",1,0.6,500);
  TH1F * test_18_3_den_C6 = new TH1F("test_18_3_den_C6","test_18_3_den_C6",1,0.6,500);
  TH1F * test_3_8_den_C6 = new TH1F("test_3_8_den_C6","test_3_8_den_C6",1,0.6,500);
  TH1F * test_8_20_den_C6 = new TH1F("test_8_20_den_C6","test_8_20_den_C6",1,0.6,500);
  TH1F * test_20_Inf_den_C6 = new TH1F("test_20_Inf_den_C6","test_20_Inf_den_C6",1,0.6,500);
  TH1F * test_05_14_num_C7 = new TH1F("test_05_14_num_C7","test_05_14_num_C7",1,0.6,500);
  TH1F * test_14_18_num_C7 = new TH1F("test_14_18_num_C7","test_14_18_num_C7",1,0.6,500);
  TH1F * test_18_3_num_C7 = new TH1F("test_18_3_num_C7","test_18_3_num_C7",1,0.6,500);
  TH1F * test_3_8_num_C7 = new TH1F("test_3_8_num_C7","test_3_8_num_C7",1,0.6,500);
  TH1F * test_8_20_num_C7 = new TH1F("test_8_20_num_C7","test_8_20_num_C7",1,0.6,500);
  TH1F * test_20_Inf_num_C7 = new TH1F("test_20_Inf_num_C7","test_20_Inf_num_C7",1,0.6,500);
  TH1F * test_05_14_den_C7 = new TH1F("test_05_14_den_C7","test_05_14_den_C7",1,0.6,500);
  TH1F * test_14_18_den_C7 = new TH1F("test_14_18_den_C7","test_14_18_den_C7",1,0.6,500);
  TH1F * test_18_3_den_C7 = new TH1F("test_18_3_den_C7","test_18_3_den_C7",1,0.6,500);
  TH1F * test_3_8_den_C7 = new TH1F("test_3_8_den_C7","test_3_8_den_C7",1,0.6,500);
  TH1F * test_8_20_den_C7 = new TH1F("test_8_20_den_C7","test_8_20_den_C7",1,0.6,500);
  TH1F * test_20_Inf_den_C7 = new TH1F("test_20_Inf_den_C7","test_20_Inf_den_C7",1,0.6,500);
  TH1F * test_05_14_num_C8 = new TH1F("test_05_14_num_C8","test_05_14_num_C8",1,0.6,500);
  TH1F * test_14_18_num_C8 = new TH1F("test_14_18_num_C8","test_14_18_num_C8",1,0.6,500);
  TH1F * test_18_3_num_C8 = new TH1F("test_18_3_num_C8","test_18_3_num_C8",1,0.6,500);
  TH1F * test_3_8_num_C8 = new TH1F("test_3_8_num_C8","test_3_8_num_C8",1,0.6,500);
  TH1F * test_8_20_num_C8 = new TH1F("test_8_20_num_C8","test_8_20_num_C8",1,0.6,500);
  TH1F * test_20_Inf_num_C8 = new TH1F("test_20_Inf_num_C8","test_20_Inf_num_C8",1,0.6,500);
  TH1F * test_05_14_den_C8 = new TH1F("test_05_14_den_C8","test_05_14_den_C8",1,0.6,500);
  TH1F * test_14_18_den_C8 = new TH1F("test_14_18_den_C8","test_14_18_den_C8",1,0.6,500);
  TH1F * test_18_3_den_C8 = new TH1F("test_18_3_den_C8","test_18_3_den_C8",1,0.6,500);
  TH1F * test_3_8_den_C8 = new TH1F("test_3_8_den_C8","test_3_8_den_C8",1,0.6,500);
  TH1F * test_8_20_den_C8 = new TH1F("test_8_20_den_C8","test_8_20_den_C8",1,0.6,500);
  TH1F * test_20_Inf_den_C8 = new TH1F("test_20_Inf_den_C8","test_20_Inf_den_C8",1,0.6,500);
  TH1F * test_05_14_num_C9 = new TH1F("test_05_14_num_C9","test_05_14_num_C9",1,0.6,500);
  TH1F * test_14_18_num_C9 = new TH1F("test_14_18_num_C9","test_14_18_num_C9",1,0.6,500);
  TH1F * test_18_3_num_C9 = new TH1F("test_18_3_num_C9","test_18_3_num_C9",1,0.6,500);
  TH1F * test_3_8_num_C9 = new TH1F("test_3_8_num_C9","test_3_8_num_C9",1,0.6,500);
  TH1F * test_8_20_num_C9 = new TH1F("test_8_20_num_C9","test_8_20_num_C9",1,0.6,500);
  TH1F * test_20_Inf_num_C9 = new TH1F("test_20_Inf_num_C9","test_20_Inf_num_C9",1,0.6,500);
  TH1F * test_05_14_den_C9 = new TH1F("test_05_14_den_C9","test_05_14_den_C9",1,0.6,500);
  TH1F * test_14_18_den_C9 = new TH1F("test_14_18_den_C9","test_14_18_den_C9",1,0.6,500);
  TH1F * test_18_3_den_C9 = new TH1F("test_18_3_den_C9","test_18_3_den_C9",1,0.6,500);
  TH1F * test_3_8_den_C9 = new TH1F("test_3_8_den_C9","test_3_8_den_C9",1,0.6,500);
  TH1F * test_8_20_den_C9 = new TH1F("test_8_20_den_C9","test_8_20_den_C9",1,0.6,500);
  TH1F * test_20_Inf_den_C9 = new TH1F("test_20_Inf_den_C9","test_20_Inf_den_C9",1,0.6,500);
  TH1F * test_05_14_num_C10 = new TH1F("test_05_14_num_C10","test_05_14_num_C10",1,0.6,500);
  TH1F * test_14_18_num_C10 = new TH1F("test_14_18_num_C10","test_14_18_num_C10",1,0.6,500);
  TH1F * test_18_3_num_C10 = new TH1F("test_18_3_num_C10","test_18_3_num_C10",1,0.6,500);
  TH1F * test_3_8_num_C10 = new TH1F("test_3_8_num_C10","test_3_8_num_C10",1,0.6,500);
  TH1F * test_8_20_num_C10 = new TH1F("test_8_20_num_C10","test_8_20_num_C10",1,0.6,500);
  TH1F * test_20_Inf_num_C10 = new TH1F("test_20_Inf_num_C10","test_20_Inf_num_C10",1,0.6,500);
  TH1F * test_05_14_den_C10 = new TH1F("test_05_14_den_C10","test_05_14_den_C10",1,0.6,500);
  TH1F * test_14_18_den_C10 = new TH1F("test_14_18_den_C10","test_14_18_den_C10",1,0.6,500);
  TH1F * test_18_3_den_C10 = new TH1F("test_18_3_den_C10","test_18_3_den_C10",1,0.6,500);
  TH1F * test_3_8_den_C10 = new TH1F("test_3_8_den_C10","test_3_8_den_C10",1,0.6,500);
  TH1F * test_8_20_den_C10 = new TH1F("test_8_20_den_C10","test_8_20_den_C10",1,0.6,500);
  TH1F * test_20_Inf_den_C10 = new TH1F("test_20_Inf_den_C10","test_20_Inf_den_C10",1,0.6,500);

  TH1F * weight_test_05_14_num_C1 = new TH1F("weight_test_05_14_num_C1","weight_test_05_14_num_C1",1,0.6,500);
  TH1F * weight_test_14_18_num_C1 = new TH1F("weight_test_14_18_num_C1","weight_test_14_18_num_C1",1,0.6,500);
  TH1F * weight_test_18_3_num_C1 = new TH1F("weight_test_18_3_num_C1","weight_test_18_3_num_C1",1,0.6,500);
  TH1F * weight_test_3_8_num_C1 = new TH1F("weight_test_3_8_num_C1","weight_test_3_8_num_C1",1,0.6,500);
  TH1F * weight_test_8_20_num_C1 = new TH1F("weight_test_8_20_num_C1","weight_test_8_20_num_C1",1,0.6,500);
  TH1F * weight_test_20_Inf_num_C1 = new TH1F("weight_test_20_Inf_num_C1","weight_test_20_Inf_num_C1",1,0.6,500);
  TH1F * weight_test_05_14_den_C1 = new TH1F("weight_test_05_14_den_C1","weight_test_05_14_den_c1",1,0.6,500);
  TH1F * weight_test_14_18_den_C1 = new TH1F("weight_test_14_18_den_C1","weight_test_14_18_den_c1",1,0.6,500);
  TH1F * weight_test_18_3_den_C1 = new TH1F("weight_test_18_3_den_C1","weight_test_18_3_den_C1",1,0.6,500);
  TH1F * weight_test_3_8_den_C1 = new TH1F("weight_test_3_8_den_C1","weight_test_3_8_den_C1",1,0.6,500);
  TH1F * weight_test_8_20_den_C1 = new TH1F("weight_test_8_20_den_C1","weight_test_8_20_den_C1",1,0.6,500);
  TH1F * weight_test_20_Inf_den_C1 = new TH1F("weight_test_20_Inf_den_C1","weight_test_20_Inf_den_C1",1,0.6,500);
  TH1F * weight_test_05_14_num_C2 = new TH1F("weight_test_05_14_num_C2","weight_test_05_14_num_C2",1,0.6,500);
  TH1F * weight_test_14_18_num_C2 = new TH1F("weight_test_14_18_num_C2","weight_test_14_18_num_C2",1,0.6,500);
  TH1F * weight_test_18_3_num_C2 = new TH1F("weight_test_18_3_num_C2","weight_test_18_3_num_C2",1,0.6,500);
  TH1F * weight_test_3_8_num_C2 = new TH1F("weight_test_3_8_num_C2","weight_test_3_8_num_C2",1,0.6,500);
  TH1F * weight_test_8_20_num_C2 = new TH1F("weight_test_8_20_num_C2","weight_test_8_20_num_C2",1,0.6,500);
  TH1F * weight_test_20_Inf_num_C2 = new TH1F("weight_test_20_Inf_num_C2","weight_test_20_Inf_num_C2",1,0.6,500);
  TH1F * weight_test_05_14_den_C2 = new TH1F("weight_test_05_14_den_C2","weight_test_05_14_den_C2",1,0.6,500);
  TH1F * weight_test_14_18_den_C2 = new TH1F("weight_test_14_18_den_C2","weight_test_14_18_den_C2",1,0.6,500);
  TH1F * weight_test_18_3_den_C2 = new TH1F("weight_test_18_3_den_C2","weight_test_18_3_den_C2",1,0.6,500);
  TH1F * weight_test_3_8_den_C2 = new TH1F("weight_test_3_8_den_C2","weight_test_3_8_den_C2",1,0.6,500);
  TH1F * weight_test_8_20_den_C2 = new TH1F("weight_test_8_20_den_C2","weight_test_8_20_den_C2",1,0.6,500);
  TH1F * weight_test_20_Inf_den_C2 = new TH1F("weight_test_20_Inf_den_C2","weight_test_20_Inf_den_C2",1,0.6,500);
  TH1F * weight_test_05_14_num_C3 = new TH1F("weight_test_05_14_num_C3","weight_test_05_14_num_C3",1,0.6,500);
  TH1F * weight_test_14_18_num_C3 = new TH1F("weight_test_14_18_num_C3","weight_test_14_18_num_C3",1,0.6,500);
  TH1F * weight_test_18_3_num_C3 = new TH1F("weight_test_18_3_num_C3","weight_test_18_3_num_C3",1,0.6,500);
  TH1F * weight_test_3_8_num_C3 = new TH1F("weight_test_3_8_num_C3","weight_test_3_8_num_C3",1,0.6,500);
  TH1F * weight_test_8_20_num_C3 = new TH1F("weight_test_8_20_num_C3","weight_test_8_20_num_C3",1,0.6,500);
  TH1F * weight_test_20_Inf_num_C3 = new TH1F("weight_test_20_Inf_num_C3","weight_test_20_Inf_num_C3",1,0.6,500);
  TH1F * weight_test_05_14_den_C3 = new TH1F("weight_test_05_14_den_C3","weight_test_05_14_den_C3",1,0.6,500);
  TH1F * weight_test_14_18_den_C3 = new TH1F("weight_test_14_18_den_C3","weight_test_14_18_den_C3",1,0.6,500);
  TH1F * weight_test_18_3_den_C3 = new TH1F("weight_test_18_3_den_C3","weight_test_18_3_den_C3",1,0.6,500);
  TH1F * weight_test_3_8_den_C3 = new TH1F("weight_test_3_8_den_C3","weight_test_3_8_den_C3",1,0.6,500);
  TH1F * weight_test_8_20_den_C3 = new TH1F("weight_test_8_20_den_C3","weight_test_8_20_den_C3",1,0.6,500);
  TH1F * weight_test_20_Inf_den_C3 = new TH1F("weight_test_20_Inf_den_C3","weight_test_20_Inf_den_C3",1,0.6,500);
  TH1F * weight_test_05_14_num_C4 = new TH1F("weight_test_05_14_num_C4","weight_test_05_14_num_C4",1,0.6,500);
  TH1F * weight_test_14_18_num_C4 = new TH1F("weight_test_14_18_num_C4","weight_test_14_18_num_C4",1,0.6,500);
  TH1F * weight_test_18_3_num_C4 = new TH1F("weight_test_18_3_num_C4","weight_test_18_3_num_C4",1,0.6,500);
  TH1F * weight_test_3_8_num_C4 = new TH1F("weight_test_3_8_num_C4","weight_test_3_8_num_C4",1,0.6,500);
  TH1F * weight_test_8_20_num_C4 = new TH1F("weight_test_8_20_num_C4","weight_test_8_20_num_C4",1,0.6,500);
  TH1F * weight_test_20_Inf_num_C4 = new TH1F("weight_test_20_Inf_num_C4","weight_test_20_Inf_num_C4",1,0.6,500);
  TH1F * weight_test_05_14_den_C4 = new TH1F("weight_test_05_14_den_C4","weight_test_05_14_den_C4",1,0.6,500);
  TH1F * weight_test_14_18_den_C4 = new TH1F("weight_test_14_18_den_C4","weight_test_14_18_den_C4",1,0.6,500);
  TH1F * weight_test_18_3_den_C4 = new TH1F("weight_test_18_3_den_C4","weight_test_18_3_den_C4",1,0.6,500);
  TH1F * weight_test_3_8_den_C4 = new TH1F("weight_test_3_8_den_C4","weight_test_3_8_den_C4",1,0.6,500);
  TH1F * weight_test_8_20_den_C4 = new TH1F("weight_test_8_20_den_C4","weight_test_8_20_den_C4",1,0.6,500);
  TH1F * weight_test_20_Inf_den_C4 = new TH1F("weight_test_20_Inf_den_C4","weight_test_20_Inf_den_C4",1,0.6,500);
  TH1F * weight_test_05_14_num_C5 = new TH1F("weight_test_05_14_num_C5","weight_test_05_14_num_C5",1,0.6,500);
  TH1F * weight_test_14_18_num_C5 = new TH1F("weight_test_14_18_num_C5","weight_test_14_18_num_C5",1,0.6,500);
  TH1F * weight_test_18_3_num_C5 = new TH1F("weight_test_18_3_num_C5","weight_test_18_3_num_C5",1,0.6,500);
  TH1F * weight_test_3_8_num_C5 = new TH1F("weight_test_3_8_num_C5","weight_test_3_8_num_C5",1,0.6,500);
  TH1F * weight_test_8_20_num_C5 = new TH1F("weight_test_8_20_num_C5","weight_test_8_20_num_C5",1,0.6,500);
  TH1F * weight_test_20_Inf_num_C5 = new TH1F("weight_test_20_Inf_num_C5","weight_test_20_Inf_num_C5",1,0.6,500);
  TH1F * weight_test_14_18_den_C5 = new TH1F("weight_test_14_18_den_C5","weight_test_14_18_den_C5",1,0.6,500);
  TH1F * weight_test_05_14_den_C5 = new TH1F("weight_test_05_14_den_C5","weight_test_05_14_den_C5",1,0.6,500);
  TH1F * weight_test_18_3_den_C5 = new TH1F("weight_test_18_3_den_C5","weight_test_18_3_den_C5",1,0.6,500);
  TH1F * weight_test_3_8_den_C5 = new TH1F("weight_test_3_8_den_C5","weight_test_3_8_den_C5",1,0.6,500);
  TH1F * weight_test_8_20_den_C5 = new TH1F("weight_test_8_20_den_C5","weight_test_8_20_den_C5",1,0.6,500);
  TH1F * weight_test_20_Inf_den_C5 = new TH1F("weight_test_20_Inf_den_C5","weight_test_20_Inf_den_C5",1,0.6,500);
  TH1F * weight_test_05_14_num_C6 = new TH1F("weight_test_05_14_num_C6","weight_test_05_14_num_C6",1,0.6,500);
  TH1F * weight_test_14_18_num_C6 = new TH1F("weight_test_14_18_num_C6","weight_test_14_18_num_C6",1,0.6,500);
  TH1F * weight_test_18_3_num_C6 = new TH1F("weight_test_18_3_num_C6","weight_test_18_3_num_C6",1,0.6,500);
  TH1F * weight_test_3_8_num_C6 = new TH1F("weight_test_3_8_num_C6","weight_test_3_8_num_C6",1,0.6,500);
  TH1F * weight_test_8_20_num_C6 = new TH1F("weight_test_8_20_num_C6","weight_test_8_20_num_C6",1,0.6,500);
  TH1F * weight_test_20_Inf_num_C6 = new TH1F("weight_test_20_Inf_num_C6","weight_test_20_Inf_num_C6",1,0.6,500);
  TH1F * weight_test_05_14_den_C6 = new TH1F("weight_test_05_14_den_C6","weight_test_05_14_den_C6",1,0.6,500);
  TH1F * weight_test_14_18_den_C6 = new TH1F("weight_test_14_18_den_C6","weight_test_14_18_den_C6",1,0.6,500);
  TH1F * weight_test_18_3_den_C6 = new TH1F("weight_test_18_3_den_C6","weight_test_18_3_den_C6",1,0.6,500);
  TH1F * weight_test_3_8_den_C6 = new TH1F("weight_test_3_8_den_C6","weight_test_3_8_den_C6",1,0.6,500);
  TH1F * weight_test_8_20_den_C6 = new TH1F("weight_test_8_20_den_C6","weight_test_8_20_den_C6",1,0.6,500);
  TH1F * weight_test_20_Inf_den_C6 = new TH1F("weight_test_20_Inf_den_C6","weight_test_20_Inf_den_C6",1,0.6,500);
  TH1F * weight_test_05_14_num_C7 = new TH1F("weight_test_05_14_num_C7","weight_test_05_14_num_C7",1,0.6,500);
  TH1F * weight_test_14_18_num_C7 = new TH1F("weight_test_14_18_num_C7","weight_test_14_18_num_C7",1,0.6,500);
  TH1F * weight_test_18_3_num_C7 = new TH1F("weight_test_18_3_num_C7","weight_test_18_3_num_C7",1,0.6,500);
  TH1F * weight_test_3_8_num_C7 = new TH1F("weight_test_3_8_num_C7","weight_test_3_8_num_C7",1,0.6,500);
  TH1F * weight_test_8_20_num_C7 = new TH1F("weight_test_8_20_num_C7","weight_test_8_20_num_C7",1,0.6,500);
  TH1F * weight_test_20_Inf_num_C7 = new TH1F("weight_test_20_Inf_num_C7","weight_test_20_Inf_num_C7",1,0.6,500);
  TH1F * weight_test_05_14_den_C7 = new TH1F("weight_test_05_14_den_C7","weight_test_05_14_den_C7",1,0.6,500);
  TH1F * weight_test_14_18_den_C7 = new TH1F("weight_test_14_18_den_C7","weight_test_14_18_den_C7",1,0.6,500);
  TH1F * weight_test_18_3_den_C7 = new TH1F("weight_test_18_3_den_C7","weight_test_18_3_den_C7",1,0.6,500);
  TH1F * weight_test_3_8_den_C7 = new TH1F("weight_test_3_8_den_C7","weight_test_3_8_den_C7",1,0.6,500);
  TH1F * weight_test_8_20_den_C7 = new TH1F("weight_test_8_20_den_C7","weight_test_8_20_den_C7",1,0.6,500);
  TH1F * weight_test_20_Inf_den_C7 = new TH1F("weight_test_20_Inf_den_C7","weight_test_20_Inf_den_C7",1,0.6,500);
  TH1F * weight_test_05_14_num_C8 = new TH1F("weight_test_05_14_num_C8","weight_test_05_14_num_C8",1,0.6,500);
  TH1F * weight_test_14_18_num_C8 = new TH1F("weight_test_14_18_num_C8","weight_test_14_18_num_C8",1,0.6,500);
  TH1F * weight_test_18_3_num_C8 = new TH1F("weight_test_18_3_num_C8","weight_test_18_3_num_C8",1,0.6,500);
  TH1F * weight_test_3_8_num_C8 = new TH1F("weight_test_3_8_num_C8","weight_test_3_8_num_C8",1,0.6,500);
  TH1F * weight_test_8_20_num_C8 = new TH1F("weight_test_8_20_num_C8","weight_test_8_20_num_C8",1,0.6,500);
  TH1F * weight_test_20_Inf_num_C8 = new TH1F("weight_test_20_Inf_num_C8","weight_test_20_Inf_num_C8",1,0.6,500);
  TH1F * weight_test_05_14_den_C8 = new TH1F("weight_test_05_14_den_C8","weight_test_05_14_den_C8",1,0.6,500);
  TH1F * weight_test_14_18_den_C8 = new TH1F("weight_test_14_18_den_C8","weight_test_14_18_den_C8",1,0.6,500);
  TH1F * weight_test_18_3_den_C8 = new TH1F("weight_test_18_3_den_C8","weight_test_18_3_den_C8",1,0.6,500);
  TH1F * weight_test_3_8_den_C8 = new TH1F("weight_test_3_8_den_C8","weight_test_3_8_den_C8",1,0.6,500);
  TH1F * weight_test_8_20_den_C8 = new TH1F("weight_test_8_20_den_C8","weight_test_8_20_den_C8",1,0.6,500);
  TH1F * weight_test_20_Inf_den_C8 = new TH1F("weight_test_20_Inf_den_C8","weight_test_20_Inf_den_C8",1,0.6,500);
  TH1F * weight_test_05_14_num_C9 = new TH1F("weight_test_05_14_num_C9","weight_test_05_14_num_C9",1,0.6,500);
  TH1F * weight_test_14_18_num_C9 = new TH1F("weight_test_14_18_num_C9","weight_test_14_18_num_C9",1,0.6,500);
  TH1F * weight_test_18_3_num_C9 = new TH1F("weight_test_18_3_num_C9","weight_test_18_3_num_C9",1,0.6,500);
  TH1F * weight_test_3_8_num_C9 = new TH1F("weight_test_3_8_num_C9","weight_test_3_8_num_C9",1,0.6,500);
  TH1F * weight_test_8_20_num_C9 = new TH1F("weight_test_8_20_num_C9","weight_test_8_20_num_C9",1,0.6,500);
  TH1F * weight_test_20_Inf_num_C9 = new TH1F("weight_test_20_Inf_num_C9","weight_test_20_Inf_num_C9",1,0.6,500);
  TH1F * weight_test_05_14_den_C9 = new TH1F("weight_test_05_14_den_C9","weight_test_05_14_den_C9",1,0.6,500);
  TH1F * weight_test_14_18_den_C9 = new TH1F("weight_test_14_18_den_C9","weight_test_14_18_den_C9",1,0.6,500);
  TH1F * weight_test_18_3_den_C9 = new TH1F("weight_test_18_3_den_C9","weight_test_18_3_den_C9",1,0.6,500);
  TH1F * weight_test_3_8_den_C9 = new TH1F("weight_test_3_8_den_C9","weight_test_3_8_den_C9",1,0.6,500);
  TH1F * weight_test_8_20_den_C9 = new TH1F("weight_test_8_20_den_C9","weight_test_8_20_den_C9",1,0.6,500);
  TH1F * weight_test_20_Inf_den_C9 = new TH1F("weight_test_20_Inf_den_C9","weight_test_20_Inf_den_C9",1,0.6,500);
  TH1F * weight_test_05_14_num_C10 = new TH1F("weight_test_05_14_num_C10","weight_test_05_14_num_C10",1,0.6,500);
  TH1F * weight_test_14_18_num_C10 = new TH1F("weight_test_14_18_num_C10","weight_test_14_18_num_C10",1,0.6,500);
  TH1F * weight_test_18_3_num_C10 = new TH1F("weight_test_18_3_num_C10","weight_test_18_3_num_C10",1,0.6,500);
  TH1F * weight_test_3_8_num_C10 = new TH1F("weight_test_3_8_num_C10","weight_test_3_8_num_C10",1,0.6,500);
  TH1F * weight_test_8_20_num_C10 = new TH1F("weight_test_8_20_num_C10","weight_test_8_20_num_C10",1,0.6,500);
  TH1F * weight_test_20_Inf_num_C10 = new TH1F("weight_test_20_Inf_num_C10","weight_test_20_Inf_num_C10",1,0.6,500);
  TH1F * weight_test_05_14_den_C10 = new TH1F("weight_test_05_14_den_C10","weight_test_05_14_den_C10",1,0.6,500);
  TH1F * weight_test_14_18_den_C10 = new TH1F("weight_test_14_18_den_C10","weight_test_14_18_den_C10",1,0.6,500);
  TH1F * weight_test_18_3_den_C10 = new TH1F("weight_test_18_3_den_C10","weight_test_18_3_den_C10",1,0.6,500);
  TH1F * weight_test_3_8_den_C10 = new TH1F("weight_test_3_8_den_C10","weight_test_3_8_den_C10",1,0.6,500);
  TH1F * weight_test_8_20_den_C10 = new TH1F("weight_test_8_20_den_C10","weight_test_8_20_den_C10",1,0.6,500);
  TH1F * weight_test_20_Inf_den_C10 = new TH1F("weight_test_20_Inf_den_C10","weight_test_20_Inf_den_C10",1,0.6,500);

  test_05_14_num_C1->Sumw2();
  test_05_14_num_C2->Sumw2();
  test_05_14_num_C3->Sumw2();
  test_05_14_num_C4->Sumw2();
  test_05_14_num_C5->Sumw2();
  test_05_14_num_C6->Sumw2();
  test_05_14_num_C7->Sumw2();
  test_05_14_num_C8->Sumw2();
  test_05_14_num_C9->Sumw2();
  test_05_14_num_C10->Sumw2();
  test_05_14_den_C1->Sumw2();
  test_05_14_den_C2->Sumw2();
  test_05_14_den_C3->Sumw2();
  test_05_14_den_C4->Sumw2();
  test_05_14_den_C5->Sumw2();
  test_05_14_den_C6->Sumw2();
  test_05_14_den_C7->Sumw2();
  test_05_14_den_C8->Sumw2();
  test_05_14_den_C9->Sumw2();
  test_05_14_den_C10->Sumw2();
  test_14_18_num_C1->Sumw2();
  test_14_18_num_C2->Sumw2();
  test_14_18_num_C3->Sumw2();
  test_14_18_num_C4->Sumw2();
  test_14_18_num_C5->Sumw2();
  test_14_18_num_C6->Sumw2();
  test_14_18_num_C7->Sumw2();
  test_14_18_num_C8->Sumw2();
  test_14_18_num_C9->Sumw2();
  test_14_18_num_C10->Sumw2();
  test_14_18_den_C1->Sumw2();
  test_14_18_den_C2->Sumw2();
  test_14_18_den_C3->Sumw2();
  test_14_18_den_C4->Sumw2();
  test_14_18_den_C5->Sumw2();
  test_14_18_den_C6->Sumw2();
  test_14_18_den_C7->Sumw2();
  test_14_18_den_C8->Sumw2();
  test_14_18_den_C9->Sumw2();
  test_14_18_den_C10->Sumw2();
  test_3_8_num_C1->Sumw2();
  test_3_8_num_C2->Sumw2();
  test_3_8_num_C3->Sumw2();
  test_3_8_num_C4->Sumw2();
  test_3_8_num_C5->Sumw2();
  test_3_8_num_C6->Sumw2();
  test_3_8_num_C7->Sumw2();
  test_3_8_num_C8->Sumw2();
  test_3_8_num_C9->Sumw2();
  test_3_8_num_C10->Sumw2();
  test_3_8_den_C1->Sumw2();
  test_3_8_den_C2->Sumw2();
  test_3_8_den_C3->Sumw2();
  test_3_8_den_C4->Sumw2();
  test_3_8_den_C5->Sumw2();
  test_3_8_den_C6->Sumw2();
  test_3_8_den_C7->Sumw2();
  test_3_8_den_C8->Sumw2();
  test_3_8_den_C9->Sumw2();
  test_3_8_den_C10->Sumw2();
  test_18_3_num_C1->Sumw2();
  test_18_3_num_C2->Sumw2();
  test_18_3_num_C3->Sumw2();
  test_18_3_num_C4->Sumw2();
  test_18_3_num_C5->Sumw2();
  test_18_3_num_C6->Sumw2();
  test_18_3_num_C7->Sumw2();
  test_18_3_num_C8->Sumw2();
  test_18_3_num_C9->Sumw2();
  test_18_3_num_C10->Sumw2();
  test_18_3_den_C1->Sumw2();
  test_18_3_den_C2->Sumw2();
  test_18_3_den_C3->Sumw2();
  test_18_3_den_C4->Sumw2();
  test_18_3_den_C5->Sumw2();
  test_18_3_den_C6->Sumw2();
  test_18_3_den_C7->Sumw2();
  test_18_3_den_C8->Sumw2();
  test_18_3_den_C9->Sumw2();
  test_18_3_den_C10->Sumw2();
  test_8_20_num_C1->Sumw2();
  test_8_20_num_C2->Sumw2();
  test_8_20_num_C3->Sumw2();
  test_8_20_num_C4->Sumw2();
  test_8_20_num_C5->Sumw2();
  test_8_20_num_C6->Sumw2();
  test_8_20_num_C7->Sumw2();
  test_8_20_num_C8->Sumw2();
  test_8_20_num_C9->Sumw2();
  test_8_20_num_C10->Sumw2();
  test_8_20_den_C1->Sumw2();
  test_8_20_den_C2->Sumw2();
  test_8_20_den_C3->Sumw2();
  test_8_20_den_C4->Sumw2();
  test_8_20_den_C5->Sumw2();
  test_8_20_den_C6->Sumw2();
  test_8_20_den_C7->Sumw2();
  test_8_20_den_C8->Sumw2();
  test_8_20_den_C9->Sumw2();
  test_8_20_den_C10->Sumw2();
  test_20_Inf_num_C1->Sumw2();
  test_20_Inf_num_C2->Sumw2();
  test_20_Inf_num_C3->Sumw2();
  test_20_Inf_num_C4->Sumw2();
  test_20_Inf_num_C5->Sumw2();
  test_20_Inf_num_C6->Sumw2();
  test_20_Inf_num_C7->Sumw2();
  test_20_Inf_num_C8->Sumw2();
  test_20_Inf_num_C9->Sumw2();
  test_20_Inf_num_C10->Sumw2();
  test_20_Inf_den_C1->Sumw2();
  test_20_Inf_den_C2->Sumw2();
  test_20_Inf_den_C3->Sumw2();
  test_20_Inf_den_C4->Sumw2();
  test_20_Inf_den_C5->Sumw2();
  test_20_Inf_den_C6->Sumw2();
  test_20_Inf_den_C7->Sumw2();
  test_20_Inf_den_C8->Sumw2();
  test_20_Inf_den_C9->Sumw2();
  test_20_Inf_den_C10->Sumw2();

  weight_test_05_14_num_C1->Sumw2();
  weight_test_05_14_num_C2->Sumw2();
  weight_test_05_14_num_C3->Sumw2();
  weight_test_05_14_num_C4->Sumw2();
  weight_test_05_14_num_C5->Sumw2();
  weight_test_05_14_num_C6->Sumw2();
  weight_test_05_14_num_C7->Sumw2();
  weight_test_05_14_num_C8->Sumw2();
  weight_test_05_14_num_C9->Sumw2();
  weight_test_05_14_num_C10->Sumw2();
  weight_test_05_14_den_C1->Sumw2();
  weight_test_05_14_den_C2->Sumw2();
  weight_test_05_14_den_C3->Sumw2();
  weight_test_05_14_den_C4->Sumw2();
  weight_test_05_14_den_C5->Sumw2();
  weight_test_05_14_den_C6->Sumw2();
  weight_test_05_14_den_C7->Sumw2();
  weight_test_05_14_den_C8->Sumw2();
  weight_test_05_14_den_C9->Sumw2();
  weight_test_05_14_den_C10->Sumw2();
  weight_test_14_18_num_C1->Sumw2();
  weight_test_14_18_num_C2->Sumw2();
  weight_test_14_18_num_C3->Sumw2();
  weight_test_14_18_num_C4->Sumw2();
  weight_test_14_18_num_C5->Sumw2();
  weight_test_14_18_num_C6->Sumw2();
  weight_test_14_18_num_C7->Sumw2();
  weight_test_14_18_num_C8->Sumw2();
  weight_test_14_18_num_C9->Sumw2();
  weight_test_14_18_num_C10->Sumw2();
  weight_test_14_18_den_C1->Sumw2();
  weight_test_14_18_den_C2->Sumw2();
  weight_test_14_18_den_C3->Sumw2();
  weight_test_14_18_den_C4->Sumw2();
  weight_test_14_18_den_C5->Sumw2();
  weight_test_14_18_den_C6->Sumw2();
  weight_test_14_18_den_C7->Sumw2();
  weight_test_14_18_den_C8->Sumw2();
  weight_test_14_18_den_C9->Sumw2();
  weight_test_14_18_den_C10->Sumw2();
  weight_test_3_8_num_C1->Sumw2();
  weight_test_3_8_num_C2->Sumw2();
  weight_test_3_8_num_C3->Sumw2();
  weight_test_3_8_num_C4->Sumw2();
  weight_test_3_8_num_C5->Sumw2();
  weight_test_3_8_num_C6->Sumw2();
  weight_test_3_8_num_C7->Sumw2();
  weight_test_3_8_num_C8->Sumw2();
  weight_test_3_8_num_C9->Sumw2();
  weight_test_3_8_num_C10->Sumw2();
  weight_test_3_8_den_C1->Sumw2();
  weight_test_3_8_den_C2->Sumw2();
  weight_test_3_8_den_C3->Sumw2();
  weight_test_3_8_den_C4->Sumw2();
  weight_test_3_8_den_C5->Sumw2();
  weight_test_3_8_den_C6->Sumw2();
  weight_test_3_8_den_C7->Sumw2();
  weight_test_3_8_den_C8->Sumw2();
  weight_test_3_8_den_C9->Sumw2();
  weight_test_3_8_den_C10->Sumw2();
  weight_test_18_3_num_C1->Sumw2();
  weight_test_18_3_num_C2->Sumw2();
  weight_test_18_3_num_C3->Sumw2();
  weight_test_18_3_num_C4->Sumw2();
  weight_test_18_3_num_C5->Sumw2();
  weight_test_18_3_num_C6->Sumw2();
  weight_test_18_3_num_C7->Sumw2();
  weight_test_18_3_num_C8->Sumw2();
  weight_test_18_3_num_C9->Sumw2();
  weight_test_18_3_num_C10->Sumw2();
  weight_test_18_3_den_C1->Sumw2();
  weight_test_18_3_den_C2->Sumw2();
  weight_test_18_3_den_C3->Sumw2();
  weight_test_18_3_den_C4->Sumw2();
  weight_test_18_3_den_C5->Sumw2();
  weight_test_18_3_den_C6->Sumw2();
  weight_test_18_3_den_C7->Sumw2();
  weight_test_18_3_den_C8->Sumw2();
  weight_test_18_3_den_C9->Sumw2();
  weight_test_18_3_den_C10->Sumw2();
  weight_test_8_20_den_C10->Sumw2();
  weight_test_8_20_num_C1->Sumw2();
  weight_test_8_20_num_C2->Sumw2();
  weight_test_8_20_num_C3->Sumw2();
  weight_test_8_20_num_C4->Sumw2();
  weight_test_8_20_num_C5->Sumw2();
  weight_test_8_20_num_C6->Sumw2();
  weight_test_8_20_num_C7->Sumw2();
  weight_test_8_20_num_C8->Sumw2();
  weight_test_8_20_num_C9->Sumw2();
  weight_test_8_20_num_C10->Sumw2();
  weight_test_8_20_den_C1->Sumw2();
  weight_test_8_20_den_C2->Sumw2();
  weight_test_8_20_den_C3->Sumw2();
  weight_test_8_20_den_C4->Sumw2();
  weight_test_8_20_den_C5->Sumw2();
  weight_test_8_20_den_C6->Sumw2();
  weight_test_8_20_den_C7->Sumw2();
  weight_test_8_20_den_C8->Sumw2();
  weight_test_8_20_den_C9->Sumw2();
  weight_test_8_20_den_C10->Sumw2();
  weight_test_20_Inf_num_C1->Sumw2();
  weight_test_20_Inf_num_C2->Sumw2();
  weight_test_20_Inf_num_C3->Sumw2();
  weight_test_20_Inf_num_C4->Sumw2();
  weight_test_20_Inf_num_C5->Sumw2();
  weight_test_20_Inf_num_C6->Sumw2();
  weight_test_20_Inf_num_C7->Sumw2();
  weight_test_20_Inf_num_C8->Sumw2();
  weight_test_20_Inf_num_C9->Sumw2();
  weight_test_20_Inf_num_C10->Sumw2();
  weight_test_20_Inf_den_C1->Sumw2();
  weight_test_20_Inf_den_C2->Sumw2();
  weight_test_20_Inf_den_C3->Sumw2();
  weight_test_20_Inf_den_C4->Sumw2();
  weight_test_20_Inf_den_C5->Sumw2();
  weight_test_20_Inf_den_C6->Sumw2();
  weight_test_20_Inf_den_C7->Sumw2();
  weight_test_20_Inf_den_C8->Sumw2();
  weight_test_20_Inf_den_C9->Sumw2();

  TH1F * hEff_vs_Cent_pPt_05 = new TH1F("hEff_vs_Cent_pPt_05","hEff_vs_Cent_pPt_05",10,0.,40.);
  TH1F * hEff_vs_Cent_pPt_14_18 = new TH1F("hEff_vs_Cent_pPt_14_18","hEff_vs_Cent_pPt_14_18",10,0.,40.);
  TH1F * hEff_vs_Cent_pPt_18_3 = new TH1F("hEff_vs_Cent_pPt_18_3","hEff_vs_Cent_pPt_18_3",10,0.,40.);
  TH1F * hEff_vs_Cent_pPt_3_8 = new TH1F("hEff_vs_Cent_pPt_3_8","hEff_vs_Cent_pPt_3_8",10,0.,40.);
  TH1F * hEff_vs_Cent_pPt_8_20 = new TH1F("hEff_vs_Cent_pPt_8_20","hEff_vs_Cent_pPt_8_20",10,0.,40.);
  TH1F * hEff_vs_Cent_pPt_20_Inf = new TH1F("hEff_vs_Cent_pPt_20_Inf","hEff_vs_Cent_pPt_20_Inf",10,0.,40.);
  TH1F * weight_hEff_vs_Cent_pPt_05_14 = new TH1F("weight_hEff_vs_Cent_pPt_05_14","weight_hEff_vs_Cent_pPt_05_14",10,0.,40.);
  TH1F * weight_hEff_vs_Cent_pPt_14_18 = new TH1F("weight_hEff_vs_Cent_pPt_14_18","weight_hEff_vs_Cent_pPt_14_18",10,0.,40.);
  TH1F * weight_hEff_vs_Cent_pPt_18_3 = new TH1F("weight_hEff_vs_Cent_pPt_18_3","weight_hEff_vs_Cent_pPt_18_3",10,0.,40.);
  TH1F * weight_hEff_vs_Cent_pPt_3_8 = new TH1F("weight_hEff_vs_Cent_pPt_3_8","weight_hEff_vs_Cent_pPt_3_8",10,0.,40.);
  TH1F * weight_hEff_vs_Cent_pPt_8_20 = new TH1F("weight_hEff_vs_Cent_pPt_8_20","weight_hEff_vs_Cent_pPt_8_20",10,0.,40.);
  TH1F * weight_hEff_vs_Cent_pPt_20_Inf = new TH1F("weight_hEff_vs_Cent_pPt_20_Inf","weight_hEff_vs_Cent_pPt_20_Inf",10,0.,40.);

/////////
//  
//  Event loop
//
/////////
  int maxEvents = t->GetEntries();
  maxEvents = 40000.;
  for(int iev = 0; iev < maxEvents; ++iev) {
     if(iev%1000==0)cout<<"Processing entry : "<<iev<<" / "<<t->GetEntries()<<endl;
     t->GetEntry(iev);

     int cent = t->evt.hiBin;

     for(int i = 0; i < t->track.nParticle; ++i) {

        double simPt = t->track.pPt[i];
        double simEta = t->track.pEta[i];
        double simPhi = t->track.pPhi[i];
/*
        std::cerr<<"   simPt: " << simPt << std::endl;
        std::cerr<<"   simEta: " << simEta << std::endl;
        std::cerr<<"   simPhi: " << simPhi << std::endl;
*/
        double weight = 0.;
        if(simPt>0.5 && simPt<1.4)
           weight = hSim3D_eta_phi_pT_05_14->GetBinContent(hSim3D_eta_phi_pT_05_14->GetXaxis()->FindBin(simEta),hSim3D_eta_phi_pT_05_14->GetYaxis()->FindBin(simPhi));
        if(simPt>1.4 && simPt<1.8)
           weight = hSim3D_eta_phi_pT_14_18->GetBinContent(hSim3D_eta_phi_pT_14_18->GetXaxis()->FindBin(simEta),hSim3D_eta_phi_pT_14_18->GetYaxis()->FindBin(simPhi));
        if(simPt>1.8 && simPt<3.)
           weight = hSim3D_eta_phi_pT_18_3->GetBinContent(hSim3D_eta_phi_pT_18_3->GetXaxis()->FindBin(simEta),hSim3D_eta_phi_pT_18_3->GetYaxis()->FindBin(simPhi));
        if(simPt>3. && simPt<8.)
           weight = hSim3D_eta_phi_pT_3_8->GetBinContent(hSim3D_eta_phi_pT_3_8->GetXaxis()->FindBin(simEta),hSim3D_eta_phi_pT_3_8->GetYaxis()->FindBin(simPhi));
        if(simPt>8. && simPt<20.)
           weight = hSim3D_eta_phi_pT_8_20->GetBinContent(hSim3D_eta_phi_pT_8_20->GetXaxis()->FindBin(simEta),hSim3D_eta_phi_pT_8_20->GetYaxis()->FindBin(simPhi));
        if(simPt>20)
           weight = hSim3D_eta_phi_pT_20_Inf->GetBinContent(hSim3D_eta_phi_pT_20_Inf->GetXaxis()->FindBin(simEta),hSim3D_eta_phi_pT_20_Inf->GetYaxis()->FindBin(simPhi));

        //use the inclusive correction
//        weight = hSim3D_eta_phi_inclusive->GetBinContent(hSim3D_eta_phi_inclusive->GetXaxis()->FindBin(simEta),hSim3D_eta_phi_inclusive->GetYaxis()->FindBin(simPhi));

//        std::cerr<<"   weight: " << weight << std::endl;

        //numerator
        if(simPt>0.5 && simPt<1.4 && t->track.pNRec[i]==1 && (t->track.mtrkQual[i]==1 || t->track.mtrkAlgo[i]<4)) {
           hEff_Cent_vs_pPt_pPt_05_num->Fill(simPt);
           weight_hEff_Cent_vs_pPt_pPt_05_num->Fill(simPt,weight);
           if(cent>=0 && cent<4) {
             test_05_14_num_C1->Fill(simPt);
             weight_test_05_14_num_C1->Fill(simPt,weight);
           }
           if(cent>=4 && cent<8) {
             test_05_14_num_C2->Fill(simPt);
             weight_test_05_14_num_C2->Fill(simPt,weight);
           }
           if(cent>=8 && cent<12) {
             test_05_14_num_C3->Fill(simPt);
             weight_test_05_14_num_C3->Fill(simPt,weight);
           }
           if(cent>=12 && cent<16) {
             test_05_14_num_C4->Fill(simPt);
             weight_test_05_14_num_C4->Fill(simPt,weight);
           }
           if(cent>=16 && cent<20) {
             test_05_14_num_C5->Fill(simPt);
             weight_test_05_14_num_C5->Fill(simPt,weight);
           }
           if(cent>=20 && cent<24) {
             test_05_14_num_C6->Fill(simPt);
             weight_test_05_14_num_C6->Fill(simPt,weight);
           }
           if(cent>=24 && cent<28) {
             test_05_14_num_C7->Fill(simPt);
             weight_test_05_14_num_C7->Fill(simPt,weight);
           }
           if(cent>=28 && cent<32) {
             test_05_14_num_C8->Fill(simPt);
             weight_test_05_14_num_C8->Fill(simPt,weight);
           }
           if(cent>=32 && cent<36) {
             test_05_14_num_C9->Fill(simPt);
             weight_test_05_14_num_C9->Fill(simPt,weight);
           }
           if(cent>=36 && cent<40) {
             test_05_14_num_C10->Fill(simPt);
             weight_test_05_14_num_C10->Fill(simPt,weight);
           }
        }
        if(simPt>1.4 && simPt<1.8 && t->track.pNRec[i]==1 && (t->track.mtrkQual[i]==1 || t->track.mtrkAlgo[i]<4)) {
           if(cent>=0 && cent<4) {
             test_14_18_num_C1->Fill(simPt);
             weight_test_14_18_num_C1->Fill(simPt,weight);
           }
           if(cent>=4 && cent<8) {
             test_14_18_num_C2->Fill(simPt);
             weight_test_14_18_num_C2->Fill(simPt,weight);
           }
           if(cent>=8 && cent<12) {
             test_14_18_num_C3->Fill(simPt);
             weight_test_14_18_num_C3->Fill(simPt,weight);
           }
           if(cent>=12 && cent<16) {
             test_14_18_num_C4->Fill(simPt);
             weight_test_14_18_num_C4->Fill(simPt,weight);
           }
           if(cent>=16 && cent<20) {
             test_14_18_num_C5->Fill(simPt);
             weight_test_14_18_num_C5->Fill(simPt,weight);
           }
           if(cent>=20 && cent<24) {
             test_14_18_num_C6->Fill(simPt);
             weight_test_14_18_num_C6->Fill(simPt,weight);
           }
           if(cent>=24 && cent<28) {
             test_14_18_num_C7->Fill(simPt);
             weight_test_14_18_num_C7->Fill(simPt,weight);
           }
           if(cent>=28 && cent<32) {
             test_14_18_num_C8->Fill(simPt);
             weight_test_14_18_num_C8->Fill(simPt,weight);
           }
           if(cent>=32 && cent<36) {
             test_14_18_num_C9->Fill(simPt);
             weight_test_14_18_num_C9->Fill(simPt,weight);
           }
           if(cent>=36 && cent<40) {
             test_14_18_num_C10->Fill(simPt);
             weight_test_14_18_num_C10->Fill(simPt,weight);
           }
        }
        if(simPt>3. && simPt<8. && t->track.pNRec[i]==1 && (t->track.mtrkQual[i]==1 || t->track.mtrkAlgo[i]<4)) {
           if(cent>=0 && cent<4) {
             test_3_8_num_C1->Fill(simPt);
             weight_test_3_8_num_C1->Fill(simPt,weight);
           }
           if(cent>=4 && cent<8) {
             test_3_8_num_C2->Fill(simPt);
             weight_test_3_8_num_C2->Fill(simPt,weight);
           }
           if(cent>=8 && cent<12) {
             test_3_8_num_C3->Fill(simPt);
             weight_test_3_8_num_C3->Fill(simPt,weight);
           }
           if(cent>=12 && cent<16) {
             test_3_8_num_C4->Fill(simPt);
             weight_test_3_8_num_C4->Fill(simPt,weight);
           }
           if(cent>=16 && cent<20) {
             test_3_8_num_C5->Fill(simPt);
             weight_test_3_8_num_C5->Fill(simPt,weight);
           }
           if(cent>=20 && cent<24) {
             test_3_8_num_C6->Fill(simPt);
             weight_test_3_8_num_C6->Fill(simPt,weight);
           }
           if(cent>=24 && cent<28) {
             test_3_8_num_C7->Fill(simPt);
             weight_test_3_8_num_C7->Fill(simPt,weight);
           }
           if(cent>=28 && cent<32) {
             test_3_8_num_C8->Fill(simPt);
             weight_test_3_8_num_C8->Fill(simPt,weight);
           }
           if(cent>=32 && cent<36) {
             test_3_8_num_C9->Fill(simPt);
             weight_test_3_8_num_C9->Fill(simPt,weight);
           }
           if(cent>=36 && cent<40) {
             test_3_8_num_C10->Fill(simPt);
             weight_test_3_8_num_C10->Fill(simPt,weight);
           }
        }
        if(simPt>1.8 && simPt<3. && t->track.pNRec[i]==1 && (t->track.mtrkQual[i]==1 || t->track.mtrkAlgo[i]<4)) {
           if(cent>=0 && cent<4) {
             test_18_3_num_C1->Fill(simPt);
             weight_test_18_3_num_C1->Fill(simPt,weight);
           }
           if(cent>=4 && cent<8) {
             test_18_3_num_C2->Fill(simPt);
             weight_test_18_3_num_C2->Fill(simPt,weight);
           }
           if(cent>=8 && cent<12) {
             test_18_3_num_C3->Fill(simPt);
             weight_test_18_3_num_C3->Fill(simPt,weight);
           }
           if(cent>=12 && cent<16) {
             test_18_3_num_C4->Fill(simPt);
             weight_test_18_3_num_C4->Fill(simPt,weight);
           }
           if(cent>=16 && cent<20) {
             test_18_3_num_C5->Fill(simPt);
             weight_test_18_3_num_C5->Fill(simPt,weight);
           }
           if(cent>=20 && cent<24) {
             test_18_3_num_C6->Fill(simPt);
             weight_test_18_3_num_C6->Fill(simPt,weight);
           }
           if(cent>=24 && cent<28) {
             test_18_3_num_C7->Fill(simPt);
             weight_test_18_3_num_C7->Fill(simPt,weight);
           }
           if(cent>=28 && cent<32) {
             test_18_3_num_C8->Fill(simPt);
             weight_test_18_3_num_C8->Fill(simPt,weight);
           }
           if(cent>=32 && cent<36) {
             test_18_3_num_C9->Fill(simPt);
             weight_test_18_3_num_C9->Fill(simPt,weight);
           }
           if(cent>=36 && cent<40) {
             test_18_3_num_C10->Fill(simPt);
             weight_test_18_3_num_C10->Fill(simPt,weight);
           }
        }
        if(simPt>8. && simPt<20. && t->track.pNRec[i]==1 && (t->track.mtrkQual[i]==1 || t->track.mtrkAlgo[i]<4)) {
           if(cent>=0 && cent<4) {
             test_8_20_num_C1->Fill(simPt);
             weight_test_8_20_num_C1->Fill(simPt,weight);
           }
           if(cent>=4 && cent<8) {
             test_8_20_num_C2->Fill(simPt);
             weight_test_8_20_num_C2->Fill(simPt,weight);
           }
           if(cent>=8 && cent<12) {
             test_8_20_num_C3->Fill(simPt);
             weight_test_8_20_num_C3->Fill(simPt,weight);
           }
           if(cent>=12 && cent<16) {
             test_8_20_num_C4->Fill(simPt);
             weight_test_8_20_num_C4->Fill(simPt,weight);
           }
           if(cent>=16 && cent<20) {
             test_8_20_num_C5->Fill(simPt);
             weight_test_8_20_num_C5->Fill(simPt,weight);
           }
           if(cent>=20 && cent<24) {
             test_8_20_num_C6->Fill(simPt);
             weight_test_8_20_num_C6->Fill(simPt,weight);
           }
           if(cent>=24 && cent<28) {
             test_8_20_num_C7->Fill(simPt);
             weight_test_8_20_num_C7->Fill(simPt,weight);
           }
           if(cent>=28 && cent<32) {
             test_8_20_num_C8->Fill(simPt);
             weight_test_8_20_num_C8->Fill(simPt,weight);
           }
           if(cent>=32 && cent<36) {
             test_8_20_num_C9->Fill(simPt);
             weight_test_8_20_num_C9->Fill(simPt,weight);
           }
           if(cent>=36 && cent<40) {
             test_8_20_num_C10->Fill(simPt);
             weight_test_8_20_num_C10->Fill(simPt,weight);
           }
        }
        if(simPt>20. && t->track.pNRec[i]==1 && (t->track.mtrkQual[i]==1 || t->track.mtrkAlgo[i]<4)) {
           if(cent>=0 && cent<4) {
             test_20_Inf_num_C1->Fill(simPt);
             weight_test_20_Inf_num_C1->Fill(simPt,weight);
           }
           if(cent>=4 && cent<8) {
             test_20_Inf_num_C2->Fill(simPt);
             weight_test_20_Inf_num_C2->Fill(simPt,weight);
           }
           if(cent>=8 && cent<12) {
             test_20_Inf_num_C3->Fill(simPt);
             weight_test_20_Inf_num_C3->Fill(simPt,weight);
           }
           if(cent>=12 && cent<16) {
             test_20_Inf_num_C4->Fill(simPt);
             weight_test_20_Inf_num_C4->Fill(simPt,weight);
           }
           if(cent>=16 && cent<20) {
             test_20_Inf_num_C5->Fill(simPt);
             weight_test_20_Inf_num_C5->Fill(simPt,weight);
           }
           if(cent>=20 && cent<24) {
             test_20_Inf_num_C6->Fill(simPt);
             weight_test_20_Inf_num_C6->Fill(simPt,weight);
           }
           if(cent>=24 && cent<28) {
             test_20_Inf_num_C7->Fill(simPt);
             weight_test_20_Inf_num_C7->Fill(simPt,weight);
           }
           if(cent>=28 && cent<32) {
             test_20_Inf_num_C8->Fill(simPt);
             weight_test_20_Inf_num_C8->Fill(simPt,weight);
           }
           if(cent>=32 && cent<36) {
             test_20_Inf_num_C9->Fill(simPt);
             weight_test_20_Inf_num_C9->Fill(simPt,weight);
           }
           if(cent>=36 && cent<40) {
             test_20_Inf_num_C10->Fill(simPt);
             weight_test_20_Inf_num_C10->Fill(simPt,weight);
           }
        }

        //denominator
        if(simPt>0.5 && simPt<1.4) {
           hEff_Cent_vs_pPt_pPt_05_den->Fill(simPt);
           weight_hEff_Cent_vs_pPt_pPt_05_den->Fill(simPt,weight);
           if(cent>=0 && cent<4) {
             test_05_14_den_C1->Fill(simPt);
             weight_test_05_14_den_C1->Fill(simPt,weight);
           }
           if(cent>=4 && cent<8) {
             test_05_14_den_C2->Fill(simPt);
             weight_test_05_14_den_C2->Fill(simPt,weight);
           }
           if(cent>=8 && cent<12) {
             test_05_14_den_C3->Fill(simPt);
             weight_test_05_14_den_C3->Fill(simPt,weight);
           }
           if(cent>=12 && cent<16) {
             test_05_14_den_C4->Fill(simPt);
             weight_test_05_14_den_C4->Fill(simPt,weight);
           }
           if(cent>=16 && cent<20) {
             test_05_14_den_C5->Fill(simPt);
             weight_test_05_14_den_C5->Fill(simPt,weight);
           }
           if(cent>=20 && cent<24) {
             test_05_14_den_C6->Fill(simPt);
             weight_test_05_14_den_C6->Fill(simPt,weight);
           }
           if(cent>=24 && cent<28) {
             test_05_14_den_C7->Fill(simPt);
             weight_test_05_14_den_C7->Fill(simPt,weight);
           }
           if(cent>=28 && cent<32) {
             test_05_14_den_C8->Fill(simPt);
             weight_test_05_14_den_C8->Fill(simPt,weight);
           }
           if(cent>=32 && cent<36) {
             test_05_14_den_C9->Fill(simPt);
             weight_test_05_14_den_C9->Fill(simPt,weight);
           }
           if(cent>=36 && cent<40) {
             test_05_14_den_C10->Fill(simPt);
             weight_test_05_14_den_C10->Fill(simPt,weight);
           }
        }
        if(simPt>1.4 && simPt<1.8) {
           if(cent>=0 && cent<4) {
             test_14_18_den_C1->Fill(simPt);
             weight_test_14_18_den_C1->Fill(simPt,weight);
           }
           if(cent>=4 && cent<8) {
             test_14_18_den_C2->Fill(simPt);
             weight_test_14_18_den_C2->Fill(simPt,weight);
           }
           if(cent>=8 && cent<12) {
             test_14_18_den_C3->Fill(simPt);
             weight_test_14_18_den_C3->Fill(simPt,weight);
           }
           if(cent>=12 && cent<16) {
             test_14_18_den_C4->Fill(simPt);
             weight_test_14_18_den_C4->Fill(simPt,weight);
           }
           if(cent>=16 && cent<20) {
             test_14_18_den_C5->Fill(simPt);
             weight_test_14_18_den_C5->Fill(simPt,weight);
           }
           if(cent>=20 && cent<24) {
             test_14_18_den_C6->Fill(simPt);
             weight_test_14_18_den_C6->Fill(simPt,weight);
           }
           if(cent>=24 && cent<28) {
             test_14_18_den_C7->Fill(simPt);
             weight_test_14_18_den_C7->Fill(simPt,weight);
           }
           if(cent>=28 && cent<32) {
             test_14_18_den_C8->Fill(simPt);
             weight_test_14_18_den_C8->Fill(simPt,weight);
           }
           if(cent>=32 && cent<36) {
             test_14_18_den_C9->Fill(simPt);
             weight_test_14_18_den_C9->Fill(simPt,weight);
           }
           if(cent>=36 && cent<40) {
             test_14_18_den_C10->Fill(simPt);
             weight_test_14_18_den_C10->Fill(simPt,weight);
           }
        }
        if(simPt>1.8 && simPt<3.) {
           if(cent>=0 && cent<4) {
             test_18_3_den_C1->Fill(simPt);
             weight_test_18_3_den_C1->Fill(simPt,weight);
           }
           if(cent>=4 && cent<8) {
             test_18_3_den_C2->Fill(simPt);
             weight_test_18_3_den_C2->Fill(simPt,weight);
           }
           if(cent>=8 && cent<12) {
             test_18_3_den_C3->Fill(simPt);
             weight_test_18_3_den_C3->Fill(simPt,weight);
           }
           if(cent>=12 && cent<16) {
             test_18_3_den_C4->Fill(simPt);
             weight_test_18_3_den_C4->Fill(simPt,weight);
           }
           if(cent>=16 && cent<20) {
             test_18_3_den_C5->Fill(simPt);
             weight_test_18_3_den_C5->Fill(simPt,weight);
           }
           if(cent>=20 && cent<24) {
             test_18_3_den_C6->Fill(simPt);
             weight_test_18_3_den_C6->Fill(simPt,weight);
           }
           if(cent>=24 && cent<28) {
             test_18_3_den_C7->Fill(simPt);
             weight_test_18_3_den_C7->Fill(simPt,weight);
           }
           if(cent>=28 && cent<32) {
             test_18_3_den_C8->Fill(simPt);
             weight_test_18_3_den_C8->Fill(simPt,weight);
           }
           if(cent>=32 && cent<36) {
             test_18_3_den_C9->Fill(simPt);
             weight_test_18_3_den_C9->Fill(simPt,weight);
           }
           if(cent>=36 && cent<40) {
             test_18_3_den_C10->Fill(simPt);
             weight_test_18_3_den_C10->Fill(simPt,weight);
           }
        }
        if(simPt>3. && simPt<8.) {
           if(cent>=0 && cent<4) {
             test_3_8_den_C1->Fill(simPt);
             weight_test_3_8_den_C1->Fill(simPt,weight);
           }
           if(cent>=4 && cent<8) {
             test_3_8_den_C2->Fill(simPt);
             weight_test_3_8_den_C2->Fill(simPt,weight);
           }
           if(cent>=8 && cent<12) {
             test_3_8_den_C3->Fill(simPt);
             weight_test_3_8_den_C3->Fill(simPt,weight);
           }
           if(cent>=12 && cent<16) {
             test_3_8_den_C4->Fill(simPt);
             weight_test_3_8_den_C4->Fill(simPt,weight);
           }
           if(cent>=16 && cent<20) {
             test_3_8_den_C5->Fill(simPt);
             weight_test_3_8_den_C5->Fill(simPt,weight);
           }
           if(cent>=20 && cent<24) {
             test_3_8_den_C6->Fill(simPt);
             weight_test_3_8_den_C6->Fill(simPt,weight);
           }
           if(cent>=24 && cent<28) {
             test_3_8_den_C7->Fill(simPt);
             weight_test_3_8_den_C7->Fill(simPt,weight);
           }
           if(cent>=28 && cent<32) {
             test_3_8_den_C8->Fill(simPt);
             weight_test_3_8_den_C8->Fill(simPt,weight);
           }
           if(cent>=32 && cent<36) {
             test_3_8_den_C9->Fill(simPt);
             weight_test_3_8_den_C9->Fill(simPt,weight);
           }
           if(cent>=36 && cent<40) {
             test_3_8_den_C10->Fill(simPt);
             weight_test_3_8_den_C10->Fill(simPt,weight);
           }
        }
        if(simPt>8. && simPt<20.) {
           if(cent>=0 && cent<4) {
             test_8_20_den_C1->Fill(simPt);
             weight_test_8_20_den_C1->Fill(simPt,weight);
           }
           if(cent>=4 && cent<8) {
             test_8_20_den_C2->Fill(simPt);
             weight_test_8_20_den_C2->Fill(simPt,weight);
           }
           if(cent>=8 && cent<12) {
             test_8_20_den_C3->Fill(simPt);
             weight_test_8_20_den_C3->Fill(simPt,weight);
           }
           if(cent>=12 && cent<16) {
             test_8_20_den_C4->Fill(simPt);
             weight_test_8_20_den_C4->Fill(simPt,weight);
           }
           if(cent>=16 && cent<20) {
             test_8_20_den_C5->Fill(simPt);
             weight_test_8_20_den_C5->Fill(simPt,weight);
           }
           if(cent>=20 && cent<24) {
             test_8_20_den_C6->Fill(simPt);
             weight_test_8_20_den_C6->Fill(simPt,weight);
           }
           if(cent>=24 && cent<28) {
             test_8_20_den_C7->Fill(simPt);
             weight_test_8_20_den_C7->Fill(simPt,weight);
           }
           if(cent>=28 && cent<32) {
             test_8_20_den_C8->Fill(simPt);
             weight_test_8_20_den_C8->Fill(simPt,weight);
           }
           if(cent>=32 && cent<36) {
             test_8_20_den_C9->Fill(simPt);
             weight_test_8_20_den_C9->Fill(simPt,weight);
           }
           if(cent>=36 && cent<40) {
             test_8_20_den_C10->Fill(simPt);
             weight_test_8_20_den_C10->Fill(simPt,weight);
           }
        }
        if(simPt>20.) {
           if(cent>=0 && cent<4) {
             test_20_Inf_den_C1->Fill(simPt);
             weight_test_20_Inf_den_C1->Fill(simPt,weight);
           }
           if(cent>=4 && cent<8) {
             test_20_Inf_den_C2->Fill(simPt);
             weight_test_20_Inf_den_C2->Fill(simPt,weight);
           }
           if(cent>=8 && cent<12) {
             test_20_Inf_den_C3->Fill(simPt);
             weight_test_20_Inf_den_C3->Fill(simPt,weight);
           }
           if(cent>=12 && cent<16) {
             test_20_Inf_den_C4->Fill(simPt);
             weight_test_20_Inf_den_C4->Fill(simPt,weight);
           }
           if(cent>=16 && cent<20) {
             test_20_Inf_den_C5->Fill(simPt);
             weight_test_20_Inf_den_C5->Fill(simPt,weight);
           }
           if(cent>=20 && cent<24) {
             test_20_Inf_den_C6->Fill(simPt);
             weight_test_20_Inf_den_C6->Fill(simPt,weight);
           }
           if(cent>=24 && cent<28) {
             test_20_Inf_den_C7->Fill(simPt);
             weight_test_20_Inf_den_C7->Fill(simPt,weight);
           }
           if(cent>=28 && cent<32) {
             test_20_Inf_den_C8->Fill(simPt);
             weight_test_20_Inf_den_C8->Fill(simPt,weight);
           }
           if(cent>=32 && cent<36) {
             test_20_Inf_den_C9->Fill(simPt);
             weight_test_20_Inf_den_C9->Fill(simPt,weight);
           }
           if(cent>=36 && cent<40) {
             test_20_Inf_den_C10->Fill(simPt);
             weight_test_20_Inf_den_C10->Fill(simPt,weight);
           }
        }
     }
 
  }


/////////
//
// compute efficiencies
//
/////////

  test_05_14_num_C1->Divide(test_05_14_den_C1);
  test_05_14_num_C2->Divide(test_05_14_den_C2);
  test_05_14_num_C3->Divide(test_05_14_den_C3);
  test_05_14_num_C4->Divide(test_05_14_den_C4);
  test_05_14_num_C5->Divide(test_05_14_den_C5);
  test_05_14_num_C6->Divide(test_05_14_den_C6);
  test_05_14_num_C7->Divide(test_05_14_den_C7);
  test_05_14_num_C8->Divide(test_05_14_den_C8);
  test_05_14_num_C9->Divide(test_05_14_den_C9);
  test_05_14_num_C10->Divide(test_05_14_den_C10);

  test_14_18_num_C1->Divide(test_14_18_den_C1);
  test_14_18_num_C2->Divide(test_14_18_den_C2);
  test_14_18_num_C3->Divide(test_14_18_den_C3);
  test_14_18_num_C4->Divide(test_14_18_den_C4);
  test_14_18_num_C5->Divide(test_14_18_den_C5);
  test_14_18_num_C6->Divide(test_14_18_den_C6);
  test_14_18_num_C7->Divide(test_14_18_den_C7);
  test_14_18_num_C8->Divide(test_14_18_den_C8);
  test_14_18_num_C9->Divide(test_14_18_den_C9);
  test_14_18_num_C10->Divide(test_14_18_den_C10);

  test_18_3_num_C1->Divide(test_18_3_den_C1);
  test_18_3_num_C2->Divide(test_18_3_den_C2);
  test_18_3_num_C3->Divide(test_18_3_den_C3);
  test_18_3_num_C4->Divide(test_18_3_den_C4);
  test_18_3_num_C5->Divide(test_18_3_den_C5);
  test_18_3_num_C6->Divide(test_18_3_den_C6);
  test_18_3_num_C7->Divide(test_18_3_den_C7);
  test_18_3_num_C8->Divide(test_18_3_den_C8);
  test_18_3_num_C9->Divide(test_18_3_den_C9);
  test_18_3_num_C10->Divide(test_18_3_den_C10);

  test_3_8_num_C1->Divide(test_3_8_den_C1);
  test_3_8_num_C2->Divide(test_3_8_den_C2);
  test_3_8_num_C3->Divide(test_3_8_den_C3);
  test_3_8_num_C4->Divide(test_3_8_den_C4);
  test_3_8_num_C5->Divide(test_3_8_den_C5);
  test_3_8_num_C6->Divide(test_3_8_den_C6);
  test_3_8_num_C7->Divide(test_3_8_den_C7);
  test_3_8_num_C8->Divide(test_3_8_den_C8);
  test_3_8_num_C9->Divide(test_3_8_den_C9);
  test_3_8_num_C10->Divide(test_3_8_den_C10);

  test_8_20_num_C1->Divide(test_8_20_den_C1);
  test_8_20_num_C2->Divide(test_8_20_den_C2);
  test_8_20_num_C3->Divide(test_8_20_den_C3);
  test_8_20_num_C4->Divide(test_8_20_den_C4);
  test_8_20_num_C5->Divide(test_8_20_den_C5);
  test_8_20_num_C6->Divide(test_8_20_den_C6);
  test_8_20_num_C7->Divide(test_8_20_den_C7);
  test_8_20_num_C8->Divide(test_8_20_den_C8);
  test_8_20_num_C9->Divide(test_8_20_den_C9);
  test_8_20_num_C10->Divide(test_8_20_den_C10);

  test_20_Inf_num_C1->Divide(test_20_Inf_den_C1);
  test_20_Inf_num_C2->Divide(test_20_Inf_den_C2);
  test_20_Inf_num_C3->Divide(test_20_Inf_den_C3);
  test_20_Inf_num_C4->Divide(test_20_Inf_den_C4);
  test_20_Inf_num_C5->Divide(test_20_Inf_den_C5);
  test_20_Inf_num_C6->Divide(test_20_Inf_den_C6);
  test_20_Inf_num_C7->Divide(test_20_Inf_den_C7);
  test_20_Inf_num_C8->Divide(test_20_Inf_den_C8);
  test_20_Inf_num_C9->Divide(test_20_Inf_den_C9);
  test_20_Inf_num_C10->Divide(test_20_Inf_den_C10);

  //don't weight in the denominator
  weight_test_05_14_num_C1->Divide(test_05_14_den_C1);
  weight_test_05_14_num_C2->Divide(test_05_14_den_C2);
  weight_test_05_14_num_C3->Divide(test_05_14_den_C3);
  weight_test_05_14_num_C4->Divide(test_05_14_den_C4);
  weight_test_05_14_num_C5->Divide(test_05_14_den_C5);
  weight_test_05_14_num_C6->Divide(test_05_14_den_C6);
  weight_test_05_14_num_C7->Divide(test_05_14_den_C7);
  weight_test_05_14_num_C8->Divide(test_05_14_den_C8);
  weight_test_05_14_num_C9->Divide(test_05_14_den_C9);
  weight_test_05_14_num_C10->Divide(test_05_14_den_C10);

  weight_test_14_18_num_C1->Divide(test_14_18_den_C1);
  weight_test_14_18_num_C2->Divide(test_14_18_den_C2);
  weight_test_14_18_num_C3->Divide(test_14_18_den_C3);
  weight_test_14_18_num_C4->Divide(test_14_18_den_C4);
  weight_test_14_18_num_C5->Divide(test_14_18_den_C5);
  weight_test_14_18_num_C6->Divide(test_14_18_den_C6);
  weight_test_14_18_num_C7->Divide(test_14_18_den_C7);
  weight_test_14_18_num_C8->Divide(test_14_18_den_C8);
  weight_test_14_18_num_C9->Divide(test_14_18_den_C9);
  weight_test_14_18_num_C10->Divide(test_14_18_den_C10);

  weight_test_18_3_num_C1->Divide(test_18_3_den_C1);
  weight_test_18_3_num_C2->Divide(test_18_3_den_C2);
  weight_test_18_3_num_C3->Divide(test_18_3_den_C3);
  weight_test_18_3_num_C4->Divide(test_18_3_den_C4);
  weight_test_18_3_num_C5->Divide(test_18_3_den_C5);
  weight_test_18_3_num_C6->Divide(test_18_3_den_C6);
  weight_test_18_3_num_C7->Divide(test_18_3_den_C7);
  weight_test_18_3_num_C8->Divide(test_18_3_den_C8);
  weight_test_18_3_num_C9->Divide(test_18_3_den_C9);
  weight_test_18_3_num_C10->Divide(test_18_3_den_C10);

  weight_test_3_8_num_C1->Divide(test_3_8_den_C1);
  weight_test_3_8_num_C2->Divide(test_3_8_den_C2);
  weight_test_3_8_num_C3->Divide(test_3_8_den_C3);
  weight_test_3_8_num_C4->Divide(test_3_8_den_C4);
  weight_test_3_8_num_C5->Divide(test_3_8_den_C5);
  weight_test_3_8_num_C6->Divide(test_3_8_den_C6);
  weight_test_3_8_num_C7->Divide(test_3_8_den_C7);
  weight_test_3_8_num_C8->Divide(test_3_8_den_C8);
  weight_test_3_8_num_C9->Divide(test_3_8_den_C9);
  weight_test_3_8_num_C10->Divide(test_3_8_den_C10);

  weight_test_8_20_num_C1->Divide(test_8_20_den_C1);
  weight_test_8_20_num_C2->Divide(test_8_20_den_C2);
  weight_test_8_20_num_C3->Divide(test_8_20_den_C3);
  weight_test_8_20_num_C4->Divide(test_8_20_den_C4);
  weight_test_8_20_num_C5->Divide(test_8_20_den_C5);
  weight_test_8_20_num_C6->Divide(test_8_20_den_C6);
  weight_test_8_20_num_C7->Divide(test_8_20_den_C7);
  weight_test_8_20_num_C8->Divide(test_8_20_den_C8);
  weight_test_8_20_num_C9->Divide(test_8_20_den_C9);
  weight_test_8_20_num_C10->Divide(test_8_20_den_C10);

  weight_test_20_Inf_num_C1->Divide(test_20_Inf_den_C1);
  weight_test_20_Inf_num_C2->Divide(test_20_Inf_den_C2);
  weight_test_20_Inf_num_C3->Divide(test_20_Inf_den_C3);
  weight_test_20_Inf_num_C4->Divide(test_20_Inf_den_C4);
  weight_test_20_Inf_num_C5->Divide(test_20_Inf_den_C5);
  weight_test_20_Inf_num_C6->Divide(test_20_Inf_den_C6);
  weight_test_20_Inf_num_C7->Divide(test_20_Inf_den_C7);
  weight_test_20_Inf_num_C8->Divide(test_20_Inf_den_C8);
  weight_test_20_Inf_num_C9->Divide(test_20_Inf_den_C9);
  weight_test_20_Inf_num_C10->Divide(test_20_Inf_den_C10);


////////////
//
// filling average efficiencies
//
//////////

  hEff_vs_Cent_pPt_05->SetBinContent(1,test_05_14_num_C1->GetBinContent(1));
  hEff_vs_Cent_pPt_05->SetBinError(1,test_05_14_num_C1->GetBinError(1));
  hEff_vs_Cent_pPt_05->SetBinContent(2,test_05_14_num_C2->GetBinContent(1));
  hEff_vs_Cent_pPt_05->SetBinError(2,test_05_14_num_C2->GetBinError(1));
  hEff_vs_Cent_pPt_05->SetBinContent(3,test_05_14_num_C3->GetBinContent(1));
  hEff_vs_Cent_pPt_05->SetBinError(3,test_05_14_num_C3->GetBinError(1));
  hEff_vs_Cent_pPt_05->SetBinContent(4,test_05_14_num_C4->GetBinContent(1));
  hEff_vs_Cent_pPt_05->SetBinError(4,test_05_14_num_C4->GetBinError(1));
  hEff_vs_Cent_pPt_05->SetBinContent(5,test_05_14_num_C5->GetBinContent(1));
  hEff_vs_Cent_pPt_05->SetBinError(5,test_05_14_num_C5->GetBinError(1));
  hEff_vs_Cent_pPt_05->SetBinContent(6,test_05_14_num_C6->GetBinContent(1));
  hEff_vs_Cent_pPt_05->SetBinError(6,test_05_14_num_C6->GetBinError(1));
  hEff_vs_Cent_pPt_05->SetBinContent(7,test_05_14_num_C7->GetBinContent(1));
  hEff_vs_Cent_pPt_05->SetBinError(7,test_05_14_num_C7->GetBinError(1));
  hEff_vs_Cent_pPt_05->SetBinContent(8,test_05_14_num_C8->GetBinContent(1));
  hEff_vs_Cent_pPt_05->SetBinError(8,test_05_14_num_C8->GetBinError(1));
  hEff_vs_Cent_pPt_05->SetBinContent(9,test_05_14_num_C9->GetBinContent(1));
  hEff_vs_Cent_pPt_05->SetBinError(9,test_05_14_num_C9->GetBinError(1));
  hEff_vs_Cent_pPt_05->SetBinContent(10,test_05_14_num_C10->GetBinContent(1));
  hEff_vs_Cent_pPt_05->SetBinError(10,test_05_14_num_C10->GetBinError(1));

  hEff_vs_Cent_pPt_14_18->SetBinContent(1,test_14_18_num_C1->GetBinContent(1));
  hEff_vs_Cent_pPt_14_18->SetBinError(1,test_14_18_num_C1->GetBinError(1));
  hEff_vs_Cent_pPt_14_18->SetBinContent(2,test_14_18_num_C2->GetBinContent(1));
  hEff_vs_Cent_pPt_14_18->SetBinError(2,test_14_18_num_C2->GetBinError(1));
  hEff_vs_Cent_pPt_14_18->SetBinContent(3,test_14_18_num_C3->GetBinContent(1));
  hEff_vs_Cent_pPt_14_18->SetBinError(3,test_14_18_num_C3->GetBinError(1));
  hEff_vs_Cent_pPt_14_18->SetBinContent(4,test_14_18_num_C4->GetBinContent(1));
  hEff_vs_Cent_pPt_14_18->SetBinError(4,test_14_18_num_C4->GetBinError(1));
  hEff_vs_Cent_pPt_14_18->SetBinContent(5,test_14_18_num_C5->GetBinContent(1));
  hEff_vs_Cent_pPt_14_18->SetBinError(5,test_14_18_num_C5->GetBinError(1));
  hEff_vs_Cent_pPt_14_18->SetBinContent(6,test_14_18_num_C6->GetBinContent(1));
  hEff_vs_Cent_pPt_14_18->SetBinError(6,test_14_18_num_C6->GetBinError(1));
  hEff_vs_Cent_pPt_14_18->SetBinContent(7,test_14_18_num_C7->GetBinContent(1));
  hEff_vs_Cent_pPt_14_18->SetBinError(7,test_14_18_num_C7->GetBinError(1));
  hEff_vs_Cent_pPt_14_18->SetBinContent(8,test_14_18_num_C8->GetBinContent(1));
  hEff_vs_Cent_pPt_14_18->SetBinError(8,test_14_18_num_C8->GetBinError(1));
  hEff_vs_Cent_pPt_14_18->SetBinContent(9,test_14_18_num_C9->GetBinContent(1));
  hEff_vs_Cent_pPt_14_18->SetBinError(9,test_14_18_num_C9->GetBinError(1));
  hEff_vs_Cent_pPt_14_18->SetBinContent(10,test_14_18_num_C10->GetBinContent(1));
  hEff_vs_Cent_pPt_14_18->SetBinError(10,test_14_18_num_C10->GetBinError(1));

  hEff_vs_Cent_pPt_18_3->SetBinContent(1,test_18_3_num_C1->GetBinContent(1));
  hEff_vs_Cent_pPt_18_3->SetBinError(1,test_18_3_num_C1->GetBinError(1));
  hEff_vs_Cent_pPt_18_3->SetBinContent(2,test_18_3_num_C2->GetBinContent(1));
  hEff_vs_Cent_pPt_18_3->SetBinError(2,test_18_3_num_C2->GetBinError(1));
  hEff_vs_Cent_pPt_18_3->SetBinContent(3,test_18_3_num_C3->GetBinContent(1));
  hEff_vs_Cent_pPt_18_3->SetBinError(3,test_18_3_num_C3->GetBinError(1));
  hEff_vs_Cent_pPt_18_3->SetBinContent(4,test_18_3_num_C4->GetBinContent(1));
  hEff_vs_Cent_pPt_18_3->SetBinError(4,test_18_3_num_C4->GetBinError(1));
  hEff_vs_Cent_pPt_18_3->SetBinContent(5,test_18_3_num_C5->GetBinContent(1));
  hEff_vs_Cent_pPt_18_3->SetBinError(5,test_18_3_num_C5->GetBinError(1));
  hEff_vs_Cent_pPt_18_3->SetBinContent(6,test_18_3_num_C6->GetBinContent(1));
  hEff_vs_Cent_pPt_18_3->SetBinError(6,test_18_3_num_C6->GetBinError(1));
  hEff_vs_Cent_pPt_18_3->SetBinContent(7,test_18_3_num_C7->GetBinContent(1));
  hEff_vs_Cent_pPt_18_3->SetBinError(7,test_18_3_num_C7->GetBinError(1));
  hEff_vs_Cent_pPt_18_3->SetBinContent(8,test_18_3_num_C8->GetBinContent(1));
  hEff_vs_Cent_pPt_18_3->SetBinError(8,test_18_3_num_C8->GetBinError(1));
  hEff_vs_Cent_pPt_18_3->SetBinContent(9,test_18_3_num_C9->GetBinContent(1));
  hEff_vs_Cent_pPt_18_3->SetBinError(9,test_18_3_num_C9->GetBinError(1));
  hEff_vs_Cent_pPt_18_3->SetBinContent(10,test_18_3_num_C10->GetBinContent(1));
  hEff_vs_Cent_pPt_18_3->SetBinError(10,test_18_3_num_C10->GetBinError(1));

  hEff_vs_Cent_pPt_3_8->SetBinContent(1,test_3_8_num_C1->GetBinContent(1));
  hEff_vs_Cent_pPt_3_8->SetBinError(1,test_3_8_num_C1->GetBinError(1));
  hEff_vs_Cent_pPt_3_8->SetBinContent(2,test_3_8_num_C2->GetBinContent(1));
  hEff_vs_Cent_pPt_3_8->SetBinError(2,test_3_8_num_C2->GetBinError(1));
  hEff_vs_Cent_pPt_3_8->SetBinContent(3,test_3_8_num_C3->GetBinContent(1));
  hEff_vs_Cent_pPt_3_8->SetBinError(3,test_3_8_num_C3->GetBinError(1));
  hEff_vs_Cent_pPt_3_8->SetBinContent(4,test_3_8_num_C4->GetBinContent(1));
  hEff_vs_Cent_pPt_3_8->SetBinError(4,test_3_8_num_C4->GetBinError(1));
  hEff_vs_Cent_pPt_3_8->SetBinContent(5,test_3_8_num_C5->GetBinContent(1));
  hEff_vs_Cent_pPt_3_8->SetBinError(5,test_3_8_num_C5->GetBinError(1));
  hEff_vs_Cent_pPt_3_8->SetBinContent(6,test_3_8_num_C6->GetBinContent(1));
  hEff_vs_Cent_pPt_3_8->SetBinError(6,test_3_8_num_C6->GetBinError(1));
  hEff_vs_Cent_pPt_3_8->SetBinContent(7,test_3_8_num_C7->GetBinContent(1));
  hEff_vs_Cent_pPt_3_8->SetBinError(7,test_3_8_num_C7->GetBinError(1));
  hEff_vs_Cent_pPt_3_8->SetBinContent(8,test_3_8_num_C8->GetBinContent(1));
  hEff_vs_Cent_pPt_3_8->SetBinError(8,test_3_8_num_C8->GetBinError(1));
  hEff_vs_Cent_pPt_3_8->SetBinContent(9,test_3_8_num_C9->GetBinContent(1));
  hEff_vs_Cent_pPt_3_8->SetBinError(9,test_3_8_num_C9->GetBinError(1));
  hEff_vs_Cent_pPt_3_8->SetBinContent(10,test_3_8_num_C10->GetBinContent(1));
  hEff_vs_Cent_pPt_3_8->SetBinError(10,test_3_8_num_C10->GetBinError(1));

  hEff_vs_Cent_pPt_8_20->SetBinContent(1,test_8_20_num_C1->GetBinContent(1));
  hEff_vs_Cent_pPt_8_20->SetBinError(1,test_8_20_num_C1->GetBinError(1));
  hEff_vs_Cent_pPt_8_20->SetBinContent(2,test_8_20_num_C2->GetBinContent(1));
  hEff_vs_Cent_pPt_8_20->SetBinError(2,test_8_20_num_C2->GetBinError(1));
  hEff_vs_Cent_pPt_8_20->SetBinContent(3,test_8_20_num_C3->GetBinContent(1));
  hEff_vs_Cent_pPt_8_20->SetBinError(3,test_8_20_num_C3->GetBinError(1));
  hEff_vs_Cent_pPt_8_20->SetBinContent(4,test_8_20_num_C4->GetBinContent(1));
  hEff_vs_Cent_pPt_8_20->SetBinError(4,test_8_20_num_C4->GetBinError(1));
  hEff_vs_Cent_pPt_8_20->SetBinContent(5,test_8_20_num_C5->GetBinContent(1));
  hEff_vs_Cent_pPt_8_20->SetBinError(5,test_8_20_num_C5->GetBinError(1));
  hEff_vs_Cent_pPt_8_20->SetBinContent(6,test_8_20_num_C6->GetBinContent(1));
  hEff_vs_Cent_pPt_8_20->SetBinError(6,test_8_20_num_C6->GetBinError(1));
  hEff_vs_Cent_pPt_8_20->SetBinContent(7,test_8_20_num_C7->GetBinContent(1));
  hEff_vs_Cent_pPt_8_20->SetBinError(7,test_8_20_num_C7->GetBinError(1));
  hEff_vs_Cent_pPt_8_20->SetBinContent(8,test_8_20_num_C8->GetBinContent(1));
  hEff_vs_Cent_pPt_8_20->SetBinError(8,test_8_20_num_C8->GetBinError(1));
  hEff_vs_Cent_pPt_8_20->SetBinContent(9,test_8_20_num_C9->GetBinContent(1));
  hEff_vs_Cent_pPt_8_20->SetBinError(9,test_8_20_num_C9->GetBinError(1));
  hEff_vs_Cent_pPt_8_20->SetBinContent(10,test_8_20_num_C10->GetBinContent(1));
  hEff_vs_Cent_pPt_8_20->SetBinError(10,test_8_20_num_C10->GetBinError(1));

  hEff_vs_Cent_pPt_20_Inf->SetBinContent(1,test_20_Inf_num_C1->GetBinContent(1));
  hEff_vs_Cent_pPt_20_Inf->SetBinError(1,test_20_Inf_num_C1->GetBinError(1));
  hEff_vs_Cent_pPt_20_Inf->SetBinContent(2,test_20_Inf_num_C2->GetBinContent(1));
  hEff_vs_Cent_pPt_20_Inf->SetBinError(2,test_20_Inf_num_C2->GetBinError(1));
  hEff_vs_Cent_pPt_20_Inf->SetBinContent(3,test_20_Inf_num_C3->GetBinContent(1));
  hEff_vs_Cent_pPt_20_Inf->SetBinError(3,test_20_Inf_num_C3->GetBinError(1));
  hEff_vs_Cent_pPt_20_Inf->SetBinContent(4,test_20_Inf_num_C4->GetBinContent(1));
  hEff_vs_Cent_pPt_20_Inf->SetBinError(4,test_20_Inf_num_C4->GetBinError(1));
  hEff_vs_Cent_pPt_20_Inf->SetBinContent(5,test_20_Inf_num_C5->GetBinContent(1));
  hEff_vs_Cent_pPt_20_Inf->SetBinError(5,test_20_Inf_num_C5->GetBinError(1));
  hEff_vs_Cent_pPt_20_Inf->SetBinContent(6,test_20_Inf_num_C6->GetBinContent(1));
  hEff_vs_Cent_pPt_20_Inf->SetBinError(6,test_20_Inf_num_C6->GetBinError(1));
  hEff_vs_Cent_pPt_20_Inf->SetBinContent(7,test_20_Inf_num_C7->GetBinContent(1));
  hEff_vs_Cent_pPt_20_Inf->SetBinError(7,test_20_Inf_num_C7->GetBinError(1));
  hEff_vs_Cent_pPt_20_Inf->SetBinContent(8,test_20_Inf_num_C8->GetBinContent(1));
  hEff_vs_Cent_pPt_20_Inf->SetBinError(8,test_20_Inf_num_C8->GetBinError(1));
  hEff_vs_Cent_pPt_20_Inf->SetBinContent(9,test_20_Inf_num_C9->GetBinContent(1));
  hEff_vs_Cent_pPt_20_Inf->SetBinError(9,test_20_Inf_num_C9->GetBinError(1));
  hEff_vs_Cent_pPt_20_Inf->SetBinContent(10,test_20_Inf_num_C10->GetBinContent(1));
  hEff_vs_Cent_pPt_20_Inf->SetBinError(10,test_20_Inf_num_C10->GetBinError(1));

  weight_hEff_vs_Cent_pPt_05_14->SetBinContent(1,weight_test_05_14_num_C1->GetBinContent(1));
  weight_hEff_vs_Cent_pPt_05_14->SetBinError(1,weight_test_05_14_num_C1->GetBinError(1));
  weight_hEff_vs_Cent_pPt_05_14->SetBinContent(2,weight_test_05_14_num_C2->GetBinContent(1));
  weight_hEff_vs_Cent_pPt_05_14->SetBinError(2,weight_test_05_14_num_C2->GetBinError(1));
  weight_hEff_vs_Cent_pPt_05_14->SetBinContent(3,weight_test_05_14_num_C3->GetBinContent(1));
  weight_hEff_vs_Cent_pPt_05_14->SetBinError(3,weight_test_05_14_num_C3->GetBinError(1));
  weight_hEff_vs_Cent_pPt_05_14->SetBinContent(4,weight_test_05_14_num_C4->GetBinContent(1));
  weight_hEff_vs_Cent_pPt_05_14->SetBinError(4,weight_test_05_14_num_C4->GetBinError(1));
  weight_hEff_vs_Cent_pPt_05_14->SetBinContent(5,weight_test_05_14_num_C5->GetBinContent(1));
  weight_hEff_vs_Cent_pPt_05_14->SetBinError(5,weight_test_05_14_num_C5->GetBinError(1));
  weight_hEff_vs_Cent_pPt_05_14->SetBinContent(6,weight_test_05_14_num_C6->GetBinContent(1));
  weight_hEff_vs_Cent_pPt_05_14->SetBinError(6,weight_test_05_14_num_C6->GetBinError(1));
  weight_hEff_vs_Cent_pPt_05_14->SetBinContent(7,weight_test_05_14_num_C7->GetBinContent(1));
  weight_hEff_vs_Cent_pPt_05_14->SetBinError(7,weight_test_05_14_num_C7->GetBinError(1));
  weight_hEff_vs_Cent_pPt_05_14->SetBinContent(8,weight_test_05_14_num_C8->GetBinContent(1));
  weight_hEff_vs_Cent_pPt_05_14->SetBinError(8,weight_test_05_14_num_C8->GetBinError(1));
  weight_hEff_vs_Cent_pPt_05_14->SetBinContent(9,weight_test_05_14_num_C9->GetBinContent(1));
  weight_hEff_vs_Cent_pPt_05_14->SetBinError(9,weight_test_05_14_num_C9->GetBinError(1));
  weight_hEff_vs_Cent_pPt_05_14->SetBinContent(10,weight_test_05_14_num_C10->GetBinContent(1));
  weight_hEff_vs_Cent_pPt_05_14->SetBinError(10,weight_test_05_14_num_C10->GetBinError(1));

  weight_hEff_vs_Cent_pPt_14_18->SetBinContent(1,weight_test_14_18_num_C1->GetBinContent(1));
  weight_hEff_vs_Cent_pPt_14_18->SetBinError(1,weight_test_14_18_num_C1->GetBinError(1));
  weight_hEff_vs_Cent_pPt_14_18->SetBinContent(2,weight_test_14_18_num_C2->GetBinContent(1));
  weight_hEff_vs_Cent_pPt_14_18->SetBinError(2,weight_test_14_18_num_C2->GetBinError(1));
  weight_hEff_vs_Cent_pPt_14_18->SetBinContent(3,weight_test_14_18_num_C3->GetBinContent(1));
  weight_hEff_vs_Cent_pPt_14_18->SetBinError(3,weight_test_14_18_num_C3->GetBinError(1));
  weight_hEff_vs_Cent_pPt_14_18->SetBinContent(4,weight_test_14_18_num_C4->GetBinContent(1));
  weight_hEff_vs_Cent_pPt_14_18->SetBinError(4,weight_test_14_18_num_C4->GetBinError(1));
  weight_hEff_vs_Cent_pPt_14_18->SetBinContent(5,weight_test_14_18_num_C5->GetBinContent(1));
  weight_hEff_vs_Cent_pPt_14_18->SetBinError(5,weight_test_14_18_num_C5->GetBinError(1));
  weight_hEff_vs_Cent_pPt_14_18->SetBinContent(6,weight_test_14_18_num_C6->GetBinContent(1));
  weight_hEff_vs_Cent_pPt_14_18->SetBinError(6,weight_test_14_18_num_C6->GetBinError(1));
  weight_hEff_vs_Cent_pPt_14_18->SetBinContent(7,weight_test_14_18_num_C7->GetBinContent(1));
  weight_hEff_vs_Cent_pPt_14_18->SetBinError(7,weight_test_14_18_num_C7->GetBinError(1));
  weight_hEff_vs_Cent_pPt_14_18->SetBinContent(8,weight_test_14_18_num_C8->GetBinContent(1));
  weight_hEff_vs_Cent_pPt_14_18->SetBinError(8,weight_test_14_18_num_C8->GetBinError(1));
  weight_hEff_vs_Cent_pPt_14_18->SetBinContent(9,weight_test_14_18_num_C9->GetBinContent(1));
  weight_hEff_vs_Cent_pPt_14_18->SetBinError(9,weight_test_14_18_num_C9->GetBinError(1));
  weight_hEff_vs_Cent_pPt_14_18->SetBinContent(10,weight_test_14_18_num_C10->GetBinContent(1));
  weight_hEff_vs_Cent_pPt_14_18->SetBinError(10,weight_test_14_18_num_C10->GetBinError(1));

  weight_hEff_vs_Cent_pPt_18_3->SetBinContent(1,weight_test_18_3_num_C1->GetBinContent(1));
  weight_hEff_vs_Cent_pPt_18_3->SetBinError(1,weight_test_18_3_num_C1->GetBinError(1));
  weight_hEff_vs_Cent_pPt_18_3->SetBinContent(2,weight_test_18_3_num_C2->GetBinContent(1));
  weight_hEff_vs_Cent_pPt_18_3->SetBinError(2,weight_test_18_3_num_C2->GetBinError(1));
  weight_hEff_vs_Cent_pPt_18_3->SetBinContent(3,weight_test_18_3_num_C3->GetBinContent(1));
  weight_hEff_vs_Cent_pPt_18_3->SetBinError(3,weight_test_18_3_num_C3->GetBinError(1));
  weight_hEff_vs_Cent_pPt_18_3->SetBinContent(4,weight_test_18_3_num_C4->GetBinContent(1));
  weight_hEff_vs_Cent_pPt_18_3->SetBinError(4,weight_test_18_3_num_C4->GetBinError(1));
  weight_hEff_vs_Cent_pPt_18_3->SetBinContent(5,weight_test_18_3_num_C5->GetBinContent(1));
  weight_hEff_vs_Cent_pPt_18_3->SetBinError(5,weight_test_18_3_num_C5->GetBinError(1));
  weight_hEff_vs_Cent_pPt_18_3->SetBinContent(6,weight_test_18_3_num_C6->GetBinContent(1));
  weight_hEff_vs_Cent_pPt_18_3->SetBinError(6,weight_test_18_3_num_C6->GetBinError(1));
  weight_hEff_vs_Cent_pPt_18_3->SetBinContent(7,weight_test_18_3_num_C7->GetBinContent(1));
  weight_hEff_vs_Cent_pPt_18_3->SetBinError(7,weight_test_18_3_num_C7->GetBinError(1));
  weight_hEff_vs_Cent_pPt_18_3->SetBinContent(8,weight_test_18_3_num_C8->GetBinContent(1));
  weight_hEff_vs_Cent_pPt_18_3->SetBinError(8,weight_test_18_3_num_C8->GetBinError(1));
  weight_hEff_vs_Cent_pPt_18_3->SetBinContent(9,weight_test_18_3_num_C9->GetBinContent(1));
  weight_hEff_vs_Cent_pPt_18_3->SetBinError(9,weight_test_18_3_num_C9->GetBinError(1));
  weight_hEff_vs_Cent_pPt_18_3->SetBinContent(10,weight_test_18_3_num_C10->GetBinContent(1));
  weight_hEff_vs_Cent_pPt_18_3->SetBinError(10,weight_test_18_3_num_C10->GetBinError(1));

  weight_hEff_vs_Cent_pPt_3_8->SetBinContent(1,weight_test_3_8_num_C1->GetBinContent(1));
  weight_hEff_vs_Cent_pPt_3_8->SetBinError(1,weight_test_3_8_num_C1->GetBinError(1));
  weight_hEff_vs_Cent_pPt_3_8->SetBinContent(2,weight_test_3_8_num_C2->GetBinContent(1));
  weight_hEff_vs_Cent_pPt_3_8->SetBinError(2,weight_test_3_8_num_C2->GetBinError(1));
  weight_hEff_vs_Cent_pPt_3_8->SetBinContent(3,weight_test_3_8_num_C3->GetBinContent(1));
  weight_hEff_vs_Cent_pPt_3_8->SetBinError(3,weight_test_3_8_num_C3->GetBinError(1));
  weight_hEff_vs_Cent_pPt_3_8->SetBinContent(4,weight_test_3_8_num_C4->GetBinContent(1));
  weight_hEff_vs_Cent_pPt_3_8->SetBinError(4,weight_test_3_8_num_C4->GetBinError(1));
  weight_hEff_vs_Cent_pPt_3_8->SetBinContent(5,weight_test_3_8_num_C5->GetBinContent(1));
  weight_hEff_vs_Cent_pPt_3_8->SetBinError(5,weight_test_3_8_num_C5->GetBinError(1));
  weight_hEff_vs_Cent_pPt_3_8->SetBinContent(6,weight_test_3_8_num_C6->GetBinContent(1));
  weight_hEff_vs_Cent_pPt_3_8->SetBinError(6,weight_test_3_8_num_C6->GetBinError(1));
  weight_hEff_vs_Cent_pPt_3_8->SetBinContent(7,weight_test_3_8_num_C7->GetBinContent(1));
  weight_hEff_vs_Cent_pPt_3_8->SetBinError(7,weight_test_3_8_num_C7->GetBinError(1));
  weight_hEff_vs_Cent_pPt_3_8->SetBinContent(8,weight_test_3_8_num_C8->GetBinContent(1));
  weight_hEff_vs_Cent_pPt_3_8->SetBinError(8,weight_test_3_8_num_C8->GetBinError(1));
  weight_hEff_vs_Cent_pPt_3_8->SetBinContent(9,weight_test_3_8_num_C9->GetBinContent(1));
  weight_hEff_vs_Cent_pPt_3_8->SetBinError(9,weight_test_3_8_num_C9->GetBinError(1));
  weight_hEff_vs_Cent_pPt_3_8->SetBinContent(10,weight_test_3_8_num_C10->GetBinContent(1));
  weight_hEff_vs_Cent_pPt_3_8->SetBinError(10,weight_test_3_8_num_C10->GetBinError(1));

  weight_hEff_vs_Cent_pPt_8_20->SetBinContent(1,weight_test_8_20_num_C1->GetBinContent(1));
  weight_hEff_vs_Cent_pPt_8_20->SetBinError(1,weight_test_8_20_num_C1->GetBinError(1));
  weight_hEff_vs_Cent_pPt_8_20->SetBinContent(2,weight_test_8_20_num_C2->GetBinContent(1));
  weight_hEff_vs_Cent_pPt_8_20->SetBinError(2,weight_test_8_20_num_C2->GetBinError(1));
  weight_hEff_vs_Cent_pPt_8_20->SetBinContent(3,weight_test_8_20_num_C3->GetBinContent(1));
  weight_hEff_vs_Cent_pPt_8_20->SetBinError(3,weight_test_8_20_num_C3->GetBinError(1));
  weight_hEff_vs_Cent_pPt_8_20->SetBinContent(4,weight_test_8_20_num_C4->GetBinContent(1));
  weight_hEff_vs_Cent_pPt_8_20->SetBinError(4,weight_test_8_20_num_C4->GetBinError(1));
  weight_hEff_vs_Cent_pPt_8_20->SetBinContent(5,weight_test_8_20_num_C5->GetBinContent(1));
  weight_hEff_vs_Cent_pPt_8_20->SetBinError(5,weight_test_8_20_num_C5->GetBinError(1));
  weight_hEff_vs_Cent_pPt_8_20->SetBinContent(6,weight_test_8_20_num_C6->GetBinContent(1));
  weight_hEff_vs_Cent_pPt_8_20->SetBinError(6,weight_test_8_20_num_C6->GetBinError(1));
  weight_hEff_vs_Cent_pPt_8_20->SetBinContent(7,weight_test_8_20_num_C7->GetBinContent(1));
  weight_hEff_vs_Cent_pPt_8_20->SetBinError(7,weight_test_8_20_num_C7->GetBinError(1));
  weight_hEff_vs_Cent_pPt_8_20->SetBinContent(8,weight_test_8_20_num_C8->GetBinContent(1));
  weight_hEff_vs_Cent_pPt_8_20->SetBinError(8,weight_test_8_20_num_C8->GetBinError(1));
  weight_hEff_vs_Cent_pPt_8_20->SetBinContent(9,weight_test_8_20_num_C9->GetBinContent(1));
  weight_hEff_vs_Cent_pPt_8_20->SetBinError(9,weight_test_8_20_num_C9->GetBinError(1));
  weight_hEff_vs_Cent_pPt_8_20->SetBinContent(10,weight_test_8_20_num_C10->GetBinContent(1));
  weight_hEff_vs_Cent_pPt_8_20->SetBinError(10,weight_test_8_20_num_C10->GetBinError(1));

  weight_hEff_vs_Cent_pPt_20_Inf->SetBinContent(1,weight_test_20_Inf_num_C1->GetBinContent(1));
  weight_hEff_vs_Cent_pPt_20_Inf->SetBinError(1,weight_test_20_Inf_num_C1->GetBinError(1));
  weight_hEff_vs_Cent_pPt_20_Inf->SetBinContent(2,weight_test_20_Inf_num_C2->GetBinContent(1));
  weight_hEff_vs_Cent_pPt_20_Inf->SetBinError(2,weight_test_20_Inf_num_C2->GetBinError(1));
  weight_hEff_vs_Cent_pPt_20_Inf->SetBinContent(3,weight_test_20_Inf_num_C3->GetBinContent(1));
  weight_hEff_vs_Cent_pPt_20_Inf->SetBinError(3,weight_test_20_Inf_num_C3->GetBinError(1));
  weight_hEff_vs_Cent_pPt_20_Inf->SetBinContent(4,weight_test_20_Inf_num_C4->GetBinContent(1));
  weight_hEff_vs_Cent_pPt_20_Inf->SetBinError(4,weight_test_20_Inf_num_C4->GetBinError(1));
  weight_hEff_vs_Cent_pPt_20_Inf->SetBinContent(5,weight_test_20_Inf_num_C5->GetBinContent(1));
  weight_hEff_vs_Cent_pPt_20_Inf->SetBinError(5,weight_test_20_Inf_num_C5->GetBinError(1));
  weight_hEff_vs_Cent_pPt_20_Inf->SetBinContent(6,weight_test_20_Inf_num_C6->GetBinContent(1));
  weight_hEff_vs_Cent_pPt_20_Inf->SetBinError(6,weight_test_20_Inf_num_C6->GetBinError(1));
  weight_hEff_vs_Cent_pPt_20_Inf->SetBinContent(7,weight_test_20_Inf_num_C7->GetBinContent(1));
  weight_hEff_vs_Cent_pPt_20_Inf->SetBinError(7,weight_test_20_Inf_num_C7->GetBinError(1));
  weight_hEff_vs_Cent_pPt_20_Inf->SetBinContent(8,weight_test_20_Inf_num_C8->GetBinContent(1));
  weight_hEff_vs_Cent_pPt_20_Inf->SetBinError(8,weight_test_20_Inf_num_C8->GetBinError(1));
  weight_hEff_vs_Cent_pPt_20_Inf->SetBinContent(9,weight_test_20_Inf_num_C9->GetBinContent(1));
  weight_hEff_vs_Cent_pPt_20_Inf->SetBinError(9,weight_test_20_Inf_num_C9->GetBinError(1));
  weight_hEff_vs_Cent_pPt_20_Inf->SetBinContent(10,weight_test_20_Inf_num_C10->GetBinContent(1));
  weight_hEff_vs_Cent_pPt_20_Inf->SetBinError(10,weight_test_20_Inf_num_C10->GetBinError(1));


/////////////////
//
// PLOTTING
//
/////////////////

  TCanvas *c1 = new TCanvas("c1","c1");
  c1->cd();

  hEff_vs_Cent_pPt_05->GetXaxis()->SetTitle("Centrality bin");
  hEff_vs_Cent_pPt_05->GetYaxis()->SetTitle("Tracking efficiency");
  hEff_vs_Cent_pPt_05->GetYaxis()->SetTitleOffset(1.3);
  gStyle->SetPadLeftMargin(0.19);
  hEff_vs_Cent_pPt_05->SetMarkerStyle(20);
  hEff_vs_Cent_pPt_05->Draw();

  hEff_vs_Cent_pPt_14_18->SetMarkerStyle(20);
  hEff_vs_Cent_pPt_14_18->SetMarkerColor(46);
  hEff_vs_Cent_pPt_14_18->SetLineColor(46);
  hEff_vs_Cent_pPt_14_18->Draw("same");

  hEff_vs_Cent_pPt_18_3->SetMarkerStyle(20);
  hEff_vs_Cent_pPt_18_3->SetMarkerColor(4);
  hEff_vs_Cent_pPt_18_3->SetLineColor(4);
  hEff_vs_Cent_pPt_18_3->Draw("same");

  hEff_vs_Cent_pPt_3_8->SetMarkerStyle(20);
  hEff_vs_Cent_pPt_3_8->SetMarkerColor(6);
  hEff_vs_Cent_pPt_3_8->SetLineColor(6);
  hEff_vs_Cent_pPt_3_8->Draw("same");

  hEff_vs_Cent_pPt_8_20->SetMarkerStyle(20);
  hEff_vs_Cent_pPt_8_20->SetMarkerColor(2);
  hEff_vs_Cent_pPt_8_20->SetLineColor(2);
  hEff_vs_Cent_pPt_8_20->Draw("same");

  hEff_vs_Cent_pPt_20_Inf->SetMarkerStyle(20);
  hEff_vs_Cent_pPt_20_Inf->SetMarkerColor(3);
  hEff_vs_Cent_pPt_20_Inf->SetLineColor(3);
  hEff_vs_Cent_pPt_20_Inf->Draw("same");

  TLegend *leg1 = new TLegend(0.20,0.65,0.92,0.90,NULL,"brNDC");
  leg1->AddEntry(hEff_vs_Cent_pPt_05,"0.6<p_{T}<1.4 GeV/c","p");
  leg1->AddEntry(hEff_vs_Cent_pPt_14_18,"1.4<p_{T}<1.8 GeV/c","p");
  leg1->AddEntry(hEff_vs_Cent_pPt_18_3,"1.8<p_{T}<3. GeV/c","p");
  leg1->AddEntry(hEff_vs_Cent_pPt_3_8,"3<p_{T}<8 GeV/c","p");
  leg1->AddEntry(hEff_vs_Cent_pPt_8_20,"8<p_{T}<20 GeV/c","p");
  leg1->AddEntry(hEff_vs_Cent_pPt_20_Inf,"20<p_{T} GeV/c","p");
  leg1->SetFillStyle(0);
  leg1->SetFillColor(0);
  leg1->SetBorderSize(0);
  leg1->Draw();


  TCanvas *c2 = new TCanvas("c2","c2");
  c2->cd();

  weight_hEff_vs_Cent_pPt_05_14->SetMaximum(1.2);
  weight_hEff_vs_Cent_pPt_05_14->SetMinimum(0.9);
  weight_hEff_vs_Cent_pPt_05_14->GetXaxis()->SetTitle("Centrality bin");
  weight_hEff_vs_Cent_pPt_05_14->GetYaxis()->SetTitle("A.u.");
  weight_hEff_vs_Cent_pPt_05_14->SetMarkerStyle(25);
  weight_hEff_vs_Cent_pPt_05_14->GetYaxis()->SetTitleOffset(1.3);
  gStyle->SetPadLeftMargin(0.19);
  weight_hEff_vs_Cent_pPt_05_14->Draw();

  weight_hEff_vs_Cent_pPt_14_18->SetMarkerStyle(25);
  weight_hEff_vs_Cent_pPt_14_18->SetMarkerColor(46);
  weight_hEff_vs_Cent_pPt_14_18->SetLineColor(46);
  weight_hEff_vs_Cent_pPt_14_18->Draw("same");

  weight_hEff_vs_Cent_pPt_18_3->SetMarkerStyle(25);
  weight_hEff_vs_Cent_pPt_18_3->SetMarkerColor(4);
  weight_hEff_vs_Cent_pPt_18_3->SetLineColor(4);
  weight_hEff_vs_Cent_pPt_18_3->Draw("same");

  weight_hEff_vs_Cent_pPt_3_8->SetMarkerStyle(25);
  weight_hEff_vs_Cent_pPt_3_8->SetMarkerColor(6);
  weight_hEff_vs_Cent_pPt_3_8->SetLineColor(6);
  weight_hEff_vs_Cent_pPt_3_8->Draw("same");

  weight_hEff_vs_Cent_pPt_8_20->SetMarkerStyle(25);
  weight_hEff_vs_Cent_pPt_8_20->SetMarkerColor(2);
  weight_hEff_vs_Cent_pPt_8_20->SetLineColor(2);
  weight_hEff_vs_Cent_pPt_8_20->Draw("same");

  weight_hEff_vs_Cent_pPt_20_Inf->SetMarkerStyle(25);
  weight_hEff_vs_Cent_pPt_20_Inf->SetMarkerColor(3);
  weight_hEff_vs_Cent_pPt_20_Inf->SetLineColor(3);
  weight_hEff_vs_Cent_pPt_20_Inf->Draw("same");

  TLegend *leg2 = new TLegend(0.20,0.65,0.92,0.90,NULL,"brNDC");
  leg2->AddEntry(weight_hEff_vs_Cent_pPt_05_14,"0.6<p_{T}<1.4 GeV/c, acceptance weighted","p");
  leg2->AddEntry(weight_hEff_vs_Cent_pPt_14_18,"1.4<p_{T}<1.8 GeV/c, acceptance weighted","p");
  leg2->AddEntry(weight_hEff_vs_Cent_pPt_18_3,"1.8<p_{T}<3. GeV/c, acceptance weighted","p");
  leg2->AddEntry(weight_hEff_vs_Cent_pPt_3_8,"3<p_{T}<8 GeV/c, acceptance weighted","p");
  leg2->AddEntry(weight_hEff_vs_Cent_pPt_8_20,"8<p_{T}<20 GeV/c, acceptance weighted","p");
  leg2->AddEntry(weight_hEff_vs_Cent_pPt_20_Inf,"20<p_{T} GeV/c, acceptance weighted","p");
  leg2->SetFillStyle(0);
  leg2->SetFillColor(0);
  leg2->SetBorderSize(0);
  leg2->Draw();

//Fit centrality distribution for 
  TF1 *fFitCent_05_14 = new TF1("fFitCent_05_14","[0]+[1]*x+[2]*x**2+[3]*x**3+[4]*x**4",0,40);
  TF1 *fFitCent_14_18 = new TF1("fFitCent_14_18","[0]+[1]*x+[2]*x**2+[3]*x**3+[4]*x**4",0,40);
  TF1 *fFitCent_18_3 = new TF1("fFitCent_18_3","[0]+[1]*x+[2]*x**2+[3]*x**3+[4]*x**4",0,40);
  TF1 *fFitCent_3_8 = new TF1("fFitCent_3_8","[0]+[1]*x+[2]*x**2+[3]*x**3+[4]*x**4",0,40);
  TF1 *fFitCent_8_20 = new TF1("fFitCent_8_20","[0]+[1]*x+[2]*x**2+[3]*x**3+[4]*x**4",0,40);
  TF1 *fFitCent_20_Inf = new TF1("fFitCent_20_Inf","[0]+[1]*x+[2]*x**2+[3]*x**3+[4]*x**4",0,40);
  weight_hEff_vs_Cent_pPt_05_14->Fit("fFitCent_05_14","0");
  weight_hEff_vs_Cent_pPt_14_18->Fit("fFitCent_14_18","0");
  weight_hEff_vs_Cent_pPt_18_3->Fit("fFitCent_18_3","0");
  weight_hEff_vs_Cent_pPt_3_8->Fit("fFitCent_3_8","0");
  weight_hEff_vs_Cent_pPt_8_20->Fit("fFitCent_8_20","0");
  weight_hEff_vs_Cent_pPt_20_Inf->Fit("fFitCent_20_Inf","0");
  double par0_05_14 = fFitCent_05_14->GetParameter(0);
  double par0_14_18 = fFitCent_14_18->GetParameter(0);
  double par0_18_3 = fFitCent_18_3->GetParameter(0);
  double par0_3_8 = fFitCent_3_8->GetParameter(0);
  double par0_8_20 = fFitCent_8_20->GetParameter(0);
  double par0_20_Inf = fFitCent_20_Inf->GetParameter(0);
  fFitCent_05_14->SetLineColor(1);
  fFitCent_05_14->Draw("same");
  fFitCent_14_18->SetLineColor(46);
  fFitCent_14_18->Draw("same");
  fFitCent_18_3->SetLineColor(4);
  fFitCent_18_3->Draw("same");
  fFitCent_3_8->SetLineColor(6);
  fFitCent_3_8->Draw("same");
  fFitCent_8_20->SetLineColor(2);
  fFitCent_8_20->Draw("same");
  fFitCent_20_Inf->SetLineColor(3);
  fFitCent_20_Inf->Draw("same");

  //trick:
  par0_05_14 = 1.;
  par0_14_18 = 1.;
  par0_18_3 = 1.;
  par0_3_8 = 1.;
  par0_8_20 = 1.;
  par0_20_Inf = 1.;

  TCanvas *c3 = new TCanvas("c3","c3");
  c3->cd();

  TH1D* weight_hEff_vs_Cent_pPt_05_14_clone = (TH1D*) weight_hEff_vs_Cent_pPt_05_14->Clone("weight_hEff_vs_Cent_pPt_05_14_clone");
  TH1D* weight_hEff_vs_Cent_pPt_14_18_clone = (TH1D*) weight_hEff_vs_Cent_pPt_14_18->Clone("weight_hEff_vs_Cent_pPt_14_18_clone");
  TH1D* weight_hEff_vs_Cent_pPt_18_3_clone = (TH1D*) weight_hEff_vs_Cent_pPt_18_3->Clone("weight_hEff_vs_Cent_pPt_18_3_clone");
  TH1D* weight_hEff_vs_Cent_pPt_3_8_clone = (TH1D*) weight_hEff_vs_Cent_pPt_3_8->Clone("weight_hEff_vs_Cent_pPt_3_8_clone");
  TH1D* weight_hEff_vs_Cent_pPt_8_20_clone = (TH1D*) weight_hEff_vs_Cent_pPt_8_20->Clone("weight_hEff_vs_Cent_pPt_8_20_clone");
  TH1D* weight_hEff_vs_Cent_pPt_20_Inf_clone = (TH1D*) weight_hEff_vs_Cent_pPt_20_Inf->Clone("weight_hEff_vs_Cent_pPt_20_Inf_clone");
  weight_hEff_vs_Cent_pPt_05_14_clone->Reset();
  weight_hEff_vs_Cent_pPt_14_18_clone->Reset();
  weight_hEff_vs_Cent_pPt_18_3_clone->Reset();
  weight_hEff_vs_Cent_pPt_3_8_clone->Reset();
  weight_hEff_vs_Cent_pPt_8_20_clone->Reset();
  weight_hEff_vs_Cent_pPt_20_Inf_clone->Reset();
  //centrality weighting
  for(int i = 1; i<=weight_hEff_vs_Cent_pPt_05_14_clone->GetNbinsX(); i++) {
     float where = weight_hEff_vs_Cent_pPt_05_14_clone->GetBinCenter(i);
     float centWeight_14_18 = fFitCent_14_18->Eval(where);
     float centWeight_05_14 = fFitCent_05_14->Eval(where);
     float centWeight_18_3 = fFitCent_18_3->Eval(where);
     float centWeight_3_8 = fFitCent_3_8->Eval(where);
     float centWeight_8_20 = fFitCent_8_20->Eval(where);
     float centWeight_20_Inf = fFitCent_20_Inf->Eval(where);

     weight_hEff_vs_Cent_pPt_05_14_clone->SetBinContent(i,par0_05_14*weight_hEff_vs_Cent_pPt_05_14->GetBinContent(i)/centWeight_05_14);
     weight_hEff_vs_Cent_pPt_05_14_clone->SetBinError(i,par0_05_14*weight_hEff_vs_Cent_pPt_05_14->GetBinError(i)/centWeight_05_14);
     weight_hEff_vs_Cent_pPt_14_18_clone->SetBinContent(i,par0_14_18*weight_hEff_vs_Cent_pPt_14_18->GetBinContent(i)/centWeight_14_18);
     weight_hEff_vs_Cent_pPt_14_18_clone->SetBinError(i,par0_14_18*weight_hEff_vs_Cent_pPt_14_18->GetBinError(i)/centWeight_14_18);
     weight_hEff_vs_Cent_pPt_18_3_clone->SetBinContent(i,par0_18_3*weight_hEff_vs_Cent_pPt_18_3->GetBinContent(i)/centWeight_18_3);
     weight_hEff_vs_Cent_pPt_18_3_clone->SetBinError(i,par0_18_3*weight_hEff_vs_Cent_pPt_18_3->GetBinError(i)/centWeight_18_3);
     weight_hEff_vs_Cent_pPt_3_8_clone->SetBinContent(i,par0_18_3*weight_hEff_vs_Cent_pPt_3_8->GetBinContent(i)/centWeight_3_8);
     weight_hEff_vs_Cent_pPt_3_8_clone->SetBinError(i,par0_18_3*weight_hEff_vs_Cent_pPt_3_8->GetBinError(i)/centWeight_3_8);
     weight_hEff_vs_Cent_pPt_8_20_clone->SetBinContent(i,par0_18_3*weight_hEff_vs_Cent_pPt_8_20->GetBinContent(i)/centWeight_8_20);
     weight_hEff_vs_Cent_pPt_8_20_clone->SetBinError(i,par0_18_3*weight_hEff_vs_Cent_pPt_8_20->GetBinError(i)/centWeight_8_20);
     weight_hEff_vs_Cent_pPt_20_Inf_clone->SetBinContent(i,par0_18_3*weight_hEff_vs_Cent_pPt_20_Inf->GetBinContent(i)/centWeight_20_Inf);
     weight_hEff_vs_Cent_pPt_20_Inf_clone->SetBinError(i,par0_18_3*weight_hEff_vs_Cent_pPt_20_Inf->GetBinError(i)/centWeight_20_Inf);
  }

  weight_hEff_vs_Cent_pPt_05_14_clone->SetMaximum(1.1);
  weight_hEff_vs_Cent_pPt_05_14_clone->SetMinimum(0.8);
  weight_hEff_vs_Cent_pPt_05_14_clone->Draw();
  weight_hEff_vs_Cent_pPt_14_18_clone->Draw("same");
  weight_hEff_vs_Cent_pPt_18_3_clone->Draw("same");
  weight_hEff_vs_Cent_pPt_3_8_clone->Draw("same");
  weight_hEff_vs_Cent_pPt_8_20_clone->Draw("same");
  weight_hEff_vs_Cent_pPt_20_Inf_clone->Draw("same");

  TLegend *leg3 = new TLegend(0.20,0.65,0.92,0.90,NULL,"brNDC");
  leg3->AddEntry(weight_hEff_vs_Cent_pPt_05_14,"0.6<p_{T}<1.4 GeV/c, acceptance+centrality weighted","p");
  leg3->AddEntry(weight_hEff_vs_Cent_pPt_14_18,"1.4<p_{T}<1.8 GeV/c, acceptance+centrality weighted","p");
  leg3->AddEntry(weight_hEff_vs_Cent_pPt_18_3,"1.8<p_{T}<3. GeV/c, acceptance+centrality weighted","p");
  leg3->AddEntry(weight_hEff_vs_Cent_pPt_3_8,"3<p_{T}<8 GeV/c, acceptance+centrality weighted","p");
  leg3->AddEntry(weight_hEff_vs_Cent_pPt_8_20,"8<p_{T}<20 GeV/c, acceptance+centrality weighted","p");
  leg3->AddEntry(weight_hEff_vs_Cent_pPt_20_Inf,"20<p_{T} GeV/c, acceptance+centrality weighted","p");
  leg3->SetFillStyle(0);
  leg3->SetFillColor(0);
  leg3->SetBorderSize(0);
  leg3->Draw();


  //write out stuff
  TFile * outf;
  if(save) {
     outf = new TFile("CentralityWeights.root", "recreate");

     outf->cd();
     fFitCent_05_14->Write();
     fFitCent_14_18->Write();
     fFitCent_18_3->Write();
     fFitCent_3_8->Write();
     fFitCent_8_20->Write();
     fFitCent_20_Inf->Write();
     outf->Close();
  }
}


