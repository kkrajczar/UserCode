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

#include "DataFormats/TrackReco/interface/Track.h"
#include "DataFormats/VertexReco/interface/Vertex.h"
#include "DataFormats/VertexReco/interface/VertexFwd.h"

#include "DataFormats/MuonReco/interface/Muon.h"

#include <fstream>
#include "TROOT.h"
#include "TFile.h"
#include "TNtuple.h"

using namespace std;
using namespace edm;
using namespace reco;

/*****************************************************************************/
class MakeAlignmentNTuple : public edm::EDAnalyzer
{
 public:
   explicit MakeAlignmentNTuple(const edm::ParameterSet& pset);
   ~MakeAlignmentNTuple();
   virtual void beginRun(edm::Run const & run, const edm::EventSetup& es);
   virtual void endJob();
   void getLeptons(const edm::Event& ev,
                   const VertexCollection * recVertices,
                   edm::Handle<edm::View<reco::Track> > recCollection);
   virtual void analyze(const edm::Event& ev, const edm::EventSetup& es);

 private:
   TFile * file_ROOT;
   string fileName_ROOT_;
   TNtuple * nLeptons;
};
