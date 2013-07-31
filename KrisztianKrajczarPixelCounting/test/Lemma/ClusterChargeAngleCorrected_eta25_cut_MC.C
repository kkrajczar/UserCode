// Plot the clusterSizeY vs eta

{
  #include "vector.h"

  gROOT->Reset();
  gROOT->ProcessLine(".x rootlogonChristof.C");
//  gROOT->ProcessLine(".x rootlogonChristof_SmallerCanvas.C");
//  gStyle->SetOptStat(0);
  gROOT->ForceStyle();
//  gStyle->SetTitleYOffset(1.35);
  gStyle->SetTitleYOffset(1.43);

  TChain ntuple("multProp_looper");
  ntuple.Add("test_nosiminfo.root");

//  for(int i = 1; i<=100; i++) {
//    ntuple.Add(Form("~krajczar/HI/CMSSW_3_6_1/src/UserCode/KrisztianKrajczarPixelCounting/test/crab_0_101014_090953/res/HIatom_test_large_%i_1.root",i));
//  }
  
  TChain ntupleMC("multProp_looper");
  for(int i = 1; i<=100; i++) {
    ntupleMC.Add(Form("~krajczar/HI/CMSSW_3_6_1/src/UserCode/KrisztianKrajczarPixelCounting/test/crab_0_101014_090953/res/HIatom_test_large_%i_1.root",i));
  }

  hChargeDist = new TH1F("hChargeDist","hChargeDist",100,0.,81.);
  hChargeDistMC = new TH1F("hChargeDistMC","hChargeDistMC",100,0.,81.);

//  ntuple->Project("hChargeDist","eloss/1000./cosh(eta)","eta<2. && eta>-2. && rver_z!=0 && bit34 && isTrigger_1 && bit36==0 && bit37==0 && bit38==0 && bit39==0 && L1_BptxMinus!=0 && L1_BptxPlus!=0");
//  ntupleMC->Project("hChargeDistMC","eloss/1000./cosh(eta)","eta<2. && eta>-2. && bit34 && isTrigger_1 && rver_z!=0");

  float eloss = 0.;
  float bit34 = 0.;
  float isTrigger_1 = 0.;
  float eta = 0.;
  float rver_z = 0.;
  float clustSizeY = 0.;
  float bit36 = 0.;
  float bit37 = 0.;
  float bit38 = 0.;
  float bit39 = 0.;
  float L1_BptxPlus = 0.;
  float L1_BptxMinus = 0.;
  ntuple->SetBranchAddress("eloss",&eloss);
  ntuple->SetBranchAddress("bit34",&bit34);
  ntuple->SetBranchAddress("isTrigger_1",&isTrigger_1);
  ntuple->SetBranchAddress("eta",&eta);
  ntuple->SetBranchAddress("rver_z",&rver_z);
  ntuple->SetBranchAddress("clustSizeY",&clustSizeY);
  ntuple->SetBranchAddress("bit36",&bit36);
  ntuple->SetBranchAddress("bit37",&bit37);
  ntuple->SetBranchAddress("bit38",&bit38);
  ntuple->SetBranchAddress("bit39",&bit39);
  ntuple->SetBranchAddress("L1_BptxPlus",&L1_BptxPlus);
  ntuple->SetBranchAddress("L1_BptxMinus",&L1_BptxMinus);
  for( int i = 0; i < ntuple->GetEntries(); i++ ) {
     ntuple->GetEntry(i);
     //trigger
     if(eta>2.5 || eta<-2.5 || isTrigger_1==0. || bit34==0. || rver_z==0.)
       continue;

     //cluster size cuts    
     if(((eta<2.5 && eta>2.0) || (eta<-2.0 && eta>-2.5)) && clustSizeY<5.5)
       continue;
     if(((eta<2.0 && eta>1.5) || (eta<-1.5 && eta>-2.0)) && clustSizeY<3.5)
       continue;
     if(((eta<1.5 && eta>1.0) || (eta<-1.0 && eta>-1.5)) && clustSizeY<2.5)
       continue;
     if(((eta<1.0 && eta>0.5) || (eta<-0.5 && eta>-1.0)) && clustSizeY<1.5)
       continue;
     if(((eta<0.5 && eta>0.0) || (eta<-0.0 && eta>-0.5)) && clustSizeY<0.5)
       continue;

     hChargeDist->Fill(eloss/1000./cosh(eta));
  }

  float elossMC = 0.;
  float bit34MC = 0.;
  float isTrigger_1MC = 0.;
  float etaMC = 0.;
  float rver_zMC = 0.;
  float clustSizeYMC = 0.;
  ntupleMC->SetBranchAddress("eloss",&elossMC);
  ntupleMC->SetBranchAddress("bit34",&bit34MC);
  ntupleMC->SetBranchAddress("isTrigger_1",&isTrigger_1MC);
  ntupleMC->SetBranchAddress("eta",&etaMC);
  ntupleMC->SetBranchAddress("rver_z",&rver_zMC);
  ntupleMC->SetBranchAddress("clustSizeY",&clustSizeYMC);
  for( int i = 0; i < ntupleMC->GetEntries(); i++ ) {
     ntupleMC->GetEntry(i);
     //trigger
     if(etaMC>2.5 || etaMC<-2.5 || isTrigger_1MC==0. || bit34MC==0. || rver_zMC==0.)
       continue;

     //cluster size cuts    
     if(((etaMC<2.5 && etaMC>2.0) || (etaMC<-2.0 && etaMC>-2.5)) && clustSizeYMC<5.5)
       continue;
     if(((etaMC<2.0 && etaMC>1.5) || (etaMC<-1.5 && etaMC>-2.0)) && clustSizeYMC<3.5)
       continue;
     if(((etaMC<1.5 && etaMC>1.0) || (etaMC<-1.0 && etaMC>-1.5)) && clustSizeYMC<2.5)
       continue;
     if(((etaMC<1.0 && etaMC>0.5) || (etaMC<-0.5 && etaMC>-1.0)) && clustSizeYMC<1.5)
       continue;
     if(((etaMC<0.5 && etaMC>0.0) || (etaMC<-0.0 && etaMC>-0.5)) && clustSizeYMC<0.5)
       continue;

     hChargeDistMC->Fill(elossMC/1000./cosh(etaMC));
  } 

  hChargeDist->Sumw2();

  hChargeDistMC->GetXaxis()->SetTitle("Angle corrected cluster charge [ke]");
  hChargeDistMC->GetYaxis()->SetTitle("Fraction of events");

  hChargeDist->SetMarkerStyle(20);
  hChargeDist->SetMarkerColor(1);

  hChargeDist->Scale(1./hChargeDist->Integral());
  hChargeDistMC->Scale(1./hChargeDistMC->Integral());

//  hChargeDist->SetMaximum(0.08);
  hChargeDistMC->SetNdivisions(506);


  hChargeDistMC->SetLineColor(2);
  hChargeDistMC->Draw();
  hChargeDist->Draw("Psame");

  TLegend *leg6 = new TLegend(0.25,0.55,0.85,0.65,NULL,"brNDC");
  leg6->AddEntry(hChargeDist,"Data, event selection","P");
  leg6->AddEntry(hChargeDistMC,"MC, event selection","L");

  leg6->SetFillStyle(0);
  leg6->SetFillColor(0);
  leg6->SetBorderSize(0);
  leg6->Draw();

  TLatex *l_2 = new TLatex(1.,0.02.,"Layer 3");
  l_2->SetTextSize(0.04);
  l_2->Draw("same");

  TLatex *l_3 = new TLatex(-1.,0.03,"-1.5<#eta<1.5");
  l_3->SetTextSize(0.04);
  l_3->Draw("same");

  TLatex *l_4 = new TLatex(-1.,0.035,"7 TeV");
  l_4->SetTextSize(0.04);
  l_4->Draw("same");

  TLatex *l_5 = new TLatex(-1.,0.04,"Cluster length cut");
  l_5->SetTextSize(0.04);
  l_5->Draw("same");

}
