void CompareOnppSide()
{

   gROOT->Reset();
   gROOT->ProcessLine(".x rootlogonChristof.C");
   gROOT->ForceStyle();
   gStyle->SetPalette(1);
   gStyle->SetTitleYOffset(1.30);
//   gStyle->SetPadRightMargin(0.16);

   bool doSave = false;

   TFile *f_nominal_M03M08_combined = new TFile("../PtSpectraCombination_StagedNormalization_EtaCM_M03_M08_TrackTrigger.root");
   TFile *f_nominal_P03P08_combined = new TFile("../PtSpectraCombination_StagedNormalization_EtaCM_P03_P08_TrackTrigger.root");

   TFile *f_reverse_M03M08_combined = new TFile("PtSpectraCombination_StagedNormalization_EtaCM_M03_M08_TrackTrigger.root");
   TFile *f_reverse_P03P08_combined = new TFile("PtSpectraCombination_StagedNormalization_EtaCM_P03_P08_TrackTrigger.root");

   TH1D *h_nominal_spec_M03M08_combined = (TH1D*)f_nominal_M03M08_combined->Get("hSumPartPt");
   TH1D *h_nominal_spec_P03P08_combined = (TH1D*)f_nominal_P03P08_combined->Get("hSumPartPt");

   TH1D *h_reverse_spec_M03M08_combined = (TH1D*)f_reverse_M03M08_combined->Get("hSumPartPt");
   TH1D *h_reverse_spec_P03P08_combined = (TH1D*)f_reverse_P03P08_combined->Get("hSumPartPt");
/*
   //number of events
   TH1D* h_nominal_numev_22_32_M03M08_combined = (TH1D*)f_nominal_M03M08_combined->Get("hNumEv_FullTrack20_22_32_trigCorr");
   TH1D* h_nominal_numev_22_32_P03P08_combined = (TH1D*)f_nominal_P03P08_combined->Get("hNumEv_FullTrack20_22_32_trigCorr");

   TH1D* h_reverse_numev_22_32_P03P08_combined = (TH1D*)f_reverse_P03P08_combined->Get("hNumEv_FullTrack20_22_32_trigCorr");
   TH1D* h_reverse_numev_22_32_M03M08_combined = (TH1D*)f_reverse_M03M08_combined->Get("hNumEv_FullTrack20_22_32_trigCorr");

   double d_nominal_numev_22_32_M03M08_combined = h_nominal_numev_22_32_M03M08_combined->GetBinContent(1);   
   double d_nominal_numev_22_32_P03P08_combined = h_nominal_numev_22_32_P03P08_combined->GetBinContent(1);   

   double d_reverse_numev_22_32_P03P08_combined = h_reverse_numev_22_32_P03P08_combined->GetBinContent(1);   
   double d_reverse_numev_22_32_M03M08_combined = h_reverse_numev_22_32_M03M08_combined->GetBinContent(1);   

   //normalization
   h_nominal_spec_M03M08_combined->Scale(1./d_nominal_numev_22_32_M03M08_combined);
   h_nominal_spec_P03P08_combined->Scale(1./d_nominal_numev_22_32_P03P08_combined);

   h_reverse_spec_P03P08_combined->Scale(1./d_reverse_numev_22_32_P03P08_combined);
   h_reverse_spec_M03M08_combined->Scale(1./d_reverse_numev_22_32_M03M08_combined);
*/
   TCanvas *c0 = new TCanvas("c0","c0");
   c0->cd();
   c0->SetLogy();

   h_nominal_spec_M03M08_combined->SetMarkerStyle(24);
   h_nominal_spec_M03M08_combined->GetXaxis()->SetTitle("p_{T} [GeV/c]");
   h_nominal_spec_M03M08_combined->Draw();

   h_nominal_spec_P03P08_combined->SetMarkerColor(1);
   h_nominal_spec_P03P08_combined->SetLineColor(1);
   h_nominal_spec_P03P08_combined->SetMarkerStyle(20);
   h_nominal_spec_P03P08_combined->Draw("same");

   h_reverse_spec_P03P08_combined->SetMarkerStyle(24);
   h_reverse_spec_P03P08_combined->SetMarkerColor(4);
   h_reverse_spec_P03P08_combined->SetLineColor(4);
   h_reverse_spec_P03P08_combined->Draw("same");

   h_reverse_spec_M03M08_combined->SetMarkerStyle(20);
   h_reverse_spec_M03M08_combined->SetMarkerColor(4);
   h_reverse_spec_M03M08_combined->SetLineColor(4);
   h_reverse_spec_M03M08_combined->Draw("same");

   TLegend *leg0 = new TLegend(0.5,0.6,0.9,0.9,NULL,"brNDC");
   leg0->AddEntry(h_nominal_spec_M03M08_combined,"pPb, combined, -0.8<#eta_{CM}<-0.3","pl");
   leg0->AddEntry(h_nominal_spec_P03P08_combined,"pPb, combined, 0.3<#eta_{CM}<0.8","pl");
   leg0->AddEntry(h_reverse_spec_P03P08_combined,"Pbp, combined, 0.3<#eta_{CM}<0.8","pl");
   leg0->AddEntry(h_reverse_spec_M03M08_combined,"Pbp, combined, -0.8<#eta_{CM}<-0.3","pl");
   leg0->SetFillStyle(0);
   leg0->SetFillColor(0);
   leg0->SetBorderSize(0);
   leg0->Draw();
   if(doSave) {
      c0->SaveAs("Figs/CompareOnppSide_c0.gif");
      c0->SaveAs("Figs/CompareOnppSide_c0.eps");
      c0->SaveAs("Figs/CompareOnppSide_c0.C");
   }


   TCanvas *c1 = new TCanvas("c1","c1");
   c1->cd();
   c1->SetLogx();
   TH1D * h_nominal_spec_M03M08_combined_copy1 = (TH1D*)h_nominal_spec_M03M08_combined->Clone("h_nominal_spec_M03M08_combined_copy1");
   TH1D * h_nominal_spec_P03P08_combined_copy1 = (TH1D*)h_nominal_spec_P03P08_combined->Clone("h_nominal_spec_P03P08_combined_copy1");

   h_nominal_spec_M03M08_combined_copy1->Divide(h_reverse_spec_P03P08_combined);
   h_nominal_spec_P03P08_combined_copy1->Divide(h_reverse_spec_M03M08_combined);

   h_nominal_spec_M03M08_combined_copy1->GetYaxis()->SetTitle("pPb / Pbp");
   h_nominal_spec_M03M08_combined_copy1->SetMinimum(0.8);
   h_nominal_spec_M03M08_combined_copy1->SetMaximum(1.2);
   h_nominal_spec_M03M08_combined_copy1->Draw();

   h_nominal_spec_P03P08_combined_copy1->Draw("same");

   TLegend *leg1 = new TLegend(0.2,0.7,0.8,0.9,NULL,"brNDC");
   leg1->AddEntry(h_nominal_spec_M03M08_combined_copy1,"combined, pPb -0.8<#eta_{CM}<-0.3 / Pbp 0.3<#eta_{CM}<0.8","pl");
   leg1->AddEntry(h_nominal_spec_P03P08_combined_copy1,"combined, pPb 0.3<#eta_{CM}<0.8 / Pbp -0.8<#eta_{CM}<-0.3","pl");
   leg1->SetFillStyle(0);
   leg1->SetFillColor(0);
   leg1->SetBorderSize(0);
   leg1->Draw();
   if(doSave) {
      c1->SaveAs("Figs/CompareOnppSide_c1.gif");
      c1->SaveAs("Figs/CompareOnppSide_c1.eps");
      c1->SaveAs("Figs/CompareOnppSide_c1.C");
   }
}
