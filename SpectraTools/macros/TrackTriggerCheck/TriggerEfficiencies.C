void putLatexInfo(bool doIt, double min, double max); 
void plotClosure(TH1D* h1_corrRec, TH1D* h2_corrRec, TH1D *h3_corrRec, TH1D* h4_corrRec,
                 TH1D* h1_sim,     TH1D* h2_sim,     TH1D *h3_sim,     TH1D* h4_sim
                 );
void normalizeByBinWidth(TH1D *histo);
void RemoveLargeerrorPoints(TH1D *h_input);
//------------------------

void TriggerEfficiencies()
{
   gROOT->Reset();
   gROOT->ProcessLine(".x rootlogonChristof.C");
   gROOT->ForceStyle();
   gStyle->SetPalette(1);
   gStyle->SetTitleYOffset(1.28);
   gStyle->SetOptFit(0000);
//   gStyle->SetPadRightMargin(0.16);

   bool doSave = true;

   //Take minbias distribution from below
//   TFile *f_minbias = new TFile("../CombineSpectra_minbias.root");
   TFile *f_minbias = new TFile("CombineSpectra_minbias.root");
   TFile *f_FullTrackTrigger_12 = new TFile("CombineSpectra_FullTrackTrigger_Track12.root");
   TFile *f_FullTrackTrigger_20 = new TFile("CombineSpectra_FullTrackTrigger_Track20.root");
   TFile *f_FullTrackTrigger_30_50 = new TFile("CombineSpectra_FullTrackTrigger_Track30_Track50.root");

   TH1D* hPartPt_minbias = (TH1D*)f_minbias->Get("hPartPt_minbias_trkCorr_trigCorr");
   TH1D* hPartPt_minbias_smallerBins = (TH1D*)f_minbias->Get("hPartPt_minbias_trkCorr_trigCorr_smallerBins");
   TH1D* hPartPt_FullTrack12 = (TH1D*)f_FullTrackTrigger_12->Get("hPartPt_FullTrack12_trkCorr_trigCorr");
   TH1D* hPartPt_FullTrack12_smallerBins = (TH1D*)f_FullTrackTrigger_12->Get("hPartPt_FullTrack12_trkCorr_trigCorr_smallerBins");
   TH1D* hPartPt_FullTrack20 = (TH1D*)f_FullTrackTrigger_20->Get("hPartPt_FullTrack20_trkCorr_trigCorr");
   TH1D* hPartPt_FullTrack20_smallerBins = (TH1D*)f_FullTrackTrigger_20->Get("hPartPt_FullTrack20_trkCorr_trigCorr_smallerBins");
   TH1D* hPartPt_FullTrack30 = (TH1D*)f_FullTrackTrigger_30_50->Get("hPartPt_FullTrack30_trkCorr_trigCorr");
   TH1D* hPartPt_FullTrack30_smallerBins = (TH1D*)f_FullTrackTrigger_30_50->Get("hPartPt_FullTrack30_trkCorr_trigCorr_smallerBins");
   TH1D* hPartPt_FullTrack50_smallerBins = (TH1D*)f_FullTrackTrigger_30_50->Get("hPartPt_FullTrack50_trkCorr_trigCorr");

   hPartPt_minbias->SetBinContent(hPartPt_minbias->FindBin(103.24),0);//Remove muon event
   hPartPt_minbias->SetBinError(hPartPt_minbias->FindBin(103.24),0);//Remove muon event

   TH1D* hNumEv_22_32_FullTrack12 = (TH1D*)f_FullTrackTrigger_12->Get("hNumEv_FullTrack12_22_32_trigCorr");
   TH1D* hNumEv_22_32_FullTrack20 = (TH1D*)f_FullTrackTrigger_20->Get("hNumEv_FullTrack20_22_32_trigCorr");
   TH1D* hNumEv_32_X_FullTrack20 = (TH1D*)f_FullTrackTrigger_20->Get("hNumEv_FullTrack20_32_X_trigCorr");
   TH1D* hNumEv_32_X_FullTrack30 = (TH1D*)f_FullTrackTrigger_30_50->Get("hNumEv_FullTrack30_32_X_trigCorr");

   float numev_22_32_FullTrack12 = hNumEv_22_32_FullTrack12->GetBinContent(1);
   float numev_22_32_FullTrack20 = hNumEv_22_32_FullTrack20->GetBinContent(1);
   float numev_32_X_FullTrack20 = hNumEv_32_X_FullTrack20->GetBinContent(1);
   float numev_32_X_FullTrack30 = hNumEv_32_X_FullTrack30->GetBinContent(1);

   TCanvas *c1 = new TCanvas("c1","c1");
   c1->SetLogy();
   hPartPt_minbias->GetXaxis()->CenterTitle();
   hPartPt_minbias->GetYaxis()->CenterTitle();
   hPartPt_minbias->GetXaxis()->SetTitle("p_{T} [GeV/c]");
   hPartPt_minbias->GetYaxis()->SetTitle("N_{Track} (|#eta_{CM}|<1) / GeV/c");
//   hPartPt_minbias->SetNdivisions(505);
   hPartPt_minbias->SetMarkerColor(1);
   hPartPt_minbias->SetLineColor(1);
   hPartPt_minbias->SetMarkerStyle(20);
   hPartPt_minbias->SetMaximum(1e+8);
   hPartPt_minbias->SetMinimum(0.1);
   hPartPt_minbias->GetXaxis()->SetRangeUser(0.,100.);
   hPartPt_minbias->Draw();

   hPartPt_minbias_smallerBins->SetMarkerStyle(25);
//   hPartPt_minbias_smallerBins->Draw("same");

   hPartPt_FullTrack12->SetMarkerColor(39);
   hPartPt_FullTrack12->SetLineColor(39);
   hPartPt_FullTrack12->SetMarkerStyle(21);
//   hPartPt_FullTrack12->Draw("same");

   hPartPt_FullTrack12_smallerBins->SetMarkerColor(39);
   hPartPt_FullTrack12_smallerBins->SetLineColor(39);
   hPartPt_FullTrack12_smallerBins->SetMarkerStyle(21);
   hPartPt_FullTrack12_smallerBins->Draw("same");

   hPartPt_FullTrack20->SetMarkerColor(8);
   hPartPt_FullTrack20->SetLineColor(8);
   hPartPt_FullTrack20->SetMarkerStyle(24);
//   hPartPt_FullTrack20->Draw("same");

   hPartPt_FullTrack20_smallerBins->SetMarkerColor(8);
   hPartPt_FullTrack20_smallerBins->SetLineColor(8);
   hPartPt_FullTrack20_smallerBins->SetMarkerStyle(24);
   hPartPt_FullTrack20_smallerBins->Draw("same");

   hPartPt_FullTrack30->SetMarkerColor(2);
   hPartPt_FullTrack30->SetLineColor(2);
   hPartPt_FullTrack30->SetMarkerStyle(25);
//   hPartPt_FullTrack30->Draw("same");

   hPartPt_FullTrack30_smallerBins->SetMarkerColor(2);
   hPartPt_FullTrack30_smallerBins->SetLineColor(2);
   hPartPt_FullTrack30_smallerBins->SetMarkerStyle(25);
   hPartPt_FullTrack30_smallerBins->Draw("same");

   hPartPt_FullTrack50_smallerBins->SetMarkerColor(4);
   hPartPt_FullTrack50_smallerBins->SetLineColor(4);
   hPartPt_FullTrack50_smallerBins->SetMarkerStyle(30);
   hPartPt_FullTrack50_smallerBins->Draw("same");

   TLegend *leg1 = new TLegend(0.6,0.65,0.95,0.95,NULL,"brNDC");
   leg1->AddEntry(hPartPt_minbias,"MinBias data","pl");
//   leg1->AddEntry(hPartPt_minbias_smallerBins,"MinBias, smaller bins","pl");
//   leg1->AddEntry(hPartPt_FullTrack12,"FullTrack12","pl");
   leg1->AddEntry(hPartPt_FullTrack12_smallerBins,"FullTrack12 trigger","pl");
//   leg1->AddEntry(hPartPt_FullTrack20,"FullTrack20 trigger","pl");
   leg1->AddEntry(hPartPt_FullTrack20_smallerBins,"FullTrack20 trigger","pl");
//   leg1->AddEntry(hPartPt_FullTrack30,"FullTrack30 trigger","pl");
   leg1->AddEntry(hPartPt_FullTrack30_smallerBins,"FullTrack30 trigger","pl");
   leg1->AddEntry(hPartPt_FullTrack50_smallerBins,"FullTrack50 trigger","pl");
   leg1->SetFillStyle(0);
   leg1->SetFillColor(0);
   leg1->SetBorderSize(0);
   leg1->Draw();
   if(doSave) {
      c1->SaveAs("Figs/TriggerEfficiencies_c1.gif");
      c1->SaveAs("Figs/TriggerEfficiencies_c1.eps");
      c1->SaveAs("Figs/TriggerEfficiencies_c1.C");
   }


   TCanvas *c2 = new TCanvas("c2","c2");
   TH1D *hPartPt_FullTrack12_copy1 = (TH1D*)hPartPt_FullTrack12->Clone("hPartPt_FullTrack12_copy1");
   TH1D *hPartPt_FullTrack12_smallerBins_copy1 = (TH1D*)hPartPt_FullTrack12_smallerBins->Clone("hPartPt_FullTrack12_smallerBins_copy1");
   TH1D *hPartPt_FullTrack20_smallerBins_copy1 = (TH1D*)hPartPt_FullTrack20_smallerBins->Clone("hPartPt_FullTrack20_smallerBins_copy1");
   TH1D *hPartPt_FullTrack30_smallerBins_copy1 = (TH1D*)hPartPt_FullTrack30_smallerBins->Clone("hPartPt_FullTrack30_smallerBins_copy1");
   TH1D *hPartPt_FullTrack50_smallerBins_copy1 = (TH1D*)hPartPt_FullTrack50_smallerBins->Clone("hPartPt_FullTrack50_smallerBins_copy1");

   TH1D *hPartPt_minbias_smallerBins_copy1 = (TH1D*)hPartPt_minbias_smallerBins->Clone("hPartPt_minbias_smallerBins_copy1");

//   hPartPt_FullTrack12_smallerBins_copy1->Rebin(4);
//   hPartPt_minbias_smallerBins_copy1->Rebin(4);

   hPartPt_FullTrack12_copy1->Divide(hPartPt_minbias);
   hPartPt_FullTrack12_smallerBins_copy1->Divide(hPartPt_minbias_smallerBins_copy1);
   hPartPt_FullTrack20_smallerBins_copy1->Divide(hPartPt_FullTrack12_smallerBins);
   hPartPt_FullTrack30_smallerBins_copy1->Divide(hPartPt_FullTrack20_smallerBins);
   hPartPt_FullTrack50_smallerBins_copy1->Divide(hPartPt_FullTrack30_smallerBins);

   TF1 * Fit_FullTrack12 = new TF1("Fit_FullTrack12","[0]",14.,22.);
   TF1 * Fit_FullTrack12_smallerBins = new TF1("Fit_FullTrack12_smallerBins","[0]",14.,22.);
   hPartPt_FullTrack12_copy1->Fit(Fit_FullTrack12,"R0");
   hPartPt_FullTrack12_smallerBins_copy1->Fit(Fit_FullTrack12_smallerBins,"R0");
   double scale_FullTrack12 = Fit_FullTrack12->GetParameter(0);
   double scale_FullTrack12_smallerBins = Fit_FullTrack12_smallerBins->GetParameter(0);
//   scale_FullTrack12_smallerBins /= 2.;

   std::cerr<<" numev_22_32_FullTrack12: " << numev_22_32_FullTrack12 << std::endl;
   std::cerr<<" numev_22_32_FullTrack20: " << numev_22_32_FullTrack20 << std::endl;

   hPartPt_FullTrack12_copy1->Scale(1./scale_FullTrack12);
   hPartPt_FullTrack12_smallerBins_copy1->Scale(1./scale_FullTrack12_smallerBins);
   hPartPt_FullTrack20_smallerBins_copy1->Scale(numev_22_32_FullTrack12/numev_22_32_FullTrack20);
   hPartPt_FullTrack30_smallerBins_copy1->Scale(numev_32_X_FullTrack20/numev_32_X_FullTrack30);

   hPartPt_FullTrack30_smallerBins_copy1->SetMaximum(1.5);
   hPartPt_FullTrack30_smallerBins_copy1->GetYaxis()->SetTitle("Trigger efficiency");
   hPartPt_FullTrack30_smallerBins_copy1->GetXaxis()->SetTitle("p_{T} [GeV/c]");
//   hPartPt_FullTrack30_smallerBins_copy1->SetNdivisions(505);
   hPartPt_FullTrack30_smallerBins_copy1->GetXaxis()->SetRangeUser(0.,250.);
   hPartPt_FullTrack30_smallerBins_copy1->SetMaximum(3.);
   hPartPt_FullTrack30_smallerBins_copy1->GetXaxis()->CenterTitle();
   hPartPt_FullTrack30_smallerBins_copy1->GetYaxis()->CenterTitle();
   hPartPt_FullTrack30_smallerBins_copy1->Draw();

//   RemoveLargeerrorPoints(hPartPt_FullTrack12_copy1);
   hPartPt_FullTrack12_copy1->Draw("same");
//   hPartPt_FullTrack12_smallerBins_copy1->Draw("same");

   hPartPt_FullTrack20_smallerBins_copy1->Draw("same");

   hPartPt_FullTrack50_smallerBins_copy1->Draw("same");

   TLegend *leg2 = new TLegend(0.25,0.65,0.55,0.95,NULL,"brNDC");
   leg2->AddEntry(hPartPt_FullTrack12_copy1,"FullTrack12","pl");
   leg2->AddEntry(hPartPt_FullTrack20_smallerBins_copy1,"FullTrack20","pl");
   leg2->AddEntry(hPartPt_FullTrack30_smallerBins_copy1,"FullTrack30","pl");
   leg2->AddEntry(hPartPt_FullTrack50_smallerBins_copy1,"FullTrack50","pl");
   leg2->SetFillStyle(0);
   leg2->SetFillColor(0);
   leg2->SetBorderSize(0);
   leg2->Draw();

   TPad *c2_zoom = new TPad("c2_zoom","c2_zoom",0.56,0.56,0.94,0.93);
//   c2_zoom->SetFillStyle(0);
   c2_zoom->Draw();
   c2_zoom->cd();
   hPartPt_FullTrack12_smallerBins_copy1->GetXaxis()->CenterTitle();
   hPartPt_FullTrack12_smallerBins_copy1->GetYaxis()->CenterTitle();
   hPartPt_FullTrack12_smallerBins_copy1->GetXaxis()->SetTitle("p_{T} [GeV/c]");
   hPartPt_FullTrack12_smallerBins_copy1->GetYaxis()->SetTitle("Trigger efficiency");
   hPartPt_FullTrack12_smallerBins_copy1->GetXaxis()->SetRangeUser(0.,18.);
   hPartPt_FullTrack12_smallerBins_copy1->SetMinimum(0.);
   hPartPt_FullTrack12_smallerBins_copy1->SetMaximum(1.6);
   hPartPt_FullTrack12_smallerBins_copy1->Draw();

   if(doSave) {
      c2->SaveAs("Figs/TriggerEfficiencies_c2.gif");
      c2->SaveAs("Figs/TriggerEfficiencies_c2.eps");
      c2->SaveAs("Figs/TriggerEfficiencies_c2.C");
   }
}

void putLatexInfo(bool doIt, double min, double max) {

   TLatex *l1a = new TLatex(0.2,0.88,"akPu3PF jets, jet |#eta|<2.");
   l1a->SetNDC();
   l1a->SetTextSize(0.035);
   l1a->Draw();

   TLatex *l1b;
   if(doIt)
//      l1b = new TLatex(0.2,0.83,Form("Dijet event sel., track p_{T}>1 GeV/c, %f<x<%f",floor(100*min+0.5)/100f10,floor(100*max+0.5)/100));
//      l1b = new TLatex(0.2,0.83,Form("Dijet event sel., track p_{T}>1 GeV/c, %1.2f<x<%1.2f",min,max));
      l1b = new TLatex(0.2,0.83,Form("track p_{T}>1 GeV/c, %1.2f<x<%1.2f",min,max));
   else
//      l1b = new TLatex(0.2,0.83,"Dijet event sel., track p_{T}>1 GeV/c");
      l1b = new TLatex(0.2,0.83,"track p_{T}>1 GeV/c");
   l1b->SetNDC();
   l1b->SetTextSize(0.035);
   l1b->Draw();

   TLatex *l1c = new TLatex(0.2,0.78,"HiForest_V2_02_07");
   l1c->SetNDC();
   l1c->SetTextSize(0.035);
   l1c->Draw();

//  TLatex *l1d = new TLatex(0.2,0.73,Form("Centrality: %s",cent));
//   l1d->SetNDC();
//   l1d->SetTextSize(0.035);
//   l1d->Draw();
}

void plotClosure(TH1D* h1_corrRec, TH1D* h2_corrRec, TH1D *h3_corrRec, TH1D* h4_corrRec,
                 TH1D* h1_sim,     TH1D* h2_sim,     TH1D *h3_sim,     TH1D* h4_sim
                 )
 {

   h1_corrRec->SetMinimum(0.4);
   h1_corrRec->SetMaximum(1.6);
   h1_corrRec->GetXaxis()->SetRangeUser(2.,179.);
   h1_corrRec->GetXaxis()->CenterTitle();
   h1_corrRec->GetYaxis()->CenterTitle();
   h1_corrRec->GetYaxis()->SetTitleOffset(1.3);
   h1_corrRec->GetYaxis()->SetTitle("Corrected reco / Sim");
   h1_corrRec->GetXaxis()->SetTitle("p_{T} [GeV]");
   h1_corrRec->Divide(h1_sim);
   h1_corrRec->SetMarkerStyle(20);
   h1_corrRec->Draw();

   h2_corrRec->Divide(h2_sim);
   h2_corrRec->SetMarkerStyle(20);
   h2_corrRec->SetMarkerColor(2);
   h2_corrRec->SetLineColor(2);
   h2_corrRec->Draw("same");

   h3_corrRec->Divide(h3_sim);
   h3_corrRec->SetMarkerStyle(20);
   h3_corrRec->SetMarkerColor(3);
   h3_corrRec->SetLineColor(3);
   h3_corrRec->Draw("same");

   h4_corrRec->Divide(h4_sim);
   h4_corrRec->SetMarkerStyle(20);
   h4_corrRec->SetMarkerColor(4);
   h4_corrRec->SetLineColor(4);
   h4_corrRec->Draw("same");

   TLegend *leg1 = new TLegend(0.15,0.15,0.82,0.29,NULL,"brNDC");
   leg1->AddEntry(h1_corrRec,"50<jet p_{T}<60 GeV/c","p");
   leg1->AddEntry(h2_corrRec,"60<jet p_{T}<70 GeV/c","p");
   leg1->AddEntry(h3_corrRec,"70<jet p_{T}<80 GeV/c","p");
   leg1->AddEntry(h4_corrRec,"80<jet p_{T}<100 GeV/c","p");
   leg1->SetFillStyle(0);
   leg1->SetFillColor(0);
   leg1->SetBorderSize(0);
   leg1->Draw();
}

void normalizeByBinWidth(TH1D *histo) {
   for(int i = 1; i <= histo->GetNbinsX(); i++) {
      float content = histo->GetBinContent(i);
      float error = histo->GetBinError(i);
      histo->SetBinContent(i,content/histo->GetBinWidth(i));
      histo->SetBinError(i,error/histo->GetBinWidth(i));
   }
}


void RemoveLargeerrorPoints(TH1D *h_input) {
  for(int i=1; i<=h_input->GetNbinsX(); i++) {
     if((h_input->GetBinError(i)/h_input->GetBinContent(i))>0.3) {
        h_input->SetBinContent(i,0);
        h_input->SetBinError(i,0);
     }
  }
}

