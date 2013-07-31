// $Id: HITriggerAnalyzer.h,v 1.2 2011/11/06 16:57:59 krajczar Exp $

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
#include "DataFormats/HeavyIonEvent/interface/Centrality.h"
#include "SimDataFormats/GeneratorProducts/interface/HepMCProduct.h"

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

#include "SimTracker/TrackerHitAssociation/interface/TrackerHitAssociator.h"

#include "SimDataFormats/TrackingHit/interface/PSimHit.h"
#include "SimDataFormats/TrackingAnalysis/interface/TrackingParticle.h"
#include "SimDataFormats/TrackingAnalysis/interface/TrackingParticleFwd.h"
#include "SimDataFormats/TrackingAnalysis/interface/TrackingVertexContainer.h"

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

#include <fstream>
using namespace std;
using namespace reco;
using namespace edm;

/*****************************************************************************/
class HITriggerAnalyzer : public edm::EDAnalyzer
{
 public:
   explicit HITriggerAnalyzer(const edm::ParameterSet& pset);
   ~HITriggerAnalyzer();
   virtual void beginJob();
   virtual void analyze(const edm::Event& ev, const edm::EventSetup& es);
   virtual void endJob();

 private:
   struct VertexHit {
      float z;
      float r;
      int w;
   };
   PSimHit* findEarliestPSimHit(std::vector<PSimHit>& simHits);
   PSimHit* findLatestPSimHit(std::vector<PSimHit>& simHits);
   bool comparePSimHits(const PSimHit * hit1, const PSimHit * hit2);
   bool compareRecHits(const SiPixelRecHit * hit1, const SiPixelRecHit * hit2);
   bool aboveTriggerThreshold_1(edm::Handle<CaloTowerCollection> towers);
   bool aboveTriggerThreshold_2(edm::Handle<CaloTowerCollection> towers);
   bool trackTrigger(edm::Handle<reco::TrackCollection>& recCollection);
   bool RichardMinBias(Handle<HcalTrigPrimDigiCollection>& tpg);
   bool	ChristofMinBias(const edm::Event& event, const edm::EventSetup& eventSetup);
   void onTriggers(const edm::Event& ev, const edm::EventSetup& es, 
                               edm::Handle<CaloTowerCollection> towers,
                               edm::Handle<SiPixelRecHitCollection> siPixelRecCollection,
                               HepMC::GenEvent * myGenEvent,
                               edm::Handle<reco::TrackCollection>& recCollection,
                               Handle<HcalTrigPrimDigiCollection>& tpg,
                               edm::Handle<reco::Centrality> cent,
                               const HepMC::HeavyIon * hi_mc);
   float produceClusterVertex(edm::Handle<SiPixelRecHitCollection> siPixelRecCollection);
   int getContainedHits(vector<VertexHit> hits, float z0, float & chi);
   float getVertexZ(edm::Handle<SiPixelRecHitCollection> siPixelRecCollection, const edm::Event& ev);

   const TrackerGeometry* theTracker;
   const SiPixelRecHitCollection* theHits;
   const BeamSpot * theBeamSpot;
   const CentralityBins * theCentBins;

   TFile * resultFile; 

   TNtuple * multProp;

   string trackCollectionLabel, resultFileLabel;
   edm::InputTag src_;
   edm::InputTag digis_src_;
   edm::InputTag vertexColl_;
   bool hasL1Triggers_;
   bool produceVertexLocally_;
};
