// Plot the clusterSizeY vs eta

{
  #include "vector.h"

  gROOT->Reset();
//  gROOT->ProcessLine(".x rootlogonChristof.C");
  gROOT->ProcessLine(".x rootlogonChristof.C");
//  gROOT->ProcessLine(".x rootlogonChristof_SmallerCanvas.C");
//  gStyle->SetOptStat(0);
  gROOT->ForceStyle();
  gStyle->SetTitleYOffset(1.35);

  TFile fOn("test_sim_391_1075ev.root");
  TFile fOff("test_sim_391_1075ev.root");

  TNtuple * nmult = (TNtuple*)fOn.Get("multProp");

  TH1F * hrver_z = new TH1F("hrver_z","hrver_z",60,-30.,30.);

  nmult->Project("hrver_z","rver_z","rver_z!=0 && bit40 && bit36==0 && bit37==0 && bit38==0 && bit39==0 && L1_BptxMinus!=0 && L1_BptxPlus!=0");

  hrver_z->GetXaxis()->SetTitle("z [cm]");
  hrver_z->GetYaxis()->SetTitle("number of vertices");
//  hrver_z->SetMaximum(170.);

  hrver_z->SetMaximum(250.);
  hrver_z->SetMarkerStyle(24);
  hrver_z->SetMarkerSize(0.1);
  hrver_z->SetMarkerColor(1);
  hrver_z->Draw();

  Double_t x_max = hrver_z->GetXaxis()->GetXmax();
  Double_t y_max = hrver_z->GetMaximum();
//  TLatex *l = new TLatex(-x_max*(7./10.),y_max*(8./10.),"Data, run #123596, bit41 OR bit41");
  TLatex *l = new TLatex(-x_max*(7./10.),y_max*(8./10.),"run #123596, bit41, BPTX coinc, veto on BH");
  l->SetTextSize(0.045);
//  l->Draw("same");

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
