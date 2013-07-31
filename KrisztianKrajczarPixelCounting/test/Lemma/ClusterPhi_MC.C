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

  hClusterPhi = new TH1F("hClusterPhi","hClusterPhi",20,-4.,4.);
  hClusterPhiMC = new TH1F("hClusterPhiMC","hClusterPhiMC",20,-4.,4.);

  ntuple->Project("hClusterPhi","phi","rver_z!=0 && bit34 && isTrigger_1 && bit36==0 && bit37==0 && bit38==0 && bit39==0");
  ntupleMC->Project("hClusterPhiMC","phi","bit34 && isTrigger_1 && rver_z!=0");

  hClusterPhi->Sumw2();

  hClusterPhiMC->GetXaxis()->SetTitle("#phi");
  hClusterPhiMC->GetYaxis()->SetTitle("Probability");

  hClusterPhi->SetMarkerStyle(20);
//  hClusterPhi->SetMarkerSize(0.1);
  hClusterPhi->SetMarkerColor(1);

  hClusterPhi->Scale(1./hClusterPhi->Integral());
  hClusterPhiMC->Scale(1./hClusterPhiMC->Integral());

//  hClusterPhi->SetMaximum(0.08);
  hClusterPhi->SetNdivisions(202);


  hClusterPhiMC->SetLineColor(2);
  hClusterPhiMC->Draw();
  hClusterPhi->Draw("Psame");

  TLegend *leg6 = new TLegend(0.25,0.55,0.85,0.65,NULL,"brNDC");
  leg6->AddEntry(hClusterPhi,"Data, event selection","P");
  leg6->AddEntry(hClusterPhiMC,"MC, event selection","L");

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

/*
  hOff_sinh->SetMarkerStyle(26);
  hOff_sinh->SetMarkerSize(0.1);
  hOff_sinh->SetMarkerColor(2);
*/
//  hOff_sinh->Draw("Psame");
/*
  line0 = new TLine(-0.5,-0.1,0.5,-0.1);
  line1_A = new TLine(-1.0,1.9,-0.5,1.9);
  line1_B = new TLine(0.5,1.9,1.0,1.9);
  line2_A = new TLine(-1.5,2.9,-1.,2.9);
  line2_B = new TLine(1.,2.9,1.5,2.9);
  line3_A = new TLine(-2.0,3.9,-1.5,3.9);
  line3_B = new TLine(1.5,3.9,2.,3.9);
  line4_A = new TLine(-2.5,5.9,-2.,5.9);
  line4_B = new TLine(2.,5.9,2.5,5.9);
  line5_A = new TLine(-3.,8.9,-2.5,8.9);
  line5_B = new TLine(2.5,8.9,3.,8.9);
*/
/*
  line0 = new TLine(-0.5,1.,0.5,1.);
  line_V_1 = new TLine(-0.5,1.,-0.5,2.);
  line_V_2 = new TLine(0.5,1.,0.5,2.);
  line_V_3 = new TLine(-1.,2.,-1.,3.);
  line_V_4 = new TLine(1.,2.,1.,3.);
  line_V_5 = new TLine(-1.5,3.,-1.5,4.);
  line_V_6 = new TLine(1.5,3.,1.5,4.);
  line_V_7 = new TLine(-2.,4.,-2.,6.);
  line_V_8 = new TLine(2.,4.,2.,6.);
  line_V_9 = new TLine(-2.5,6.,-2.5,9.);
  line_V_10 = new TLine(2.5,6.,2.5,9.);
  line1_A = new TLine(-1.0,2.,-0.5,2.);
  line1_B = new TLine(0.5,2.,1.0,2.);
  line2_A = new TLine(-1.5,3.,-1.,3.);
  line2_B = new TLine(1.,3.,1.5,3.);
  line3_A = new TLine(-2.0,4.,-1.5,4.);
  line3_B = new TLine(1.5,4.,2.,4.);
  line4_A = new TLine(-2.5,6.,-2.,6.);
  line4_B = new TLine(2.,6.,2.5,6.);
  line5_A = new TLine(-3.,9.,-2.5,9.);
  line5_B = new TLine(2.5,9.,3.,9.);

  line0->SetLineColor(1);
  line_V_1->SetLineColor(1);
  line_V_2->SetLineColor(1);
  line_V_3->SetLineColor(1);
  line_V_4->SetLineColor(1);
  line_V_5->SetLineColor(1);
  line_V_6->SetLineColor(1);
  line_V_7->SetLineColor(1);
  line_V_8->SetLineColor(1);
  line_V_9->SetLineColor(1);
  line_V_10->SetLineColor(1);
  line1_A->SetLineColor(1);
  line1_B->SetLineColor(1);
  line2_A->SetLineColor(1);
  line2_B->SetLineColor(1);
  line3_A->SetLineColor(1);
  line3_B->SetLineColor(1);
  line4_A->SetLineColor(1);
  line4_B->SetLineColor(1);
  line5_A->SetLineColor(1);
  line5_B->SetLineColor(1);

  line0->SetLineWidth(2);
  line_V_1->SetLineWidth(2);
  line_V_2->SetLineWidth(2);
  line_V_3->SetLineWidth(2);
  line_V_4->SetLineWidth(2);
  line_V_5->SetLineWidth(2);
  line_V_6->SetLineWidth(2);
  line_V_7->SetLineWidth(2);
  line_V_8->SetLineWidth(2);
  line_V_9->SetLineWidth(2);
  line_V_10->SetLineWidth(2);
  line1_A->SetLineWidth(2);
  line1_B->SetLineWidth(2);
  line2_A->SetLineWidth(2);
  line2_B->SetLineWidth(2);
  line3_A->SetLineWidth(2);
  line3_B->SetLineWidth(2);
  line4_A->SetLineWidth(2);
  line4_B->SetLineWidth(2);
  line5_A->SetLineWidth(2);
  line5_B->SetLineWidth(2);

  line0->Draw("same");
  line_V_1->Draw("same");
  line_V_2->Draw("same");
  line_V_3->Draw("same");
  line_V_4->Draw("same");
  line_V_5->Draw("same");
  line_V_6->Draw("same");
  line_V_7->Draw("same");
  line_V_8->Draw("same");
  line_V_9->Draw("same");
  line_V_10->Draw("same");
  line1_A->Draw("same");
  line1_B->Draw("same");
  line2_A->Draw("same");
  line2_B->Draw("same");
  line3_A->Draw("same");
  line3_B->Draw("same");
  line4_A->Draw("same");
  line4_B->Draw("same");
  line5_A->Draw("same");
  line5_B->Draw("same");
*/
}
