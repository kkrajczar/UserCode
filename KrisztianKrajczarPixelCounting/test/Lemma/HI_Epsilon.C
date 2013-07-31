{
  gROOT->Reset();
  gROOT->ProcessLine(".x rootlogonChristof.C");
//  gROOT->SetStyle("Plain");
//  gStyle->SetOptStat(0);
   gROOT->ForceStyle();

  TChain ntuple1("multProp");
  for(int i = 1; i<=100; i++) {
    ntuple1.Add(Form("crab_0_101014_090953/res/HIatom_test_large_%i_1.root",i));
  }

  //histograms
  TH1D* hEpsilon = new TH1D("hEpsilon","hEpsilon",50,-0.5,49.5);
  TH1D* hNumEv = new TH1D("hNumEv","hNumEv",2,-0.5,1.5);
  TH1D* hTrigger = new TH1D("hTrigger","hTrigger",2,-0.5,1.5);

  int i = 0;
  char cond[100], condV[500], condVA[100], condVA_etaP[100], condVA_etaN[100], condVA_eta0[100];
  char condVA_etaP1[100], condVA_etaN1[100];
  for(i=0; i<=50; i++)  {

     std::cerr<<" i: " << i << std::endl;
     // reset the histograms
     hNumEv->Reset();
     hTrigger->Reset();  

     // conditions
     sprintf(cond,"cluster_counter==%i",i);
     sprintf(condV,"bit34 && isTrigger_1 && rver_z!=0. && cluster_counter==%i",i);

     // fill histograms
     ntuple1->Project("hNumEv","numEv",cond);
     ntuple1->Project("hTrigger","numEv",condV);

     double numEv = hNumEv->GetBinContent(hNumEv->FindBin(1.));

     //beware
     if(numEv==0)
       continue;

     double numEv_error = hNumEv->GetBinError(hNumEv->FindBin(1.));

     double isTrigger = hTrigger->GetBinContent(hTrigger->FindBin(1.));
     double isTrigger_error = hTrigger->GetBinError(hTrigger->FindBin(1.));

     double epsilon = isTrigger/numEv;
     if(epsilon!=0)
//        double epsilon_error = epsilon*(sqrt((isTrigger_error/isTrigger)**2 + (numEv_error/numEv)**2));
        double epsilon_error = sqrt((epsilon*(1.-epsilon)/numEv));
     else
        double epsilon_error = 1.;
       

     std::cerr<<"When the multiplicity is "<<i<<" the epsilon is "<<epsilon<<std::endl;

     hEpsilon->SetBinContent(hEpsilon->FindBin(i),epsilon);
     hEpsilon->SetBinError(hEpsilon->FindBin(i),epsilon_error);
  }

  // canvas
/*
  TCanvas* c5 = new TCanvas("c5","c5",500,350);
  c5->cd();
  gPad->SetTicks(1,1);
*/
//  gPad->SetLogy();

  // draw
  hEpsilon->GetXaxis()->SetTitle("Selected hits");
  hEpsilon->GetYaxis()->SetTitle("Event selection efficiency");

//  hEpsilon->Rebin(3);
  hEpsilon->Scale(1./hEpsilon->GetBinWidth(0));

  hEpsilon->SetLineStyle(1);
  hEpsilon->SetMarkerStyle(25);
  hEpsilon->SetMarkerSize(0.8);
  hEpsilon->SetMinimum(0.);
  hEpsilon->SetMaximum(1.2);
//  hEpsilon->SetAxisRange(0.,50.);

//  hEpsilon->Draw();
  hEpsilon->Draw("PE");

//  TLegend *leg6 = new TLegend(0.35,0.20,0.93,0.40,NULL,"brNDC");
  TLegend *leg6 = new TLegend(0.35,0.20,0.73,0.40);
  leg6->AddEntry(hEpsilon,"#varepsilon_{bit34 && hf && vtx}","L");

  TLatex *l_2 = new TLatex(4.,1.1,"HI");
  l_2->SetTextSize(0.045);
  l_2->Draw("same");

  TLatex *l_3 = new TLatex(23.,0.42,"#sqrt{s}=??? TeV");
  l_3->SetTextSize(0.045);
//  l_3->Draw("same");

  leg6->SetFillStyle(0);
  leg6->SetFillColor(0);
  leg6->SetBorderSize(0);
  leg6->Draw();

//  c5->Update();
}
