// $Id: ChargedMultiplicityAnalyzerNoSimInfo_new.cc,v 1.36 2010/10/29 15:21:22 krajczar Exp $

#include "ChargedMultiplicityAnalyzerNoSimInfo_new.h"

/*****************************************************************************/
ChargedMultiplicityAnalyzerNoSimInfo_new::ChargedMultiplicityAnalyzerNoSimInfo_new(const edm::ParameterSet& pset)
{
  resultFileLabel       = pset.getParameter<string>("file");
  simulateTriggers_     = pset.getParameter<bool>("simulateTriggers");
  hasL1Triggers_        = pset.getParameter<bool>("hasL1Triggers");
  produceVertexLocally_ = pset.getParameter<bool>("produceVertexLocally");
  src_                  = pset.getParameter<edm::InputTag>("src");
  vertexColl_           = pset.getParameter<edm::InputTag>("vertexColl");
}

/*****************************************************************************/
ChargedMultiplicityAnalyzerNoSimInfo_new::~ChargedMultiplicityAnalyzerNoSimInfo_new()
{
}

/*****************************************************************************/
//void ChargedMultiplicityAnalyzerNoSimInfo_new::beginJob(const edm::EventSetup& es)
void ChargedMultiplicityAnalyzerNoSimInfo_new::beginJob()
{
  // file
  resultFile = new TFile(resultFileLabel.c_str(),"recreate","",6);
  TDirectory::TContext context(resultFile);

  // ntuples
  multProp = new TNtuple("multProp","multProp",
     "clusters:clusters_on_layers:rver_z:failedSizeP5:failedSizeP4:failedSizeP3:failedSizeP2:failedSizeP1:failedSizeN1:failedSizeN2:failedSizeN3:failedSizeN4:failedSizeN5:M:isTrigger_1:isTrigger_2:trackTrigger:track5Trigger:HLT_ZeroBias:HLT_ZeroBias1kHz:HLT_MinBiasPixel_SingleTrack:HLT_MinBiasBSC_OR:HLT_ZeroBiasPixel_SingleTrack:HLT_L1_BscMinBiasOR_BptxPlusORMinus:HLT_HighMultiplicityBSC:HLT_L1_BSC:HLT_L1_BPTX:HLT_L1_BPTX_MinusOnly:HLT_L1_BPTX_PlusOnly:HLT_MinBiasHcal:HLT_BackwardBSC:HLT_ForwardBSC:hf:bit0:bit3:bit4:bit9:bit34:bit35:bit36:bit37:bit38:bit39:bit40:bit41:bit42:bit43:L1_BptxMinus:L1_BptxPlus:L1_BptxPlusORMinus:L1_BscMinBiasOR_BptxPlusORMinus:numEv:H_recMC_etaP5:H_recMC_etaP4:H_recMC_etaP3:H_recMC_etaP2:H_recMC_etaP1:H_recMC_etaN1:H_recMC_etaN2:H_recMC_etaN3:H_recMC_etaN4:H_recMC_etaN5:clustSizeY_etaP6:clustSizeY_etaP5:clustSizeY_etaP4:clustSizeY_etaP3:clustSizeY_etaP2:clustSizeY_etaP1:clustSizeY_etaN1:clustSizeY_etaN2:clustSizeY_etaN3:clustSizeY_etaN4:clustSizeY_etaN5:clustSizeY_etaN6:cluster_counter");
  nd_multProp = new TNtuple("nd_multProp","nd_multProp",
     "clusters:clusters_on_layers:rver_z:failedSizeP5:failedSizeP4:failedSizeP3:failedSizeP2:failedSizeP1:failedSizeN1:failedSizeN2:failedSizeN3:failedSizeN4:failedSizeN5:M:isTrigger_1:isTrigger_2:trackTrigger:track5Trigger:HLT_ZeroBias:HLT_ZeroBias1kHz:HLT_MinBiasPixel_SingleTrack:HLT_MinBiasBSC_OR:HLT_ZeroBiasPixel_SingleTrack:HLT_L1_BscMinBiasOR_BptxPlusORMinus:HLT_HighMultiplicityBSC:HLT_L1_BSC:HLT_L1_BPTX:HLT_L1_BPTX_MinusOnly:HLT_L1_BPTX_PlusOnly:HLT_MinBiasHcal:HLT_BackwardBSC:HLT_ForwardBSC:hf:bit0:bit3:bit4:bit9:bit34:bit35:bit36:bit37:bit38:bit39:bit40:bit41:bit42:bit43:L1_BptxMinus:L1_BptxPlus:L1_BptxPlusORMinus:L1_BscMinBiasOR_BptxPlusORMinus:numEv:H_recMC_etaP5:H_recMC_etaP4:H_recMC_etaP3:H_recMC_etaP2:H_recMC_etaP1:H_recMC_etaN1:H_recMC_etaN2:H_recMC_etaN3:H_recMC_etaN4:H_recMC_etaN5:clustSizeY_etaP6:clustSizeY_etaP5:clustSizeY_etaP4:clustSizeY_etaP3:clustSizeY_etaP2:clustSizeY_etaP1:clustSizeY_etaN1:clustSizeY_etaN2:clustSizeY_etaN3:clustSizeY_etaN4:clustSizeY_etaN5:clustSizeY_etaN6:cluster_counter");
  rd_multProp = new TNtuple("rd_multProp","rd_multProp",
     "clusters:clusters_on_layers:rver_z:failedSizeP5:failedSizeP4:failedSizeP3:failedSizeP2:failedSizeP1:failedSizeN1:failedSizeN2:failedSizeN3:failedSizeN4:failedSizeN5:M:isTrigger_1:isTrigger_2:trackTrigger:track5Trigger:HLT_ZeroBias:HLT_ZeroBias1kHz:HLT_MinBiasPixel_SingleTrack:HLT_MinBiasBSC_OR:HLT_ZeroBiasPixel_SingleTrack:HLT_L1_BscMinBiasOR_BptxPlusORMinus:HLT_HighMultiplicityBSC:HLT_L1_BSC:HLT_L1_BPTX:HLT_L1_BPTX_MinusOnly:HLT_L1_BPTX_PlusOnly:HLT_MinBiasHcal:HLT_BackwardBSC:HLT_ForwardBSC:hf:bit0:bit3:bit4:bit9:bit34:bit35:bit36:bit37:bit38:bit39:bit40:bit41:bit42:bit43:L1_BptxMinus:L1_BptxPlus:L1_BptxPlusORMinus:L1_BscMinBiasOR_BptxPlusORMinus:numEv:H_recMC_etaP5:H_recMC_etaP4:H_recMC_etaP3:H_recMC_etaP2:H_recMC_etaP1:H_recMC_etaN1:H_recMC_etaN2:H_recMC_etaN3:H_recMC_etaN4:H_recMC_etaN5:clustSizeY_etaP6:clustSizeY_etaP5:clustSizeY_etaP4:clustSizeY_etaP3:clustSizeY_etaP2:clustSizeY_etaP1:clustSizeY_etaN1:clustSizeY_etaN2:clustSizeY_etaN3:clustSizeY_etaN4:clustSizeY_etaN5:clustSizeY_etaN6:cluster_counter");
  multProp_looper = new TNtuple("multProp_looper","multProp_looper",
      "isTrigger_1:isTrigger_2:rver_z:eta:eta_det:phi:eloss:M:clustSizeY:clustSizeX:length:pixels:cluster_counter:HLT_ZeroBias:HLT_ZeroBias1kHz:HLT_MinBiasPixel_SingleTrack:HLT_MinBiasBSC_OR:HLT_ZeroBiasPixel_SingleTrack:HLT_L1_BscMinBiasOR_BptxPlusORMinus:HLT_HighMultiplicityBSC:HLT_L1_BSC:HLT_L1_BPTX:HLT_L1_BPTX_MinusOnly:HLT_L1_BPTX_PlusOnly:HLT_MinBiasHcal:HLT_BackwardBSC:HLT_ForwardBSC:bit0:bit3:bit4:bit9:bit34:bit35:bit36:bit37:bit38:bit39:bit40:bit41:bit42:bit43:L1_BptxMinus:L1_BptxPlus:L1_BptxPlusORMinus:L1_BscMinBiasOR_BptxPlusORMinus:hf");
  nd_multProp_looper = new TNtuple("nd_multProp_looper","nd_multProp_looper",
      "isTrigger_1:isTrigger_2:rver_z:eta:eta_det:phi:eloss:M:clustSizeY:clustSizeX:length:pixels:cluster_counter:HLT_ZeroBias:HLT_ZeroBias1kHz:HLT_MinBiasPixel_SingleTrack:HLT_MinBiasBSC_OR:HLT_ZeroBiasPixel_SingleTrack:HLT_L1_BscMinBiasOR_BptxPlusORMinus:HLT_HighMultiplicityBSC:HLT_L1_BSC:HLT_L1_BPTX:HLT_L1_BPTX_MinusOnly:HLT_L1_BPTX_PlusOnly:HLT_MinBiasHcal:HLT_BackwardBSC:HLT_ForwardBSC:bit0:bit3:bit4:bit9:bit34:bit35:bit36:bit37:bit38:bit39:bit40:bit41:bit42:bit43:L1_BptxMinus:L1_BptxPlus:L1_BptxPlusORMinus:L1_BscMinBiasOR_BptxPlusORMinus:hf");
  rd_multProp_looper = new TNtuple("rd_multProp_looper","rd_multProp_looper",
      "isTrigger_1:isTrigger_2:rver_z:eta:eta_det:phi:eloss:M:clustSizeY:clustSizeX:length:pixels:cluster_counter:HLT_ZeroBias:HLT_ZeroBias1kHz:HLT_MinBiasPixel_SingleTrack:HLT_MinBiasBSC_OR:HLT_ZeroBiasPixel_SingleTrack:HLT_L1_BscMinBiasOR_BptxPlusORMinus:HLT_HighMultiplicityBSC:HLT_L1_BSC:HLT_L1_BPTX:HLT_L1_BPTX_MinusOnly:HLT_L1_BPTX_PlusOnly:HLT_MinBiasHcal:HLT_BackwardBSC:HLT_ForwardBSC:bit0:bit3:bit4:bit9:bit34:bit35:bit36:bit37:bit38:bit39:bit40:bit41:bit42:bit43:L1_BptxMinus:L1_BptxPlus:L1_BptxPlusORMinus:L1_BscMinBiasOR_BptxPlusORMinus:hf");
  nCLusterVertices = new TNtuple("nCLusterVertices","nCLusterVertices","numRecHits_l1:rver_z");

  // histograms
  PureCorrEta = new TH1F("PureCorrEta","PureCorrEta",30,-3.,3.);
  PureCutCorrEta = new TH1F("PureCutCorrEta","PureCutCorrEta",30,-3.,3.);
  ResPureAdc = new TH1F("ResPureAdc","ResPureAdc",50,0.,2550.);
  ResPureAdc_det = new TH1F("ResPureAdc_det","ResPureAdc_det",50,0.,2550.);
  ResPureCentralAdc = new TH1F("ResPureCentralAdc","ResPureCentralAdc",50,0.,2550.);
  ResPureCutAdc = new TH1F("ResPureCutAdc","ResPureCutAdc",50,0.,2550.);
  ResPureCutCentralAdc = new TH1F("ResPureCutCentralAdc","ResPureCutCentralAdc",50,0.,2550.);

  hCorrEtaSizeY = new TH2F("hCorrEtaSizeY","hCorrEtaSizeY",300,-3.,3.,20,0.,20.);
  hCorrEtaADC = new TH2F("hCorrEtaADC","hCorrEtaADC",300,-3.,3.,125,0.,2500.);
  hClusterZSizeY = new TH2F("hClusterZSizeY","hClusterZSizeY",600,-30.,30.,200,0.,20.);
  PureAdcvsCorrEta = new TH2F("PureAdcvsCorrEta","PureAdcvsCorrEta",300,-3.,3.,2550,0.,2550.);
  PureCutAdcvsCorrEta = new TH2F("PureCutAdcvsCorrEta","PureCutAdcvsCorrEta",300,-3.,3.,25000,0.,2550.);

}

/*****************************************************************************/
void ChargedMultiplicityAnalyzerNoSimInfo_new::endJob()
{
  TDirectory::TContext context(resultFile);

  // ntuples
  multProp->Write();
  nd_multProp->Write();
  rd_multProp->Write();
  multProp_looper->Write();
  nd_multProp_looper->Write();
  rd_multProp_looper->Write();
  nCLusterVertices->Write();

  // histograms
  hCorrEtaSizeY->Write();
  hCorrEtaADC->Write();
  hClusterZSizeY->Write();
  PureCorrEta->Write();
  PureCutCorrEta->Write();
  ResPureAdc->Write();
  ResPureAdc_det->Write();
  ResPureCentralAdc->Write();
  ResPureCutAdc->Write();
  ResPureCutCentralAdc->Write();
  PureAdcvsCorrEta->Write();
  PureCutAdcvsCorrEta->Write();

  resultFile->Close();
  delete resultFile;
}

/*****************************************************************************/
float ChargedMultiplicityAnalyzerNoSimInfo_new::getVertexZ
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
//    if(rver_z!=0)
//      std::cerr<<" vertex found: " << vertices->size() << std::endl;

  } else {
    rver_z = produceClusterVertex(siPixelRecCollection);
  }
  return rver_z;
}

/*****************************************************************************/
int ChargedMultiplicityAnalyzerNoSimInfo_new::getContainedHits
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
float ChargedMultiplicityAnalyzerNoSimInfo_new::produceClusterVertex
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
void ChargedMultiplicityAnalyzerNoSimInfo_new::clusterVertices
    (const edm::Event& ev, const edm::EventSetup& es,
//     const reco::VertexCollection* vertices,
     edm::Handle<SiPixelRecHitCollection> siPixelRecCollection)
{
  // get vertex_z
  float rver_z = getVertexZ(siPixelRecCollection, ev);

  int numRecHits_1l = 0;
  edm::ESHandle<TrackerGeometry> geom;
  es.get<TrackerDigiGeometryRecord>().get(geom);
  const SiPixelRecHitCollection pixelRecHits = *(siPixelRecCollection.product());
  for(SiPixelRecHitCollection::DataContainer::const_iterator iPRH = pixelRecHits.data().begin(); iPRH != pixelRecHits.data().end(); ++iPRH) {
      const PixelGeomDetUnit* pgdu = dynamic_cast<const PixelGeomDetUnit*>(geom->idToDetUnit(iPRH->geographicalId()));
      PXBDetId pdetId = PXBDetId(iPRH->geographicalId());
      int layer=pdetId.layer();
      GlobalPoint globalPosition = pgdu->toGlobal(iPRH->localPosition());
      bool isAnyPixelAtEdge = isRecHitAtTheEdge(iPRH,pgdu);
      if(!isAnyPixelAtEdge && layer == 1 && (pgdu->subDetector() == GeomDetEnumerators::PixelBarrel))
        numRecHits_1l++;
  }

  vector<float> result;
  result.push_back(numRecHits_1l);
  result.push_back(rver_z);
  nCLusterVertices->Fill(&result[0]);
}

/*****************************************************************************/
bool ChargedMultiplicityAnalyzerNoSimInfo_new::aboveTriggerThreshold_1(edm::Handle<CaloTowerCollection> towers)
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
bool ChargedMultiplicityAnalyzerNoSimInfo_new::aboveTriggerThreshold_2(edm::Handle<CaloTowerCollection> towers)
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
bool ChargedMultiplicityAnalyzerNoSimInfo_new::ChristofMinBias(const edm::Event& event, const edm::EventSetup& eventSetup)
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
     if(energy>3. && eta<-3.)
       neg_eta = true;
     if(energy>3. && eta>3.)
       pos_eta = true;
  }

/*
  edm::Handle<CaloTowerCollection> towers;
  event.getByLabel("towerMaker",towers);
  CaloTowerCollection::const_iterator cal;

  bool pos_eta = false;
  bool neg_eta = false;

  for( cal = towers->begin(); cal != towers->end(); ++cal ) {

     double eta = cal->eta();
     double energy   = cal->energy();
     CaloTowerDetId idT = cal->id();
     int ieta = idT.ieta();

     //trigger criterion
     if(energy>3. && eta<-3.)
       neg_eta = true;
     if(energy>3. && eta>3.)
       pos_eta = true;
  }
*/

  if(neg_eta && pos_eta)
    return true;

  return false;
}

/*****************************************************************************/
bool ChargedMultiplicityAnalyzerNoSimInfo_new::trackTrigger(edm::Handle<reco::TrackCollection>& recCollection)
{
  int tracks = recCollection.product()->size();
  if(tracks>0)
    return true;
  else
    return false;
}

/*****************************************************************************/
bool ChargedMultiplicityAnalyzerNoSimInfo_new::track5Trigger(edm::Handle<reco::TrackCollection>& recCollection)
{
  int tracks = recCollection.product()->size();
  if(tracks>4)
    return true;
  else
    return false;
}

/*****************************************************************************/
bool ChargedMultiplicityAnalyzerNoSimInfo_new::isRecHitAtTheEdge(SiPixelRecHitCollection::DataContainer::const_iterator iPRH,
                                                    const PixelGeomDetUnit* pgdu)
{
  bool isAnyPixelAtEdge = false;
  std::vector<SiPixelCluster::Pixel> pixels = (*iPRH).cluster()->pixels();
  for(std::vector<SiPixelCluster::Pixel>::const_iterator pixel = pixels.begin(); pixel != pixels.end(); pixel++) {
     int pixelX = int((*pixel).x);
     int pixelY = int((*pixel).y);
     const RectangularPixelTopology* theTopol = dynamic_cast<const RectangularPixelTopology*>( & (pgdu->specificTopology()) );
     if(theTopol->isItEdgePixelInX(pixelX) || theTopol->isItEdgePixelInY(pixelY)) {
       isAnyPixelAtEdge = true;
     }
  }
  return isAnyPixelAtEdge;
}

/*****************************************************************************/
void ChargedMultiplicityAnalyzerNoSimInfo_new::onFirst(edm::Handle<SiPixelRecHitCollection>& siPixelRecCollection,
//                                                  const reco::VertexCollection* vertices,
                                                  const edm::Event& ev,
                                                  const edm::EventSetup& es)
{
  // get vertex_z
  float rver_z = getVertexZ(siPixelRecCollection, ev);

  edm::ESHandle<TrackerGeometry> geom;
  es.get<TrackerDigiGeometryRecord>().get(geom);
  const SiPixelRecHitCollection pixelRecHits = *(siPixelRecCollection.product());

  // Check all and unused RecHits
  // collect event-by-event
  //ofstream file("vertex.log");
  //file<<" # recVertex at: " << rver_z << endl;
  hClusterZSizeY->Reset();
  for(SiPixelRecHitCollection::DataContainer::const_iterator iPRH = pixelRecHits.data().begin(); iPRH != pixelRecHits.data().end(); ++iPRH) {
      const PixelGeomDetUnit* pgdu = dynamic_cast<const PixelGeomDetUnit*>(geom->idToDetUnit(iPRH->geographicalId()));
      PXBDetId pdetId = PXBDetId(iPRH->geographicalId());
      int layer=pdetId.layer();
      GlobalPoint globalPosition = pgdu->toGlobal(iPRH->localPosition());
      float z = globalPosition.z();
      float x = fabs(globalPosition.x() - theBeamSpot->position().x());
      float y = fabs(globalPosition.y() - theBeamSpot->position().y());
      float R = TMath::Sqrt(x*x + y*y);
      float det_eta = globalPosition.eta();
      float eta_corr = -999.;
      eta_corr = -log(tan(atan2(R,(z-rver_z))/2.));
      float ccharge = (iPRH)->cluster()->charge();
      float adc = ccharge/135.;
      //all
      bool isAnyPixelAtEdge = isRecHitAtTheEdge(iPRH,pgdu);
      if(!isAnyPixelAtEdge && layer == 1 && (pgdu->subDetector() == GeomDetEnumerators::PixelBarrel)) {
         PureAdcvsCorrEta->Fill(eta_corr, adc);
         PureCorrEta->Fill(eta_corr);
         if((130.*cosh(eta_corr)-33.)<adc) {  //cut
            PureCutCorrEta->Fill(eta_corr);
            PureCutAdcvsCorrEta->Fill(eta_corr,adc);
         }
         // pixel size in y direction vs eta_corr
         hCorrEtaSizeY->Fill(eta_corr,(iPRH)->cluster()->sizeY());
         hCorrEtaADC->Fill(eta_corr,adc);
         hClusterZSizeY->Fill(z,(iPRH)->cluster()->sizeY());
         if(eta_corr<0.1 && eta_corr>-0.1)
            ResPureCentralAdc->Fill(adc);
         if(eta_corr<0.1 && eta_corr>-0.1 && ((130.*cosh(eta_corr)-33.)<adc)) //cut
            ResPureCutCentralAdc->Fill(adc);
         if(eta_corr<2.1 && eta_corr>1.9)
            ResPureAdc->Fill(adc);
         if(det_eta<2.1 && det_eta>1.9)  //same as the preceding lines but we use detector eta here
            ResPureAdc_det->Fill(adc);
         if(eta_corr<2.1 && eta_corr>1.9 && ((130.*cosh(eta_corr)-33.)<adc)) //cut
            ResPureCutAdc->Fill(adc);
      }

  }
  //file.close();
}

/*****************************************************************************/
bool ChargedMultiplicityAnalyzerNoSimInfo_new::compareRecHits
  (const SiPixelRecHit * hit1, const SiPixelRecHit * hit2)
{
  return hit1->geographicalId() == hit2->geographicalId() &&
        (hit1->cluster())->charge() == (hit2->cluster())->charge() &&
        (hit1->cluster())->size() == (hit2->cluster())->size() &&
        (hit1->cluster())->sizeX() == (hit2->cluster())->sizeX() &&
        (hit1->cluster())->sizeY() == (hit2->cluster())->sizeY();
}

/*****************************************************************************/
float ChargedMultiplicityAnalyzerNoSimInfo_new::geomAcc(double vert_z, double eta_l, double eta_h, int desLayer)
{
  // eta = -ln(tan(theta/2)); pixel in z dir: 55 cm
  // double eta_corr = -log(tan(atan2(R,(globalPosition.z()-rver_z))/2.));

  float eta_max_lemma = 2.5;
  float eta_min_lemma = -2.5;
  float eta_max = 2.5;
  float eta_min = -2.5;
  double R = 4.4;
  if(desLayer == 2) {eta_max = 2.; eta_min = -2.; R = 7.3;}
  if(desLayer == 3) {eta_max = 1.7; eta_min = -1.7; R = 10.2;}
  float binwidth = 0.5;
  float halflenght = 55./2.;  // 53? 54?

  eta_max_lemma = -log(tan(atan2(R,(halflenght-vert_z))/2.));
  eta_min_lemma = -log(tan(atan2(R,(-halflenght-vert_z))/2.));

  if(eta_max_lemma>eta_min_lemma) {
    eta_max = eta_max_lemma;
    eta_min = eta_min_lemma;
  } else {
    eta_max = eta_min_lemma;
    eta_min = eta_max_lemma;
  }

//  cerr<< " vert_z : " << vert_z << endl;
//  cerr<< " eta_min: " << eta_min << endl;
//  cerr<< " eta_max: " << eta_max << endl;
//  cerr<< " eta_l:   " << eta_l << endl;
//  cerr<< " eta_h:   " << eta_h << endl;

  // correction for small pt-s:
  eta_max = eta_max-0.006;  // TEST
  eta_min = eta_min+0.006;  // TEST

  if(eta_h < eta_min) { if(eta_l==0.0) cerr<< " STRANGE 1 " << endl; return 0.; }
  if(eta_l > eta_max) { if(eta_l==0.0) cerr<< " STRANGE 2 " << endl; return 0.; }
  if(eta_l > eta_min && eta_h < eta_max) { return 1.; }
  if(eta_l < eta_min && eta_h > eta_min) { return ((eta_h-eta_min)/binwidth); }
  if(eta_l < eta_max && eta_h > eta_max) { return ((eta_max-eta_l)/binwidth); }

  return -1.;
}

/*****************************************************************************/
void ChargedMultiplicityAnalyzerNoSimInfo_new::multiplicityProperties
   (const edm::Event& ev, const edm::EventSetup& es, 
    edm::Handle<SiPixelRecHitCollection> siPixelRecCollection,
//    const reco::VertexCollection* vertices,
    int desLayer)
{
  // Triggers
  edm::Handle<edm::TriggerResults> triggerResults;
  ev.getByType(triggerResults);

//  edm::TriggerNames triggerNames;
  const edm::TriggerNames & triggerNames = ev.triggerNames(*triggerResults);
//  triggerNames.init( *(triggerResults.product()) );

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
//      bunchCrossing->triggerNames.push_back(triggerNames.triggerName(itrig));
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
/*
    std::cerr<< "L1_BptxMinus name:   " << is_L1_BptxMinus << std::endl;
    std::cerr<< "L1_BptxPlus name:   " << is_L1_BptxPlus << std::endl;
    std::cerr<< "L1_BptxPlusORMinus name:   " << is_L1_BptxPlusORMinus << std::endl;
    std::cerr<< "L1_BscMinBiasOR_BptxPlusORMinus name:   " << is_L1_BscMinBiasOR_BptxPlusORMinus << std::endl;
*/
/*
    is_L1_BptxMinus = l1AlgorithmResult(ev, es, "L1_BptxMinus");
    is_L1_BptxPlus = l1AlgorithmResult(ev, es, "L1_BptxPlus");
    is_L1_BptxPlusORMinus = l1AlgorithmResult(ev, es, "L1_BptxPlusORMinus");
    is_L1_BscMinBiasOR_BptxPlusORMinus = l1AlgorithmResult(ev, es, "L1_BscMinBiasOR_BptxPlusORMinus");
*/
  }

  edm::ESHandle<TrackerGeometry> geom;
  es.get<TrackerDigiGeometryRecord>().get(geom);

  vector<float> result;
  const SiPixelRecHitCollection pixelRecHits = *(siPixelRecCollection.product());
/*
  //for Vincenzo
  edm::Handle<edm::DetSetVector<PixelDigi> > pixelDigis;
  ev.getByLabel("siPixelDigis", pixelDigis);

  result.push_back(pixelDigis->size());
*/
  result.push_back(pixelRecHits.size()); //clusters

  // get number of clusters
  float clusters_on_layers = 0.;
  for(SiPixelRecHitCollection::DataContainer::const_iterator iPRH = pixelRecHits.data().begin(); iPRH != pixelRecHits.data().end(); ++iPRH ) {
     const PixelGeomDetUnit* pgdu = dynamic_cast<const PixelGeomDetUnit*>(geom->idToDetUnit((*iPRH).geographicalId()));
     PXBDetId pdetId = PXBDetId(iPRH->geographicalId());
     int layer=pdetId.layer();
     GlobalPoint globalPosition = pgdu->toGlobal(iPRH->localPosition());
     if((pgdu->subDetector() == GeomDetEnumerators::PixelBarrel) && (layer == desLayer))
       clusters_on_layers++;
  }

  result.push_back(clusters_on_layers); //clusters_on_layers

  // get vertex_z
  double rver_z = (double)getVertexZ(siPixelRecCollection, ev);

  result.push_back(rver_z); //rver_z

  std::vector<const SiPixelRecHit*> passedRecHits;
  std::vector<const SiPixelRecHit*> failedRecHitsP5;
  std::vector<const SiPixelRecHit*> failedRecHitsP4;
  std::vector<const SiPixelRecHit*> failedRecHitsP3;
  std::vector<const SiPixelRecHit*> failedRecHitsP2;
  std::vector<const SiPixelRecHit*> failedRecHitsP1;
  std::vector<const SiPixelRecHit*> failedRecHitsN1;
  std::vector<const SiPixelRecHit*> failedRecHitsN2;
  std::vector<const SiPixelRecHit*> failedRecHitsN3;
  std::vector<const SiPixelRecHit*> failedRecHitsN4;
  std::vector<const SiPixelRecHit*> failedRecHitsN5;

  // select hits based on ADC information
  for(SiPixelRecHitCollection::DataContainer::const_iterator iPRH = pixelRecHits.data().begin(); iPRH != pixelRecHits.data().end(); ++iPRH ) {
     const PixelGeomDetUnit* pgdu = dynamic_cast<const PixelGeomDetUnit*>(geom->idToDetUnit((*iPRH).geographicalId()));
     PXBDetId pdetId = PXBDetId(iPRH->geographicalId());
     int layer=pdetId.layer();
     double ccharge = (*iPRH).cluster()->charge();
     double adc = ccharge/135.;
     GlobalPoint globalPosition = pgdu->toGlobal(iPRH->localPosition());
//     if(vertices->size()!=1) //should never happen with cluster vertices
//       break;
     float x = fabs(globalPosition.x() - theBeamSpot->position().x());
     float y = fabs(globalPosition.y() - theBeamSpot->position().y());
     double R = TMath::Sqrt(x*x + y*y);
     double eta_corr = -log(tan(atan2(R,(globalPosition.z()-rver_z))/2.));
     if((pgdu->subDetector() == GeomDetEnumerators::PixelBarrel) && (layer == desLayer) && (adc>(130.*cosh(eta_corr)-33.)))
       passedRecHits.push_back(&(*iPRH));
     if((pgdu->subDetector() == GeomDetEnumerators::PixelBarrel) && (layer == desLayer) && (adc<(130.*cosh(eta_corr)-33.)) && eta_corr<2.5 && eta_corr>2.0)
       failedRecHitsP5.push_back(&(*iPRH));
     if((pgdu->subDetector() == GeomDetEnumerators::PixelBarrel) && (layer == desLayer) && (adc<(130.*cosh(eta_corr)-33.)) && eta_corr<=2.0 && eta_corr>1.5)
       failedRecHitsP4.push_back(&(*iPRH));
     if((pgdu->subDetector() == GeomDetEnumerators::PixelBarrel) && (layer == desLayer) && (adc<(130.*cosh(eta_corr)-33.)) && eta_corr<=1.5 && eta_corr>1.0)
       failedRecHitsP3.push_back(&(*iPRH));
     if((pgdu->subDetector() == GeomDetEnumerators::PixelBarrel) && (layer == desLayer) && (adc<(130.*cosh(eta_corr)-33.)) && eta_corr<=1.0 && eta_corr>0.5)
       failedRecHitsP2.push_back(&(*iPRH));
     if((pgdu->subDetector() == GeomDetEnumerators::PixelBarrel) && (layer == desLayer) && (adc<(130.*cosh(eta_corr)-33.)) && eta_corr<=0.5 && eta_corr>0.0)
       failedRecHitsP1.push_back(&(*iPRH));
     if((pgdu->subDetector() == GeomDetEnumerators::PixelBarrel) && (layer == desLayer) && (adc<(130.*cosh(eta_corr)-33.)) && eta_corr<=0.0 && eta_corr>-0.5)
       failedRecHitsN1.push_back(&(*iPRH));
     if((pgdu->subDetector() == GeomDetEnumerators::PixelBarrel) && (layer == desLayer) && (adc<(130.*cosh(eta_corr)-33.)) && eta_corr<=-0.5 && eta_corr>-1.0)
       failedRecHitsN2.push_back(&(*iPRH));
     if((pgdu->subDetector() == GeomDetEnumerators::PixelBarrel) && (layer == desLayer) && (adc<(130.*cosh(eta_corr)-33.)) && eta_corr<=-1.0 && eta_corr>-1.5)
       failedRecHitsN3.push_back(&(*iPRH));
     if((pgdu->subDetector() == GeomDetEnumerators::PixelBarrel) && (layer == desLayer) && (adc<(130.*cosh(eta_corr)-33.)) && eta_corr<=-1.5 && eta_corr>-2.0)
       failedRecHitsN4.push_back(&(*iPRH));
     if((pgdu->subDetector() == GeomDetEnumerators::PixelBarrel) && (layer == desLayer) && (adc<(130.*cosh(eta_corr)-33.)) && eta_corr<=-2.0 && eta_corr>-2.5)
       failedRecHitsN5.push_back(&(*iPRH));
  }
  
  // multiplicity after cut applied; ADC information
  int counter = 0;
  for(std::vector<const SiPixelRecHit*>::const_iterator iPRH = passedRecHits.begin(); iPRH != passedRecHits.end(); ++iPRH ) {
     const PixelGeomDetUnit* pgdu = dynamic_cast<const PixelGeomDetUnit*>(geom->idToDetUnit((**iPRH).geographicalId()));
     PXBDetId pdetId = PXBDetId((**iPRH).geographicalId());
     int layer=pdetId.layer();
     if((pgdu->subDetector() == GeomDetEnumerators::PixelBarrel) && (layer == desLayer))
       counter++;
  }

//  if(vertices->size()!=1)  // shouldn't happen with cluster vertices; would be needed otherwise at low mult.
    for(SiPixelRecHitCollection::DataContainer::const_iterator iPRH = pixelRecHits.data().begin(); iPRH != pixelRecHits.data().end(); ++iPRH ) {
       const PixelGeomDetUnit* pgdu = dynamic_cast<const PixelGeomDetUnit*>(geom->idToDetUnit((*iPRH).geographicalId()));
       PXBDetId pdetId = PXBDetId((*iPRH).geographicalId());
       int layer=pdetId.layer();
       double ccharge = (*iPRH).cluster()->charge();
       double adc = ccharge/135.;
       GlobalPoint globalPosition = pgdu->toGlobal(iPRH->localPosition());
       if((pgdu->subDetector() == GeomDetEnumerators::PixelBarrel) && (layer == desLayer) && (adc>(130.*cosh(globalPosition.eta())-33.))) {
         counter++;
         passedRecHits.push_back(&(*iPRH)); //We don't apply the dEdx cut here
       }
    }

  result.push_back(failedRecHitsP5.size());  //failedSizeP5
  result.push_back(failedRecHitsP4.size());  //failedSizeP4
  result.push_back(failedRecHitsP3.size());  //failedSizeP3
  result.push_back(failedRecHitsP2.size());  //failedSizeP2
  result.push_back(failedRecHitsP1.size());  //failedSizeP1
  result.push_back(failedRecHitsN1.size());  //failedSizeN1
  result.push_back(failedRecHitsN2.size());  //failedSizeN2
  result.push_back(failedRecHitsN3.size());  //failedSizeN3
  result.push_back(failedRecHitsN4.size());  //failedSizeN4
  result.push_back(failedRecHitsN5.size());  //failedSizeN5
  result.push_back(counter);  //M

  //simulate triggers
  if(simulateTriggers_) {
    // Get trigger objects
    edm::Handle<reco::TrackCollection>  recCollection;
    ev.getByLabel("hltPixelTracksForMinBias", recCollection);

    edm::Handle<CaloTowerCollection> towers; 
    ev.getByLabel("towerMaker",towers);

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
    if(trackTrigger(recCollection)) {
      result.push_back(1);  //trackTrigger
    } else {
      result.push_back(0);  //trackTrigger
    }
    if(track5Trigger(recCollection)) {
      result.push_back(1);  //track5Trigger
    } else {
      result.push_back(0);  //track5Trigger
    }
    result.push_back(0);  //no sim.: HLT_ZeroBias
    result.push_back(0);  //no sim.: HLT_ZeroBias1kHz
    result.push_back(0);  //no sim.: HLT_MinBiasPixel_Single
    result.push_back(0);  //no sim.: HLT_MinBiasBSC_OR 
    result.push_back(0);  //no sim.: HLT_ZeroBiasPixel_SingleTrack
    result.push_back(0);  //no sim.: HLT_L1_BscMinBiasOR_BptxPlusORMinus
    result.push_back(0);  //no sim.: HLT_HighMultiplicityBSC
    result.push_back(0);  //no sim.: HLT_L1_BSC
    result.push_back(0);  //no sim.: HLT_L1_BPTX
    result.push_back(0);  //no sim.: HLT_L1_BPTX_MinusOnly
    result.push_back(0);  //no sim.: HLT_L1_BPTX_PlusOnly
    result.push_back(0);  //no sim.: HLT_MinBiasHcal
    result.push_back(0);  //no sim.: HLT_BackwardBSC
    result.push_back(0);  //no sim.: HLT_ForwardBSC
    if(ChristofMinBias(ev,es)) {
      result.push_back(1);//hf
    } else {
      result.push_back(0);//hf
    }
  }

  if(!simulateTriggers_) {
    edm::Handle<CaloTowerCollection> towers;
    ev.getByLabel("towerMaker",towers);

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
    result.push_back(0);  //track5Trigger
    if(is_HLT_ZeroBias) {
      result.push_back(1);  //HLT_ZeroBias
    } else {
      result.push_back(0);  //HLT_ZeroBias
    }
    if(is_HLT_ZeroBias1kHz) {
      result.push_back(1);  //HLT_ZeroBias1kHz
    } else {
      result.push_back(0);  //HLT_ZeroBias1kHz
    }
    if(is_HLT_MinBiasPixel_SingleTrack) {
      result.push_back(1);  //HLT_MinBiasPixel_Single
    } else {
      result.push_back(0);  //HLT_MinBiasPixel_Single
    }
    if(is_HLT_MinBiasBSC_OR ) {
      result.push_back(1);  //HLT_MinBiasBSC_OR 
    } else {
      result.push_back(0);  //HLT_MinBiasBSC_OR 
    }
    if(is_HLT_ZeroBiasPixel_SingleTrack) {
      result.push_back(1);  //HLT_ZeroBiasPixel_SingleTrack
    } else {
      result.push_back(0);  //HLT_ZeroBiasPixel_SingleTrack
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

//  result.push_back(vertices->size());  //numVtx
  result.push_back(1);    //numEv

  int H_recMC_etaP5 = 0;
  int H_recMC_etaP4 = 0;
  int H_recMC_etaP3 = 0;
  int H_recMC_etaP2 = 0;
  int H_recMC_etaP1 = 0;
  int H_recMC_etaN1 = 0;
  int H_recMC_etaN2 = 0;
  int H_recMC_etaN3 = 0;
  int H_recMC_etaN4 = 0;
  int H_recMC_etaN5 = 0;
  for(std::vector<const SiPixelRecHit*>::const_iterator iPRH = passedRecHits.begin(); iPRH != passedRecHits.end(); ++iPRH ) {
     const PixelGeomDetUnit* pgdu = dynamic_cast<const PixelGeomDetUnit*>(geom->idToDetUnit((**iPRH).geographicalId()));
     PXBDetId pdetId = PXBDetId((**iPRH).geographicalId());
     int layer=pdetId.layer();
     GlobalPoint globalPosition = pgdu->toGlobal((**iPRH).localPosition());
     float x = fabs(globalPosition.x() - theBeamSpot->position().x());
     float y = fabs(globalPosition.y() - theBeamSpot->position().y());
     double R = TMath::Sqrt(x*x + y*y);
     double eta_corr = -log(tan(atan2(R,(globalPosition.z()-rver_z))/2.));
     if((pgdu->subDetector() == GeomDetEnumerators::PixelBarrel) && (layer == desLayer) && eta_corr<2.5 && eta_corr>2.0)   //Positive etas
       H_recMC_etaP5++;
     if((pgdu->subDetector() == GeomDetEnumerators::PixelBarrel) && (layer == desLayer) && eta_corr<=2.0 && eta_corr>1.5)   //Positive etas
       H_recMC_etaP4++;
     if((pgdu->subDetector() == GeomDetEnumerators::PixelBarrel) && (layer == desLayer) && eta_corr<=1.5 && eta_corr>1.0)   //Positive etas
       H_recMC_etaP3++;
     if((pgdu->subDetector() == GeomDetEnumerators::PixelBarrel) && (layer == desLayer) && eta_corr<=1.0 && eta_corr>0.5)   //Positive etas
       H_recMC_etaP2++;
     if((pgdu->subDetector() == GeomDetEnumerators::PixelBarrel) && (layer == desLayer) && eta_corr<=0.5 && eta_corr>0.0)   //Positive etas
       H_recMC_etaP1++;
     if((pgdu->subDetector() == GeomDetEnumerators::PixelBarrel) && (layer == desLayer) && eta_corr<=0.0 && eta_corr>-0.5)   //Negative etas
       H_recMC_etaN1++;
     if((pgdu->subDetector() == GeomDetEnumerators::PixelBarrel) && (layer == desLayer) && eta_corr<=-0.5 && eta_corr>-1.0)   //Negative etas
       H_recMC_etaN2++;
     if((pgdu->subDetector() == GeomDetEnumerators::PixelBarrel) && (layer == desLayer) && eta_corr<=-1.0 && eta_corr>-1.5)   //Negative etas
       H_recMC_etaN3++;
     if((pgdu->subDetector() == GeomDetEnumerators::PixelBarrel) && (layer == desLayer) && eta_corr<=-1.5 && eta_corr>-2.0)   //Negative etas
       H_recMC_etaN4++;
     if((pgdu->subDetector() == GeomDetEnumerators::PixelBarrel) && (layer == desLayer) && eta_corr<=-2.0 && eta_corr>-2.5)   //Negative etas
       H_recMC_etaN5++;
  }

  result.push_back(H_recMC_etaP5);  //H_recMC_etaP5
  result.push_back(H_recMC_etaP4);  //H_recMC_etaP4
  result.push_back(H_recMC_etaP3);  //H_recMC_etaP3
  result.push_back(H_recMC_etaP2);  //H_recMC_etaP2
  result.push_back(H_recMC_etaP1);  //H_recMC_etaP1
  result.push_back(H_recMC_etaN1);  //H_recMC_etaN1
  result.push_back(H_recMC_etaN2);  //H_recMC_etaN2
  result.push_back(H_recMC_etaN3);  //H_recMC_etaN3
  result.push_back(H_recMC_etaN4);  //H_recMC_etaN4
  result.push_back(H_recMC_etaN5);  //H_recMC_etaN5

  // cluster selection based on cluster size
  int clustSizeY_etaP6 = 0;
  int clustSizeY_etaP5 = 0;
  int clustSizeY_etaP4 = 0;
  int clustSizeY_etaP3 = 0;
  int clustSizeY_etaP2 = 0;
  int clustSizeY_etaP1 = 0;
  int clustSizeY_etaN1 = 0;
  int clustSizeY_etaN2 = 0;
  int clustSizeY_etaN3 = 0;
  int clustSizeY_etaN4 = 0;
  int clustSizeY_etaN5 = 0;
  int clustSizeY_etaN6 = 0;
  std::vector<const SiPixelRecHit*> passedClusters;
  for(SiPixelRecHitCollection::DataContainer::const_iterator iPRH = pixelRecHits.data().begin(); iPRH != pixelRecHits.data().end(); ++iPRH ) {
     const PixelGeomDetUnit* pgdu = dynamic_cast<const PixelGeomDetUnit*>(geom->idToDetUnit((*iPRH).geographicalId()));
     PXBDetId pdetId = PXBDetId((*iPRH).geographicalId());
     int layer=pdetId.layer();
     GlobalPoint globalPosition = pgdu->toGlobal((*iPRH).localPosition());
     float x = fabs(globalPosition.x() - theBeamSpot->position().x());
     float y = fabs(globalPosition.y() - theBeamSpot->position().y());
     double R = TMath::Sqrt(x*x + y*y);
     double eta_corr = -log(tan(atan2(R,(globalPosition.z()-rver_z))/2.));
     int clustSizeY = (iPRH)->cluster()->sizeY();

     if((pgdu->subDetector() == GeomDetEnumerators::PixelBarrel) && (layer == desLayer) && eta_corr<3.0 && eta_corr>=2.5 && clustSizeY>8.5)   
       { clustSizeY_etaP6++; passedClusters.push_back(&(*iPRH)); }
     if((pgdu->subDetector() == GeomDetEnumerators::PixelBarrel) && (layer == desLayer) && eta_corr<2.5 && eta_corr>2.0 && clustSizeY>5.5)   //Positive etas
       { clustSizeY_etaP5++; passedClusters.push_back(&(*iPRH)); }
     if((pgdu->subDetector() == GeomDetEnumerators::PixelBarrel) && (layer == desLayer) && eta_corr<=2.0 && eta_corr>1.5 && clustSizeY>3.5)   //Positive etas
       { clustSizeY_etaP4++; passedClusters.push_back(&(*iPRH)); }
     if((pgdu->subDetector() == GeomDetEnumerators::PixelBarrel) && (layer == desLayer) && eta_corr<=1.5 && eta_corr>1.0 && clustSizeY>2.5)   //Positive etas
       { clustSizeY_etaP3++; passedClusters.push_back(&(*iPRH)); }
     if((pgdu->subDetector() == GeomDetEnumerators::PixelBarrel) && (layer == desLayer) && eta_corr<=1.0 && eta_corr>0.5 && clustSizeY>1.5)   //Positive etas
       { clustSizeY_etaP2++; passedClusters.push_back(&(*iPRH)); }
     if((pgdu->subDetector() == GeomDetEnumerators::PixelBarrel) && (layer == desLayer) && eta_corr<=0.5 && eta_corr>0.0)   //Positive etas + no cut
       { clustSizeY_etaP1++; passedClusters.push_back(&(*iPRH)); }
     if((pgdu->subDetector() == GeomDetEnumerators::PixelBarrel) && (layer == desLayer) && eta_corr<=0.0 && eta_corr>-0.5)   //Negative etas + no cut
       { clustSizeY_etaN1++; passedClusters.push_back(&(*iPRH)); }
     if((pgdu->subDetector() == GeomDetEnumerators::PixelBarrel) && (layer == desLayer) && eta_corr<=-0.5 && eta_corr>-1.0 && clustSizeY>1.5)   //Negative etas
       { clustSizeY_etaN2++; passedClusters.push_back(&(*iPRH)); }
     if((pgdu->subDetector() == GeomDetEnumerators::PixelBarrel) && (layer == desLayer) && eta_corr<=-1.0 && eta_corr>-1.5 && clustSizeY>2.5)   //Negative etas
       { clustSizeY_etaN3++; passedClusters.push_back(&(*iPRH)); }
     if((pgdu->subDetector() == GeomDetEnumerators::PixelBarrel) && (layer == desLayer) && eta_corr<=-1.5 && eta_corr>-2.0 && clustSizeY>3.5)   //Negative etas
       { clustSizeY_etaN4++; passedClusters.push_back(&(*iPRH)); }
     if((pgdu->subDetector() == GeomDetEnumerators::PixelBarrel) && (layer == desLayer) && eta_corr<=-2.0 && eta_corr>-2.5 && clustSizeY>5.5)   //Negative etas
       { clustSizeY_etaN5++; passedClusters.push_back(&(*iPRH)); }
     if((pgdu->subDetector() == GeomDetEnumerators::PixelBarrel) && (layer == desLayer) && eta_corr<=-2.5 && eta_corr>-3.0 && clustSizeY>8.5)   
       { clustSizeY_etaN6++; passedClusters.push_back(&(*iPRH)); }
  }

  result.push_back(clustSizeY_etaP6);  //clustSizeY_etaP6
  result.push_back(clustSizeY_etaP5);  //clustSizeY_etaP5
  result.push_back(clustSizeY_etaP4);  //clustSizeY_etaP4
  result.push_back(clustSizeY_etaP3);  //clustSizeY_etaP3
  result.push_back(clustSizeY_etaP2);  //clustSizeY_etaP2
  result.push_back(clustSizeY_etaP1);  //clustSizeY_etaP1
  result.push_back(clustSizeY_etaN1);  //clustSizeY_etaN1
  result.push_back(clustSizeY_etaN2);  //clustSizeY_etaN2
  result.push_back(clustSizeY_etaN3);  //clustSizeY_etaN3
  result.push_back(clustSizeY_etaN4);  //clustSizeY_etaN4
  result.push_back(clustSizeY_etaN5);  //clustSizeY_etaN5
  result.push_back(clustSizeY_etaN6);  //clustSizeY_etaN6

  int cluster_counter = clustSizeY_etaP5+clustSizeY_etaP4+clustSizeY_etaP3+clustSizeY_etaP2+clustSizeY_etaP1+clustSizeY_etaN1+clustSizeY_etaN2+clustSizeY_etaN3+clustSizeY_etaN4+clustSizeY_etaN5;
  result.push_back(cluster_counter);

  // fill the ntuples
  if(desLayer==1)
    multProp->Fill(&result[0]);
  if(desLayer==2)
    nd_multProp->Fill(&result[0]);
  if(desLayer==3)
    rd_multProp->Fill(&result[0]);

  // fill ntuple for the looper correction, cluster size
//  if(vertices->size()==1) { //should always be true with cluster vertices
    // Get pixel hits
    theHits = siPixelRecCollection.product();

    for(SiPixelRecHitCollection::const_iterator detunit_iter = theHits->begin();
                                             detunit_iter!= theHits->end(); detunit_iter++)
    {
      SiPixelRecHitCollection::DetSet range = *detunit_iter;
      unsigned int id = range.detId();
      const PixelGeomDetUnit* pixelDet =
        dynamic_cast<const PixelGeomDetUnit*> (theTracker->idToDet((id)));

      PXBDetId pid(id);
      // Take all hits
      if(pid.subdetId() == PixelSubdetector::PixelBarrel)
      { 
        if(pid.layer() == (unsigned)desLayer)
        for(SiPixelRecHitCollection::DetSet::const_iterator recHit = range.begin();
                             recHit!= range.end(); recHit++)
        {
          GlobalPoint gpos = pixelDet->toGlobal(recHit->localPosition());
          float x = fabs(gpos.x() - theBeamSpot->position().x());
          float y = fabs(gpos.y() - theBeamSpot->position().y());
          double R = TMath::Sqrt(x*x + y*y);
          float eta = -log(tan(atan2(R,(gpos.z()-rver_z))/2.));
          float eta_det = -log(tan(atan2(R,(gpos.z()-0.))/2.));
          float eloss = recHit->cluster()->charge();
          int clustSizeY = recHit->cluster()->sizeY();
          int clustSizeX = recHit->cluster()->sizeX();
          float phi = gpos.phi();
          int pixels = recHit->cluster()->size();

          double length = (recHit->localPosition()).mag()/fabsf((recHit->localPosition()).z())*pixelDet->surface().bounds().thickness();
  
          vector<float> result_looper;

          edm::Handle<CaloTowerCollection> towers;
          ev.getByLabel("towerMaker",towers);

          result_looper.push_back(aboveTriggerThreshold_1(towers));
          result_looper.push_back(aboveTriggerThreshold_2(towers));

          result_looper.push_back(rver_z);
          result_looper.push_back(eta);
          result_looper.push_back(eta_det);
          result_looper.push_back(phi);
          result_looper.push_back(eloss);
//          result_looper.push_back(type*(isAtEdge(topology,*recHit) ? -1 : 1));
          result_looper.push_back(counter);
//          result_looper.push_back(vertices->size());
          result_looper.push_back(clustSizeY);
          result_looper.push_back(clustSizeX);
          result_looper.push_back(length);
          result_looper.push_back(pixels);
          result_looper.push_back(cluster_counter);
          result_looper.push_back(is_HLT_ZeroBias);
          result_looper.push_back(is_HLT_ZeroBias1kHz);
          result_looper.push_back(is_HLT_MinBiasPixel_SingleTrack);
          result_looper.push_back(is_HLT_MinBiasBSC_OR);
          result_looper.push_back(is_HLT_ZeroBiasPixel_SingleTrack);
          result_looper.push_back(is_HLT_L1_BscMinBiasOR_BptxPlusORMinus);
          result_looper.push_back(is_HLT_HighMultiplicityBSC);
          result_looper.push_back(is_HLT_L1_BSC);
          result_looper.push_back(is_HLT_L1_BPTX);
          result_looper.push_back(is_HLT_L1_BPTX_MinusOnly);
          result_looper.push_back(is_HLT_L1_BPTX_PlusOnly);
          result_looper.push_back(is_HLT_MinBiasHcal);
          result_looper.push_back(is_HLT_BackwardBSC);
          result_looper.push_back(is_HLT_ForwardBSC);

          result_looper.push_back(is_bit0);
          result_looper.push_back(is_bit3);
          result_looper.push_back(is_bit4);
          result_looper.push_back(is_bit9);
          result_looper.push_back(is_bit34);
          result_looper.push_back(is_bit35);
          result_looper.push_back(is_bit36);
          result_looper.push_back(is_bit37);
          result_looper.push_back(is_bit38);
          result_looper.push_back(is_bit39);
          result_looper.push_back(is_bit40);
          result_looper.push_back(is_bit41);
          result_looper.push_back(is_bit42);
          result_looper.push_back(is_bit43);

          result_looper.push_back(is_L1_BptxMinus);
          result_looper.push_back(is_L1_BptxPlus);
          result_looper.push_back(is_L1_BptxPlusORMinus);
          result_looper.push_back(is_L1_BscMinBiasOR_BptxPlusORMinus);

          result_looper.push_back(ChristofMinBias(ev,es));

          // fill the ntuples
          if(desLayer==1)
            multProp_looper->Fill(&result_looper[0]);
          if(desLayer==2)
            nd_multProp_looper->Fill(&result_looper[0]);
          if(desLayer==3)
            rd_multProp_looper->Fill(&result_looper[0]);

        }
      }
    }
//  }
}

/*****************************************************************************/
bool ChargedMultiplicityAnalyzerNoSimInfo_new::isAtEdge
  (const RectangularPixelTopology* topology, const SiPixelRecHit & recHit)
{
  return topology->isItEdgePixelInX(recHit.cluster()->minPixelCol()) ||
         topology->isItEdgePixelInX(recHit.cluster()->maxPixelCol()) ||
         topology->isItEdgePixelInY(recHit.cluster()->minPixelRow()) ||
         topology->isItEdgePixelInY(recHit.cluster()->maxPixelRow());
}

/*****************************************************************************/
void ChargedMultiplicityAnalyzerNoSimInfo_new::analyze
  (const edm::Event& ev, const edm::EventSetup& es)
{
/*
  edm::EventID eventId = ev.id();
  int runNumber = eventId.run();
  int lumi = ev.luminosityBlock();

  //BEWARE!!! skip events based on run number and lumi section
  std::cerr<<" run number: " << runNumber << std::endl;
  std::cerr<<"    lumi section: " << lumi << std::endl;
  if(lumi<41 || lumi>96 || runNumber!=124023)
    return;
*/
  // Get recHits
  edm::Handle<SiPixelRecHitCollection> siPixelRecCollection;
  ev.getByLabel(src_,siPixelRecCollection);

  // Get tracker geometry
  edm::ESHandle<TrackerGeometry> tracker;
  es.get<TrackerDigiGeometryRecord>().get(tracker);
  theTracker = tracker.product();

  // Beam spot
  edm::Handle<BeamSpot>      beamSpotHandle;
  ev.getByLabel("offlineBeamSpot", beamSpotHandle);
  theBeamSpot = beamSpotHandle.product();

  // analyze
  onFirst(siPixelRecCollection, ev, es);
  multiplicityProperties(ev, es, siPixelRecCollection, 1);
  multiplicityProperties(ev, es, siPixelRecCollection, 2);
  multiplicityProperties(ev, es, siPixelRecCollection, 3);
  clusterVertices(ev, es, siPixelRecCollection);

}
