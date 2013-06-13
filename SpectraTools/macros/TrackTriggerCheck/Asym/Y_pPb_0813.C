#include <TROOT.h>
#include <TStyle.h>
#include <TFile.h>
#include <TH1D.h>
#include <TNtuple.h>
#include <iostream>
#include <TLegend.h>
#include <TLatex.h>

void Y_pPb_0813()
{
   gROOT->Reset();
   gROOT->ProcessLine(".x rootlogonChristof.C");
   gROOT->ForceStyle();
   gStyle->SetPalette(1);
   gStyle->SetTitleYOffset(1.30);
//   gStyle->SetPadRightMargin(0.16);

   //Get pPb spectrum
   TFile *f_pPb_EtaCM_P08_P13 = new TFile("PtSpectraCombination_StagedNormalization_EtaCM_P08_P13_TrackTrigger.root");
   TH1D *hSpectrum_EtaCM_P08_P13 = (TH1D*)f_pPb_EtaCM_P08_P13->Get("hSumPartPt");
//   TH1D *hSpectrum_EtaCM_P08_P13 = (TH1D*)f_pPb_EtaCM_P08_P13->Get("hPartPt_minbias_trkCorr_trigCorr");
//   TH1D* hNumEv_minbias_0308 = (TH1D*)f_pPb_EtaCM_P08_P13->Get("hNumEv_minbias_trigCorr");
//   float numev_minbias_0308 = hNumEv_minbias_0308->GetBinContent(1);

   TFile *f_pPb_EtaCM_M08_M13 = new TFile("PtSpectraCombination_StagedNormalization_EtaCM_M08_M13_TrackTrigger.root");
   TH1D *hSpectrum_EtaCM_M08_M13 = (TH1D*)f_pPb_EtaCM_M08_M13->Get("hSumPartPt");
//   TH1D *hSpectrum_EtaCM_M08_M13 = (TH1D*)f_pPb_EtaCM_M08_M13->Get("hPartPt_minbias_trkCorr_trigCorr");
//   TH1D* hNumEv_minbias_M03M08 = (TH1D*)f_pPb_EtaCM_M08_M13->Get("hNumEv_minbias_trigCorr");
//   float numev_minbias_M03M08 = hNumEv_minbias_M03M08->GetBinContent(1);

   //cross-check:
//   std::cerr<<" event 0308  : " << numev_minbias_0308 << std::endl;
//   std::cerr<<" event M03M08: " << numev_minbias_M03M08 << std::endl;

   //normalization
//   hSpectrum_EtaCM_P08_P13->Scale(1./numev_minbias_0308);
//   hSpectrum_EtaCM_M08_M13->Scale(1./numev_minbias_M03M08);


   //PLOTTING
   bool DoSave = true;

   TCanvas *c1 = new TCanvas("c1","c1");
   c1->SetLogy();
   hSpectrum_EtaCM_P08_P13->GetXaxis()->SetTitle("p_{T} [GeV/c]");
   hSpectrum_EtaCM_P08_P13->GetYaxis()->SetTitle("1/N_{ev} dN/dp_{T}");
   hSpectrum_EtaCM_P08_P13->SetMarkerStyle(20);
   hSpectrum_EtaCM_P08_P13->Draw();
   hSpectrum_EtaCM_M08_M13->SetMarkerStyle(20);
   hSpectrum_EtaCM_M08_M13->SetMarkerColor(4);
   hSpectrum_EtaCM_M08_M13->SetLineColor(4);
   hSpectrum_EtaCM_M08_M13->Draw("same");
   TLegend *leg1 = new TLegend(0.4,0.7,0.8,0.85,NULL,"brNDC");
   leg1->AddEntry(hSpectrum_EtaCM_P08_P13,"pPb, 0.8<#eta_{CM}<1.3","pl");
   leg1->AddEntry(hSpectrum_EtaCM_M08_M13,"pPb, -1.3<#eta_{CM}<-0.8","pl");
   leg1->SetFillStyle(0);
   leg1->SetFillColor(0);
   leg1->SetBorderSize(0);
   leg1->Draw();
   if(DoSave) {
      c1->SaveAs("Figs/Y_pPb_0813_c1.gif");
      c1->SaveAs("Figs/Y_pPb_0813_c1.eps");
      c1->SaveAs("Figs/Y_pPb_0813_c1.C");
   }

   TCanvas *c2 = new TCanvas("c2","c2");
   c2->SetLogx();
   TH1D* hSpectrum_EtaCM_P08_P13_copy1 = (TH1D*)hSpectrum_EtaCM_P08_P13->Clone("hSpectrum_EtaCM_P08_P13_copy1");
   hSpectrum_EtaCM_P08_P13_copy1->Divide(hSpectrum_EtaCM_M08_M13);
   hSpectrum_EtaCM_P08_P13_copy1->GetYaxis()->SetTitle("Y_{asym}");
   hSpectrum_EtaCM_P08_P13_copy1->SetMinimum(0.2);
   hSpectrum_EtaCM_P08_P13_copy1->SetMaximum(1.9);
   hSpectrum_EtaCM_P08_P13_copy1->GetXaxis()->SetRangeUser(0.,100.);
   hSpectrum_EtaCM_P08_P13_copy1->Draw();   
   TLegend *leg2 = new TLegend(0.43,0.08,0.93,0.33,NULL,"brNDC");
   leg2->AddEntry(hSpectrum_EtaCM_P08_P13_copy1,"Y_{asym} = #frac{dN/dp_{T}(0.8<#eta_{CM}<1.3)}{dN/dp_{T}(-1.3<#eta_{CM}<-0.8)}","");
   leg2->SetFillStyle(0);
   leg2->SetFillColor(0);
   leg2->SetBorderSize(0);
   leg2->Draw();
   TPad *c2_zoom = new TPad("c2_zoom","c2_zoom",0.57,0.57,0.95,0.95);
   c2_zoom->SetFillStyle(0);
   c2_zoom->Draw();
   c2_zoom->cd();
   TH1D* hSpectrum_EtaCM_P08_P13_copy2 = (TH1D*)hSpectrum_EtaCM_P08_P13_copy1->Clone("hSpectrum_EtaCM_P08_P13_copy2");
   hSpectrum_EtaCM_P08_P13_copy2->SetMinimum(0.);
   hSpectrum_EtaCM_P08_P13_copy2->SetMaximum(1.45);
   hSpectrum_EtaCM_P08_P13_copy2->GetXaxis()->SetRangeUser(0.,14.);
   hSpectrum_EtaCM_P08_P13_copy2->Draw();
   if(DoSave) {
      c2->SaveAs("Figs/Y_pPb_0813_c2.gif");
      c2->SaveAs("Figs/Y_pPb_0813_c2.eps");
      c2->SaveAs("Figs/Y_pPb_0813_c2.C");
   }

   TCanvas *c3 = new TCanvas("c3","c3");
   c3->cd();
   TH1D * hSpectrum_EtaCM_P08_P13_copy3 = hSpectrum_EtaCM_P08_P13_copy2->Clone("hSpectrum_EtaCM_P08_P13_copy3");
   hSpectrum_EtaCM_P08_P13_copy3->Draw();
}
