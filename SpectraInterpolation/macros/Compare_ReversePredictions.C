void Compare_ReversePredictions() {

  SetStyle();
  gStyle->SetOptFile(0);
  gStyle->SetOptStat(0);
  gStyle->SetOptFit(0);

  TFile * f_pt = new TFile("output_interpolation_KK_LogFitForC6_YenJiePredMeasTest.root");
  TFile * f_Exp0_xt = new TFile("output_interpolation_KK_LogFitForC6_TryExtrapolationInXT_Exp0_YenJiePredMeasTest.root");

  TH1D* h_2760Meas = (TH1D*)f_pt->Get("h2760_EdTxt");
  TH1D* h_pTPol2Pred = (TH1D*)f_pt->Get("h2760_To100GeV_FromLogFit_test");

  TH1D *h_xTPol2Pred_xt = (TH1D*)f_Exp0_xt->Get("h2760_To100GeV_FromLogFit_test");
  TH1D *h_xTPol2Pred_pt = From_xT_to_pT_histo(h_xTPol2Pred_xt,h_2760Meas,2760.,0.);

  TCanvas *c1 = new TCanvas("c1","c1",500,500);
  c1->SetLogy();
  h_2760Meas->GetXaxis()->SetTitle("p_{T} [GeV/c]");
  h_2760Meas->GetYaxis()->SetTitle("Ed^{3}#sigma/dp^{3}");
  h_2760Meas->GetXaxis()->CenterTitle();
  h_2760Meas->GetYaxis()->CenterTitle();
  h_2760Meas->Draw();  

  h_pTPol2Pred->SetLineColor(2);
  h_pTPol2Pred->SetLineStyle(2);
  h_pTPol2Pred->SetLineWidth(3);
  h_pTPol2Pred->Draw("same");
  
  h_xTPol2Pred_pt->SetLineColor(3);
  h_xTPol2Pred_pt->SetLineStyle(3);
  h_xTPol2Pred_pt->SetLineWidth(3);
  h_xTPol2Pred_pt->Draw("same");

  TLegend *leg1 = new TLegend(0.19,0.61,0.96,0.91);
  leg1->SetBorderSize(0);
  leg1->SetFillStyle(0);
  leg1->SetFillColor(0);
  leg1->AddEntry(h_2760Meas,"2.76 TeV, measurement","l");
  leg1->AddEntry(h_pTPol2Pred,"2.76 TeV, log-log pol2 interpolation in p_{T}","l");
  leg1->AddEntry(h_xTPol2Pred_pt,"2.76 TeV, log-log pol2 interpolation in x_{T}","l");
  leg1->Draw();


  TCanvas *c2 = new TCanvas("c2","c2",500,500);
  TH1F * h_2760Meas_copy1 = (TH1F*)h_2760Meas->Clone("h_2760Meas_copy1");
  TH1F * h_2760Meas_copy2 = (TH1F*)h_2760Meas->Clone("h_2760Meas_copy2");

  h_2760Meas_copy1->Divide(h_pTPol2Pred);
  h_2760Meas_copy1->SetLineStyle(2);
  h_2760Meas_copy1->SetLineColor(2);
  h_2760Meas_copy1->SetLineWidth(3);
  h_2760Meas_copy1->SetMinimum(0.5);
  h_2760Meas_copy1->SetMaximum(1.5);
  h_2760Meas_copy1->GetYaxis()->SetTitle("Measurement / Predictions");
  h_2760Meas_copy1->Draw();

  h_2760Meas_copy2->Divide(h_xTPol2Pred_pt);
  h_2760Meas_copy2->SetLineColor(3);
  h_2760Meas_copy2->SetLineStyle(3);
  h_2760Meas_copy2->SetLineWidth(3);
  h_2760Meas_copy2->Draw("same");

  TLegend *leg2 = new TLegend(0.19,0.61,0.99,0.91);
  leg2->SetBorderSize(0);
  leg2->SetFillStyle(0);
  leg2->SetFillColor(0);
  leg2->AddEntry(h_2760Meas_copy1,"log-log pol2 interpolation in p_{T}","l");
  leg2->AddEntry(h_2760Meas_copy2,"log-log pol2 interpolation in x_{T}","l");
  leg2->Draw();
}

void SetStyle() {

   gStyle->SetErrorX(0);
   gStyle->SetPalette(1,0);
   gStyle->SetPadColor(0);
   gStyle->SetPadBorderSize(0);
   gStyle->SetPadBorderMode(0);
   gStyle->SetCanvasColor(0);
   gStyle->SetCanvasBorderMode(0);
   gStyle->SetCanvasBorderSize(0);
   gStyle->SetFrameBorderMode(0);
   gStyle->SetFrameLineColor(0);
   gStyle->SetTitleColor(0);
   gStyle->SetTitleBorderSize(0);

   gStyle->SetPalette(1,0);

   gStyle->SetPadTickX(1);
   gStyle->SetPadTickY(1);
   gStyle->SetPadColor(0);
   gStyle->SetPadBorderSize(0);
   gStyle->SetPadBorderMode(0);
   gStyle->SetCanvasColor(0);
   gStyle->SetCanvasBorderMode(0);
   gStyle->SetCanvasBorderSize(0);
   gStyle->SetFrameBorderMode(0);
   gStyle->SetFrameLineColor(0);
   gStyle->SetTextFont(62);
   gStyle->SetLabelFont(42,"XYZ");
   gStyle->SetTitleFont(42,"XYZ");
   gStyle->SetTitleColor(0);
   gStyle->SetTitleBorderSize(0);
   gStyle->SetTitleXSize(.045);
   gStyle->SetTitleYSize(.045);
   //gStyle->SetTitleXOffset(1.0);
   //gStyle->SetTitleYOffset(1.6);
   gStyle->SetTitleXOffset(1.2);
   //gStyle->SetTitleYOffset(2.2);
   gStyle->SetTitleYOffset(1.8);
   gStyle->SetLabelSize(0.040,"XYZ");
   gStyle->SetLabelOffset(0.01,"X");
   gStyle->SetLabelOffset(0.01,"Y");
   gStyle->SetTitleColor(1,"XYZ");
   gStyle->SetHistFillColor(1);
   gStyle->SetHistFillStyle(0);
   gStyle->SetHistLineColor(1);
   gStyle->SetHistLineStyle(0);
   gStyle->SetHistLineWidth(3);
   gStyle->SetHistLineWidth(1);
   gStyle->SetEndErrorSize(0);
   gStyle->SetErrorX(0);
   gStyle->SetMarkerStyle(20);
   //gStyle->SetMarkerSize(1.25);
   gStyle->SetMarkerSize(1.5);

   gStyle->SetOptFit(1111);
   gStyle->SetStatColor(0);
   gStyle->SetStatBorderSize(1);
   gStyle->SetOptTitle(0);
   //gStyle->SetOptStat(1111);
   //gStyle->SetOptStat(0);


   gStyle->SetPadLeftMargin(0.17);
   //gStyle->SetPadLeftMargin(0.21);
   gStyle->SetPadBottomMargin(0.14);
   gStyle->SetPadTopMargin(0.05);
   gStyle->SetPadRightMargin(0.04);


   const Int_t NRGBs = 5;
   //const Int_t NCont = 255;
   const Int_t NCont = 200;

   Double_t stops[NRGBs] = { 0.00, 0.34, 0.61, 0.84, 1.00 };
   Double_t red[NRGBs]   = { 0.00, 0.00, 0.87, 1.00, 0.51 };
   Double_t green[NRGBs] = { 0.00, 0.81, 1.00, 0.20, 0.00 };
   Double_t blue[NRGBs]  = { 0.51, 1.00, 0.12, 0.00, 0.00 };
   TColor::CreateGradientColorTable(NRGBs, stops, red, green, blue, NCont);
   //gStyle->CreateColorGradientTable(NRGBs, stops, red, green, blue, NCont);

   gStyle->SetNumberContours(NCont);

   gROOT->ForceStyle();
}

TH1D* From_xT_to_pT(TF1 *f_xt, TH1D *h_binning, double sqrts, double exp) {

  TH1D* h_pt = h_binning->Clone("h_pt");
  h_pt->Reset();

  //xt distribution is a function. Use the pT binning of the pT distribution
  for(int i=1; i<=h_pt->GetNbinsX(); i++) {

     double pt = h_pt->GetBinCenter(i);
     double content = h_pt->GetBinContent(i);
     double xt = 2.*pt/sqrts;

     h_pt->SetBinContent(i,f_xt->Eval(xt)/sqrts**exp);
  }

  return h_pt;
}

TH1D* From_xT_to_pT_histo(TH1D *h_input, TH1D *h_binning, double sqrts, double exp) {

  TH1D *h_pt = (TH1D*)h_binning->Clone("h_pt");
  h_pt->Reset();

  for(int i=1; i<=h_input->GetNbinsX(); i++) {
     double xT = h_input->GetBinCenter(i);
     double content = h_input->GetBinContent(i)/TMath::Power(sqrts,exp);
     double pT = sqrts*xT/2.;
     std::cerr<<" pT: " << pT << std::endl;
     if(pT>120) break;
     h_pt->SetBinContent(h_pt->FindBin(pT),content);
  }

  return h_pt;
}
