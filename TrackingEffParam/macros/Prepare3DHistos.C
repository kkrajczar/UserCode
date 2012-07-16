


#include "hiForest.h"
#include "TCanvas.h"
#include "TH3.h"
#include "TH2.h"
#include "TH1.h"
#include "TNtuple.h"
#include "TMath.h"

#include "TCut.h"
#include <string>

using namespace std;

void Prepare3DHistos(
		 const char* infname = "/net/hisrv0001/home/yenjie/scratch/hiForest/prod/production/CMSSW_4_4_2_patch6/test/forest21_simTrack/merged_pthat80_simTrack_v2.root",
                 const char* outname = "TrkCorr_3DHistos_pThat80_Inclusive.root",
                 bool save = false
		 ) {

  //Define binning	
  const Double_t small = 1e-3;

  std::vector<Double_t> ptBins;
  Double_t pt;
  for(pt =   0  ; pt <   1.0-small; pt +=  0.15) ptBins.push_back(pt); //8 bins
  for(pt =   1.0; pt <   2.2-small; pt +=  0.1) ptBins.push_back(pt); //12 bins
  for(pt =   2.2; pt <   6.0-small; pt +=  0.475) ptBins.push_back(pt); //8 bins
  for(pt =   6.0; pt <  22.-small; pt +=  2. ) ptBins.push_back(pt); // 8 bins
  Double_t highPtBins[8] = {22.,30.,45.,60.,90.,120.,180.,300.};
  ptBins.insert(ptBins.end(),highPtBins,highPtBins+8);

  std::vector<Double_t> etaBins;
  Double_t eta;
  for(eta = -2.4; eta < 2.4-small; eta += 0.1) etaBins.push_back(eta);
  etaBins.push_back(2.4);

  std::vector<Double_t> phiBins;
  Double_t phi;
  for(phi = -TMath::Pi(); phi < TMath::Pi()-small; phi += 0.1) phiBins.push_back(phi);
  phiBins.push_back(TMath::Pi());

  //Recreate output file
  TFile* outf = new TFile(outname, "recreate");

  //Define output histograms
  TH3D * hSim3D = new TH3D("hSim3D","hSim3D",etaBins.size()-1,&etaBins[0],ptBins.size()-1,&ptBins[0],phiBins.size()-1,&phiBins[0]);
  TH3D * hEff3D = new TH3D("hEff3D","hEff3D",etaBins.size()-1,&etaBins[0],ptBins.size()-1,&ptBins[0],phiBins.size()-1,&phiBins[0]);

  TH3D * hRec3D = new TH3D("hRec3D","hRec3D",etaBins.size()-1,&etaBins[0],ptBins.size()-1,&ptBins[0],phiBins.size()-1,&phiBins[0]);
  TH3D * hFak3D = new TH3D("hFak3D","hFak3D",etaBins.size()-1,&etaBins[0],ptBins.size()-1,&ptBins[0],phiBins.size()-1,&phiBins[0]);

  HiForest * t = new HiForest(infname);
  t->InitTree();

  //Event loop
  int maxEvents = t->GetEntries();
  for(int iev = 0; iev < maxEvents; ++iev) {
     if(iev%1000==0)cout<<"Processing entry : "<<iev<<" / "<<t->GetEntries()<<endl;
     t->GetEntry(iev);

//     int cent = t->evt.hiBin;
 
     //SimTrack loop
     for(int i = 0; i < t->track.nParticle; ++i) {
        double simEta = t->track.pEta[i];
        double simPhi = t->track.pPhi[i];
        double simPt = t->track.pPt[i];

        hSim3D->Fill(simEta,simPt,simPhi);        
        if(t->track.pNRec[i]==1 && (t->track.mtrkQual[i]==1 || t->track.mtrkAlgo[i]<4))
           hEff3D->Fill(simEta,simPt,simPhi);        
     }
 
     //Track loop
     for(int i = 0; i < t->track.nTrk; ++i) {
        double trkEta =  t->track.trkEta[i];
        double trkPt =  t->track.trkPt[i];
        double trkPhi =  t->track.trkPhi[i];
 
        if(!(t->track.trkAlgo[i]<4 || t->track.highPurity[i]==1))
         continue;

        hRec3D->Fill(trkEta,trkPt,trkPhi);
        if(t->track.trkFake[i]==1)
           hFak3D->Fill(trkEta,trkPt,trkPhi);
     }
  }


  //Write output
  if(save) {
     outf->cd();

     hSim3D->Write();
     hEff3D->Write();
     hRec3D->Write();
     hFak3D->Write();

     outf->Close();
  }
}


