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

#include "TROOT.h"
#include "TFile.h"
#include "TNtuple.h"

#include <fstream>
using namespace std;
using namespace reco;
using namespace edm;

/*****************************************************************************/
class TrackAnalyzer : public edm::EDAnalyzer
{
 public:
   explicit TrackAnalyzer(const edm::ParameterSet& pset);
   ~TrackAnalyzer();
   virtual void beginJob(const edm::EventSetup& es);
   virtual void endJob();
   virtual void analyze(const edm::Event& ev, const edm::EventSetup& es);

 private:
   TFile * resultFile;

   TNtuple * nTriplets;
   TNtuple * nPairs;

   edm::Handle<edm::View<reco::Track> >    recCollection_triplets;
   edm::Handle<edm::View<reco::Track> >    recCollection_pairs;
   const reco::VertexCollection * vertices;

   string resultFileLabel;
};

/*****************************************************************************/
TrackAnalyzer::TrackAnalyzer(const edm::ParameterSet& pset)
{
  resultFileLabel = pset.getParameter<string>("file");
}

/*****************************************************************************/
TrackAnalyzer::~TrackAnalyzer()
{
}

/*****************************************************************************/
void TrackAnalyzer::beginJob(const edm::EventSetup& es)
{
  resultFile = new TFile(resultFileLabel.c_str(),"recreate");
  resultFile->cd();

  nTriplets = new TNtuple("nTriplets","nTriplets","eta:pt:size");
  nPairs = new TNtuple("nPairs","nPairs","eta:pt:size");
}

/*****************************************************************************/
void TrackAnalyzer::endJob()
{
  resultFile->cd();

  nTriplets->Write();
  nPairs->Write();

  resultFile->Close();
}

/*****************************************************************************/
void TrackAnalyzer::analyze
  (const edm::Event& ev, const edm::EventSetup& es)
{
  edm::Handle<reco::VertexCollection> vertexCollection;
  ev.getByLabel("pixel3Vertices",vertexCollection);
  vertices = vertexCollection.product();

  if(vertices->size()==1) {

    ev.getByLabel("pixel3tracks", recCollection_triplets);
    ev.getByLabel("pixel2tracks", recCollection_pairs);

    for(edm::View<reco::Track>::size_type i=0;
            i < recCollection_triplets.product()->size(); ++i)
    {
      vector<float> result_triplets;
      edm::RefToBase<reco::Track> recTrack(recCollection_triplets, i);
      result_triplets.push_back(recTrack->eta());
      result_triplets.push_back(recTrack->pt());
      result_triplets.push_back(1.);
      nTriplets->Fill(&result_triplets[0]);
    }

    for(edm::View<reco::Track>::size_type i=0;
            i < recCollection_pairs.product()->size(); ++i)
    {
      vector<float> result_pairs;
      edm::RefToBase<reco::Track> recTrack(recCollection_pairs, i);
      result_pairs.push_back(recTrack->eta());
      result_pairs.push_back(recTrack->pt());
      result_pairs.push_back(1.);
      nPairs->Fill(&result_pairs[0]);
    }
  }

}

DEFINE_FWK_MODULE(TrackAnalyzer);
