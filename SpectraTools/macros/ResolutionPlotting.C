//#include "hiForest.h"
//#include "utilities.h"
#include <TROOT.h>
#include <TStyle.h>
#include <TFile.h>
#include <TH1D.h>
#include <TNtuple.h>
#include <iostream>
#include <TLegend.h>
#include <TLatex.h>

TH1D* divideHistosDiffBins(TH1D* h_Num, TH1D* h_Den);
void RemoveLargeerrorPoints(TH1D *h_input);
//------------------------

void ResolutionPlotting()
{

   gROOT->Reset();
   gROOT->ProcessLine(".x rootlogonChristof.C");
   gROOT->ForceStyle();
   gStyle->SetPalette(1);
   gStyle->SetTitleYOffset(1.30);
   gStyle->SetPadRightMargin(0.16);

   bool doSave = true;

   TFile *f_input = new TFile("Resolution.root");
   TH2D *hRes_80 = (TH2D*)f_input->Get("hSimPtRecPt_80");
   TH2D *hRes_370 = (TH2D*)f_input->Get("hSimPtRecPt_370");

   TH1D * hDum = new TH1D("hDum","hDum",2000,0.3,100.);

   hRes_80->FitSlicesY(0,5,-1,0,"NQ");
   hRes_370->FitSlicesY(0,5,-1,0,"NQ");

   TCanvas *c0 = new TCanvas("c0","c0");
   c0->cd();
   c0->SetLogz();
   hRes_370->GetXaxis()->SetTitle("sim p_{T} [GeV/c]");
   hRes_370->GetYaxis()->SetTitle("reco p_{T} [GeV/c]");
   gStyle->SetPadRightMargin(0.16);
   hRes_370->GetXaxis()->SetRangeUser(0.,100.);
   hRes_370->GetYaxis()->SetRangeUser(0.,100.);
   hRes_370->Draw("colz");
   gStyle->SetPadRightMargin(0.04);
   if(doSave) {
      c0->SaveAs("Figs/ResolutionPlotting_c0.gif");
      c0->SaveAs("Figs/ResolutionPlotting_c0.eps");
      c0->SaveAs("Figs/ResolutionPlotting_c0.C");
   }

   //mean
   TCanvas *c1 = new TCanvas("c1","c1");
   c1->cd();
   TH1D *h1_80 = (TH1D*)gDirectory->Get(Form("%s_1",hRes_80->GetName()));
   TH1D *h1_370 = (TH1D*)gDirectory->Get(Form("%s_1",hRes_370->GetName()));
   hDum->SetMaximum(100.);
   hDum->Draw();
   h1_80->Draw("same");

   //sigma
   TCanvas *c2 = new TCanvas("c2","c2");
   c2->cd();
   c2->SetLogx();
   TH1D *h2_80 = (TH1D*)gDirectory->Get(Form("%s_2",hRes_80->GetName()));
   TH1D *hDum2 = (TH1D*)hDum->Clone("hDum2");
   hDum2->SetMaximum(0.1);
   hDum2->GetXaxis()->CenterTitle();
   hDum2->GetYaxis()->CenterTitle();
   hDum2->GetXaxis()->SetTitle("p_{T} [GeV/c]");
   hDum2->GetYaxis()->SetTitle("Resolution");
   hDum2->Draw();
   TH1D *h1_80_copy1 = (TH1D*)h1_80->Clone("h1_80_copy1");
   h2_80->Divide(h1_80_copy1);
   h2_80->SetMarkerStyle(20);
   RemoveLargeerrorPoints(h2_80);
   h2_80->Draw("same");

   TH1D *h2_370 = (TH1D*)gDirectory->Get(Form("%s_2",hRes_370->GetName()));
   TH1D *h1_370_copy1 = (TH1D*)h1_370->Clone("h1_370_copy1");
   h2_370->Divide(h1_370_copy1);
   h2_370->SetMarkerStyle(25);
   h2_370->SetMarkerColor(4);
   h2_370->SetLineColor(4);
   RemoveLargeerrorPoints(h2_370);
   h2_370->Draw("same");

//   TF1 *fFit = new TF1("fFit","[0]+[1]*x^[2]+log([3]*x)",0.6,50.);
   TF1 *fFit = new TF1("fFit","[0]*pow(x,[1])/(1+exp([2]*(x+[3])))+ [4]*pow(x,[5])",0.6,90.);
//   h2_80->Rebin(2);
   fFit->SetLineWidth(3);
   h2_370->Fit(fFit,"REM","same");

   TLegend *leg2 = new TLegend(0.6,0.8,0.8,0.9,NULL,"brNDC");
   leg2->AddEntry(h2_370,"Pt370","pl");
   leg2->AddEntry(h2_80,"Pt80","pl");
   leg2->SetFillStyle(0);
   leg2->SetFillColor(0);
   leg2->SetBorderSize(0);
   leg2->Draw();
   TLatex * l1 = new TLatex(0.25,0.75,"Fit: [0]*pow(x,[1])/(1+exp([2]*(x+[3])))+ [4]*pow(x,[5])");
   l1->SetNDC();
   l1->SetTextSize(0.03);
   l1->Draw();
   if(doSave) {
      c2->SaveAs("Figs/ResolutionPlotting_c2.gif");
      c2->SaveAs("Figs/ResolutionPlotting_c2.eps");
      c2->SaveAs("Figs/ResolutionPlotting_c2.C");
   }
}


TH1D* divideHistosDiffBins(TH1D* h_Num, TH1D* h_Den) {
   TH1D *h_ratio = (TH1D*)h_Num->Clone("h_ratio");
   h_ratio->Reset();
   for(int i = 1; i <= h_Num->GetNbinsX(); i++) {
      float content = h_Num->GetBinContent(i);
      float error = h_Num->GetBinError(i);
      float center = h_Num->GetBinCenter(i);
      int which_bin_in_h_Den = h_Den->FindBin(center);
      float content_h_Den = h_Den->GetBinContent(which_bin_in_h_Den);

      if(content_h_Den==0)
         continue;

      h_ratio->SetBinContent(i,content/content_h_Den);      
      h_ratio->SetBinError(i,error/content_h_Den);      
   }
   return h_ratio;
}

void convertToYield(TH1D* h_ppRef_LogLogpt, float sigma_inel) {

   for(int i = 1; i <= h_ppRef_LogLogpt->GetNbinsX(); i++) {
      float content_Ed3sigmadp3 = h_ppRef_LogLogpt->GetBinContent(i);
      float bincenter = h_ppRef_LogLogpt->GetBinCenter(i);
      //multiply by 2*pi*pT
      float content_d2sigmadetadpT = content_Ed3sigmadp3*2.*TMath::Pi()*bincenter;
      //multiply by 2: reference pp is for the average of the + and - particles
      content_d2sigmadetadpT *= 2.;
      //convert d2sigmadetadpT to d2NdetadpT
      float content_d2NdetadpT = content_d2sigmadetadpT/sigma_inel;
      //convert d2NdetadpT to dNdpT in |eta|<1
      content_d2NdetadpT *= 2.;
      h_ppRef_LogLogpt->SetBinContent(i,content_d2NdetadpT);
   }
}

void RemoveLargeerrorPoints(TH1D *h_input) {
  for(int i=1; i<=h_input->GetNbinsX(); i++) {
     if((h_input->GetBinError(i)/h_input->GetBinContent(i))>0.3) {
        h_input->SetBinContent(i,0);
        h_input->SetBinError(i,0);
     }
  }
}

