// $Id: HITriggerAnalyzer.cc,v 1.1 2010/10/29 15:26:06 krajczar Exp $

#include "HITriggerAnalyzer.h"

/*****************************************************************************/
HITriggerAnalyzer::HITriggerAnalyzer(const edm::ParameterSet& pset)
{
  resultFileLabel       = pset.getParameter<string>("file");
  hasL1Triggers_        = pset.getParameter<bool>("hasL1Triggers");
  produceVertexLocally_ = pset.getParameter<bool>("produceVertexLocally");
  src_                  = pset.getParameter<edm::InputTag>("src");
  digis_src_            = pset.getParameter<edm::InputTag>("digis_src");
  vertexColl_           = pset.getParameter<edm::InputTag>("vertexColl");
}

/*****************************************************************************/
HITriggerAnalyzer::~HITriggerAnalyzer()
{
}

/*****************************************************************************/
void HITriggerAnalyzer::beginJob()
{

  // Root
  resultFile = new TFile(resultFileLabel.c_str(),"recreate","",6);
  TDirectory::TContext context(resultFile);

  multProp = new TNtuple("multProp","multProp",
     "B_mc:NPart:NPartSigma:NColl:NCollSigma:NHard:NHardSigma:B:BSigma:rver_z:isTrigger_1:isTrigger_2:trackTrigger:track5Trigger:HLT_ZeroBias:HLT_ZeroBias1kHz:HLT_MinBiasPixel_SingleTrack:HLT_MinBiasBSC_OR:HLT_ZeroBiasPixel_SingleTrack:HLT_L1_BscMinBiasOR_BptxPlusORMinus:HLT_HighMultiplicityBSC:HLT_L1_BSC:HLT_L1_BPTX:HLT_L1_BPTX_MinusOnly:HLT_L1_BPTX_PlusOnly:HLT_MinBiasHcal:HLT_BackwardBSC:HLT_ForwardBSC:hf:bit0:bit3:bit4:bit9:bit34:bit35:bit36:bit37:bit38:bit39:bit40:bit41:bit42:bit43:L1_BptxMinus:L1_BptxPlus:L1_BptxPlusORMinus:L1_BscMinBiasOR_BptxPlusORMinus:numEv:procID");
}

/*****************************************************************************/
void HITriggerAnalyzer::endJob()
{
  TDirectory::TContext context(resultFile);

  multProp->Write();

  resultFile->Close();
  delete resultFile;
}

/*****************************************************************************/
float HITriggerAnalyzer::getVertexZ
     (edm::Handle<SiPixelRecHitCollection> siPixelRecCollection, const edm::Event& ev)
{
  float rver_z = 0.;
  if(!produceVertexLocally_) {
    edm::Handle<reco::VertexCollection> vertexCollection;
    ev.getByLabel(vertexColl_,vertexCollection);
    const reco::VertexCollection * vertices = vertexCollection.product();
    unsigned int vertex_tracks = 0;
    for(reco::VertexCollection::const_iterator
        vertex = vertices->begin(); vertex!= vertices->end(); vertex++)
    {
       if(vertex->tracksSize()>vertex_tracks) {
         vertex_tracks = vertex->tracksSize();
         rver_z = vertex->z();
       }
    }
  } else {
    rver_z = produceClusterVertex(siPixelRecCollection);
  }
  return rver_z;
}

/*****************************************************************************/
int HITriggerAnalyzer::getContainedHits
  (vector<VertexHit> hits, float z0, float & chi)
{
  int n = 0;
  chi = 0.;

  for(vector<VertexHit>::const_iterator hit = hits.begin();
                                        hit!= hits.end(); hit++)
  {
    // Predicted cluster width in y direction
    float p = 2 * fabs(hit->z - z0)/hit->r + 0.5; // check

    if(fabs(p - hit->w) <= 1.)
    {
      chi += fabs(p - hit->w);
      n++;
    }
  }

  return n;
}

/*****************************************************************************/
float HITriggerAnalyzer::produceClusterVertex
     (edm::Handle<SiPixelRecHitCollection> siPixelRecCollection)
{
  const SiPixelRecHitCollection* thePixelHits = siPixelRecCollection.product();

  if(thePixelHits->size() > 0)
  {
    vector<VertexHit> hits;

    for(SiPixelRecHitCollection::DataContainer::const_iterator
           recHit = thePixelHits->data().begin(),
           recHitEnd = thePixelHits->data().end();
           recHit != recHitEnd; ++recHit)
    {
      if(recHit->isValid())
      {
       	DetId id = recHit->geographicalId();
        const PixelGeomDetUnit* pgdu =
          dynamic_cast<const PixelGeomDetUnit*>(theTracker->idToDetUnit(id));
        const RectangularPixelTopology* theTopol =
          dynamic_cast<const RectangularPixelTopology*>( &(pgdu->specificTopology()) );
        vector<SiPixelCluster::Pixel> pixels = recHit->cluster()->pixels();

        bool pixelOnEdge = false;
        for(vector<SiPixelCluster::Pixel>::const_iterator
               pixel = pixels.begin(); pixel!= pixels.end(); pixel++)
        {
          int pos_x = (int)pixel->x;
          int pos_y = (int)pixel->y;

          if(theTopol->isItEdgePixelInX(pos_x) ||
              theTopol->isItEdgePixelInY(pos_y))
          { pixelOnEdge = true; break; }
        }

	if(!pixelOnEdge)
        if(id.subdetId() == int(PixelSubdetector::PixelBarrel))
        {
          PXBDetId pid(id);

          LocalPoint lpos = LocalPoint(recHit->localPosition().x(),
                                       recHit->localPosition().y(),
                                       recHit->localPosition().z());

          GlobalPoint gpos = theTracker->idToDet(id)->toGlobal(lpos);

          VertexHit hit;
          hit.z = gpos.z();
          hit.r = gpos.perp();
          hit.w = recHit->cluster()->sizeY();

          hits.push_back(hit);
        }
      }
    }

    int nhits; int nhits_max = 0;
    float chi; float chi_max = 1e+9;

    float zest = 0;

//    for(float z0 = -15.9; z0 <= 15.95; z0 += 0.1) //2TeV: sigma_z = 5.3
    for(float z0 = -22.2; z0 <= 22.25; z0 += 0.1) //900GeV: sigma_z = 7.4
    {
      nhits = getContainedHits(hits, z0, chi);

      if(nhits > 0)
      {
       	if(nhits >  nhits_max)
        { chi_max = 1e+9; nhits_max = nhits; }

        if(nhits >= nhits_max)
        if(chi < chi_max)
        { chi_max = chi; zest = z0; }
      }
    }
    return zest;
  }
  else {
    return 0.;
  }
}

/*****************************************************************************/
bool HITriggerAnalyzer::aboveTriggerThreshold_1(edm::Handle<CaloTowerCollection> towers)
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
  if(negTowers>0 && posTowers>0)
    return true;

  return false;
}

/*****************************************************************************/
bool HITriggerAnalyzer::aboveTriggerThreshold_2(edm::Handle<CaloTowerCollection> towers)
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
  if(negTowers>1 && posTowers>1)
    return true;

  return false;
}

/*****************************************************************************/
bool HITriggerAnalyzer::trackTrigger(edm::Handle<reco::TrackCollection>& recCollection)
{
  int tracks = recCollection.product()->size();
  if(tracks>0)
    return true;
  else
    return false;
}

/*****************************************************************************/
bool HITriggerAnalyzer::ChristofMinBias(const edm::Event& event, const edm::EventSetup& eventSetup)
{
  edm::Handle<HFRecHitCollection> collection;
  event.getByLabel("hfreco",collection);

  edm::ESHandle<CaloGeometry> geom;
  eventSetup.get<CaloGeometryRecord>().get(geom);

  bool pos_eta = false;
  bool neg_eta = false;
  for(std::vector<HFRecHit>::const_iterator it=collection->begin(), itEnd=collection->end(); it!=itEnd; ++it) {
     const CaloCellGeometry *cell = (*geom).getGeometry ((*it).detid());
     const GlobalPoint& pos = cell->getPosition();
     float eta = pos.eta();
     float energy = (*it).energy();

     //trigger criterion
     if(energy>3. && eta<0.)
       neg_eta = true;     
     if(energy>3. && eta>0.)
       pos_eta = true;     
  }

  if(neg_eta && pos_eta)
    return true;

  return false;
}

/*****************************************************************************/
void HITriggerAnalyzer::onTriggers
   (const edm::Event& ev, const edm::EventSetup& es, edm::Handle<CaloTowerCollection> towers,
    edm::Handle<SiPixelRecHitCollection> siPixelRecCollection,
    HepMC::GenEvent * myGenEvent,
    edm::Handle<reco::TrackCollection>& recCollection,
    Handle<HcalTrigPrimDigiCollection>& tpg,
    edm::Handle<reco::Centrality> cent,
    const HepMC::HeavyIon * hi_mc)
{
  vector<float> result;

  //centrality
  double bMean_mc = hi_mc->impact_parameter();

  double hf = cent->EtHFhitSum();

  double npartMean = theCentBins->NpartMean(hf);
  double npartSigma = theCentBins->NpartSigma(hf);
  double ncollMean = theCentBins->NcollMean(hf);
  double ncollSigma = theCentBins->NcollSigma(hf);
  double nhardMean = theCentBins->NhardMean(hf);
  double nhardSigma = theCentBins->NhardSigma(hf);
  double bMean = theCentBins->bMean(hf);
  double bSigma = theCentBins->bSigma(hf);

  result.push_back(bMean_mc); //B_mc
  result.push_back(npartMean); //NPart
  result.push_back(npartSigma);//NPartSigma
  result.push_back(ncollMean); //NColl
  result.push_back(ncollSigma);//NCollSigma
  result.push_back(nhardMean); //NHard
  result.push_back(nhardSigma);//NHardSigma
  result.push_back(bMean);     //B
  result.push_back(bSigma);    //BSigma

  // Triggers
  edm::Handle<edm::TriggerResults> triggerResults;
  ev.getByType(triggerResults);

  const edm::TriggerNames & triggerNames = ev.triggerNames(*triggerResults);

  bool is_HLT_ZeroBias = false;
  bool is_HLT_ZeroBias1kHz = false;
  bool is_HLT_MinBiasPixel_SingleTrack = false;
  bool is_HLT_MinBiasBSC_OR = false;
  bool is_HLT_ZeroBiasPixel_SingleTrack = false;
  bool is_HLT_L1_BscMinBiasOR_BptxPlusORMinus = false;
  bool is_HLT_HighMultiplicityBSC = false;
  bool is_HLT_L1_BSC = false;
  bool is_HLT_L1_BPTX = false;
  bool is_HLT_L1_BPTX_MinusOnly = false;
  bool is_HLT_L1_BPTX_PlusOnly = false;
  bool is_HLT_MinBiasHcal = false;
  bool is_HLT_BackwardBSC = false;
  bool is_HLT_ForwardBSC = false;

  bool is_bit0 = false;
  bool is_bit3 = false;
  bool is_bit4 = false;
  bool is_bit9 = false;
  bool is_bit34 = false;
  bool is_bit35 = false;
  bool is_bit36 = false;
  bool is_bit37 = false;
  bool is_bit38 = false;
  bool is_bit39 = false;
  bool is_bit40 = false;
  bool is_bit41 = false;
  bool is_bit42 = false;
  bool is_bit43 = false;

  bool is_L1_BptxMinus = false;
  bool is_L1_BptxPlus = false;
  bool is_L1_BptxPlusORMinus = false;
  bool is_L1_BscMinBiasOR_BptxPlusORMinus = false;

  if(triggerResults.product()->wasrun())
  if(triggerResults.product()->accept())
  for(unsigned int itrig = 0; itrig < triggerResults.product()->size(); ++itrig) {
    if(triggerResults.product()->accept(itrig))
    {
      if(strcmp(triggerNames.triggerName(itrig).c_str(),"HLT_ZeroBias") == 0)
        is_HLT_ZeroBias = true;
      if(strcmp(triggerNames.triggerName(itrig).c_str(),"HLT_ZeroBias1kHz") == 0)
        is_HLT_ZeroBias1kHz = true;
      if(strcmp(triggerNames.triggerName(itrig).c_str(),"HLT_MinBiasPixel_SingleTrack") == 0)
        is_HLT_MinBiasPixel_SingleTrack = true;
      if(strcmp(triggerNames.triggerName(itrig).c_str(),"HLT_MinBiasBSC_OR") == 0)
        is_HLT_MinBiasBSC_OR = true;
      if(strcmp(triggerNames.triggerName(itrig).c_str(),"HLT_ZeroBiasPixel_SingleTrack") == 0)
        is_HLT_ZeroBiasPixel_SingleTrack = true;
      if(strcmp(triggerNames.triggerName(itrig).c_str(),"HLT_L1_BscMinBiasOR_BptxPlusORMinus") == 0)
        is_HLT_L1_BscMinBiasOR_BptxPlusORMinus = true;
      if(strcmp(triggerNames.triggerName(itrig).c_str(),"HLT_HighMultiplicityBSC") == 0)
        is_HLT_HighMultiplicityBSC = true;
      if(strcmp(triggerNames.triggerName(itrig).c_str(),"HLT_L1_BSC") == 0)
        is_HLT_L1_BSC = true;
      if(strcmp(triggerNames.triggerName(itrig).c_str(),"HLT_L1_BPTX") == 0)
        is_HLT_L1_BPTX = true;
      if(strcmp(triggerNames.triggerName(itrig).c_str(),"HLT_L1_BPTX_MinusOnly") == 0)
        is_HLT_L1_BPTX_MinusOnly = true;
      if(strcmp(triggerNames.triggerName(itrig).c_str(),"HLT_L1_BPTX_PlusOnly") == 0)
        is_HLT_L1_BPTX_PlusOnly = true;
      if(strcmp(triggerNames.triggerName(itrig).c_str(),"HLT_MinBiasHcal") == 0)
        is_HLT_MinBiasHcal = true;
      if(strcmp(triggerNames.triggerName(itrig).c_str(),"HLT_BackwardBSC") == 0)
        is_HLT_BackwardBSC = true;
      if(strcmp(triggerNames.triggerName(itrig).c_str(),"HLT_ForwardBSC") == 0)
        is_HLT_ForwardBSC = true;
    }
  }

  if(hasL1Triggers_) {
    edm::Handle< L1GlobalTriggerReadoutRecord > gtReadoutRecord;
    ev.getByLabel( edm::InputTag("gtDigis"), gtReadoutRecord);
    const TechnicalTriggerWord&  technicalTriggerWord = gtReadoutRecord->technicalTriggerWord();
    is_bit0 = technicalTriggerWord.at(0);
    is_bit3 = technicalTriggerWord.at(3);
    is_bit4 = technicalTriggerWord.at(4);
    is_bit9 = technicalTriggerWord.at(9);
    is_bit34 = technicalTriggerWord.at(34);
    is_bit35 = technicalTriggerWord.at(35);
    is_bit36 = technicalTriggerWord.at(36);
    is_bit37 = technicalTriggerWord.at(37);
    is_bit38 = technicalTriggerWord.at(38);
    is_bit39 = technicalTriggerWord.at(39);
    is_bit40 = technicalTriggerWord.at(40);
    is_bit41 = technicalTriggerWord.at(41);
    is_bit42 = technicalTriggerWord.at(42);
    is_bit43 = technicalTriggerWord.at(43);

    edm::ESHandle<L1GtTriggerMenu> menuRcd;
    es.get<L1GtTriggerMenuRcd>().get(menuRcd) ;
    const L1GtTriggerMenu* menu = menuRcd.product();

    const DecisionWord& gtDecisionWordBeforeMask = gtReadoutRecord->decisionWord();
    is_L1_BptxMinus = menu->gtAlgorithmResult( "L1_BptxMinus", gtDecisionWordBeforeMask);
    is_L1_BptxPlus = menu->gtAlgorithmResult( "L1_BptxPlus", gtDecisionWordBeforeMask);
    is_L1_BptxPlusORMinus = menu->gtAlgorithmResult( "L1_BptxPlusORMinus", gtDecisionWordBeforeMask);
    is_L1_BscMinBiasOR_BptxPlusORMinus = menu->gtAlgorithmResult( "L1_BscMinBiasOR_BptxPlusORMinus", gtDecisionWordBeforeMask);
  }

  // Get simulated
  edm::Handle<TrackingParticleCollection> simCollection;
//  ev.getByType(simCollection);
  ev.getByLabel("mergedtruth","MergedTrackTruth",simCollection);

  // get vertex_z
  double rver_z = (double)getVertexZ(siPixelRecCollection, ev);

  result.push_back(rver_z); //rver_z

  if(aboveTriggerThreshold_1(towers)) {
    result.push_back(1);  //isTrigger_1
  } else {
    result.push_back(0);  //isTrigger_1
  }
  if(aboveTriggerThreshold_2(towers)) {
    result.push_back(1);  //isTrigger_2
  } else {
    result.push_back(0);  //isTrigger_2
  }
  result.push_back(0);  //trackTrigger
  if(is_HLT_ZeroBias) {
    result.push_back(1);//HLT_ZeroBias
  } else {
    result.push_back(0);//HLT_ZeroBias
  }
  if(is_HLT_ZeroBias1kHz) {
    result.push_back(1);//HLT_ZeroBias1kHz
  } else {
    result.push_back(0);//HLT_ZeroBias1kHz
  }
  if(is_HLT_MinBiasPixel_SingleTrack) {
   result.push_back(1);//HLT_MinBiasPixel_Single
  } else {
  result.push_back(0);//HLT_MinBiasPixel_Single
  }
  if(is_HLT_MinBiasBSC_OR ) {
    result.push_back(1);//HLT_MinBiasBSC_OR 
  } else {
    result.push_back(0);//HLT_MinBiasBSC_OR 
  }
  if(is_HLT_ZeroBiasPixel_SingleTrack) {
    result.push_back(1);//HLT_ZeroBiasPixel_SingleTrack
  } else {
    result.push_back(0);//HLT_ZeroBiasPixel_SingleTrack
  }
  if(is_HLT_L1_BscMinBiasOR_BptxPlusORMinus) {
    result.push_back(1);//HLT_L1_BscMinBiasOR_BptxPlusORMinus
  } else {
    result.push_back(0);//HLT_L1_BscMinBiasOR_BptxPlusORMinus
  }
  if(is_HLT_HighMultiplicityBSC) {
    result.push_back(1);//HLT_HighMultiplicityBSC
  } else {
    result.push_back(0);//HLT_HighMultiplicityBSC
  }
  if(is_HLT_L1_BSC) {
    result.push_back(1);//HLT_L1_BSC
  } else {
    result.push_back(0);//HLT_L1_BSC
  }
  if(is_HLT_L1_BPTX) {
    result.push_back(1);//HLT_L1_BPTX
  } else {
    result.push_back(0);//HLT_L1_BPTX
  }
  if(is_HLT_L1_BPTX_MinusOnly) {
     result.push_back(1);//HLT_L1_BPTX_MinusOnly
  } else {
    result.push_back(0);//HLT_L1_BPTX_MinusOnly
  }
  if(is_HLT_L1_BPTX_PlusOnly) {
    result.push_back(1);//HLT_L1_BPTX_PlusOnly
  } else {
    result.push_back(0);//HLT_L1_BPTX_PlusOnly
  }
  if(is_HLT_MinBiasHcal) {
    result.push_back(1);//HLT_MinBiasHcal
  } else {
    result.push_back(0);//HLT_MinBiasHcal
  }
  if(is_HLT_BackwardBSC) {
    result.push_back(1);//HLT_BackwardBSC
  } else {
    result.push_back(0);//HLT_BackwardBSC
  }
  if(is_HLT_ForwardBSC) {
    result.push_back(1);//HLT_ForwardBSC
  } else {
    result.push_back(0);//HLT_ForwardBSC
  }
  if(ChristofMinBias(ev,es)) {
    result.push_back(1);//hf
  } else {
    result.push_back(0);//hf
  }

  result.push_back(is_bit0);
  result.push_back(is_bit3);
  result.push_back(is_bit4);
  result.push_back(is_bit9);
  result.push_back(is_bit34);
  result.push_back(is_bit35);
  result.push_back(is_bit36);
  result.push_back(is_bit37);
  result.push_back(is_bit38);
  result.push_back(is_bit39);
  result.push_back(is_bit40);
  result.push_back(is_bit41);
  result.push_back(is_bit42);
  result.push_back(is_bit43);

  result.push_back(is_L1_BptxMinus);
  result.push_back(is_L1_BptxPlus);
  result.push_back(is_L1_BptxPlusORMinus);
  result.push_back(is_L1_BscMinBiasOR_BptxPlusORMinus);

  result.push_back(1);    //numEv
  int procID = myGenEvent->signal_process_id();
  result.push_back(procID);  //process ID

  multProp->Fill(&result[0]);
}

/*****************************************************************************/
void HITriggerAnalyzer::analyze
  (const edm::Event& ev, const edm::EventSetup& es)
{
//  std::cerr<<"[HITriggerAnalyzer] started" << std::endl;

  // Get HI MC
  Handle<HepMCProduct> mcp;
  ev.getByType(mcp);
  const HepMC::GenEvent * mc = mcp->GetEvent();
  const HepMC::HeavyIon * hi_mc = mc->heavy_ion();  

  theCentBins = getCentralityBinsFromDB(es);
  edm::Handle<reco::Centrality> cent;
  ev.getByLabel(edm::InputTag("hiCentrality"),cent);

  // Get tracker geometry
  edm::ESHandle<TrackerGeometry> tracker;
  es.get<TrackerDigiGeometryRecord>().get(tracker);
  theTracker = tracker.product();

  // Beam spot
  edm::Handle<BeamSpot>      beamSpotHandle;
  ev.getByLabel("offlineBeamSpot", beamSpotHandle);
  theBeamSpot = beamSpotHandle.product();

  // Get simulated
  edm::Handle<vector<PSimHit> > simHits;
  ev.getByLabel("g4SimHits","TrackerHitsPixelBarrelLowTof", simHits);

  // Get reconstructed
    //tracks -only if triggers are simulated (track triggers, etc.)-
  edm::Handle<reco::TrackCollection>  recCollection;
  ev.getByLabel("hltPixelTracksForMinBias", recCollection);
//  ev.getByLabel(trackCollectionLabel, recCollection);

    //calorimeter
    //Richard
  Handle<HcalTrigPrimDigiCollection> tpg;
  ev.getByLabel("hcalDigis",tpg);

  edm::Handle<CaloTowerCollection> towers; 
  ev.getByLabel("towerMaker",towers);

  // Get siPixelRecHits
  edm::Handle<SiPixelRecHitCollection> siPixelRecCollection;
  ev.getByLabel(src_,siPixelRecCollection);

  //MC
  Handle<HepMCProduct> evt;
  ev.getByType(evt);
//  ev.getByLabel("source",evt); //give strange procID number: 1,4,5,6,7
//  ev.getByLabel("generator",evt); /give strange procID number: 1,4,5,6,7
  HepMC::GenEvent * myGenEvent = new  HepMC::GenEvent(*(evt->GetEvent()));

  onTriggers(ev, es, towers, siPixelRecCollection, myGenEvent, recCollection, tpg, cent, hi_mc);
}
