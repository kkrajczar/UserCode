// Plot the clusterSizeY vs eta

{
  #include "vector.h"

  gROOT->Reset();
//  gROOT->ProcessLine(".x rootlogonChristof.C");
  gROOT->ProcessLine(".x rootlogonChristof.C");
//  gROOT->ProcessLine(".x rootlogonChristof_SmallerCanvas.C");
//  gStyle->SetOptStat(0);
  gROOT->ForceStyle();
  gStyle->SetTitleYOffset(1.4);

  TChain ntuple("multProp_looper");
  for(int i = 1; i<=11; i++) {
    ntuple.Add(Form("crab_0_101105_085004/res/test_sim_%i_1.root",i));
  }

  TChain ntupleMC("multProp_looper");
  for(int i = 1; i<=100; i++) {
    ntupleMC.Add(Form("/net/hibat0002/d00/scratch/krajczar/HI_sim_CMSSW_3_6_1/crab_0_101014_090953/res/HIatom_test_large_%i_1.root",i));
  }

  hPixelDist = new TH1F("hPixelDist","hPixelDist",600,-0.5,599.5);
  hPixelDistMC = new TH1F("hPixelDistMC","hPixelDistMC",600,-0.5,599.5);

  ntuple->Project("hPixelDist","pixels","rver_z!=0 && bit34 && isTrigger_1 && bit36==0 && bit37==0 && bit38==0 && bit39==0");
  ntupleMC->Project("hPixelDistMC","pixels","bit34 && isTrigger_1 && rver_z!=0");

  hPixelDist->Sumw2();

  hPixelDistMC->GetXaxis()->SetTitle("Number of Pixels");
  hPixelDistMC->GetYaxis()->SetTitle("Probability");

  hPixelDist->SetMarkerStyle(20);
//  hPixelDist->SetMarkerSize(0.1);
  hPixelDist->SetMarkerColor(1);

  hPixelDist->Scale(1./hPixelDist->Integral());
  hPixelDistMC->Scale(1./hPixelDistMC->Integral());

//  hPixelDist->SetMaximum(0.08);
  hPixelDist->SetNdivisions(202);


  hPixelDistMC->SetLineColor(2);
  hPixelDistMC->Draw();
  hPixelDist->Draw("Psame");

  TLegend *leg6 = new TLegend(0.25,0.55,0.85,0.65,NULL,"brNDC");
  leg6->AddEntry(hPixelDist,"Data, event selection","P");
  leg6->AddEntry(hPixelDistMC,"MC, event selection","L");

  leg6->SetFillStyle(0);
  leg6->SetFillColor(0);
  leg6->SetBorderSize(0);
  leg6->Draw();

//  TLatex *l_2 = new TLatex(-1.,13.,"No BX selection");
  TLatex *l_2 = new TLatex(1.,0.02.,"Layer 1");
//  TLatex *l_2 = new TLatex(-1.,13.,"bit34 && isTrigger_1 OR bit41");
  l_2->SetTextSize(0.04);
  l_2->Draw("same");

  TLatex *l_3 = new TLatex(-1.,0.05,"run #123596, lumi sec. 69-144");
  l_3->SetTextSize(0.04);
//  l_3->Draw("same");

}
