{
#include <iostream>
#include <fstream>
#include "divide_graph_by_function.C"
using namespace std;

  gROOT->Reset();
  gROOT->ProcessLine(".x rootlogonChristof.C");
  gStyle->SetOptLogy(0);
  gROOT->ForceStyle();
  gStyle->SetTitleYOffset(1.26);

  bool doSave = true;

  TFile *f_ours = new TFile("CombineSpectra_minbias_Eta01.root");
  TH1D * hNumEv_minbias = (TH1D*)f_ours->Get("hNumEv_minbias_trigCorr");
  TH1D * hSpectrum_minbias = (TH1D*)f_ours->Get("hPartPt_minbias_trkCorr_trigCorr");
  float numev_minbias = hNumEv_minbias->GetBinContent(1);
  hSpectrum_minbias->Scale(1./numev_minbias); //events
  hSpectrum_minbias->Scale(1./0.1); //eta normalization

  ifstream
  infile("Ferenc_UnidentifiedSpectrum.dat");
  if(infile.is_open())
     cout << "Reading..." << endl;

  Float_t pt_lemma, yield_lemma, yielderror_lemma;
  Float_t pt[23], yield[23], pterror[23], yielderror[23];
  for(Int_t j=0;j<23;j++) {
     infile >> pt_lemma;
     pt[j] = pt_lemma;
     infile >> yield_lemma;
     yield[j] = yield_lemma;
     infile >> yielderror_lemma;
     yielderror[j] = yielderror_lemma;
     
     pterror[j] = 0.;
  }


  //Plotting
  hSpectrum_minbias->SetMarkerStyle(24);
  hSpectrum_minbias->GetXaxis()->SetRangeUser(0.,1.8);
  hSpectrum_minbias->GetXaxis()->SetTitle("p_{T} [GeV/c]");
  hSpectrum_minbias->GetYaxis()->SetTitle("1/N d^{2}N/d#etadp_{T} (0<|#eta_{lab}|<0.1)");
  TF1 *f1 = new TF1("f1","[0]*(1.+x/[1])^[2]",0.4,2.0);
  f1->SetParameters(1,1,-7.);
  hSpectrum_minbias->SetStats(0);
  hSpectrum_minbias->Fit("f1","REM");
//  hSpectrum_minbias->Draw();

  TGraphErrors *gFerenc = new TGraphErrors(23,pt,yield,pterror,yielderror);
  gFerenc->SetMarkerStyle(20);
  gFerenc->SetMarkerSize(1.4);
  gFerenc->SetLineColor(2);
  gFerenc->SetMarkerColor(2);
  gFerenc->Draw("psame");

   TLegend *leg1 = new TLegend(0.5,0.57,0.93,0.75,NULL,"brNDC");
   leg1->AddEntry(hSpectrum_minbias,"HIN-12-017","pl");
   leg1->AddEntry(gFerenc,"HIN-12-016","pl");
   leg1->SetFillStyle(0);
   leg1->SetFillColor(0);
   leg1->SetBorderSize(0);
   leg1->Draw();
   if(doSave) {
      c1->SaveAs("Figs/CompareToFerenc_c1.gif");
      c1->SaveAs("Figs/CompareToFerenc_c1.eps");
      c1->SaveAs("Figs/CompareToFerenc_c1.C");
   }

  
  TCanvas *c2 = new TCanvas("c2","c2");
  c2->cd();
  TH1D *hSpectrum_minbias_copy1 = (TH1D*)hSpectrum_minbias->Clone("hSpectrum_minbias_copy1");
  TGraphErrors *gFerenc_copy1 = (TGraphErrors*)gFerenc->Clone("gFerenc_copy1");
  TF1 * f1_copy1 = (TF1*)f1->Clone("f1_copy1");

  hSpectrum_minbias_copy1->Divide(f1_copy1);
  hSpectrum_minbias_copy1->SetMinimum(0.8);
  hSpectrum_minbias_copy1->SetMaximum(1.2);
  hSpectrum_minbias_copy1->GetYaxis()->SetTitle("Measurement / Fit");
  hSpectrum_minbias_copy1->Draw();

  TGraphErrors* gRatio = divide_graph_by_function(gFerenc_copy1,f1_copy1);
  gRatio->SetMarkerStyle(20);
  gRatio->SetMarkerColor(2);
  gRatio->SetLineColor(2);
  gRatio->SetMarkerSize(1.4);
  gRatio->Draw("psame");

   TLegend *leg2 = new TLegend(0.5,0.57,0.93,0.75,NULL,"brNDC");
   leg2->AddEntry(hSpectrum_minbias,"HIN-12-017","pl");
   leg2->AddEntry(gFerenc,"HIN-12-016","pl");
   leg2->SetFillStyle(0);
   leg2->SetFillColor(0);
   leg2->SetBorderSize(0);
   leg2->Draw();
   if(doSave) {
      c2->SaveAs("Figs/CompareToFerenc_c2.gif");
      c2->SaveAs("Figs/CompareToFerenc_c2.eps");
      c2->SaveAs("Figs/CompareToFerenc_c2.C");
   }

}
