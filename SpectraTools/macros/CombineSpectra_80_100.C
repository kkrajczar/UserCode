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

void putLatexInfo(bool doIt, double min, double max); 
void plotClosure(TH1D* h1_corrRec, TH1D* h2_corrRec, TH1D *h3_corrRec, TH1D* h4_corrRec,
                 TH1D* h1_sim,     TH1D* h2_sim,     TH1D *h3_sim,     TH1D* h4_sim
                 );
TH1D* divideHistosDiffBins(TH1D* h_Num, TH1D* h_Den);
void normalizeByBinWidth(TH1D *histo);
//------------------------

void CombineSpectra_80_100()
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
   TFile * f_output = new TFile("CombineSpectra_80_100.root","recreate");

   TrackCorrector corr("trackCorrections_HIN12017v1_HijingCombined.root");
   corr.load("trkCorr_HIN12017");

   // Define the input file and HiForest
   char *infName_80_100 = "root://eoscms//eos/cms/store/caf/user/yjlee/pPb2013/promptReco/PA2013_HiForest_PromptReco_JSonPPb_forestv77.root";
   HiForest *c_80_100 = new HiForest(infName_80_100,"",cPPb);
//   c_80_100->doTrackCorrections=1;
//   c_80_100->InitTree();

   std::vector<Double_t> ptBins;
   const Double_t small = 1e-3;
   Double_t pt;
   for(pt =   0.  ; pt <   48.-small; pt +=  2./2.) ptBins.push_back(pt);
   for(pt =   48.; pt <   60.-small; pt +=  4./2.) ptBins.push_back(pt); 
   for(pt =   60.; pt <   76.-small; pt +=  8./2.) ptBins.push_back(pt); 
   for(pt =   76.; pt <   140.-small; pt +=  16./2.) ptBins.push_back(pt); 
   for(pt =   140.; pt <   364.-small; pt +=  32./2.) ptBins.push_back(pt); 
   ptBins.push_back(364.0);
/*
   std::vector<Double_t> ptBins_part;
   Double_t pt_part;
   for(pt_part =   0.2  ; pt_part <   1.2-small; pt_part +=  0.05) ptBins_part.push_back(pt_part);
   for(pt_part =   1.2; pt_part <   2.4-small; pt_part +=  0.1 ) ptBins_part.push_back(pt_part); //12 bins
   for(pt_part =   2.4; pt_part <   7.2-small; pt_part +=  0.4 ) ptBins_part.push_back(pt_part); //12 bins
   for(pt_part =   7.2; pt_part <  16.8-small; pt_part +=  1.6 ) ptBins_part.push_back(pt_part);//it was 3.2
   for(pt_part =  16.8; pt_part <  30.0-small; pt_part +=  6.6 ) ptBins_part.push_back(pt_part);
   for(pt_part =  30.0; pt_part <  100.0-small; pt_part +=  17.5 ) ptBins_part.push_back(pt_part);
   for(pt_part =  100.0; pt_part <  300.0-small; pt_part += 25. ) ptBins_part.push_back(pt_part);
   ptBins_part.push_back(300.0);
*/
   Int_t NumOfPtBins_part = 34;
   double ptBins_part[] = {0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0, 1.1, 1.2, 1.4, 1.6, 1.8, 2.0, 2.2, 2.4, 3.2, 4.0, 4.8, 5.6, 6.4, 7.2, 9.6, 12.0, 14.4, 19.2, 24.0, 28.8, 35.2, 41.6, 48.0, 60.8, 73.6, 86.4, 103.6};

   TTree * t = new TTree("t","whatever");
   JetData data(t,1);
/*
   TH1D * hJetPt_minbias = new TH1D("hJetPt_minbias","hJetPt_minbias",200,0.,200.);
   TH1D * hJetPt_Jet80 = new TH1D("hJetPt_Jet80","hJetPt_Jet80",200,0.,200.);
   TH1D * hJetPt_Jet100 = new TH1D("hJetPt_Jet100","hJetPt_Jet100",200,0.,200.);
   TH1D * hJetPt_Jet120 = new TH1D("hJetPt_Jet120","hJetPt_Jet120",200,0.,200.);
*/
   TH1D * hJetPt_Jet20 = new TH1D("hJetPt_Jet20","hJetPt_Jet20",ptBins.size()-1,&ptBins[0]);
   TH1D * hJetPt_Jet40 = new TH1D("hJetPt_Jet40","hJetPt_Jet40",ptBins.size()-1,&ptBins[0]);
   TH1D * hJetPt_Jet60 = new TH1D("hJetPt_Jet60","hJetPt_Jet60",ptBins.size()-1,&ptBins[0]);
   TH1D * hJetPt_Jet60_Req40 = new TH1D("hJetPt_Jet60_Req40","hJetPt_Jet60_Req40",ptBins.size()-1,&ptBins[0]);
   TH1D * hJetPt_Jet80 = new TH1D("hJetPt_Jet80","hJetPt_Jet80",ptBins.size()-1,&ptBins[0]);
   TH1D * hJetPt_Jet100 = new TH1D("hJetPt_Jet100","hJetPt_Jet100",ptBins.size()-1,&ptBins[0]);
   TH1D * hJetPt_Jet120 = new TH1D("hJetPt_Jet120","hJetPt_Jet120",ptBins.size()-1,&ptBins[0]);

//   TH1D * hPartPt_95_120_Jet80 = new TH1D("hPartPt_95_120_Jet80","hPartPt_95_120_Jet80",ptBins_part.size()-1,&ptBins_part[0]);
   TH1D * hPartPt_95_120_Jet80 = new TH1D("hPartPt_95_120_Jet80","hPartPt_95_120_Jet80",NumOfPtBins_part-1,&ptBins_part[0]);
   TH1D * hPartPt_95_120_Jet80_corrected = new TH1D("hPartPt_95_120_Jet80_corrected","hPartPt_95_120_Jet80_corrected",NumOfPtBins_part-1,&ptBins_part[0]);
//   TH1D * hPartPt_120_X_Jet100 = new TH1D("hPartPt_120_X_Jet100","hPartPt_120_X_Jet100",ptBins_part.size()-1,&ptBins_part[0]);
   TH1D * hPartPt_120_X_Jet100 = new TH1D("hPartPt_120_X_Jet100","hPartPt_120_X_Jet100",NumOfPtBins_part-1,&ptBins_part[0]);
   TH1D * hPartPt_120_X_Jet100_corrected = new TH1D("hPartPt_120_X_Jet100_corrected","hPartPt_120_X_Jet100_corrected",NumOfPtBins_part-1,&ptBins_part[0]);
   TH1D * hNumEv_95_120_Jet80 = new TH1D("hNumEv_95_120_Jet80","hNumEv_95_120_Jet80",1,0.,1.);
   TH1D * hNumEv_120_X_Jet100 = new TH1D("hNumEv_120_X_Jet100","hNumEv_120_X_Jet100",1,0.,1.);

   hJetPt_Jet20->Sumw2();
   hJetPt_Jet40->Sumw2();
   hJetPt_Jet60->Sumw2();
   hJetPt_Jet80->Sumw2();
   hJetPt_Jet100->Sumw2();
   hJetPt_Jet120->Sumw2();

   hPartPt_95_120_Jet80->Sumw2();
   hPartPt_95_120_Jet80_corrected->Sumw2();
   hPartPt_120_X_Jet100->Sumw2();
   hPartPt_120_X_Jet100_corrected->Sumw2();

   int numev_95_120_Jet80 = 0;
   int numev_120_X_Jet100 = 0;

   for (int i=0;i<c_80_100->GetEntries();i++) {
//   for (int i=0;i<100000;i++) {

      c_80_100->GetEntry(i);

      data.leadingJetPt = -1;
      data.leadingJetIt = -1;
      data.leadingJetTrackMax = -1;

      if (i % 2000 == 0) cout <<i<<" / "<<c_80_100->GetEntries()<<endl;

      if(c_80_100->evt.run>211256) //211256: last pPb run (Pb goes to +eta)
         continue;

      //event selection
      bool event_accepted = true;
      if(!(c_80_100->skim.phfPosFilter1 && c_80_100->skim.phfNegFilter1
          && c_80_100->skim.pBeamScrapingFilter
          && c_80_100->skim.pprimaryvertexFilter
          && c_80_100->skim.pVertexFilterCutGplus
          && TMath::Abs(c_80_100->evt.vz)<15.
          )
        ) event_accepted = false;

      if(event_accepted == false)
         continue;

      //Jets
      for (int j=0;j<c_80_100->akPu3PF.nref;j++) {
         if (fabs(c_80_100->akPu3PF.jteta[j])>2.5) continue;
//         if (fabs(c_80_100->akPu3PF.jtpt[j])<30) continue;
//         if (c_80_100->akPu3PF.trackMax[j]<4) continue; //Do we need this?
         if (c_80_100->akPu3PF.rawpt[j]<15) continue;
         if (c_80_100->akPu3PF.jtpt[j]>data.leadingJetPt) {
            data.leadingJetPt = c_80_100->akPu3PF.jtpt[j];
            data.leadingJetEta = c_80_100->akPu3PF.jteta[j];
            data.leadingJetPhi = c_80_100->akPu3PF.jtphi[j];
            data.leadingJetTrackMax = c_80_100->akPu3PF.trackMax[j];
            data.leadingJetIt = j;
         }
      }

      if(c_80_100->hlt.HLT_PAJet40_NoJetID_v1)
        hJetPt_Jet40->Fill(data.leadingJetPt);
      if(c_80_100->hlt.HLT_PAJet40_NoJetID_v1 && c_80_100->hlt.HLT_PAJet60_NoJetID_v1)
        hJetPt_Jet60_Req40->Fill(data.leadingJetPt);
      if(c_80_100->hlt.HLT_PAJet60_NoJetID_v1)
        hJetPt_Jet60->Fill(data.leadingJetPt);
      if(c_80_100->hlt.HLT_PAJet80_NoJetID_v1)
        hJetPt_Jet80->Fill(data.leadingJetPt);
      if(c_80_100->hlt.HLT_PAJet100_NoJetID_v1)
        hJetPt_Jet100->Fill(data.leadingJetPt);
      if(c_80_100->hlt.HLT_PAJet120_NoJetID_v1)
        hJetPt_Jet120->Fill(data.leadingJetPt);

      if(c_80_100->hlt.HLT_PAJet80_NoJetID_v1 && data.leadingJetPt>=95. && data.leadingJetPt<120.)
	 numev_95_120_Jet80++;
      if(c_80_100->hlt.HLT_PAJet100_NoJetID_v1 && data.leadingJetPt>=120.)
         numev_120_X_Jet100++;

      //Tracks
      for(int j=0;j<c_80_100->track.nTrk;j++) {
         if(!((c_80_100->track.trkPt[j]>0.2) 
             && (c_80_100->track.trkEta[j]<0.535)
             && (c_80_100->track.trkEta[j]>-1.465)
             && (c_80_100->track.highPurity[j])
             && (fabs(c_80_100->track.trkDz1[j]/c_80_100->track.trkDzError1[j])<3)
             && (fabs(c_80_100->track.trkDxy1[j]/c_80_100->track.trkDxyError1[j])<3)
             && (c_80_100->track.trkPtError[j]/c_80_100->track.trkPt[j]<0.1)
           ))
            continue;            

         if(data.leadingJetPt==-1) //for corrections
            data.leadingJetPt=10.;
         double trkWeight = 1.;
         trkWeight = corr.getWeight(c_80_100->track.trkPt[j],c_80_100->track.trkEta[j],data.leadingJetPt);

         if(c_80_100->hlt.HLT_PAJet80_NoJetID_v1 && data.leadingJetPt>=95. && data.leadingJetPt<120.) {
            hPartPt_95_120_Jet80->Fill(c_80_100->track.trkPt[j]);
            hPartPt_95_120_Jet80_corrected->Fill(c_80_100->track.trkPt[j],trkWeight);
         }
         if(c_80_100->hlt.HLT_PAJet100_NoJetID_v1 && data.leadingJetPt>=120.) {
            hPartPt_120_X_Jet100->Fill(c_80_100->track.trkPt[j]);
            hPartPt_120_X_Jet100_corrected->Fill(c_80_100->track.trkPt[j],trkWeight);
         }
      } //Tracks end
   }//event

   hNumEv_95_120_Jet80->SetBinContent(1,numev_95_120_Jet80);
   hNumEv_120_X_Jet100->SetBinContent(1,numev_120_X_Jet100);
   normalizeByBinWidth(hJetPt_Jet40);
   normalizeByBinWidth(hJetPt_Jet60);
   normalizeByBinWidth(hJetPt_Jet80);
   normalizeByBinWidth(hJetPt_Jet100);
   normalizeByBinWidth(hJetPt_Jet120);
   normalizeByBinWidth(hPartPt_95_120_Jet80);
   normalizeByBinWidth(hPartPt_95_120_Jet80_corrected);
   normalizeByBinWidth(hPartPt_120_X_Jet100);
   normalizeByBinWidth(hPartPt_120_X_Jet100_corrected);
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
   hJetPt_Jet80->Write();
   hJetPt_Jet100->Write();
   hPartPt_95_120_Jet80->Write();
   hPartPt_95_120_Jet80_corrected->Write();
   hPartPt_120_X_Jet100->Write();
   hPartPt_120_X_Jet100_corrected->Write();
   hNumEv_95_120_Jet80->Write();
   hNumEv_120_X_Jet100->Write();
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

void putLatexInfo(bool doIt, double min, double max) {

   TLatex *l1a = new TLatex(0.2,0.88,"akPu3PF jets, jet |#eta|<2.");
   l1a->SetNDC();
   l1a->SetTextSize(0.035);
   l1a->Draw();

   TLatex *l1b;
   if(doIt)
//      l1b = new TLatex(0.2,0.83,Form("Dijet event sel., track p_{T}>1 GeV/c, %f<x<%f",floor(100*min+0.5)/100f10,floor(100*max+0.5)/100));
//      l1b = new TLatex(0.2,0.83,Form("Dijet event sel., track p_{T}>1 GeV/c, %1.2f<x<%1.2f",min,max));
      l1b = new TLatex(0.2,0.83,Form("track p_{T}>1 GeV/c, %1.2f<x<%1.2f",min,max));
   else
//      l1b = new TLatex(0.2,0.83,"Dijet event sel., track p_{T}>1 GeV/c");
      l1b = new TLatex(0.2,0.83,"track p_{T}>1 GeV/c");
   l1b->SetNDC();
   l1b->SetTextSize(0.035);
   l1b->Draw();

   TLatex *l1c = new TLatex(0.2,0.78,"HiForest_V2_02_07");
   l1c->SetNDC();
   l1c->SetTextSize(0.035);
   l1c->Draw();

//  TLatex *l1d = new TLatex(0.2,0.73,Form("Centrality: %s",cent));
//   l1d->SetNDC();
//   l1d->SetTextSize(0.035);
//   l1d->Draw();
}

void plotClosure(TH1D* h1_corrRec, TH1D* h2_corrRec, TH1D *h3_corrRec, TH1D* h4_corrRec,
                 TH1D* h1_sim,     TH1D* h2_sim,     TH1D *h3_sim,     TH1D* h4_sim
                 )
 {

   h1_corrRec->SetMinimum(0.4);
   h1_corrRec->SetMaximum(1.6);
   h1_corrRec->GetXaxis()->SetRangeUser(2.,179.);
   h1_corrRec->GetXaxis()->CenterTitle();
   h1_corrRec->GetYaxis()->CenterTitle();
   h1_corrRec->GetYaxis()->SetTitleOffset(1.3);
   h1_corrRec->GetYaxis()->SetTitle("Corrected reco / Sim");
   h1_corrRec->GetXaxis()->SetTitle("p_{T} [GeV]");
   h1_corrRec->Divide(h1_sim);
   h1_corrRec->SetMarkerStyle(20);
   h1_corrRec->Draw();

   h2_corrRec->Divide(h2_sim);
   h2_corrRec->SetMarkerStyle(20);
   h2_corrRec->SetMarkerColor(2);
   h2_corrRec->SetLineColor(2);
   h2_corrRec->Draw("same");

   h3_corrRec->Divide(h3_sim);
   h3_corrRec->SetMarkerStyle(20);
   h3_corrRec->SetMarkerColor(3);
   h3_corrRec->SetLineColor(3);
   h3_corrRec->Draw("same");

   h4_corrRec->Divide(h4_sim);
   h4_corrRec->SetMarkerStyle(20);
   h4_corrRec->SetMarkerColor(4);
   h4_corrRec->SetLineColor(4);
   h4_corrRec->Draw("same");

   TLegend *leg1 = new TLegend(0.15,0.15,0.82,0.29,NULL,"brNDC");
   leg1->AddEntry(h1_corrRec,"50<jet p_{T}<60 GeV/c","p");
   leg1->AddEntry(h2_corrRec,"60<jet p_{T}<70 GeV/c","p");
   leg1->AddEntry(h3_corrRec,"70<jet p_{T}<80 GeV/c","p");
   leg1->AddEntry(h4_corrRec,"80<jet p_{T}<100 GeV/c","p");
   leg1->SetFillStyle(0);
   leg1->SetFillColor(0);
   leg1->SetBorderSize(0);
   leg1->Draw();
}

void normalizeByBinWidth(TH1D *histo) {
   for(int i = 1; i <= histo->GetNbinsX(); i++) {
      float content = histo->GetBinContent(i);
      float error = histo->GetBinError(i);
      histo->SetBinContent(i,content/histo->GetBinWidth(i));
      histo->SetBinError(i,error/histo->GetBinWidth(i));
   }
}
