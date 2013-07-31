// $Id: ChargedMultiplicityAnalyzer_new.h,v 1.15 2011/11/06 16:57:59 krajczar Exp $

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

#include "CalibCalorimetry/CaloTPG/src/CaloTPGTranscoderULUT.h"

#include "CalibFormats/CaloTPG/interface/CaloTPGRecord.h"

#include "SimTracker/TrackerHitAssociation/interface/TrackerHitAssociator.h"

#include "SimDataFormats/TrackingHit/interface/PSimHit.h"
#include "SimDataFormats/TrackingAnalysis/interface/TrackingParticle.h"
#include "SimDataFormats/TrackingAnalysis/interface/TrackingParticleFwd.h"
#include "SimDataFormats/TrackingAnalysis/interface/TrackingVertexContainer.h"

#include "CLHEP/Vector/LorentzVector.h"

#include "MagneticField/Records/interface/IdealMagneticFieldRecord.h"
#include "MagneticField/Engine/interface/MagneticField.h"

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
class ChargedMultiplicityAnalyzer_new : public edm::EDAnalyzer
{
 public:
   explicit ChargedMultiplicityAnalyzer_new(const edm::ParameterSet& pset);
   ~ChargedMultiplicityAnalyzer_new();
   virtual void beginJob();
   virtual void analyze(const edm::Event& ev, const edm::EventSetup& es);
   virtual void endJob();

 private:
   struct VertexHit {
      float z;
      float r;
      int w;
   };
   void checkVertices(
//                      const reco::VertexCollection* vertices,
                      edm::Handle<TrackingVertexCollection>& TVCollection,
                      edm::Handle<reco::TrackCollection>& recCollection,
                      HepMC::GenEvent * myGenEvent);
   PSimHit* findEarliestPSimHit(std::vector<PSimHit>& simHits);
   PSimHit* findLatestPSimHit(std::vector<PSimHit>& simHits);
   bool comparePSimHits(const PSimHit * hit1, const PSimHit * hit2);
   bool compareRecHits(const SiPixelRecHit * hit1, const SiPixelRecHit * hit2);
   void FirstSimOnFirst(edm::Handle<SiPixelRecHitCollection>& siPixelRecCollection,
//                        const reco::VertexCollection* vertices,
                        const edm::Event& ev,
                        const edm::EventSetup& es);
   bool isRecHitAtTheEdge(SiPixelRecHitCollection::DataContainer::const_iterator iPRH,
                          const PixelGeomDetUnit* pgdu);
   bool aboveTriggerThreshold_1(edm::Handle<CaloTowerCollection> towers);
   bool aboveTriggerThreshold_2(edm::Handle<CaloTowerCollection> towers);
   bool trackTrigger(edm::Handle<reco::TrackCollection>& recCollection);
   bool track5Trigger(edm::Handle<reco::TrackCollection>& recCollection);
   bool RichardMinBias(Handle<HcalTrigPrimDigiCollection>& tpg);
   bool	ChristofMinBias(const edm::Event& event, const edm::EventSetup& eventSetup);
   bool isAtEdge(const RectangularPixelTopology * topology,
                 const SiPixelRecHit & recHit);   
   void multiplicityProperties(const edm::Event& ev, const edm::EventSetup& es, 
                               edm::Handle<CaloTowerCollection> towers,
                               edm::Handle<SiPixelRecHitCollection> siPixelRecCollection,
//                               const reco::VertexCollection* vertices,
                               HepMC::GenEvent * myGenEvent,
                               edm::Handle<reco::TrackCollection>& recCollection,
                               Handle<HcalTrigPrimDigiCollection>& tpg,
                               int desLayer);
   vector<PSimHit> orderPSimHits(vector<PSimHit>);
   void checkEta(const edm::Event& ev, const edm::EventSetup& es,
                 edm::Handle<CaloTowerCollection> towers,
                 edm::Handle<SiPixelRecHitCollection> siPixelRecCollection,
//                 const reco::VertexCollection* vertices,
                 HepMC::GenEvent * myGenEvent);
   void clusterVertices(const edm::Event& ev, const edm::EventSetup& es,
//                        const reco::VertexCollection* vertices,
                        edm::Handle<SiPixelRecHitCollection> siPixelRecCollection);
   void checkSimTracks(const edm::Event& ev, const edm::EventSetup& es,
                        edm::Handle<SiPixelRecHitCollection> siPixelRecCollection);
   float geomAcc(double vert_z, double eta_l, double eta_h, int desLayer);
   float produceClusterVertex(edm::Handle<SiPixelRecHitCollection> siPixelRecCollection);
   int getContainedHits(vector<VertexHit> hits, float z0, float & chi);
   float getVertexZ(edm::Handle<SiPixelRecHitCollection> siPixelRecCollection, const edm::Event& ev);

   const TrackerGeometry* theTracker;
   const SiPixelRecHitCollection* theHits;
   const BeamSpot * theBeamSpot;

   TH1F * hNum_nd; 
   TH1F * hNum_nsd; 
   TH1F * hNum_nsd_trig; 
   TH1F * hNum_sd_trig; 

   TFile * resultFile; 
   TNtuple * verticesInfo;
//   TNtuple * multi;
   TNtuple * looper;
   //multiplicity
   TNtuple * multProp;
   TNtuple * nd_multProp;
   TNtuple * rd_multProp;
   TNtuple * multProp_looper;
   TNtuple * nd_multProp_looper;
   TNtuple * rd_multProp_looper;
   TNtuple * hPabsTof;
   TNtuple * nd_hPabsTof;
   TNtuple * rd_hPabsTof;
   TH1D * hLooperPt;
   TH1D * hPt;
   TH1D * hNonLooperPt;
//   TH1D * hProba;
   TNtuple * hJustLooper;
   TNtuple * nd_hJustLooper;
   TNtuple * rd_hJustLooper;

   //magnetic field
//   TNtuple * nMagField;

   // eta check
   TNtuple * NCheckEta;

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

   //decay
   TNtuple * NDecay;
   TNtuple * nd_NDecay;
   TNtuple * rd_NDecay;
   TNtuple * NDecayInfo;

   // interactions
   TNtuple * NInter;
   TNtuple * nd_NInter;
   TNtuple * rd_NInter;

   // below the cut
   TNtuple * NBelow;
   TNtuple * nd_NBelow;
   TNtuple * rd_NBelow;

   // geo part
   TNtuple * NGeo;
   TNtuple * nd_NGeo;
   TNtuple * rd_NGeo;

   TNtuple * NLooper;
   TNtuple * nd_NLooper;
   TNtuple * rd_NLooper;
   TNtuple * NStrange;
   TNtuple * nd_NStrange;
   TNtuple * rd_NStrange;
   TNtuple * NHitAssoc;

   TH1F * hClusterEta_1_7;
   TH1F * hClusterEta_8_13;
   TH1F * hClusterEta_14_20;
   TH1F * hClusterEta_21_31;
   TH1F * hClusterEta_32_52;
   TH1F * hClusterEta_53_499;

   // testing
   TH1D * hTestEtaFull;
   TH1D * hTestEtaFullV;
   TH1D * hTest_nd;
   TH1D * hTest_nsd;
   TH1D * hTest_nsd_trig;
   TH1D * hTest_sd_trig;
   TH1D * hTest_nd_counter;
   TH1D * hTest_sd_1;
   TH1D * hTest_sd_1_counter;
   TH1D * hTest_sd_2;
   TH1D * hTest_sd_2_counter;
   TH1D * hTest_dd;
   TH1D * hTest_dd_counter;
   TH1D * hTestEtaRestricted_10;
   TH1D * hTestEta_1_8;
   TH1D * hTestEta_9_15;
   TH1D * hTestEta_16_23;
   TH1D * hTestEta_24_36;
   TH1D * hTestEta_37_58;
   TH1D * hTestEta_59_499;
   TH1D * hTestEtaRestricted; 
   TH1D * hTestEtaRestricted_1;
   TH1D * hTestEtaRestrictedV;
   TH1D * hLastTOF;

   int full;
   int fullV;
   int restricted;
   int restrictedV;
   int num_nd;
   int num_nsd;
   int num_nsd_trig;
   int num_sd_trig;
   int num_nd_counter;
   int num_sd_1;
   int num_sd_1_counter;
   int num_sd_2;
   int num_sd_2_counter;
   int num_dd;
   int num_dd_counter;
   int num_10;
   int num_1_8;
   int num_9_15; 
   int num_16_23; 
   int num_24_36; 
   int num_37_58; 
   int num_59_499; 
   // clusters
   int num_cluster_1_7;
   int num_cluster_8_13; 
   int num_cluster_14_20; 
   int num_cluster_21_31; 
   int num_cluster_32_52; 
   int num_cluster_53_499; 

   TH1F * PureCorrEta;
   TH1F * PureCutCorrEta;
   TH1F * DesiredEtaDist;
   TH1F * FeriDesiredEta;
   TH1F * SimRecCorrEta;
   TH1F * RecAdc;
   TH1F * ResCentralAdc;
   TH1F * ResCentralAdcFine;
   TH1F * ResElseCentralAdc;
   TH1F * ResPureAdc;
   TH1F * ResPureAdc_det;
   TH1F * ResPureCentralAdc;
   TH1F * ResPureCutAdc;
   TH1F * ResPureCutCentralAdc;

   TH1F * SimEnergyLoss;
   TH2F * RecAdcvsCorrEta;
   TH2F * SimRecAdcvsCorrEta;
   TH1F * ResSimRecAdc;
   TH1F * ResSimRecAdc_det;
   TH1F * ResSimRecAdcFine;
   TH1F * ResSimRecAdcLog;
   TH1F * FullResSimAdc;
   TH2F * ElseSimRecAdcvsCorrEta;
   TH1F * ResElseSimRecAdc;
   TH1F * ResElseSimRecAdc_det;
   TH2F * PureAdcvsCorrEta;
   TH2F * PureCutAdcvsCorrEta;
   TH2F * hAdcPerCoshCorrEta;

   string trackCollectionLabel, resultFileLabel;
   edm::InputTag src_;
   edm::InputTag vertexColl_;
   bool simulateTriggers_;
   bool hasL1Triggers_;
   bool produceVertexLocally_;

   int nEvents;
   int test;
   int proba;
   int nrv;
};
