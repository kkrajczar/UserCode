{
  gROOT->Reset();
  gROOT->ProcessLine(".x rootlogonChristof.C");
  gStyle->SetOptLogy(0);
  gROOT->ForceStyle();
  gStyle->SetTitleYOffset(1.38);

  TFile *f = new TFile("CombineSpectra_minbias.root");
  TH1D * hRecMult = (TH1D*)f->Get("hRecMultiplicity");

  //Plotting
  TCanvas *c1 = new TCanvas("c1","c1");
  c1->cd();
  hRecMult->Scale(1./hRecMult->Integral());
  hRecMult->SetMarkerStyle(24);
  hRecMult->GetXaxis()->SetTitle("Number of selected tracks");
  hRecMult->GetYaxis()->SetTitle("Probability");
  hRecMult->Draw();

  TPad *c1_zoom = new TPad("c1_zoom","c1_zoom",0.56,0.56,0.94,0.93);
  c1_zoom->SetFillStyle(0);
  c1_zoom->Draw();
  c1_zoom->cd();
  TH1D* hRecMult_zoomed = (TH1D*)hRecMult->Clone("hRecMult_zoomed");
  hRecMult_zoomed->GetXaxis()->SetRangeUser(0.,30.);
  hRecMult_zoomed->Draw();

  c1->cd();
  TPad *c2_zoom = new TPad("c2_zoom","c2_zoom",0.56,0.16,0.94,0.53);
  c2_zoom->SetFillStyle(0);
  c2_zoom->Draw();
  c2_zoom->cd();
  c2_zoom->SetLogy();
  TH1D* hRecMult_copy = (TH1D*)hRecMult->Clone("hRecMult_copy");
  hRecMult_copy->Draw();
}
