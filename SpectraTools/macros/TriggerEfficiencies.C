void putLatexInfo(bool doIt, double min, double max); 
void plotClosure(TH1D* h1_corrRec, TH1D* h2_corrRec, TH1D *h3_corrRec, TH1D* h4_corrRec,
                 TH1D* h1_sim,     TH1D* h2_sim,     TH1D *h3_sim,     TH1D* h4_sim
                 );
void normalizeByBinWidth(TH1D *histo);
//------------------------

void TriggerEfficiencies()
{
   gROOT->Reset();
   gROOT->ProcessLine(".x rootlogonChristof.C");
   gROOT->ForceStyle();
   gStyle->SetPalette(1);
   gStyle->SetTitleYOffset(1.30);
   gStyle->SetOptFit(0000);
//   gStyle->SetPadRightMargin(0.16);

   bool doSave = true;

   //Take minbias distribution from below
   TFile *f_minbias = new TFile("CombineSpectra_minbias.root");
   //Use the jet40 || jet60 skimmed Forest for the 40 & 60 distributions
   TFile *f_40_60 = new TFile("CombineSpectra_40_60.root");
   TFile *f_80_100 = new TFile("CombineSpectra_80_100.root");

   TH1D* hJetPt_larger_minbias = (TH1D*)f_minbias->Get("hJetPt_larger_minbias");
   TH1D* hJetPt_Jet40 = (TH1D*)f_40_60->Get("hJetPt_Jet40");
   TH1D* hJetPt_larger_Jet40 = (TH1D*)f_40_60->Get("hJetPt_larger_Jet40");
   TH1D* hJetPt_Jet60 = (TH1D*)f_40_60->Get("hJetPt_Jet60");
   TH1D* hJetPt_Jet80 = (TH1D*)f_80_100->Get("hJetPt_Jet80");
   TH1D* hJetPt_Jet100 = (TH1D*)f_80_100->Get("hJetPt_Jet100");

   TCanvas *c1 = new TCanvas("c1","c1");
   c1->SetLogy();
   hJetPt_larger_minbias->GetXaxis()->CenterTitle();
   hJetPt_larger_minbias->GetYaxis()->CenterTitle();
   hJetPt_larger_minbias->GetXaxis()->SetTitle("Offline jet p_{T} [GeV/c]");
   hJetPt_larger_minbias->GetYaxis()->SetTitle("N_{Leading jet} (|#eta|<2.5) / GeV/c");
   hJetPt_larger_minbias->SetNdivisions(505);
   hJetPt_larger_minbias->SetMarkerColor(1);
   hJetPt_larger_minbias->SetLineColor(1);
   hJetPt_larger_minbias->SetMarkerStyle(20);
   hJetPt_larger_minbias->SetMaximum(1e+6);
   hJetPt_larger_minbias->GetXaxis()->SetRangeUser(0.,250.);
   hJetPt_larger_minbias->Draw();

   hJetPt_Jet40->SetMarkerColor(3);
   hJetPt_Jet40->SetLineColor(3);
   hJetPt_Jet40->SetMarkerStyle(24);
   hJetPt_Jet40->Draw("same");

   hJetPt_larger_Jet40->SetMarkerColor(3);
   hJetPt_larger_Jet40->SetLineColor(3);
   hJetPt_larger_Jet40->SetMarkerStyle(25);
   hJetPt_larger_Jet40->Draw("same");

   hJetPt_Jet60->SetMarkerColor(6);
   hJetPt_Jet60->SetLineColor(6);
   hJetPt_Jet60->SetMarkerStyle(20);
   hJetPt_Jet60->Draw("same");

   hJetPt_Jet80->SetMarkerColor(4);
   hJetPt_Jet80->SetLineColor(4);
   hJetPt_Jet80->SetMarkerStyle(24);
   hJetPt_Jet80->Draw("same");

   hJetPt_Jet100->SetMarkerColor(2);
   hJetPt_Jet100->SetLineColor(2);
   hJetPt_Jet100->SetMarkerStyle(20);
   hJetPt_Jet100->Draw("same");

   TLegend *leg1 = new TLegend(0.7,0.7,0.95,0.95,NULL,"brNDC");
   leg1->AddEntry(hJetPt_larger_minbias,"MinBias","pl");
   leg1->AddEntry(hJetPt_larger_Jet40,"Jet40, wider bins","pl");
   leg1->AddEntry(hJetPt_Jet40,"Jet40","pl");
   leg1->AddEntry(hJetPt_Jet60,"Jet60","pl");
   leg1->AddEntry(hJetPt_Jet80,"Jet80","pl");
   leg1->AddEntry(hJetPt_Jet100,"Jet100","pl");
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
   TH1D *hJetPt_larger_Jet40_copy1 = (TH1D*)hJetPt_larger_Jet40->Clone("hJetPt_larger_Jet40_copy1");
   TH1D *hJetPt_Jet60_copy1 = (TH1D*)hJetPt_Jet60->Clone("hJetPt_Jet60_copy1");
   TH1D *hJetPt_Jet80_copy1 = (TH1D*)hJetPt_Jet80->Clone("hJetPt_Jet80_copy1");
   TH1D *hJetPt_Jet100_copy1 = (TH1D*)hJetPt_Jet100->Clone("hJetPt_Jet100_copy1");

   hJetPt_larger_Jet40_copy1->Divide(hJetPt_larger_minbias);
   hJetPt_Jet60_copy1->Divide(hJetPt_Jet40);
   hJetPt_Jet80_copy1->Divide(hJetPt_Jet60);
   hJetPt_Jet100_copy1->Divide(hJetPt_Jet80);

   TF1 * Fit_40 = new TF1("Fit_40","[0]",60.,200.);
   TF1 * Fit_60 = new TF1("Fit_60","[0]",80.,200.);
   TF1 * Fit_80 = new TF1("Fit_80","[0]",100.,200.);
   TF1 * Fit_100 = new TF1("Fit_100","[0]",120.,200.);

   hJetPt_larger_Jet40_copy1->GetYaxis()->SetTitle("Trigger efficiency");
   hJetPt_larger_Jet40_copy1->Fit(Fit_40,"R0");
   hJetPt_Jet60_copy1->Fit(Fit_60,"R0");
   hJetPt_Jet80_copy1->Fit(Fit_80,"R0");
   hJetPt_Jet100_copy1->Fit(Fit_100,"R0");

   double scale_40 = Fit_40->GetParameter(0);
   double scale_60 = Fit_60->GetParameter(0);
   double scale_80 = Fit_80->GetParameter(0);
   double scale_100 = Fit_100->GetParameter(0);

   hJetPt_larger_Jet40_copy1->Scale(1./scale_40);
   hJetPt_Jet60_copy1->Scale(1./scale_60);
   hJetPt_Jet80_copy1->Scale(1./scale_80);
   hJetPt_Jet100_copy1->Scale(1./scale_100);

   hJetPt_larger_Jet40_copy1->SetMaximum(1.5);
   hJetPt_larger_Jet40_copy1->GetXaxis()->SetTitle("Offline jet p_{T} [GeV/c]");
   hJetPt_larger_Jet40_copy1->SetNdivisions(505);
   hJetPt_larger_Jet40_copy1->GetXaxis()->SetRangeUser(0.,250.);
   hJetPt_larger_Jet40_copy1->Draw();
   hJetPt_Jet60_copy1->Draw("same");
   hJetPt_Jet80_copy1->Draw("same");
   hJetPt_Jet100_copy1->Draw("same");

   TLegend *leg2 = new TLegend(0.5,0.2,0.7,0.45,NULL,"brNDC");
   leg2->AddEntry(hJetPt_larger_Jet40_copy1,"Jet40","pl");
   leg2->AddEntry(hJetPt_Jet60_copy1,"Jet60","pl");
   leg2->AddEntry(hJetPt_Jet80_copy1,"Jet80","pl");
   leg2->AddEntry(hJetPt_Jet100_copy1,"Jet100","pl");
   leg2->SetFillStyle(0);
   leg2->SetFillColor(0);
   leg2->SetBorderSize(0);
   leg2->Draw();
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
