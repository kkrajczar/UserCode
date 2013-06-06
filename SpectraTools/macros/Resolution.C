#include "../hiForest.h"
#include "../utilities.h"
#include <TROOT.h>
#include <TStyle.h>
#include <TFile.h>
#include <TH1D.h>
#include <TNtuple.h>
#include <iostream>
#include <TLegend.h>
#include <TLatex.h>
#include "TrackCorrector.C"

TH1D* divideHistosDiffBins(TH1D* h_Num, TH1D* h_Den);
void normalizeByBinWidth(TH1D *histo);
void fillHistograms(HiForest *c, TH2D *hRes1, TH2D *hRes2, TH2D *hRes3, TH2D *hRes4, TH2D *hRes5, TH2D *hRes6, TH2D *hRes7, TH2D *hRes8);
//------------------------

void Resolution()
{
   gROOT->Reset();
   gROOT->ProcessLine(".x rootlogonChristof.C");
   gROOT->ForceStyle();
   gStyle->SetPalette(1);
   gStyle->SetTitleYOffset(1.30);
   gStyle->SetPadRightMargin(0.16);

   bool doSave = false;
   TFile * f_output = new TFile("Resolution.root","recreate");

   TrackCorrector corr("trackCorrections_HIN12017v1_HijingCombined.root");
   corr.load("trkCorr_HIN12017");

   // Define the input file and HiForest
   char *infName_370 = "root://eoscms//eos/cms/store/caf/user/dgulhan/pPb/HP04/prod16/Hijing_Pythia_pt370/HiForest_v77_merged01/pt370_HP04_prod16_v77_merged_forest_0.root";
   char *infName_80 = "root://eoscms//eos/cms/store/caf/user/dgulhan/pPb/HP04/prod16/Hijing_Pythia_pt80/HiForest_v77_merged01/pt80_HP04_prod16_v77_merged_forest_0.root";
//   char *infName_80 = "root://eoscms//eos/cms/store/caf/user/dgulhan/pPb/HP04/prod16/Hijing_Pythia_pt15/HiForest_v77_merged01/pt15_HP04_prod16_v77_merged_forest_0.root";
   HiForest *c_370 = new HiForest(infName_370,"",cPPb);
   HiForest *c_80 = new HiForest(infName_80,"",cPPb);
//   c_MC->doTrackCorrections=1;
//   c_MC->InitTree();

   std::vector<Double_t> ptBins;
   const Double_t small = 1e-3;
   Double_t pt;
   for(pt =   0.  ; pt <   48.-small; pt +=  2./20.) ptBins.push_back(pt);
   for(pt =   48.; pt <   60.-small; pt +=  4./20. ) ptBins.push_back(pt); 
   for(pt =   60.; pt <   76.-small; pt +=  8./20. ) ptBins.push_back(pt); 
   for(pt =   76.; pt <   140.-small; pt +=  16./20. ) ptBins.push_back(pt); 
   for(pt =   140.; pt <   300.-small; pt +=  32./10. ) ptBins.push_back(pt); 
   ptBins.push_back(300.0);

   std::vector<Double_t> ptBins_larger;
   Double_t pt_larger;
   for(pt_larger =   0.  ; pt_larger <   48.-small; pt_larger +=  2./10.) ptBins_larger.push_back(pt_larger);
   for(pt_larger =   48.; pt_larger <   60.-small; pt_larger +=  4./10. ) ptBins_larger.push_back(pt_larger); 
   for(pt_larger =   60.; pt_larger <   76.-small; pt_larger +=  8./10. ) ptBins_larger.push_back(pt_larger); 
   for(pt_larger =   76.; pt_larger <   140.-small; pt_larger +=  16./10. ) ptBins_larger.push_back(pt_larger); 
   for(pt_larger =   140.; pt_larger <   300.-small; pt_larger +=  32./10. ) ptBins_larger.push_back(pt_larger); 
   ptBins_larger.push_back(300.0);

   std::vector<Double_t> ptBins_smaller;
   Double_t pt_smaller;
   for(pt_smaller =   0.  ; pt_smaller <   48.-small; pt_smaller +=  2./40.) ptBins_smaller.push_back(pt_smaller);
   for(pt_smaller =   48.; pt_smaller <   60.-small; pt_smaller +=  4./40. ) ptBins_smaller.push_back(pt_smaller); 
   for(pt_smaller =   60.; pt_smaller <   76.-small; pt_smaller +=  8./20. ) ptBins_smaller.push_back(pt_smaller); 
   for(pt_smaller =   76.; pt_smaller <   140.-small; pt_smaller +=  16./20. ) ptBins_smaller.push_back(pt_smaller); 
   for(pt_smaller =   140.; pt_smaller <   300.-small; pt_smaller +=  32./10. ) ptBins_smaller.push_back(pt_smaller); 
   ptBins_smaller.push_back(300.0);

   std::vector<Double_t> ptBins_evensmaller;
   Double_t pt_evensmaller;
   for(pt_evensmaller =   0.  ; pt_evensmaller <   28.-small; pt_evensmaller +=  2./80.) ptBins_evensmaller.push_back(pt_evensmaller);
   for(pt_evensmaller =   28.; pt_evensmaller <   60.-small; pt_evensmaller +=  4./40. ) ptBins_evensmaller.push_back(pt_evensmaller); 
   for(pt_evensmaller =   60.; pt_evensmaller <   76.-small; pt_evensmaller +=  8./20. ) ptBins_evensmaller.push_back(pt_evensmaller); 
   for(pt_evensmaller =   76.; pt_evensmaller <   140.-small; pt_evensmaller +=  16./20. ) ptBins_evensmaller.push_back(pt_evensmaller); 
   for(pt_evensmaller =   140.; pt_evensmaller <   300.-small; pt_evensmaller +=  32./10. ) ptBins_evensmaller.push_back(pt_evensmaller); 
   ptBins_evensmaller.push_back(300.0);

   std::vector<Double_t> ptBins_evensmaller2;
   Double_t pt_evensmaller2;
   for(pt_evensmaller2 =   0.  ; pt_evensmaller2 <   18.-small; pt_evensmaller2 +=  2./160.) ptBins_evensmaller2.push_back(pt_evensmaller2);
   for(pt_evensmaller2 =   18.; pt_evensmaller2 <   60.-small; pt_evensmaller2 +=  4./20. ) ptBins_evensmaller2.push_back(pt_evensmaller2); 
   for(pt_evensmaller2 =   60.; pt_evensmaller2 <   76.-small; pt_evensmaller2 +=  8./20. ) ptBins_evensmaller2.push_back(pt_evensmaller2); 
   for(pt_evensmaller2 =   76.; pt_evensmaller2 <   140.-small; pt_evensmaller2 +=  16./20. ) ptBins_evensmaller2.push_back(pt_evensmaller2); 
   for(pt_evensmaller2 =   140.; pt_evensmaller2 <   300.-small; pt_evensmaller2 +=  32./10. ) ptBins_evensmaller2.push_back(pt_evensmaller2); 
   ptBins_evensmaller2.push_back(300.0);

   std::vector<Double_t> ptBins_evensmaller3;
   Double_t pt_evensmaller3;
   for(pt_evensmaller3 =   0.  ; pt_evensmaller3 <   8.-small; pt_evensmaller3 +=  2./320.) ptBins_evensmaller3.push_back(pt_evensmaller3);
   for(pt_evensmaller3 =   8.; pt_evensmaller3 <   60.-small; pt_evensmaller3 +=  4./40. ) ptBins_evensmaller3.push_back(pt_evensmaller3); 
   for(pt_evensmaller3 =   60.; pt_evensmaller3 <   76.-small; pt_evensmaller3 +=  8./20. ) ptBins_evensmaller3.push_back(pt_evensmaller3); 
   for(pt_evensmaller3 =   76.; pt_evensmaller3 <   140.-small; pt_evensmaller3 +=  16./20. ) ptBins_evensmaller3.push_back(pt_evensmaller3); 
   for(pt_evensmaller3 =   140.; pt_evensmaller3 <   300.-small; pt_evensmaller3 +=  32./10. ) ptBins_evensmaller3.push_back(pt_evensmaller3); 
   ptBins_evensmaller3.push_back(300.0);

   std::vector<Double_t> ptBins_evensmaller4;
   Double_t pt_evensmaller4;
   for(pt_evensmaller4 =   0.  ; pt_evensmaller4 <   8.-small; pt_evensmaller4 +=  2./640.) ptBins_evensmaller4.push_back(pt_evensmaller4);
   for(pt_evensmaller4 =   8.; pt_evensmaller4 <   60.-small; pt_evensmaller4 +=  4./40. ) ptBins_evensmaller4.push_back(pt_evensmaller4); 
   for(pt_evensmaller4 =   60.; pt_evensmaller4 <   76.-small; pt_evensmaller4 +=  8./20. ) ptBins_evensmaller4.push_back(pt_evensmaller4); 
   for(pt_evensmaller4 =   76.; pt_evensmaller4 <   140.-small; pt_evensmaller4 +=  16./20. ) ptBins_evensmaller4.push_back(pt_evensmaller4); 
   for(pt_evensmaller4 =   140.; pt_evensmaller4 <   300.-small; pt_evensmaller4 +=  32./10. ) ptBins_evensmaller4.push_back(pt_evensmaller4); 
   ptBins_evensmaller4.push_back(300.0);

   Int_t NumOfPtBins_part = 34;
   double ptBins_part[] = {0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0, 1.1, 1.2, 1.4, 1.6, 1.8, 2.0, 2.2, 2.4, 3.2, 4.0, 4.8, 5.6, 6.4, 7.2, 9.6, 12.0, 14.4, 19.2, 24.0, 28.8, 35.2, 41.6, 48.0, 60.8, 73.6, 86.4, 103.6};


   Int_t NumOfPtBins_005 = 26;
   double ptBins_005[] = {0.6, 0.8, 1.0, 1.5, 2.1, 3., 3.5, 4.5, 5.2, 6., 7., 8., 10., 12.5, 15., 17.5, 20., 25., 31., 37., 43., 50., 60., 70., 80., 100., 120.};

   TH2D * hSimPtRecPt_80 = new TH2D("hSimPtRecPt_80","hSimPtRecPt_80",ptBins.size()-1,&ptBins[0],ptBins.size()-1,&ptBins[0]);
   TH2D * hSimPtRecPt_80_005 = new TH2D("hSimPtRecPt_80_005","hSimPtRecPt_80_005",NumOfPtBins_005-1,&ptBins_005[0],NumOfPtBins_005-1,&ptBins_005[0]);
   TH2D * hSimPtRecPt_80_larger = new TH2D("hSimPtRecPt_80_larger","hSimPtRecPt_80_larger",ptBins_larger.size()-1,&ptBins_larger[0],ptBins_larger.size()-1,&ptBins_larger[0]);
   TH2D * hSimPtRecPt_80_smaller = new TH2D("hSimPtRecPt_80_smaller","hSimPtRecPt_80_smaller",ptBins_smaller.size()-1,&ptBins_smaller[0],ptBins_smaller.size()-1,&ptBins_smaller[0]);
   TH2D * hSimPtRecPt_80_evensmaller = new TH2D("hSimPtRecPt_80_evensmaller","hSimPtRecPt_80_evensmaller",ptBins_evensmaller.size()-1,&ptBins_evensmaller[0],ptBins_evensmaller.size()-1,&ptBins_evensmaller[0]);
   TH2D * hSimPtRecPt_80_evensmaller2 = new TH2D("hSimPtRecPt_80_evensmaller2","hSimPtRecPt_80_evensmaller2",ptBins_evensmaller2.size()-1,&ptBins_evensmaller2[0],ptBins_evensmaller2.size()-1,&ptBins_evensmaller2[0]);
   TH2D * hSimPtRecPt_80_evensmaller3 = new TH2D("hSimPtRecPt_80_evensmaller3","hSimPtRecPt_80_evensmaller3",ptBins_evensmaller3.size()-1,&ptBins_evensmaller3[0],ptBins_evensmaller3.size()-1,&ptBins_evensmaller3[0]);
   TH2D * hSimPtRecPt_80_evensmaller4 = new TH2D("hSimPtRecPt_80_evensmaller4","hSimPtRecPt_80_evensmaller4",ptBins_evensmaller4.size()-1,&ptBins_evensmaller4[0],ptBins_evensmaller4.size()-1,&ptBins_evensmaller4[0]);
   TH2D * hSimPtRecPt_370 = new TH2D("hSimPtRecPt_370","hSimPtRecPt_370",ptBins.size()-1,&ptBins[0],ptBins.size()-1,&ptBins[0]);
   TH2D * hSimPtRecPt_370_005 = new TH2D("hSimPtRecPt_370_005","hSimPtRecPt_370_005",NumOfPtBins_005-1,&ptBins_005[0],NumOfPtBins_005-1,&ptBins_005[0]);
   TH2D * hSimPtRecPt_370_larger = new TH2D("hSimPtRecPt_370_larger","hSimPtRecPt_370_larger",ptBins_larger.size()-1,&ptBins_larger[0],ptBins_larger.size()-1,&ptBins_larger[0]);
   TH2D * hSimPtRecPt_370_smaller = new TH2D("hSimPtRecPt_370_smaller","hSimPtRecPt_370_smaller",ptBins_smaller.size()-1,&ptBins_smaller[0],ptBins_smaller.size()-1,&ptBins_smaller[0]);
   TH2D * hSimPtRecPt_370_evensmaller = new TH2D("hSimPtRecPt_370_evensmaller","hSimPtRecPt_370_evensmaller",ptBins_evensmaller.size()-1,&ptBins_evensmaller[0],ptBins_evensmaller.size()-1,&ptBins_evensmaller[0]);
   TH2D * hSimPtRecPt_370_evensmaller2 = new TH2D("hSimPtRecPt_370_evensmaller2","hSimPtRecPt_370_evensmaller2",ptBins_evensmaller2.size()-1,&ptBins_evensmaller2[0],ptBins_evensmaller2.size()-1,&ptBins_evensmaller2[0]);
   TH2D * hSimPtRecPt_370_evensmaller3 = new TH2D("hSimPtRecPt_370_evensmaller3","hSimPtRecPt_370_evensmaller3",ptBins_evensmaller3.size()-1,&ptBins_evensmaller3[0],ptBins_evensmaller3.size()-1,&ptBins_evensmaller3[0]);
   TH2D * hSimPtRecPt_370_evensmaller4 = new TH2D("hSimPtRecPt_370_evensmaller4","hSimPtRecPt_370_evensmaller4",ptBins_evensmaller4.size()-1,&ptBins_evensmaller4[0],ptBins_evensmaller4.size()-1,&ptBins_evensmaller4[0]);

   hSimPtRecPt_80->Sumw2();
   hSimPtRecPt_80_005->Sumw2();
   hSimPtRecPt_80_larger->Sumw2();
   hSimPtRecPt_80_smaller->Sumw2();
   hSimPtRecPt_80_evensmaller->Sumw2();
   hSimPtRecPt_80_evensmaller2->Sumw2();
   hSimPtRecPt_80_evensmaller3->Sumw2();
   hSimPtRecPt_80_evensmaller4->Sumw2();
   hSimPtRecPt_370->Sumw2();
   hSimPtRecPt_370_005->Sumw2();
   hSimPtRecPt_370_larger->Sumw2();
   hSimPtRecPt_370_smaller->Sumw2();
   hSimPtRecPt_370_evensmaller->Sumw2();
   hSimPtRecPt_370_evensmaller2->Sumw2();
   hSimPtRecPt_370_evensmaller3->Sumw2();
   hSimPtRecPt_370_evensmaller4->Sumw2();

   fillHistograms(c_80, hSimPtRecPt_80, hSimPtRecPt_80_larger, hSimPtRecPt_80_smaller, hSimPtRecPt_80_evensmaller, hSimPtRecPt_80_evensmaller2, hSimPtRecPt_80_evensmaller3,hSimPtRecPt_80_evensmaller4, hSimPtRecPt_80_005);
   fillHistograms(c_370, hSimPtRecPt_370, hSimPtRecPt_370_larger, hSimPtRecPt_370_smaller, hSimPtRecPt_370_evensmaller, hSimPtRecPt_370_evensmaller2, hSimPtRecPt_370_evensmaller3, hSimPtRecPt_370_evensmaller4, hSimPtRecPt_370_005);

   f_output->cd();
   hSimPtRecPt_80->Write();
   hSimPtRecPt_80_005->Write();
   hSimPtRecPt_80_larger->Write();
   hSimPtRecPt_80_smaller->Write();
   hSimPtRecPt_80_evensmaller->Write();
   hSimPtRecPt_80_evensmaller2->Write();
   hSimPtRecPt_80_evensmaller3->Write();
   hSimPtRecPt_80_evensmaller4->Write();
   hSimPtRecPt_370->Write();
   hSimPtRecPt_370_005->Write();
   hSimPtRecPt_370_larger->Write();
   hSimPtRecPt_370_smaller->Write();
   hSimPtRecPt_370_evensmaller->Write();
   hSimPtRecPt_370_evensmaller2->Write();
   hSimPtRecPt_370_evensmaller3->Write();
   hSimPtRecPt_370_evensmaller4->Write();
   f_output->Close();
}

TH1D* divideHistosDiffBins(TH1D* h_Num, TH1D* h_Den) {
   TH1D *h_ratio = (TH1D*)h_Num->Clone("h_ratio");
   h_ratio->Reset();
   for(int i = 1; i <= h_Num->GetNbinsX(); i++) {
      float content = h_Num->GetBinContent(i);
      float error = h_Num->GetBinError(i);
      float center = h_Num->GetBinCenter(i);
      int which_bin_in_h_Den = h_Den->FindBin(center);
      float content_h_Den = h_Den->GetBinContent(which_bin_in_h_Den);

      if(content_h_Den==0)
         continue;

      h_ratio->SetBinContent(i,content/content_h_Den);      
      h_ratio->SetBinError(i,error/content_h_Den);      
   }
   return h_ratio;
}


void normalizeByBinWidth(TH1D *histo) {
   for(int i = 1; i <= histo->GetNbinsX(); i++) {
      float content = histo->GetBinContent(i);
      float error = histo->GetBinError(i);
      histo->SetBinContent(i,content/histo->GetBinWidth(i));
      histo->SetBinError(i,error/histo->GetBinWidth(i));
   }
}

void fillHistograms(HiForest * c_MC, TH2D* hRes1, TH2D* hRes2, TH2D* hRes3, TH2D* hRes4, TH2D* hRes5, TH2D* hRes6, TH2D* hRes7, TH2D* hRes8) {

   for (int i=0;i<c_MC->GetEntries();i++) {
//   for (int i=0;i<10000;i++) {

      c_MC->GetEntry(i);

//      data.leadingJetPt = -1;
//      data.leadingJetIt = -1;
//      data.leadingJetTrackMax = -1;

      if (i % 2000 == 0) cout <<i<<" / "<<c_MC->GetEntries()<<endl;

      //event selection
      bool event_accepted = true;
      if(!(c_MC->skim.phfPosFilter1 && c_MC->skim.phfNegFilter1
          && c_MC->skim.pBeamScrapingFilter
          && c_MC->skim.pprimaryvertexFilter
//          && c_MC->skim.pVertexFilterCutGplus
          && TMath::Abs(c_MC->evt.vz)<15.
          )
        ) event_accepted = false;

      if(event_accepted == false)
         continue;

      //trackingParticles
      for (int j=0;j<c_MC->track.nParticle;j++) {
         if(!(fabs(c_MC->track.pEta[j])<1.0
           ))
           continue;

         if(!(c_MC->track.mtrkPt[j]>0.1
             && (c_MC->track.mtrkQual[j]==1)
             && (fabs(c_MC->track.mtrkDz1[j]/c_MC->track.mtrkDzError1[j])<3)
             && (fabs(c_MC->track.mtrkDxy1[j]/c_MC->track.mtrkDxyError1[j])<3)
             && (c_MC->track.mtrkPtError[j]/c_MC->track.mtrkPt[j]<0.1)
           ))
           continue;

         hRes1->Fill(c_MC->track.pPt[j],c_MC->track.mtrkPt[j]);
         hRes2->Fill(c_MC->track.pPt[j],c_MC->track.mtrkPt[j]);
         hRes3->Fill(c_MC->track.pPt[j],c_MC->track.mtrkPt[j]);
         hRes4->Fill(c_MC->track.pPt[j],c_MC->track.mtrkPt[j]);
         hRes5->Fill(c_MC->track.pPt[j],c_MC->track.mtrkPt[j]);
         hRes6->Fill(c_MC->track.pPt[j],c_MC->track.mtrkPt[j]);
         hRes7->Fill(c_MC->track.pPt[j],c_MC->track.mtrkPt[j]);
         hRes8->Fill(c_MC->track.pPt[j],c_MC->track.mtrkPt[j]);
      }
   }//event
/*
   TCanvas *c1 = new TCanvas("c1","c1");
   c1->cd();
   c1->SetLogz();
   hRes1->GetXaxis()->CenterTitle();
   hRes1->GetYaxis()->CenterTitle();
   hRes1->GetXaxis()->SetTitle("p_{T}^{Sim} [GeV/c]");
   hRes1->GetYaxis()->SetTitle("p_{T}^{Rec} [GeV/c]");
//   hRes1->SetNdivisions(505);
   hRes1->SetMarkerColor(1);
   hRes1->SetLineColor(1);
   hRes1->SetMarkerStyle(20);
   hRes1->Draw("colz");
*/
/*
   TLegend *leg1 = new TLegend(0.50,0.75,0.82,0.89,NULL,"brNDC");
   leg1->AddEntry(hPartPt_trkCorr_trigCorr,"Fully corrected (trig.+trk. corr.) reco","pl");
   leg1->AddEntry(hPartPt_trigCorr,"Trigger-corrected (no trk. corr.) reco","pl");
   leg1->AddEntry(hPartPt_truth,"Sim particles","pl");
   leg1->SetFillStyle(0);
   leg1->SetFillColor(0);
   leg1->SetBorderSize(0);
   leg1->Draw();
   if(doSave) {
      c1->SaveAs("Figs/Resolution_c1.gif");
      c1->SaveAs("Figs/Resolution_c1.eps");
      c1->SaveAs("Figs/Resolution_c1.C");
   }


   TCanvas *c2 = new TCanvas("c2","c2");
   TH1D *hPartPt_truth_copy1 = (TH1D*)hPartPt_truth->Clone("hPartPt_truth_copy1");
   TH1D *hPartPt_truth_copy2 = (TH1D*)hPartPt_truth->Clone("hPartPt_truth_copy2");
   hPartPt_truth_copy1->Divide(hPartPt_trkCorr_trigCorr);
   hPartPt_truth_copy2->Divide(hPartPt_trigCorr);

   hPartPt_truth_copy1->GetYaxis()->SetTitle("Truth / Reco");
   hPartPt_truth_copy1->SetMarkerColor(1);
   hPartPt_truth_copy1->SetLineColor(1);
   hPartPt_truth_copy1->SetMarkerStyle(20);
   hPartPt_truth_copy1->Draw();

   hPartPt_truth_copy2->SetMarkerColor(4);
   hPartPt_truth_copy2->SetLineColor(4);
   hPartPt_truth_copy2->SetMarkerStyle(20);
   hPartPt_truth_copy2->Draw("same");

//   TLegend *leg2 = new TLegend(0.50,0.75,0.82,0.89,NULL,"brNDC");
//   leg2->AddEntry(hJetPt_Jet40_copy1,"Jet40","pl");
//   leg2->SetFillStyle(0);
//   leg2->SetFillColor(0);
//   leg2->SetBorderSize(0);
//   leg2->Draw();
   if(doSave) {
      c2->SaveAs("Figs/c2.gif");
      c2->SaveAs("Figs/c2.eps");
      c2->SaveAs("Figs/c2.C");
   }
*/
}
