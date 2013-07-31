{
  gROOT->Reset();
//  gROOT->ProcessLine(".x rootlogonChristof_SmallerCanvas.C");
  gROOT->ProcessLine(".x rootlogonChristof.C");
//  gStyle->SetOptStat(0);
  gROOT->ForceStyle();
  gStyle->SetTitleYOffset(1.35);

  TCanvas MyCanvas("MyCanvas","My Canvas");

  TChain ntuple("nDist");
  ntuple.Add("clusters_DATA.root");

  TChain ntupleMC("nDist");
  ntupleMC.Add("clusters_SIM.root");

//  TH1D* hDistData = new TH1D("hDistData","hDistData",80,0.,0.2);
//  TH1D* hDataMC = new TH1D("hDistMC","hDistMC",80,0.,0.2);
  TH1D* hDistData = new TH1D("hDistData","hDistData",80,0.,2.);
  TH1D* hDataMC = new TH1D("hDistMC","hDistMC",80,0.,2.);

  hDistData->Sumw2();

  ntuple->Project("hDistData","min","layer==1");
  ntupleMC->Project("hDistMC","min","layer==1");

  hDistData->Scale(1./hDistData->Integral());
  hDistMC->Scale(1./hDistMC->Integral());
    
  hDistMC->SetLineColor(2);

//  hDistData->SetMarkerSize(0.8);
  hDistData->SetMarkerStyle(25);

//  hDistData->GetXaxis()->SetTitle("Minimal distance between clusters [cm]");
//  hDistData->GetYaxis()->SetTitle("Arbitrary");
  hDistMC->GetXaxis()->SetTitle("Minimal distance between clusters [cm]");
  hDistMC->GetYaxis()->SetTitle("Arbitrary");

  hDistMC->SetNdivisions(508);

//  hDistMC->SetMaximum(0.06);

  hDistMC->Draw();
  hDistData->Draw("psame");

  TLatex *l_2 = new TLatex(0.1.,0.01,"1. barrel layer");
  l_2->SetTextSize(0.045);
  l_2->Draw("same");

  TLegend *leg6 = new TLegend(0.35,0.55,1.1,0.85,NULL,"brNDC");
  leg6->AddEntry(hDistData,"Data after event selection","P");
  leg6->AddEntry(hDistMC,"MC after event selection","L");

  leg6->SetFillStyle(0);
  leg6->SetFillColor(0);
  leg6->SetBorderSize(0);
  leg6->Draw();
}
