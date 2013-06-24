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

TH1D* divideHistosDiffBins(TH1D* h_Num, TH1D* h_Den);
TH1D* singleReference(TH1D* hPtbased, TH1D* hXtbased);
TGraphErrors* drawErrorBoxes(TH1 *hist);
void drawBox(Double_t y, Double_t err, Double_t x, Double_t width, Int_t color);
void convertToYield(TH1D* h_ppRef_LogLogpt, float sigma_inel);
TH1D* From_xT_to_pT_histo(TH1D *h_input, TH1D *h_binning, double sqrts, double exp);
std::pair<TGraphErrors*,TGraphErrors*> readInData(char * name);
void drawTickError(TH1 *hist, TGraphErrors *tg);
void drawTick(Double_t Y, Double_t Erru, Double_t Errd, Double_t X, Double_t Tick_x, Double_t Tick_y, Int_t TickColor);
//------------------------

void R_pPb_test()
{
   gROOT->Reset();
   gROOT->ProcessLine(".x rootlogonChristof.C");
   gROOT->ForceStyle();
   gStyle->SetPalette(1);
   gStyle->SetTitleYOffset(1.30);
//   gStyle->SetPadRightMargin(0.16);
   gStyle->SetErrorX(0);
//   gStyle->SetEndErrorSize(10.);

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
   TFile *f_CombpPbPbp_TrackTriggered = new TFile("TrackTriggerCheck/PtSpectraCombination_StagedNormalization_NoOLDAlignmentRuns_CombpPbPbp_TrackTrigger.root");
   TFile *f_pPb_TrackTriggered = new TFile("TrackTriggerCheck/PtSpectraCombination_StagedNormalization_NoOLDAlignmentRuns_TrackTrigger.root");
   TFile *f_Pbp_TrackTriggered = new TFile("TrackTriggerCheck/Asym/ReverseBeam/PtSpectraCombination_StagedNormalization_TrackTrigger.root");

   TH1D *hCombined_pPb_JetTriggered = (TH1D*)f_pPb_JetTriggered->Get("hSumPartPt");
   TH1D *hCombined_CombpPbPbp_TrackTriggered = (TH1D*)f_CombpPbPbp_TrackTriggered->Get("hSumPartPt");
   TH1D *hCombined_pPb_TrackTriggered = (TH1D*)f_pPb_TrackTriggered->Get("hSumPartPt");
   TH1D *hCombined_Pbp_TrackTriggered = (TH1D*)f_Pbp_TrackTriggered->Get("hSumPartPt");

   //Get binning and resolution correction
   TFile *f_binningAndResol = new TFile("BinningAndResolutionCorrection.root");
   TFile *f_binningAndResol_extendedPt = new TFile("TrackTriggerCheck/BinningAndResolutionCorrection_TrackTrigger.root");
   TH1D *hBinningAndResol = (TH1D*)f_binningAndResol->Get("hPt_pseudo2_copy1");
   TH1D *hBinningAndResol_extendedPt = (TH1D*)f_binningAndResol_extendedPt->Get("hPt_pseudo2_copy1");

   //Apply binning and resolution correction
   hCombined_pPb_JetTriggered->Divide(hBinningAndResol);   
   hCombined_CombpPbPbp_TrackTriggered->Divide(hBinningAndResol_extendedPt);   
   hCombined_pPb_TrackTriggered->Divide(hBinningAndResol_extendedPt);   
   hCombined_Pbp_TrackTriggered->Divide(hBinningAndResol_extendedPt);   

//   float ncoll = 7.9; //Anna's original number for 0-100% DS
   float ncoll = 6.9; //ALICE, this seems to be the pure Glauber number, but not(!) DS

   //PLOTTING
   bool DoSave = true;

   TCanvas *c1 = new TCanvas("c1","c1");
   c1->cd();
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
   c2->cd();
   c2->SetLogx();
   TH1D* hCombined_pPb_JetTriggered_copy1 = (TH1D*)hCombined_pPb_JetTriggered->Clone("hCombined_pPb_JetTriggered_copy1");
   TH1D* hCombined_CombpPbPbp_TrackTriggered_copy1 = (TH1D*)hCombined_CombpPbPbp_TrackTriggered->Clone("hCombined_CombpPbPbp_TrackTriggered_copy1");
   TH1D* hCombined_pPb_TrackTriggered_copy1 = (TH1D*)hCombined_pPb_TrackTriggered->Clone("hCombined_pPb_TrackTriggered_copy1");
   TH1D* hCombined_pPb_TrackTriggered_copy2 = (TH1D*)hCombined_pPb_TrackTriggered->Clone("hCombined_pPb_TrackTriggered_copy2");
   TH1D* hCombined_Pbp_TrackTriggered_copy1 = (TH1D*)hCombined_Pbp_TrackTriggered->Clone("hCombined_Pbp_TrackTriggered_copy1");
   hCombined_pPb_JetTriggered_copy1->Scale(1./ncoll);
   hCombined_CombpPbPbp_TrackTriggered_copy1->Scale(1./ncoll);
   hCombined_pPb_TrackTriggered_copy1->Scale(1./ncoll);
   hCombined_pPb_TrackTriggered_copy2->Scale(1./ncoll);
   hCombined_Pbp_TrackTriggered_copy1->Scale(1./ncoll);

   TH1D *h_RpPbpt_JetTriggered = divideHistosDiffBins(hCombined_pPb_JetTriggered_copy1,combinedRef);
   TH1D *h_RCombpPbPbppt_TrackTriggered = divideHistosDiffBins(hCombined_CombpPbPbp_TrackTriggered_copy1,combinedRef);
   TH1D *h_RpPbpt_TrackTriggered = divideHistosDiffBins(hCombined_pPb_TrackTriggered_copy1,combinedRef);
   TH1D *h_RPbppt_TrackTriggered = divideHistosDiffBins(hCombined_Pbp_TrackTriggered_copy1,combinedRef);
//   TH1D *h_RpPbpt_TrackTriggered_relPlacement = divideHistosDiffBins(hCombined_pPb_TrackTriggered_copy2,h_relativePlacement);
   h_RCombpPbPbppt_TrackTriggered->GetXaxis()->SetTitle("p_{T} [GeV/c]");
   h_RCombpPbPbppt_TrackTriggered->GetYaxis()->SetTitle("R_{pPb} (|#eta_{CM}|<1)");
   h_RCombpPbPbppt_TrackTriggered->SetMinimum(0.);
   h_RCombpPbPbppt_TrackTriggered->SetMaximum(2.0);
   h_RCombpPbPbppt_TrackTriggered->SetMarkerStyle(20);   
   h_RCombpPbPbppt_TrackTriggered->SetMarkerColor(1);   
   h_RCombpPbPbppt_TrackTriggered->SetLineColor(1);   
   TH1D* hDum = (TH1D*)h_RCombpPbPbppt_TrackTriggered->Clone("hDum");
   hDum->Reset();
   hDum->Draw();
   TGraphErrors* h_RCombpPbPbppt_TrackTriggered_sys = drawErrorBoxes(h_RCombpPbPbppt_TrackTriggered);
   drawTickError(h_RCombpPbPbppt_TrackTriggered,h_RCombpPbPbppt_TrackTriggered_sys);
   h_RCombpPbPbppt_TrackTriggered->Draw("same");   
   h_RpPbpt_JetTriggered->SetMarkerStyle(25);   
   h_RpPbpt_JetTriggered->SetMarkerColor(2);   
   h_RpPbpt_JetTriggered->SetLineColor(2);   
   h_RpPbpt_JetTriggered->Draw("same");   

//   h_RpPbpt_TrackTriggered_relPlacement->SetMarkerStyle(24);
//   h_RpPbpt_TrackTriggered_relPlacement->SetMarkerColor(1);
//   h_RpPbpt_TrackTriggered_relPlacement->SetLineColor(1);
//   h_RpPbpt_TrackTriggered_relPlacement->Draw("same");

   TLegend *leg2 = new TLegend(0.3,0.78,0.9,0.93,NULL,"brNDC");
   leg2->AddEntry(h_RCombpPbPbppt_TrackTriggered,"Track-triggered spectrum","pl");
   leg2->AddEntry(h_RpPbpt_JetTriggered,"Jet-triggered spectrum (inc. old align. runs)","pl");
   leg2->SetFillStyle(0);
   leg2->SetFillColor(0);
   leg2->SetBorderSize(0);
   leg2->Draw();

   TLatex *l2 = new TLatex(0.2,0.2,"N_{coll}=6.9 (Glauber minimum bias N_{coll})");
   l2->SetNDC();
   l2->SetTextSize(0.035);
   l2->Draw();
   if(DoSave) {
      c2->SaveAs("Figs/R_pPb_test_c2.gif");
      c2->SaveAs("Figs/R_pPb_test_c2.eps");
      c2->SaveAs("Figs/R_pPb_test_c2.C");
   }


   //Comparison of the pPb and Pbp spectra
   TCanvas *c2a = new TCanvas("c2a","c2a");
   c2a->cd();
   c2a->SetLogx();
   hDum->Draw();
   TGraphErrors* h_RCombpPbPbppt_TrackTriggered_sys_lemma = drawErrorBoxes(h_RCombpPbPbppt_TrackTriggered);
   drawTickError(h_RCombpPbPbppt_TrackTriggered,h_RCombpPbPbppt_TrackTriggered_sys_lemma);
   h_RCombpPbPbppt_TrackTriggered->Draw("same");
   h_RpPbpt_TrackTriggered->SetMarkerStyle(24);
   h_RpPbpt_TrackTriggered->SetMarkerColor(4);
   h_RpPbpt_TrackTriggered->SetLineColor(4);
   h_RpPbpt_TrackTriggered->Draw("same");
   h_RPbppt_TrackTriggered->SetMarkerStyle(24);
   h_RPbppt_TrackTriggered->SetMarkerColor(6);
   h_RPbppt_TrackTriggered->SetLineColor(6);
   h_RPbppt_TrackTriggered->Draw("same");
   TLegend *leg2a = new TLegend(0.3,0.78,0.9,0.93,NULL,"brNDC");
   leg2a->AddEntry(h_RCombpPbPbppt_TrackTriggered,"Track-triggered spectrum, pPb+Pbp combined","pl");
   leg2a->AddEntry(h_RpPbpt_TrackTriggered,"Track-triggered spectrum, pPb","pl");
   leg2a->AddEntry(h_RPbppt_TrackTriggered,"Track-triggered spectrum, Pbp","pl");
   leg2a->SetFillStyle(0);
   leg2a->SetFillColor(0);
   leg2a->SetBorderSize(0);
   leg2a->Draw();
   l2->Draw();
   if(DoSave) {
      c2a->SaveAs("Figs/R_pPb_test_c2a.gif");
      c2a->SaveAs("Figs/R_pPb_test_c2a.eps");
      c2a->SaveAs("Figs/R_pPb_test_c2a.C");
   }


   TCanvas *c2ai = new TCanvas("c2ai","c2ai");
   c2ai->cd();
   c2ai->SetLogx();
   hDum->Draw();
   TGraphErrors* h_RCombpPbPbppt_TrackTriggered_sys_lemma2 = drawErrorBoxes(h_RCombpPbPbppt_TrackTriggered);
   drawTickError(h_RCombpPbPbppt_TrackTriggered,h_RCombpPbPbppt_TrackTriggered_sys_lemma2);
   h_RCombpPbPbppt_TrackTriggered->Draw("same");
   drawBox(1.,0.06,0.6,0.15,17);
   TLegend *leg2ai = new TLegend(0.2,0.78,0.9,0.93,NULL,"brNDC");
   leg2ai->AddEntry(h_RCombpPbPbppt_TrackTriggered,"pPb #sqrt{s_{NN}} = 5.02 TeV, charged particles","pl");
   leg2ai->SetFillStyle(0);
   leg2ai->SetFillColor(0);
   leg2ai->SetBorderSize(0);
   leg2ai->Draw();
   TLatex *prel = new TLatex(0.2,0.25,"CMS Preliminary");
   TLatex *l2ai = new TLatex(0.2,0.2,"N_{coll}=6.9");
   l2ai->SetNDC();
   prel->SetNDC();
   l2ai->SetTextSize(0.035);
   prel->SetTextSize(0.035);
   l2ai->Draw();
   prel->Draw();
   if(DoSave) {
      c2ai->SaveAs("Figs/R_pPb_test_c2ai.gif");
      c2ai->SaveAs("Figs/R_pPb_test_c2ai.eps");
      c2ai->SaveAs("Figs/R_pPb_test_c2ai.C");
   }


   TCanvas *c3 = new TCanvas("c3","c3");
   c3->cd();
   TH1D* h_RCombpPbPbppt_TrackTriggered_copy1 = (TH1D*)h_RCombpPbPbppt_TrackTriggered->Clone("h_RCombpPbPbppt_TrackTriggered_copy1");
   TH1D* h_RpPbpt_JetTriggered_copy1 = (TH1D*)h_RpPbpt_JetTriggered->Clone("h_RpPbpt_JetTriggered_copy1");
   TH1D *hDum_copy1 = (TH1D*)hDum->Clone("hDum_copy1");
   hDum_copy1->GetXaxis()->SetRangeUser(0.,120.);
   hDum_copy1->Draw();
   TGraphErrors* h_RCombpPbPbppt_TrackTriggered_copy1_sys = drawErrorBoxes(h_RCombpPbPbppt_TrackTriggered_copy1);
   drawTickError(h_RCombpPbPbppt_TrackTriggered_copy1,h_RCombpPbPbppt_TrackTriggered_copy1_sys);
   h_RCombpPbPbppt_TrackTriggered_copy1->Draw("same");      
   h_RpPbpt_JetTriggered_copy1->Draw("same");      
   leg2->Draw();
   if(DoSave) {
      c3->SaveAs("Figs/R_pPb_test_c3.gif");
      c3->SaveAs("Figs/R_pPb_test_c3.eps");
      c3->SaveAs("Figs/R_pPb_test_c3.C");
   }


   TCanvas *c4 = new TCanvas("c4","c4");
   c4->cd();
   c4->SetLogx();
   char * name_ALICE_RpPb = "ALICE_RpPb_EtaCMS03.dat";
   TGraphErrors *gALICE_stat_RpPb = readInData(name_ALICE_RpPb).first;   
   TGraphErrors *gALICE_syst_RpPb = readInData(name_ALICE_RpPb).second;   
   TH1D* h_RCombpPbPbppt_TrackTriggered_copy2 = (TH1D*)h_RCombpPbPbppt_TrackTriggered->Clone("h_RCombpPbPbppt_TrackTriggered_copy2");
   TH1D *hDum_copy2 = (TH1D*)hDum->Clone("hDum_copy2");
   hDum_copy2->GetYaxis()->SetTitle("R_{pPb}");
   hDum_copy2->Draw();
   TGraphErrors* h_RCombpPbPbppt_TrackTriggered_copy2_sys = drawErrorBoxes(h_RCombpPbPbppt_TrackTriggered_copy2);
   drawTickError(h_RCombpPbPbppt_TrackTriggered_copy2,h_RCombpPbPbppt_TrackTriggered_copy2_sys);
   h_RCombpPbPbppt_TrackTriggered_copy2->Draw("same");
   gALICE_syst_RpPb->SetMarkerColor(4);
   gALICE_syst_RpPb->SetLineColor(4);
   gALICE_syst_RpPb->Draw("[]same");
   gALICE_stat_RpPb->SetMarkerStyle(20);
   gALICE_stat_RpPb->SetMarkerColor(4);
   gALICE_stat_RpPb->SetLineColor(4);
   gALICE_stat_RpPb->Draw("psame");
   TLegend *leg4 = new TLegend(0.4,0.75,0.8,0.9,NULL,"brNDC");
   leg4->AddEntry(h_RCombpPbPbppt_TrackTriggered_copy2,"CMS, |#eta_{CM}|<1","pl");
   leg4->AddEntry(gALICE_stat_RpPb, "ALICE, |#eta_{CM}|<0.3","pl");
   leg4->SetFillStyle(0);
   leg4->SetFillColor(0);
   leg4->SetBorderSize(0);
   leg4->Draw();
   if(DoSave) {
      c4->SaveAs("Figs/R_pPb_test_c4.gif");
      c4->SaveAs("Figs/R_pPb_test_c4.eps");
      c4->SaveAs("Figs/R_pPb_test_c4.C");
   }


   TCanvas *c5 = new TCanvas("c5","c5");
   c5->cd();
   TH1D *hDum_copy3 = (TH1D*)hDum_copy2->Clone("hDum_copy3");
   hDum_copy3->GetXaxis()->SetRangeUser(0.,19.);
   hDum_copy3->Draw();
   TGraphErrors* h_RCombpPbPbppt_TrackTriggered_copy2_sys_inst2 = drawErrorBoxes(h_RCombpPbPbppt_TrackTriggered_copy2);
   drawTickError(h_RCombpPbPbppt_TrackTriggered_copy2,h_RCombpPbPbppt_TrackTriggered_copy2_sys_inst2);
   h_RCombpPbPbppt_TrackTriggered_copy2->Draw("same");
   gALICE_syst_RpPb->Draw("[]same");
   gALICE_stat_RpPb->Draw("psame");
   leg4->Draw();
   if(DoSave) {
      c5->SaveAs("Figs/R_pPb_test_c5.gif");
      c5->SaveAs("Figs/R_pPb_test_c5.eps");
      c5->SaveAs("Figs/R_pPb_test_c5.C");
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

     double low_th = 12.5;
     double high_th = 13.5;//20.

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


TGraphErrors* drawErrorBoxes(TH1 *hist) {

  Float_t pt[hist->GetNbinsX()], yield[hist->GetNbinsX()], pterror[hist->GetNbinsX()], yielderror[hist->GetNbinsX()];
  for(int i=1;i <= hist->GetNbinsX();i++){
     double x = hist->GetBinCenter(i);
     double y = hist->GetBinContent(i);
     double w = hist->GetBinWidth(i);

     Double_t err = 0.;

     if(x<1.0)
       err = 0.102;
     else if(x<2.0)
       err = 0.106;
     else if(x<3.2)
       err = 0.118;
     else if(x<24.)
       err = 0.143;
     else
       err = 0.181;

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


std::pair<TGraphErrors*,TGraphErrors*> readInData(char * name) {

  std::ifstream data(name,ios_base::in);
  if(data.is_open())
     cout << "Reading..." << endl;

  Float_t pt[45], yield[45], pterror[45], yielderror_stat[45], yielderror_syst[45];
  Float_t pt_lemma, yield_lemma, yielderror_stat_lemma, yielderror_syst_lemma;
  for(Int_t j=0;j<45;j++) {
     data >> pt_lemma;
     pt[j] = pt_lemma;
     data >> yield_lemma;
     yield[j] = yield_lemma;
     data >> yielderror_stat_lemma;
     yielderror_stat[j] = yielderror_stat_lemma;
     data >> yielderror_syst_lemma;
     yielderror_syst[j] = yielderror_syst_lemma;

     pterror[j] = 0.;
  }

  TGraphErrors *gALICE_stat = new TGraphErrors(45,pt,yield,pterror,yielderror_stat);
  TGraphErrors *gALICE_syst = new TGraphErrors(45,pt,yield,pterror,yielderror_syst);
  return std::pair<TGraphErrors*,TGraphErrors*>(gALICE_stat,gALICE_syst);
}


void drawTickError(TH1 *hist, TGraphErrors *tg) {

  for(int i=0;i<hist->GetNbinsX();i++){
    double x = hist->GetBinCenter(i+1);
    double y = hist->GetBinContent(i+1);
    double w = hist->GetBinWidth(i+1);
//    drawTick(Double_t Y, Double_t Erru, Double_t Errd, Double_t X, Double_t Tick_x, Double_t Tick_y, Int_t TickColor)
    if(y>0.1) //not to draw lines for empty bins
       drawTick(y,tg->GetErrorY(i),tg->GetErrorY(i),x,0.015,0.3*w,1);
  }
}


void drawTick(Double_t Y, Double_t Erru, Double_t Errd, Double_t X, Double_t Tick_x, Double_t Tick_y, Int_t TickColor) {

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

