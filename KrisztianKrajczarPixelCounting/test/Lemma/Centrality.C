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

  hImpactDistMC = new TH1F("hImpactDistMC","hImpactDistMC",200,0.,20.);
  hImpactDistMC_trig = new TH1F("hImpactDistMC_trig","hImpactDistMC_trig",200,0.,20.);

  ntupleMC->Project("hImpactDistMC","B");
  ntupleMC->Project("hImpactDistMC_trig","B","bit34 && isTrigger_1 && rver_z!=0");

  hImpactDistMC->GetXaxis()->SetTitle("Impact Parameter [cm]");
  hImpactDistMC->GetYaxis()->SetTitle("Probability");
  hImpactDistMC->SetNdivisions(804);

  hImpactDistMC->Scale(1./hImpactDistMC->Integral());
  hImpactDistMC_trig->Scale(1./hImpactDistMC_trig->Integral());
  hImpactDistMC->SetLineColor(1);
  hImpactDistMC_trig->SetLineColor(2);
  hImpactDistMC->Draw();
  hImpactDistMC_trig->Draw("same");

  TLegend *leg6 = new TLegend(0.25,0.55,0.85,0.65,NULL,"brNDC");
  leg6->AddEntry(hImpactDistMC,"Selected clusters, real","L");
  leg6->AddEntry(hImpactDistMC_trig,"Selected clusters, triggered","L");

  leg6->SetFillStyle(0);
  leg6->SetFillColor(0);
  leg6->SetBorderSize(0);
  leg6->Draw();
}
