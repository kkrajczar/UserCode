// Plot the clusterSizeY vs eta

{
  #include "vector.h"

  gROOT->Reset();
  gROOT->ProcessLine(".x rootlogonChristof.C");
//  gStyle->SetOptStat(0);
  gROOT->ForceStyle();
  gStyle->SetTitleYOffset(1.35);

  TChain ntuple("multProp_looper");
  for(int i = 1; i<=100; i++) {
    ntuple.Add(Form("crab_0_101014_090953/res/HIatom_test_large_%i_1.root",i));
  }

  TChain ntuple_mc("multProp_looper");
  for(int i = 1; i<=100; i++) {
    ntuple_mc.Add(Form("crab_0_101014_090953/res/HIatom_test_large_%i_1.root",i));
  }

  hSizeData_sel = new TH1F("hSizeData_sel","hSizeData_sel",50,-0.5,49.5);
  hSizeData_mc = new TH1F("hSizeData_mc","hSizeData_mc",50,-0.5,49.5);

  ntuple_mc->Project("hSizeData_mc","clustSizeY","rver_z!=0 && bit34 && isTrigger_1");
  ntuple->Project("hSizeData_sel","clustSizeY","rver_z!=0 && bit34 && isTrigger_1");

  hSizeData_mc->GetXaxis()->SetTitle("Cluster size in local y");
  hSizeData_mc->GetYaxis()->SetTitle("Arbitrary");
//  hSizeData_mc->SetMaximum(170.);

//  hSizeData_mc->Sumw2();
  hSizeData_sel->Sumw2();

  hSizeData_mc->Scale(1./hSizeData_mc->Integral());
  hSizeData_sel->Scale(1./hSizeData_sel->Integral());

//  hSizeData_mc->SetMarkerStyle(20);
//  hSizeData_mc->SetMarkerSize(0.8);
  hSizeData_mc->SetLineColor(2);
  hSizeData_mc->Draw();

  hSizeData_sel->SetMarkerColor(1);
  hSizeData_sel->SetMarkerStyle(20);
//  hSizeData_sel->SetMarkerSize(0.8);
  hSizeData_sel->Draw("Psame");

  TLatex *l_2 = new TLatex(10.,0.1,"layer 1");
//  TLatex *l_2 = new TLatex(-1.,13.,"bit40 OR bit40");
  l_2->SetTextSize(0.04);
  l_2->Draw("same");

  TLatex *l_3 = new TLatex(10.,0.1,"veto on bit36, bit37, bit38, bit39");
  l_3->SetTextSize(0.04);
//  l_3->Draw("same");

  TLegend *leg6 = new TLegend(0.45,0.45,0.95,0.65,NULL,"brNDC");
  leg6->AddEntry(hSizeData_mc,"MC, event selection","L");
  leg6->AddEntry(hSizeData_sel,"Data, event selection","P");

  leg6->SetFillStyle(0);
  leg6->SetFillColor(0);
  leg6->SetBorderSize(0);
//  leg6->Draw();
}
