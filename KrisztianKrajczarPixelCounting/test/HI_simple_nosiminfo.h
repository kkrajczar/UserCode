// $Id: HI_simple_nosiminfo.h,v 1.1 2011/11/06 17:08:27 krajczar Exp $

#include "DataFormats/SiPixelDigi/interface/PixelDigi.h"

#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/EventSetup.h"
#include "FWCore/Framework/interface/ESHandle.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "DataFormats/SiPixelDetId/interface/PixelSubdetector.h"
#include "DataFormats/SiPixelDetId/interface/PXBDetId.h"
#include "DataFormats/TrackerRecHit2D/interface/SiPixelRecHitCollection.h"
#include "DataFormats/VertexReco/interface/Vertex.h"
#include "DataFormats/VertexReco/interface/VertexFwd.h"
#include "DataFormats/DetId/interface/DetId.h"
#include "DataFormats/SiPixelCluster/interface/SiPixelCluster.h" 
#include "DataFormats/CaloTowers/interface/CaloTowerCollection.h"
#include "DataFormats/CaloTowers/interface/CaloTower.h"
#include "DataFormats/HcalDigi/interface/HcalDigiCollections.h"
#include "DataFormats/HcalRecHit/interface/HcalRecHitCollections.h"
#include "DataFormats/HcalRecHit/interface/HFRecHit.h"
#include "DataFormats/BeamSpot/interface/BeamSpot.h"
#include "DataFormats/HeavyIonEvent/interface/CentralityProvider.h"

#include "Geometry/Records/interface/TrackerDigiGeometryRecord.h" 
#include "Geometry/TrackerGeometryBuilder/interface/TrackerGeometry.h"
#include "Geometry/TrackerGeometryBuilder/interface/PixelGeomDetUnit.h"
#include "Geometry/TrackerGeometryBuilder/interface/PixelGeomDetType.h"
#include "Geometry/TrackerGeometryBuilder/interface/RectangularPixelTopology.h"
#include "Geometry/CaloGeometry/interface/CaloCellGeometry.h"
#include "Geometry/CaloGeometry/interface/CaloGeometry.h"
#include "Geometry/Records/interface/CaloGeometryRecord.h"

#include "CalibCalorimetry/CaloTPG/src/CaloTPGTranscoderULUT.h"

#include "CalibFormats/CaloTPG/interface/CaloTPGRecord.h"

#include "CLHEP/Vector/LorentzVector.h"

#include "FWCore/Common/interface/TriggerNames.h"
#include "DataFormats/Common/interface/TriggerResults.h"

#include "DataFormats/L1GlobalTrigger/interface/L1GlobalTriggerReadoutSetupFwd.h"
#include "DataFormats/L1GlobalTrigger/interface/L1GlobalTriggerReadoutSetup.h"
#include "DataFormats/L1GlobalTrigger/interface/L1GlobalTriggerReadoutRecord.h"
#include "DataFormats/L1GlobalTrigger/interface/L1GlobalTriggerRecord.h"
#include "L1Trigger/GlobalTriggerAnalyzer/interface/L1GtUtils.h"
#include "CondFormats/L1TObjects/interface/L1GtTriggerMenu.h"
#include "CondFormats/DataRecord/interface/L1GtTriggerMenuRcd.h"

#include "TROOT.h"
#include "TFile.h"
#include "TNtuple.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TMath.h"

#include <fstream>
using namespace std;
using namespace reco;
using namespace edm;

/*****************************************************************************/
class HI_simple_nosiminfo : public edm::EDAnalyzer
{
 public:
   explicit HI_simple_nosiminfo(const edm::ParameterSet& pset);
   ~HI_simple_nosiminfo();
   virtual void beginJob();
   virtual void analyze(const edm::Event& ev, const edm::EventSetup& es);
   virtual void endJob();

 private:
   struct VertexHit {
      float z;
      float r;
      int w;
   };
   bool compareRecHits(const SiPixelRecHit * hit1, const SiPixelRecHit * hit2);
   void onFirst(edm::Handle<SiPixelRecHitCollection>& siPixelRecCollection,
                                      const edm::Event& ev,
                                      const edm::EventSetup& es);
   bool isRecHitAtTheEdge(SiPixelRecHitCollection::DataContainer::const_iterator iPRH,
                          const PixelGeomDetUnit* pgdu);
   bool aboveTriggerThreshold_CandMaker(edm::Handle<CaloTowerCollection> towers, double threshold_);
   bool aboveTriggerThreshold_1(edm::Handle<CaloTowerCollection> towers);
   bool aboveTriggerThreshold_2(edm::Handle<CaloTowerCollection> towers);
   bool aboveTriggerThreshold_3(edm::Handle<CaloTowerCollection> towers);
   bool isAtEdge(const RectangularPixelTopology * topology,
                 const SiPixelRecHit & recHit);   
   void multiplicityProperties(const edm::Event& ev, const edm::EventSetup& es, 
                               edm::Handle<CaloTowerCollection> towers,
                               edm::Handle<SiPixelRecHitCollection> siPixelRecCollection,
                               edm::Handle<reco::TrackCollection>& recCollection,
                               Handle<HcalTrigPrimDigiCollection>& tpg,
                               CentralityProvider * centrality_,
                               int desLayer);
   void clusterVertices(const edm::Event& ev, const edm::EventSetup& es,
                        edm::Handle<SiPixelRecHitCollection> siPixelRecCollection);
   float produceClusterVertex(edm::Handle<SiPixelRecHitCollection> siPixelRecCollection);
   int getContainedHits(vector<VertexHit> hits, float z0, float & chi);
   bool getEdwardVertex(const edm::Event& ev);
   float getVertexZ(edm::Handle<SiPixelRecHitCollection> siPixelRecCollection, const edm::Event& ev);
   void HF_details(edm::Handle<CaloTowerCollection> towers,
                   CentralityProvider * centrality_,
                   const edm::Event& ev,
                   edm::Handle<SiPixelRecHitCollection> siPixelRecCollection);
   int KK_B0_cent(edm::Handle<CaloTowerCollection> towers);

   const TrackerGeometry* theTracker;
   const SiPixelRecHitCollection* theHits;
   const BeamSpot * theBeamSpot;
   CentralityProvider * centrality_;

   TH1F * hNum_nd; 
   TH1F * hNum_nsd; 
   TH1F * hNum_nsd_trig; 
   TH1F * hNum_sd_trig; 

   TFile * resultFile; 

   TNtuple * nHF_towers;
   TNtuple * nHF_event;
   TNtuple * nHF_Y_event;

   TNtuple * multProp;
   TNtuple * nd_multProp;
   TNtuple * rd_multProp;
   TNtuple * multProp_looper;
   TNtuple * nd_multProp_looper;
   TNtuple * rd_multProp_looper;
   TH1D * hLooperPt;
   TH1D * hPt;
   TH1D * hNonLooperPt;
   TNtuple * hJustLooper;
   TNtuple * nd_hJustLooper;
   TNtuple * rd_hJustLooper;

   // cluster vertices
   TNtuple * nCLusterVertices;
   TNtuple * nClusterPrim;
   TNtuple * nClusterAll;
   TNtuple * nClusterUnused;
   // cluster size
   TH2F * hCorrEtaSizeY;
   TH2F * hCorrEtaADC;
   TH2F * hClusterZSizeY;
   TH1F * ResPureClusterY;
   TH1F * ResSimRecClusterY;
   TH1F * ResElseSimRecClusterY;

   TH1D * hTestEtaFull;
   TH1D * hTestEtaRestricted; 

   TH1D * hLastTOF;

   int full;
   int restricted;

   TH1F * PureCorrEta;
   TH1F * PureCutCorrEta;
   TH1F * DesiredEtaDist;
   TH1F * RecAdc;
   TH1F * ResCentralAdc;
   TH1F * ResCentralAdcFine;
   TH1F * ResElseCentralAdc;
   TH1F * ResPureAdc;
   TH1F * ResPureAdc_det;
   TH1F * ResPureCentralAdc;
   TH1F * ResPureCutAdc;
   TH1F * ResPureCutCentralAdc;

   TH2F * RecAdcvsCorrEta;
   TH2F * PureAdcvsCorrEta;
   TH2F * PureCutAdcvsCorrEta;
   TH2F * hAdcPerCoshCorrEta;

   string trackCollectionLabel, resultFileLabel;
   edm::InputTag src_;
   edm::InputTag digis_src_;
   edm::InputTag vertexColl_;
   edm::InputTag triggerLabel_;
   bool hasL1Triggers_;
   bool produceVertexLocally_;

   int test;
   int proba;
};
