#include "MakeAlignmentNTuple.h"

/*****************************************************************************/
MakeAlignmentNTuple::MakeAlignmentNTuple(const edm::ParameterSet& pset)
{
  //inicializations
  fileName_ROOT_ = pset.getParameter<string>("fileName_ROOT");
}

/*****************************************************************************/
MakeAlignmentNTuple::~MakeAlignmentNTuple()
{
}

/*****************************************************************************/
void MakeAlignmentNTuple::beginRun(edm::Run const & run, const edm::EventSetup& es)
{
  file_ROOT = new TFile(fileName_ROOT_.c_str(),"RECREATE","",6);
  TDirectory::TContext context(file_ROOT);

  nLeptons = new TNtuple("nLeptons","nLeptons",
         "run:event:numOfVtx:vtxId:vtxX:vtxY:vtxZ:trackChi2:trackCharge:trackPx:trackPy:trackPz:trackQuality:trackEta:trackPhi");
}

/*****************************************************************************/
void MakeAlignmentNTuple::endJob()
{
  TDirectory::TContext context(file_ROOT);

  nLeptons->Write();

  file_ROOT->Close();
  delete file_ROOT;
}

/*****************************************************************************/
void MakeAlignmentNTuple::getLeptons(const edm::Event& ev,
                                     const VertexCollection * recVertices,
                                     edm::Handle<edm::View<reco::Track> > recCollection_muon)
{
  unsigned int run = ev.id().run();
  unsigned int event = ev.id().event();

  if(recCollection_muon->size()<2)
     return;

  for(View<Track>::size_type i=0; i < recCollection_muon->size(); ++i) {
     RefToBase<Track> track(recCollection_muon, i);

     if(track->pt()<30)
       continue;

     unsigned int quality=0;
     if(track->quality(reco::TrackBase::undefQuality))quality=1;
     if(track->quality(reco::TrackBase::loose))quality=2;
     if(track->quality(reco::TrackBase::tight))quality=3;
     if(track->quality(reco::TrackBase::highPurity))quality=4;

     vector<float> result_leptons;
     result_leptons.push_back(run); //run
     result_leptons.push_back(event); //event
     result_leptons.push_back(recVertices->size()); //numOfVtx
     result_leptons.push_back(-99.); //vtxId
     result_leptons.push_back(-99.); //vtxX
     result_leptons.push_back(-99.); //vtxY
     result_leptons.push_back(-99.); //vtxZ
     result_leptons.push_back(track->normalizedChi2()); //trackChi2
     result_leptons.push_back(track->charge()); //trackCharge
     result_leptons.push_back(track->px()); //trackPx
     result_leptons.push_back(track->py()); //trackPy
     result_leptons.push_back(track->pz()); //trackPz
     result_leptons.push_back(quality); //trackQuality
     result_leptons.push_back(track->eta()); //trackEta
     result_leptons.push_back(track->phi()); //trackPhi
    
     nLeptons->Fill(&result_leptons[0]);
  } 
}

/*****************************************************************************/
void MakeAlignmentNTuple::analyze(
    const edm::Event& ev, const edm::EventSetup& es)
{
  //get rec tracks
  edm::Handle<edm::View<reco::Track> > recCollection_muons;
  ev.getByLabel("tevMuons", "default", recCollection_muons);

  //get rec vertices
   edm::Handle<VertexCollection> recVertexCollection;
//  ev.getByLabel("offlinePrimaryVertices", recVertexCollection);
  ev.getByLabel("offlinePrimaryVerticesWithBS", recVertexCollection);
  const VertexCollection * recVertices;
  recVertices = recVertexCollection.product();

  //process only muons for now
  getLeptons(ev, recVertices, recCollection_muons);
}
