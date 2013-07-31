{
  #include "vector.h"

  gROOT->Reset();
  gROOT->ProcessLine(".x rootlogon.C");
  gROOT->ForceStyle();

  gStyle->SetPalette(1);
//  gStyle->SetPadRightMargin(0.16);

  TFile f_1("test_orig_3layer.root");
  TFile f_2("test_90_3layer.root");
  TFile f_3("test_95_3layer.root");

  TNtuple * nTriplets_1 = (TNtuple*)f_1.Get("nTriplets");
  TNtuple * nPairs_1 = (TNtuple*)f_1.Get("nPairs");
  TNtuple * nTriplets_2 = (TNtuple*)f_2.Get("nTriplets");
  TNtuple * nPairs_2 = (TNtuple*)f_2.Get("nPairs");
  TNtuple * nTriplets_3 = (TNtuple*)f_3.Get("nTriplets");
  TNtuple * nPairs_3 = (TNtuple*)f_3.Get("nPairs");

  TH1F * hTriplets_lemma = new TH1F("hTriplets_lemma","hTriplets_lemma",6,-3.,3.);
  TH1F * hTriplets_1D_1 = new TH1F("hTriplets_1D_1","hTriplets_1D_1",6,-3.,3.);
  TH1F * hPairs_1D_1 = new TH1F("hPairs_1D_1","hPairs_1D_1",6,-3.,3.);
  TH1F * hTriplets_1D_2 = new TH1F("hTriplets_1D_2","hTriplets_1D_2",6,-3.,3.);
  TH1F * hPairs_1D_2 = new TH1F("hPairs_1D_2","hPairs_1D_2",6,-3.,3.);
  TH1F * hTriplets_1D_3 = new TH1F("hTriplets_1D_3","hTriplets_1D_3",6,-3.,3.);
  TH1F * hPairs_1D_3 = new TH1F("hPairs_1D_3","hPairs_1D_3",6,-3.,3.);

  nTriplets_1->Project("hTriplets_lemma","eta","fabs(eta)<2.");
  nTriplets_1->Project("hTriplets_1D_1","eta","fabs(eta)<2.");
  nPairs_1->Project("hPairs_1D_1","eta","fabs(eta)<2.");
  nTriplets_2->Project("hTriplets_1D_2","eta","fabs(eta)<2.");
  nPairs_2->Project("hPairs_1D_2","eta","fabs(eta)<2.");
  nTriplets_3->Project("hTriplets_1D_3","eta","fabs(eta)<2.");
  nPairs_3->Project("hPairs_1D_3","eta","fabs(eta)<2.");

  hTriplets_lemma->Sumw2();
  hTriplets_1D_1->Sumw2();
  hTriplets_1D_2->Sumw2();
  hTriplets_1D_3->Sumw2();

  hTriplets_lemma->Divide(hPairs_1D_1);
  hTriplets_1D_1->Divide(hPairs_1D_1);

  hTriplets_1D_2->Divide(hPairs_1D_2);

  hTriplets_1D_3->Divide(hPairs_1D_3);

  hTriplets_1D_2->Divide(hTriplets_1D_1);

  hTriplets_1D_3->Divide(hTriplets_lemma);

  hTriplets_1D_2->SetMaximum(1.1);
  hTriplets_1D_2->GetXaxis()->SetTitle("#eta");
  hTriplets_1D_2->GetYaxis()->SetTitle("Hit efficiency");
  hTriplets_1D_2->Draw();

  hTriplets_1D_3->SetLineColor(2);
  hTriplets_1D_3->Draw("same");

  TLegend *leg6 = new TLegend(0.25,0.15,0.75,0.45,NULL,"brNDC");
  leg6->AddEntry(hTriplets_1D_2,"hit eff.: 90%","L");
  leg6->AddEntry(hTriplets_1D_3,"hit eff.: 95%","L");

  leg6->SetFillStyle(0);
  leg6->SetFillColor(0);
  leg6->SetBorderSize(0);
  leg6->Draw();
}
