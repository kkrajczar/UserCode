#include "TFile.h"
#include "TH1.h"
#include "TH2.h"
#include "TH3.h"
#include "TProfile.h"
#include "TLatex.h"
#include "TLegend.h"
#include "TROOT.h"
#include "TStyle.h"
#include "TTree.h"
#include "TCanvas.h"
#include "TMath.h"
#include <iostream>

using namespace std;

void ComputeAcceptanceWeight(bool save=false, bool plot=true) {

  gROOT->Reset();
  gROOT->ProcessLine(".x rootlogonChristof.C");
  gROOT->ForceStyle();
  gStyle->SetPalette(1);
//  gStyle->SetPadLeftMargin(0.19);
//  gStyle->SetPadRightMargin(0.19);

  TFile *f = TFile::Open("TrkCorr_3DHistos_pThat80_Inclusive.root");

  TH3D *hSim3D = (TH3D*)f->Get("hSim3D");
  TH3D *hEff3D = (TH3D*)f->Get("hEff3D");

  TH2D *hSim3D_eta_phi = hSim3D->Project3D("zx");
  TH2D *hEff3D_eta_phi = hEff3D->Project3D("zx");

  //Find pT bins:
  Int_t bin_pT_06 = hSim3D->GetYaxis()->FindBin(0.6);
  Int_t bin_pT_05 = hSim3D->GetYaxis()->FindBin(0.5);
  Int_t bin_pT_14 = hSim3D->GetYaxis()->FindBin(1.4);
  Int_t bin_pT_16 = hSim3D->GetYaxis()->FindBin(1.6);
  Int_t bin_pT_17 = hSim3D->GetYaxis()->FindBin(1.7);
  Int_t bin_pT_15 = hSim3D->GetYaxis()->FindBin(1.5);
  Int_t bin_pT_18 = hSim3D->GetYaxis()->FindBin(1.8);
  Int_t bin_pT_2 = hSim3D->GetYaxis()->FindBin(2.);
  Int_t bin_pT_3 = hSim3D->GetYaxis()->FindBin(3.);
  Int_t bin_pT_8 = hSim3D->GetYaxis()->FindBin(8.);
  Int_t bin_pT_20 = hSim3D->GetYaxis()->FindBin(20.);

  TH3D *hSim3D_clone_v0 = (TH3D*)hSim3D->Clone("hSim3D_clone_v0");
  TH3D *hEff3D_clone_v0 = (TH3D*)hEff3D->Clone("hEff3D_clone_v0");
  hSim3D_clone_v0->GetYaxis()->SetRange(bin_pT_06,bin_pT_14);
  hEff3D_clone_v0->GetYaxis()->SetRange(bin_pT_06,bin_pT_14);
  TH2D *hSim3D_eta_phi_pT_06_14 = hSim3D_clone_v0->Project3D("zx");
  TH2D *hEff3D_eta_phi_pT_06_14 = hEff3D_clone_v0->Project3D("zx");

  TH3D *hSim3D_clone_v1a = (TH3D*)hSim3D->Clone("hSim3D_clone_v1a");
  TH3D *hEff3D_clone_v1a = (TH3D*)hEff3D->Clone("hEff3D_clone_v1a");
  hSim3D_clone_v1a->GetYaxis()->SetRange(bin_pT_14,bin_pT_16);
  hEff3D_clone_v1a->GetYaxis()->SetRange(bin_pT_14,bin_pT_16);
  TH2D *hSim3D_eta_phi_pT_14_16 = hSim3D_clone_v1a->Project3D("zx");
  TH2D *hEff3D_eta_phi_pT_14_16 = hEff3D_clone_v1a->Project3D("zx");

  TH3D *hSim3D_clone_v1 = (TH3D*)hSim3D->Clone("hSim3D_clone_v1");
  TH3D *hEff3D_clone_v1 = (TH3D*)hEff3D->Clone("hEff3D_clone_v1");
  hSim3D_clone_v1->GetYaxis()->SetRange(bin_pT_16,bin_pT_18);
  hEff3D_clone_v1->GetYaxis()->SetRange(bin_pT_16,bin_pT_18);
  TH2D *hSim3D_eta_phi_pT_16_18 = hSim3D_clone_v1->Project3D("zx");
  TH2D *hEff3D_eta_phi_pT_16_18 = hEff3D_clone_v1->Project3D("zx");

  TH3D *hSim3D_clone_v1OLD = (TH3D*)hSim3D->Clone("hSim3D_clone_v1OLD");
  TH3D *hEff3D_clone_v1OLD = (TH3D*)hEff3D->Clone("hEff3D_clone_v1OLD");
  hSim3D_clone_v1OLD->GetYaxis()->SetRange(bin_pT_14,bin_pT_18);
  hEff3D_clone_v1OLD->GetYaxis()->SetRange(bin_pT_14,bin_pT_18);
  TH2D *hSim3D_eta_phi_pT_14_18 = hSim3D_clone_v1OLD->Project3D("zx");
  TH2D *hEff3D_eta_phi_pT_14_18 = hEff3D_clone_v1OLD->Project3D("zx");

  TH3D *hSim3D_clone_v2 = (TH3D*)hSim3D->Clone("hSim3D_clone_v2");
  TH3D *hEff3D_clone_v2 = (TH3D*)hEff3D->Clone("hEff3D_clone_v2");
  hSim3D_clone_v2->GetYaxis()->SetRange(bin_pT_18,bin_pT_3);
  hEff3D_clone_v2->GetYaxis()->SetRange(bin_pT_18,bin_pT_3);
  TH2D *hSim3D_eta_phi_pT_18_3 = hSim3D_clone_v2->Project3D("zx");
  TH2D *hEff3D_eta_phi_pT_18_3 = hEff3D_clone_v2->Project3D("zx");

  TH3D *hSim3D_clone_v3 = (TH3D*)hSim3D->Clone("hSim3D_clone_v3");
  TH3D *hEff3D_clone_v3 = (TH3D*)hEff3D->Clone("hEff3D_clone_v3");
  hSim3D_clone_v3->GetYaxis()->SetRange(bin_pT_3,bin_pT_8);
  hEff3D_clone_v3->GetYaxis()->SetRange(bin_pT_3,bin_pT_8);
  TH2D *hSim3D_eta_phi_pT_3_8 = hSim3D_clone_v3->Project3D("zx");
  TH2D *hEff3D_eta_phi_pT_3_8 = hEff3D_clone_v3->Project3D("zx");

  TH3D *hSim3D_clone_v4 = (TH3D*)hSim3D->Clone("hSim3D_clone_v4");
  TH3D *hEff3D_clone_v4 = (TH3D*)hEff3D->Clone("hEff3D_clone_v4");
  hSim3D_clone_v4->GetYaxis()->SetRange(bin_pT_8,bin_pT_20);
  hEff3D_clone_v4->GetYaxis()->SetRange(bin_pT_8,bin_pT_20);
  TH2D *hSim3D_eta_phi_pT_8_20 = hSim3D_clone_v4->Project3D("zx");
  TH2D *hEff3D_eta_phi_pT_8_20 = hEff3D_clone_v4->Project3D("zx");
  
  TH3D *hSim3D_clone_v5 = (TH3D*)hSim3D->Clone("hSim3D_clone_v5");
  TH3D *hEff3D_clone_v5 = (TH3D*)hEff3D->Clone("hEff3D_clone_v5");
  hSim3D_clone_v5->GetYaxis()->SetRange(bin_pT_20,hSim3D_clone_v5->GetNbinsY());
  hEff3D_clone_v5->GetYaxis()->SetRange(bin_pT_20,hSim3D_clone_v5->GetNbinsY());
  TH2D *hSim3D_eta_phi_pT_20_Inf = hSim3D_clone_v5->Project3D("zx");
  TH2D *hEff3D_eta_phi_pT_20_Inf = hEff3D_clone_v5->Project3D("zx");


  //plot the distributions and compute ratios
  if(plot) {
     TCanvas *c1 = new TCanvas("c1","c1");
     c1->cd();

     hSim3D_eta_phi->SetLineColor(2);
     hSim3D_eta_phi->GetXaxis()->CenterTitle();
     hSim3D_eta_phi->GetYaxis()->CenterTitle();
     hSim3D_eta_phi->GetXaxis()->SetTitleOffset(1.03);
     hSim3D_eta_phi->GetYaxis()->SetTitleOffset(1.3);
     hSim3D_eta_phi->GetXaxis()->SetTitle("#eta");
     hSim3D_eta_phi->GetYaxis()->SetTitle("#phi");
     hSim3D_eta_phi->Draw("surf");

     hEff3D_eta_phi->SetLineColor(1);
     hEff3D_eta_phi->Draw("surfsame");


     TCanvas *c2 = new TCanvas("c2","c2");
     c2->SetTitle("Inclusive p_{T}");
     c2->cd();

     TH2F *hSim3D_eta_phi_clone = hSim3D_eta_phi->Clone("hSim3D_eta_phi_clone");
     TH2F *hEff3D_eta_phi_clone = hEff3D_eta_phi->Clone("hEff3D_eta_phi_clone");
     hSim3D_eta_phi_clone->Divide(hEff3D_eta_phi_clone);
     hSim3D_eta_phi_clone->GetZaxis()->SetRangeUser(0.,35.);
     hSim3D_eta_phi_clone->Draw("surf");


     TCanvas *c3 = new TCanvas("c3","c3");
     c3->SetTitle("0.6<p_{T}<1.4 GeV/c");
     c3->cd();

     TH2F *hSim3D_eta_phi_pT_06_14_clone = hSim3D_eta_phi_pT_06_14->Clone("hSim3D_eta_phi_pT_06_14_clone");
     TH2F *hEff3D_eta_phi_pT_06_14_clone = hEff3D_eta_phi_pT_06_14->Clone("hEff3D_eta_phi_pT_06_14_clone");
     hSim3D_eta_phi_pT_06_14_clone->Divide(hEff3D_eta_phi_pT_06_14_clone);
     hSim3D_eta_phi_pT_06_14_clone->SetLineColor(2);
     hSim3D_eta_phi_pT_06_14_clone->GetXaxis()->SetTitle("#eta");
     hSim3D_eta_phi_pT_06_14_clone->GetYaxis()->SetTitle("#phi");
     hSim3D_eta_phi_pT_06_14_clone->GetZaxis()->SetRangeUser(0.,35.);
     hSim3D_eta_phi_pT_06_14_clone->Draw("surf");

     TCanvas *c4 = new TCanvas("c4","c4");
     c4->SetTitle("1.6<p_{T}<1.8 GeV/c");
     c4->cd();

     TH2F *hSim3D_eta_phi_pT_16_18_clone = hSim3D_eta_phi_pT_16_18->Clone("hSim3D_eta_phi_pT_16_18_clone");
     TH2F *hEff3D_eta_phi_pT_16_18_clone = hEff3D_eta_phi_pT_16_18->Clone("hEff3D_eta_phi_pT_16_18_clone");
     hSim3D_eta_phi_pT_16_18_clone->Divide(hEff3D_eta_phi_pT_16_18_clone);
     hSim3D_eta_phi_pT_16_18_clone->SetLineColor(2);
     hSim3D_eta_phi_pT_16_18_clone->GetXaxis()->SetTitle("#eta");
     hSim3D_eta_phi_pT_16_18_clone->GetYaxis()->SetTitle("#phi");
     hSim3D_eta_phi_pT_16_18_clone->GetZaxis()->SetRangeUser(0.,35.);
     hSim3D_eta_phi_pT_16_18_clone->Draw("surf");


     TCanvas *c5 = new TCanvas("c5","c5");
     c5->SetTitle("1.8<p_{T}<3 GeV/c");
     c5->cd();

     TH2F *hSim3D_eta_phi_pT_18_3_clone = hSim3D_eta_phi_pT_18_3->Clone("hSim3D_eta_phi_pT_18_3_clone");
     TH2F *hEff3D_eta_phi_pT_18_3_clone = hEff3D_eta_phi_pT_18_3->Clone("hEff3D_eta_phi_pT_18_3_clone");
     hSim3D_eta_phi_pT_18_3_clone->Divide(hEff3D_eta_phi_pT_18_3_clone);
     hSim3D_eta_phi_pT_18_3_clone->SetLineColor(2);
     hSim3D_eta_phi_pT_18_3_clone->GetXaxis()->SetTitle("#eta");
     hSim3D_eta_phi_pT_18_3_clone->GetYaxis()->SetTitle("#phi");
     hSim3D_eta_phi_pT_18_3_clone->GetZaxis()->SetRangeUser(0.,35.);
     hSim3D_eta_phi_pT_18_3_clone->Draw("surf");


     TCanvas *c6 = new TCanvas("c6","c6");
     c6->SetTitle("3<p_{T}<8 GeV/c");
     c6->cd();

     TH2F *hSim3D_eta_phi_pT_3_8_clone = hSim3D_eta_phi_pT_3_8->Clone("hSim3D_eta_phi_pT_3_8_clone");
     TH2F *hEff3D_eta_phi_pT_3_8_clone = hEff3D_eta_phi_pT_3_8->Clone("hEff3D_eta_phi_pT_3_8_clone");
     hSim3D_eta_phi_pT_3_8_clone->Divide(hEff3D_eta_phi_pT_3_8_clone);
     hSim3D_eta_phi_pT_3_8_clone->SetLineColor(2);
     hSim3D_eta_phi_pT_3_8_clone->GetXaxis()->SetTitle("#eta");
     hSim3D_eta_phi_pT_3_8_clone->GetYaxis()->SetTitle("#phi");
     hSim3D_eta_phi_pT_3_8_clone->GetZaxis()->SetRangeUser(0.,35.);
     hSim3D_eta_phi_pT_3_8_clone->Draw("surf");


     TCanvas *c7 = new TCanvas("c7","c7");
     c7->SetTitle("8<p_{T}<20 GeV/c");
     c7->cd();

     TH2F *hSim3D_eta_phi_pT_8_20_clone = hSim3D_eta_phi_pT_8_20->Clone("hSim3D_eta_phi_pT_8_20_clone");
     TH2F *hEff3D_eta_phi_pT_8_20_clone = hEff3D_eta_phi_pT_8_20->Clone("hEff3D_eta_phi_pT_8_20_clone");
     hSim3D_eta_phi_pT_8_20_clone->Divide(hEff3D_eta_phi_pT_8_20_clone);
     hSim3D_eta_phi_pT_8_20_clone->SetLineColor(2);
     hSim3D_eta_phi_pT_8_20_clone->GetXaxis()->SetTitle("#eta");
     hSim3D_eta_phi_pT_8_20_clone->GetYaxis()->SetTitle("#phi");
     hSim3D_eta_phi_pT_8_20_clone->GetZaxis()->SetRangeUser(0.,35.);
     hSim3D_eta_phi_pT_8_20_clone->Draw("surf");


     TCanvas *c8 = new TCanvas("c8","c8");
     c8->SetTitle("20<p_{T} GeV/c");
     c8->cd();

     TH2F *hSim3D_eta_phi_pT_20_Inf_clone = hSim3D_eta_phi_pT_20_Inf->Clone("hSim3D_eta_phi_pT_20_Inf_clone");
     TH2F *hEff3D_eta_phi_pT_20_Inf_clone = hEff3D_eta_phi_pT_20_Inf->Clone("hEff3D_eta_phi_pT_20_Inf_clone");
     hSim3D_eta_phi_pT_20_Inf_clone->Divide(hEff3D_eta_phi_pT_20_Inf_clone);
     hSim3D_eta_phi_pT_20_Inf_clone->SetLineColor(2);
     hSim3D_eta_phi_pT_20_Inf_clone->GetXaxis()->SetTitle("#eta");
     hSim3D_eta_phi_pT_20_Inf_clone->GetYaxis()->SetTitle("#phi");
     hSim3D_eta_phi_pT_20_Inf_clone->GetZaxis()->SetRangeUser(0.,35.);
     hSim3D_eta_phi_pT_20_Inf_clone->Draw("surf");


     TCanvas *c9 = new TCanvas("c9","c9");
     c9->SetTitle("1.4<p_{T}<1.6 GeV/c");
     c9->cd();

     TH2F *hSim3D_eta_phi_pT_14_16_clone = hSim3D_eta_phi_pT_14_16->Clone("hSim3D_eta_phi_pT_14_16_clone");
     TH2F *hEff3D_eta_phi_pT_14_16_clone = hEff3D_eta_phi_pT_14_16->Clone("hEff3D_eta_phi_pT_14_16_clone");
     hSim3D_eta_phi_pT_14_16_clone->Divide(hEff3D_eta_phi_pT_14_16_clone);
     hSim3D_eta_phi_pT_14_16_clone->SetLineColor(2);
     hSim3D_eta_phi_pT_14_16_clone->GetXaxis()->SetTitle("#eta");
     hSim3D_eta_phi_pT_14_16_clone->GetYaxis()->SetTitle("#phi");
     hSim3D_eta_phi_pT_14_16_clone->GetZaxis()->SetRangeUser(0.,35.);
     hSim3D_eta_phi_pT_14_16_clone->Draw("surf");

     TCanvas *c10 = new TCanvas("c10","c10");
     c10->SetTitle("1.4<p_{T}<1.8 GeV/c");
     c10->cd();

     TH2F *hSim3D_eta_phi_pT_14_18_clone = hSim3D_eta_phi_pT_14_18->Clone("hSim3D_eta_phi_pT_14_18_clone");
     TH2F *hEff3D_eta_phi_pT_14_18_clone = hEff3D_eta_phi_pT_14_18->Clone("hEff3D_eta_phi_pT_14_18_clone");
     hSim3D_eta_phi_pT_14_18_clone->Divide(hEff3D_eta_phi_pT_14_18_clone);
     hSim3D_eta_phi_pT_14_18_clone->SetLineColor(2);
     hSim3D_eta_phi_pT_14_18_clone->GetXaxis()->SetTitle("#eta");
     hSim3D_eta_phi_pT_14_18_clone->GetYaxis()->SetTitle("#phi");
     hSim3D_eta_phi_pT_14_18_clone->GetZaxis()->SetRangeUser(0.,35.);
     hSim3D_eta_phi_pT_14_18_clone->Draw("surf");
  }
 
  //save the output
  if(save) {
     //save weights in histograms
     TFile* outf = new TFile("AcceptanceWeights.root", "recreate");

     outf->cd();
     hSim3D_eta_phi_clone->Write();
     hSim3D_eta_phi_pT_06_14_clone->Write();
     hSim3D_eta_phi_pT_14_16_clone->Write();
     hSim3D_eta_phi_pT_16_18_clone->Write();
     hSim3D_eta_phi_pT_14_18_clone->Write();
     hSim3D_eta_phi_pT_18_3_clone->Write();
     hSim3D_eta_phi_pT_3_8_clone->Write();
     hSim3D_eta_phi_pT_8_20_clone->Write();
     hSim3D_eta_phi_pT_20_Inf_clone->Write();
     outf->Close();
  }
}
