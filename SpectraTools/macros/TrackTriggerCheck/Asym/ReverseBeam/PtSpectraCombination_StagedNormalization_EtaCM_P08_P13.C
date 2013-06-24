#include <TROOT.h>
#include <TStyle.h>
#include <TFile.h>
#include <TH1D.h>
#include <TNtuple.h>
#include <TCanvas.h>
#include <iostream>
#include <TLegend.h>

void normalizeByBinWidth(TH1D *histo);
//------------------------

void PtSpectraCombination_StagedNormalization_EtaCM_P08_P13()
{
   gROOT->Reset();
   gROOT->ProcessLine(".x rootlogonChristof.C");
   gROOT->ForceStyle();
   gStyle->SetPalette(1);
   gStyle->SetTitleYOffset(1.27);
   gStyle->SetOptFit(0000);
//   gStyle->SetPadRightMargin(0.16);

   bool doSave = true;

   TFile *f_minbias = new TFile("CombineSpectra_minbias_EtaCM_P08_P13.root");
   TFile *f_FullTrack_12 = new TFile("CombineSpectra_FullTrackTrigger_Track12_EtaCM_P08_P13.root");
   TFile *f_FullTrack_20 = new TFile("CombineSpectra_FullTrackTrigger_Track20_EtaCM_P08_P13.root");
   TFile *f_FullTrack_30_50 = new TFile("CombineSpectra_FullTrackTrigger_Track30_Track50_EtaCM_P08_P13.root");
   TFile *f_out = new TFile("PtSpectraCombination_StagedNormalization_EtaCM_P08_P13_TrackTrigger.root","recreate");

   //Get spectra
   TH1D* hPartPt_minbias_corrected = (TH1D*)f_minbias->Get("hPartPt_minbias_trkCorr_trigCorr");
   TH1D* hPartPt_0_14_minbias_corrected = (TH1D*)f_minbias->Get("hPartPt_0_14_minbias_trkCorr_trigCorr");
   TH1D* hPartPt_14_22_FullTrack12_corrected = (TH1D*)f_FullTrack_12->Get("hPartPt_FullTrack12_14_22_trkCorr_trigCorr");
   TH1D* hPartPt_22_32_FullTrack20_corrected = (TH1D*)f_FullTrack_20->Get("hPartPt_FullTrack20_22_32_trkCorr_trigCorr");
   TH1D* hPartPt_32_X_FullTrack30_corrected = (TH1D*)f_FullTrack_30_50->Get("hPartPt_FullTrack30_SpectComb_trkCorr_trigCorr");

   hPartPt_0_14_minbias_corrected->SetBinContent(hPartPt_0_14_minbias_corrected->FindBin(103.24),0);//Remove muon event
   hPartPt_0_14_minbias_corrected->SetBinError(hPartPt_0_14_minbias_corrected->FindBin(103.24),0);//Remove muon event
   hPartPt_minbias_corrected->SetBinContent(hPartPt_minbias_corrected->FindBin(103.24),0);//Remove muon event
   hPartPt_minbias_corrected->SetBinError(hPartPt_minbias_corrected->FindBin(103.24),0);//Remove muon event

   //Get number of events
   TH1D* hNumEv_minbias = (TH1D*)f_minbias->Get("hNumEv_minbias_trigCorr");
   TH1D* hNumEv_0_14_minbias = (TH1D*)f_minbias->Get("hNumEv_0_14_minbias_trigCorr");
   TH1D* hNumEv_14_22_minbias = (TH1D*)f_minbias->Get("hNumEv_14_22_minbias_trigCorr");
   TH1D* hNumEv_14_22_FullTrack12 = (TH1D*)f_FullTrack_12->Get("hNumEv_FullTrack12_14_22_trigCorr");
   TH1D* hNumEv_22_32_FullTrack12 = (TH1D*)f_FullTrack_12->Get("hNumEv_FullTrack12_22_32_trigCorr");
   TH1D* hNumEv_22_32_FullTrack20 = (TH1D*)f_FullTrack_20->Get("hNumEv_FullTrack20_22_32_trigCorr");
   TH1D* hNumEv_32_X_FullTrack20 = (TH1D*)f_FullTrack_20->Get("hNumEv_FullTrack20_32_X_trigCorr");
   TH1D* hNumEv_32_X_FullTrack30 = (TH1D*)f_FullTrack_30_50->Get("hNumEv_FullTrack30_32_X_trigCorr");

   float numev_minbias = hNumEv_minbias->GetBinContent(1);
   float numev_0_14_minbias = hNumEv_0_14_minbias->GetBinContent(1);
   float numev_14_22_minbias = hNumEv_14_22_minbias->GetBinContent(1);
   float numev_14_22_FullTrack12 = hNumEv_14_22_FullTrack12->GetBinContent(1);
   float numev_22_32_FullTrack12 = hNumEv_22_32_FullTrack12->GetBinContent(1);
   float numev_22_32_FullTrack20 = hNumEv_22_32_FullTrack20->GetBinContent(1);
   float numev_32_X_FullTrack20 = hNumEv_32_X_FullTrack20->GetBinContent(1);
   float numev_32_X_FullTrack30 = hNumEv_32_X_FullTrack30->GetBinContent(1);

   std::cerr<<" Number of minbias events in the normalization classes:" << std::endl;
   std::cerr<<"   All      : " << numev_minbias << std::endl;
   std::cerr<<"    0-14 MB : " << numev_0_14_minbias << std::endl;
   std::cerr<<"   14-22 MB : " << numev_14_22_minbias << std::endl;
   std::cerr<<"   14-22 T12: " << numev_14_22_FullTrack12 << std::endl;
   std::cerr<<"   22-32 T12: " << numev_22_32_FullTrack12 << std::endl;
   std::cerr<<"   22-32 T20: " << numev_22_32_FullTrack20 << std::endl;
   std::cerr<<"   32-X  T20: " << numev_32_X_FullTrack20 << std::endl;
   std::cerr<<"   32-X  T30: " << numev_32_X_FullTrack30 << std::endl;

   //Prepare the individual normalizations
   float norm_0_14_minbias = numev_minbias;
   float norm_14_22_FullTrack12 = numev_14_22_FullTrack12*numev_minbias/numev_14_22_minbias;
//   float norm_14_22_FullTrack12 = numev_14_22_FullTrack12*11165.040;
   float norm_22_32_FullTrack20 = norm_14_22_FullTrack12*numev_22_32_FullTrack20/numev_22_32_FullTrack12;
   float norm_32_X_FullTrack30 = norm_22_32_FullTrack20*numev_32_X_FullTrack30/numev_32_X_FullTrack20;

   std::cerr<<"Normalization factors:" << std::endl;
   std::cerr<<"      norm_0_14_minbias     : " << norm_0_14_minbias << std::endl;
   std::cerr<<"      norm_14_22_FullTrack12: " << norm_14_22_FullTrack12 << std::endl;
   std::cerr<<"      norm_22_32_FullTrack20: " << norm_22_32_FullTrack20 << std::endl;
   std::cerr<<"      norm_32_X_FullTrack30 : " << norm_32_X_FullTrack30 << std::endl;

   hPartPt_minbias_corrected->Scale(1./numev_minbias);
   hPartPt_0_14_minbias_corrected->Scale(1./norm_0_14_minbias);
   hPartPt_14_22_FullTrack12_corrected->Scale(1./norm_14_22_FullTrack12);
   hPartPt_22_32_FullTrack20_corrected->Scale(1./norm_22_32_FullTrack20);
   hPartPt_32_X_FullTrack30_corrected->Scale(1./norm_32_X_FullTrack30);

   TCanvas *c1 = new TCanvas("c1","c1");
   c1->cd();
   c1->SetLogy();
   hPartPt_0_14_minbias_corrected->GetXaxis()->CenterTitle();
   hPartPt_0_14_minbias_corrected->GetYaxis()->CenterTitle();
   hPartPt_0_14_minbias_corrected->GetXaxis()->SetTitle("p_{T} [GeV/c]");
   hPartPt_0_14_minbias_corrected->GetYaxis()->SetTitle("1/N_{ev} dN/dp_{T} (|#eta_{CM}|<1)");
//   hPartPt_0_14_minbias_corrected->SetNdivisions(505);
   hPartPt_0_14_minbias_corrected->SetMarkerColor(42);
   hPartPt_0_14_minbias_corrected->SetLineColor(42);
   hPartPt_0_14_minbias_corrected->SetMarkerStyle(34);
   hPartPt_0_14_minbias_corrected->SetMinimum(1e-11);
   hPartPt_0_14_minbias_corrected->SetFillColor(42);
//   hPartPt_0_14_minbias_corrected->SetFillStyle(3305);
   hPartPt_0_14_minbias_corrected->Draw("hist");

   hPartPt_minbias_corrected->SetMarkerStyle(20);
   hPartPt_minbias_corrected->Draw("same");

   hPartPt_14_22_FullTrack12_corrected->SetMarkerColor(2);
   hPartPt_14_22_FullTrack12_corrected->SetLineColor(2);
   hPartPt_14_22_FullTrack12_corrected->SetMarkerStyle(20);
   hPartPt_14_22_FullTrack12_corrected->SetFillColor(2);
   hPartPt_14_22_FullTrack12_corrected->SetFillStyle(3002);
   hPartPt_14_22_FullTrack12_corrected->Draw("same");

   hPartPt_22_32_FullTrack20_corrected->SetMarkerColor(4);
   hPartPt_22_32_FullTrack20_corrected->SetLineColor(4);
   hPartPt_22_32_FullTrack20_corrected->SetMarkerStyle(20);
//   hPartPt_22_32_FullTrack20_corrected->SetFillColor(2);
//   hPartPt_22_32_FullTrack20_corrected->SetFillStyle(3002);
   hPartPt_22_32_FullTrack20_corrected->Draw("samehist");

   hPartPt_32_X_FullTrack30_corrected->SetMarkerColor(2);
   hPartPt_32_X_FullTrack30_corrected->SetLineColor(2);
   hPartPt_32_X_FullTrack30_corrected->SetMarkerStyle(20);
//   hPartPt_32_X_FullTrack30_corrected->SetFillColor(2);
//   hPartPt_32_X_FullTrack30_corrected->SetFillStyle(3002);
   hPartPt_32_X_FullTrack30_corrected->Draw("samehist");

   //Sum
   TH1D * hSumPartPt = (TH1D*)hPartPt_0_14_minbias_corrected->Clone("hSumPartPt");
   hSumPartPt->Add(hPartPt_14_22_FullTrack12_corrected);
   hSumPartPt->Add(hPartPt_22_32_FullTrack20_corrected);
   hSumPartPt->Add(hPartPt_32_X_FullTrack30_corrected);
   hSumPartPt->SetMarkerStyle(25);
   hSumPartPt->SetMarkerColor(1);
   hSumPartPt->SetLineColor(1);
   hSumPartPt->Draw("same");

   TLegend *leg1 = new TLegend(0.48,0.47,0.93,0.95,NULL,"brNDC");
   leg1->AddEntry(hPartPt_minbias_corrected,"MinBias, inclusive","pl");
   leg1->AddEntry(hPartPt_0_14_minbias_corrected,"MinBias, p_{T}<14 GeV/c","f");
   leg1->AddEntry(hPartPt_14_22_FullTrack12_corrected,"FullTrack12, 14<p_{T}<22 GeV/c","pl");
   leg1->AddEntry(hPartPt_22_32_FullTrack20_corrected,"FullTrack20, 22<p_{T}<32 GeV/c","l");
   leg1->AddEntry(hPartPt_32_X_FullTrack30_corrected,"FullTrack30, 32<p_{T} GeV/c","l");
   leg1->AddEntry(hSumPartPt,"Combined spectrum","pl");
   leg1->SetFillStyle(0);
   leg1->SetFillColor(0);
   leg1->SetBorderSize(0);
   leg1->Draw();
   if(doSave) {
      c1->SaveAs("Figs/PtSpectraCombination_StagedNormalization_EtaCM_P08_P13_c1.gif");
      c1->SaveAs("Figs/PtSpectraCombination_StagedNormalization_EtaCM_P08_P13_c1.eps");
      c1->SaveAs("Figs/PtSpectraCombination_StagedNormalization_EtaCM_P08_P13_c1.C");
   }


   TCanvas *c2 = new TCanvas("c2","c2");
   c2->cd();
   TH1D *hSumPartPt_copy1 = (TH1D*)hSumPartPt->Clone("hSumPartPt_copy1");
   hSumPartPt_copy1->Divide(hPartPt_minbias_corrected);
   hSumPartPt_copy1->GetYaxis()->SetTitle("Combined spectrum / MB inclusive");
   hSumPartPt_copy1->Draw();

   TLatex *inf1 = new TLatex(0.33,0.17,"Combined spectrum: from track triggers");
   inf1->SetNDC();
   inf1->SetTextSize(0.035);
   inf1->Draw();

   TPad *c2_zoom = new TPad("c2_zoom","c2_zoom",0.56,0.56,0.94,0.93);
   c2_zoom->SetFillStyle(0);
   c2_zoom->SetLogx();
   c2_zoom->Draw();
   c2_zoom->cd();
   TH1D *hSumPartPt_copy2 = (TH1D*)hSumPartPt_copy1->Clone("hSumPartPt_copy2");
   hSumPartPt_copy2->GetXaxis()->CenterTitle();
   hSumPartPt_copy2->GetYaxis()->CenterTitle();
   hSumPartPt_copy2->GetXaxis()->SetTitle("p_{T} [GeV/c]");
   hSumPartPt_copy2->GetYaxis()->SetTitle("Combined spectrum / MB inclusive ");
   hSumPartPt_copy2->GetXaxis()->SetRangeUser(0.,18.);
   hSumPartPt_copy2->SetMinimum(0.95);
   hSumPartPt_copy2->SetMaximum(1.05);
   hSumPartPt_copy2->Draw();
   if(doSave) {
      c2->SaveAs("Figs/PtSpectraCombination_StagedNormalization_EtaCM_P08_P13_c2.gif");
      c2->SaveAs("Figs/PtSpectraCombination_StagedNormalization_EtaCM_P08_P13_c2.eps");
      c2->SaveAs("Figs/PtSpectraCombination_StagedNormalization_EtaCM_P08_P13_c2.C");
   }

/*
   TLegend *leg2 = new TLegend(0.80,0.75,0.95,0.95,NULL,"brNDC");
   leg2->AddEntry(hPartPt_Jet40_copy1,"Jet40","pl");
   leg2->AddEntry(hPartPt_Jet60_copy1,"Jet60","pl");
   leg2->AddEntry(hPartPt_Jet80_copy1,"Jet80","pl");
   leg2->AddEntry(hPartPt_Jet100_copy1,"Jet100","pl");
   leg2->SetFillStyle(0);
   leg2->SetFillColor(0);
   leg2->SetBorderSize(0);
   leg2->Draw();
*/
   
  f_out->cd();
  hSumPartPt->Write();
  f_out->Close();

}

void normalizeByBinWidth(TH1D *histo) {
   for(int i = 1; i <= histo->GetNbinsX(); i++) {
      float content = histo->GetBinContent(i);
      float error = histo->GetBinError(i);
      histo->SetBinContent(i,content/histo->GetBinWidth(i));
      histo->SetBinError(i,error/histo->GetBinWidth(i));
   }
}
