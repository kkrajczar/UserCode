


#include "hiForest.h"
#include "TStyle.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TH3.h"
#include "TH2.h"
#include "TH1.h"
#include "TNtuple.h"
#include "TMath.h"

#include "TCut.h"
#include <string>

using namespace std;

void CheckClosure_MyCorrections(
		 const char* infname = "/net/hisrv0001/home/yenjie/scratch/hiForest/prod/production/CMSSW_4_4_2_patch6/test/forest21_simTrack/merged_pthat80_simTrack_v2.root"
		 ) {

  gROOT->Reset();
  gROOT->ProcessLine(".x rootlogonChristof.C");
  gROOT->ForceStyle();
  gStyle->SetPalette(1);

  //Define binning	
  const Double_t small = 1e-3;

  std::vector<Double_t> ptBins;
  Double_t pt;
  for(pt =   0  ; pt <   1.0-small; pt +=  0.15) ptBins.push_back(pt); //8 bins
  for(pt =   1.0; pt <   2.2-small; pt +=  0.1) ptBins.push_back(pt); //12 bins
  for(pt =   2.2; pt <   6.0-small; pt +=  0.475) ptBins.push_back(pt); //8 bins
  for(pt =   6.0; pt <  22.-small; pt +=  2. ) ptBins.push_back(pt); // 8 bins
//  Double_t highPtBins[8] = {22.,30.,45.,60.,90.,120.,180.,300.};
//  ptBins.insert(ptBins.end(),highPtBins,highPtBins+8);
  ptBins.push_back(22.);
  ptBins.push_back(30.);
  ptBins.push_back(45.);
  ptBins.push_back(60.);
  ptBins.push_back(90.);
  ptBins.push_back(120.);
  ptBins.push_back(180.);
  ptBins.push_back(300.);

  std::vector<Double_t> etaBins;
  Double_t eta;
  for(eta = -2.4; eta < 2.4-small; eta += 0.1) etaBins.push_back(eta);
  etaBins.push_back(2.4);

  std::vector<Double_t> phiBins;
  Double_t phi;
  for(phi = -TMath::Pi(); phi < TMath::Pi()-small; phi += 0.1) phiBins.push_back(phi);
  phiBins.push_back(TMath::Pi());

  HiForest * t = new HiForest(infname);
  t->InitTree();

  //Define histos
  TH1D *hSimPt = new TH1D("hSimPt","hSimPt",ptBins.size()-1,&ptBins[0]);
  TH1D *hSimEta = new TH1D("hSimEta","hSimEta",etaBins.size()-1,&etaBins[0]);
  TH1D *hSimEta_Cent_0_3 = new TH1D("hSimEta_Cent_0_3","hSimEta_Cent_0_3",etaBins.size()-1,&etaBins[0]);
  TH1D *hSimEta_pT_06_14 = new TH1D("hSimEta_pT_06_14","hSimEta_pT_06_14",etaBins.size()-1,&etaBins[0]);
  TH1D *hSimEta_pT_16_18 = new TH1D("hSimEta_pT_16_18","hSimEta_pT_16_18",etaBins.size()-1,&etaBins[0]);
  TH1D *hSimEta_pT_18_3 = new TH1D("hSimEta_pT_18_3","hSimEta_pT_18_3",etaBins.size()-1,&etaBins[0]);
  TH1D *hSimEta_pT_3_8 = new TH1D("hSimEta_pT_3_8","hSimEta_pT_3_8",etaBins.size()-1,&etaBins[0]);
  TH1D *hSimPhi = new TH1D("hSimPhi","hSimPhi",phiBins.size()-1,&phiBins[0]);

  TH1D *hCorrRecPt = new TH1D("hCorrRecPt","hCorrRecPt",ptBins.size()-1,&ptBins[0]);
  TH1D *hRecEta = new TH1D("hRecEta","hRecEta",etaBins.size()-1,&etaBins[0]);
  TH1D *hCorrRecEta = new TH1D("hCorrRecEta","hCorrRecEta",etaBins.size()-1,&etaBins[0]);
  TH1D *hRecPhi = new TH1D("hRecPhi","hRecPhi",phiBins.size()-1,&phiBins[0]);
  TH1D *hCorrRecPhi = new TH1D("hCorrRecPhi","hCorrRecPhi",phiBins.size()-1,&phiBins[0]);
  TH1D *hCorrRecEta_Cent_0_3 = new TH1D("hCorrRecEta_Cent_0_3","hCorrRecEta_Cent_0_3",etaBins.size()-1,&etaBins[0]);
  TH1D *hCorrRecEta_pT_06_14 = new TH1D("hCorrRecEta_pT_06_14","hCorrRecEta_pT_06_14",etaBins.size()-1,&etaBins[0]);
  TH1D *hCorrRecEta_pT_16_18 = new TH1D("hCorrRecEta_pT_16_18","hCorrRecEta_pT_16_18",etaBins.size()-1,&etaBins[0]);
  TH1D *hCorrRecEta_pT_18_3 = new TH1D("hCorrRecEta_pT_18_3","hCorrRecEta_pT_18_3",etaBins.size()-1,&etaBins[0]);
  TH1D *hCorrRecEta_pT_3_8 = new TH1D("hCorrRecEta_pT_3_8","hCorrRecEta_pT_3_8",etaBins.size()-1,&etaBins[0]);

  hSimPt->Sumw2();
  hSimEta->Sumw2();
  hSimPhi->Sumw2();
  hSimEta_Cent_0_3->Sumw2();
  hSimEta_pT_06_14->Sumw2();
  hSimEta_pT_16_18->Sumw2();
  hSimEta_pT_18_3->Sumw2();
  hSimEta_pT_3_8->Sumw2();
  hCorrRecPt->Sumw2();
  hRecEta->Sumw2();
  hCorrRecEta->Sumw2();
  hRecPhi->Sumw2();
  hCorrRecPhi->Sumw2();
  hCorrRecEta_Cent_0_3->Sumw2();
  hCorrRecEta_pT_06_14->Sumw2();
  hCorrRecEta_pT_16_18->Sumw2();
  hCorrRecEta_pT_18_3->Sumw2();
  hCorrRecEta_pT_3_8->Sumw2();

  //Get AccWeights
  //Read acceptance corr.
  TFile *fAccCorr = TFile::Open("AcceptanceWeights.root");
  TH2D * hSim3D_eta_phi_inclusive = (TH2D*)fAccCorr->Get("hSim3D_eta_phi_clone");
  TH2D * hSim3D_eta_phi_pT_05_14 = (TH2D*)fAccCorr->Get("hSim3D_eta_phi_pT_06_14_clone");
  TH2D * hSim3D_eta_phi_pT_14_16 = (TH2D*)fAccCorr->Get("hSim3D_eta_phi_pT_14_16_clone");
  TH2D * hSim3D_eta_phi_pT_16_18 = (TH2D*)fAccCorr->Get("hSim3D_eta_phi_pT_16_18_clone");
  TH2D * hSim3D_eta_phi_pT_18_3 = (TH2D*)fAccCorr->Get("hSim3D_eta_phi_pT_18_3_clone");
  TH2D * hSim3D_eta_phi_pT_3_8 = (TH2D*)fAccCorr->Get("hSim3D_eta_phi_pT_3_8_clone");
  TH2D * hSim3D_eta_phi_pT_8_20 = (TH2D*)fAccCorr->Get("hSim3D_eta_phi_pT_8_20_clone");
  TH2D * hSim3D_eta_phi_pT_20_Inf = (TH2D*)fAccCorr->Get("hSim3D_eta_phi_pT_20_Inf_clone");
//  fAccCorr->Close();

  //Get CentWeights
  //Read centrality corr.
  TFile *fCentCorr = TFile::Open("CentralityWeights.root");
  TF1 *fFitCent_05_14 = (TF1*)fCentCorr->Get("fFitCent_05_14");
  TF1 *fFitCent_14_18 = (TF1*)fCentCorr->Get("fFitCent_14_18");
  TF1 *fFitCent_18_3 = (TF1*)fCentCorr->Get("fFitCent_18_3");
  TF1 *fFitCent_3_8 = (TF1*)fCentCorr->Get("fFitCent_3_8");
  TF1 *fFitCent_8_20 = (TF1*)fCentCorr->Get("fFitCent_8_20");
  TF1 *fFitCent_20_Inf = (TF1*)fCentCorr->Get("fFitCent_20_Inf");
//  fCentCorr->Close();

  
  //Event loop
  int maxEvents = t->GetEntries();
  maxEvents = 20000.;
  for(int iev = 0; iev < maxEvents; ++iev) {
     if(iev%1000==0)cout<<"Processing entry : "<<iev<<" / "<<t->GetEntries()<<endl;
     t->GetEntry(iev);

     int cent = t->evt.hiBin;

     for(int i = 0; i < t->track.nParticle; ++i) {

        double simPt = t->track.pPt[i];
        double simEta = t->track.pEta[i];
        double simPhi = t->track.pPhi[i];
/*
        std::cerr<<"   simPt: " << simPt << std::endl;
        std::cerr<<"   simEta: " << simEta << std::endl;
        std::cerr<<"   simPhi: " << simPhi << std::endl;
*/
        double weight_acc = 0.;
        double weight_cent = 0.;
        TF1 *funCentCorr;

        if(simPt>0.5 && simPt<1.4) {
           weight_acc = hSim3D_eta_phi_pT_05_14->GetBinContent(hSim3D_eta_phi_pT_05_14->GetXaxis()->FindBin(simEta),hSim3D_eta_phi_pT_05_14->GetYaxis()->FindBin(simPhi));
           funCentCorr = fFitCent_05_14;
        }
        if(simPt>1.4 && simPt<1.6) {
           weight_acc = hSim3D_eta_phi_pT_14_16->GetBinContent(hSim3D_eta_phi_pT_14_16->GetXaxis()->FindBin(simEta),hSim3D_eta_phi_pT_14_16->GetYaxis()->FindBin(simPhi));
           funCentCorr = fFitCent_14_18;
        }
        if(simPt>1.6 && simPt<1.8) {
           weight_acc = hSim3D_eta_phi_pT_16_18->GetBinContent(hSim3D_eta_phi_pT_16_18->GetXaxis()->FindBin(simEta),hSim3D_eta_phi_pT_16_18->GetYaxis()->FindBin(simPhi));
           funCentCorr = fFitCent_14_18;
        }
        if(simPt>1.8 && simPt<3.) {
           weight_acc = hSim3D_eta_phi_pT_18_3->GetBinContent(hSim3D_eta_phi_pT_18_3->GetXaxis()->FindBin(simEta),hSim3D_eta_phi_pT_18_3->GetYaxis()->FindBin(simPhi));
           funCentCorr = fFitCent_18_3;
        }
        if(simPt>3. && simPt<8.) {
           weight_acc = hSim3D_eta_phi_pT_3_8->GetBinContent(hSim3D_eta_phi_pT_3_8->GetXaxis()->FindBin(simEta),hSim3D_eta_phi_pT_3_8->GetYaxis()->FindBin(simPhi));
           funCentCorr = fFitCent_3_8;
        }
        if(simPt>8. && simPt<20.) {
           weight_acc = hSim3D_eta_phi_pT_8_20->GetBinContent(hSim3D_eta_phi_pT_8_20->GetXaxis()->FindBin(simEta),hSim3D_eta_phi_pT_8_20->GetYaxis()->FindBin(simPhi));
           funCentCorr = fFitCent_8_20;
        }
        if(simPt>20) {
           weight_acc = hSim3D_eta_phi_pT_20_Inf->GetBinContent(hSim3D_eta_phi_pT_20_Inf->GetXaxis()->FindBin(simEta),hSim3D_eta_phi_pT_20_Inf->GetYaxis()->FindBin(simPhi));
           funCentCorr = fFitCent_20_Inf;
        }

        weight_cent = funCentCorr->Eval(cent);

        hSimPt->Fill(simPt);
        hSimPhi->Fill(simPhi);
        hSimEta->Fill(simEta);
        if(cent<4)
          hSimEta_Cent_0_3->Fill(simEta);
        if(simPt>0.6 && simPt<1.4)
          hSimEta_pT_06_14->Fill(simEta);
        if(simPt>1.6 && simPt<1.8)
          hSimEta_pT_16_18->Fill(simEta);
        if(simPt>1.8 && simPt<3.)
          hSimEta_pT_18_3->Fill(simEta);
        if(simPt>3. && simPt<8.)
          hSimEta_pT_3_8->Fill(simEta);

        if(t->track.pNRec[i]==1 && (t->track.mtrkQual[i]==1 || t->track.mtrkAlgo[i]<4)) {
           hCorrRecPt->Fill(simPt,weight_acc/weight_cent);
           hRecEta->Fill(simPhi);
           hCorrRecEta->Fill(simEta,weight_acc/weight_cent);
           hRecPhi->Fill(simPhi);
           hCorrRecPhi->Fill(simPhi,weight_acc/weight_cent);
           if(cent<4)
              hCorrRecEta_Cent_0_3->Fill(simEta,weight_acc/weight_cent);
           if(simPt>0.6 && simPt<1.4)
             hCorrRecEta_pT_06_14->Fill(simEta,weight_acc/weight_cent);
           if(simPt>1.6 && simPt<1.8)
             hCorrRecEta_pT_16_18->Fill(simEta,weight_acc/weight_cent);
           if(simPt>1.8 && simPt<3.)
             hCorrRecEta_pT_18_3->Fill(simEta,weight_acc/weight_cent);
           if(simPt>3. && simPt<8.)
             hCorrRecEta_pT_3_8->Fill(simEta,weight_acc/weight_cent);
        }
 
     }
 
  }


  TCanvas *c1 = new TCanvas("c1","c1");
  c1->cd();

  hSimPhi->GetXaxis()->SetTitle("#phi");
  hSimPhi->GetYaxis()->SetTitleOffset(1.5);
  hSimPhi->GetYaxis()->SetTitle("Entries");
  gStyle->SetPadLeftMargin(0.18);
  hSimPhi->Draw();

  hCorrRecPhi->SetLineColor(2);
  hCorrRecPhi->Draw("same");

  hRecPhi->SetLineColor(6);
  hRecPhi->Draw("same");

  TLegend *leg1 = new TLegend(0.20,0.65,0.92,0.90,NULL,"brNDC");
  leg1->AddEntry(hSimPhi,"Sim","l");
  leg1->AddEntry(hRecPhi,"Matched sim","l");
  leg1->AddEntry(hCorrRecPhi,"Acc.+cent. weighted matched sim","l");
  leg1->SetFillStyle(0);
  leg1->SetFillColor(0);
  leg1->SetBorderSize(0);
  leg1->Draw();


  TCanvas *c2 = new TCanvas("c2","c2");
  c2->cd();

  TH1D *hSimPhi_clone_v1 = (TH1D*)hSimPhi->Clone("hSimPhi_clone_v1");
  TH1D *hCorrRecPhi_clone = (TH1D*)hCorrRecPhi->Clone("hCorrRecPhi_clone");
  hCorrRecPhi_clone->Divide(hSimPhi_clone_v1);
  hCorrRecPhi_clone->GetXaxis()->SetTitle("#phi");
  hCorrRecPhi_clone->GetYaxis()->SetTitleOffset(1.5);
  gStyle->SetPadLeftMargin(0.18);
  hCorrRecPhi_clone->GetYaxis()->SetTitle("Weighted matched sim / Sim");
  hCorrRecPhi_clone->Draw();


  TCanvas *c3 = new TCanvas("c3","c3");
  c3->cd();

  hSimEta->GetXaxis()->SetTitle("#eta");
  hSimEta->GetYaxis()->SetTitleOffset(1.5);
  gStyle->SetPadLeftMargin(0.18);
  hSimEta->GetYaxis()->SetTitle("Entries");
  hSimEta->Draw();

  hCorrRecEta->SetLineColor(2);
  hCorrRecEta->Draw("same");

  hRecEta->SetLineColor(6);
  hRecEta->Draw("same");

  TLegend *leg3 = new TLegend(0.20,0.65,0.92,0.90,NULL,"brNDC");
  leg3->AddEntry(hSimEta,"Sim","l");
  leg3->AddEntry(hRecEta,"Matched sim","l");
  leg3->AddEntry(hCorrRecEta,"Acc.+cent. weighted matched sim","l");
  leg3->SetFillStyle(0);
  leg3->SetFillColor(0);
  leg3->SetBorderSize(0);
  leg3->Draw();


  TCanvas *c4 = new TCanvas("c4","c4");
  c4->cd();

  TH1D *hSimEta_clone_v1 = (TH1D*)hSimEta->Clone("hSimEta_clone_v1");
  TH1D *hCorrRecEta_clone = (TH1D*)hCorrRecEta->Clone("hCorrRecEta_clone");
  hCorrRecEta_clone->Divide(hSimEta_clone_v1);
  hCorrRecEta_clone->GetXaxis()->SetTitle("#eta");
  hCorrRecEta_clone->GetYaxis()->SetTitleOffset(1.5);
  gStyle->SetPadLeftMargin(0.18);
  hCorrRecEta_clone->GetYaxis()->SetTitle("Weighted matched sim / Sim");
  hCorrRecEta_clone->Draw();


  TCanvas *c5 = new TCanvas("c5","c5");
  c5->cd();

  hCorrRecEta_Cent_0_3->Divide(hSimEta_Cent_0_3);
  hCorrRecEta_Cent_0_3->Draw();  


  TCanvas *c6 = new TCanvas("c6","c6");
  c6->cd();

  hCorrRecEta_pT_06_14->Divide(hSimEta_pT_06_14);
  hCorrRecEta_pT_06_14->Draw();  


  TCanvas *c7 = new TCanvas("c7","c7");
  c7->cd();

  hCorrRecEta_pT_18_3->Divide(hSimEta_pT_18_3);
  hCorrRecEta_pT_18_3->Draw();  


  TCanvas *c8 = new TCanvas("c8","c8");
  c8->cd();

  hCorrRecEta_pT_3_8->Divide(hSimEta_pT_3_8);
  hCorrRecEta_pT_3_8->Draw();  


  TCanvas *c9 = new TCanvas("c9","c9");
  c9->cd();

  hCorrRecEta_pT_16_18->Divide(hSimEta_pT_16_18);
  hCorrRecEta_pT_16_18->Draw();  

}


