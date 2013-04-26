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

void PtSpectraCombination()
{
   gROOT->Reset();
   gROOT->ProcessLine(".x rootlogonChristof.C");
   gROOT->ForceStyle();
   gStyle->SetPalette(1);
   gStyle->SetTitleYOffset(1.27);
   gStyle->SetOptFit(0000);
//   gStyle->SetPadRightMargin(0.16);

   bool doSave = true;

   TFile *f_minbias = new TFile("CombineSpectra_minbias.root");
   TFile *f_40_60 = new TFile("CombineSpectra_40_60.root");
   TFile *f_80_100 = new TFile("CombineSpectra_80_100.root");
   TFile *f_out = new TFile("PtSpectraCombination.root","recreate");

   //Get spectra
   TH1D* hPartPt_minbias_corrected = (TH1D*)f_minbias->Get("hPartPt_minbias_trkCorr_trigCorr");
   TH1D* hPartPt_0_60_minbias_corrected = (TH1D*)f_minbias->Get("hPartPt_0_60_minbias_trkCorr_trigCorr");
   TH1D* hPartPt_60_75_Jet40_corrected = (TH1D*)f_40_60->Get("hPartPt_60_75_Jet40_corrected");
   TH1D* hPartPt_75_95_Jet60_corrected = (TH1D*)f_40_60->Get("hPartPt_75_95_Jet60_corrected");
   TH1D* hPartPt_95_120_Jet80_corrected = (TH1D*)f_80_100->Get("hPartPt_95_120_Jet80_corrected");
   TH1D* hPartPt_120_X_Jet100_corrected = (TH1D*)f_80_100->Get("hPartPt_120_X_Jet100_corrected");

   hPartPt_0_60_minbias_corrected->SetBinContent(hPartPt_0_60_minbias_corrected->FindBin(103.24),0);//Remove muon event
   hPartPt_0_60_minbias_corrected->SetBinError(hPartPt_0_60_minbias_corrected->FindBin(103.24),0);//Remove muon event
   hPartPt_minbias_corrected->SetBinContent(hPartPt_minbias_corrected->FindBin(103.24),0);//Remove muon event
   hPartPt_minbias_corrected->SetBinError(hPartPt_minbias_corrected->FindBin(103.24),0);//Remove muon event

   //Get number of events
   TH1D* hNumEv_minbias = (TH1D*)f_minbias->Get("hNumEv_minbias_trigCorr");
   TH1D* hNumEv_0_60_minbias = (TH1D*)f_minbias->Get("hNumEv_0_60_minbias_trigCorr");
   TH1D* hNumEv_60_75_minbias = (TH1D*)f_minbias->Get("hNumEv_60_75_minbias");
   TH1D* hNumEv_75_95_minbias = (TH1D*)f_minbias->Get("hNumEv_75_95_minbias");
   TH1D* hNumEv_95_120_minbias = (TH1D*)f_minbias->Get("hNumEv_95_120_minbias");
   TH1D* hNumEv_120_X_minbias = (TH1D*)f_minbias->Get("hNumEv_120_X_minbias");
   TH1D* hNumEv_60_75_Jet40 = (TH1D*)f_40_60->Get("hNumEv_60_75_Jet40");
   TH1D* hNumEv_75_95_Jet60 = (TH1D*)f_40_60->Get("hNumEv_75_95_Jet60");
   TH1D* hNumEv_95_120_Jet80 = (TH1D*)f_80_100->Get("hNumEv_95_120_Jet80");
   TH1D* hNumEv_120_X_Jet100 = (TH1D*)f_80_100->Get("hNumEv_120_X_Jet100");

   float numev_minbias = hNumEv_minbias->GetBinContent(1);
   float numev_0_60_minbias = hNumEv_0_60_minbias->GetBinContent(1);
   float numev_60_75_minbias = hNumEv_60_75_minbias->GetBinContent(1);
   float numev_75_95_minbias = hNumEv_75_95_minbias->GetBinContent(1);
   float numev_95_120_minbias = hNumEv_95_120_minbias->GetBinContent(1);
   float numev_120_X_minbias = hNumEv_120_X_minbias->GetBinContent(1);
   float numev_60_75_Jet40 = hNumEv_60_75_Jet40->GetBinContent(1);
   float numev_75_95_Jet60 = hNumEv_75_95_Jet60->GetBinContent(1);
   float numev_95_120_Jet80 = hNumEv_95_120_Jet80->GetBinContent(1);
   float numev_120_X_Jet100 = hNumEv_120_X_Jet100->GetBinContent(1);

   std::cerr<<" Number of minbias events in the normalization classes:" << std::endl;
   std::cerr<<"   All: " << numev_minbias << std::endl;
   std::cerr<<"      : " << numev_0_60_minbias << std::endl;
   std::cerr<<"      : " << numev_60_75_minbias << std::endl;
   std::cerr<<"      : " << numev_75_95_minbias << std::endl;
   std::cerr<<"      : " << numev_95_120_minbias << std::endl;
   std::cerr<<"      : " << numev_120_X_minbias << std::endl;

   //Prepare the individual normalizations
   float norm_0_60_minbias = numev_minbias;
   float norm_60_75_Jet40 = numev_60_75_Jet40*numev_minbias/numev_60_75_minbias;
   float norm_75_95_Jet60 = numev_75_95_Jet60*numev_minbias/numev_75_95_minbias;
   float norm_95_120_Jet80 = numev_95_120_Jet80*numev_minbias/numev_95_120_minbias;
   float norm_120_X_Jet100 = numev_120_X_Jet100*numev_minbias/numev_120_X_minbias;

   hPartPt_minbias_corrected->Scale(1./numev_minbias);
   hPartPt_0_60_minbias_corrected->Scale(1./norm_0_60_minbias);
   hPartPt_60_75_Jet40_corrected->Scale(1./norm_60_75_Jet40);
   hPartPt_75_95_Jet60_corrected->Scale(1./norm_75_95_Jet60);
   hPartPt_95_120_Jet80_corrected->Scale(1./norm_95_120_Jet80);
   hPartPt_120_X_Jet100_corrected->Scale(1./norm_120_X_Jet100);

   TCanvas *c1 = new TCanvas("c1","c1");
   c1->cd();
   c1->SetLogy();
   hPartPt_0_60_minbias_corrected->GetXaxis()->CenterTitle();
   hPartPt_0_60_minbias_corrected->GetYaxis()->CenterTitle();
   hPartPt_0_60_minbias_corrected->GetXaxis()->SetTitle("p_{T} [GeV/c]");
   hPartPt_0_60_minbias_corrected->GetYaxis()->SetTitle("1/N_{ev} dN/dp_{T} (|#eta|<1)");
//   hPartPt_0_60_minbias_corrected->SetNdivisions(505);
   hPartPt_0_60_minbias_corrected->SetMarkerColor(42);
   hPartPt_0_60_minbias_corrected->SetLineColor(42);
   hPartPt_0_60_minbias_corrected->SetMarkerStyle(34);
   hPartPt_0_60_minbias_corrected->SetMinimum(1e-11);
   hPartPt_0_60_minbias_corrected->SetFillColor(42);
//   hPartPt_0_60_minbias_corrected->SetFillStyle(3305);
   hPartPt_0_60_minbias_corrected->Draw("hist");

   hPartPt_minbias_corrected->SetMarkerStyle(20);
   hPartPt_minbias_corrected->Draw("same");

   hPartPt_60_75_Jet40_corrected->SetMarkerColor(3);
   hPartPt_60_75_Jet40_corrected->SetLineColor(3);
   hPartPt_60_75_Jet40_corrected->SetMarkerStyle(24);
   hPartPt_60_75_Jet40_corrected->SetFillColor(3);
   hPartPt_60_75_Jet40_corrected->SetFillStyle(3315);
   hPartPt_60_75_Jet40_corrected->Draw("samehist");

   hPartPt_75_95_Jet60_corrected->SetMarkerColor(6);
   hPartPt_75_95_Jet60_corrected->SetLineColor(6);
   hPartPt_75_95_Jet60_corrected->SetMarkerStyle(20);
   hPartPt_75_95_Jet60_corrected->SetFillColor(6);
   hPartPt_75_95_Jet60_corrected->SetFillStyle(3395);
   hPartPt_75_95_Jet60_corrected->Draw("samehist");

   hPartPt_95_120_Jet80_corrected->SetMarkerColor(4);
   hPartPt_95_120_Jet80_corrected->SetLineColor(4);
   hPartPt_95_120_Jet80_corrected->SetMarkerStyle(24);
   hPartPt_95_120_Jet80_corrected->SetFillColor(4);
   hPartPt_95_120_Jet80_corrected->SetFillStyle(3353);
   hPartPt_95_120_Jet80_corrected->Draw("samehist");

   hPartPt_120_X_Jet100_corrected->SetMarkerColor(2);
   hPartPt_120_X_Jet100_corrected->SetLineColor(2);
   hPartPt_120_X_Jet100_corrected->SetMarkerStyle(20);
//   hPartPt_120_X_Jet100_corrected->SetFillColor(2);
//   hPartPt_120_X_Jet100_corrected->SetFillStyle(3002);
   hPartPt_120_X_Jet100_corrected->Draw("samehist");

   //Sum
   TH1D * hSumPartPt = (TH1D*)hPartPt_0_60_minbias_corrected->Clone("hSumPartPt");
   hSumPartPt->Add(hPartPt_60_75_Jet40_corrected);
   hSumPartPt->Add(hPartPt_75_95_Jet60_corrected);
   hSumPartPt->Add(hPartPt_95_120_Jet80_corrected);
   hSumPartPt->Add(hPartPt_120_X_Jet100_corrected);
   hSumPartPt->SetMarkerStyle(25);
   hSumPartPt->SetMarkerColor(1);
   hSumPartPt->SetLineColor(1);
   hSumPartPt->Draw("same");

   TLegend *leg1 = new TLegend(0.48,0.47,0.93,0.95,NULL,"brNDC");
   leg1->AddEntry(hPartPt_minbias_corrected,"MinBias, all","pl");
   leg1->AddEntry(hPartPt_0_60_minbias_corrected,"MinBias, Jet E_{T}<60 GeV/c","f");
   leg1->AddEntry(hPartPt_60_75_Jet40_corrected,"Jet40, 60<Jet E_{T}<75 GeV/c","f");
   leg1->AddEntry(hPartPt_75_95_Jet60_corrected,"Jet60, 75<Jet E_{T}<95 GeV/c","f");
   leg1->AddEntry(hPartPt_95_120_Jet80_corrected,"Jet80, 95<Jet E_{T}<120 GeV/c","f");
   leg1->AddEntry(hPartPt_120_X_Jet100_corrected,"Jet100, 120<Jet E_{T} GeV/c","l");
   leg1->AddEntry(hSumPartPt,"Combined","pl");
   leg1->SetFillStyle(0);
   leg1->SetFillColor(0);
   leg1->SetBorderSize(0);
   leg1->Draw();
   if(doSave) {
      c1->SaveAs("Figs/PtSpectraCombination_c1.gif");
      c1->SaveAs("Figs/PtSpectraCombination_c1.eps");
      c1->SaveAs("Figs/PtSpectraCombination_c1.C");
   }


   TCanvas *c2 = new TCanvas("c2","c2");
   c2->cd();
   TH1D *hSumPartPt_copy1 = (TH1D*)hSumPartPt->Clone("hSumPartPt_copy1");
   hSumPartPt_copy1->Divide(hPartPt_minbias_corrected);
   hSumPartPt_copy1->GetYaxis()->SetTitle("Combined / MB all");
   hSumPartPt_copy1->Draw();
   if(doSave) {
      c2->SaveAs("Figs/PtSpectraCombination_c2.gif");
      c2->SaveAs("Figs/PtSpectraCombination_c2.eps");
      c2->SaveAs("Figs/PtSpectraCombination_c2.C");
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
