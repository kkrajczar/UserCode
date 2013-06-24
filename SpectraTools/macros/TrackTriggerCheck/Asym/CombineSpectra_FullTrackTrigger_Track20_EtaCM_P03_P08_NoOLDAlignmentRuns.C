#include "../../../hiForest.h"
#include "../../../utilities.h"
#include <TROOT.h>
#include <TStyle.h>
#include <TFile.h>
#include <TH1D.h>
#include <TNtuple.h>
#include <iostream>
#include <TLegend.h>
#include <TLatex.h>
#include "../../TrackCorrector.C"

TH1D* divideHistosDiffBins(TH1D* h_Num, TH1D* h_Den);
void normalizeByBinWidth(TH1D *histo);
//------------------------

void CombineSpectra_FullTrackTrigger_Track20_EtaCM_P03_P08_NoOLDAlignmentRuns()
{
   //Plan: trigger efficiencies (up to a plateau): Not sure though if this would work
   // Jet40: from MB
   // Jet60: from MB or Jet40
   // Jet80: from MB or Jet40 or Jet60

   gROOT->Reset();
   gROOT->ProcessLine(".x rootlogonChristof.C");
   gROOT->ForceStyle();
   gStyle->SetPalette(1);
   gStyle->SetTitleYOffset(1.30);
   gStyle->SetPadRightMargin(0.16);

   bool doSave = false;
   TFile * f_output = new TFile("CombineSpectra_FullTrackTrigger_Track20_EtaCM_P03_P08_NoOLDAlignmentRuns.root","recreate");

   TrackCorrector corr("../../trackCorrections_HIN12017v1_HijingCombined.root");
   corr.load("trkCorr_HIN12017");

   // Define the input file and HiForest
   char *infName_FullTrackTrigger_Track20 = "root://eoscms//eos/cms/store/group/phys_heavyions/krajczar/FullTrack20/PA2013_HiForest_PromptReco_highPtTrack20_JSonPPb_forestv84.root";
   HiForest *c_FullTrackTrigger_Track20 = new HiForest(infName_FullTrackTrigger_Track20,"",cPPb);
//   c_FullTrackTrigger_Track20->doTrackCorrections=1;
//   c_FullTrackTrigger_Track20->InitTree();

   std::vector<Double_t> ptBins;
   const Double_t small = 1e-3;
   Double_t pt;
   for(pt = 0.2; pt < 20.0-small; pt += 0.1 ) { ptBins.push_back(pt); std::cerr<<" pt: " << pt << std::endl; }
   for(pt = 20.0; pt < 40.0-small; pt += 0.2 ) { ptBins.push_back(pt); std::cerr<<" pt: " << pt << std::endl; }
   for(pt = 40.0; pt < 103.6-small; pt += 0.4 ) { ptBins.push_back(pt); std::cerr<<" pt: " << pt << std::endl; }
   ptBins.push_back(103.6);
   std::cerr<<" ptBins.size()-1: " << ptBins.size()-1 << std::endl;

   //orig
//   Int_t NumOfPtBins_part = 34;
//   double ptBins_part[] = {0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0, 1.1, 1.2, 1.4, 1.6, 1.8, 2.0, 2.2, 2.4, 3.2, 4.0, 4.8, 5.6, 6.4, 7.2, 9.6, 12.0, 14.4, 19.2, 24.0, 28.8, 35.2, 41.6, 48.0, 60.8, 73.6, 86.4, 103.6};
   //extended pt bins, binwidth at the end: 17.2
   Int_t NumOfPtBins_part = 40;
   double ptBins_part[] = {0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0, 1.1, 1.2, 1.4, 1.6, 1.8, 2.0, 2.2, 2.4, 3.2, 4.0, 4.8, 5.6, 6.4, 7.2, 9.6, 12.0, 14.4, 19.2, 24.0, 28.8, 35.2, 41.6, 48.0, 60.8, 73.6, 86.4, 103.6, 120.8, 138., 155.2, 172.4, 189.6, 206.8};

   TTree * t = new TTree("t","whatever");
   JetData data(t,1);

   //For trigger
   TH1D * hPartPt_FullTrack20_trkCorr = new TH1D("hPartPt_FullTrack20_trkCorr","hPartPt_FullTrack20_trkCorr",NumOfPtBins_part-1,&ptBins_part[0]);
   TH1D * hPartPt_FullTrack20_trkCorr_trigCorr = new TH1D("hPartPt_FullTrack20_trkCorr_trigCorr","hPartPt_FullTrack20_trkCorr_trigCorr",NumOfPtBins_part-1,&ptBins_part[0]);
   TH1D * hPartPt_FullTrack20_trkCorr_smallerBins = new TH1D("hPartPt_FullTrack20_trkCorr_smallerBins","hPartPt_FullTrack20_trkCorr_smallerBins",ptBins.size()-1,&ptBins[0]);
   TH1D * hPartPt_FullTrack20_trkCorr_trigCorr_smallerBins = new TH1D("hPartPt_FullTrack20_trkCorr_trigCorr_smallerBins","hPartPt_FullTrack20_trkCorr_trigCorr_smallerBins",ptBins.size()-1,&ptBins[0]);

   //For spectra combination
   TH1D * hPartPt_FullTrack20_22_32_trkCorr_trigCorr = new TH1D("hPartPt_FullTrack20_22_32_trkCorr_trigCorr","hPartPt_FullTrack20_SpectCombt_rkCorr_trigCorr",NumOfPtBins_part-1,&ptBins_part[0]);
   TH1D * hNumEv_FullTrack20_22_32_trigCorr = new TH1D("hNumEv_FullTrack20_22_32_trigCorr","hNumEv_FullTrack20_22_32_trigCorr",1,0.,1.);
   TH1D * hNumEv_FullTrack20_32_X_trigCorr = new TH1D("hNumEv_FullTrack20_32_X_trigCorr","hNumEv_FullTrack20_32_X_trigCorr",1,0.,1.);

   hPartPt_FullTrack20_trkCorr->Sumw2();
   hPartPt_FullTrack20_trkCorr_trigCorr->Sumw2();
   hPartPt_FullTrack20_trkCorr_smallerBins->Sumw2();
   hPartPt_FullTrack20_trkCorr_trigCorr_smallerBins->Sumw2();

   hPartPt_FullTrack20_22_32_trkCorr_trigCorr->Sumw2();

   int numev_FullTrack20_22_32_trigCorr = 0;
   int numev_FullTrack20_32_X_trigCorr = 0;

   for (int i=0;i<c_FullTrackTrigger_Track20->GetEntries();i++) {
//   for (int i=0;i<1000000;i++) {

      c_FullTrackTrigger_Track20->GetEntry(i);

      data.leadingJetPt = -1;
      data.leadingJetIt = -1;
      data.leadingJetTrackMax = -1;

      if (i % 2000 == 0) cout <<i<<" / "<<c_FullTrackTrigger_Track20->GetEntries()<<endl;

      if(c_FullTrackTrigger_Track20->evt.run<210676 || c_FullTrackTrigger_Track20->evt.run>211256) //211256: last pPb run (Pb goes to +eta)
         continue;

      //event selection
      bool event_accepted = true;
      if(!(c_FullTrackTrigger_Track20->skim.phfPosFilter1 && c_FullTrackTrigger_Track20->skim.phfNegFilter1
          && c_FullTrackTrigger_Track20->skim.pBeamScrapingFilter
          && c_FullTrackTrigger_Track20->skim.pprimaryvertexFilter
          && c_FullTrackTrigger_Track20->skim.pVertexFilterCutGplus
          && TMath::Abs(c_FullTrackTrigger_Track20->evt.vz)<15.
          )
        ) event_accepted = false;

      if(event_accepted == false)
         continue;

      //Jets
      for (int j=0;j<c_FullTrackTrigger_Track20->akPu3PF.nref;j++) {
         if (fabs(c_FullTrackTrigger_Track20->akPu3PF.jteta[j])>2.5) continue;
//         if (fabs(c_FullTrackTrigger_Track20->akPu3PF.jtpt[j])<30) continue;
//         if (c_FullTrackTrigger_Track20->akPu3PF.trackMax[j]<4) continue; //Do we need this?
         if (c_FullTrackTrigger_Track20->akPu3PF.rawpt[j]<15) continue;
         if (c_FullTrackTrigger_Track20->akPu3PF.jtpt[j]>data.leadingJetPt) {
            data.leadingJetPt = c_FullTrackTrigger_Track20->akPu3PF.jtpt[j];
            data.leadingJetEta = c_FullTrackTrigger_Track20->akPu3PF.jteta[j];
            data.leadingJetPhi = c_FullTrackTrigger_Track20->akPu3PF.jtphi[j];
            data.leadingJetTrackMax = c_FullTrackTrigger_Track20->akPu3PF.trackMax[j];
            data.leadingJetIt = j;
         }
      }

      //Tracks for event weights; eta-pt cut removed
      int trackMult = 0;
      for(int j=0;j<c_FullTrackTrigger_Track20->track.nTrk;j++) {
         if(!((c_FullTrackTrigger_Track20->track.highPurity[j])
             && (fabs(c_FullTrackTrigger_Track20->track.trkDz1[j]/c_FullTrackTrigger_Track20->track.trkDzError1[j])<3)
             && (fabs(c_FullTrackTrigger_Track20->track.trkDxy1[j]/c_FullTrackTrigger_Track20->track.trkDxyError1[j])<3)
             && (c_FullTrackTrigger_Track20->track.trkPtError[j]/c_FullTrackTrigger_Track20->track.trkPt[j]<0.1)
            ))
            continue;
         trackMult++;
      }
      // Don't analyze 0 multiplicity events; add correction later if needed
      if(trackMult==0)
        { std::cerr<<" FullTrack20 but 0 multiplicity!!" << std::endl; continue; }
      double evtWeight = 1.;
      evtWeight = corr.getEventWeight(trackMult);

      //Tracks for event classification: same as for analysis
      bool FullTrack20_trackAbove22 = false;
      bool FullTrack20_trackAbove32 = false;
      double rapidityShift = 0.465; //eta_lab = eta_cm - y_NN
      for(int j=0;j<c_FullTrackTrigger_Track20->track.nTrk;j++) {
         if(!((c_FullTrackTrigger_Track20->track.trkPt[j]>0.2) 
             && (c_FullTrackTrigger_Track20->track.trkEta[j]<(0.8-rapidityShift))
             && (c_FullTrackTrigger_Track20->track.trkEta[j]>(0.3-rapidityShift))
             && (c_FullTrackTrigger_Track20->track.highPurity[j])
             && (fabs(c_FullTrackTrigger_Track20->track.trkDz1[j]/c_FullTrackTrigger_Track20->track.trkDzError1[j])<3)
             && (fabs(c_FullTrackTrigger_Track20->track.trkDxy1[j]/c_FullTrackTrigger_Track20->track.trkDxyError1[j])<3)
             && (c_FullTrackTrigger_Track20->track.trkPtError[j]/c_FullTrackTrigger_Track20->track.trkPt[j]<0.1)
           ))
            continue;            
           if(c_FullTrackTrigger_Track20->track.trkPt[j]>22.)
              FullTrack20_trackAbove22 = true; 
           if(c_FullTrackTrigger_Track20->track.trkPt[j]>32.)
              FullTrack20_trackAbove32 = true;
      }


      //Tracks
      for(int j=0;j<c_FullTrackTrigger_Track20->track.nTrk;j++) {
         if(!((c_FullTrackTrigger_Track20->track.trkPt[j]>0.2) 
             && (c_FullTrackTrigger_Track20->track.trkEta[j]<(0.8-rapidityShift))
             && (c_FullTrackTrigger_Track20->track.trkEta[j]>(0.3-rapidityShift))
             && (c_FullTrackTrigger_Track20->track.highPurity[j])
             && (fabs(c_FullTrackTrigger_Track20->track.trkDz1[j]/c_FullTrackTrigger_Track20->track.trkDzError1[j])<3)
             && (fabs(c_FullTrackTrigger_Track20->track.trkDxy1[j]/c_FullTrackTrigger_Track20->track.trkDxyError1[j])<3)
             && (c_FullTrackTrigger_Track20->track.trkPtError[j]/c_FullTrackTrigger_Track20->track.trkPt[j]<0.1)
           ))
            continue;            

         // trk corrections
         if(data.leadingJetPt==-1) //for corrections
            data.leadingJetPt=10.;
         double trkWeight = 1.;
         trkWeight = corr.getWeight(c_FullTrackTrigger_Track20->track.trkPt[j],c_FullTrackTrigger_Track20->track.trkEta[j],data.leadingJetPt);

         //Trigger
         //v1 version of the trigger is not stored in HLTAnalysis, rely on skimming (so don't require HLT path here)
         hPartPt_FullTrack20_trkCorr->Fill(c_FullTrackTrigger_Track20->track.trkPt[j],trkWeight);
         hPartPt_FullTrack20_trkCorr_trigCorr->Fill(c_FullTrackTrigger_Track20->track.trkPt[j],trkWeight*evtWeight);
         hPartPt_FullTrack20_trkCorr_smallerBins->Fill(c_FullTrackTrigger_Track20->track.trkPt[j],trkWeight);
         hPartPt_FullTrack20_trkCorr_trigCorr_smallerBins->Fill(c_FullTrackTrigger_Track20->track.trkPt[j],trkWeight*evtWeight);

         //Spectra combination
         if(FullTrack20_trackAbove22 && !FullTrack20_trackAbove32) {
            hPartPt_FullTrack20_22_32_trkCorr_trigCorr->Fill(c_FullTrackTrigger_Track20->track.trkPt[j],trkWeight*evtWeight);
         }
      } //Tracks end
 
      // event number
      if(FullTrack20_trackAbove22 && !FullTrack20_trackAbove32)
         numev_FullTrack20_22_32_trigCorr += evtWeight;
      if(FullTrack20_trackAbove32)
         numev_FullTrack20_32_X_trigCorr += evtWeight;
   }//event

   hNumEv_FullTrack20_22_32_trigCorr->SetBinContent(1,numev_FullTrack20_22_32_trigCorr);
   hNumEv_FullTrack20_32_X_trigCorr->SetBinContent(1,numev_FullTrack20_32_X_trigCorr);
   normalizeByBinWidth(hPartPt_FullTrack20_trkCorr);
   normalizeByBinWidth(hPartPt_FullTrack20_trkCorr_trigCorr);
   normalizeByBinWidth(hPartPt_FullTrack20_trkCorr_smallerBins);
   normalizeByBinWidth(hPartPt_FullTrack20_trkCorr_trigCorr_smallerBins);
   normalizeByBinWidth(hPartPt_FullTrack20_22_32_trkCorr_trigCorr);
/*
   TCanvas *c1 = new TCanvas("c1","c1");
   c1->SetLogy();

   hJetPt_minbias->GetXaxis()->CenterTitle();
   hJetPt_minbias->GetYaxis()->CenterTitle();
   hJetPt_minbias->GetXaxis()->SetTitle("Offline jet p_{T} [GeV/c]");
   hJetPt_minbias->GetYaxis()->SetTitle("N_{Leading jet} (|#eta|<2) / GeV/c");
   hJetPt_minbias->SetNdivisions(505);
   hJetPt_minbias->SetMarkerColor(1);
   hJetPt_minbias->SetLineColor(1);
   hJetPt_minbias->SetMarkerStyle(20);
   hJetPt_minbias->Draw();

   hJetPt_Jet40->SetMarkerColor(3);
   hJetPt_Jet40->SetLineColor(3);
   hJetPt_Jet40->SetMarkerStyle(28);
   hJetPt_Jet40->Draw();

   hJetPt_Jet60->SetMarkerColor(5);
   hJetPt_Jet60->SetLineColor(5);
   hJetPt_Jet60->SetMarkerStyle(30);
   hJetPt_Jet60->Draw("same");

   hJetPt_Jet80->SetMarkerColor(4);
   hJetPt_Jet80->SetLineColor(4);
   hJetPt_Jet80->SetMarkerStyle(24);
   hJetPt_Jet80->Draw("same");

   hJetPt_Jet100->SetMarkerColor(6);
   hJetPt_Jet100->SetLineColor(6);
   hJetPt_Jet100->SetMarkerStyle(25);
   hJetPt_Jet100->Draw("same");

   hJetPt_Jet120->SetMarkerColor(2);
   hJetPt_Jet120->SetLineColor(2);
   hJetPt_Jet120->SetMarkerStyle(27);
   hJetPt_Jet120->Draw("same");

   TLegend *leg1 = new TLegend(0.50,0.75,0.82,0.89,NULL,"brNDC");
//   leg1->AddEntry(hJetPt_minbias,"MinBias","pl");
   leg1->AddEntry(hJetPt_Jet40,"Jet40","pl");
   leg1->AddEntry(hJetPt_Jet60,"Jet60","pl");
//   leg1->AddEntry(hJetPt_Jet80,"Jet80","pl");
//   leg1->AddEntry(hJetPt_Jet100,"Jet100","pl");
//   leg1->AddEntry(hJetPt_Jet120,"Jet120","pl");
   leg1->SetFillStyle(0);
   leg1->SetFillColor(0);
   leg1->SetBorderSize(0);
   leg1->Draw();
   if(doSave) {
      c1->SaveAs("Figs/c1.gif");
      c1->SaveAs("Figs/c1.eps");
      c1->SaveAs("Figs/c1.C");
   }


   TCanvas *c2 = new TCanvas("c2","c2");
   TH1D *hJetPt_Jet40_copy1 = (TH1D*)hJetPt_Jet40->Clone("hJetPt_Jet40_copy1");
   TH1D *hJetPt_Jet60_copy1 = (TH1D*)hJetPt_Jet60->Clone("hJetPt_Jet60_copy1");
   TH1D *hJetPt_Jet80_copy1 = (TH1D*)hJetPt_Jet80->Clone("hJetPt_Jet80_copy1");
   TH1D *hJetPt_Jet100_copy1 = (TH1D*)hJetPt_Jet100->Clone("hJetPt_Jet100_copy1");
   TH1D *hJetPt_Jet120_copy1 = (TH1D*)hJetPt_Jet120->Clone("hJetPt_Jet120_copy1");

//   hJetPt_Jet40_copy1->Divide(hJetPt_Jet40,hJetPt_minbias,1,1,"B");
//   hJetPt_Jet60_copy1->Divide(hJetPt_Jet60,hJetPt_minbias,1,1,"B");
//   hJetPt_Jet80_copy1->Divide(hJetPt_Jet80,hJetPt_minbias,1,1,"B");
//   hJetPt_Jet100_copy1->Divide(hJetPt_Jet100,hJetPt_minbias,1,1,"B");
//   hJetPt_Jet120_copy1->Divide(hJetPt_Jet120,hJetPt_minbias,1,1,"B");
   hJetPt_Jet60_copy1->Divide(hJetPt_Jet60,hJetPt_Jet40,1,1,"B");

//   hJetPt_Jet40_copy1->GetYaxis()->SetTitle("Trigger efficiency");
//   hJetPt_Jet40_copy1->Draw();
   hJetPt_Jet60_copy1->Draw();
//   hJetPt_Jet80_copy1->Draw("same");
//   hJetPt_Jet100_copy1->Draw("same");
//   hJetPt_Jet120_copy1->Draw("same");

   TLegend *leg2 = new TLegend(0.50,0.75,0.82,0.89,NULL,"brNDC");
   leg2->AddEntry(hJetPt_Jet40_copy1,"Jet40","pl");
   leg2->AddEntry(hJetPt_Jet60_copy1,"Jet60","pl");
   leg2->AddEntry(hJetPt_Jet80_copy1,"Jet80","pl");
   leg2->AddEntry(hJetPt_Jet100_copy1,"Jet100","pl");
   leg2->AddEntry(hJetPt_Jet120_copy1,"Jet120","pl");
   leg2->SetFillStyle(0);
   leg2->SetFillColor(0);
   leg2->SetBorderSize(0);
   leg2->Draw();
   if(doSave) {
      c2->SaveAs("Figs/c2.gif");
      c2->SaveAs("Figs/c2.eps");
      c2->SaveAs("Figs/c2.C");
   }
*/
   f_output->cd();
   hPartPt_FullTrack20_trkCorr->Write();
   hPartPt_FullTrack20_trkCorr_trigCorr->Write();
   hPartPt_FullTrack20_trkCorr_smallerBins->Write();
   hPartPt_FullTrack20_trkCorr_trigCorr_smallerBins->Write();
   hPartPt_FullTrack20_22_32_trkCorr_trigCorr->Write();
   hNumEv_FullTrack20_22_32_trigCorr->Write();
   hNumEv_FullTrack20_32_X_trigCorr->Write();
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
