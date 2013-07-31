#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/EventSetup.h"
#include "DataFormats/Common/interface/Handle.h"
#include "FWCore/Framework/interface/ESHandle.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"

#include "SimDataFormats/TrackingAnalysis/interface/TrackingParticle.h"
#include "SimDataFormats/TrackingAnalysis/interface/TrackingParticleFwd.h"

#include "SimTracker/Records/interface/TrackAssociatorRecord.h"
#include "SimTracker/TrackAssociation/interface/TrackAssociatorByHits.h"

#include "DataFormats/TrackReco/interface/Track.h"
#include "DataFormats/VertexReco/interface/Vertex.h"
#include "DataFormats/VertexReco/interface/VertexFwd.h"
#include "DataFormats/BeamSpot/interface/BeamSpot.h"

#include <fstream>
#include "TROOT.h"
#include "TFile.h"
#include "TNtuple.h"

using namespace std;
using namespace edm;
using namespace reco;

#define SQR(x) ((x) * (x))

/*****************************************************************************/
class HighMultAnalyzer : public edm::EDAnalyzer
{
 public:
   explicit HighMultAnalyzer(const edm::ParameterSet& pset);
   ~HighMultAnalyzer();
   virtual void beginRun(edm::Run const & run, const edm::EventSetup& es);
   virtual void endJob();
   bool isPrimary(const TrackingParticleRef & simTrack);
   bool isPrimary(const Track & recTrack, const Vertex & vertex);
   void processSimTracks(const TrackingParticleCollection *tPC, 
                         bool forHeader, 
                         unsigned int & num_simPart);
   void processRecTracks(edm::Handle<edm::View<reco::Track> > recCollection,
                         const VertexCollection * recVertices,
                         bool forHeader,
                         unsigned int & num_recPart,
                         float & ratio_pt,
                         float & angle);
   virtual void analyze(const edm::Event& ev, const edm::EventSetup& es);

 private:
   ofstream file_ASCII;
   string fileName_ASCII_;
   TFile * file_ROOT;
   string fileName_ROOT_;
   TNtuple * nSimTracks;
   TNtuple * nRecTracks;
   TNtuple * nEvent;

   bool hasSIMInfo;
   bool writeASCII;
   unsigned int multiplicityCut;
   unsigned long int numEv;

   edm::Handle<TrackingParticleCollection> simCollection;
   edm::Handle<edm::View<reco::Track> > recCollection;
   edm::Handle<BeamSpot> beamSpotHandle;
   edm::Handle<VertexCollection> recVertexCollection;
   const TrackingParticleCollection *tPC;
   const BeamSpot * theBeamSpot;
   const VertexCollection * recVertices;
   const TrackAssociatorBase * theAssociatorByHits;
   reco::SimToRecoCollection simToReco;
   reco::RecoToSimCollection recoToSim;
};
