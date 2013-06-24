#include <TROOT.h>
#include <TStyle.h>
#include <TFile.h>
#include <TH1D.h>
#include <TNtuple.h>
#include <iostream>
#include <fstream>
#include <TLegend.h>
#include <TLatex.h>
#include <TLine.h>
#include <TGraphErrors.h>
#include <TCanvas.h>
#include <TMath.h>

TGraphErrors* drawErrorBoxes(TH1 *hist);
void drawBox(Double_t y, Double_t err, Double_t x, Double_t width, Int_t color);
void drawTickError(TH1 *hist, TGraphErrors *tg);
void drawTick(Double_t Y, Double_t Erru, Double_t Errd, Double_t X, Double_t Tick_x, Double_t Tick_y, Int_t TickColor);


void Y_pPb_0308()
{
   gROOT->Reset();
   gROOT->ProcessLine(".x rootlogonChristof.C");
   gROOT->ForceStyle();
   gStyle->SetPalette(1);
   gStyle->SetTitleYOffset(1.28);
//   gStyle->SetPadRightMargin(0.16);

   //Get pPb spectrum
   TFile *f_CombpPbPbp_EtaCM_P03_P08 = new TFile("PtSpectraCombination_StagedNormalization_EtaCM_P03_P08_NoOLDAlignmentRuns_CombpPbPbp_TrackTrigger.root");
   TFile *f_pPb_EtaCM_P03_P08 = new TFile("PtSpectraCombination_StagedNormalization_EtaCM_P03_P08_NoOLDAlignmentRuns_TrackTrigger.root");
   TFile *f_Pbp_EtaCM_P03_P08 = new TFile("ReverseBeam/PtSpectraCombination_StagedNormalization_EtaCM_P03_P08_TrackTrigger.root");
   TH1D *hSpectrum_CombpPbPbp_EtaCM_P03_P08 = (TH1D*)f_CombpPbPbp_EtaCM_P03_P08->Get("hSumPartPt");
   TH1D *hSpectrum_pPb_EtaCM_P03_P08 = (TH1D*)f_pPb_EtaCM_P03_P08->Get("hSumPartPt");
   TH1D *hSpectrum_Pbp_EtaCM_P03_P08 = (TH1D*)f_Pbp_EtaCM_P03_P08->Get("hSumPartPt");
//   TH1D *hSpectrum_pPb_EtaCM_P03_P08 = (TH1D*)f_pPb_EtaCM_P03_P08->Get("hPartPt_minbias_trkCorr_trigCorr");
//   TH1D* hNumEv_minbias_0308 = (TH1D*)f_pPb_EtaCM_P03_P08->Get("hNumEv_minbias_trigCorr");
//   float numev_minbias_0308 = hNumEv_minbias_0308->GetBinContent(1);

   TFile *f_CombpPbPbp_EtaCM_M03_M08 = new TFile("PtSpectraCombination_StagedNormalization_EtaCM_M03_M08_NoOLDAlignmentRuns_CombpPbPbp_TrackTrigger.root");
   TFile *f_pPb_EtaCM_M03_M08 = new TFile("PtSpectraCombination_StagedNormalization_EtaCM_M03_M08_NoOLDAlignmentRuns_TrackTrigger.root");
   TFile *f_Pbp_EtaCM_M03_M08 = new TFile("ReverseBeam/PtSpectraCombination_StagedNormalization_EtaCM_M03_M08_TrackTrigger.root");
   TH1D *hSpectrum_CombpPbPbp_EtaCM_M03_M08 = (TH1D*)f_CombpPbPbp_EtaCM_M03_M08->Get("hSumPartPt");
   TH1D *hSpectrum_pPb_EtaCM_M03_M08 = (TH1D*)f_pPb_EtaCM_M03_M08->Get("hSumPartPt");
   TH1D *hSpectrum_Pbp_EtaCM_M03_M08 = (TH1D*)f_Pbp_EtaCM_M03_M08->Get("hSumPartPt");
//   TH1D *hSpectrum_pPb_EtaCM_M03_M08 = (TH1D*)f_pPb_EtaCM_M03_M08->Get("hPartPt_minbias_trkCorr_trigCorr");
//   TH1D* hNumEv_minbias_M03M08 = (TH1D*)f_pPb_EtaCM_M03_M08->Get("hNumEv_minbias_trigCorr");
//   float numev_minbias_M03M08 = hNumEv_minbias_M03M08->GetBinContent(1);

   //PLOTTING
   bool DoSave = true;

   TCanvas *c1 = new TCanvas("c1","c1");
   c1->SetLogy();
   hSpectrum_pPb_EtaCM_P03_P08->GetXaxis()->SetTitle("p_{T} [GeV/c]");
   hSpectrum_pPb_EtaCM_P03_P08->GetYaxis()->SetTitle("1/N_{ev} dN/dp_{T}");
   hSpectrum_pPb_EtaCM_P03_P08->SetMarkerStyle(20);
   hSpectrum_pPb_EtaCM_P03_P08->Draw();
   hSpectrum_pPb_EtaCM_M03_M08->SetMarkerStyle(20);
   hSpectrum_pPb_EtaCM_M03_M08->SetMarkerColor(4);
   hSpectrum_pPb_EtaCM_M03_M08->SetLineColor(4);
   hSpectrum_pPb_EtaCM_M03_M08->Draw("same");
   TLegend *leg1 = new TLegend(0.4,0.7,0.8,0.85,NULL,"brNDC");
   leg1->AddEntry(hSpectrum_pPb_EtaCM_P03_P08,"pPb, 0.3<#eta_{CM}<0.8","pl");
   leg1->AddEntry(hSpectrum_pPb_EtaCM_M03_M08,"pPb, -0.8<#eta_{CM}<-0.3","pl");
   leg1->SetFillStyle(0);
   leg1->SetFillColor(0);
   leg1->SetBorderSize(0);
   leg1->Draw();
   if(DoSave) {
      c1->SaveAs("Figs/Y_pPb_0308_c1.gif");
      c1->SaveAs("Figs/Y_pPb_0308_c1.eps");
      c1->SaveAs("Figs/Y_pPb_0308_c1.C");
   }

   TCanvas *c2 = new TCanvas("c2","c2");
   c2->SetLogx();
   TH1D* hSpectrum_pPb_EtaCM_P03_P08_copy1 = (TH1D*)hSpectrum_pPb_EtaCM_P03_P08->Clone("hSpectrum_pPb_EtaCM_P03_P08_copy1");
   TH1D* hSpectrum_Pbp_EtaCM_M03_M08_copy1 = (TH1D*)hSpectrum_Pbp_EtaCM_M03_M08->Clone("hSpectrum_Pbp_EtaCM_M03_M08_copy1");

   hSpectrum_CombpPbPbp_EtaCM_P03_P08->Divide(hSpectrum_CombpPbPbp_EtaCM_M03_M08);
   hSpectrum_pPb_EtaCM_P03_P08_copy1->Divide(hSpectrum_pPb_EtaCM_M03_M08);
   hSpectrum_Pbp_EtaCM_M03_M08_copy1->Divide(hSpectrum_Pbp_EtaCM_P03_P08);

   hSpectrum_CombpPbPbp_EtaCM_P03_P08->GetYaxis()->SetTitle("Y_{asym}");
   hSpectrum_CombpPbPbp_EtaCM_P03_P08->SetMarkerStyle(20);
   hSpectrum_CombpPbPbp_EtaCM_P03_P08->SetMinimum(0.2);
   hSpectrum_CombpPbPbp_EtaCM_P03_P08->SetMaximum(1.9);
   hSpectrum_CombpPbPbp_EtaCM_P03_P08->GetXaxis()->SetRangeUser(0.,100.);
   hSpectrum_CombpPbPbp_EtaCM_P03_P08->Draw();   
   TGraphErrors* hSpectrum_CombpPbPbp_EtaCM_P03_P08_sys = drawErrorBoxes(hSpectrum_CombpPbPbp_EtaCM_P03_P08);
   drawTickError(hSpectrum_CombpPbPbp_EtaCM_P03_P08,hSpectrum_CombpPbPbp_EtaCM_P03_P08_sys);
   hSpectrum_CombpPbPbp_EtaCM_P03_P08->Draw("same");   
   hSpectrum_pPb_EtaCM_P03_P08_copy1->SetMarkerStyle(24);   
   hSpectrum_pPb_EtaCM_P03_P08_copy1->SetMarkerColor(4);   
   hSpectrum_pPb_EtaCM_P03_P08_copy1->SetLineColor(4);   
   hSpectrum_pPb_EtaCM_P03_P08_copy1->Draw("same");   

   hSpectrum_Pbp_EtaCM_M03_M08_copy1->SetMarkerStyle(24);
   hSpectrum_Pbp_EtaCM_M03_M08_copy1->SetLineColor(6);
   hSpectrum_Pbp_EtaCM_M03_M08_copy1->SetMarkerColor(6);  
   hSpectrum_Pbp_EtaCM_M03_M08_copy1->Draw("same");   

   TLegend *leg2 = new TLegend(0.23,0.15,0.86,0.36,NULL,"brNDC");
//   leg2->AddEntry(hSpectrum_pPb_EtaCM_P03_P08_copy1,"pPb, dN/dp_{T}(0.3<#eta_{CM}<0.8) / dN/dp_{T}(-0.8<#eta_{CM}<-0.3)","pl");
//   leg2->AddEntry(hSpectrum_Pbp_EtaCM_M03_M08_copy1,"Pbp, dN/dp_{T}(-0.8<#eta_{CM}<-0.3) / dN/dp_{T}(0.3<#eta_{CM}<0.8)","pl");
   leg2->AddEntry(hSpectrum_CombpPbPbp_EtaCM_P03_P08,"pPb+Pbp combined, 0.3<#eta_{CM}<0.8 / -0.8<#eta_{CM}<-0.3","pl");
   leg2->AddEntry(hSpectrum_pPb_EtaCM_P03_P08_copy1,"pPb, 0.3<#eta_{CM}<0.8 / -0.8<#eta_{CM}<-0.3","pl");
   leg2->AddEntry(hSpectrum_Pbp_EtaCM_M03_M08_copy1,"Pbp, -0.8<#eta_{CM}<-0.3 / 0.3<#eta_{CM}<0.8","pl");
   leg2->SetFillStyle(0);
   leg2->SetFillColor(0);
   leg2->SetBorderSize(0);
   leg2->Draw();
   TPad *c2_zoom = new TPad("c2_zoom","c2_zoom",0.57,0.57,0.95,0.95);
   c2_zoom->SetFillStyle(0);
   c2_zoom->Draw();
   c2_zoom->cd();
   TH1D* hSpectrum_CombpPbPbp_EtaCM_P03_P08_copy1 = (TH1D*)hSpectrum_CombpPbPbp_EtaCM_P03_P08->Clone("hSpectrum_CombpPbPbp_EtaCM_P03_P08_copy1");
   TH1D* hSpectrum_pPb_EtaCM_P03_P08_copy2 = (TH1D*)hSpectrum_pPb_EtaCM_P03_P08_copy1->Clone("hSpectrum_pPb_EtaCM_P03_P08_copy2");
   TH1D* hSpectrum_Pbp_EtaCM_M03_M08_copy2 = (TH1D*)hSpectrum_Pbp_EtaCM_M03_M08_copy1->Clone("hSpectrum_Pbp_EtaCM_M03_M08_copy2");
   hSpectrum_CombpPbPbp_EtaCM_P03_P08_copy1->SetMinimum(0.);
   hSpectrum_CombpPbPbp_EtaCM_P03_P08_copy1->SetMaximum(1.45);
   hSpectrum_CombpPbPbp_EtaCM_P03_P08_copy1->GetXaxis()->SetRangeUser(0.,14.);
   hSpectrum_CombpPbPbp_EtaCM_P03_P08_copy1->Draw();
   TGraphErrors* hSpectrum_CombpPbPbp_EtaCM_P03_P08_copy1_sys = drawErrorBoxes(hSpectrum_CombpPbPbp_EtaCM_P03_P08_copy1);
   drawTickError(hSpectrum_CombpPbPbp_EtaCM_P03_P08_copy1,hSpectrum_CombpPbPbp_EtaCM_P03_P08_copy1_sys);
   hSpectrum_CombpPbPbp_EtaCM_P03_P08_copy1->Draw("same");
   hSpectrum_pPb_EtaCM_P03_P08_copy2->Draw("same");
   hSpectrum_Pbp_EtaCM_M03_M08_copy2->Draw("same");
   if(DoSave) {
      c2->SaveAs("Figs/Y_pPb_0308_c2.gif");
      c2->SaveAs("Figs/Y_pPb_0308_c2.eps");
      c2->SaveAs("Figs/Y_pPb_0308_c2.C");
   }


   TCanvas *c2a = new TCanvas("c2a","c2a");
   c2a->SetLogx();
   hSpectrum_CombpPbPbp_EtaCM_P03_P08->GetYaxis()->SetTitle("Y_{asym} (0.3<|#eta_{CM}|<0.8)");
   hSpectrum_CombpPbPbp_EtaCM_P03_P08->Draw();   
   TGraphErrors* hSpectrum_CombpPbPbp_EtaCM_P03_P08_sys_inst2 = drawErrorBoxes(hSpectrum_CombpPbPbp_EtaCM_P03_P08);
   drawTickError(hSpectrum_CombpPbPbp_EtaCM_P03_P08,hSpectrum_CombpPbPbp_EtaCM_P03_P08_sys_inst2);
   hSpectrum_CombpPbPbp_EtaCM_P03_P08->Draw("same");   
//   hSpectrum_Pbp_EtaCM_M03_M08_copy1->Draw("same");   
   TLegend *leg2a = new TLegend(0.18,0.22,0.92,0.43,NULL,"brNDC");
   leg2a->AddEntry(hSpectrum_CombpPbPbp_EtaCM_P03_P08,"pPb #sqrt{s_{NN}} = 5.02 TeV, charged particles","pl");
//   leg2a->AddEntry(hSpectrum_Pbp_EtaCM_M03_M08_copy1,"Pbp, -0.8<#eta_{CM}<-0.3 / 0.3<#eta_{CM}<0.8","pl");
   leg2a->SetFillStyle(0);
   leg2a->SetFillColor(0);
   leg2a->SetBorderSize(0);
   leg2a->Draw();
   TLatex *prel = new TLatex(0.2,0.25,"CMS Preliminary");
   prel->SetNDC();
   prel->SetTextSize(0.035);
   prel->Draw();
   TPad *c2a_zoom = new TPad("c2a_zoom","c2a_zoom",0.57,0.57,0.95,0.95);
   c2a_zoom->SetFillStyle(0);
   c2a_zoom->Draw();
   c2a_zoom->cd();
   TH1D* hSpectrum_CombpPbPbp_EtaCM_P03_P08_copy2 = (TH1D*)hSpectrum_CombpPbPbp_EtaCM_P03_P08->Clone("hSpectrum_CombpPbPbp_EtaCM_P03_P08_copy2");
   hSpectrum_CombpPbPbp_EtaCM_P03_P08_copy2->Draw();
   TGraphErrors* hSpectrum_CombpPbPbp_EtaCM_P03_P08_copy2_sys_inst3 = drawErrorBoxes(hSpectrum_CombpPbPbp_EtaCM_P03_P08_copy2);
   drawTickError(hSpectrum_CombpPbPbp_EtaCM_P03_P08_copy2,hSpectrum_CombpPbPbp_EtaCM_P03_P08_copy2_sys_inst3);
   hSpectrum_CombpPbPbp_EtaCM_P03_P08_copy2->Draw("same");
//   hSpectrum_Pbp_EtaCM_M03_M08_copy2->Draw("same");
   if(DoSave) {
      c2a->SaveAs("Figs/Y_pPb_0308_c2a.gif");
      c2a->SaveAs("Figs/Y_pPb_0308_c2a.eps");
      c2a->SaveAs("Figs/Y_pPb_0308_c2a.C");
   }


/*
   TCanvas *c3 = new TCanvas("c3","c3");
   c3->cd();
   TH1D * hSpectrum_pPb_EtaCM_P03_P08_copy3 = hSpectrum_pPb_EtaCM_P03_P08_copy2->Clone("hSpectrum_pPb_EtaCM_P03_P08_copy3");
   hSpectrum_pPb_EtaCM_P03_P08_copy3->Draw();
*/
}


TGraphErrors* drawErrorBoxes(TH1 *hist) {

  Float_t pt[hist->GetNbinsX()], yield[hist->GetNbinsX()], pterror[hist->GetNbinsX()], yielderror[hist->GetNbinsX()];
  for(int i=1;i <= hist->GetNbinsX();i++){
     double x = hist->GetBinCenter(i);
     double y = hist->GetBinContent(i);
     double w = hist->GetBinWidth(i);

     Double_t err = 0.;

     if(x<1.0)
       err = 0.03;
     else if(x<2.0)
       err = 0.03;
     else if(x<3.2)
       err = 0.03;
     else if(x<24.)
       err = 0.03;
     else
       err = 0.03;

     drawBox(y,err,x,w*0.6,5);

     pt[i-1]=x;
     pterror[i-1]=0.;
     yield[i-1]=y;
     yielderror[i-1]=err*yield[i-1];//err is relative error here
  }
  TGraphErrors *sys = new TGraphErrors(hist->GetNbinsX(),pt,yield,pterror,yielderror);
  return sys;
}


void drawBox(Double_t y, Double_t err, Double_t x, Double_t width, Int_t color) {
  TGraphErrors *tg = new TGraphErrors();

  double xvalue[2];
  double yvalue[2];
  double xerror[2];
  double yerror[2];

  xvalue[0] = x - 0.5*width;
  xvalue[1] = x + 0.5*width;
  yvalue[0] = y;
  yvalue[1] = y;

  xerror[0] = 0.0;
  xerror[1] = 0.0;

  yerror[0] = err*yvalue[0];
  yerror[1] = err*yvalue[0];

  tg = new TGraphErrors(2,xvalue,yvalue,xerror,yerror);

  tg->SetFillColor(color);
  tg->SetLineColor(color);

  tg->SetFillStyle(1001);
  tg->Draw("3");
}


void drawTickError(TH1 *hist, TGraphErrors *tg) {

  for(int i=0;i<hist->GetNbinsX();i++){
    double x = hist->GetBinCenter(i+1);
    double y = hist->GetBinContent(i+1);
    double w = hist->GetBinWidth(i+1);
//    drawTick(Double_t Y, Double_t Erru, Double_t Errd, Double_t X, Double_t Tick_x, Double_t Tick_y, Int_t TickColor)
    if(y>0.1 && x<100.) //not to draw lines for empty bins
       drawTick(y,tg->GetErrorY(i),tg->GetErrorY(i),x,0.015,0.3*w,1);
  }
}


void drawTick(Double_t Y, Double_t Erru, Double_t Errd, Double_t X, Double_t Tick_x, Double_t Tick_y, Int_t TickColor) 
{

  Int_t tcolor[13]={kViolet+2,kBlue,kAzure+6,kGreen-3,kOrange-5,kOrange-3,kOrange+4,kRed-3,kRed,kRed+2,kMagenta,kOrange,1};

  if(TickColor>13){
    TickColor = tcolor[TickColor-14];
  }

  TLine *line;
  line = new TLine(X-Tick_y,Y+Erru,X-Tick_y,Y+Erru-Tick_x);
  line->SetLineColor(TickColor);
  line->Draw();
  line = new TLine(X+Tick_y,Y+Erru,X+Tick_y,Y+Erru-Tick_x);
  line->SetLineColor(TickColor);
  line->Draw();
  line = new TLine(X-Tick_y,Y+Erru,X+Tick_y,Y+Erru);
  line->SetLineColor(TickColor);
  line->Draw();

  line = new TLine(X-Tick_y,Y-Errd,X-Tick_y,Y-Errd+Tick_x);
  line->SetLineColor(TickColor);
  line->Draw();
  line = new TLine(X+Tick_y,Y-Errd,X+Tick_y,Y-Errd+Tick_x);
  line->SetLineColor(TickColor);
  line->Draw();
  line = new TLine(X-Tick_y,Y-Errd,X+Tick_y,Y-Errd);
  line->SetLineColor(TickColor);
  line->Draw();
}

