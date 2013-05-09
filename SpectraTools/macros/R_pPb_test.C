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
   TFile *f_ppRef_pt = new TFile("output_interpolation_KK_LogFitForC6.root");
   TFile *f_ppRef_xt = new TFile("output_interpolation_KK_LogFitForC6_TryExtrapolationInXT.root");
//   TFile *f_ppRef_xt = new TFile("output_interpolation_KK_LogFitForC6_TryExtrapolationInXT_LowerLimit.root");
   TH1D* h_ppRef_LogLogpt = (TH1D*)f_ppRef_pt->Get("h5020_To100GeV_FromLogFit"); //including CDF data
//   TH1D* h_ppRef_LogLogpt = (TH1D*)f_ppRef_pt->Get("h5020_To100GeV_09_7_FromLogFit"); //only CMS data
   TH1D* h_ppRef_LogLogxt = (TH1D*)f_ppRef_xt->Get("h5020_FromLogFit");
   // Convert the reference to differential yield
   convertToYield(h_ppRef_LogLogpt,70.0); // Sigma_inel at 5.02 TeV
   TH1D *h_ppRef_LogLogxt_pt = From_xT_to_pT_histo(h_ppRef_LogLogxt,h_ppRef_LogLogpt,5020.,4.9);
   convertToYield(h_ppRef_LogLogxt_pt,70.0); // Sigma_inel at 5.02 TeV

   //Get pPb spectrum
   TFile *f_pPb = new TFile("PtSpectraCombination.root");
   TH1D *hCombined_pPb = (TH1D*)f_pPb->Get("hSumPartPt");

   //Get binning and resolution correction
   TFile *f_binningAndResol = new TFile("BinningAndResolutionCorrection.root");
   TH1D *hBinningAndResol = (TH1D*)f_binningAndResol->Get("hPt_copy1");

   //Apply binning and resolution correction
   hCombined_pPb->Divide(hBinningAndResol);   

   float ncoll = 7.9;

   //PLOTTING
   bool DoSave = true;

   TCanvas *c1 = new TCanvas("c1","c1");
   c1->SetLogy();
   hCombined_pPb->GetXaxis()->SetTitle("p_{T} [GeV/c]");
   hCombined_pPb->GetYaxis()->SetTitle("1/N_{ev} dN/dp_{T} (|#eta|<1)");
   hCombined_pPb->SetMarkerStyle(20);
   hCombined_pPb->SetMinimum(2.*1e-10);
   hCombined_pPb->Draw();
   h_ppRef_LogLogpt->SetLineColor(2);
   h_ppRef_LogLogpt->Draw("same");
   h_ppRef_LogLogxt_pt->SetLineColor(4);
   h_ppRef_LogLogxt_pt->Draw("same");
   TLegend *leg1 = new TLegend(0.3,0.7,0.8,0.85,NULL,"brNDC");
   leg1->AddEntry(hCombined_pPb,"pPb","pl");
   leg1->AddEntry(h_ppRef_LogLogpt,"pp reference, p_{T}-based interp.","pl");
   leg1->AddEntry(h_ppRef_LogLogxt_pt,"pp reference, x_{T}-based interp.","pl");
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
   TH1D* hCombined_pPb_copy1 = (TH1D*)hCombined_pPb->Clone("hCombined_pPb_copy1");
   TH1D* hCombined_pPb_copy2 = (TH1D*)hCombined_pPb->Clone("hCombined_pPb_copy2");
   hCombined_pPb_copy1->Scale(1./ncoll);
   hCombined_pPb_copy2->Scale(1./ncoll);
   TH1D *h_RpPbpt = divideHistosDiffBins(hCombined_pPb_copy1,h_ppRef_LogLogpt);
   TH1D *h_RpPbxt_pt = divideHistosDiffBins(hCombined_pPb_copy2,h_ppRef_LogLogxt_pt);
   h_RpPbpt->GetXaxis()->SetTitle("p_{T} [GeV/c]");
   h_RpPbpt->GetYaxis()->SetTitle("R_{pPb}");
   h_RpPbpt->SetMinimum(0.);
   h_RpPbpt->SetMaximum(1.2);
   h_RpPbpt->SetMarkerColor(2);   
   h_RpPbpt->SetLineColor(2);   
   h_RpPbpt->Draw();   
   h_RpPbxt_pt->SetMarkerColor(4);   
   h_RpPbxt_pt->SetLineColor(4);   
   h_RpPbxt_pt->Draw("same");   
   TLatex *l1 = new TLatex(0.2,0.3,"N_{coll}=7.9");
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

