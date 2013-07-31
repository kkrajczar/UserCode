#include "HighMultAnalyzer.h"

/*****************************************************************************/
HighMultAnalyzer::HighMultAnalyzer(const edm::ParameterSet& pset)
{
  //inicializations
  fileName_ASCII_ = pset.getParameter<string>("fileName_ASCII");
  fileName_ROOT_ = pset.getParameter<string>("fileName_ROOT");

  writeASCII = pset.getParameter<bool>("writeASCII");
  hasSIMInfo = pset.getParameter<bool>("hasSIMInfo");
  multiplicityCut = pset.getParameter<int>("multiplicityCut");

  if(writeASCII) {
     file_ASCII.open(fileName_ASCII_.c_str());
     file_ASCII << fixed << setprecision(3);
  }
}

/*****************************************************************************/
HighMultAnalyzer::~HighMultAnalyzer()
{
}

/*****************************************************************************/
void HighMultAnalyzer::beginRun(edm::Run const & run, const edm::EventSetup& es)
{
  file_ROOT = new TFile(fileName_ROOT_.c_str(),"RECREATE","",6);
  TDirectory::TContext context(file_ROOT);

  if(hasSIMInfo) {
    //get associator
    edm::ESHandle<TrackAssociatorBase> associatorByHitsHandle;
    es.get<TrackAssociatorRecord>().get("TrackAssociatorByHits", associatorByHitsHandle);
    theAssociatorByHits =
     (const TrackAssociatorBase*)associatorByHitsHandle.product();

    nSimTracks = new TNtuple("nSimTracks","nSimTracks",
         "pid:eta:pt:phi:reconstructed");
    nRecTracks = new TNtuple("nRecTracks","nRecTracks",
         "eta:pt:phi:nhits:quality:real");
  }
  else {
    nRecTracks = new TNtuple("nRecTracks","nRecTracks",
         "eta:pt:phi:nhits:quality");
  }

  nEvent = new TNtuple("nEvent","nEvent",
         "run:lumi:event:vertices:vertex_z:recTracks:ratio_pt:angle");

  numEv=0;
}

/*****************************************************************************/
void HighMultAnalyzer::endJob()
{
  if(writeASCII)
     file_ASCII.close();

  TDirectory::TContext context(file_ROOT);

  if(hasSIMInfo)
     nSimTracks->Write();
  nRecTracks->Write();
  nEvent->Write();
  file_ROOT->Close();
  delete file_ROOT;

}

/*****************************************************************************/
bool HighMultAnalyzer::isPrimary(const TrackingParticleRef & simTrack)
{
  return (simTrack->status()>=0); //status()<0 -> non-primary
//  return (simTrack->parentVertex()->nSourceTracks() == 0); //old definition
}

/*****************************************************************************/
bool HighMultAnalyzer::isPrimary(const Track & recTrack, const Vertex & vertex)
{
  double dt = fabs(recTrack.dxy(theBeamSpot->position()));
  double st = sqrt(SQR(recTrack.dxyError()) +
                   theBeamSpot->BeamWidthX() *
                   theBeamSpot->BeamWidthY());

  if(dt > min(0.2, 5 * st)) return false;

  double dz = fabs(recTrack.vertex().z() - vertex.position().z());
  double sz = sqrt(SQR(recTrack.dzError()) +
                   SQR(cosh(recTrack.eta())) *
                   theBeamSpot->BeamWidthX() *
                   theBeamSpot->BeamWidthY());

  if(dz > 5 * sz ) return false;

  return true;
}

/*****************************************************************************/
void HighMultAnalyzer::processSimTracks(const TrackingParticleCollection *tPC,
                                        bool forHeader,
                                        unsigned int & num_simPart)

{
  num_simPart = 0;
  for(TrackingParticleCollection::size_type i=0; i < tPC->size(); i++) {

     TrackingParticleRef tpr(simCollection, i);
     TrackingParticle* tp=const_cast<TrackingParticle*>(tpr.get());

     //|eta|>2.5 || charge==0 || pt<0.1 -> continue
     if(fabs(tp->eta())>2.5 || tp->charge()==0 || tp->pt()<0.1) 
       	continue;
     //only primaries
     if(!isPrimary(tpr))
        continue;
  
     num_simPart++;
     if(forHeader)
        continue;

     std::vector<std::pair<RefToBase<Track>, double> > rt;

     if(writeASCII) {
        file_ASCII << " #" << num_simPart << ", pid=" << tp->pdgId()
                   << ", eta=" << tp->eta() << ", pt=" << tp->pt()
                   << ", phi=" << tp->phi();
     }

     if(simToReco.find(tpr) != simToReco.end()) {
        rt = (std::vector<std::pair<RefToBase<Track>, double> >) simToReco[tpr];
        if(rt.size()!=0)
        if(writeASCII)
           file_ASCII << ", reconstructed" << "\n";
     } else {
        if(writeASCII)  
           file_ASCII << ", NOT reconstructed" << "\n";
     }

     vector<float> result_sim;
     result_sim.push_back(tp->pdgId());
     result_sim.push_back(tp->eta());
     result_sim.push_back(tp->pt());
     result_sim.push_back(tp->phi());
     result_sim.push_back(rt.size()!=0);
     nSimTracks->Fill(&result_sim[0]);
  }

  if(writeASCII)  
  if(!forHeader)
     file_ASCII << "\n";
}

/*****************************************************************************/
void HighMultAnalyzer::processRecTracks(edm::Handle<edm::View<reco::Track> > recCollection,
                                        const VertexCollection * recVertices, 
                                        bool forHeader,
                                        unsigned int & num_recPart,
                                        float & ratio_pt,
                                        float & angle)
{
  num_recPart = 0;
  ratio_pt = 0.;
  angle = 0.;

  float pt1 = 0.;
  float pt2 = 0.;
  RefToBase<Track> track_pt1;
  RefToBase<Track> track_pt2;

  for(View<Track>::size_type i=0; i < recCollection->size(); ++i) {
     RefToBase<Track> track(recCollection, i);
     bool rec_primary = false;

     for(VertexCollection::const_iterator vertex = recVertices->begin();
                                          vertex!= recVertices->end();
                                          vertex++) {
        //check vertex compatibility
        if(isPrimary(*track,*vertex))
           rec_primary = true;
     }
     //only primaries
     if(!rec_primary) {
        continue;
     }
/*     
     if(!forHeader) {
        std::cerr<<" track_z: " << track->vertex().z() << std::endl;
        std::cerr<<" track_pt: " << track->pt() << std::endl;
     }
*/
     num_recPart++;
     if(forHeader)
        continue;

     if(writeASCII) {
        file_ASCII << " #" << num_recPart << ", eta=" << track->eta()
                   << ", pt=" << track->pt() << ", phi=" << track->phi()
                   << ", nhits=" << track->numberOfValidHits();
     }

     //quality
     unsigned int quality=0;
     if(track->quality(reco::TrackBase::undefQuality))quality=1;
     if(track->quality(reco::TrackBase::loose))quality=2;
     if(track->quality(reco::TrackBase::tight))quality=3;
     if(track->quality(reco::TrackBase::highPurity))quality=4;

     if(writeASCII) {
        if(quality==1)
           file_ASCII << ", quality=undef(1)";
        else if(quality==2)
           file_ASCII << ", quality=loose(2)";
        else if(quality==3)
           file_ASCII << ", quality=tight(3)";
        else if(quality==4)
           file_ASCII << ", quality=high(4)";
        else
           file_ASCII << "quality=NO_QUALITY(0)";

        if(!hasSIMInfo)
           file_ASCII << "\n";
     }

     std::vector<std::pair<TrackingParticleRef, double> > tp;
     if(hasSIMInfo) {
        if(recoToSim.find(track) != recoToSim.end()) {
           tp = recoToSim[track];
           if(tp.size()!=0) 
           if(writeASCII) {
              file_ASCII << ", real" << "\n";
           }
        } else {
           if(writeASCII)  
              file_ASCII << ", FAKE" << "\n";
        }
     }

     vector<float> result_rec;
     result_rec.push_back(track->eta());
     result_rec.push_back(track->pt());
     result_rec.push_back(track->phi());
     result_rec.push_back(track->numberOfValidHits());
     result_rec.push_back(quality);
     if(hasSIMInfo)
       result_rec.push_back(tp.size()!=0);
     nRecTracks->Fill(&result_rec[0]);

     //select largest pts
     if(pt1 < track->pt()) {
       //if pt1 has already some positive value, pass it over to pt2
       //always works except if the largest pt corresponds to the first track
       //thus, the second if is needed 
       if(pt1>0) {
          pt2 = pt1;
          track_pt2 = track_pt1;
       }
       pt1 = track->pt();
       track_pt1 = track;
     }
     if(((pt2+0.0001) < track->pt()) && ((pt1-0.0001) > track->pt())) { //0.0001: to avoid problems with float
       pt2 = track->pt();
       track_pt2 = track;
     }
  }

  //if we only interested in the number of tracks -> no further action needed
  if(forHeader)
    return;

  //compute angle and pt ratio
  if(pt1!=0. && pt2!=0.) {
     ratio_pt = pt1/pt2;
     angle = TMath::ACos((track_pt1->px()*track_pt2->px() + track_pt1->py()*track_pt2->py())/(pt1*pt2));
  } else {
     ratio_pt = -1000.;
     angle = -1000.;   
  }

  if(writeASCII)  
    file_ASCII << "\n";
}

/*****************************************************************************/
void HighMultAnalyzer::analyze(
    const edm::Event& ev, const edm::EventSetup& es)
{
  vector<float> result_event;

  //get run, LS and event number
  unsigned int run = ev.id().run();
  unsigned int lumi = ev.luminosityBlock();
  unsigned int event = ev.id().event();

  //get rec tracks
  ev.getByLabel("generalTracks", recCollection);

  //get beam spot
  ev.getByLabel("offlineBeamSpot", beamSpotHandle);
  theBeamSpot = beamSpotHandle.product();

  //get rec vertices
//  ev.getByLabel("pixelVertices", recVertexCollection);
//  ev.getByLabel("offlinePrimaryVertices", recVertexCollection);
  ev.getByLabel("offlinePrimaryVerticesWithBS", recVertexCollection);
  recVertices = recVertexCollection.product();

/*
  std::cerr<< "number of recTracks: " << recCollection.product()->size() << std::endl;
  std::cerr<< "number of vertices : " << recVertices->size() << std::endl;
  for(VertexCollection::const_iterator vertex = recVertices->begin();
                                       vertex!= recVertices->end();
                                       vertex++) {
     std::cerr<< " vertex_z: " << vertex->position().z() << std::endl;
  }
*/

  //increase number of processed events and initialize # of rec. tracks
  numEv++;
  unsigned int num_recPart = 0;
  float ratio_pt = 0.;
  float angle = 0.;

  //compute number of rec tracks
  processRecTracks(recCollection,recVertices,true,num_recPart,ratio_pt,angle);

  //multiplicity cut
  if(num_recPart < multiplicityCut)
    return;

  //fill track ntuples
  if(hasSIMInfo) {
     //get sim tracks
     ev.getByLabel("mergedtruth", simCollection);
     tPC = simCollection.product();

     //set up association
     recoToSim = theAssociatorByHits->associateRecoToSim(recCollection, simCollection, &ev);
     simToReco = theAssociatorByHits->associateSimToReco(recCollection, simCollection, &ev);

     //initialize # of rec. tracks
     unsigned int num_simPart = 0;

     //compute number of sim tracks
     processSimTracks(tPC,true,num_simPart);

     if(writeASCII) {
        //event header
        file_ASCII << "\n";
        file_ASCII << "========== " << numEv << ". event in the input file; hasSIMInfo: YES =========" << "\n";
        file_ASCII << "     ------>>>> recTrack cut: " << multiplicityCut << " <<<<------"<< "\n";
        file_ASCII << " # of 'proper' simTracks: " << num_simPart << ",";
        file_ASCII << " # of 'proper' recTracks: " << num_recPart << "\n ";
        file_ASCII << "\n";
     }

     //process sim. tracks
     if(num_simPart>0) {
        if(writeASCII) {
           file_ASCII << " simTracks:" << "\n";
           file_ASCII << " ---------" << "\n";
        }
        processSimTracks(tPC,false,num_simPart);
     }
  } else {
     if(writeASCII) {
        //event header
        file_ASCII << "\n";
        file_ASCII << "========== " << numEv << ". event in the input file; hasSIMInfo: NO =========" << "\n";
        file_ASCII << "     ------>>>> recTrack cut: " << multiplicityCut << " <<<<------"<< "\n";
        file_ASCII << " # of 'proper' recTracks: " << num_recPart << "\n ";
        file_ASCII << "\n";
     }
  }

  //process rec. tracks
  if(num_recPart>0) {
     if(writeASCII) {
       file_ASCII << " recTracks:" << "\n";
       file_ASCII << " ---------" << "\n";
     }
     processRecTracks(recCollection,recVertices,false,num_recPart,ratio_pt,angle);
  }

  //fill event ntuple
  result_event.push_back(run);
  result_event.push_back(lumi);
  result_event.push_back(event);
  result_event.push_back(recVertices->size());
  result_event.push_back((recVertices->begin())->position().z());
  result_event.push_back(num_recPart);
  result_event.push_back(ratio_pt);
  result_event.push_back(angle);
  nEvent->Fill(&result_event[0]);
}
