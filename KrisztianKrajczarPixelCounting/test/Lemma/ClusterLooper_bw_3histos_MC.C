{
  gROOT->Reset();
  gROOT->ProcessLine(".x rootlogonChristof.C");
//  gStyle->SetOptStat(0);
  gROOT->ForceStyle();
  gStyle->SetTitleYOffset(1.35);

  TChain ntuple1("multProp_looper");
  for(int i = 1; i<=10; i++) {
    ntuple1.Add(Form("crab_0_101013_092513/res/HIatom_test_large_%i_1.root",i));
  }

  TChain ntuple2("hJustLooper");
  for(int i = 1; i<=10; i++) {
    ntuple2.Add(Form("crab_0_101013_092513/res/HIatom_test_large_%i_1.root",i));
  }

  TH1D* hEloss = new TH1D("hEloss","hEloss",21,-0.5,20.5);
  TH1D* hAll = new TH1D("hAll","hAll",21,-0.5,20.5);
  TH1D* hAll3 = new TH1D("hAll3","hAll3",21,-0.5,20.5);

  TH1D* hEloss_2 = new TH1D("hEloss_2","hEloss_2",21,-0.5,20.5);
  TH1D* hAll_2 = new TH1D("hAll_2","hAll_2",21,-0.5,20.5);
  TH1D* hAll3_2 = new TH1D("hAll3_2","hAll3_2",21,-0.5,20.5);

//  ntuple2->Project("hEloss","clustSizeY","rver_z!=0 && bit34 && isTrigger_1 && eta>-2.0 && eta<-1.5");
//  ntuple1->Project("hAll","clustSizeY","rver_z!=0 && bit34 && isTrigger_1 && eta>-2.0 && eta<-1.5");
//  ntuple1->Project("hAll3","clustSizeY","rver_z!=0 && bit34 && isTrigger_1 && eta>-2.0 && eta<-1.5 && clustSizeY<3.5");

//NOTRIGGERINFO!!:
  ntuple2->Project("hEloss","clustSizeY","rver_z!=0 && eta>-2.0 && eta<-1.5");
  ntuple1->Project("hAll","clustSizeY","rver_z!=0 && eta>-2.0 && eta<-1.5");
  ntuple1->Project("hAll3","clustSizeY","rver_z!=0 && eta>-2.0 && eta<-1.5 && clustSizeY<3.5");

  ntuple2->Project("hEloss_2","clustSizeY","rver_z!=0 && eta>-1.5 && eta<-1.0");
  ntuple1->Project("hAll_2","clustSizeY","rver_z!=0 && eta>-1.5 && eta<-1.0");
  ntuple1->Project("hAll3_2","clustSizeY","rver_z!=0 && eta>-1.5 && eta<-1.0 && clustSizeY<2.5");

  hEloss->GetXaxis()->SetTitle("Cluster size");
  hEloss->GetYaxis()->SetTitle("Entries");

//  double Correction2 = hEloss->GetEntries()/hAll3->GetEntries();
//  std::cerr<<"Correction2: "<<Correction2<<std::endl;

//  hAll->SetMinimum(0.);
//  hAll->SetMinimum(2000.);
  hAll->GetXaxis()->SetRange(0.,700.);

  hAll->SetLineStyle(7);
  hAll->Draw();
  hAll_2->SetLineStyle(7);
  hAll_2->SetLineColor(2);
  hAll_2->Draw("same");

  hEloss->SetLineStyle(1);
  hEloss->Draw("same");
  hEloss_2->SetLineStyle(1);
  hEloss_2->SetLineColor(2);
  hEloss_2->Draw("same");

  hAll3->SetLineStyle(8);
  hAll3->Draw("same");
  hAll3_2->SetLineStyle(8);
  hAll3_2->SetLineColor(2);
  hAll3_2->Draw("same");

  hAll->GetXaxis()->SetTitle("Cluster size");
  hAll->GetYaxis()->SetTitle("Entries");

  TLegend *leg6 = new TLegend(0.67,0.80,0.94,0.94,NULL,"brNDC");
  leg6->AddEntry(hAll,"MC, all hits","L");
  leg6->AddEntry(hAll3,"MC, all hits below the cut","L");
  leg6->AddEntry(hEloss,"MC, looper hits below the cut","L");

  leg6->SetFillColor(0);
  leg6->SetBorderSize(0);
  leg6->Draw();

  TLatex *l_1 = new TLatex(-4.5,47,"-2<#eta<-1.5");
  l_1->Draw("same");
}
