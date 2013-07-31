#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/EventSetup.h"
#include "FWCore/Framework/interface/ESHandle.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Utilities/interface/Exception.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"

#include "DataFormats/TrackReco/interface/TrackFwd.h"
#include "DataFormats/TrackReco/interface/Track.h"
#include "DataFormats/VertexReco/interface/Vertex.h"
#include "DataFormats/VertexReco/interface/VertexFwd.h"

#include "DataFormats/SiPixelDetId/interface/PixelSubdetector.h"
#include "DataFormats/SiPixelDetId/interface/PXBDetId.h"
#include "DataFormats/TrackerRecHit2D/interface/SiPixelRecHitCollection.h"
#include "DataFormats/DetId/interface/DetId.h"
#include "DataFormats/SiPixelCluster/interface/SiPixelCluster.h"

#include "Geometry/Records/interface/TrackerDigiGeometryRecord.h"
#include "Geometry/TrackerGeometryBuilder/interface/TrackerGeometry.h"
#include "Geometry/TrackerGeometryBuilder/interface/PixelGeomDetUnit.h"
#include "Geometry/TrackerGeometryBuilder/interface/PixelGeomDetType.h"
#include "Geometry/TrackerGeometryBuilder/interface/RectangularPixelTopology.h"

#include "FWCore/Common/interface/TriggerNames.h"
#include "DataFormats/Common/interface/TriggerResults.h"

#include "DataFormats/L1GlobalTrigger/interface/L1GlobalTriggerReadoutSetupFwd.h"
#include "DataFormats/L1GlobalTrigger/interface/L1GlobalTriggerReadoutSetup.h"
#include "DataFormats/L1GlobalTrigger/interface/L1GlobalTriggerReadoutRecord.h"
#include "DataFormats/L1GlobalTrigger/interface/L1GlobalTriggerRecord.h"
#include "L1Trigger/GlobalTriggerAnalyzer/interface/L1GtUtils.h"
#include "CondFormats/L1TObjects/interface/L1GtTriggerMenu.h"
#include "CondFormats/DataRecord/interface/L1GtTriggerMenuRcd.h"

#include "DataFormats/CaloTowers/interface/CaloTowerCollection.h"
#include "DataFormats/CaloTowers/interface/CaloTower.h"
#include "DataFormats/HcalDigi/interface/HcalDigiCollections.h"
#include "DataFormats/HcalRecHit/interface/HcalRecHitCollections.h"
#include "DataFormats/HcalRecHit/interface/HFRecHit.h"

#include "TROOT.h"
#include "TFile.h"
#include "TNtuple.h"

#include <fstream>
using namespace std;
using namespace reco;
using namespace edm;

/*****************************************************************************/
class SplitAnalyzer : public edm::EDAnalyzer
{
 public:
   explicit SplitAnalyzer(const edm::ParameterSet& pset);
   ~SplitAnalyzer();
   virtual void beginJob();
   virtual void endJob();
   bool aboveTriggerThreshold_3(edm::Handle<CaloTowerCollection> towers);
   virtual void analyze(const edm::Event& ev, const edm::EventSetup& es);

 private:
   TFile * resultFile;

   TNtuple * nTriplets;
   TNtuple * nPairs;
   TNtuple * nDist;

   edm::Handle<edm::View<reco::Track> >    recCollection_triplets;
   edm::Handle<edm::View<reco::Track> >    recCollection_pairs;
   const reco::VertexCollection * vertices;

   int numEv;
   int clusters_1;
   int clusters_2;
   int clusters_3;

   string resultFileLabel;
};

/*****************************************************************************/
SplitAnalyzer::SplitAnalyzer(const edm::ParameterSet& pset)
{
  resultFileLabel = pset.getParameter<string>("file");
}

/*****************************************************************************/
SplitAnalyzer::~SplitAnalyzer()
{
}

/*****************************************************************************/
void SplitAnalyzer::beginJob()
{
  resultFile = new TFile(resultFileLabel.c_str(),"recreate");
  resultFile->cd();

  nTriplets = new TNtuple("nTriplets","nTriplets","eta:pt:size");
  nPairs = new TNtuple("nPairs","nPairs","eta:pt:size");
  nDist = new TNtuple("nDist","nDist","min:layer:eta");

  numEv=0;
//  clusters_1=0;
//  clusters_2=0;
//  clusters_3=0;
}

/*****************************************************************************/
void SplitAnalyzer::endJob()
{
//  std::cerr<<"  events: " << numEv << std::endl;

  resultFile->cd();

//  nTriplets->Write();
//  nPairs->Write();
  nDist->Write();

  std::cerr<< "1 layer clusters: " << clusters_1 << std::endl;
  std::cerr<< "2 layer clusters: " << clusters_2 << std::endl;
  std::cerr<< "3 layer clusters: " << clusters_3 << std::endl;

  resultFile->Close();
}

/*****************************************************************************/
bool SplitAnalyzer::aboveTriggerThreshold_3(edm::Handle<CaloTowerCollection> towers)
{
  int negTowers = 0;
  int posTowers = 0;
  for(CaloTowerCollection::const_iterator cal = towers->begin(); cal != towers->end(); ++cal) {
     for(unsigned int i = 0; i < cal->constituentsSize(); i++) {
        const DetId id = cal->constituent(i);
        if(id.det() == DetId::Hcal) {
          HcalSubdetector subdet=(HcalSubdetector(id.subdetId()));
          if(subdet == HcalForward) {
            if(cal->energy()>3. && cal->eta()<-3.)
              negTowers++;
            if(cal->energy()>3. && cal->eta()>3.)
              posTowers++;
          }
	}
     }
  }
  if(negTowers>2 && posTowers>2)
    return true;

  return false;
}

/*****************************************************************************/
void SplitAnalyzer::analyze
  (const edm::Event& ev, const edm::EventSetup& es)
{
  // get trigger decisions
  bool accept = false;

  bool is_bit36 = false;
  bool is_bit37 = false;
  bool is_bit38 = false;
  bool is_bit39 = false;
  bool is_bit40 = false;
  bool is_bit41 = false;
  bool is_isTrigger_3 = false;

  edm::Handle< L1GlobalTriggerReadoutRecord > gtReadoutRecord;
  ev.getByLabel( edm::InputTag("gtDigis"), gtReadoutRecord);
  const TechnicalTriggerWord&  technicalTriggerWord = gtReadoutRecord->technicalTriggerWord();
  is_bit36 = technicalTriggerWord.at(36);
  is_bit37 = technicalTriggerWord.at(37);
  is_bit38 = technicalTriggerWord.at(38);
  is_bit39 = technicalTriggerWord.at(39);
  is_bit40 = technicalTriggerWord.at(40);
  is_bit41 = technicalTriggerWord.at(41);

  bool is_vtx = false; 
  edm::Handle<reco::VertexCollection> vertexCollection;
  ev.getByLabel("hiSelectedVertex",vertexCollection);
  const reco::VertexCollection * vertices = vertexCollection.product();
  if(vertices->size() > 0)
    is_vtx = true;

  float rver_z = 0.;
  unsigned int vertex_tracks = 0;
  for(reco::VertexCollection::const_iterator
      vertex = vertices->begin(); vertex!= vertices->end(); vertex++)
  {
     if(vertex->tracksSize()>vertex_tracks) {
       vertex_tracks = vertex->tracksSize();
       rver_z = vertex->z();
     }
  }

  edm::Handle<CaloTowerCollection> towers;
  ev.getByLabel("towerMaker",towers);
  is_isTrigger_3 = aboveTriggerThreshold_3(towers);

  // define trigger
//  if(!is_bit36 && !is_bit37 && !is_bit38 && !is_bit39 && is_bit40 && is_vtx)
  if(is_isTrigger_3 && is_vtx)
    accept = true;

if(accept) {

  // Get recHits
  edm::Handle<SiPixelRecHitCollection> siPixelRecCollection;
  ev.getByLabel("siPixelRecHits",siPixelRecCollection);
  const SiPixelRecHitCollection pixelRecHits = *(siPixelRecCollection.product());

  // Get tracker geometry
  const TrackerGeometry* theTracker;
  edm::ESHandle<TrackerGeometry> tracker;
  es.get<TrackerDigiGeometryRecord>().get(tracker);
  theTracker = tracker.product();

  edm::ESHandle<TrackerGeometry> geom;
  es.get<TrackerDigiGeometryRecord>().get(geom);
/*
  //test
  for(SiPixelRecHitCollection::DataContainer::const_iterator IPRH = pixelRecHits.data().begin();
                                                             IPRH != pixelRecHits.data().end();
                                                             ++IPRH) {
     const PixelGeomDetUnit* pgdu = dynamic_cast<const PixelGeomDetUnit*>(geom->idToDetUnit((*IPRH).geographicalId()));

     //barrel
     if(pgdu->subDetector() != GeomDetEnumerators::PixelBarrel)
       continue;

     //layer
     PXBDetId pdetId = PXBDetId(IPRH->geographicalId());
     int layer=pdetId.layer();
     
     //increase
     if(layer==1)
       clusters_1++;
     if(layer==2)
       clusters_2++;
     if(layer==3)
       clusters_3++;
  }
*/

  //real work
  int first = 0;
  for(SiPixelRecHitCollection::DataContainer::const_iterator IPRH_1 = pixelRecHits.data().begin(); 
                                                             IPRH_1 != pixelRecHits.data().end(); 
                                                             ++IPRH_1, first++ ) {

     const PixelGeomDetUnit* pgdu_1 = dynamic_cast<const PixelGeomDetUnit*>(geom->idToDetUnit((*IPRH_1).geographicalId()));
//     const RectangularPixelTopology* topol_1 = dynamic_cast<const RectangularPixelTopology*>(&(pgdu_1->specificTopology()));
     const PixelTopology* topol_1 = &(pgdu_1->specificTopology());

     //barrel
     if(pgdu_1->subDetector() != GeomDetEnumerators::PixelBarrel)
       continue;

     //eta of the cluster
     GlobalPoint globalPosition = pgdu_1->toGlobal((*IPRH_1).localPosition());
     float z = globalPosition.z();
     float R = sqrt(globalPosition.x()*globalPosition.x()+globalPosition.y()*globalPosition.y());
     float eta_corr = -log(tan(atan2(R,(z-rver_z))/2.));

     //layer
     PXBDetId pdetId_1 = PXBDetId(IPRH_1->geographicalId());
     int layer_1=pdetId_1.layer();

     float distance_min = 1000.;

     //pixels
     vector<SiPixelCluster::Pixel> pixels_1 = (*IPRH_1).cluster()->pixels();

     for(vector<SiPixelCluster::Pixel>::const_iterator pixel_1 = pixels_1.begin();
                                                       pixel_1!= pixels_1.end();
                                                       pixel_1++) {

       LocalPoint lp_1 = topol_1->localPosition(MeasurementPoint(pixel_1->x, pixel_1->y));
       GlobalPoint gp_1 =  pgdu_1->surface().toGlobal(Local3DPoint(lp_1.x(),lp_1.y(),lp_1.z()));

       //second loop on clusters
       float second = 0;
       for(SiPixelRecHitCollection::DataContainer::const_iterator IPRH_2 = pixelRecHits.data().begin(); 
                                                                  IPRH_2 != pixelRecHits.data().end(); 
                                                                  ++IPRH_2, second++) {

          const PixelGeomDetUnit* pgdu_2 = dynamic_cast<const PixelGeomDetUnit*>(geom->idToDetUnit((*IPRH_2).geographicalId()));
//          const RectangularPixelTopology* topol_2 = dynamic_cast<const RectangularPixelTopology*>(&(pgdu_2->specificTopology()));
          const PixelTopology* topol_2 = &(pgdu_2->specificTopology());

          //barrel
          if(pgdu_2->subDetector() != GeomDetEnumerators::PixelBarrel)
            continue;

          // no double counting (should be after "barrel")
          if(second<=first)
            continue;

          //layer
          PXBDetId pdetId_2 = PXBDetId(IPRH_2->geographicalId());
          int layer_2=pdetId_2.layer();
          if(layer_2 != layer_1)
            continue;

          //second loop on pixels
          vector<SiPixelCluster::Pixel> pixels_2 = (*IPRH_2).cluster()->pixels();
          for(vector<SiPixelCluster::Pixel>::const_iterator pixel_2 = pixels_2.begin();
                                                            pixel_2!= pixels_2.end();
                                                            pixel_2++) {

            LocalPoint lp_2 = topol_2->localPosition(MeasurementPoint(pixel_2->x, pixel_2->y));
            GlobalPoint gp_2 =  pgdu_2->surface().toGlobal(Local3DPoint(lp_2.x(),lp_2.y(),lp_2.z()));

            float distance = (gp_1-gp_2).mag();
            if(distance < distance_min)
              distance_min = distance;
          }  //pixel_2
       } //cluster_2
     } //pixel_1
     vector<float> result;
     result.push_back(distance_min);
     result.push_back(layer_1);
     result.push_back(eta_corr);
     nDist->Fill(&result[0]);
  } //cluster_1

} //accept
}

DEFINE_FWK_MODULE(SplitAnalyzer);
