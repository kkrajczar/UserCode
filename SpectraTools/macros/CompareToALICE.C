#include "divide_graph_by_function.C"

void normalizeBy2PiPt(TH1D *hist);
TGraphErrors *gALICE(char *name);
void plotSpectrum(TH1D * cms, TGraphErrors *alice, char * yaxis);
void plotRatio(TH1D * cms, TGraphErrors *alice, char *yaxis);


void CompareToALICE () {

  gROOT->Reset();
  gROOT->ProcessLine(".x rootlogonChristof.C");
  gStyle->SetOptLogy(0);
  gROOT->ForceStyle();
  gStyle->SetTitleYOffset(1.26);

  bool doSave = true;

  TFile *f_CMS03 = new TFile("CombineSpectra_minbias_EtaCMS03.root");
  TFile *f_CMS0308 = new TFile("CombineSpectra_minbias_EtaCMS0308.root");
  TFile *f_CMS0813 = new TFile("CombineSpectra_minbias_EtaCMS0813.root");

  TH1D * hnumev_minbias_CMS03 = (TH1D*)f_CMS03->Get("hNumEv_minbias_trigCorr");
  TH1D * hnumev_minbias_CMS0308 = (TH1D*)f_CMS0308->Get("hNumEv_minbias_trigCorr");
  TH1D * hnumev_minbias_CMS0813 = (TH1D*)f_CMS0813->Get("hNumEv_minbias_trigCorr");
  TH1D * hSpectrum_minbias_CMS03 = (TH1D*)f_CMS03->Get("hPartPt_minbias_trkCorr_trigCorr");
  TH1D * hSpectrum_minbias_CMS0308 = (TH1D*)f_CMS0308->Get("hPartPt_minbias_trkCorr_trigCorr");
  TH1D * hSpectrum_minbias_CMS0813 = (TH1D*)f_CMS0813->Get("hPartPt_minbias_trkCorr_trigCorr");

  float numev_minbias_CMS03 = hnumev_minbias_CMS03->GetBinContent(1);
  hSpectrum_minbias_CMS03->Scale(1./numev_minbias_CMS03); //events
  hSpectrum_minbias_CMS03->Scale(1./(0.6)); //eta normalization
  normalizeBy2PiPt(hSpectrum_minbias_CMS03);

  float numev_minbias_CMS0308 = hnumev_minbias_CMS0308->GetBinContent(1);
  hSpectrum_minbias_CMS0308->Scale(1./numev_minbias_CMS0308); //events
  hSpectrum_minbias_CMS0308->Scale(1./(0.5)); //eta normalization
  normalizeBy2PiPt(hSpectrum_minbias_CMS0308);

  float numev_minbias_CMS0813 = hnumev_minbias_CMS0813->GetBinContent(1);
  hSpectrum_minbias_CMS0813->Scale(1./numev_minbias_CMS0813); //events
  hSpectrum_minbias_CMS0813->Scale(1./(0.5)); //eta normalization
  normalizeBy2PiPt(hSpectrum_minbias_CMS0813);

  char * name_ALICE_CMS03 = "ALICE_EtaCMS03.dat";
  char * name_ALICE_CMS0308 = "ALICE_EtaCMS0308.dat";
  char * name_ALICE_CMS0813 = "ALICE_EtaCMS0813.dat";
  char * eta_CMS03 = "|#eta_{CMS}|<0.3";
  char * eta_CMS0308 = "0.3<|#eta_{CMS}|<0.8";
  char * eta_CMS0813 = "0.8<|#eta_{CMS}|<1.3";


  //Plotting
  TCanvas *c1 = new TCanvas("c1","c1");
  c1->cd();
  c1->SetLogy();

  TGraphErrors *gALICE_CMS03 = readInData(name_ALICE_CMS03);
  plotSpectrum(hSpectrum_minbias_CMS03, gALICE_CMS03, eta_CMS03);
  if(doSave) {
     c1->SaveAs("Figs/CompareToALICE_c1.gif");
     c1->SaveAs("Figs/CompareToALICE_c1.eps");
     c1->SaveAs("Figs/CompareToALICE_c1.C");
  }

  
  TCanvas *c2 = new TCanvas("c2","c2");
  c2->cd();
  plotRatio(hSpectrum_minbias_CMS03, gALICE_CMS03, eta_CMS03);
  if(doSave) {
     c2->SaveAs("Figs/CompareToALICE_c2.gif");
     c2->SaveAs("Figs/CompareToALICE_c2.eps");
     c2->SaveAs("Figs/CompareToALICE_c2.C");
  }


  TCanvas *c3 = new TCanvas("c3","c3");
  c3->cd();
  c3->SetLogy();

  TGraphErrors *gALICE_CMS0308 = readInData(name_ALICE_CMS0308);
  plotSpectrum(hSpectrum_minbias_CMS0308, gALICE_CMS0308, eta_CMS0308);
  if(doSave) {
     c3->SaveAs("Figs/CompareToALICE_c3.gif");
     c3->SaveAs("Figs/CompareToALICE_c3.eps");
     c3->SaveAs("Figs/CompareToALICE_c3.C");
  }

  
  TCanvas *c4 = new TCanvas("c4","c4");
  c4->cd();
  plotRatio(hSpectrum_minbias_CMS0308, gALICE_CMS0308, eta_CMS0308);
  if(doSave) {
     c4->SaveAs("Figs/CompareToALICE_c4.gif");
     c4->SaveAs("Figs/CompareToALICE_c4.eps");
     c4->SaveAs("Figs/CompareToALICE_c4.C");
  }


  TCanvas *c5 = new TCanvas("c5","c5");
  c5->cd();
  c5->SetLogy();

  TGraphErrors *gALICE_CMS0813 = readInData(name_ALICE_CMS0813);
  plotSpectrum(hSpectrum_minbias_CMS0813, gALICE_CMS0813, eta_CMS0813);
  if(doSave) {
     c5->SaveAs("Figs/CompareToALICE_c5.gif");
     c5->SaveAs("Figs/CompareToALICE_c5.eps");
     c5->SaveAs("Figs/CompareToALICE_c5.C");
  }

  
  TCanvas *c6 = new TCanvas("c6","c6");
  c6->cd();
  plotRatio(hSpectrum_minbias_CMS0813, gALICE_CMS0813, eta_CMS0813);
  if(doSave) {
     c6->SaveAs("Figs/CompareToALICE_c6.gif");
     c6->SaveAs("Figs/CompareToALICE_c6.eps");
     c6->SaveAs("Figs/CompareToALICE_c6.C");
  }

}


void normalizeBy2PiPt(TH1D *hist) {

  for(int i=1; i<=hist->GetNbinsX(); i++) {
     double pT = hist->GetBinCenter(i);
     double content = hist->GetBinContent(i);
     double error = hist->GetBinError(i);
     hist->SetBinContent(i,content/(2.*TMath::Pi()*pT));
     hist->SetBinError(i,error/(2.*TMath::Pi()*pT));
  }
}


TGraphErrors * readInData(char * name) {

  ifstream data(name);
  if(data.is_open())
     cout << "Reading..." << endl;

  Float_t pt[45], yield[45], pterror[45], yielderror[45];
  Float_t pt_lemma, yield_lemma, yielderror_lemma;
  for(Int_t j=0;j<45;j++) {
     data >> pt_lemma;
     pt[j] = pt_lemma;
     data >> yield_lemma;
     yield[j] = yield_lemma;
     data >> yielderror_lemma;
     yielderror[j] = yielderror_lemma;

     pterror[j] = 0.;
  }

  TGraphErrors *gALICE = new TGraphErrors(45,pt,yield,pterror,yielderror);
  return gALICE;
}


void plotSpectrum(TH1D * cms, TGraphErrors *alice, char * yaxis) {

  cms->SetMarkerStyle(24);
  cms->GetXaxis()->SetRangeUser(0.,18.0);
  cms->GetXaxis()->SetTitle("p_{T} [GeV/c]");
  cms->GetYaxis()->SetTitle(Form("1/N 1/(2#pi p_{T})d^{2}N/d#etadp_{T} (%s)",yaxis));
  TF1 *f1 = new TF1("f1","[0]*(1.+x/[1])^[2]",0.4,18.0);
  f1->SetParameters(1,1,-7.);
  cms->SetStats(0);
  cms->Fit("f1","REM0");
  cms->Draw();
  TF1 * f1_lemma = cms->GetFunction("f1");
  f1_lemma->Draw("same");

  alice->SetMarkerStyle(20);
  alice->SetMarkerSize(1.4);
  alice->SetLineColor(2);
  alice->SetMarkerColor(2);
  alice->Draw("psame");

  TLegend *leg1 = new TLegend(0.17,0.15,0.6,0.33,NULL,"brNDC");
  leg1->AddEntry(cms,"HIN-12-017","pl");
  leg1->AddEntry(alice,"ALICE","pl");
  leg1->SetFillStyle(0);
  leg1->SetFillColor(0);
  leg1->SetBorderSize(0);
  leg1->Draw();

  TPad *c1_zoom = new TPad("c1_zoom","c1_zoom",0.46,0.46,0.94,0.93);
  c1_zoom->SetFillStyle(0);
  c1_zoom->Draw();
  c1_zoom->cd();
  TH1D* cms_zoomed = (TH1D*)cms->Clone("cms_zoomed");
  TGraphErrors *alice_zoomed = (TGraphErrors*)alice->Clone("alice_zoomed");
  cms_zoomed->GetXaxis()->SetRangeUser(0.,2.);
  cms_zoomed->Draw();
  TF1 * f1_zoomed = cms->GetFunction("f1");
  f1_zoomed->Draw("same");
  alice_zoomed->Draw("psame");
}


void plotRatio(TH1D * cms, TGraphErrors *alice, char *yaxis) {

  TH1D *cms_copy1 = (TH1D*)cms->Clone("cms_copy1");
  TGraphErrors *alice_copy1 = (TGraphErrors*)alice->Clone("alice_copy1");
  TF1 * f1_copy1 = cms->GetFunction("f1");

  cms_copy1->Divide(f1_copy1);
  cms_copy1->SetMinimum(0.7);
  cms_copy1->SetMaximum(1.9);
  cms_copy1->GetYaxis()->SetTitle(Form("Measurement (%s) / Fit",yaxis));
  cms_copy1->Draw();

  TGraphErrors* gRatio = divide_graph_by_function(alice_copy1,f1_copy1);
  gRatio->SetMarkerStyle(20);
  gRatio->SetMarkerColor(2);
  gRatio->SetLineColor(2);
  gRatio->SetMarkerSize(1.4);
  gRatio->Draw("psame");

  TLegend *leg2 = new TLegend(0.6,0.75,1.,0.93,NULL,"brNDC");
  leg2->AddEntry(cms,"HIN-12-017","pl");
  leg2->AddEntry(alice,"ALICE","pl");
  leg2->SetFillStyle(0);
  leg2->SetFillColor(0);
  leg2->SetBorderSize(0);
  leg2->Draw();

  TPad *c2_zoom = new TPad("c2_zoom","c2_zoom",0.19,0.53,0.57,0.93);
  c2_zoom->SetFillStyle(0);
  c2_zoom->Draw();
  c2_zoom->cd();
  TH1D* cms_copy1_zoomed = (TH1D*)cms_copy1->Clone("cms_copy1_zoomed");
  TGraphErrors *gRatio_zoomed = (TGraphErrors*)gRatio->Clone("gRatio_zoomed");
  cms_copy1_zoomed->GetXaxis()->SetRangeUser(0.,2.);
  cms_copy1_zoomed->SetMaximum(1.1);
  cms_copy1_zoomed->SetMinimum(0.9);
  cms_copy1_zoomed->Draw();
  gRatio_zoomed->Draw("psame");
}
