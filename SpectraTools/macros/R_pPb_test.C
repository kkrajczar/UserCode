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
TH1D* singleReference(TH1D* hPtbased, TH1D* hXtbased);
void drawErrorBoxes(TH1 *hist);
void drawBox(Double_t y, Double_t err, Double_t x, Double_t width);
//------------------------

void R_pPb_test()
{

   gROOT->Reset();
   gROOT->ProcessLine(".x rootlogonChristof.C");
   gROOT->ForceStyle();
   gStyle->SetPalette(1);
   gStyle->SetTitleYOffset(1.30);
//   gStyle->SetPadRightMargin(0.16);

   // Get pp referece spectrum - Is this Ed^3sigma/dp^3 or Ed^3N/dp^3
   TFile *f_relativePlacement = new TFile("output_interpolation_KK_LogFitForC6_RelativePlacement.root");
   TFile *f_ppRef_pt = new TFile("output_interpolation_KK_LogFitForC6.root");
   TFile *f_ppRef_xt = new TFile("output_interpolation_KK_LogFitForC6_TryExtrapolationInXT.root");

   TH1D* h_relativePlacement = (TH1D*)f_relativePlacement->Get("h5020_To100GeV_RelativePlacement_BasedOn7TeV");
   convertToYield(h_relativePlacement,70.0); // Sigma_inel at 5.02 TeV

//   TFile *f_ppRef_xt = new TFile("output_interpolation_KK_LogFitForC6_TryExtrapolationInXT_LowerLimit.root");
   TH1D* h_ppRef_LogLogpt = (TH1D*)f_ppRef_pt->Get("h5020_To100GeV_FromLogFit"); //including CDF data
//   TH1D* h_ppRef_LogLogpt = (TH1D*)f_ppRef_pt->Get("h5020_To100GeV_09_7_FromLogFit"); //only CMS data
   convertToYield(h_ppRef_LogLogpt,70.0); // Sigma_inel at 5.02 TeV

   TH1D* h_ppRef_LogLogxt = (TH1D*)f_ppRef_xt->Get("h5020_FromLogFit");
   // Convert the reference to differential yield
   TH1D *h_ppRef_LogLogxt_pt = From_xT_to_pT_histo(h_ppRef_LogLogxt,h_ppRef_LogLogpt,5020.,4.9);
   convertToYield(h_ppRef_LogLogxt_pt,70.0); // Sigma_inel at 5.02 TeV

   //Combined references
   TH1D * combinedRef = singleReference(h_ppRef_LogLogpt,h_ppRef_LogLogxt_pt);

   //Get pPb spectrum
   TFile *f_pPb_JetTriggered = new TFile("PtSpectraCombination_StagedNormalization.root");
   TFile *f_pPb_TrackTriggered = new TFile("TrackTriggerCheck/PtSpectraCombination_StagedNormalization_TrackTrigger.root");
//   TFile *f_pPb_TrackTriggered = new TFile("TrackTriggerCheck/PtSpectraCombination_TrackTrigger.root");
//   TFile *f_pPb_TrackTriggered = new TFile("TrackTriggerCheck/PtSpectraCombination_StagedNormalization_TrackTrigger.root");

   TH1D *hCombined_pPb_JetTriggered = (TH1D*)f_pPb_JetTriggered->Get("hSumPartPt");
   TH1D *hCombined_pPb_TrackTriggered = (TH1D*)f_pPb_TrackTriggered->Get("hSumPartPt");

   //Get binning and resolution correction
   TFile *f_binningAndResol = new TFile("BinningAndResolutionCorrection.root");
   TFile *f_binningAndResol_extendedPt = new TFile("TrackTriggerCheck/BinningAndResolutionCorrection_TrackTrigger.root");
   TH1D *hBinningAndResol = (TH1D*)f_binningAndResol->Get("hPt_pseudo2_copy1");
   TH1D *hBinningAndResol_extendedPt = (TH1D*)f_binningAndResol_extendedPt->Get("hPt_pseudo2_copy1");

   //Apply binning and resolution correction
   hCombined_pPb_JetTriggered->Divide(hBinningAndResol);   
   hCombined_pPb_TrackTriggered->Divide(hBinningAndResol_extendedPt);   

//   float ncoll = 7.9; //Anna's original number for 0-100% DS
   float ncoll = 6.9; //ALICE, this seems to be the pure Glauber number, but not(!) DS

   //PLOTTING
   bool DoSave = true;

   TCanvas *c1 = new TCanvas("c1","c1");
   c1->SetLogy();
   hCombined_pPb_JetTriggered->GetXaxis()->SetTitle("p_{T} [GeV/c]");
   hCombined_pPb_JetTriggered->GetYaxis()->SetTitle("1/N_{ev} dN/dp_{T} (|#eta_{CM}|<1)");
   hCombined_pPb_JetTriggered->SetMarkerStyle(20);
   hCombined_pPb_JetTriggered->SetMinimum(2.*1e-10);
   hCombined_pPb_JetTriggered->Draw();
   hCombined_pPb_TrackTriggered->SetMarkerColor(1);
   hCombined_pPb_TrackTriggered->SetLineColor(1);
   hCombined_pPb_TrackTriggered->SetMarkerStyle(25);
   hCombined_pPb_TrackTriggered->Draw("same");
   h_ppRef_LogLogpt->SetLineColor(2);
   h_ppRef_LogLogpt->Draw("same");
   h_ppRef_LogLogxt_pt->SetLineColor(4);
   h_ppRef_LogLogxt_pt->Draw("same");
   TLegend *leg1 = new TLegend(0.3,0.7,0.8,0.85,NULL,"brNDC");
   leg1->AddEntry(hCombined_pPb_JetTriggered,"Data: pPb, jet-triggered","pl");
   leg1->AddEntry(hCombined_pPb_TrackTriggered,"Data: pPb, track-triggered","pl");
   leg1->AddEntry(h_ppRef_LogLogpt,"pp ref.: p_{T}-based interp.","pl");
   leg1->AddEntry(h_ppRef_LogLogxt_pt,"pp ref.: x_{T}-based interp.","pl");
   leg1->SetFillStyle(0);
   leg1->SetFillColor(0);
   leg1->SetBorderSize(0);
   leg1->Draw();
   if(DoSave) {
      c1->SaveAs("Figs/R_pPb_test_c1.gif");
      c1->SaveAs("Figs/R_pPb_test_c1.eps");
      c1->SaveAs("Figs/R_pPb_test_c1.C");
   }

   TCanvas *c2 = new TCanvas("c2","c2");
   c2->SetLogx();
   TH1D* hCombined_pPb_JetTriggered_copy1 = (TH1D*)hCombined_pPb_JetTriggered->Clone("hCombined_pPb_JetTriggered_copy1");
   TH1D* hCombined_pPb_JetTriggered_copy2 = (TH1D*)hCombined_pPb_JetTriggered->Clone("hCombined_pPb_JetTriggered_copy2");
   TH1D* hCombined_pPb_TrackTriggered_copy1 = (TH1D*)hCombined_pPb_TrackTriggered->Clone("hCombined_pPb_TrackTriggered_copy1");
   TH1D* hCombined_pPb_TrackTriggered_copy2 = (TH1D*)hCombined_pPb_TrackTriggered->Clone("hCombined_pPb_TrackTriggered_copy2");
   hCombined_pPb_JetTriggered_copy1->Scale(1./ncoll);
   hCombined_pPb_JetTriggered_copy2->Scale(1./ncoll);
   hCombined_pPb_TrackTriggered_copy1->Scale(1./ncoll);
   hCombined_pPb_TrackTriggered_copy2->Scale(1./ncoll);
//   TH1D *h_RpPbpt_JetTriggered = divideHistosDiffBins(hCombined_pPb_JetTriggered_copy1,h_ppRef_LogLogpt);
//   TH1D *h_RpPbxt_pt_JetTriggered = divideHistosDiffBins(hCombined_pPb_JetTriggered_copy2,h_ppRef_LogLogxt_pt);
//   TH1D *h_RpPbpt_TrackTriggered = divideHistosDiffBins(hCombined_pPb_TrackTriggered_copy1,h_ppRef_LogLogpt);
//   TH1D *h_RpPbxt_pt_TrackTriggered = divideHistosDiffBins(hCombined_pPb_TrackTriggered_copy2,h_ppRef_LogLogxt_pt);

   TH1D *hCombined_pPb_JetTriggered_copy2 = (TH1D*)hCombined_pPb_JetTriggered_copy1->Clone("hCombined_pPb_JetTriggered_copy2");
   TH1D *h_RpPbpt_JetTriggered = divideHistosDiffBins(hCombined_pPb_JetTriggered_copy1,combinedRef);
   TH1D *h_RpPbpt_TrackTriggered = divideHistosDiffBins(hCombined_pPb_TrackTriggered_copy1,combinedRef);
   TH1D *h_RpPbpt_TrackTriggered_relPlacement = divideHistosDiffBins(hCombined_pPb_TrackTriggered_copy2,h_relativePlacement);
   h_RpPbpt_TrackTriggered->GetXaxis()->SetTitle("p_{T} [GeV/c]");
   h_RpPbpt_TrackTriggered->GetYaxis()->SetTitle("R_{pPb} (|#eta_{CM}|<1)");
   h_RpPbpt_TrackTriggered->SetMinimum(0.);
   h_RpPbpt_TrackTriggered->SetMaximum(1.9);
//   h_RpPbpt_TrackTriggered->GetXaxis()->SetRangeUser(0.,19.);
   h_RpPbpt_TrackTriggered->SetMarkerStyle(20);   
   h_RpPbpt_TrackTriggered->SetMarkerColor(1);   
   h_RpPbpt_TrackTriggered->SetLineColor(1);   
   TH1D* hDum = (TH1D*)h_RpPbpt_TrackTriggered->Clone("hDum");
   hDum->Reset();
//   hDum->GetXaxis()->SetRangeUser(0.,120.);
   hDum->Draw();
   drawErrorBoxes(h_RpPbpt_TrackTriggered);
   h_RpPbpt_TrackTriggered->Draw("same");   
   h_RpPbpt_JetTriggered->SetMarkerStyle(25);   
   h_RpPbpt_JetTriggered->SetMarkerColor(2);   
   h_RpPbpt_JetTriggered->SetLineColor(2);   
   h_RpPbpt_JetTriggered->Draw("same");   

   h_RpPbpt_TrackTriggered_relPlacement->SetMarkerStyle(24);
   h_RpPbpt_TrackTriggered_relPlacement->SetMarkerColor(1);
   h_RpPbpt_TrackTriggered_relPlacement->SetLineColor(1);
//   h_RpPbpt_TrackTriggered_relPlacement->Draw("same");
/*
   h_RpPbxt_pt_JetTriggered->SetMarkerColor(4);   
   h_RpPbxt_pt_JetTriggered->SetLineColor(4);   
   h_RpPbxt_pt_JetTriggered->Draw("same");   
   h_RpPbxt_pt_TrackTriggered->SetMarkerStyle(25);   
   h_RpPbxt_pt_TrackTriggered->SetMarkerColor(4);   
   h_RpPbxt_pt_TrackTriggered->SetLineColor(4);   
   h_RpPbxt_pt_TrackTriggered->Draw("same");   
*/
   TLegend *leg2 = new TLegend(0.3,0.75,0.9,0.9,NULL,"brNDC");
   leg2->AddEntry(h_RpPbpt_TrackTriggered,"Track-triggered spectrum","pl");
   leg2->AddEntry(h_RpPbpt_JetTriggered,"Jet-triggered spectrum","pl");
   leg2->SetFillStyle(0);
   leg2->SetFillColor(0);
   leg2->SetBorderSize(0);
   leg2->Draw();

   TLatex *l1 = new TLatex(0.2,0.2,"N_{coll}=6.9 (Glauber minimum bias N_{coll})");
   l1->SetNDC();
   l1->SetTextSize(0.035);
   l1->Draw();
//   TLatex *l2 = new TLatex(0.2,0.25,"pPb: no resolution/binning correction");
//   l2->SetNDC();
//   l2->SetTextSize(0.035);
//   l2->Draw();
   if(DoSave) {
      c2->SaveAs("Figs/R_pPb_test_c2.gif");
      c2->SaveAs("Figs/R_pPb_test_c2.eps");
      c2->SaveAs("Figs/R_pPb_test_c2.C");
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

TH1D* From_xT_to_pT_histo(TH1D *h_input, TH1D *h_binning, double sqrts, double exp) {

  TH1D *h_pt = (TH1D*)h_binning->Clone("h_pt");
  h_pt->Reset();

  for(int i=1; i<=h_input->GetNbinsX(); i++) {
     double xT = h_input->GetBinCenter(i);
     double content = h_input->GetBinContent(i)/TMath::Power(sqrts,exp);
     double pT = 5020.*xT/2.;
     if(pT>120) break;
     h_pt->SetBinContent(h_pt->FindBin(pT),content);
  }

  return h_pt;
}

TH1D* singleReference(TH1D* hPtbased, TH1D* hXtbased) {
  TH1D* hNewRef = (TH1D*)hXtbased->Clone("hNewRef");
  hNewRef->Reset();
  for(int i=1; i<=hXtbased->GetNbinsX(); i++) {
     double pt = hXtbased->GetBinCenter(i);

     double content_ptbased = hPtbased->GetBinContent(i);
     double error_ptbased = hPtbased->GetBinError(i);

     double content_xtbased = hXtbased->GetBinContent(i);
     double error_xtbased = hXtbased->GetBinError(i);

     double low_th = 13.;
     double high_th = 20.;

     if(pt < low_th) {
       hNewRef->SetBinContent(i,content_ptbased);
       hNewRef->SetBinError(i,error_ptbased);
     }
     else if(pt >= high_th) {
       hNewRef->SetBinContent(i,content_xtbased);
       hNewRef->SetBinError(i,error_xtbased);
     }
     else {
       double newContent = content_ptbased*(high_th-pt)/(high_th-low_th) + (content_xtbased)*(pt-low_th)/(high_th-low_th);
       double newError = error_ptbased*(high_th-pt)/(high_th-low_th) + (error_xtbased)*(pt-low_th)/(high_th-low_th);
       hNewRef->SetBinContent(i,newContent);
       hNewRef->SetBinError(i,newError);
     }
  }
  return hNewRef;
}

void drawErrorBoxes(TH1 *hist) {
  for(int i=1;i <= hist->GetNbinsX();i++){
     double x = hist->GetBinCenter(i);
     double y = hist->GetBinContent(i);
     double w = hist->GetBinWidth(i);

     drawBox(y,0.15,x,w*0.8);
  }
}

void drawBox(Double_t y, Double_t err, Double_t x, Double_t width) {
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

  tg->SetFillColor(kYellow);
  tg->SetLineColor(kYellow);

  tg->SetFillStyle(1001);
  tg->Draw("3");
}
