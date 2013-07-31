// $Id: ChargedMultiplicityAnalyzerNoSimInfo_new.h,v 1.17 2011/11/06 16:57:59 krajczar Exp $

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

#include "Geometry/Records/interface/TrackerDigiGeometryRecord.h" 
#include "Geometry/TrackerGeometryBuilder/interface/TrackerGeometry.h"
#include "Geometry/TrackerGeometryBuilder/interface/PixelGeomDetUnit.h"
#include "Geometry/TrackerGeometryBuilder/interface/PixelGeomDetType.h"
#include "Geometry/TrackerGeometryBuilder/interface/RectangularPixelTopology.h"
#include "Geometry/CaloGeometry/interface/CaloCellGeometry.h"
#include "Geometry/CaloGeometry/interface/CaloGeometry.h"
#include "Geometry/Records/interface/CaloGeometryRecord.h"

#include "FWCore/Common/interface/TriggerNames.h"
#include "DataFormats/Common/interface/TriggerResults.h"
#include "DataFormats/L1GlobalTrigger/interface/L1GlobalTriggerReadoutSetupFwd.h"
#include "DataFormats/L1GlobalTrigger/interface/L1GlobalTriggerReadoutSetup.h"
#include "DataFormats/L1GlobalTrigger/interface/L1GlobalTriggerReadoutRecord.h"
#include "DataFormats/L1GlobalTrigger/interface/L1GlobalTriggerRecord.h"

#include "L1Trigger/GlobalTriggerAnalyzer/interface/L1GtUtils.h"
#include "CondFormats/L1TObjects/interface/L1GtTriggerMenu.h"
#include "CondFormats/DataRecord/interface/L1GtTriggerMenuRcd.h"

#include "CLHEP/Vector/LorentzVector.h"

#include "TROOT.h"
#include "TFile.h"
#include "TNtuple.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TMath.h"

#include <fstream>
#include <iomanip>

using namespace std;
using namespace reco;
using namespace edm;

/*****************************************************************************/
class ChargedMultiplicityAnalyzerNoSimInfo_new : public edm::EDAnalyzer
{
 public:
   explicit ChargedMultiplicityAnalyzerNoSimInfo_new(const edm::ParameterSet& pset);
   ~ChargedMultiplicityAnalyzerNoSimInfo_new();
//   virtual void beginJob(const edm::EventSetup& es);
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
//                        const reco::VertexCollection* vertices,
                        const edm::Event& ev,
                        const edm::EventSetup& es);
   bool isRecHitAtTheEdge(SiPixelRecHitCollection::DataContainer::const_iterator iPRH,
                          const PixelGeomDetUnit* pgdu);
   bool aboveTriggerThreshold_1(edm::Handle<CaloTowerCollection> towers);
   bool aboveTriggerThreshold_2(edm::Handle<CaloTowerCollection> towers);
   bool trackTrigger(edm::Handle<reco::TrackCollection>& recCollection);
   bool track5Trigger(edm::Handle<reco::TrackCollection>& recCollection);
   bool ChristofMinBias(const edm::Event& event, const edm::EventSetup& eventSetup);
   bool isAtEdge(const RectangularPixelTopology * topology,
                 const SiPixelRecHit & recHit);   
   void multiplicityProperties(const edm::Event& ev, const edm::EventSetup& es, 
                               edm::Handle<SiPixelRecHitCollection> siPixelRecCollection,
//                               const reco::VertexCollection* vertices,
                               int desLayer);
   void clusterVertices(const edm::Event& ev, const edm::EventSetup& es,
//                        const reco::VertexCollection* vertices,
                        edm::Handle<SiPixelRecHitCollection> siPixelRecCollection);
   float geomAcc(double vert_z, double eta_l, double eta_h, int desLayer);
   float produceClusterVertex(edm::Handle<SiPixelRecHitCollection> siPixelRecCollection);
   int getContainedHits(vector<VertexHit> hits, float z0, float & chi);
   float getVertexZ(edm::Handle<SiPixelRecHitCollection> siPixelRecCollection, const edm::Event& ev);

   const TrackerGeometry* theTracker;
   const SiPixelRecHitCollection* theHits;
   const BeamSpot * theBeamSpot;

   string trackCollectionLabel, resultFileLabel;
   edm::InputTag src_;
   edm::InputTag vertexColl_;
   bool simulateTriggers_;
   bool hasL1Triggers_;
   bool produceVertexLocally_;

   // file
   TFile * resultFile; 

   // ntuples
   TNtuple * multProp;
   TNtuple * nd_multProp;
   TNtuple * rd_multProp;
   TNtuple * multProp_looper;
   TNtuple * nd_multProp_looper;
   TNtuple * rd_multProp_looper;
   TNtuple * nCLusterVertices;

   // histograms
   TH1F * PureCorrEta;
   TH1F * PureCutCorrEta;
   TH1F * ResPureAdc;
   TH1F * ResPureAdc_det;
   TH1F * ResPureCentralAdc;
   TH1F * ResPureCutAdc;
   TH1F * ResPureCutCentralAdc;

   TH2F * hCorrEtaSizeY;
   TH2F * hCorrEtaADC;
   TH2F * hClusterZSizeY;
   TH2F * PureAdcvsCorrEta;
   TH2F * PureCutAdcvsCorrEta;

};

