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
void normalizeByBinWidth(TH2D *histo);
//------------------------

void ResolutionPlotting()
{

   gROOT->Reset();
   gROOT->ProcessLine(".x rootlogonChristof.C");
   gROOT->ForceStyle();
   gStyle->SetPalette(1);
   gStyle->SetTitleYOffset(1.30);
   gStyle->SetPadRightMargin(0.16);

   bool doSave = false;

   TFile *f_input = new TFile("Resolution.root");
   TH2D *hRes_80 = (TH2D*)f_input->Get("hSimPtRecPt_80");
   TH2D *hRes_80_005 = (TH2D*)f_input->Get("hSimPtRecPt_80_005");
   TH2D *hRes_80_larger = (TH2D*)f_input->Get("hSimPtRecPt_80_larger");
   TH2D *hRes_80_smaller = (TH2D*)f_input->Get("hSimPtRecPt_80_smaller");
   TH2D *hRes_80_evensmaller = (TH2D*)f_input->Get("hSimPtRecPt_80_evensmaller");
   TH2D *hRes_80_evensmaller2 = (TH2D*)f_input->Get("hSimPtRecPt_80_evensmaller2");
   TH2D *hRes_80_evensmaller3 = (TH2D*)f_input->Get("hSimPtRecPt_80_evensmaller3");
   TH2D *hRes_80_evensmaller4 = (TH2D*)f_input->Get("hSimPtRecPt_80_evensmaller4");
   TH2D *hRes_370 = (TH2D*)f_input->Get("hSimPtRecPt_370");
   TH2D *hRes_370_larger = (TH2D*)f_input->Get("hSimPtRecPt_370_larger");
   TH2D *hRes_370_smaller = (TH2D*)f_input->Get("hSimPtRecPt_370_smaller");
   TH2D *hRes_370_evensmaller = (TH2D*)f_input->Get("hSimPtRecPt_370_evensmaller");
   TH2D *hRes_370_evensmaller2 = (TH2D*)f_input->Get("hSimPtRecPt_370_evensmaller2");
   TH2D *hRes_370_evensmaller3 = (TH2D*)f_input->Get("hSimPtRecPt_370_evensmaller3");
   TH2D *hRes_370_evensmaller4 = (TH2D*)f_input->Get("hSimPtRecPt_370_evensmaller4");
/*
   //Binwidth noralization
   normalizeByBinWidth(hRes_80);
   normalizeByBinWidth(hRes_80_larger);
   normalizeByBinWidth(hRes_80_smaller);
   normalizeByBinWidth(hRes_80_evensmaller);
   normalizeByBinWidth(hRes_370);
   normalizeByBinWidth(hRes_370_larger);
   normalizeByBinWidth(hRes_370_smaller);
   normalizeByBinWidth(hRes_370_evensmaller);
*/
   TH1D * hDum = new TH1D("hDum","hDum",2000,0.45,100.);

   //FitSlicesY
   hRes_80->FitSlicesY(0,0,-1,0,"NQ");  //0,5
   hRes_80_005->FitSlicesY(0,0,-1,0,"NQ"); 
   hRes_80_larger->FitSlicesY(0,0,-1,0,"NQ");
   hRes_80_smaller->FitSlicesY(0,0,-1,0,"NQ");
   hRes_80_evensmaller->FitSlicesY(0,0,-1,0,"NQ");
   hRes_80_evensmaller2->FitSlicesY(0,0,-1,0,"NQ");
   hRes_80_evensmaller3->FitSlicesY(0,0,-1,0,"NQ");
   hRes_80_evensmaller4->FitSlicesY(0,0,-1,0,"NQ");
   hRes_370->FitSlicesY(0,0,-1,0,"NQ");
   hRes_370_larger->FitSlicesY(0,0,-1,0,"NQ");
   hRes_370_smaller->FitSlicesY(0,0,-1,0,"NQ");
   hRes_370_evensmaller->FitSlicesY(0,0,-1,0,"NQ");
   hRes_370_evensmaller2->FitSlicesY(0,0,-1,0,"NQ");
   hRes_370_evensmaller3->FitSlicesY(0,0,-1,0,"NQ");
   hRes_370_evensmaller4->FitSlicesY(0,0,-1,0,"NQ");

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
   TH1D *h1_80_005 = (TH1D*)gDirectory->Get(Form("%s_1",hRes_80_005->GetName()));
   TH1D *h1_80_larger = (TH1D*)gDirectory->Get(Form("%s_1",hRes_80_larger->GetName()));
   TH1D *h1_80_smaller = (TH1D*)gDirectory->Get(Form("%s_1",hRes_80_smaller->GetName()));
   TH1D *h1_80_evensmaller = (TH1D*)gDirectory->Get(Form("%s_1",hRes_80_evensmaller->GetName()));
   TH1D *h1_80_evensmaller2 = (TH1D*)gDirectory->Get(Form("%s_1",hRes_80_evensmaller2->GetName()));
   TH1D *h1_80_evensmaller3 = (TH1D*)gDirectory->Get(Form("%s_1",hRes_80_evensmaller3->GetName()));
   TH1D *h1_80_evensmaller4 = (TH1D*)gDirectory->Get(Form("%s_1",hRes_80_evensmaller4->GetName()));
   TH1D *h1_370 = (TH1D*)gDirectory->Get(Form("%s_1",hRes_370->GetName()));
   TH1D *h1_370_larger = (TH1D*)gDirectory->Get(Form("%s_1",hRes_370_larger->GetName()));
   TH1D *h1_370_smaller = (TH1D*)gDirectory->Get(Form("%s_1",hRes_370_smaller->GetName()));
   TH1D *h1_370_evensmaller = (TH1D*)gDirectory->Get(Form("%s_1",hRes_370_evensmaller->GetName()));
   TH1D *h1_370_evensmaller2 = (TH1D*)gDirectory->Get(Form("%s_1",hRes_370_evensmaller2->GetName()));
   TH1D *h1_370_evensmaller3 = (TH1D*)gDirectory->Get(Form("%s_1",hRes_370_evensmaller3->GetName()));
   TH1D *h1_370_evensmaller4 = (TH1D*)gDirectory->Get(Form("%s_1",hRes_370_evensmaller4->GetName()));
   hDum->SetMaximum(100.);
   hDum->Draw();
   h1_80->SetMarkerStyle(20);
   h1_80->Draw("same");
   h1_370_evensmaller2->SetMarkerColor(2);
   h1_370_evensmaller2->SetLineColor(2);
   h1_370_evensmaller2->SetMarkerStyle(30);
   h1_370_evensmaller2->Draw("same");

   //sigma
   TCanvas *c2 = new TCanvas("c2","c2");
   c2->cd();
   c2->SetLogx();
   TH1D *h2_80 = (TH1D*)gDirectory->Get(Form("%s_2",hRes_80->GetName()));
   TH1D *hDum2 = (TH1D*)hDum->Clone("hDum2");
   hDum2->SetMaximum(20.);
   hDum2->GetXaxis()->CenterTitle();
   hDum2->GetYaxis()->CenterTitle();
   hDum2->GetXaxis()->SetTitle("p_{T} [GeV/c]");
   hDum2->GetYaxis()->SetTitle("Resolution [%]");
   hDum2->Draw();
   TH1D *h1_80_copy1 = (TH1D*)h1_80->Clone("h1_80_copy1");
   h2_80->Divide(h1_80_copy1);
   h2_80->SetMarkerStyle(20);
   RemoveLargeerrorPoints(h2_80);
   h2_80->Scale(100.);//%
   h2_80->Draw("same");

   TH1D *h2_80_005 = (TH1D*)gDirectory->Get(Form("%s_2",hRes_80_005->GetName()));
   TH1D *h1_80_005_copy1 = (TH1D*)h1_80_005->Clone("h1_80_005_copy1");
   h2_80_005->Divide(h1_80_005_copy1);
   h2_80_005->SetMarkerStyle(20);
   h2_80_005->SetMarkerSize(1.5);
   h2_80_005->SetMarkerColor(kOrange);
   h2_80_005->SetLineColor(1);
   RemoveLargeerrorPoints(h2_80_005);
   h2_80_005->Scale(100.);
   h2_80_005->Draw("same");

   TH1D *h2_80_larger = (TH1D*)gDirectory->Get(Form("%s_2",hRes_80_larger->GetName()));
   TH1D *h1_80_larger_copy1 = (TH1D*)h1_80_larger->Clone("h1_80_larger_copy1");
   h2_80_larger->Divide(h1_80_larger_copy1);
   h2_80_larger->SetMarkerStyle(21);
   h2_80_larger->SetMarkerColor(1);
   h2_80_larger->SetLineColor(1);
   RemoveLargeerrorPoints(h2_80_larger);
   h2_80_larger->Scale(100.);
   h2_80_larger->Draw("same");

   TH1D *h2_80_smaller = (TH1D*)gDirectory->Get(Form("%s_2",hRes_80_smaller->GetName()));
   TH1D *h1_80_smaller_copy1 = (TH1D*)h1_80_smaller->Clone("h1_80_smaller_copy1");
   h2_80_smaller->Divide(h1_80_smaller_copy1);
   h2_80_smaller->SetMarkerStyle(33);
   h2_80_smaller->SetMarkerColor(1);
   h2_80_smaller->SetLineColor(1);
   RemoveLargeerrorPoints(h2_80_smaller);
   h2_80_smaller->Scale(100.);
   h2_80_smaller->Draw("same");

   TH1D *h2_80_evensmaller = (TH1D*)gDirectory->Get(Form("%s_2",hRes_80_evensmaller->GetName()));
   TH1D *h1_80_evensmaller_copy1 = (TH1D*)h1_80_evensmaller->Clone("h1_80_evensmaller_copy1");
   h2_80_evensmaller->Divide(h1_80_evensmaller_copy1);
   h2_80_evensmaller->SetMarkerStyle(29);
   h2_80_evensmaller->SetMarkerColor(1);
   h2_80_evensmaller->SetLineColor(1);
   RemoveLargeerrorPoints(h2_80_evensmaller);
   h2_80_evensmaller->Scale(100.);
   h2_80_evensmaller->Draw("same");

   TH1D *h2_80_evensmaller2 = (TH1D*)gDirectory->Get(Form("%s_2",hRes_80_evensmaller2->GetName()));
   TH1D *h1_80_evensmaller2_copy1 = (TH1D*)h1_80_evensmaller2->Clone("h1_80_evensmaller2_copy1");
   h2_80_evensmaller2->Divide(h1_80_evensmaller2_copy1);
   h2_80_evensmaller2->SetMarkerStyle(29);
   h2_80_evensmaller2->SetMarkerColor(2);
   h2_80_evensmaller2->SetLineColor(2);
   RemoveLargeerrorPoints(h2_80_evensmaller2);
   h2_80_evensmaller2->Scale(100.);
   h2_80_evensmaller2->Draw("same");

   TH1D *h2_80_evensmaller3 = (TH1D*)gDirectory->Get(Form("%s_2",hRes_80_evensmaller3->GetName()));
   TH1D *h1_80_evensmaller3_copy1 = (TH1D*)h1_80_evensmaller3->Clone("h1_80_evensmaller3_copy1");
   h2_80_evensmaller3->Divide(h1_80_evensmaller3_copy1);
   h2_80_evensmaller3->SetMarkerStyle(24);
   h2_80_evensmaller3->SetMarkerColor(2);
   h2_80_evensmaller3->SetLineColor(2);
   RemoveLargeerrorPoints(h2_80_evensmaller3);
   h2_80_evensmaller3->Scale(100.);
   h2_80_evensmaller3->Draw("same");

   TH1D *h2_80_evensmaller4 = (TH1D*)gDirectory->Get(Form("%s_2",hRes_80_evensmaller4->GetName()));
   TH1D *h1_80_evensmaller4_copy1 = (TH1D*)h1_80_evensmaller4->Clone("h1_80_evensmaller4_copy1");
   h2_80_evensmaller4->Divide(h1_80_evensmaller4_copy1);
   h2_80_evensmaller4->SetMarkerStyle(20);
   h2_80_evensmaller4->SetMarkerColor(2);
   h2_80_evensmaller4->SetLineColor(2);
   RemoveLargeerrorPoints(h2_80_evensmaller4);
   h2_80_evensmaller4->Scale(100.);
   h2_80_evensmaller4->Draw("same");

   TH1D *h2_370 = (TH1D*)gDirectory->Get(Form("%s_2",hRes_370->GetName()));
   TH1D *h1_370_copy1 = (TH1D*)h1_370->Clone("h1_370_copy1");
   h2_370->Divide(h1_370_copy1);
   h2_370->SetMarkerStyle(24);
   h2_370->SetMarkerColor(4);
   h2_370->SetLineColor(4);
   RemoveLargeerrorPoints(h2_370);
   h2_370->Scale(100.);
   h2_370->Draw("same");

   TH1D *h2_370_larger = (TH1D*)gDirectory->Get(Form("%s_2",hRes_370_larger->GetName()));
   TH1D *h1_370_larger_copy1 = (TH1D*)h1_370_larger->Clone("h1_370_larger_copy1");
   h2_370_larger->Divide(h1_370_larger_copy1);
   h2_370_larger->SetMarkerStyle(25);
   h2_370_larger->SetMarkerColor(4);
   h2_370_larger->SetLineColor(4);
   RemoveLargeerrorPoints(h2_370_larger);
   h2_370_larger->Scale(100.);
   h2_370_larger->Draw("same");

   TH1D *h2_370_smaller = (TH1D*)gDirectory->Get(Form("%s_2",hRes_370_smaller->GetName()));
   TH1D *h1_370_smaller_copy1 = (TH1D*)h1_370_smaller->Clone("h1_370_smaller_copy1");
   h2_370_smaller->Divide(h1_370_smaller_copy1);
   h2_370_smaller->SetMarkerStyle(27);
   h2_370_smaller->SetMarkerColor(4);
   h2_370_smaller->SetLineColor(4);
   RemoveLargeerrorPoints(h2_370_smaller);
   h2_370_smaller->Scale(100.);
   h2_370_smaller->Draw("same");

   TH1D *h2_370_evensmaller = (TH1D*)gDirectory->Get(Form("%s_2",hRes_370_evensmaller->GetName()));
   TH1D *h1_370_evensmaller_copy1 = (TH1D*)h1_370_evensmaller->Clone("h1_370_evensmaller_copy1");
   h2_370_evensmaller->Divide(h1_370_evensmaller_copy1);
   h2_370_evensmaller->SetMarkerStyle(30);
   h2_370_evensmaller->SetMarkerColor(4);
   h2_370_evensmaller->SetLineColor(4);
   RemoveLargeerrorPoints(h2_370_evensmaller);
//   h2_370_evensmaller->Draw("same");

   TH1D *h2_370_evensmaller2 = (TH1D*)gDirectory->Get(Form("%s_2",hRes_370_evensmaller2->GetName()));
   TH1D *h1_370_evensmaller2_copy1 = (TH1D*)h1_370_evensmaller2->Clone("h1_370_evensmaller2_copy1");
   h2_370_evensmaller2->Divide(h1_370_evensmaller2_copy1);
   h2_370_evensmaller2->SetMarkerStyle(30);
   h2_370_evensmaller2->SetMarkerColor(4);
   h2_370_evensmaller2->SetLineColor(4);
   RemoveLargeerrorPoints(h2_370_evensmaller2);
//   h2_370_evensmaller2->Draw("same");

//   TF1 *fFit = new TF1("fFit","100.*([0]*pow(x,[1])/(1+exp([2]*(x+[3])))+[4]*pow(x,[5]))",0.6,90.);//%
//   TF1 *fFit = new TF1("fFit","100.*([0]*pow(x,[1])/(1+exp([2]*(x+[3])))+[4]*pow(x,[5]))",0.6,90.);//%
   TF1 *fFit = new TF1("fFit","100.*([0]*pow(x,[1])/(1+exp([2]*(x+[3])))+[4]*pow(x,[5]))",0.4,100.);//%
   fFit->SetLineWidth(3);
   fFit->SetLineStyle(2);
   fFit->SetLineColor(8);
//   h2_370->Fit(fFit,"REM","same");
//   h2_80_evensmaller2->Fit(fFit,"REM","same");
//   h2_80_evensmaller2->Fit(fFit,"REM0");
   fFit->SetParameter(0,6.91047e-03);
   fFit->SetParameter(1,1.62838e-01);
   fFit->SetParameter(2,-7.82497e+03);
   fFit->SetParameter(3,7.09137e+03);
   fFit->SetParameter(4,5.12914e-03);
   fFit->SetParameter(5,-1.43678e+00);
   fFit->SetParameter(5,-1.23678e+00);
   fFit->Draw("same");

   TLegend *leg2 = new TLegend(0.2,0.6,0.9,0.9,NULL,"brNDC");
   leg2->AddEntry(h2_80_005,"Pt80, HIN-10-005 binning","pl");
   leg2->AddEntry(h2_80_larger,"#hat{p}_{T}=80, bin width at low-p_{T}: 200 MeV/c","pl");
   leg2->AddEntry(h2_80,"#hat{p}_{T}=80, bin width at low-p_{T}: 100 MeV/c","pl");
   leg2->AddEntry(h2_80_smaller,"#hat{p}_{T}=80, bin width at low-p_{T}: 50 MeV/c","pl");
   leg2->AddEntry(h2_80_evensmaller,"#hat{p}_{T}=80, bin width at low-p_{T}: 25 MeV/c","pl");
   leg2->AddEntry(h2_80_evensmaller2,"#hat{p}_{T}=80, bin width at low-p_{T}: 12.5 MeV/c","pl");
   leg2->AddEntry(h2_80_evensmaller3,"#hat{p}_{T}=80, bin width at low-p_{T}: 6.25 MeV/c","pl");
   leg2->AddEntry(h2_80_evensmaller4,"#hat{p}_{T}=80, bin width at low-p_{T}: 3.125 MeV/c","pl");
   leg2->AddEntry(h2_370_larger,"#hat{p}_{T}=370, bin width at low-p_{T}: 200 MeV/c","pl");
   leg2->AddEntry(h2_370,"#hat{p}_{T}=370, bin width at low-p_{T}: 100 MeV/c","pl");
   leg2->AddEntry(h2_370_smaller,"#hat{p}_{T}=370, bin width at low-p_{T}: 50 MeV/c","pl");
   leg2->AddEntry(fFit,"Parameterization: a#upointx^{b}/(1+exp(c#upoint(x+d)))+e#upointx^{f}","l");
//   leg2->AddEntry(h2_370_evensmaller,"Pt370_evensmaller, even smaller bins","pl");
//   leg2->AddEntry(h2_370_evensmaller2,"Pt370_evensmaller2, even smaller bins","pl");
   leg2->SetFillStyle(0);
   leg2->SetFillColor(0);
   leg2->SetBorderSize(0);
   leg2->Draw();
//   TLatex * l1 = new TLatex(0.25,0.75,"Fit: [0]*pow(x,[1])/(1+exp([2]*(x+[3])))+ [4]*pow(x,[5])");
   TLatex * l1 = new TLatex(0.25,0.55,"Parameterization: a#upointx^{b}/(1+exp(c#upoint(x+d)))+e#upointx^{f}");
   l1->SetNDC();
   l1->SetTextSize(0.03);
//   l1->Draw();
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


void RemoveLargeerrorPoints(TH1D *h_input) {
  for(int i=1; i<=h_input->GetNbinsX(); i++) {
     if((h_input->GetBinError(i)/h_input->GetBinContent(i))>0.3) {
        h_input->SetBinContent(i,0);
        h_input->SetBinError(i,0);
     }
  }
}


void normalizeByBinWidth(TH2D *histo) {
   for(int i = 1; i <= histo->GetNbinsX(); i++) {
      float content = histo->GetBinContent(i);
      float error = histo->GetBinError(i);
      histo->SetBinContent(i,content/histo->GetBinWidth(i));
      histo->SetBinError(i,error/histo->GetBinWidth(i));
   }
}

