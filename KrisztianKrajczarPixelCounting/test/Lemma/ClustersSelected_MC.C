// plot cluster_counter

{
  #include "vector.h"

  gROOT->Reset();
//  gROOT->ProcessLine(".x rootlogonChristof.C");
  gROOT->ProcessLine(".x rootlogonChristof.C");
//  gROOT->ProcessLine(".x rootlogonChristof_SmallerCanvas.C");
//  gStyle->SetOptStat(0);
  gROOT->ForceStyle();
  gStyle->SetTitleYOffset(1.4);

  TChain ntupleMC("multProp");
  for(int i = 1; i<=100; i++) {
    ntupleMC.Add(Form("crab_0_101014_090953/res/HIatom_test_large_%i_1.root",i));
  }

  hChargeDistMC = new TH1F("hChargeDistMC","hChargeDistMC",240,0.,12000.);
  hChargeDistMC_trig = new TH1F("hChargeDistMC_trig","hChargeDistMC_trig",240,0.,12000.);

  ntupleMC->Project("hChargeDistMC","cluster_counter");
  ntupleMC->Project("hChargeDistMC_trig","cluster_counter","bit34 && isTrigger_1 && rver_z!=0");

  hChargeDistMC->GetXaxis()->SetTitle("Number of clusters");
  hChargeDistMC->GetYaxis()->SetTitle("Probability");
  hChargeDistMC->SetNdivisions(804);

  hChargeDistMC->Scale(1./hChargeDistMC->Integral());
  hChargeDistMC_trig->Scale(1./hChargeDistMC_trig->Integral());
  hChargeDistMC->SetLineColor(1);
  hChargeDistMC_trig->SetLineColor(2);
  hChargeDistMC->Draw();
  hChargeDistMC_trig->Draw("same");

  TLegend *leg6 = new TLegend(0.25,0.55,0.85,0.65,NULL,"brNDC");
  leg6->AddEntry(hChargeDistMC,"Selected clusters, real","L");
  leg6->AddEntry(hChargeDistMC_trig,"Selected clusters, triggered","L");

  leg6->SetFillStyle(0);
  leg6->SetFillColor(0);
  leg6->SetBorderSize(0);
  leg6->Draw();
}
