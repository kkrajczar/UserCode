{
  gROOT->Reset();
//  gROOT->ProcessLine(".x rootlogonChristof.C");
//  gROOT->ProcessLine(".x rootlogonChristof_SmallerCanvas.C");
  gROOT->ProcessLine(".x rootlogonChristof.C");
//  gStyle->SetOptStat(0);
  gROOT->ForceStyle();
  gStyle->SetTitleYOffset(1.35);

  TCanvas MyCanvas("MyCanvas","My Canvas");

  TFile f("HIatom_test_large.root");
  TNtuple * ntuple1 = (TNtuple*)f.Get("multProp_looper");
  TH1D* hDist = new TH1D("hDist","hDist",30,0.,30.);
  TH1D* hDist_vtx = new TH1D("hDist_vtx","hDist_vtx",30,0.,30.);

  TChain ntupleMC("multProp_looper");
  ntupleMC.Add("HIatom_test_large.root");

  TH1D* hDistMC_vtx = new TH1D("hDistMC_vtx","hDistMC_vtx",30,0.,30.);
  
  char cond[300], cond_vtx[300], condMC_vtx[300];

    sprintf(cond,"isTrigger_1 && bit36==0 && bit37==0 && bit38==0 && bit39==0 && bit34 && eta>-2.0 && eta<-1.5");
    sprintf(cond_vtx,"isTrigger_1 && bit36==0 && bit37==0 && bit38==0 && bit39==0 && bit34 && rver_z!=0 && eta>-2.0 && eta<-1.5");
    sprintf(condMC_vtx,"isTrigger_1 && bit34 && rver_z!=0 && eta>-2.0 && eta<-1.5");
    hDist->Reset();
    hDist_vtx->Reset();
    ntuple1->Project("hDist","clustSizeY",cond);
    ntuple1->Project("hDist_vtx","clustSizeY",cond_vtx);
//    hDist->Draw();
    hDist_vtx->SetLineColor(1);
//    hDist_vtx->Draw("same");

    ntupleMC->Project("hDistMC_vtx","clustSizeY",condMC_vtx);
    
    hDist_vtx->Sumw2();
//    hDistMC_vtx->Sumw2();

    hDist_vtx->SetMarkerStyle(20);
    hDist_vtx->SetMarkerColor(1);
//    hDistMC_vtx->SetMarkerStyle(20);
//    hDistMC_vtx->SetMarkerColor(2);

    hDist_vtx->Scale(1./hDist_vtx->Integral());
    hDistMC_vtx->Scale(1./hDistMC_vtx->Integral());

    hDistMC_vtx->GetXaxis()->SetTitle("cluster size");
    hDistMC_vtx->GetYaxis()->SetTitle("Probability");

    hDistMC_vtx->SetLineColor(2);
//    hDistMC_vtx->Draw("same");
    hDistMC_vtx->Draw();

    hDist_vtx->Draw("same");

    Double_t x_max = hDist->GetXaxis()->GetXmax();
    Double_t y_max = 0.1;

//    TLatex *l = new TLatex(x_max*(7./10.),y_max*(7./10.),Form("%1.1f<#eta<%1.1f",(-3.+0.2*i),(-3.+0.2*(i+1))));
    TLatex *l = new TLatex(x_max*(7./10.),y_max*(7./10.),"-1.5<#eta<-1.0");
    l->SetTextSize(0.045);
    l->Draw("same");

//    TLatex *l = new TLatex(x_max*(7./10.),y_max*(6./10),"layer 1");
    TLatex *l = new TLatex(0.,0.01,"layer 1");
    l->SetTextSize(0.045);
    l->Draw("same");

    TLatex *l = new TLatex(x_max*(0.1/10.),y_max*(5./10.),"veto on bit 36, bit37, bit38 and bit39");
    l->SetTextSize(0.045);
//    l->Draw("same");

    TLegend *leg6 = new TLegend(0.45,0.30,1.0,0.50);
    leg6->AddEntry(hDistMC_vtx,"MC after event selection","L");
    leg6->AddEntry(hDist_vtx,"Data after event selection","P");

    leg6->SetFillStyle(0);
    leg6->SetFillColor(0);
    leg6->SetBorderSize(0);
    leg6->Draw();

    TLatex *l_2 = new TLatex(4.,1.1,"CMS Preliminary");
    l_2->SetTextSize(0.045);
  //  l_2->Draw("same");


}
