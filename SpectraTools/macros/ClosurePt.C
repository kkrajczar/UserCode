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
//------------------------

void ClosurePt()
{
   gROOT->Reset();
   gROOT->ProcessLine(".x rootlogonChristof.C");
   gROOT->ForceStyle();
   gStyle->SetPalette(1);
   gStyle->SetTitleYOffset(1.30);
//   gStyle->SetPadRightMargin(0.16);

   bool doSave = false;
   TFile * f_output = new TFile("ClosurePt.root","recreate");

   TrackCorrector corr("trackCorrections_HIN12017v1_HijingCombined.root");
//   TrackCorrector corr("trackCorrections_HIN12017v2b_HijingPtHat80.root");
   corr.load("trkCorr_HIN12017");

   // Define the input file and HiForest
//   char *infName_20 = "root://eoscms//eos/cms/store/caf/user/dgulhan/pPb/HP04/prod16/Hijing_Pythia_pt370/HiForest_v77_merged01/pt370_HP04_prod16_v77_merged_forest_0.root";
   char *infName_20 = "root://eoscms//eos/cms/store/caf/user/dgulhan/pPb/HP04/prod16/Hijing_Pythia_pt280/HiForest_v77_merged01/pt280_HP04_prod16_v77_merged_forest_0.root";
//   char *infName_20 = "root://eoscms//eos/cms/store/caf/user/dgulhan/pPb/HP04/prod16/Hijing_Pythia_pt50/HiForest_v77_merged01/pt50_HP04_prod16_v77_merged_forest_0.root";
//   char *infName_20 = "root://eoscms//eos/cms/store/caf/user/dgulhan/pPb/HP04/prod16/Hijing_Pythia_pt80/HiForest_v77_merged01/pt80_HP04_prod16_v77_merged_forest_0.root";
//   char *infName_20 = "root://eoscms//eos/cms/store/caf/user/dgulhan/pPb/HP04/prod16/Hijing_Pythia_pt15/HiForest_v77_merged01/pt15_HP04_prod16_v77_merged_forest_0.root";
   HiForest *c_MC = new HiForest(infName_20,"",cPPb);
//   c_MC->doTrackCorrections=1;
//   c_MC->InitTree();

   std::vector<Double_t> ptBins;
   const Double_t small = 1e-3;
   Double_t pt;
   for(pt =   0.  ; pt <   48.-small; pt +=  2./2.) ptBins.push_back(pt);
   for(pt =   48.; pt <   60.-small; pt +=  4./2. ) ptBins.push_back(pt); 
   for(pt =   60.; pt <   76.-small; pt +=  8./2. ) ptBins.push_back(pt); 
   for(pt =   76.; pt <   140.-small; pt +=  16./2. ) ptBins.push_back(pt); 
   for(pt =   140.; pt <   364.-small; pt +=  32./2. ) ptBins.push_back(pt); 
   ptBins.push_back(364.0);

   std::vector<Double_t> ptBins_larger;
   Double_t pt_larger;
   for(pt_larger =   0.  ; pt_larger <   48.-small; pt_larger +=  2.) ptBins_larger.push_back(pt_larger);
   for(pt_larger =   48.; pt_larger <   60.-small; pt_larger +=  4.) ptBins_larger.push_back(pt_larger);
   for(pt_larger =   60.; pt_larger <   76.-small; pt_larger +=  8.) ptBins_larger.push_back(pt_larger);
   for(pt_larger =   76.; pt_larger <   140.-small; pt_larger +=  16.) ptBins_larger.push_back(pt_larger);
   for(pt_larger =   140.; pt_larger <   364.-small; pt_larger +=  32.) ptBins_larger.push_back(pt_larger);
   ptBins_larger.push_back(364.0);

//   Int_t NumOfPtBins_part = 34;
   Int_t NumOfPtBins_part = 43;
//   double ptBins_part[] = {0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0, 1.1, 1.2, 1.4, 1.6, 1.8, 2.0, 2.2, 2.4, 3.2, 4.0, 4.8, 5.6, 6.4, 7.2, 9.6, 12.0, 14.4, 19.2, 24.0, 28.8, 35.2, 41.6, 48.0, 60.8, 73.6, 86.4, 103.6};
   double ptBins_part[] = {0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0, 1.1, 1.2, 1.4, 1.6, 1.8, 2.0, 2.2, 2.4, 3.2, 4.0, 4.8, 5.6, 6.4, 7.2, 9.6, 12.0, 14.4, 19.2, 24.0, 28.8, 35.2, 41.6, 48.0, 60.8, 73.6, 86.4, 103.6, 138., 155.2, 172.4, 189.6, 206.8, 224., 258.4, 292.8, 327.3};

   TTree * t = new TTree("t","whatever");
   JetData data(t,1);

   TH1D * hPartPt_trkCorr_trigCorr = new TH1D("hPartPt_trkCorr_trigCorr","hPartPt_trkCorr_trigCorr",NumOfPtBins_part-1,&ptBins_part[0]);
   TH1D * hPartPt_trigCorr = new TH1D("hPartPt_trigCorr","hPartPt_trigCorr",NumOfPtBins_part-1,&ptBins_part[0]);
   TH1D * hPartPt_truth = new TH1D("hPartPt_truth","hPartPt_truth",NumOfPtBins_part-1,&ptBins_part[0]);
   TH1D * hNumEv_Meas = new TH1D("hNumEv_Meas","hNumEv_Meas",1,0.,1.);
   TH1D * hNumEv_Truth = new TH1D("hNumEv_Truth","hNumEv_Truth",1,0.,1.);

   TH1D * hPartPt_trkCorr_trigCorr_JetsMod = new TH1D("hPartPt_trkCorr_trigCorr_JetsMod","hPartPt_trkCorr_trigCorr_JetsMod",NumOfPtBins_part-1,&ptBins_part[0]);
   TH1D * hPartPt_truth_JetsMod = new TH1D("hPartPt_truth_JetsMod","hPartPt_truth_JetsMod",NumOfPtBins_part-1,&ptBins_part[0]);

   TH1D * hJetForCorr_orig = new TH1D("hJetForCorr_orig","hJetForCorr_orig",195,10.,400.);
   TH1D * hJetForCorr_weighted = new TH1D("hJetForCorr_weighted","hJetForCorr_weighted",195,10.,400.);

   hPartPt_trkCorr_trigCorr->Sumw2();
   hPartPt_trigCorr->Sumw2();
   hPartPt_truth->Sumw2();
   hPartPt_trkCorr_trigCorr_JetsMod->Sumw2();
   hPartPt_truth_JetsMod->Sumw2();

   hJetForCorr_orig->Sumw2();
   hJetForCorr_weighted->Sumw2();

   float NumEv_Meas = 0;
   float NumEv_Truth = 0;

   for (int i=0;i<c_MC->GetEntries();i++) {
//   for (int i=0;i<40000;i++) {

      c_MC->GetEntry(i);

      if(!(TMath::Abs(c_MC->evt.vz)<15.))
         continue;

      //Jets
      data.leadingJetPt = -1;
      data.leadingJetIt = -1;
      data.leadingJetTrackMax = -1;
      for (int j=0;j<c_MC->akPu3PF.nref;j++) {
         if (fabs(c_MC->akPu3PF.jteta[j])>2.5) continue;
//         if (fabs(c_MC->akPu3PF.jtpt[j])<30) continue;
//         if (c_MC->akPu3PF.trackMax[j]<4) continue; //Do we need this?
         if (c_MC->akPu3PF.rawpt[j]<15) continue;
         if (c_MC->akPu3PF.jtpt[j]>data.leadingJetPt) {
            data.leadingJetPt = c_MC->akPu3PF.jtpt[j];
            data.leadingJetEta = c_MC->akPu3PF.jteta[j];
            data.leadingJetPhi = c_MC->akPu3PF.jtphi[j];
            data.leadingJetTrackMax = c_MC->akPu3PF.trackMax[j];
            data.leadingJetIt = j;
         }
      }
      double jetmod = exp(data.leadingJetPt/200.);

      NumEv_Truth++;

      //trackingParticles
      for (int j=0;j<c_MC->track.nParticle;j++) {
         if(!((c_MC->track.pPt[j]>0.2) 
             && (fabs(c_MC->track.pEta[j])<1.0)
           ))
           continue;

         hPartPt_truth->Fill(c_MC->track.pPt[j]);
         hPartPt_truth_JetsMod->Fill(c_MC->track.pPt[j],jetmod);
      }

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

      hJetForCorr_orig->Fill(data.leadingJetPt);
      hJetForCorr_weighted->Fill(data.leadingJetPt,jetmod);

      //Tracks for event weights; eta-pt cut removed
      int trackMult = 0;
      for(int j=0;j<c_MC->track.nTrk;j++) {
         if(!((c_MC->track.highPurity[j])
             && (fabs(c_MC->track.trkDz1[j]/c_MC->track.trkDzError1[j])<3)
             && (fabs(c_MC->track.trkDxy1[j]/c_MC->track.trkDxyError1[j])<3)
             && (c_MC->track.trkPtError[j]/c_MC->track.trkPt[j]<0.1)
            ))
            continue;
         trackMult++;
      }
      // Don't analyze 0 multiplicity events; correction added later
      if(trackMult==0)
        { std::cerr<<" Accepted, but 0 multiplicity!!" << std::endl; continue; }
      double evtWeight = 1.;
      evtWeight = corr.getEventWeight(trackMult);
      //do not add the zero multiplicity correction, this in not MB MC

      NumEv_Meas += evtWeight;

      //Tracks
      for(int j=0;j<c_MC->track.nTrk;j++) {
         if(!((c_MC->track.trkPt[j]>0.2) 
             && (fabs(c_MC->track.trkEta[j])<1.0)
             && (c_MC->track.highPurity[j])
             && (fabs(c_MC->track.trkDz1[j]/c_MC->track.trkDzError1[j])<3)
             && (fabs(c_MC->track.trkDxy1[j]/c_MC->track.trkDxyError1[j])<3)
             && (c_MC->track.trkPtError[j]/c_MC->track.trkPt[j]<0.1)
           ))
            continue;            

         if(data.leadingJetPt==-1) //for corrections
            data.leadingJetPt=10.;
         double trkWeight = 1.;
         trkWeight = corr.getWeight(c_MC->track.trkPt[j],c_MC->track.trkEta[j],data.leadingJetPt);

         hPartPt_trkCorr_trigCorr->Fill(c_MC->track.trkPt[j],trkWeight*evtWeight);
         hPartPt_trigCorr->Fill(c_MC->track.trkPt[j],evtWeight);

         hPartPt_trkCorr_trigCorr_JetsMod->Fill(c_MC->track.trkPt[j],trkWeight*evtWeight*jetmod);
      } //Tracks end
   }//event

   hNumEv_Meas->SetBinContent(1,NumEv_Meas);
   hNumEv_Truth->SetBinContent(1,NumEv_Truth);
   normalizeByBinWidth(hPartPt_trkCorr_trigCorr);
   normalizeByBinWidth(hPartPt_trkCorr_trigCorr_JetsMod);
   normalizeByBinWidth(hPartPt_trigCorr);
   normalizeByBinWidth(hPartPt_truth);
   normalizeByBinWidth(hPartPt_truth_JetsMod);
   normalizeByBinWidth(hJetForCorr_orig);
   normalizeByBinWidth(hJetForCorr_weighted);


   TCanvas *c0 = new TCanvas("c0","c0");
   c0->cd();
   c0->SetLogy();
   hJetForCorr_weighted->GetXaxis()->SetTitle("Leading jet p_{T}");
   hJetForCorr_weighted->GetYaxis()->SetTitle("Counts / GeV/c");
   hJetForCorr_weighted->SetMarkerStyle(20);
   hJetForCorr_weighted->Draw();

   hJetForCorr_orig->SetMarkerStyle(24);
   hJetForCorr_orig->SetMarkerColor(6);
   hJetForCorr_orig->SetLineColor(6);
   hJetForCorr_orig->Draw("same");

   TLegend *leg0 = new TLegend(0.50,0.15,0.82,0.35,NULL,"brNDC");
   leg0->AddEntry(hJetForCorr_orig,"Original","pl");
   leg0->AddEntry(hJetForCorr_weighted,"Weighted (exp(pt/200))","pl");
   leg0->SetFillStyle(0);
   leg0->SetFillColor(0);
   leg0->SetBorderSize(0);
   leg0->Draw();
   if(doSave) {
      c0->SaveAs("Figs/ClosurePt_c0.gif");
      c0->SaveAs("Figs/ClosurePt_c0.eps");
      c0->SaveAs("Figs/ClosurePt_c0.C");
   }
  

   TCanvas *c1 = new TCanvas("c1","c1");
   c1->cd();
   c1->SetLogy();

   hPartPt_trkCorr_trigCorr->GetXaxis()->CenterTitle();
   hPartPt_trkCorr_trigCorr->GetYaxis()->CenterTitle();
   hPartPt_trkCorr_trigCorr->GetXaxis()->SetTitle("p_{T} [GeV/c]");
   hPartPt_trkCorr_trigCorr->GetYaxis()->SetTitle("1/N_{ev} dN/dp_{T} (|#eta|<1)");
//   hPartPt_trkCorr_trigCorr->SetNdivisions(505);
   hPartPt_trkCorr_trigCorr->SetMarkerColor(1);
   hPartPt_trkCorr_trigCorr->SetLineColor(1);
   hPartPt_trkCorr_trigCorr->SetMarkerStyle(20);
   hPartPt_trkCorr_trigCorr->Scale(1./NumEv_Meas);
   hPartPt_trkCorr_trigCorr->Draw();

   hPartPt_trigCorr->SetMarkerColor(4);
   hPartPt_trigCorr->SetLineColor(4);
   hPartPt_trigCorr->SetMarkerStyle(20);
   hPartPt_trigCorr->Scale(1./NumEv_Meas);
   hPartPt_trigCorr->Draw("same");

   hPartPt_truth->SetMarkerColor(2);
   hPartPt_truth->SetLineColor(2);
   hPartPt_truth->SetMarkerStyle(24);
   hPartPt_truth->Scale(1./NumEv_Truth);
   hPartPt_truth->Draw("same");

   TLegend *leg1 = new TLegend(0.50,0.75,0.82,0.89,NULL,"brNDC");
   leg1->AddEntry(hPartPt_trkCorr_trigCorr,"Fully corrected (trig.+trk. corr.) reco","pl");
   leg1->AddEntry(hPartPt_trigCorr,"Trigger-corrected (no trk. corr.) reco","pl");
   leg1->AddEntry(hPartPt_truth,"Sim particles","pl");
   leg1->SetFillStyle(0);
   leg1->SetFillColor(0);
   leg1->SetBorderSize(0);
   leg1->Draw();
   if(doSave) {
      c1->SaveAs("Figs/ClosurePt_c1.gif");
      c1->SaveAs("Figs/ClosurePt_c1.eps");
      c1->SaveAs("Figs/ClosurePt_c1.C");
   }


   TCanvas *c2 = new TCanvas("c2","c2");
   c2->cd();
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
      c2->SaveAs("Figs/ClosurePt_c2.gif");
      c2->SaveAs("Figs/ClosurePt_c2.eps");
      c2->SaveAs("Figs/ClosurePt_c2.C");
   }


   TCanvas *c3 = new TCanvas("c3","c3");
   c3->cd();
   c3->SetLogy();
   hPartPt_trkCorr_trigCorr_JetsMod->Scale(1./NumEv_Meas);
   hPartPt_truth_JetsMod->Scale(1./NumEv_Truth);
   hPartPt_truth_JetsMod->SetMarkerColor(2);
   hPartPt_truth_JetsMod->SetLineColor(2);
   hPartPt_truth_JetsMod->SetMarkerStyle(24);
   hPartPt_truth_JetsMod->GetYaxis()->SetTitle("1/N_{ev} dN/dp_{T} (|#eta|<1)");
   hPartPt_truth_JetsMod->GetXaxis()->SetTitle("p_{T} [GeV/c]");
   hPartPt_truth_JetsMod->Draw();
   hPartPt_trkCorr_trigCorr_JetsMod->SetMarkerColor(1);
   hPartPt_trkCorr_trigCorr_JetsMod->SetLineColor(1);
   hPartPt_trkCorr_trigCorr_JetsMod->SetMarkerStyle(20);
   hPartPt_trkCorr_trigCorr_JetsMod->Draw("same");
   TLegend *leg3 = new TLegend(0.20,0.75,0.82,0.89,NULL,"brNDC");
   leg3->AddEntry(hPartPt_trkCorr_trigCorr_JetsMod,"Fully corrected (trig.+trk. corr.) reco, jet weights","pl");
   leg3->AddEntry(hPartPt_truth_JetsMod,"Sim particles, jet weights","pl");
   leg3->SetFillStyle(0);
   leg3->SetFillColor(0);
   leg3->SetBorderSize(0);
   leg3->Draw();
   if(doSave) {
      c3->SaveAs("Figs/ClosurePt_c3.gif");
      c3->SaveAs("Figs/ClosurePt_c3.eps");
      c3->SaveAs("Figs/ClosurePt_c3.C");
   }


   TCanvas *c4 = new TCanvas("c4","c4");
   c4->cd();
   TH1D *hPartPt_truth_JetsMod_copy1 = (TH1D*)hPartPt_truth_JetsMod->Clone("hPartPt_truth_JetsMod_copy1");
   hPartPt_truth_JetsMod_copy1->Divide(hPartPt_trkCorr_trigCorr_JetsMod);

   hPartPt_truth_JetsMod_copy1->GetYaxis()->SetTitle("Truth (jet mod) / Reco (jet mod)");
   hPartPt_truth_JetsMod_copy1->SetMarkerColor(1);
   hPartPt_truth_JetsMod_copy1->SetLineColor(1);
   hPartPt_truth_JetsMod_copy1->SetMarkerStyle(20);
   hPartPt_truth_JetsMod_copy1->Draw();
   if(doSave) {
      c4->SaveAs("Figs/ClosurePt_c4.gif");
      c4->SaveAs("Figs/ClosurePt_c4.eps");
      c4->SaveAs("Figs/ClosurePt_c4.C");
   }


   f_output->cd();
   hPartPt_trkCorr_trigCorr->Write();
   hPartPt_trkCorr_trigCorr_JetsMod->Write();
   hPartPt_truth->Write();
   hPartPt_truth_JetsMod->Write();
   hJetForCorr_orig->Write();
   hJetForCorr_weighted->Write();
   hNumEv_Meas->Write();
   hNumEv_Truth->Write();
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
