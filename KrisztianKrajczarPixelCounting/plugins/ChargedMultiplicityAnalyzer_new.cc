// $Id: ChargedMultiplicityAnalyzer_new.cc,v 1.25 2010/10/29 15:21:22 krajczar Exp $
// TRICK: DataContainer in the recHit loops

#include "ChargedMultiplicityAnalyzer_new.h"

/*****************************************************************************/
ChargedMultiplicityAnalyzer_new::ChargedMultiplicityAnalyzer_new(const edm::ParameterSet& pset)
{
  resultFileLabel       = pset.getParameter<string>("file");
  simulateTriggers_     = pset.getParameter<bool>("simulateTriggers");
  hasL1Triggers_        = pset.getParameter<bool>("hasL1Triggers");
  produceVertexLocally_ = pset.getParameter<bool>("produceVertexLocally");
  src_                  = pset.getParameter<edm::InputTag>("src");
  vertexColl_           = pset.getParameter<edm::InputTag>("vertexColl");
}

/*****************************************************************************/
ChargedMultiplicityAnalyzer_new::~ChargedMultiplicityAnalyzer_new()
{
}

/*****************************************************************************/
void ChargedMultiplicityAnalyzer_new::beginJob()
{

  // Root
  resultFile = new TFile(resultFileLabel.c_str(),"recreate","",6);
  TDirectory::TContext context(resultFile);

  verticesInfo = new TNtuple("verticesInfo","verticesInfo",
     "numrvertices:numsvertices:numrectracks:procID");
//  multi = new TNtuple("multi","multi", "eta:eloss:type");
  looper = new TNtuple("looper","looper","Dtof");

  //magnetic field
//  nMagField = new TNtuple("nMagField","nMagField","x:y:z");

  //multiplicity
  hNum_nd = new TH1F("hNum_nd","hNum_nd",1,-0.5,0.5);
  hNum_nsd = new TH1F("hNum_nsd","hNum_nsd",1,-0.5,0.5);
  hNum_nsd_trig = new TH1F("hNum_nsd_trig","hNum_nsd_trig",1,-0.5,0.5);
  hNum_sd_trig = new TH1F("hNum_sd_trig","hNum_sd_trig",1,-0.5,0.5);

  multProp = new TNtuple("multProp","multProp",
     "digis:clusters:clusters_on_layers:rver_z:failedSizeP5:failedSizeP4:failedSizeP3:failedSizeP2:failedSizeP1:failedSizeN1:failedSizeN2:failedSizeN3:failedSizeN4:failedSizeN5:M:isTrigger_1:isTrigger_2:trackTrigger:track5Trigger:HLT_ZeroBias:HLT_ZeroBias1kHz:HLT_MinBiasPixel_SingleTrack:HLT_MinBiasBSC_OR:HLT_ZeroBiasPixel_SingleTrack:HLT_L1_BscMinBiasOR_BptxPlusORMinus:HLT_HighMultiplicityBSC:HLT_L1_BSC:HLT_L1_BPTX:HLT_L1_BPTX_MinusOnly:HLT_L1_BPTX_PlusOnly:HLT_MinBiasHcal:HLT_BackwardBSC:HLT_ForwardBSC:hf:minBias:bit0:bit3:bit4:bit9:bit34:bit35:bit36:bit37:bit38:bit39:bit40:bit41:bit42:bit43:L1_BptxMinus:L1_BptxPlus:L1_BptxPlusORMinus:L1_BscMinBiasOR_BptxPlusORMinus:numVtx:numEv:procID:T_truth:T_truth_etaP6:T_truth_etaP5:T_truth_etaP4:T_truth_etaP3:T_truth_etaP2:T_truth_etaP1:T_truth_etaN1:T_truth_etaN2:T_truth_etaN3:T_truth_etaN4:T_truth_etaN5:T_truth_etaN6:T_truth_etaP6_eff:T_truth_etaP5_eff:T_truth_etaP4_eff:T_truth_etaP3_eff:T_truth_etaP2_eff:T_truth_etaP1_eff:T_truth_etaN1_eff:T_truth_etaN2_eff:T_truth_etaN3_eff:T_truth_etaN4_eff:T_truth_etaN5_eff:T_truth_etaN6_eff:H_recMC_etaP5:H_recMC_etaP4:H_recMC_etaP3:H_recMC_etaP2:H_recMC_etaP1:H_recMC_etaN1:H_recMC_etaN2:H_recMC_etaN3:H_recMC_etaN4:H_recMC_etaN5:clustSizeY_etaP6:clustSizeY_etaP5:clustSizeY_etaP4:clustSizeY_etaP3:clustSizeY_etaP2:clustSizeY_etaP1:clustSizeY_etaN1:clustSizeY_etaN2:clustSizeY_etaN3:clustSizeY_etaN4:clustSizeY_etaN5:clustSizeY_etaN6:cluster_counter");
  nd_multProp = new TNtuple("nd_multProp","nd_multProp",
     "digis:clusters:clusters_on_layers:rver_z:failedSizeP5:failedSizeP4:failedSizeP3:failedSizeP2:failedSizeP1:failedSizeN1:failedSizeN2:failedSizeN3:failedSizeN4:failedSizeN5:M:isTrigger_1:isTrigger_2:trackTrigger:track5Trigger:HLT_ZeroBias:HLT_ZeroBias1kHz:HLT_MinBiasPixel_SingleTrack:HLT_MinBiasBSC_OR:HLT_ZeroBiasPixel_SingleTrack:HLT_L1_BscMinBiasOR_BptxPlusORMinus:HLT_HighMultiplicityBSC:HLT_L1_BSC:HLT_L1_BPTX:HLT_L1_BPTX_MinusOnly:HLT_L1_BPTX_PlusOnly:HLT_MinBiasHcal:HLT_BackwardBSC:HLT_ForwardBSC:hf:minBias:bit0:bit3:bit4:bit9:bit34:bit35:bit36:bit37:bit38:bit39:bit40:bit41:bit42:bit43:L1_BptxMinus:L1_BptxPlus:L1_BptxPlusORMinus:L1_BscMinBiasOR_BptxPlusORMinus:numVtx:numEv:procID:T_truth:T_truth_etaP6:T_truth_etaP5:T_truth_etaP4:T_truth_etaP3:T_truth_etaP2:T_truth_etaP1:T_truth_etaN1:T_truth_etaN2:T_truth_etaN3:T_truth_etaN4:T_truth_etaN5:T_truth_etaN6:T_truth_etaP6_eff:T_truth_etaP5_eff:T_truth_etaP4_eff:T_truth_etaP3_eff:T_truth_etaP2_eff:T_truth_etaP1_eff:T_truth_etaN1_eff:T_truth_etaN2_eff:T_truth_etaN3_eff:T_truth_etaN4_eff:T_truth_etaN5_eff:T_truth_etaN6_eff:H_recMC_etaP5:H_recMC_etaP4:H_recMC_etaP3:H_recMC_etaP2:H_recMC_etaP1:H_recMC_etaN1:H_recMC_etaN2:H_recMC_etaN3:H_recMC_etaN4:H_recMC_etaN5:clustSizeY_etaP6:clustSizeY_etaP5:clustSizeY_etaP4:clustSizeY_etaP3:clustSizeY_etaP2:clustSizeY_etaP1:clustSizeY_etaN1:clustSizeY_etaN2:clustSizeY_etaN3:clustSizeY_etaN4:clustSizeY_etaN5:clustSizeY_etaN6:cluster_counter");
  rd_multProp = new TNtuple("rd_multProp","rd_multProp",
     "digis:clusters:clusters_on_layers:rver_z:failedSizeP5:failedSizeP4:failedSizeP3:failedSizeP2:failedSizeP1:failedSizeN1:failedSizeN2:failedSizeN3:failedSizeN4:failedSizeN5:M:isTrigger_1:isTrigger_2:trackTrigger:track5Trigger:HLT_ZeroBias:HLT_ZeroBias1kHz:HLT_MinBiasPixel_SingleTrack:HLT_MinBiasBSC_OR:HLT_ZeroBiasPixel_SingleTrack:HLT_L1_BscMinBiasOR_BptxPlusORMinus:HLT_HighMultiplicityBSC:HLT_L1_BSC:HLT_L1_BPTX:HLT_L1_BPTX_MinusOnly:HLT_L1_BPTX_PlusOnly:HLT_MinBiasHcal:HLT_BackwardBSC:HLT_ForwardBSC:hf:minBias:bit0:bit3:bit4:bit9:bit34:bit35:bit36:bit37:bit38:bit39:bit40:bit41:bit42:bit43:L1_BptxMinus:L1_BptxPlus:L1_BptxPlusORMinus:L1_BscMinBiasOR_BptxPlusORMinus:numVtx:numEv:procID:T_truth:T_truth_etaP6:T_truth_etaP5:T_truth_etaP4:T_truth_etaP3:T_truth_etaP2:T_truth_etaP1:T_truth_etaN1:T_truth_etaN2:T_truth_etaN3:T_truth_etaN4:T_truth_etaN5:T_truth_etaN6:T_truth_etaP6_eff:T_truth_etaP5_eff:T_truth_etaP4_eff:T_truth_etaP3_eff:T_truth_etaP2_eff:T_truth_etaP1_eff:T_truth_etaN1_eff:T_truth_etaN2_eff:T_truth_etaN3_eff:T_truth_etaN4_eff:T_truth_etaN5_eff:T_truth_etaN6_eff:H_recMC_etaP5:H_recMC_etaP4:H_recMC_etaP3:H_recMC_etaP2:H_recMC_etaP1:H_recMC_etaN1:H_recMC_etaN2:H_recMC_etaN3:H_recMC_etaN4:H_recMC_etaN5:clustSizeY_etaP6:clustSizeY_etaP5:clustSizeY_etaP4:clustSizeY_etaP3:clustSizeY_etaP2:clustSizeY_etaP1:clustSizeY_etaN1:clustSizeY_etaN2:clustSizeY_etaN3:clustSizeY_etaN4:clustSizeY_etaN5:clustSizeY_etaN6:cluster_counter");
  multProp_looper = new TNtuple("multProp_looper","multProp_looper",
      "isTrigger_1:isTrigger_2:rver_z:eta:eta_det:phi:eloss:type:M:numVtx:clustSizeY:clustSizeX:length:pixels:cluster_counter:HLT_ZeroBias:HLT_ZeroBias1kHz:HLT_MinBiasPixel_SingleTrack:HLT_MinBiasBSC_OR:HLT_ZeroBiasPixel_SingleTrack:HLT_L1_BscMinBiasOR_BptxPlusORMinus:HLT_HighMultiplicityBSC:HLT_L1_BSC:HLT_L1_BPTX:HLT_L1_BPTX_MinusOnly:HLT_L1_BPTX_PlusOnly:HLT_MinBiasHcal:HLT_BackwardBSC:HLT_ForwardBSC:bit0:bit3:bit4:bit9:bit34:bit35:bit36:bit37:bit38:bit39:bit40:bit41:bit42:bit43:L1_BptxMinus:L1_BptxPlus:L1_BptxPlusORMinus:L1_BscMinBiasOR_BptxPlusORMinus:hf");
  nd_multProp_looper = new TNtuple("nd_multProp_looper","nd_multProp_looper",
      "isTrigger_1:isTrigger_2:rver_z:eta:eta_det:phi:eloss:type:M:numVtx:clustSizeY:clustSizeX:length:pixels:cluster_counter:HLT_ZeroBias:HLT_ZeroBias1kHz:HLT_MinBiasPixel_SingleTrack:HLT_MinBiasBSC_OR:HLT_ZeroBiasPixel_SingleTrack:HLT_L1_BscMinBiasOR_BptxPlusORMinus:HLT_HighMultiplicityBSC:HLT_L1_BSC:HLT_L1_BPTX:HLT_L1_BPTX_MinusOnly:HLT_L1_BPTX_PlusOnly:HLT_MinBiasHcal:HLT_BackwardBSC:HLT_ForwardBSC:bit0:bit3:bit4:bit9:bit34:bit35:bit36:bit37:bit38:bit39:bit40:bit41:bit42:bit43:L1_BptxMinus:L1_BptxPlus:L1_BptxPlusORMinus:L1_BscMinBiasOR_BptxPlusORMinus:hf");
  rd_multProp_looper = new TNtuple("rd_multProp_looper","rd_multProp_looper",
      "isTrigger_1:isTrigger_2:rver_z:eta:eta_det:phi:eloss:type:M:numVtx:clustSizeY:clustSizeX:length:pixels:cluster_counter:HLT_ZeroBias:HLT_ZeroBias1kHz:HLT_MinBiasPixel_SingleTrack:HLT_MinBiasBSC_OR:HLT_ZeroBiasPixel_SingleTrack:HLT_L1_BscMinBiasOR_BptxPlusORMinus:HLT_HighMultiplicityBSC:HLT_L1_BSC:HLT_L1_BPTX:HLT_L1_BPTX_MinusOnly:HLT_L1_BPTX_PlusOnly:HLT_MinBiasHcal:HLT_BackwardBSC:HLT_ForwardBSC:bit0:bit3:bit4:bit9:bit34:bit35:bit36:bit37:bit38:bit39:bit40:bit41:bit42:bit43:L1_BptxMinus:L1_BptxPlus:L1_BptxPlusORMinus:L1_BscMinBiasOR_BptxPlusORMinus:hf");
  hPabsTof = new TNtuple("hPabsTof","hPabsTof",
      "pabs:tof");
  nd_hPabsTof = new TNtuple("nd_hPabsTof","nd_hPabsTof",
      "pabs:tof");
  rd_hPabsTof = new TNtuple("rd_hPabsTof","rd_hPabsTof",
      "pabs:tof");
  hLooperPt = new TH1D("hLooperPt","hLooperPt",100,0.,5.);
  hPt = new TH1D("hPt","hPt",100,0.,5.);
  hNonLooperPt = new TH1D("hNonLooperPt","hNonLooperPt",100,0.,5.);
//  hProba = new TH1D("hProba","hProba",10000,0.,1000.);
  hJustLooper = new TNtuple("hJustLooper","hJustLooper","rver_z:eloss:eta:M:numVtx:clustSizeY:cluster_counter");
  nd_hJustLooper = new TNtuple("nd_hJustLooper","nd_hJustLooper","rver_z:eloss:eta:M:numVtx:clustSizeY:cluster_counter");
  rd_hJustLooper = new TNtuple("rd_hJustLooper","rd_hJustLooper","rver_z:eloss:eta:M:numVtx:clustSizeY:cluster_counter");
  hLastTOF = new TH1D("hLastTOF","hLastTOF",200,0.,40.);

  //check eta
  NCheckEta = new TNtuple("NCheckEta","NCheckEta",
     "adc:eta:eta_corr:above_eta:above_eta_corr");

  //cluster vertices
  nCLusterVertices = new TNtuple("nCLusterVertices","nCLusterVertices",
     "numRecHits_l1:sver_z:rver_z");
  nClusterPrim = new TNtuple("nClusterPrim","nClusterPrim",
     "eta_corr:sizeY");
  nClusterAll = new TNtuple("nClusterAll","nClusterAll",
     "eta_corr:sizeY");
  nClusterUnused = new TNtuple("nClusterUnused","nClusterUnused",
     "eta_corr:sizeY");
  hCorrEtaSizeY = new TH2F("hCorrEtaSizeY","hCorrEtaSizeY",300,-3.,3.,20,0.,20.);
  hCorrEtaADC = new TH2F("hCorrEtaADC","hCorrEtaADC",300,-3.,3.,125,0.,2500.);
  hClusterZSizeY = new TH2F("hClusterZSizeY","hClusterZSizeY",600,-30.,30.,200,0.,20.);
  ResPureClusterY = new TH1F("ResPureClusterY","ResPureClusterY",60,0.,30.);
  ResSimRecClusterY = new TH1F("ResSimRecClusterY","ResSimRecClusterY",60,0.,30.);
  ResElseSimRecClusterY = new TH1F("ResElseSimRecClusterY","ResElseSimRecClusterY",60,0.,30.);

  //decay
  NDecay = new TNtuple("NDecay","NDecay",
     "decayCounter:num_weaks:decayHits_etaP6:decayHits_etaP5:decayHits_etaP4:decayHits_etaP3:decayHits_etaP2:decayHits_etaP1:decayHits_etaN1:decayHits_etaN2:decayHits_etaN3:decayHits_etaN4:decayHits_etaN5:decayHits_etaN6:cluster_counter");
  nd_NDecay = new TNtuple("nd_NDecay","nd_NDecay",
     "decayCounter:num_weaks:decayHits_etaP6:decayHits_etaP5:decayHits_etaP4:decayHits_etaP3:decayHits_etaP2:decayHits_etaP1:decayHits_etaN1:decayHits_etaN2:decayHits_etaN3:decayHits_etaN4:decayHits_etaN5:decayHits_etaN6:cluster_counter");
  rd_NDecay = new TNtuple("rd_NDecay","rd_NDecay",
     "decayCounter:num_weaks:decayHits_etaP6:decayHits_etaP5:decayHits_etaP4:decayHits_etaP3:decayHits_etaP2:decayHits_etaP1:decayHits_etaN1:decayHits_etaN2:decayHits_etaN3:decayHits_etaN4:decayHits_etaN5:decayHits_etaN6:cluster_counter");
  NDecayInfo = new TNtuple("NDecayInfo","NDecayInfo","parentID:ID");

  // interaction
  NInter = new TNtuple("NInter","NInter",
     "interHits_etaP6:interHits_etaP5:interHits_etaP4:interHits_etaP3:interHits_etaP2:interHits_etaP1:interHits_etaN1:interHits_etaN2:interHits_etaN3:interHits_etaN4:interHits_etaN5:interHits_etaN6:cluster_counter");
  nd_NInter = new TNtuple("nd_NInter","nd_NInter",
     "interHits_etaP6:interHits_etaP5:interHits_etaP4:interHits_etaP3:interHits_etaP2:interHits_etaP1:interHits_etaN1:interHits_etaN2:interHits_etaN3:interHits_etaN4:interHits_etaN5:interHits_etaN6:cluster_counter");
  rd_NInter = new TNtuple("rd_NInter","rd_NInter",
     "interHits_etaP6:interHits_etaP5:interHits_etaP4:interHits_etaP3:interHits_etaP2:interHits_etaP1:interHits_etaN1:interHits_etaN2:interHits_etaN3:interHits_etaN4:interHits_etaN5:interHits_etaN6:cluster_counter");

  // below the cut
  NBelow = new TNtuple("NBelow","NBelow",
     "belowHits_etaP6:belowHits_etaP5:belowHits_etaP4:belowHits_etaP3:belowHits_etaP2:belowHits_etaP1:belowHits_etaN1:belowHits_etaN2:belowHits_etaN3:belowHits_etaN4:belowHits_etaN5:belowHits_etaN6:cluster_counter");
  nd_NBelow = new TNtuple("nd_NBelow","nd_NBelow",
     "belowHits_etaP6:belowHits_etaP5:belowHits_etaP4:belowHits_etaP3:belowHits_etaP2:belowHits_etaP1:belowHits_etaN1:belowHits_etaN2:belowHits_etaN3:belowHits_etaN4:belowHits_etaN5:belowHits_etaN6:cluster_counter");
  rd_NBelow = new TNtuple("rd_NBelow","rd_NBelow",
     "belowHits_etaP6:belowHits_etaP5:belowHits_etaP4:belowHits_etaP3:belowHits_etaP2:belowHits_etaP1:belowHits_etaN1:belowHits_etaN2:belowHits_etaN3:belowHits_etaN4:belowHits_etaN5:belowHits_etaN6:cluster_counter");

  // geo
  NGeo = new TNtuple("NGeo","NGeo",
     "geoHits_etaP6:geoHits_etaP5:geoHits_etaP4:geoHits_etaP3:geoHits_etaP2:geoHits_etaP1:geoHits_etaN1:geoHits_etaN2:geoHits_etaN3:geoHits_etaN4:geoHits_etaN5:geoHits_etaN6:cluster_counter");
  nd_NGeo = new TNtuple("nd_NGeo","nd_NGeo",
     "geoHits_etaP6:geoHits_etaP5:geoHits_etaP4:geoHits_etaP3:geoHits_etaP2:geoHits_etaP1:geoHits_etaN1:geoHits_etaN2:geoHits_etaN3:geoHits_etaN4:geoHits_etaN5:geoHits_etaN6:cluster_counter");
  rd_NGeo = new TNtuple("rd_NGeo","rd_NGeo",
     "geoHits_etaP6:geoHits_etaP5:geoHits_etaP4:geoHits_etaP3:geoHits_etaP2:geoHits_etaP1:geoHits_etaN1:geoHits_etaN2:geoHits_etaN3:geoHits_etaN4:geoHits_etaN5:geoHits_etaN6:cluster_counter");

  NLooper = new TNtuple("NLooper","NLooper",
     "looperHits_etaP6:looperHits_etaP5:looperHits_etaP4:looperHits_etaP3:looperHits_etaP2:looperHits_etaP1:looperHits_etaN1:looperHits_etaN2:looperHits_etaN3:looperHits_etaN4:looperHits_etaN5:looperHits_etaN6:cluster_counter");
  nd_NLooper = new TNtuple("nd_NLooper","nd_NLooper",
     "looperHits_etaP6:looperHits_etaP5:looperHits_etaP4:looperHits_etaP3:looperHits_etaP2:looperHits_etaP1:looperHits_etaN1:looperHits_etaN2:looperHits_etaN3:looperHits_etaN4:looperHits_etaN5:looperHits_etaN6:cluster_counter");
  rd_NLooper = new TNtuple("rd_NLooper","rd_NLooper",
     "looperHits_etaP6:looperHits_etaP5:looperHits_etaP4:looperHits_etaP3:looperHits_etaP2:looperHits_etaP1:looperHits_etaN1:looperHits_etaN2:looperHits_etaN3:looperHits_etaN4:looperHits_etaN5:looperHits_etaN6:cluster_counter");
  NStrange = new TNtuple("NStrange","NStrange",
     "strangeHits_etaP6:strangeHits_etaP5:strangeHits_etaP4:strangeHits_etaP3:strangeHits_etaP2:strangeHits_etaP1:strangeHits_etaN1:strangeHits_etaN2:strangeHits_etaN3:strangeHits_etaN4:strangeHits_etaN5:strangeHits_etaN6:cluster_counter");
  nd_NStrange = new TNtuple("nd_NStrange","nd_NStrange",
     "strangeHits_etaP6:strangeHits_etaP5:strangeHits_etaP4:strangeHits_etaP3:strangeHits_etaP2:strangeHits_etaP1:strangeHits_etaN1:strangeHits_etaN2:strangeHits_etaN3:strangeHits_etaN4:strangeHits_etaN5:strangeHits_etaN6:cluster_counter");
  rd_NStrange = new TNtuple("rd_NStrange","rd_NStrange",
     "strangeHits_etaP6:strangeHits_etaP5:strangeHits_etaP4:strangeHits_etaP3:strangeHits_etaP2:strangeHits_etaP1:strangeHits_etaN1:strangeHits_etaN2:strangeHits_etaN3:strangeHits_etaN4:strangeHits_etaN5:strangeHits_etaN6:cluster_counter");
  NHitAssoc = new TNtuple("NHitAssoc","NHitAssoc","dist_3D:dist_z");

  hClusterEta_1_7 = new TH1F("hClusterEta_1_7","hClusterEta_1_7",28,-7.,7.);
  hClusterEta_8_13 = new TH1F("hClusterEta_8_13","hClusterEta_8_13",28,-7.,7.);
  hClusterEta_14_20 = new TH1F("hClusterEta_14_20","hClusterEta_14_20",28,-7.,7.);
  hClusterEta_21_31 = new TH1F("hClusterEta_21_31","hClusterEta_21_31",28,-7.,7.);
  hClusterEta_32_52 = new TH1F("hClusterEta_32_52","hClusterEta_32_52",28,-7.,7.);
  hClusterEta_53_499 = new TH1F("hClusterEta_53_499","hClusterEta_53_499",28,-7.,7.);

  hTestEtaFull = new TH1D("hTestEtaFull","hTestEtaFull",14,-3.5,3.5);
  hTestEtaFullV = new TH1D("hTestEtaFullV","hTestEtaFullV",14,-3.5,3.5);
  hTest_nd = new TH1D("hTest_nd","hTest_nd",14,-3.5,3.5);
  hTest_nsd = new TH1D("hTest_nsd","hTest_nsd",14,-3.5,3.5);
  hTest_nsd_trig = new TH1D("hTest_nsd_trig","hTest_nsd_trig",14,-3.5,3.5);
  hTest_sd_trig = new TH1D("hTest_sd_trig","hTest_sd_trig",14,-3.5,3.5);
  hTest_nd_counter = new TH1D("hTest_nd_counter","hTest_nd_counter",14,-3.5,3.5);
  hTest_sd_1 = new TH1D("hTest_sd_1","hTest_sd_1",14,-3.5,3.5);
  hTest_sd_1_counter = new TH1D("hTest_sd_1_counter","hTest_sd_1_counter",14,-3.5,3.5);
  hTest_sd_2 = new TH1D("hTest_sd_2","hTest_sd_2",14,-3.5,3.5);
  hTest_sd_2_counter = new TH1D("hTest_sd_2_counter","hTest_sd_2_counter",14,-3.5,3.5);
  hTest_dd = new TH1D("hTest_dd","hTest_dd",14,-3.5,3.5);
  hTest_dd_counter = new TH1D("hTest_dd_counter","hTest_dd_counter",14,-3.5,3.5);
  hTestEtaRestricted_10 = new TH1D("hTestEtaRestricted_10","hTestEtaRestricted_10",14,-3.5,3.5);
  hTestEta_1_8 = new TH1D("hTestEta_1_8","hTestEta_1_8",28,-7.,7.);
  hTestEta_9_15 = new TH1D("hTestEta_9_15","hTestEta_9_15",28,-7.,7.);
  hTestEta_16_23 = new TH1D("hTestEta_16_23","hTestEta_16_23",28,-7.,7.);
  hTestEta_24_36 = new TH1D("hTestEta_24_36","hTestEta_24_36",28,-7.,7.);
  hTestEta_37_58 = new TH1D("hTestEta_37_58","hTestEta_37_58",28,-7.,7.);
  hTestEta_59_499 = new TH1D("hTestEta_59_499","hTestEta_59_499",28,-7.,7.);

  hTestEtaRestricted = new TH1D("hTestEtaRestricted","hTestEtaRestricted",14,-3.5,3.5);
  hTestEtaRestricted_1 = new TH1D("hTestEtaRestricted_1","hTestEtaRestricted_1",14,-3.5,3.5);
  hTestEtaRestrictedV = new TH1D("hTestEtaRestrictedV","hTestEtaRestrictedV",14,-3.5,3.5);

  full = 0;
  fullV = 0;
  restricted = 0;
  restrictedV = 0;
  num_nd = 0;
  num_nsd = 0;
  num_nd_counter = 0;
  num_sd_1 = 0;
  num_sd_1_counter = 0;
  num_sd_2 = 0;
  num_sd_2_counter = 0;
  num_dd = 0;
  num_dd_counter = 0;
  num_10 = 0;
  num_1_8 = 0;
  num_9_15 = 0; 
  num_16_23 = 0; 
  num_24_36 = 0; 
  num_37_58 = 0; 
  num_59_499 = 0; 
  // cluster
  num_cluster_1_7 = 0;
  num_cluster_8_13 = 0; 
  num_cluster_14_20 = 0; 
  num_cluster_21_31 = 0; 
  num_cluster_32_52 = 0; 
  num_cluster_53_499 = 0; 

  PureCorrEta = new TH1F("PureCorrEta","PureCorrEta",30,-3.,3.);
  PureCutCorrEta = new TH1F("PureCutCorrEta","PureCutCorrEta",30,-3.,3.);
  DesiredEtaDist = new TH1F("DesiredEtaDist","DesiredEtaDist",30,-3.,3.);
  FeriDesiredEta = new TH1F("FeriDesiredEta","FeriDesiredEta",30,-3.,3.);
  SimRecCorrEta = new TH1F("SimRecCorrEta","SimRecCorrEta",30,-3.,3.);
  RecAdc = new TH1F("RecAdc","RecAdc",2550,0.,2550.);
  ResCentralAdc = new TH1F("ResCentralAdc","ResCentralAdc",50,0.,2550.);
  ResCentralAdcFine = new TH1F("ResCentralAdcFine","ResCentralAdcFine",50,0.,500.);
  ResElseCentralAdc = new TH1F("ResElseCentralAdc","ResElseCentralAdc",50,0.,2550.);
  ResPureAdc = new TH1F("ResPureAdc","ResPureAdc",50,0.,2550.);
  ResPureAdc_det = new TH1F("ResPureAdc_det","ResPureAdc_det",50,0.,2550.);
  ResPureCentralAdc = new TH1F("ResPureCentralAdc","ResPureCentralAdc",50,0.,2550.);
  ResPureCutAdc = new TH1F("ResPureCutAdc","ResPureCutAdc",50,0.,2550.);
  ResPureCutCentralAdc = new TH1F("ResPureCutCentralAdc","ResPureCutCentralAdc",50,0.,2550.);

  SimEnergyLoss = new TH1F("SimEnergyLoss","SimEnergyLoss",200,0.,0.003);
  RecAdcvsCorrEta = new TH2F("RecAdcvsCorrEta","RecAdcvsCorrEta",300,-3.,3.,25500,0.,2550.);
  SimRecAdcvsCorrEta = new TH2F("SimRecAdcvsCorrEta","SimRecAdcvsCorrEta",300,-3.,3.,2550,0.,2550.);
  ResSimRecAdc = new TH1F("ResSimRecAdc","ResSimRecAdc",50,0.,2550.);
  ResSimRecAdc_det = new TH1F("ResSimRecAdc_det","ResSimRecAdc_det",50,0.,2550.);
  ResSimRecAdcFine = new TH1F("ResSimRecAdcFine","ResSimRecAdcFine",80,0.,800.);
  ResSimRecAdcLog = new TH1F("ResSimRecAdcLog","ResSimRecAdcLog",50,3.,10.);
  FullResSimAdc = new TH1F("FullResSimAdc","FullResSimAdc",50,0.,2550.);
  ElseSimRecAdcvsCorrEta = new TH2F("ElseSimRecAdcvsCorrEta","ElseSimRecAdcvsCorrEta",300,-3.,3.,25500,0.,2550.);
  ResElseSimRecAdc = new TH1F("ResElseSimRecAdc","ResElseSimRecAdc",50,0.,2550.);
  ResElseSimRecAdc_det = new TH1F("ResElseSimRecAdc_det","ResElseSimRecAdc_det",50,0.,2550.);
  PureAdcvsCorrEta = new TH2F("PureAdcvsCorrEta","PureAdcvsCorrEta",300,-3.,3.,2550,0.,2550.);
  PureCutAdcvsCorrEta = new TH2F("PureCutAdcvsCorrEta","PureCutAdcvsCorrEta",300,-3.,3.,25000,0.,2550.);
  hAdcPerCoshCorrEta = new TH2F("hAdcPerCoshCorrEta","hAdcPerCoshCorrEta",300,-3.,3.,25500,0.,2550.);

  nEvents = 0;
  test = 0;
  proba = 0;
  nrv = 0;

}

/*****************************************************************************/
void ChargedMultiplicityAnalyzer_new::endJob()
{
  TDirectory::TContext context(resultFile);

//  nMagField->Write();

  hNum_nd->Write();
  hNum_nsd->Write();
  hNum_nsd_trig->Write();
  hNum_sd_trig->Write();
  verticesInfo->Write();
//  multi->Write();
//  looper->Write();
  multProp->Write();
  nd_multProp->Write();
  rd_multProp->Write();
  multProp_looper->Write();
  nd_multProp_looper->Write();
  rd_multProp_looper->Write();
//  hPabsTof->Write();
//  nd_hPabsTof->Write();
//  rd_hPabsTof->Write();
//  hLooperPt->Write();
//  hPt->Write();
//  hNonLooperPt->Write();
//  hProba->Write();
  hJustLooper->Write();
  nd_hJustLooper->Write();
  rd_hJustLooper->Write();
//  hLastTOF->Write();

//  NCheckEta->Write();
  //clusters
//  nCLusterVertices->Write();
//  nClusterPrim->Write();
//  nClusterAll->Write();
//  nClusterUnused->Write();
  hCorrEtaSizeY->Write();
  hCorrEtaADC->Write();
  hClusterZSizeY->Write();
//  ResPureClusterY->Write();
//  ResSimRecClusterY->Write();
//  ResElseSimRecClusterY->Write();
  hClusterEta_1_7->Write();
  hClusterEta_8_13->Write();
  hClusterEta_14_20->Write();
  hClusterEta_21_31->Write();
  hClusterEta_32_52->Write();
  hClusterEta_53_499->Write();

  //decay
  NDecay->Write();
  nd_NDecay->Write();
  rd_NDecay->Write();
  NDecayInfo->Write();

  // interactions
  NInter->Write();
  nd_NInter->Write();
  rd_NInter->Write();

  // below the cut
  NBelow->Write();
  nd_NBelow->Write();
  rd_NBelow->Write();

  // geo
  NGeo->Write();
  nd_NGeo->Write();
  rd_NGeo->Write();

  NLooper->Write();
  nd_NLooper->Write();
  rd_NLooper->Write();
  NStrange->Write();
  nd_NStrange->Write();
  rd_NStrange->Write();
  NHitAssoc->Write();

  hTestEtaFull->Write();
  hTestEtaFullV->Write();
  hTestEtaRestricted->Write();
  hTestEtaRestricted_1->Write();
  hTestEtaRestrictedV->Write();
  hTest_nd->Write();
  hTest_nsd->Write();
  hTest_nsd_trig->Write();
  hTest_sd_trig->Write();
  hTest_nd_counter->Write();
  hTest_sd_1->Write();
  hTest_sd_1_counter->Write();
  hTest_sd_2->Write();
  hTest_sd_2_counter->Write();
  hTest_dd->Write();
  hTest_dd_counter->Write();
  hTestEtaRestricted_10->Write();
  hTestEta_1_8->Write();
  hTestEta_9_15->Write();
  hTestEta_16_23->Write();
  hTestEta_24_36->Write();
  hTestEta_37_58->Write();
  hTestEta_59_499->Write();

  PureCorrEta->Write();
  PureCutCorrEta->Write();
  DesiredEtaDist->Write();
//  FeriDesiredEta->Write();
  SimRecCorrEta->Write();
  RecAdc->Write();
  ResCentralAdc->Write();
  ResCentralAdcFine->Write();
  ResElseCentralAdc->Write();
  ResPureAdc->Write();
  ResPureAdc_det->Write();
  ResPureCentralAdc->Write();
  ResPureCutAdc->Write();
  ResPureCutCentralAdc->Write();

//  SimEnergyLoss->Write();
  RecAdcvsCorrEta->Write();
  SimRecAdcvsCorrEta->Write();
  ResSimRecAdc->Write();
  ResSimRecAdc_det->Write();
  ResSimRecAdcFine->Write();
  ResSimRecAdcLog->Write();
  FullResSimAdc->Write();
  ElseSimRecAdcvsCorrEta->Write();
  ResElseSimRecAdc->Write();
  ResElseSimRecAdc_det->Write();
  PureAdcvsCorrEta->Write();
  PureCutAdcvsCorrEta->Write();
  hAdcPerCoshCorrEta->Write();

  resultFile->Close();
  delete resultFile;

  cerr<<"We had "<<nEvents<<" number of events with 1 vertex"<<endl;
  cerr<<"Test the number of events: filling RecCut: "<<test<<endl;
  cerr<<"Test the number of events: filling SimPrim: "<<proba<<endl;
  cerr<<"I found " << nrv <<" reconstructed single vertex" <<endl;
  cerr<<"FULL: "<<full<<endl;
  cerr<<"FULLV: "<<fullV<<endl;
  cerr<<"RESTRICTED: "<<restricted<<endl;
  cerr<<"RESTRICTEDV: "<<restrictedV<<endl;
  cerr<<"num_nd: "<<num_nd<<endl;
  cerr<<"num_nd_counter: "<<num_nd_counter<<endl;
  cerr<<"num_sd_1: "<<num_sd_1<<endl;
  cerr<<"num_sd_1_counter: "<<num_sd_1_counter<<endl;
  cerr<<"num_sd_2: "<<num_sd_2<<endl;
  cerr<<"num_sd_2_counter: "<<num_sd_2_counter<<endl;
  cerr<<"num_dd: "<<num_dd<<endl;
  cerr<<"num_dd_counter: "<<num_dd_counter<<endl;
  cerr<<"num_10: "<<num_10<<endl;
  cerr<<"num_1_8: "<<num_1_8<<endl;
  cerr<<"num_9_15: "<<num_9_15<<endl;
  cerr<<"num_16_23: "<<num_16_23<<endl;
  cerr<<"num_24_36: "<<num_24_36<<endl;
  cerr<<"num_37_58: "<<num_37_58<<endl;
  cerr<<"num_59_499: "<<num_59_499<<endl;
  cerr<<" CLUSTERS -STARTS-"<< endl;
  cerr<<"num_cluster_1_7: "<<num_cluster_1_7<<endl;
  cerr<<"num_cluster_8_13: "<<num_cluster_8_13<<endl;
  cerr<<"num_cluster_14_20: "<<num_cluster_14_20<<endl;
  cerr<<"num_cluster_21_31: "<<num_cluster_21_31<<endl;
  cerr<<"num_cluster_32_52: "<<num_cluster_32_52<<endl;
  cerr<<"num_cluster_53_499: "<<num_cluster_53_499<<endl;
  cerr<<" CLUSTERS -FINISHED-"<< endl;

}

/*****************************************************************************/
float ChargedMultiplicityAnalyzer_new::getVertexZ
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
int ChargedMultiplicityAnalyzer_new::getContainedHits
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
float ChargedMultiplicityAnalyzer_new::produceClusterVertex
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
void ChargedMultiplicityAnalyzer_new::clusterVertices
    (const edm::Event& ev, const edm::EventSetup& es,
//     const reco::VertexCollection* vertices,
     edm::Handle<SiPixelRecHitCollection> siPixelRecCollection)
{
  edm::Handle<edm::SimVertexContainer> simVertices;
  ev.getByType(                        simVertices);

  float sver_z = 0;
  if((*(simVertices.product())).size() > 0)
    sver_z = (*(simVertices.product())).at(0).position().z();

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
  result.push_back(sver_z);
  result.push_back(rver_z);
  nCLusterVertices->Fill(&result[0]);

}

/*****************************************************************************/
bool ChargedMultiplicityAnalyzer_new::aboveTriggerThreshold_1(edm::Handle<CaloTowerCollection> towers)
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
bool ChargedMultiplicityAnalyzer_new::aboveTriggerThreshold_2(edm::Handle<CaloTowerCollection> towers)
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
bool ChargedMultiplicityAnalyzer_new::trackTrigger(edm::Handle<reco::TrackCollection>& recCollection)
{
  int tracks = recCollection.product()->size();
  if(tracks>0)
    return true;
  else
    return false;
}

/*****************************************************************************/
bool ChargedMultiplicityAnalyzer_new::track5Trigger(edm::Handle<reco::TrackCollection>& recCollection)
{
  int tracks = recCollection.product()->size();
  if(tracks>4)
    return true;
  else
    return false;
}

/*****************************************************************************/
bool ChargedMultiplicityAnalyzer_new::ChristofMinBias(const edm::Event& event, const edm::EventSetup& eventSetup)
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
bool ChargedMultiplicityAnalyzer_new::RichardMinBias(Handle<HcalTrigPrimDigiCollection>& tpg)
{
  bool pos = false;
  bool neg = false; 
  double tpg_et = 0.;
//  std::cerr<<"@@@@ tpg->size(): "<< tpg->size() << std::endl;
  for(HcalTrigPrimDigiCollection::const_iterator tpg_iter = tpg->begin(); tpg_iter != tpg->end(); ++tpg_iter) {
    tpg_et = double(tpg_iter->SOI_compressedEt());//this is the trig.tow

    if(TMath::Abs(tpg_iter->id().ieta())>=29.) {
      if(tpg_et>=2.)
        pos = true;
    }

    if(tpg_iter->id().ieta()<=-29.) {
      if(tpg_et>=2.)
        neg = true;
    }
  }
  if(neg && pos)
    return true;
  else
    return false;
}

/*****************************************************************************/
bool ChargedMultiplicityAnalyzer_new::isRecHitAtTheEdge(SiPixelRecHitCollection::DataContainer::const_iterator iPRH,
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
//       cerr<<"XXXX At the EDGE"<<endl;
     }
  }
  return isAnyPixelAtEdge;
}

/*****************************************************************************/
void ChargedMultiplicityAnalyzer_new::FirstSimOnFirst(edm::Handle<SiPixelRecHitCollection>& siPixelRecCollection,
//                                                  const reco::VertexCollection* vertices,
                                                  const edm::Event& ev,
                                                  const edm::EventSetup& es)
{
//  std::cerr<<"ChargedMultiplicityAnalyzer_new::FirstSimOnFirst(1)"<<std::endl;

  // Get simulated
  edm::Handle<TrackingParticleCollection> simCollection;
//  ev.getByType(simCollection);
  ev.getByLabel("mergedtruth","MergedTrackTruth",simCollection);

  const TrackingParticleCollection *tPC = simCollection.product();

//  int numrvertices = vertices->size();

//  if(numrvertices!=1)
//    return;

  // get vertex_z
  float rver_z = getVertexZ(siPixelRecCollection, ev);
/*
  if(numrvertices==1)  {
     reco::VertexCollection::const_iterator vertex = vertices->begin();
     rver_z = vertex->z();
     nEvents++;
  }
*/
  TrackerHitAssociator simHitFinder(ev);
  edm::ESHandle<TrackerGeometry> geom;
  es.get<TrackerDigiGeometryRecord>().get(geom);  
  const SiPixelRecHitCollection pixelRecHits = *(siPixelRecCollection.product());
  std::vector<std::vector<const SiPixelRecHit*> > tpRecHitsVectorVector;

  bool isPrim = false;
//  std::cerr<<"ChargedMultiplicityAnalyzer_new::FirstSimOnFirst(2)"<<std::endl;
  // Loop through the TrackingParticles
  for(TrackingParticleCollection::const_iterator t = tPC->begin(); t != tPC->end(); ++t) {
     std::vector<const SiPixelRecHit*> tpRecHitVector;

        if(t->trackPSimHit().size() == 0)
          continue;
        std::vector<PSimHit> TP_pSHV = t->trackPSimHit();
        PSimHit* earliestSH = findEarliestPSimHit(TP_pSHV);

        const PixelGeomDetUnit* pgdu = dynamic_cast<const PixelGeomDetUnit*>(geom->idToDetUnit(earliestSH->detUnitId()));   //tp_psh
        if(pgdu==0)
          continue;
        PXBDetId pdetId = PXBDetId(earliestSH->detUnitId());  //tp_psh
        int layer=pdetId.layer();

        // Selection based on proccess type and first barrel layer
        // First step
        // Primary, first pixel barrel
        if(earliestSH->processType()==2 && layer == 1 && (pgdu->subDetector() == GeomDetEnumerators::PixelBarrel)) {  //tp_psh

           // Loop through all recHits and find the associated simHits
           for(SiPixelRecHitCollection::DataContainer::const_iterator iPRH = pixelRecHits.data().begin(); iPRH != pixelRecHits.data().end(); ++iPRH ) {
//std::cerr<<"ChargedMultiplicityAnalyzer_new::FirstSimOnFirst(3)"<<std::endl;
            std::vector<PSimHit> associatedSimHits = simHitFinder.associateHit(*iPRH);
//std::cerr<<"ChargedMultiplicityAnalyzer_new::FirstSimOnFirst(4)"<<std::endl;

              // Loop through the associated simHits, find the one we had before
              float energy_loss = 0.;
              for(std::vector<PSimHit>::const_iterator aSH = associatedSimHits.begin(); aSH != associatedSimHits.end(); aSH++ ) {
                 energy_loss += aSH->energyLoss();
                 if(comparePSimHits(&(*earliestSH), &(*aSH)) ) {   //tp_psh
                     bool alreadyStoredRecHit = false;

                     // Cycle through the RecHits stored in the vector, making sure it hasn't already been added
                     for(std::vector<const SiPixelRecHit*>::const_iterator tpRHV = tpRecHitVector.begin(); tpRHV != tpRecHitVector.end(); ++tpRHV ) {
                         if(compareRecHits((*tpRHV), &(*iPRH)))
                             alreadyStoredRecHit = true;
                     }

                     if(!alreadyStoredRecHit) {
                       tpRecHitVector.push_back(&(*iPRH));
                       // Fill eta vs ADC of primary non-loopers
                       const PixelGeomDetUnit* pgdu = dynamic_cast<const PixelGeomDetUnit*>(geom->idToDetUnit((*iPRH).geographicalId()));
                       GlobalPoint globalPosition = pgdu->toGlobal((*iPRH).localPosition());
                       float z = globalPosition.z();
                       float x = fabs(globalPosition.x() - theBeamSpot->position().x());
                       float y = fabs(globalPosition.y() - theBeamSpot->position().y());
                       float R = TMath::Sqrt(x*x + y*y);
                       float det_eta = globalPosition.eta();
                       float eta_corr = -999.;
                       eta_corr = -log(tan(atan2(R,(z-rver_z))/2.));
                       float ccharge = (*iPRH).cluster()->charge();
                       float adc = ccharge/135.;
                       //Is the recHit at the edge of the detector?
                       bool isAnyPixelAtEdge = isRecHitAtTheEdge(iPRH,pgdu);
//                       cerr<<"XXXX EdgeCheck"<<endl;
                       DesiredEtaDist->Fill(eta_corr); 
                       isPrim = true;
                       if(!isAnyPixelAtEdge) {
                         SimRecAdcvsCorrEta->Fill(eta_corr,adc);
                         SimRecCorrEta->Fill(eta_corr);
                         float adcpercorreta = adc/cosh(eta_corr);
                         hAdcPerCoshCorrEta->Fill(eta_corr,adcpercorreta);
                         // cluster inf.
                         vector<float> clustPrim;
                         clustPrim.push_back(eta_corr);  //eta
                         clustPrim.push_back((iPRH)->cluster()->sizeY());  //sizeY
                         nClusterPrim->Fill(&clustPrim[0]);
                         if(eta_corr<2.1 && eta_corr>1.9) {
                           ResSimRecAdc->Fill(adc);
                           ResSimRecClusterY->Fill((iPRH)->cluster()->sizeY());
                           ResSimRecAdcFine->Fill(adc);
                           ResSimRecAdcLog->Fill(log(adc));
//                           if(adc<400)
//                             cerr<<"XXXX Too low ADC!! problem?"<<endl;
                         }
                         if(det_eta<2.1 && det_eta>1.9)  //Just a test: what happens if we don't correct the eta
                           ResSimRecAdc_det->Fill(adc);
                         if(eta_corr<0.1 && eta_corr>-0.1) {
                           ResCentralAdc->Fill(adc);
                           ResCentralAdcFine->Fill(adc);
                         }
                       }
                       if(eta_corr<2.1 && eta_corr>1.9)
                         FullResSimAdc->Fill(adc);
                       break;
                     }

                 }
              }
              SimEnergyLoss->Fill(energy_loss);
           }
        }

     tpRecHitsVectorVector.push_back(tpRecHitVector);
  }

  // Check all and unused RecHits
  bool isRecHit = false;
  for(SiPixelRecHitCollection::DataContainer::const_iterator iPRH = pixelRecHits.data().begin(); iPRH != pixelRecHits.data().end(); ++iPRH) {
      bool recHitUsed = false;
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
            isRecHit = true;
            PureCutCorrEta->Fill(eta_corr);
            PureCutAdcvsCorrEta->Fill(eta_corr,adc);
         }
         // cluster , all
         vector<float> clustAll;
         clustAll.push_back(eta_corr);
         clustAll.push_back((iPRH)->cluster()->sizeY());
         nClusterAll->Fill(&clustAll[0]);
         // pixel size in y direction vs eta_corr
         hCorrEtaSizeY->Fill(eta_corr,(iPRH)->cluster()->sizeY());
         hCorrEtaADC->Fill(eta_corr,adc);
         hClusterZSizeY->Fill(z,(iPRH)->cluster()->sizeY());
         // partial distributions
         if(eta_corr<0.1 && eta_corr>-0.1)
            ResPureCentralAdc->Fill(adc);
         if(eta_corr<0.1 && eta_corr>-0.1 && ((130.*cosh(eta_corr)-33.)<adc)) //cut
            ResPureCutCentralAdc->Fill(adc);
         if(eta_corr<2.1 && eta_corr>1.9) {
            ResPureAdc->Fill(adc);
            ResPureClusterY->Fill((iPRH)->cluster()->sizeY());
         }
         if(det_eta<2.1 && det_eta>1.9)  //same as the preceding lines but we use detector eta here
            ResPureAdc_det->Fill(adc);
         if(eta_corr<2.1 && eta_corr>1.9 && ((130.*cosh(eta_corr)-33.)<adc)) //cut
            ResPureCutAdc->Fill(adc);
      }

      for(std::vector<std::vector<const SiPixelRecHit*> >::const_iterator rcV = tpRecHitsVectorVector.begin(); rcV != tpRecHitsVectorVector.end(); ++rcV) {

          for(std::vector<const SiPixelRecHit*>::const_iterator rc = rcV->begin(); rc != rcV->end(); ++rc) {
              if(compareRecHits((*rc), &(*iPRH))) {
                  recHitUsed = true;
              }
          }
      }

      //unused
      if(!recHitUsed ) {
        if(!isAnyPixelAtEdge && layer==1 && (pgdu->subDetector() == GeomDetEnumerators::PixelBarrel))  {  //if first pixel layer 
          ElseSimRecAdcvsCorrEta->Fill(eta_corr,adc);
          // cluster,  unused
          vector<float> clustUnused;
          clustUnused.push_back(eta_corr);
          clustUnused.push_back((iPRH)->cluster()->sizeY());
          nClusterUnused->Fill(&clustUnused[0]);
          if(eta_corr<2.1 && eta_corr>1.9) {
             ResElseSimRecAdc->Fill(adc);
             ResElseSimRecClusterY->Fill((iPRH)->cluster()->sizeY());
          }
          if(det_eta<2.1 && det_eta>1.9)
             ResElseSimRecAdc_det->Fill(adc);  //A test
          if(eta_corr<0.1 && eta_corr>-0.1)
             ResElseCentralAdc->Fill(adc);
        }
      }
  }
  if(isRecHit)
    test++;
  if(isPrim)
    proba++;
}

/*****************************************************************************/
void ChargedMultiplicityAnalyzer_new::checkVertices
  (
//   const reco::VertexCollection* vertices,
   edm::Handle<TrackingVertexCollection>& TVCollection,
   edm::Handle<reco::TrackCollection>& recCollection,
   HepMC::GenEvent * myGenEvent)
{
  //Number of vertices found in the event
  vector<float> result;

  int numrvertices = 666;  
//  int numrvertices = vertices->size();  

  int numsvertices = TVCollection.product()->size();
  int numrectracks = recCollection.product()->size();
  int procID = myGenEvent->signal_process_id();

/*
  int h=1;
  if(numrvertices>1)
    for(reco::VertexCollection::const_iterator vert = vertices->begin(); vert != vertices->end(); vert++, h++) {
       std::cerr<<"Z position of the "<<h<<". vertex: "<< vert->position().z() <<std::endl;
    }
*/
  result.push_back(numrvertices);
  result.push_back(numsvertices);    
  result.push_back(numrectracks);
  result.push_back(procID);

  verticesInfo->Fill(&result[0]);
/* 
  if(vertices->size()==1)
    nrv++;
*/
}

/*****************************************************************************/
PSimHit* ChargedMultiplicityAnalyzer_new::findLatestPSimHit
  (std::vector<PSimHit>& simHits)
{
  PSimHit* latest;
  latest = &(*(simHits.begin()));
  for(std::vector<PSimHit>::iterator simHit = simHits.begin(); simHit != simHits.end(); ++simHit) {
     if(simHit->pabs() < latest->pabs())  {
        latest = &(*simHit);
     }
  }

  return latest;
}

/*****************************************************************************/
PSimHit* ChargedMultiplicityAnalyzer_new::findEarliestPSimHit
  (std::vector<PSimHit>& simHits)
{
  if(simHits.size()<1)
    cerr<<"XXXX There're no simhits here"<<endl;
  PSimHit* earliest;
  earliest = &(*(simHits.begin()));
  int kkk = 0;
  int which_kkk = 0;
  for(std::vector<PSimHit>::iterator simHit = simHits.begin(); simHit != simHits.end(); ++simHit, kkk++) {
     if(simHit->timeOfFlight() < earliest->timeOfFlight())  {
        earliest = &(*simHit);
        which_kkk = kkk;
     }
  }

//test
  PSimHit* frenk;
  frenk = &(*(simHits.begin()));
  int kk = 0;
  int which_kk = 0;
  for(std::vector<PSimHit>::iterator simHit = simHits.begin(); simHit != simHits.end(); ++simHit, kk++) {
     if(simHit->pabs() > frenk->pabs())  {
        frenk = &(*simHit);
        which_kk = kk;
     }
  }
  
//  if(!comparePSimHits(&(*earliest), &(*frenk)))
//    cerr<<"XXXX DEAD DEAD DEAD   number of PSimHits: " << simHits.size() << ". Their position: "<<  which_kkk << ", " << which_kk << endl;

  return earliest;
}

/*****************************************************************************/
bool ChargedMultiplicityAnalyzer_new::comparePSimHits
  (const PSimHit * hit1, const PSimHit * hit2)
{
  return hit1->detUnitId() == hit2->detUnitId() &&
         hit1->trackId() == hit2->trackId() &&
         hit1->timeOfFlight() == hit2->timeOfFlight() &&
         hit1->pabs() == hit2->pabs() &&
         hit1->processType() == hit2->processType() &&
         hit1->particleType() == hit2->particleType() &&
         hit1->energyLoss() == hit2->energyLoss() &&
         hit1->thetaAtEntry() == hit2->thetaAtEntry() &&
         hit1->phiAtEntry() == hit2->phiAtEntry();
}

/*****************************************************************************/
bool ChargedMultiplicityAnalyzer_new::compareRecHits
  (const SiPixelRecHit * hit1, const SiPixelRecHit * hit2)
{
  return hit1->geographicalId() == hit2->geographicalId() &&
        (hit1->cluster())->charge() == (hit2->cluster())->charge() &&
        (hit1->cluster())->size() == (hit2->cluster())->size() &&
        (hit1->cluster())->sizeX() == (hit2->cluster())->sizeX() &&
        (hit1->cluster())->sizeY() == (hit2->cluster())->sizeY();
}

/*****************************************************************************/
void ChargedMultiplicityAnalyzer_new::checkEta
   (const edm::Event& ev, const edm::EventSetup& es, edm::Handle<CaloTowerCollection> towers,
    edm::Handle<SiPixelRecHitCollection> siPixelRecCollection,
//    const reco::VertexCollection* vertices,
    HepMC::GenEvent * myGenEvent)
{
  // Get simulated
  edm::Handle<TrackingParticleCollection> simCollection;
//  ev.getByType(simCollection);
  ev.getByLabel("mergedtruth","MergedTrackTruth",simCollection);

//  const TrackingParticleCollection *tPC = simCollection.product();

  edm::Handle<vector<PSimHit> > simHits;
  ev.getByLabel("g4SimHits","TrackerHitsPixelBarrelLowTof", simHits);

  vector<float> result;
  const SiPixelRecHitCollection pixelRecHits = *(siPixelRecCollection.product());
  edm::ESHandle<TrackerGeometry> geom;
  es.get<TrackerDigiGeometryRecord>().get(geom);

  // get vertex_z
  double rver_z = (double)getVertexZ(siPixelRecCollection, ev);
/*
  if(vertices->size()==1)  {
     reco::VertexCollection::const_iterator vertex = vertices->begin();
     rver_z = vertex->z();
  }
*/
  for(SiPixelRecHitCollection::DataContainer::const_iterator iPRH = pixelRecHits.data().begin(); iPRH != pixelRecHits.data().end(); ++iPRH ) {
     result.clear();

     const PixelGeomDetUnit* pgdu = dynamic_cast<const PixelGeomDetUnit*>(geom->idToDetUnit((*iPRH).geographicalId()));
     PXBDetId pdetId = PXBDetId(iPRH->geographicalId());
     int layer=pdetId.layer();
     if(!(pgdu->subDetector() == GeomDetEnumerators::PixelBarrel && layer == 1))
       continue;
     double ccharge = (*iPRH).cluster()->charge();
     double adc = ccharge/135.;
     GlobalPoint globalPosition = pgdu->toGlobal(iPRH->localPosition());
     // corrected eta
     double eta = globalPosition.eta();
     double eta_corr = 0.;
     double above_eta = 30.;
     double above_eta_corr = 30.;
//     if(vertices->size()==1) {
       float x = fabs(globalPosition.x() - theBeamSpot->position().x());
       float y = fabs(globalPosition.y() - theBeamSpot->position().y());
       double R = TMath::Sqrt(x*x + y*y);
       eta_corr = -log(tan(atan2(R,(globalPosition.z()-rver_z))/2.));
//     }
//     else
//       eta_corr = eta;
     
     if(adc>(130.*cosh(eta_corr)-33.)) {
       above_eta = eta;
       above_eta_corr = eta_corr;       
     }
    
     result.push_back(adc); //adc
     result.push_back(eta); //eta
     result.push_back(eta_corr); //eta_corr
     result.push_back(above_eta);//above_eta
     result.push_back(above_eta_corr); //above_eta_corr

     NCheckEta->Fill(&result[0]);
  }

}

/*****************************************************************************/
void ChargedMultiplicityAnalyzer_new::checkSimTracks
   (const edm::Event& ev, const edm::EventSetup& es, edm::Handle<SiPixelRecHitCollection> siPixelRecCollection)
{
  // Get simulated
  edm::Handle<TrackingParticleCollection> simCollection;
//  ev.getByType(simCollection);
  ev.getByLabel("mergedtruth","MergedTrackTruth",simCollection);

  const TrackingParticleCollection *tPC = simCollection.product();

  edm::ESHandle<TrackerGeometry> geom;
  es.get<TrackerDigiGeometryRecord>().get(geom);

  for(TrackingParticleCollection::const_iterator t = tPC->begin(); t != tPC->end(); ++t) {
    if(TMath::Abs(t->pt() - 1.07793)<0.0001 || TMath::Abs(t->pt() - 1.7243)<0.0001) {
      cerr<< "------------ STRANGE SIM TRACK --------------------" << endl;
      cerr<< " number of sim hits: " << t->trackPSimHit().size() << endl;
      for(std::vector<PSimHit>::const_iterator
                    simHit = t->pSimHit_begin();
                    simHit!= t->pSimHit_end(); simHit++) {
         const PixelGeomDetUnit* pgdu = dynamic_cast<const PixelGeomDetUnit*>(geom->idToDetUnit(simHit->detUnitId()));
         PXBDetId pdetId = PXBDetId(simHit->detUnitId());
         int layer=pdetId.layer();
         cerr<< " --- hit ---" << endl;
         cerr<< "  [process type]: " << simHit->processType() << endl;
         if(pgdu!=0) {
           cerr<< "  [sub detector]: " << pgdu->subDetector() << endl;
           cerr<< "  [layer]:        " << layer << ". layer" << endl;
           GlobalPoint globalPosition = pgdu->toGlobal(simHit->localPosition());
           float x = fabs(globalPosition.x() - theBeamSpot->position().x());
           float y = fabs(globalPosition.y() - theBeamSpot->position().y());
           double R = TMath::Sqrt(x*x + y*y);
           cerr<< "  [R]:            " << R << endl;
           cerr<< "  [z pos]:        " << globalPosition.z() << endl;
         }
         if(pgdu==0) {
           cerr<< "  [sub detector]: No valid detector!" << endl; 
           cerr<< "  [layer]:        No valid detector!" << endl;
       	   cerr<< "  [R]:            No valid detector!" << endl;
           cerr<< "  [z pos]:        No valid detector!" << endl;
         }
      }
    }
  }
//////// CHECK HIT ASSOCIATION

          theHits = siPixelRecCollection.product();
          TrackerHitAssociator theHitAssociator(ev);

          for(SiPixelRecHitCollection::const_iterator detunit_iter = theHits->begin();
                                                   detunit_iter!= theHits->end(); detunit_iter++)
          {
            SiPixelRecHitCollection::DetSet range = *detunit_iter;
            unsigned int id = range.detId();
            const PixelGeomDetUnit* pixelDet =
              dynamic_cast<const PixelGeomDetUnit*> (theTracker->idToDet((id)));

            PXBDetId pid(id); 
            // Take all hits
            if(pid.subdetId() == PixelSubdetector::PixelBarrel && pid.layer()==1) {
              for(SiPixelRecHitCollection::DetSet::const_iterator recHit = range.begin();
                                                          recHit!= range.end(); recHit++)
              {
                GlobalPoint gpos = pixelDet->toGlobal(recHit->localPosition());

                // associate 
                vector<PSimHit> simHits_ass = theHitAssociator.associateHit(*recHit);
                for(std::vector<PSimHit>::const_iterator assSimHit = simHits_ass.begin();
                                                         assSimHit != simHits_ass.end(); assSimHit++)  {
                  const PixelGeomDetUnit* pgdu = dynamic_cast<const PixelGeomDetUnit*>(geom->idToDetUnit(assSimHit->detUnitId()));
                  PXBDetId pdetId = PXBDetId(assSimHit->detUnitId());
//                  unsigned int layer=pdetId.layer();
                  GlobalPoint globalPosition = pgdu->toGlobal(assSimHit->localPosition());

                   if(assSimHit->processType()==2) {
                     vector<float> result;
                     result.push_back((globalPosition-gpos).mag());
                     result.push_back(TMath::Abs(globalPosition.z()-gpos.z()));
                     NHitAssoc->Fill(&result[0]);
                   }
                }
              }
            }
          }
}

/*****************************************************************************/
float ChargedMultiplicityAnalyzer_new::geomAcc(double vert_z, double eta_l, double eta_h, int desLayer)
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
  eta_max = eta_max-0.006;  // TEST, BEWARE
  eta_min = eta_min+0.006;  // TEST, BEWARE

  if(eta_h < eta_min) { if(eta_l==0.0) cerr<< " STRANGE 1 " << endl; return 0.; }
  if(eta_l > eta_max) { if(eta_l==0.0) cerr<< " STRANGE 2 " << endl; return 0.; }
  if(eta_l > eta_min && eta_h < eta_max) { return 1.; }
  if(eta_l < eta_min && eta_h > eta_min) { return ((eta_h-eta_min)/binwidth); }
  if(eta_l < eta_max && eta_h > eta_max) { return ((eta_max-eta_l)/binwidth); }

  return -1.;
}

/*****************************************************************************/
void ChargedMultiplicityAnalyzer_new::multiplicityProperties
   (const edm::Event& ev, const edm::EventSetup& es, edm::Handle<CaloTowerCollection> towers,
    edm::Handle<SiPixelRecHitCollection> siPixelRecCollection,
//    const reco::VertexCollection* vertices,
    HepMC::GenEvent * myGenEvent,
    edm::Handle<reco::TrackCollection>& recCollection,
    Handle<HcalTrigPrimDigiCollection>& tpg,
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
    is_L1_BptxMinus = l1AlgorithmResult(ev, es, "L1_BptxMinus");
    is_L1_BptxPlus = l1AlgorithmResult(ev, es, "L1_BptxPlus");
    is_L1_BptxPlusORMinus = l1AlgorithmResult(ev, es, "L1_BptxPlusORMinus");
    is_L1_BscMinBiasOR_BptxPlusORMinus = l1AlgorithmResult(ev, es, "L1_BscMinBiasOR_BptxPlusORMinus");
*/
  }

  // just a check
  std::vector<const SiPixelRecHit*> knownHits;

  // Get simulated
  edm::Handle<TrackingParticleCollection> simCollection;
//  ev.getByType(simCollection);
  ev.getByLabel("mergedtruth","MergedTrackTruth",simCollection);

  const TrackingParticleCollection *tPC = simCollection.product();

  edm::Handle<vector<PSimHit> > simHits;
  ev.getByLabel("g4SimHits","TrackerHitsPixelBarrelLowTof", simHits);

  edm::ESHandle<TrackerGeometry> geom;
  es.get<TrackerDigiGeometryRecord>().get(geom);

  vector<float> result;
  const SiPixelRecHitCollection pixelRecHits = *(siPixelRecCollection.product());

  //for Vincenzo
  edm::Handle<edm::DetSetVector<PixelDigi> > pixelDigis;
  ev.getByLabel("siPixelDigis", pixelDigis);
  
  result.push_back(pixelDigis->size());
  result.push_back(pixelRecHits.size());

  // get number of clusters
  float clusters_on_layers = 0.;
  for(SiPixelRecHitCollection::DataContainer::const_iterator iPRH = pixelRecHits.data().begin(); iPRH != pixelRecHits.data().end(); ++iPRH ) {

     const PixelGeomDetUnit* pgdu = dynamic_cast<const PixelGeomDetUnit*>(geom->idToDetUnit((*iPRH).geographicalId()));
     PXBDetId pdetId = PXBDetId(iPRH->geographicalId());
     int layer=pdetId.layer();
     GlobalPoint globalPosition = pgdu->toGlobal(iPRH->localPosition());

     //model geometrical acceptance
     //900 GeV
     if(layer==1 && (globalPosition.phi() > -1.395) && (globalPosition.phi() < -1.105) && (globalPosition.eta() > 1.085) && (globalPosition.eta() < 1.725))
       continue;
     if(layer==1 && (globalPosition.phi() > 1.57) && (globalPosition.phi() < 1.77) && (globalPosition.eta() > -0.27) && (globalPosition.eta() < -0.02))
       continue;

     if((pgdu->subDetector() == GeomDetEnumerators::PixelBarrel) && (layer == desLayer))
       clusters_on_layers++;
  }

  result.push_back(clusters_on_layers); //clusters_on_layers

  // get vertex_z
  double rver_z = (double)getVertexZ(siPixelRecCollection, ev);

/*
  if(vertices->size()==1)  { //with cluster vertexing this should alwasy be the case
     reco::VertexCollection::const_iterator vertex = vertices->begin();
     rver_z = vertex->z();
  }
*/
  result.push_back(rver_z); //rver_z

  // cosh(Eta) cut.
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

  for(SiPixelRecHitCollection::DataContainer::const_iterator iPRH = pixelRecHits.data().begin(); iPRH != pixelRecHits.data().end(); ++iPRH ) {
     const PixelGeomDetUnit* pgdu = dynamic_cast<const PixelGeomDetUnit*>(geom->idToDetUnit((*iPRH).geographicalId()));
     PXBDetId pdetId = PXBDetId(iPRH->geographicalId());
     int layer=pdetId.layer();
     double ccharge = (*iPRH).cluster()->charge();
     double adc = ccharge/135.;
     GlobalPoint globalPosition = pgdu->toGlobal(iPRH->localPosition());

     //model geometrical acceptance
     //900 GeV
     if(layer==1 && (globalPosition.phi() > -1.395) && (globalPosition.phi() < -1.105) && (globalPosition.eta() > 1.085) && (globalPosition.eta() < 1.725))
       continue;
     if(layer==1 && (globalPosition.phi() > 1.57) && (globalPosition.phi() < 1.77) && (globalPosition.eta() > -0.27) && (globalPosition.eta() < -0.02))
       continue;

     // corrected eta
//     if(vertices->size()!=1)
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
  
  // M, /*temporarily*/ passedRecHits is /*NOT*/ IN USE!!!
  int counter = 0;
//  for(SiPixelRecHitCollection::DataContainer::const_iterator iPRH = pixelRecHits.data().begin(); iPRH != pixelRecHits.data().end(); ++iPRH ) {
  for(std::vector<const SiPixelRecHit*>::const_iterator iPRH = passedRecHits.begin(); iPRH != passedRecHits.end(); ++iPRH ) {
     const PixelGeomDetUnit* pgdu = dynamic_cast<const PixelGeomDetUnit*>(geom->idToDetUnit((**iPRH).geographicalId()));
     PXBDetId pdetId = PXBDetId((**iPRH).geographicalId());
     int layer=pdetId.layer();

     GlobalPoint globalPosition = pgdu->toGlobal((**iPRH).localPosition());

     //model geometrical acceptance
     //900 GeV
     if(layer==1 && (globalPosition.phi() > -1.395) && (globalPosition.phi() < -1.105) && (globalPosition.eta() > 1.085) && (globalPosition.eta() < 1.725))
       continue;
     if(layer==1 && (globalPosition.phi() > 1.57) && (globalPosition.phi() < 1.77) && (globalPosition.eta() > -0.27) && (globalPosition.eta() < -0.02))
       continue;

     if((pgdu->subDetector() == GeomDetEnumerators::PixelBarrel) && (layer == desLayer))
       counter++;
  }
/*
  //attempt to solve problem with multiplicity arose by passedRecHits (:M != 1,2) (should it be ahead of the previous part?)
  if(vertices->size()!=1)
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
*/
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
//    edm::Handle<reco::TrackCollection>  recCollection;
//    ev.getByLabel("hltPixelTracksForMinBias", recCollection);

//    edm::Handle<CaloTowerCollection> towers;
//    ev.getByLabel("towerMaker",towers);

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
    if(RichardMinBias(tpg)) {
      result.push_back(1);//minBias
    } else {
      result.push_back(0);//minBias
    }
  }

  if(!simulateTriggers_) {
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
    result.push_back(0);  //minBias
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
  result.push_back(1);  //numVtx
  result.push_back(1);    //numEv
  int procID = myGenEvent->signal_process_id();
  result.push_back(procID);  //process ID

  // T_truth
  int T_truth = 0;
  int T_truth_etaP6 = 0; float T_truth_etaP6_eff = 0;
  int T_truth_etaP5 = 0; float T_truth_etaP5_eff = 0;
  int T_truth_etaP4 = 0; float T_truth_etaP4_eff = 0;
  int T_truth_etaP3 = 0; float T_truth_etaP3_eff = 0;
  int T_truth_etaP2 = 0; float T_truth_etaP2_eff = 0;
  int T_truth_etaP1 = 0; float T_truth_etaP1_eff = 0;
  int T_truth_etaN1 = 0; float T_truth_etaN1_eff = 0;
  int T_truth_etaN2 = 0; float T_truth_etaN2_eff = 0;
  int T_truth_etaN3 = 0; float T_truth_etaN3_eff = 0;
  int T_truth_etaN4 = 0; float T_truth_etaN4_eff = 0;
  int T_truth_etaN5 = 0; float T_truth_etaN5_eff = 0;
  int T_truth_etaN6 = 0; float T_truth_etaN6_eff = 0;
  for(TrackingParticleCollection::const_iterator t = tPC->begin(); t != tPC->end(); ++t) {
//     if((t->charge()==1 || t->charge()==-1) && (t->vertex().Rho() < 0.2) && (TMath::Abs(t->eta())<2.5))    //"classical"
     if((t->charge()==1 || t->charge()==-1) && (t->parentVertex()->nSourceTracks() == 0) && fabs(t->pdgId())!=11 && fabs(t->pdgId())!=13 && (TMath::Abs(t->eta())<2.5))    //"classical"
       T_truth++;
//     if((t->charge()==1 || t->charge()==-1) && (t->vertex().Rho() < 0.2) && t->eta()<2.5 && t->eta()>2.0) //Positive

     if((t->charge()==1 || t->charge()==-1) && (t->parentVertex()->nSourceTracks() == 0) && fabs(t->pdgId())!=11 && fabs(t->pdgId())!=13 && t->eta()<3.0 && t->eta()>2.5) { //Positive
       T_truth_etaP6++;
       T_truth_etaP6_eff += 1.*geomAcc(rver_z,2.5,3.0,desLayer);
     }       
     if((t->charge()==1 || t->charge()==-1) && (t->parentVertex()->nSourceTracks() == 0) && fabs(t->pdgId())!=11 && fabs(t->pdgId())!=13 && t->eta()<2.5 && t->eta()>2.0) { //Positive
       T_truth_etaP5++;
       T_truth_etaP5_eff += 1.*geomAcc(rver_z,2.0,2.5,desLayer);
     }
//     if((t->charge()==1 || t->charge()==-1) && (t->vertex().Rho() < 0.2) && t->eta()<=2.0 && t->eta()>1.5) //Positive
     if((t->charge()==1 || t->charge()==-1) && (t->parentVertex()->nSourceTracks() == 0) && fabs(t->pdgId())!=11 && fabs(t->pdgId())!=13 && t->eta()<=2.0 && t->eta()>1.5) { //Positive
       T_truth_etaP4++;
       T_truth_etaP4_eff += 1.*geomAcc(rver_z,1.5,2.0,desLayer);
     }
//     if((t->charge()==1 || t->charge()==-1) && (t->vertex().Rho() < 0.2) && t->eta()<=1.5 && t->eta()>1.0) //Positive
     if((t->charge()==1 || t->charge()==-1) && (t->parentVertex()->nSourceTracks() == 0) && fabs(t->pdgId())!=11 && fabs(t->pdgId())!=13 && t->eta()<=1.5 && t->eta()>1.0) { //Positive
       T_truth_etaP3++;
       T_truth_etaP3_eff += 1.*geomAcc(rver_z,1.0,1.5,desLayer);
     }
//     if((t->charge()==1 || t->charge()==-1) && (t->vertex().Rho() < 0.2) && t->eta()<=1.0 && t->eta()>0.5) //Positive
     if((t->charge()==1 || t->charge()==-1) && (t->parentVertex()->nSourceTracks() == 0) && fabs(t->pdgId())!=11 && fabs(t->pdgId())!=13 && t->eta()<=1.0 && t->eta()>0.5) { //Positive
       T_truth_etaP2++;
       T_truth_etaP2_eff += 1.*geomAcc(rver_z,0.5,1.0,desLayer);
     }
//     if((t->charge()==1 || t->charge()==-1) && (t->vertex().Rho() < 0.2) && t->eta()<=0.5 && t->eta()>0.0) //Positive
     if((t->charge()==1 || t->charge()==-1) && (t->parentVertex()->nSourceTracks() == 0) && fabs(t->pdgId())!=11 && fabs(t->pdgId())!=13 && t->eta()<=0.5 && t->eta()>0.0) { //Positive
       T_truth_etaP1++;
       T_truth_etaP1_eff += 1.*geomAcc(rver_z,0.0,0.5,desLayer);
     }
//     if((t->charge()==1 || t->charge()==-1) && (t->vertex().Rho() < 0.2) && t->eta()<=0.0 && t->eta()>-0.5) //Negative
     if((t->charge()==1 || t->charge()==-1) && (t->parentVertex()->nSourceTracks() == 0) && fabs(t->pdgId())!=11 && fabs(t->pdgId())!=13 && t->eta()<=0.0 && t->eta()>-0.5) { //Negative
       T_truth_etaN1++;
       T_truth_etaN1_eff += 1.*geomAcc(rver_z,-0.5,0.0,desLayer);
     }
//     if((t->charge()==1 || t->charge()==-1) && (t->vertex().Rho() < 0.2) && t->eta()<=-0.5 && t->eta()>-1.0) //Negative
     if((t->charge()==1 || t->charge()==-1) && (t->parentVertex()->nSourceTracks() == 0) && fabs(t->pdgId())!=11 && fabs(t->pdgId())!=13 && t->eta()<=-0.5 && t->eta()>-1.0) { //Negative
       T_truth_etaN2++;
       T_truth_etaN2_eff += 1.*geomAcc(rver_z,-1.0,-0.5,desLayer);
     }
//     if((t->charge()==1 || t->charge()==-1) && (t->vertex().Rho() < 0.2) && t->eta()<=-1.0 && t->eta()>-1.5) //Negative
     if((t->charge()==1 || t->charge()==-1) && (t->parentVertex()->nSourceTracks() == 0) && fabs(t->pdgId())!=11 && fabs(t->pdgId())!=13 && t->eta()<=-1.0 && t->eta()>-1.5) { //Negative
       T_truth_etaN3++;
       T_truth_etaN3_eff += 1.*geomAcc(rver_z,-1.5,-1.0,desLayer);
     }
//     if((t->charge()==1 || t->charge()==-1) && (t->vertex().Rho() < 0.2) && t->eta()<=-1.5 && t->eta()>-2.0) //Negative
     if((t->charge()==1 || t->charge()==-1) && (t->parentVertex()->nSourceTracks() == 0) && fabs(t->pdgId())!=11 && fabs(t->pdgId())!=13 && t->eta()<=-1.5 && t->eta()>-2.0) { //Negative
       T_truth_etaN4++;
       T_truth_etaN4_eff += 1.*geomAcc(rver_z,-2.0,-1.5,desLayer);
     }
//     if((t->charge()==1 || t->charge()==-1) && (t->vertex().Rho() < 0.2) && t->eta()<=-2.0 && t->eta()>-2.5) //Negative
     if((t->charge()==1 || t->charge()==-1) && (t->parentVertex()->nSourceTracks() == 0) && fabs(t->pdgId())!=11 && fabs(t->pdgId())!=13 && t->eta()<=-2.0 && t->eta()>-2.5) { //Negative
       T_truth_etaN5++;
       T_truth_etaN5_eff += 1.*geomAcc(rver_z,-2.5,-2.0,desLayer);
     }
     if((t->charge()==1 || t->charge()==-1) && (t->parentVertex()->nSourceTracks() == 0) && fabs(t->pdgId())!=11 && fabs(t->pdgId())!=13 && t->eta()<=-2.5 && t->eta()>-3.0) { //Negative
       T_truth_etaN6++;
       T_truth_etaN6_eff += 1.*geomAcc(rver_z,-3.0,-2.5,desLayer);
     }
  }
  result.push_back(T_truth);  //T_truth
  result.push_back(T_truth_etaP6);  //T_truth_etaP6
  result.push_back(T_truth_etaP5);  //T_truth_etaP5
  result.push_back(T_truth_etaP4);  //T_truth_etaP4
  result.push_back(T_truth_etaP3);  //T_truth_etaP3
  result.push_back(T_truth_etaP2);  //T_truth_etaP2
  result.push_back(T_truth_etaP1);  //T_truth_etaP1
  result.push_back(T_truth_etaN1);  //T_truth_etaN1
  result.push_back(T_truth_etaN2);  //T_truth_etaN2
  result.push_back(T_truth_etaN3);  //T_truth_etaN3
  result.push_back(T_truth_etaN4);  //T_truth_etaN4
  result.push_back(T_truth_etaN5);  //T_truth_etaN5
  result.push_back(T_truth_etaN6);  //T_truth_etaN6
  // effective tracks (they hit the pixel detector)
  result.push_back(T_truth_etaP6_eff);  //T_truth_etaP6_eff
  result.push_back(T_truth_etaP5_eff);  //T_truth_etaP5_eff
  result.push_back(T_truth_etaP4_eff);  //T_truth_etaP4_eff
  result.push_back(T_truth_etaP3_eff);  //T_truth_etaP3_eff
  result.push_back(T_truth_etaP2_eff);  //T_truth_etaP2_eff
  result.push_back(T_truth_etaP1_eff);  //T_truth_etaP1_eff
  result.push_back(T_truth_etaN1_eff);  //T_truth_etaN1_eff
  result.push_back(T_truth_etaN2_eff);  //T_truth_etaN2_eff
  result.push_back(T_truth_etaN3_eff);  //T_truth_etaN3_eff
  result.push_back(T_truth_etaN4_eff);  //T_truth_etaN4_eff
  result.push_back(T_truth_etaN5_eff);  //T_truth_etaN5_eff
  result.push_back(T_truth_etaN6_eff);  //T_truth_etaN6_eff

  // H_recMC, passedRecHits in use!!!
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

     //model geometrical acceptance
     //900 GeV
     if(layer==1 && (globalPosition.phi() > -1.395) && (globalPosition.phi() < -1.105) && (globalPosition.eta() > 1.085) && (globalPosition.eta() < 1.725))
       continue;
     if(layer==1 && (globalPosition.phi() > 1.57) && (globalPosition.phi() < 1.77) && (globalPosition.eta() > -0.27) && (globalPosition.eta() < -0.02))
       continue;

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

  // cluster size -STARTS-
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

     //model geometrical acceptance
     //900 GeV
     if(layer==1 && (globalPosition.phi() > -1.395) && (globalPosition.phi() < -1.105) && (globalPosition.eta() > 1.085) && (globalPosition.eta() < 1.725))
       continue;
     if(layer==1 && (globalPosition.phi() > 1.57) && (globalPosition.phi() < 1.77) && (globalPosition.eta() > -0.27) && (globalPosition.eta() < -0.02))
       continue;

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
  // cluster size -FINISHED-

if(desLayer==1) {
  // compare the dNdeta distribution in case of M<3 to arbitrary M
  bool isFull = false;
  bool isFullV = false;
  bool isRestricted = false;
  bool isRestrictedV = false;
  bool is_nd = false;
  bool is_nsd = false;
  bool is_nsd_trig = false;
  bool is_sd_trig = false;
  bool is_nd_counter = false;
  bool is_sd_1 = false;
  bool is_sd_1_counter = false;
  bool is_sd_2 = false;
  bool is_sd_2_counter = false;
  bool is_dd = false;
  bool is_dd_counter = false;
  bool is_10 = false;
  bool is_1_8 = false;
  bool is_9_15 = false;
  bool is_16_23 = false;
  bool is_24_36 = false;
  bool is_37_58 = false;
  bool is_59_499 = false;
  bool cluster_1_7 = false;
  bool cluster_8_13 = false;
  bool cluster_14_20 = false;
  bool cluster_21_31 = false;
  bool cluster_32_52 = false;
  bool cluster_53_499 = false;
  for(TrackingParticleCollection::const_iterator t = tPC->begin(); t != tPC->end(); ++t) {
     // without vertex criteria
     if((t->charge()==1 || t->charge()==-1) && (t->parentVertex()->nSourceTracks() == 0) && fabs(t->pdgId())!=11 && fabs(t->pdgId())!=13)  { 
       double test_eta_full = t->eta();
       hTestEtaFull->Fill(test_eta_full);
       isFull = true;
       if(rver_z!=0) {
         double test_eta_restricted = t->eta();
         hTestEtaRestricted->Fill(test_eta_restricted);
         isRestricted = true;
       }
       //nd test -start-
       if(counter>10) {
         double test_eta_restricted_10 = t->eta();
         hTestEtaRestricted_10->Fill(test_eta_restricted_10);
         is_10 = true;
       }
       if(procID!=92 && procID!=93 && procID!=94) {
         double test_nd = t->eta();
         hTest_nd->Fill(test_nd);
         is_nd = true;
       }         
       if(procID!=92 && procID!=93) {
//       if(procID!=5 && procID!=6) {
         double test_nsd = t->eta();
         hTest_nsd->Fill(test_nsd);
         is_nsd = true;
       }         
       if(procID!=92 && procID!=93 && aboveTriggerThreshold_1(towers) && is_bit34 && rver_z!=0) {
//       if(procID!=5 && procID!=6) {
         double test_nsd_trig = t->eta();
         hTest_nsd_trig->Fill(test_nsd_trig);
         is_nsd_trig = true;
       }         
       if((procID==92 || procID==93) && aboveTriggerThreshold_1(towers) && is_bit34 && rver_z!=0) {
//       if(procID!=5 && procID!=6) {
         double test_sd_trig = t->eta();
         hTest_sd_trig->Fill(test_sd_trig);
         is_sd_trig = true;
       }         
       if(procID!=92 && procID!=93 && procID!=94 && counter>0) {
         double test_nd_counter = t->eta();
         hTest_nd_counter->Fill(test_nd_counter);
         is_nd_counter = true;
       }
       //nd test -end-
       //sd_1 test -start-
       if(procID==92) {
         double test_sd_1 = t->eta();
         hTest_sd_1->Fill(test_sd_1);
         is_sd_1 = true;
       }
       if(procID==92 && counter>0) {
         double test_sd_1_counter = t->eta();
         hTest_sd_1_counter->Fill(test_sd_1_counter);
         is_sd_1_counter = true;
       }
       //sd_1 test -end-
       //sd_2 test -start-
       if(procID==93) {
         double test_sd_2 = t->eta();
         hTest_sd_2->Fill(test_sd_2);
         is_sd_2 = true;
       }
       if(procID==93 && counter>0) {
         double test_sd_2_counter = t->eta();
         hTest_sd_2_counter->Fill(test_sd_2_counter);
         is_sd_2_counter = true;
       }
       //sd_2 test -end-
       //dd test -start-
       if(procID==94) {
         double test_dd = t->eta();
         hTest_dd->Fill(test_dd);
         is_dd = true;
       }
       if(procID==94 && counter>0) {
         double test_dd_counter = t->eta();
         hTest_dd_counter->Fill(test_dd_counter);
         is_dd_counter = true;
       }
       //dd test -end-
       if(counter<1) {
         double test_eta_restricted_1 = t->eta();
         hTestEtaRestricted_1->Fill(test_eta_restricted_1);
       }
       //For partial distributions
       if(counter>0 && counter<9) {  //1-8
         double test_eta_restricted = t->eta();
         hTestEta_1_8->Fill(test_eta_restricted);
         is_1_8 = true;
       }   
       if(counter>8 && counter<16) {  //9-15
         double test_eta_restricted = t->eta();
         hTestEta_9_15->Fill(test_eta_restricted);
         is_9_15 = true;
       }
       if(counter>15 && counter<24) {  //16-23
         double test_eta_restricted = t->eta();
         hTestEta_16_23->Fill(test_eta_restricted);
         is_16_23 = true;
       }
       if(counter>23 && counter<37) {  //24-36
         double test_eta_restricted = t->eta();
         hTestEta_24_36->Fill(test_eta_restricted);
         is_24_36 = true;
       }
       if(counter>36 && counter<59) {  //37-58
         double test_eta_restricted = t->eta();
         hTestEta_37_58->Fill(test_eta_restricted);
         is_37_58 = true;
       }
       if(counter>58 && counter<500) {  //59-499
         double test_eta_restricted = t->eta();
         hTestEta_59_499->Fill(test_eta_restricted);
         is_59_499 = true;
       }
       // cluster subsections
       if(cluster_counter>0 && cluster_counter<8) {  //1-7
         double Cluster_eta_restricted = t->eta();
         hClusterEta_1_7->Fill(Cluster_eta_restricted);
         cluster_1_7 = true;
       }
       if(cluster_counter>7 && cluster_counter<14) {  //8-13
         double Cluster_eta_restricted = t->eta();
         hClusterEta_8_13->Fill(Cluster_eta_restricted);
         cluster_8_13 = true;
       }
       if(cluster_counter>13 && cluster_counter<21) {  //14-20
         double Cluster_eta_restricted = t->eta();
         hClusterEta_14_20->Fill(Cluster_eta_restricted);
         cluster_14_20 = true;
       }
       if(cluster_counter>20 && cluster_counter<32) {  //21-31
         double Cluster_eta_restricted = t->eta();
         hClusterEta_21_31->Fill(Cluster_eta_restricted);
         cluster_21_31 = true;
       }
       if(cluster_counter>31 && cluster_counter<53) {  //32-52
         double Cluster_eta_restricted = t->eta();
         hClusterEta_32_52->Fill(Cluster_eta_restricted);
         cluster_32_52 = true;
       }
       if(cluster_counter>52 && cluster_counter<500) {  //53-499
         double Cluster_eta_restricted = t->eta();
         hClusterEta_53_499->Fill(Cluster_eta_restricted);
         cluster_53_499 = true;
       }

     }
     // with 1 reconstructed vertex
//     if((t->charge()==1 || t->charge()==-1) && (t->vertex().Rho() < 0.2) && vertices->size()==1)  {
     if((t->charge()==1 || t->charge()==-1) && (t->vertex().Rho() < 0.2))  {
       double test_eta_full = t->eta();
       hTestEtaFullV->Fill(test_eta_full);
       isFullV = true;
       if(counter<3) { // if M<3
         double test_eta_restricted = t->eta();
         hTestEtaRestrictedV->Fill(test_eta_restricted);
         isRestrictedV = true;
       }
     }
  }
  if(isFull)
    full++;
  if(isFullV)
    fullV++;
  if(isRestricted)
    restricted++;
  if(isRestrictedV)
    restrictedV++;
  if(is_10)
    num_10++;
  if(is_nd) {
    num_nd++;
    hNum_nd->Fill(0);
  }
  if(is_nsd) {
    num_nsd++;
    hNum_nsd->Fill(0);
  }
  if(is_nsd_trig) {
    num_nsd_trig++;
    hNum_nsd_trig->Fill(0);
  }
  if(is_sd_trig) {
    num_sd_trig++;
    hNum_sd_trig->Fill(0);
  }
  if(is_nd_counter)
    num_nd_counter++;
  if(is_sd_1)
    num_sd_1++;
  if(is_sd_1_counter)
    num_sd_1_counter++;
  if(is_sd_2)
    num_sd_2++;
  if(is_sd_2_counter)
    num_sd_2_counter++;
  if(is_dd)
    num_dd++;
  if(is_dd_counter)
    num_dd_counter++;
  if(is_1_8)
    num_1_8++;
  if(is_9_15)
    num_9_15++;
  if(is_16_23) 
    num_16_23++;
  if(is_24_36)
    num_24_36++;
  if(is_37_58)
    num_37_58++;
  if(is_59_499)
    num_59_499++;
  // cluster
  if(cluster_1_7)
    num_cluster_1_7++;
  if(cluster_8_13)
    num_cluster_8_13++;
  if(cluster_14_20) 
    num_cluster_14_20++;
  if(cluster_21_31)
    num_cluster_21_31++;
  if(cluster_32_52)
    num_cluster_32_52++;
  if(cluster_53_499)
    num_cluster_53_499++;
}
  // in my case H_recMC = H_data and E_recMC = E_data

  // fill the ntuple
  if(desLayer==1)
    multProp->Fill(&result[0]);
  if(desLayer==2)
    nd_multProp->Fill(&result[0]);
  if(desLayer==3)
    rd_multProp->Fill(&result[0]);

// LOOPER part starts here
// which are the looper hits?
  int looperHits_etaP6 = 0;
  int looperHits_etaP5 = 0;
  int looperHits_etaP4 = 0;
  int looperHits_etaP3 = 0;
  int looperHits_etaP2 = 0;
  int looperHits_etaP1 = 0;
  int looperHits_etaN1 = 0;
  int looperHits_etaN2 = 0;
  int looperHits_etaN3 = 0;
  int looperHits_etaN4 = 0;
  int looperHits_etaN5 = 0;
  int looperHits_etaN6 = 0;
  vector<float> looper_result;
  vector<TrackingParticle> loopers;  // it was inside the if below
  vector<TrackingParticle> geoPrims; 
//  if(vertices->size()==1) {
  if(1) {
    TrackerHitAssociator theHitAssociator(ev);
    // Get simulated
    edm::Handle<TrackingParticleCollection> simCollection;
//    ev.getByType(simCollection);
    ev.getByLabel("mergedtruth","MergedTrackTruth",simCollection);
    // Get pixel hits
    theHits = siPixelRecCollection.product();
    // result vector

    for(SiPixelRecHitCollection::const_iterator detunit_iter = theHits->begin();
                                             detunit_iter!= theHits->end(); detunit_iter++)
    {
      SiPixelRecHitCollection::DetSet range = *detunit_iter;
      unsigned int id = range.detId();
      const PixelGeomDetUnit* pixelDet =
        dynamic_cast<const PixelGeomDetUnit*> (theTracker->idToDet((id)));

      const RectangularPixelTopology* topology =
        dynamic_cast<const RectangularPixelTopology*>
          (&(pixelDet->specificTopology()));

      PXBDetId pid(id);
      // Take all hits
      if(pid.subdetId() == PixelSubdetector::PixelBarrel)
      { 
        // Look at a certain barrel only
        if(pid.layer() == (unsigned)desLayer)
        for(SiPixelRecHitCollection::DetSet::const_iterator recHit = range.begin();
                             recHit!= range.end(); recHit++)
        {
          GlobalPoint gpos = pixelDet->toGlobal(recHit->localPosition());

          //model geometrical acceptance
          //900 GeV
          if(pid.layer()==1 && (gpos.phi() > -1.395) && (gpos.phi() < -1.105) && (gpos.eta() > 1.085) && (gpos.eta() < 1.725))
            continue;
          if(pid.layer()==1 && (gpos.phi() > 1.57) && (gpos.phi() < 1.77) && (gpos.eta() > -0.27) && (gpos.eta() < -0.02))
            continue;
  
          // eta and eloss
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

          // associate 
          vector<PSimHit> simHits_ass = theHitAssociator.associateHit(*recHit);
          vector<PSimHit> ordered_ass = orderPSimHits(simHits_ass);
          const PSimHit * bestSimHit = 0;

          // background = 1, primary = 2, primary looper = 3
          int type = 1;
//          const PSimHit * lemmaHit = 0;  // get rid of fake loopers
          for(vector<PSimHit>::const_iterator simHit = ordered_ass.begin();  //originally  simHits_ass.begin() and ...end()
                      simHit!= ordered_ass.end(); simHit++)                  // WARNING!!!
            if(simHit->processType() == 2)  //we expect one bestSimHit
            {
              bestSimHit = &(*simHit);
              type = 2;  
            }

          // Is it a looping hit?
          if(type == 2)
          for(TrackingParticleCollection::size_type i=0;
               i < simCollection.product()->size(); ++i)
          {
            const TrackingParticleRef simTrack(simCollection, i);

            hPt->Fill(simTrack->pt());

            const PSimHit * firstSimHit = 0;
            float pmin = 100.;
            for(std::vector<PSimHit>::const_iterator
                          simHit = simTrack->pSimHit_begin();
                          simHit!= simTrack->pSimHit_end(); simHit++) {
              //WARNING: DIFFERENT FIRST DEFINITION!! (> pmax) -> (< pmin) !!
              const PixelGeomDetUnit* Bpgdu = dynamic_cast<const PixelGeomDetUnit*>(geom->idToDetUnit(simHit->detUnitId()));
              if(Bpgdu==0)
                continue;
              PXBDetId BpdetId = PXBDetId(simHit->detUnitId());
              int Blayer=BpdetId.layer();
              if(simHit->pabs() < pmin && Blayer==desLayer && simHit->processType() == 2 && Bpgdu->subDetector() == GeomDetEnumerators::PixelBarrel)  //BEWARE
              { pmin = simHit->pabs(); firstSimHit = &(*simHit); }
            }

            if(firstSimHit != 0)
              if(bestSimHit->trackId() == firstSimHit->trackId())
              {
                if(!(bestSimHit->pabs() == firstSimHit->pabs())) {
                  if(abs(bestSimHit->timeOfFlight()-firstSimHit->timeOfFlight())<0.14) {  //hardcut on geos
                    // geo effect part
                    bool alreadY = false;
                    for(vector<TrackingParticle>::const_iterator tLemma = geoPrims.begin(); tLemma != geoPrims.end(); tLemma++) {
                      if(tLemma->pt() == simTrack->pt())
                        alreadY = true;
                    }
                    if(!alreadY)
                      geoPrims.push_back(*simTrack);
                    continue;
                  }
                  type = 3;
                  // remove multiple entries BEWARE
                  bool alreadY = false;
                  for(vector<TrackingParticle>::const_iterator tLemma = loopers.begin(); tLemma != loopers.end(); tLemma++) {
                    if(tLemma->pt() == simTrack->pt())
                      alreadY = true;
                  }
                  if(!alreadY)
                    loopers.push_back(*simTrack);
//                    hLooperPt->Fill(simTrack->pt());
                }
                if(type==2) {
//                  hNonLooperPt->Fill(simTrack->pt());
                  if(simTrack->vertex().Rho()>0.2) 
//                  if(simTrack->parentVertex()->nSourceTracks() != 0) 
                    { /* std::cerr<<"XXXX Secondary candidate: "<< simTrack->pdgId() << std::endl; */ type=4; }
                }
  
                break;
              }
          }

          vector<float> result_looper;

          result_looper.push_back(aboveTriggerThreshold_1(towers));
          result_looper.push_back(aboveTriggerThreshold_2(towers));

          result_looper.push_back(rver_z);
          result_looper.push_back(eta);
          result_looper.push_back(eta_det);
          result_looper.push_back(phi);
          result_looper.push_back(eloss);
          result_looper.push_back(type*(isAtEdge(topology,*recHit) ? -1 : 1));
          result_looper.push_back(counter);
//          result_looper.push_back(vertices->size());
          result_looper.push_back(1);
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

//          if(eloss/(135.*cosh(eta))<713. && eloss/(135.*cosh(eta))>712. && type==3)
//             std::cerr<<"Suspicious energy loss of a looper particle(2): "<< eloss/(135.*cosh(eta)) << std::endl;
//          if(type==3)
//             hProba->Fill(eloss/(135.*cosh(eta)));

          // Filling
          if(desLayer==1)
            multProp_looper->Fill(&result_looper[0]);
          if(desLayer==2)
            nd_multProp_looper->Fill(&result_looper[0]);
          if(desLayer==3)
            rd_multProp_looper->Fill(&result_looper[0]);

        }
      }
    }

//one would analyze the vector "loopers" here
    //loop over the looper particles
    for(vector<TrackingParticle>::const_iterator tPR = loopers.begin(); tPR != loopers.end(); tPR++) {
       //find their hits which are in the first pixel barrel layer
//       cerr<< "Another looper " << endl; // BEWARE 
       vector<PSimHit> looper_hits;
       vector<PSimHit> final_looper_hits;
       vector<PSimHit> simHits_ass;
       for(std::vector<PSimHit>::const_iterator
           simHit = tPR->pSimHit_begin();
           simHit!= tPR->pSimHit_end(); simHit++)  {
          const PixelGeomDetUnit* pgdu = dynamic_cast<const PixelGeomDetUnit*>(geom->idToDetUnit(simHit->detUnitId()));
          if(pgdu==0)
            continue;
          PXBDetId pdetId = PXBDetId(simHit->detUnitId());  //geographicalId());
          int layer=pdetId.layer();
          if((pgdu->subDetector() == GeomDetEnumerators::PixelBarrel) && (layer == desLayer) && (simHit->processType() == 2)) {
            looper_hits.push_back(*simHit);
            //get tof and pabs for every hit
            vector<float> pabstof;
            pabstof.push_back(simHit->pabs());
            pabstof.push_back(simHit->tof());
            hPabsTof->Fill(&pabstof[0]);
            pabstof.clear();
          }
       }

       float pmax = 0.;
       float pmin = 9999.;
       const PSimHit * firstSimHit = 0;
       const PSimHit * lastSimHit = 0;
       // loop through the selected looper hits
       for(std::vector<PSimHit>::const_iterator
           simHit = looper_hits.begin();
           simHit!= looper_hits.end(); simHit++)  {
          // select the first hit
          if(simHit->pabs() > pmax)
            { pmax = simHit->pabs(); firstSimHit = &(*simHit); }
          // select the last hit
          if((simHit->pabs() < pmin) && !(firstSimHit->pabs()==simHit->pabs()))
            { pmin = simHit->pabs(); lastSimHit = &(*simHit); }
       }

       // get TOF
       if(!(lastSimHit == 0))
         hLastTOF->Fill(lastSimHit->timeOfFlight());

       // final looper hits
       for(std::vector<PSimHit>::const_iterator
           simHit = looper_hits.begin();
           simHit!= looper_hits.end(); simHit++)  {
          if(!(firstSimHit->pabs() == simHit->pabs()) && simHit->processType() == 2)   // BEWARE
            final_looper_hits.push_back(*simHit);
       }

       for(std::vector<PSimHit>::const_iterator lSimHit = final_looper_hits.begin();
                                                lSimHit != final_looper_hits.end(); lSimHit++)  {
          //we have to compare the final_looper_hits to associated simHits
//          cerr<< " Another final_looper_hit " << endl; // BEWARE
          bool back = false;  // if we find the corresponding recHit, we should take the next element of final_looper_hit 
          for(SiPixelRecHitCollection::const_iterator detunit_iter = theHits->begin();
                                                   detunit_iter!= theHits->end(); detunit_iter++)
          {
            if(back)
              break;
            SiPixelRecHitCollection::DetSet range = *detunit_iter;
            unsigned int id = range.detId();
            const PixelGeomDetUnit* pixelDet =
              dynamic_cast<const PixelGeomDetUnit*> (theTracker->idToDet((id)));

            PXBDetId pid(id); 
            // Take all hits
            if(pid.subdetId() == PixelSubdetector::PixelBarrel && pid.layer()==(unsigned)desLayer)
              for(SiPixelRecHitCollection::DetSet::const_iterator recHit = range.begin();
                                                          recHit!= range.end(); recHit++)
              {
                if(back)
                  break;
                GlobalPoint gpos = pixelDet->toGlobal(recHit->localPosition());

                //model geometrical acceptance
                //900 GeV
                if(pid.layer()==1 && (gpos.phi() > -1.395) && (gpos.phi() < -1.105) && (gpos.eta() > 1.085) && (gpos.eta() < 1.725))
                  continue;
                if(pid.layer()==1 && (gpos.phi() > 1.57) && (gpos.phi() < 1.77) && (gpos.eta() > -0.27) && (gpos.eta() < -0.02))
                  continue;

                // eta and eloss
                float x = fabs(gpos.x() - theBeamSpot->position().x());
                float y = fabs(gpos.y() - theBeamSpot->position().y());
                double R = TMath::Sqrt(x*x + y*y);
                float eta = -log(tan(atan2(R,(gpos.z()-rver_z))/2.));
                float eloss = recHit->cluster()->charge();
                int clustSizeY = recHit->cluster()->sizeY();

//TEST -starts-
//           	//check if it is passed
//                bool HitPassed = false;
//                for(std::vector<const SiPixelRecHit*>::const_iterator passedrecHit = passedClusters.begin(); passedrecHit != passedClusters.end(); ++passedrecHit ) {
//                  if(compareRecHits((*passedrecHit),&(*recHit)))
//                  { HitPassed = true; break; }
//                }
//                if(!HitPassed)
//                  continue;
//TEST -ends-
                // associate 
                simHits_ass = theHitAssociator.associateHit(*recHit);
                // compare the simHits_ass and final_looper_hits
                for(std::vector<PSimHit>::const_iterator assSimHit = simHits_ass.begin();
                                                         assSimHit != simHits_ass.end(); assSimHit++)  {
                    if(comparePSimHits(&(*lSimHit),&(*assSimHit))) {
                      vector<float> input;
//                      cerr<<" !!!! eloss: " << eloss << endl;
                      knownHits.push_back(&(*recHit));

                      input.push_back(rver_z);
                      input.push_back(eloss);
                      input.push_back(eta);
                      input.push_back(counter);
//                      input.push_back(vertices->size());
                      input.push_back(1);
                      input.push_back(clustSizeY);
                      input.push_back(cluster_counter);

                      // number of hits
                      if((pixelDet->subDetector() == GeomDetEnumerators::PixelBarrel) && (pid.layer() == (unsigned)desLayer) && eta<3.0 && eta>2.5)
                        looperHits_etaP6++;
                      if((pixelDet->subDetector() == GeomDetEnumerators::PixelBarrel) && (pid.layer() == (unsigned)desLayer) && eta<2.5 && eta>2.0)
                        looperHits_etaP5++;
                      if((pixelDet->subDetector() == GeomDetEnumerators::PixelBarrel) && (pid.layer() == (unsigned)desLayer) && eta<=2.0 && eta>1.5)
                        looperHits_etaP4++;
                      if((pixelDet->subDetector() == GeomDetEnumerators::PixelBarrel) && (pid.layer() == (unsigned)desLayer) && eta<=1.5 && eta>1.0)
                        looperHits_etaP3++;
                      if((pixelDet->subDetector() == GeomDetEnumerators::PixelBarrel) && (pid.layer() == (unsigned)desLayer) && eta<=1.0 && eta>0.5)
                        looperHits_etaP2++;
                      if((pixelDet->subDetector() == GeomDetEnumerators::PixelBarrel) && (pid.layer() == (unsigned)desLayer) && eta<=0.5 && eta>0.0)
                        looperHits_etaP1++;
                      if((pixelDet->subDetector() == GeomDetEnumerators::PixelBarrel) && (pid.layer() == (unsigned)desLayer) && eta<=0.0 && eta>-0.5)
                        looperHits_etaN1++;
                      if((pixelDet->subDetector() == GeomDetEnumerators::PixelBarrel) && (pid.layer() == (unsigned)desLayer) && eta<=-0.5 && eta>-1.0)
                        looperHits_etaN2++;
                      if((pixelDet->subDetector() == GeomDetEnumerators::PixelBarrel) && (pid.layer() == (unsigned)desLayer) && eta<=-1.0 && eta>-1.5)
                        looperHits_etaN3++;
                      if((pixelDet->subDetector() == GeomDetEnumerators::PixelBarrel) && (pid.layer() == (unsigned)desLayer) && eta<=-1.5 && eta>-2.0)
                        looperHits_etaN4++;
                      if((pixelDet->subDetector() == GeomDetEnumerators::PixelBarrel) && (pid.layer() == (unsigned)desLayer) && eta<=-2.0 && eta>-2.5)
                        looperHits_etaN5++;
                      if((pixelDet->subDetector() == GeomDetEnumerators::PixelBarrel) && (pid.layer() == (unsigned)desLayer) && eta<=-2.5 && eta>-3.0)
                        looperHits_etaN6++;

                      // Filling
                      if(desLayer==1)
                        hJustLooper->Fill(&input[0]);
                      if(desLayer==2)
                        nd_hJustLooper->Fill(&input[0]);
                      if(desLayer==3)
                        rd_hJustLooper->Fill(&input[0]);

                      back = true;
                      break;
                    }
                }
              }
          } //end of recHits
       }
    } //end of trackingParticles

  } // end of always if
//  } // end of 1vtx condition

  looper_result.push_back(looperHits_etaP6);
  looper_result.push_back(looperHits_etaP5);
  looper_result.push_back(looperHits_etaP4);
  looper_result.push_back(looperHits_etaP3);
  looper_result.push_back(looperHits_etaP2);
  looper_result.push_back(looperHits_etaP1);
  looper_result.push_back(looperHits_etaN1);
  looper_result.push_back(looperHits_etaN2);
  looper_result.push_back(looperHits_etaN3);
  looper_result.push_back(looperHits_etaN4);
  looper_result.push_back(looperHits_etaN5);
  looper_result.push_back(looperHits_etaN6);
  looper_result.push_back(cluster_counter);

  if(desLayer==1)  
    NLooper->Fill(&looper_result[0]);
  if(desLayer==2)  
    nd_NLooper->Fill(&looper_result[0]);
  if(desLayer==3)  
    rd_NLooper->Fill(&looper_result[0]);

//LOOPER part ends here

// contribution from decays -STARTS-
  theHits = siPixelRecCollection.product();
  TrackerHitAssociator theHitAssociator(ev);
//  edm::Handle<TrackingParticleCollection> simCollection;
//  ev.getByType(simCollection);

  int decayCounter = 0;
  int decayHits_etaP6 = 0;
  int decayHits_etaP5 = 0;
  int decayHits_etaP4 = 0;
  int decayHits_etaP3 = 0;
  int decayHits_etaP2 = 0;
  int decayHits_etaP1 = 0;
  int decayHits_etaN1 = 0;
  int decayHits_etaN2 = 0;
  int decayHits_etaN3 = 0;
  int decayHits_etaN4 = 0;
  int decayHits_etaN5 = 0;
  int decayHits_etaN6 = 0;

/**************************************/
//
//  geomaterical acceptance is not corrected from this onwards
//
/**************************************/

  // use all or the passed clusters
  cerr<<" Number of passed clusters: " << passedClusters.size() << endl;
  for(std::vector<const SiPixelRecHit*>::const_iterator recHit = passedClusters.begin(); recHit != passedClusters.end(); ++recHit ) {
//  for(SiPixelRecHitCollection::id_iterator id = theHits->id_begin();
//                                           id!= theHits->id_end(); id++)  {
//     SiPixelRecHitCollection::range range = theHits->get((*id));
//     const PixelGeomDetUnit* pixelDet =
//           dynamic_cast<const PixelGeomDetUnit*> (theTracker->idToDet((*id)));
//     PXBDetId pid(*id);
     const PixelGeomDetUnit* pixelDet = dynamic_cast<const PixelGeomDetUnit*>(geom->idToDetUnit((**recHit).geographicalId()));
     PXBDetId pdetId = PXBDetId((**recHit).geographicalId());
     int layer=pdetId.layer();

     // vertex check, it never fires
//     if(vertices->size()!=1)
//       break;

     int alreadyFound = false;
     if((pixelDet->subDetector() == GeomDetEnumerators::PixelBarrel) && layer==desLayer) {
//       for(SiPixelRecHitCollection::DataContainer::const_iterator recHit = range.first;
//                                                   recHit!= range.second; recHit++)  {
//          cerr<< " [ChargedMultiplicityAnalyzer_new]: new recHit" << endl;;
//          GlobalPoint globalPosition = pixelDet->toGlobal((recHit)->localPosition());
          GlobalPoint globalPosition = pixelDet->toGlobal((**recHit).localPosition());
          float x = fabs(globalPosition.x() - theBeamSpot->position().x());
          float y = fabs(globalPosition.y() - theBeamSpot->position().y());
          double R = TMath::Sqrt(x*x + y*y);
          double eta_corr = -log(tan(atan2(R,(globalPosition.z()-rver_z))/2.));
          // get assosiated sim tracks
          vector<PSimHit> simHits_ass = theHitAssociator.associateHit(**recHit);
          for(std::vector<PSimHit>::const_iterator assSimHit = simHits_ass.begin();
                                                   assSimHit != simHits_ass.end(); assSimHit++)  {
             if(alreadyFound)
               break;
             if(assSimHit->processType()==4) {
               // filling ntuple
               knownHits.push_back((*recHit));

               if((pixelDet->subDetector() == GeomDetEnumerators::PixelBarrel) && (layer == desLayer) && eta_corr<3.0 && eta_corr>2.5)
                 decayHits_etaP6++;
               if((pixelDet->subDetector() == GeomDetEnumerators::PixelBarrel) && (layer == desLayer) && eta_corr<2.5 && eta_corr>2.0)
                 decayHits_etaP5++;
               if((pixelDet->subDetector() == GeomDetEnumerators::PixelBarrel) && (layer == desLayer) && eta_corr<=2.0 && eta_corr>1.5)
                 decayHits_etaP4++;
               if((pixelDet->subDetector() == GeomDetEnumerators::PixelBarrel) && (layer == desLayer) && eta_corr<=1.5 && eta_corr>1.0)  
                 decayHits_etaP3++;
               if((pixelDet->subDetector() == GeomDetEnumerators::PixelBarrel) && (layer == desLayer) && eta_corr<=1.0 && eta_corr>0.5)
                 decayHits_etaP2++;
               if((pixelDet->subDetector() == GeomDetEnumerators::PixelBarrel) && (layer == desLayer) && eta_corr<=0.5 && eta_corr>0.0)  
                 decayHits_etaP1++;
               if((pixelDet->subDetector() == GeomDetEnumerators::PixelBarrel) && (layer == desLayer) && eta_corr<=0.0 && eta_corr>-0.5)
                 decayHits_etaN1++;
               if((pixelDet->subDetector() == GeomDetEnumerators::PixelBarrel) && (layer == desLayer) && eta_corr<=-0.5 && eta_corr>-1.0)
                 decayHits_etaN2++;
               if((pixelDet->subDetector() == GeomDetEnumerators::PixelBarrel) && (layer == desLayer) && eta_corr<=-1.0 && eta_corr>-1.5)
                 decayHits_etaN3++;
               if((pixelDet->subDetector() == GeomDetEnumerators::PixelBarrel) && (layer == desLayer) && eta_corr<=-1.5 && eta_corr>-2.0)
                 decayHits_etaN4++;
               if((pixelDet->subDetector() == GeomDetEnumerators::PixelBarrel) && (layer == desLayer) && eta_corr<=-2.0 && eta_corr>-2.5)
                 decayHits_etaN5++;
               if((pixelDet->subDetector() == GeomDetEnumerators::PixelBarrel) && (layer == desLayer) && eta_corr<=-2.5 && eta_corr>-3.0)
                 decayHits_etaN6++;

               //check, not needed
//               cerr<< " Found a RecHit coming from a decay" << endl;
               int parentID = 0;
               // Found the particle causing the hit
               for(TrackingParticleCollection::size_type i=0;
                   i < simCollection.product()->size(); ++i) {
                  if(alreadyFound)
                    break;
                  const TrackingParticleRef simTrack(simCollection, i);
                  for(std::vector<PSimHit>::const_iterator
                      simHit = simTrack->pSimHit_begin();
                      simHit!= simTrack->pSimHit_end(); simHit++) {
                      if(simHit->pabs() == assSimHit->pabs()) {
//                        cerr<<" The particle leaving the decay hit: " << simTrack->pdgId() << endl;
                        if(simTrack->parentVertex()->nSourceTracks() != 0) {
//                          cerr<<" Mother of that particle: "<< (*(simTrack->parentVertex()->sourceTracks_begin()))->pdgId() << endl;
                          parentID = (*(simTrack->parentVertex()->sourceTracks_begin()))->pdgId();
                        }
                        if(simTrack->parentVertex()->nSourceTracks() == 0)  {
//                          cerr<<" The particle doesn't have a mother" << endl;
                          parentID = -1;
                        }
                        alreadyFound = true;
                        vector<float> result_decay;
                        result_decay.push_back(parentID);
                        result_decay.push_back(simTrack->pdgId());
                        NDecayInfo->Fill(&result_decay[0]);
                        break;
                      }
                  }     
               }
             }
          }
//       }
     }
  }

  int num_weaks = 0;
  for(TrackingParticleCollection::size_type i=0;
      i < simCollection.product()->size(); ++i) {
     const TrackingParticleRef simTrack(simCollection, i);

     int parentID = 0;
     if(simTrack->parentVertex()->nSourceTracks() != 0)
       parentID = (*(simTrack->parentVertex()->sourceTracks_begin()))->pdgId();
     if(parentID==310 || parentID==3122)
     for(std::vector<PSimHit>::const_iterator
         simHit = simTrack->pSimHit_begin();
         simHit!= simTrack->pSimHit_end(); simHit++) {
        const PixelGeomDetUnit* Bpgdu = dynamic_cast<const PixelGeomDetUnit*>(geom->idToDetUnit(simHit->detUnitId()));
        if(Bpgdu==0)
          continue;
        PXBDetId BpdetId = PXBDetId(simHit->detUnitId());
        int Blayer=BpdetId.layer();
        if(Blayer==desLayer && Bpgdu->subDetector() == GeomDetEnumerators::PixelBarrel) {
          num_weaks++;
          break;
        }
     }
  }
  
  cerr<< " (number of decay hits: " << decayHits_etaP5+decayHits_etaP4+decayHits_etaP3+decayHits_etaP2+decayHits_etaP1+decayHits_etaN1+decayHits_etaN2+decayHits_etaN3+decayHits_etaN4+decayHits_etaN5 << ")" << endl;
  vector<float> result_decay;
  result_decay.push_back(decayCounter);
  result_decay.push_back(num_weaks);
  result_decay.push_back(decayHits_etaP6);
  result_decay.push_back(decayHits_etaP5);
  result_decay.push_back(decayHits_etaP4);
  result_decay.push_back(decayHits_etaP3);
  result_decay.push_back(decayHits_etaP2);
  result_decay.push_back(decayHits_etaP1);
  result_decay.push_back(decayHits_etaN1);
  result_decay.push_back(decayHits_etaN2);
  result_decay.push_back(decayHits_etaN3);
  result_decay.push_back(decayHits_etaN4);
  result_decay.push_back(decayHits_etaN5);
  result_decay.push_back(decayHits_etaN6);
  result_decay.push_back(cluster_counter);

  if(desLayer==1)
    NDecay->Fill(&result_decay[0]);
  if(desLayer==2)
    nd_NDecay->Fill(&result_decay[0]);
  if(desLayer==3)
    rd_NDecay->Fill(&result_decay[0]);
// contribution from decays -FINISHED-

// contribution of different interactions (non-primary, non-decay products)
// -STARTS-
//  cerr<< " Intarection part starts." << endl;
  int interHits_etaP6 = 0;
  int interHits_etaP5 = 0;
  int interHits_etaP4 = 0;
  int interHits_etaP3 = 0;
  int interHits_etaP2 = 0;
  int interHits_etaP1 = 0;
  int interHits_etaN1 = 0;
  int interHits_etaN2 = 0;
  int interHits_etaN3 = 0;
  int interHits_etaN4 = 0;
  int interHits_etaN5 = 0;
  int interHits_etaN6 = 0;
  // use all or the passed cluster
  // currently: all
  for(std::vector<const SiPixelRecHit*>::const_iterator recHit = passedClusters.begin(); recHit != passedClusters.end(); ++recHit ) {
//  for(SiPixelRecHitCollection::id_iterator id = theHits->id_begin();
//                                           id!= theHits->id_end(); id++)  {
//     SiPixelRecHitCollection::range range = theHits->get((*id));
//     const PixelGeomDetUnit* pixelDet =
//           dynamic_cast<const PixelGeomDetUnit*> (theTracker->idToDet((*id)));
//     PXBDetId pid(*id);

     const PixelGeomDetUnit* pixelDet = dynamic_cast<const PixelGeomDetUnit*>(geom->idToDetUnit((**recHit).geographicalId()));
     PXBDetId pdetId = PXBDetId((**recHit).geographicalId());
     int layer=pdetId.layer();

     // vertex check, it never fires
//     if(vertices->size()!=1)
//       break;

     int alreadyFound = false;
     if(pixelDet->subDetector() == GeomDetEnumerators::PixelBarrel && layer==desLayer) {
//       for(SiPixelRecHitCollection::DataContainer::const_iterator recHit = range.first;
//                                                   recHit!= range.second; recHit++)  {
          bool fromInt = true;
//          GlobalPoint globalPosition = pixelDet->toGlobal((recHit)->localPosition());
          GlobalPoint globalPosition = pixelDet->toGlobal((**recHit).localPosition());
          float x = fabs(globalPosition.x() - theBeamSpot->position().x());
          float y = fabs(globalPosition.y() - theBeamSpot->position().y());
          double R = TMath::Sqrt(x*x + y*y);
          double eta_corr = -log(tan(atan2(R,(globalPosition.z()-rver_z))/2.));
          // get assosiated sim tracks
          vector<PSimHit> simHits_ass = theHitAssociator.associateHit(**recHit);
          // check the hits
          for(std::vector<PSimHit>::const_iterator assSimHit = simHits_ass.begin();
                                                   assSimHit != simHits_ass.end(); assSimHit++)  {
             if(assSimHit->processType() == 4 || assSimHit->processType() == 2)
               fromInt = false;
          }
          // move to the next recHit
          if(!fromInt)
            continue;
          for(std::vector<PSimHit>::const_iterator assSimHit = simHits_ass.begin();
                                                   assSimHit != simHits_ass.end(); assSimHit++)  {
             if(alreadyFound)
               break;
             if(assSimHit->processType() != 4 && assSimHit->processType() != 2) {
              // filling ntuple
               knownHits.push_back(*recHit);

               if((pixelDet->subDetector() == GeomDetEnumerators::PixelBarrel) && (layer == desLayer) && eta_corr<3.0 && eta_corr>2.5)
                 interHits_etaP6++;
               if((pixelDet->subDetector() == GeomDetEnumerators::PixelBarrel) && (layer == desLayer) && eta_corr<2.5 && eta_corr>2.0)
                 interHits_etaP5++;
               if((pixelDet->subDetector() == GeomDetEnumerators::PixelBarrel) && (layer == desLayer) && eta_corr<=2.0 && eta_corr>1.5)
                 interHits_etaP4++;
               if((pixelDet->subDetector() == GeomDetEnumerators::PixelBarrel) && (layer == desLayer) && eta_corr<=1.5 && eta_corr>1.0)
                 interHits_etaP3++;
               if((pixelDet->subDetector() == GeomDetEnumerators::PixelBarrel) && (layer == desLayer) && eta_corr<=1.0 && eta_corr>0.5)
                 interHits_etaP2++;
               if((pixelDet->subDetector() == GeomDetEnumerators::PixelBarrel) && (layer == desLayer) && eta_corr<=0.5 && eta_corr>0.0)
                 interHits_etaP1++;
               if((pixelDet->subDetector() == GeomDetEnumerators::PixelBarrel) && (layer == desLayer) && eta_corr<=0.0 && eta_corr>-0.5)
                 interHits_etaN1++;
               if((pixelDet->subDetector() == GeomDetEnumerators::PixelBarrel) && (layer == desLayer) && eta_corr<=-0.5 && eta_corr>-1.0)
                 interHits_etaN2++;
               if((pixelDet->subDetector() == GeomDetEnumerators::PixelBarrel) && (layer == desLayer) && eta_corr<=-1.0 && eta_corr>-1.5)
                 interHits_etaN3++;
               if((pixelDet->subDetector() == GeomDetEnumerators::PixelBarrel) && (layer == desLayer) && eta_corr<=-1.5 && eta_corr>-2.0)
                 interHits_etaN4++;
               if((pixelDet->subDetector() == GeomDetEnumerators::PixelBarrel) && (layer == desLayer) && eta_corr<=-2.0 && eta_corr>-2.5)
                 interHits_etaN5++;
               if((pixelDet->subDetector() == GeomDetEnumerators::PixelBarrel) && (layer == desLayer) && eta_corr<=-2.5 && eta_corr>-3.0)
                 interHits_etaN6++;

               alreadyFound = true;                
             }
          }
//       }
     }
  }    

  cerr << " (number of hits from interaction: " << interHits_etaP5+interHits_etaP4+interHits_etaP3+interHits_etaP2+interHits_etaP1+interHits_etaN1+interHits_etaN2+interHits_etaN3+interHits_etaN4+interHits_etaN5 << ")" << endl; 
  vector<float> result_inter;
  result_inter.push_back(interHits_etaP6);
  result_inter.push_back(interHits_etaP5);
  result_inter.push_back(interHits_etaP4);
  result_inter.push_back(interHits_etaP3);
  result_inter.push_back(interHits_etaP2);
  result_inter.push_back(interHits_etaP1);
  result_inter.push_back(interHits_etaN1);
  result_inter.push_back(interHits_etaN2);
  result_inter.push_back(interHits_etaN3);
  result_inter.push_back(interHits_etaN4);
  result_inter.push_back(interHits_etaN5);
  result_inter.push_back(interHits_etaN6);
  result_inter.push_back(cluster_counter);

  if(desLayer==1)
    NInter->Fill(&result_inter[0]);
  if(desLayer==2)
    nd_NInter->Fill(&result_inter[0]);
  if(desLayer==3)
    rd_NInter->Fill(&result_inter[0]);
// -FINISHED-

// primary non-loopers below the cut
// -STARTS-
//  cerr<< " Below part starts." << endl;
  int belowHits_etaP6 = 0;
  int belowHits_etaP5 = 0;
  int belowHits_etaP4 = 0;
  int belowHits_etaP3 = 0;
  int belowHits_etaP2 = 0;
  int belowHits_etaP1 = 0;
  int belowHits_etaN1 = 0;
  int belowHits_etaN2 = 0;
  int belowHits_etaN3 = 0;
  int belowHits_etaN4 = 0;
  int belowHits_etaN5 = 0;
  int belowHits_etaN6 = 0;
  vector<float> result_below;
  int addedHits = 0;
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
      // Look at the first barrel only
      if(pid.layer() == (unsigned)desLayer)
      for(SiPixelRecHitCollection::DetSet::const_iterator recHit = range.begin();
                             recHit!= range.end(); recHit++)
      {
        //check if it is passed
        bool above = false;
        for(std::vector<const SiPixelRecHit*>::const_iterator passedrecHit = passedClusters.begin(); passedrecHit != passedClusters.end(); ++passedrecHit ) {
          if(compareRecHits((*passedrecHit),&(*recHit)))
            { above = true; break; }
        }
        if(above)
          continue;
        //the real work starts
        GlobalPoint globalPosition = pixelDet->toGlobal((*recHit).localPosition());
        float x = fabs(globalPosition.x() - theBeamSpot->position().x());
        float y = fabs(globalPosition.y() - theBeamSpot->position().y());
        double R = TMath::Sqrt(x*x + y*y);
        double eta_corr = -log(tan(atan2(R,(globalPosition.z()-rver_z))/2.));
//        float eloss = recHit->cluster()->charge();
//        int clustSizeY = recHit->cluster()->sizeY();
        vector<PSimHit> simHits_ass = theHitAssociator.associateHit(*recHit);
        //associated sim hits
        bool usedRecHit = false;
        for(std::vector<PSimHit>::const_iterator assSimHit = simHits_ass.begin();
                                                 assSimHit != simHits_ass.end(); assSimHit++)  {
           if(assSimHit->processType() != 2)
             continue; 
           for(TrackingParticleCollection::size_type i=0; i < simCollection.product()->size(); ++i) {
             const TrackingParticleRef simTrack(simCollection, i);
             for(std::vector<PSimHit>::const_iterator
               simHit = simTrack->pSimHit_begin();
               simHit!= simTrack->pSimHit_end(); simHit++) {
               if(comparePSimHits(&(*simHit),&(*assSimHit))) {
                 bool onLooper = false;
                 for(vector<TrackingParticle>::const_iterator tLemma = loopers.begin(); tLemma != loopers.end(); tLemma++) {
                   if(tLemma->pt() == simTrack->pt()) {
                     onLooper = true;
                   }
                 }
                 if(!onLooper) {

                   // number of hits
                   if((pixelDet->subDetector() == GeomDetEnumerators::PixelBarrel) && (pid.layer() == (unsigned)desLayer) && eta_corr<3.0 && eta_corr>2.5)
                     belowHits_etaP6++;
                   if((pixelDet->subDetector() == GeomDetEnumerators::PixelBarrel) && (pid.layer() == (unsigned)desLayer) && eta_corr<2.5 && eta_corr>2.0)
                     belowHits_etaP5++;
                   if((pixelDet->subDetector() == GeomDetEnumerators::PixelBarrel) && (pid.layer() == (unsigned)desLayer) && eta_corr<=2.0 && eta_corr>1.5)
                     belowHits_etaP4++;
                   if((pixelDet->subDetector() == GeomDetEnumerators::PixelBarrel) && (pid.layer() == (unsigned)desLayer) && eta_corr<=1.5 && eta_corr>1.0)
                     belowHits_etaP3++;
                   if((pixelDet->subDetector() == GeomDetEnumerators::PixelBarrel) && (pid.layer() == (unsigned)desLayer) && eta_corr<=1.0 && eta_corr>0.5)
                     belowHits_etaP2++;
                   if((pixelDet->subDetector() == GeomDetEnumerators::PixelBarrel) && (pid.layer() == (unsigned)desLayer) && eta_corr<=0.5 && eta_corr>0.0)
                     belowHits_etaP1++;
                   if((pixelDet->subDetector() == GeomDetEnumerators::PixelBarrel) && (pid.layer() == (unsigned)desLayer) && eta_corr<=0.0 && eta_corr>-0.5)
                     belowHits_etaN1++;
                   if((pixelDet->subDetector() == GeomDetEnumerators::PixelBarrel) && (pid.layer() == (unsigned)desLayer) && eta_corr<=-0.5 && eta_corr>-1.0)
                     belowHits_etaN2++;
                   if((pixelDet->subDetector() == GeomDetEnumerators::PixelBarrel) && (pid.layer() == (unsigned)desLayer) && eta_corr<=-1.0 && eta_corr>-1.5)
                     belowHits_etaN3++;
                   if((pixelDet->subDetector() == GeomDetEnumerators::PixelBarrel) && (pid.layer() == (unsigned)desLayer) && eta_corr<=-1.5 && eta_corr>-2.0)
                     belowHits_etaN4++;
                   if((pixelDet->subDetector() == GeomDetEnumerators::PixelBarrel) && (pid.layer() == (unsigned)desLayer) && eta_corr<=-2.0 && eta_corr>-2.5)
                     belowHits_etaN5++;
                   if((pixelDet->subDetector() == GeomDetEnumerators::PixelBarrel) && (pid.layer() == (unsigned)desLayer) && eta_corr<=-2.5 && eta_corr>-3.0)
                     belowHits_etaN6++;

                   addedHits++;
                   usedRecHit = true;
                   break;
                 }
               }
             }
             if(usedRecHit)
               break;
           }          
           if(usedRecHit)
             break;
        }
      }
    }
  }
  cerr<< " number of added hits: " << addedHits << endl;
  result_below.push_back(belowHits_etaP6);
  result_below.push_back(belowHits_etaP5);
  result_below.push_back(belowHits_etaP4);
  result_below.push_back(belowHits_etaP3);
  result_below.push_back(belowHits_etaP2);
  result_below.push_back(belowHits_etaP1);
  result_below.push_back(belowHits_etaN1);
  result_below.push_back(belowHits_etaN2);
  result_below.push_back(belowHits_etaN3);
  result_below.push_back(belowHits_etaN4);
  result_below.push_back(belowHits_etaN5);
  result_below.push_back(belowHits_etaN6);
  result_below.push_back(cluster_counter);

  if(desLayer==1)
    NBelow->Fill(&result_below[0]);
  if(desLayer==2)
    nd_NBelow->Fill(&result_below[0]);
  if(desLayer==3)
    rd_NBelow->Fill(&result_below[0]);
// -FINISHED-

// geo part -STARTS- here
// use the passed clusters if we add only non-duplicated hits before
  vector<float> result_geo;
  int geoadded = 0;
  int geoHits_etaP6 = 0;
  int geoHits_etaP5 = 0;
  int geoHits_etaP4 = 0;
  int geoHits_etaP3 = 0;
  int geoHits_etaP2 = 0;
  int geoHits_etaP1 = 0;
  int geoHits_etaN1 = 0;
  int geoHits_etaN2 = 0;
  int geoHits_etaN3 = 0;
  int geoHits_etaN4 = 0;
  int geoHits_etaN5 = 0;
  int geoHits_etaN6 = 0;
  for(vector<TrackingParticle>::const_iterator tPR = geoPrims.begin(); tPR != geoPrims.end(); tPR++) {
    for(std::vector<PSimHit>::const_iterator
        simHit = tPR->pSimHit_begin();
        simHit!= tPR->pSimHit_end(); simHit++)  {
       bool nextOne = false;
       if(simHit->processType()==2)
       for(SiPixelRecHitCollection::const_iterator detunit_iter = theHits->begin();
                                                detunit_iter!= theHits->end(); detunit_iter++)
       {
         if(nextOne)
           break;
         SiPixelRecHitCollection::DetSet range = *detunit_iter;
         unsigned int id = range.detId();
         const PixelGeomDetUnit* pixelDet =
           dynamic_cast<const PixelGeomDetUnit*> (theTracker->idToDet((id)));

         PXBDetId pid(id);

         // Take all hits
         if(pid.subdetId() == PixelSubdetector::PixelBarrel)
         {
          // Look at the first barrel only
           if(pid.layer() == (unsigned)desLayer)
           for(SiPixelRecHitCollection::DetSet::const_iterator recHit = range.begin();
                                  recHit!= range.end(); recHit++)
           {
              // use only the passed clusters
//              bool passedHit = false;
//              for(std::vector<const SiPixelRecHit*>::const_iterator passedrecHit = passedClusters.begin(); 
//                                      passedrecHit != passedClusters.end(); ++passedrecHit ) {
//                if(compareRecHits((*passedrecHit),&(*recHit)))
//                  passedHit = true;
//              }
//              if(!passedHit)
//                continue;
              if(nextOne)
                break;
              GlobalPoint globalPosition = pixelDet->toGlobal((*recHit).localPosition());
              float x = fabs(globalPosition.x() - theBeamSpot->position().x());
              float y = fabs(globalPosition.y() - theBeamSpot->position().y());
              double R = TMath::Sqrt(x*x + y*y);
              double eta_corr = -log(tan(atan2(R,(globalPosition.z()-rver_z))/2.));
//              float eloss = recHit->cluster()->charge();
//              int clustSizeY = recHit->cluster()->sizeY();
              vector<PSimHit> simHits_ass = theHitAssociator.associateHit(*recHit);
              for(std::vector<PSimHit>::const_iterator assSimHit = simHits_ass.begin();
                                                       assSimHit != simHits_ass.end(); assSimHit++)  {
                if(comparePSimHits(&(*simHit),&(*assSimHit))) {
                  geoadded++;
                  knownHits.push_back(&(*recHit));

                   // number of hits
                   if((pixelDet->subDetector() == GeomDetEnumerators::PixelBarrel) && (pid.layer() == (unsigned)desLayer) && eta_corr<3.0 && eta_corr>2.5)
                     geoHits_etaP6++;
                   if((pixelDet->subDetector() == GeomDetEnumerators::PixelBarrel) && (pid.layer() == (unsigned)desLayer) && eta_corr<2.5 && eta_corr>2.0)
                     geoHits_etaP5++;
                   if((pixelDet->subDetector() == GeomDetEnumerators::PixelBarrel) && (pid.layer() == (unsigned)desLayer) && eta_corr<=2.0 && eta_corr>1.5)
                     geoHits_etaP4++;
                   if((pixelDet->subDetector() == GeomDetEnumerators::PixelBarrel) && (pid.layer() == (unsigned)desLayer) && eta_corr<=1.5 && eta_corr>1.0)
                     geoHits_etaP3++;
                   if((pixelDet->subDetector() == GeomDetEnumerators::PixelBarrel) && (pid.layer() == (unsigned)desLayer) && eta_corr<=1.0 && eta_corr>0.5)
                     geoHits_etaP2++;
                   if((pixelDet->subDetector() == GeomDetEnumerators::PixelBarrel) && (pid.layer() == (unsigned)desLayer) && eta_corr<=0.5 && eta_corr>0.0)
                     geoHits_etaP1++;
                   if((pixelDet->subDetector() == GeomDetEnumerators::PixelBarrel) && (pid.layer() == (unsigned)desLayer) && eta_corr<=0.0 && eta_corr>-0.5)
                     geoHits_etaN1++;
                   if((pixelDet->subDetector() == GeomDetEnumerators::PixelBarrel) && (pid.layer() == (unsigned)desLayer) && eta_corr<=-0.5 && eta_corr>-1.0)
                     geoHits_etaN2++;
                   if((pixelDet->subDetector() == GeomDetEnumerators::PixelBarrel) && (pid.layer() == (unsigned)desLayer) && eta_corr<=-1.0 && eta_corr>-1.5)
                     geoHits_etaN3++;
                   if((pixelDet->subDetector() == GeomDetEnumerators::PixelBarrel) && (pid.layer() == (unsigned)desLayer) && eta_corr<=-1.5 && eta_corr>-2.0)
                     geoHits_etaN4++;
                   if((pixelDet->subDetector() == GeomDetEnumerators::PixelBarrel) && (pid.layer() == (unsigned)desLayer) && eta_corr<=-2.0 && eta_corr>-2.5)
                     geoHits_etaN5++;
                   if((pixelDet->subDetector() == GeomDetEnumerators::PixelBarrel) && (pid.layer() == (unsigned)desLayer) && eta_corr<=-2.5 && eta_corr>-3.0)
                     geoHits_etaN6++;

                  nextOne = true;
                  break;  // if one hit is found we should aim for the next simTrack (by definition on geomPrims)
                } 
             }
           }
         }
       }
       if(nextOne)
         break;
    }
  }
  cerr<< " (number of geo hits removed: " << geoadded << ")" << endl;
  result_geo.push_back(geoHits_etaP6);
  result_geo.push_back(geoHits_etaP5);
  result_geo.push_back(geoHits_etaP4);
  result_geo.push_back(geoHits_etaP3);
  result_geo.push_back(geoHits_etaP2);
  result_geo.push_back(geoHits_etaP1);
  result_geo.push_back(geoHits_etaN1);
  result_geo.push_back(geoHits_etaN2);
  result_geo.push_back(geoHits_etaN3);
  result_geo.push_back(geoHits_etaN4);
  result_geo.push_back(geoHits_etaN5);
  result_geo.push_back(geoHits_etaN6);
  result_geo.push_back(cluster_counter);

  if(desLayer==1)
    NGeo->Fill(&result_geo[0]);
  if(desLayer==2)
    nd_NGeo->Fill(&result_geo[0]);
  if(desLayer==3)
    rd_NGeo->Fill(&result_geo[0]);
// -FINISHED-

// -not properly associated recHits- -STARTS-
  int strangeHits_etaP6 = 0;
  int strangeHits_etaP5 = 0;
  int strangeHits_etaP4 = 0;
  int strangeHits_etaP3 = 0;
  int strangeHits_etaP2 = 0;
  int strangeHits_etaP1 = 0;
  int strangeHits_etaN1 = 0;
  int strangeHits_etaN2 = 0;
  int strangeHits_etaN3 = 0;
  int strangeHits_etaN4 = 0;
  int strangeHits_etaN5 = 0;
  int strangeHits_etaN6 = 0;
  
  std::vector<const SiPixelRecHit*> strangeRecHits;
  for(SiPixelRecHitCollection::const_iterator detunit_iter = theHits->begin();
                                           detunit_iter!= theHits->end(); detunit_iter++)
  {
     // vertex check, it never fires
//     if(vertices->size()!=1)
//       break;

     SiPixelRecHitCollection::DetSet range = *detunit_iter;
     unsigned int id = range.detId();
     const PixelGeomDetUnit* pixelDet =  dynamic_cast<const PixelGeomDetUnit*> (theTracker->idToDet((id)));

     PXBDetId pid(id);
     // Take all hits
     if(pid.subdetId() == PixelSubdetector::PixelBarrel && pid.layer()==(unsigned)desLayer) {
       for(SiPixelRecHitCollection::DetSet::const_iterator recHit = range.begin();
                                                   recHit!= range.end(); recHit++)
       {
          // only use the passed clusters
          bool passedHit = false;
          for(std::vector<const SiPixelRecHit*>::const_iterator passedrecHit = passedClusters.begin(); 
                                  passedrecHit != passedClusters.end(); ++passedrecHit ) {
            if(compareRecHits((*passedrecHit),&(*recHit)))
              passedHit = true;
          }
          if(!passedHit)
            continue;

          GlobalPoint gpos = pixelDet->toGlobal(recHit->localPosition());
          float x = fabs(gpos.x() - theBeamSpot->position().x());
          float y = fabs(gpos.y() - theBeamSpot->position().y());
          double R = TMath::Sqrt(x*x + y*y);
          double eta_corr = -log(tan(atan2(R,(gpos.z()-rver_z))/2.));
//          float eloss = recHit->cluster()->charge();
//          int clustSizeY = recHit->cluster()->sizeY();
          bool Found = false;
          // associate 
          vector<PSimHit> simHits_ass = theHitAssociator.associateHit(*recHit);
          for(std::vector<PSimHit>::const_iterator assSimHit = simHits_ass.begin();
                                                   assSimHit != simHits_ass.end(); assSimHit++)  {
             const PixelGeomDetUnit* pgdu = dynamic_cast<const PixelGeomDetUnit*>(geom->idToDetUnit(assSimHit->detUnitId()));
             PXBDetId pdetId = PXBDetId(assSimHit->detUnitId());
//             int layer=pdetId.layer();
             GlobalPoint globalPosition = pgdu->toGlobal(assSimHit->localPosition());
             if(assSimHit->processType()==2 && (globalPosition-gpos).mag()>0.1) {
               // check wether we removed it already
               for(std::vector<const SiPixelRecHit*>::const_iterator knownHit = knownHits.begin();
                                                                     knownHit != knownHits.end(); ++knownHit ) {
                if(compareRecHits((*knownHit),&(*recHit)))
                  Found = true;
               }
               if(!Found) {
                 strangeRecHits.push_back(&(*recHit));

                 // number of hits
                 if((pixelDet->subDetector() == GeomDetEnumerators::PixelBarrel) && (pid.layer() == (unsigned)desLayer) && eta_corr<3.0 && eta_corr>2.5)
                   strangeHits_etaP6++;
                 if((pixelDet->subDetector() == GeomDetEnumerators::PixelBarrel) && (pid.layer() == (unsigned)desLayer) && eta_corr<2.5 && eta_corr>2.0)
                   strangeHits_etaP5++;
                 if((pixelDet->subDetector() == GeomDetEnumerators::PixelBarrel) && (pid.layer() == (unsigned)desLayer) && eta_corr<=2.0 && eta_corr>1.5)
                   strangeHits_etaP4++;
                 if((pixelDet->subDetector() == GeomDetEnumerators::PixelBarrel) && (pid.layer() == (unsigned)desLayer) && eta_corr<=1.5 && eta_corr>1.0)
                   strangeHits_etaP3++;
                 if((pixelDet->subDetector() == GeomDetEnumerators::PixelBarrel) && (pid.layer() == (unsigned)desLayer) && eta_corr<=1.0 && eta_corr>0.5)
                   strangeHits_etaP2++;
                 if((pixelDet->subDetector() == GeomDetEnumerators::PixelBarrel) && (pid.layer() == (unsigned)desLayer) && eta_corr<=0.5 && eta_corr>0.0)
                   strangeHits_etaP1++;
                 if((pixelDet->subDetector() == GeomDetEnumerators::PixelBarrel) && (pid.layer() == (unsigned)desLayer) && eta_corr<=0.0 && eta_corr>-0.5)
                   strangeHits_etaN1++;
                 if((pixelDet->subDetector() == GeomDetEnumerators::PixelBarrel) && (pid.layer() == (unsigned)desLayer) && eta_corr<=-0.5 && eta_corr>-1.0)
                   strangeHits_etaN2++;
                 if((pixelDet->subDetector() == GeomDetEnumerators::PixelBarrel) && (pid.layer() == (unsigned)desLayer) && eta_corr<=-1.0 && eta_corr>-1.5)
                   strangeHits_etaN3++;
                 if((pixelDet->subDetector() == GeomDetEnumerators::PixelBarrel) && (pid.layer() == (unsigned)desLayer) && eta_corr<=-1.5 && eta_corr>-2.0)
                   strangeHits_etaN4++;
                 if((pixelDet->subDetector() == GeomDetEnumerators::PixelBarrel) && (pid.layer() == (unsigned)desLayer) && eta_corr<=-2.0 && eta_corr>-2.5)
                   strangeHits_etaN5++;
                 if((pixelDet->subDetector() == GeomDetEnumerators::PixelBarrel) && (pid.layer() == (unsigned)desLayer) && eta_corr<=-2.5 && eta_corr>-3.0)
                   strangeHits_etaN6++;

                 break; //go to the next recHit
               }
             }
          }
       }
     }
  }
  cerr<< " number of strangeRecHits: " << strangeRecHits.size() << endl;
  vector<float> result_strange;
  result_strange.push_back(strangeHits_etaP6);
  result_strange.push_back(strangeHits_etaP5);
  result_strange.push_back(strangeHits_etaP4);
  result_strange.push_back(strangeHits_etaP3);
  result_strange.push_back(strangeHits_etaP2);
  result_strange.push_back(strangeHits_etaP1);
  result_strange.push_back(strangeHits_etaN1);
  result_strange.push_back(strangeHits_etaN2);
  result_strange.push_back(strangeHits_etaN3);
  result_strange.push_back(strangeHits_etaN4);
  result_strange.push_back(strangeHits_etaN5);
  result_strange.push_back(strangeHits_etaN6);
  result_strange.push_back(cluster_counter);

  if(desLayer==1)
    NStrange->Fill(&result_strange[0]);
  if(desLayer==2)
    nd_NStrange->Fill(&result_strange[0]);
  if(desLayer==3)
    rd_NStrange->Fill(&result_strange[0]);
// -FINISHED-

// check knownhits -STARTS-
// use passedCluster!! and add prims below the cut!!
// known hits = loopers + decays + interactions + geo
/*
  int numPrimaries = T_truth_etaP5+T_truth_etaP4+T_truth_etaP3+T_truth_etaP2+T_truth_etaP1+T_truth_etaN1+T_truth_etaN2+T_truth_etaN3+T_truth_etaN4+T_truth_etaN5;
  cerr<< " number of primary particles: " << numPrimaries << endl;
  cerr<< " number of known cluster (we remove these): " << knownHits.size() << endl;
  for(SiPixelRecHitCollection::id_iterator id = theHits->id_begin();
                                           id!= theHits->id_end(); id++)
  {
    SiPixelRecHitCollection::range range = theHits->get((*id));
    const PixelGeomDetUnit* pixelDet =
      dynamic_cast<const PixelGeomDetUnit*> (theTracker->idToDet((*id)));

    // Take all hits
    if((*id).subdetId() == PixelSubdetector::PixelBarrel)
    {
      PXBDetId pid(*id);

      // Look at the first barrel only
      if(pid.layer() == desLayer)
      for(SiPixelRecHitCollection::DataContainer::const_iterator recHit = range.first;
                             recHit!= range.second; recHit++)
      {
         // use passed clusters
         bool passedHit = false;
         for(std::vector<const SiPixelRecHit*>::const_iterator passedrecHit = passedClusters.begin();
                                  passedrecHit != passedClusters.end(); ++passedrecHit ) {
            if(compareRecHits((*passedrecHit),&(*recHit)))
              passedHit = true;
         }
         if(!passedHit)
           continue;

         bool Found = false;
         for(std::vector<const SiPixelRecHit*>::const_iterator knownHit = knownHits.begin();
                                                   knownHit != knownHits.end(); ++knownHit ) {
            if(compareRecHits((*knownHit),&(*recHit)))
              Found=true;
         }
         if(!Found) {
           //find the sim track
           bool nextRecHit = false;
           vector<PSimHit> simHits_ass = theHitAssociator.associateHit(*recHit);
           for(std::vector<PSimHit>::const_iterator assSimHit = simHits_ass.begin();
                                                    assSimHit != simHits_ass.end(); assSimHit++)  {
             if(assSimHit->processType()==2)  
             for(TrackingParticleCollection::size_type i=0; i < simCollection.product()->size(); ++i) {
               const TrackingParticleRef simTrack(simCollection, i);
               for(std::vector<PSimHit>::const_iterator
                    simHit = simTrack->pSimHit_begin();
                    simHit!= simTrack->pSimHit_end(); simHit++) {
                 if(comparePSimHits(&(*simHit),&(*assSimHit))) {
                    GlobalPoint globalPosition = pixelDet->toGlobal((*recHit).localPosition());
                    double R = TMath::Sqrt(globalPosition.x()*globalPosition.x()+globalPosition.y()*globalPosition.y());
                    cerr<<" Found a _good_ primary hit" << endl;
                    cerr<<"  simTrack infos: pt:  " << simTrack->pt() << ", id: "<< simTrack->pdgId() << endl;
                    cerr<<"  production time:     " << simTrack->parentVertex()->position().T() << endl;
                    cerr<<"  recHit trans. dist.: " << R << endl;
                    cerr<<"  recHit z pos:        " << globalPosition.z() << endl;
                    cerr<<"  time of flight:      " << assSimHit->timeOfFlight() << endl;
                    nextRecHit = true;
                    break;
                 }
               }     
               if(nextRecHit)
                 break;
             }
             if(nextRecHit)
               break;
           }
         }
      } 
    }
  }
// -FINISHED-
*/
}

/*****************************************************************************/
bool ChargedMultiplicityAnalyzer_new::isAtEdge
  (const RectangularPixelTopology* topology, const SiPixelRecHit & recHit)
{
  return topology->isItEdgePixelInX(recHit.cluster()->minPixelCol()) ||
         topology->isItEdgePixelInX(recHit.cluster()->maxPixelCol()) ||
         topology->isItEdgePixelInY(recHit.cluster()->minPixelRow()) ||
         topology->isItEdgePixelInY(recHit.cluster()->maxPixelRow());
}

/*****************************************************************************/
vector<PSimHit> ChargedMultiplicityAnalyzer_new::orderPSimHits(vector<PSimHit> simHits)
{
  vector<PSimHit> ordered;
  PSimHit * earliest = 0;
  vector<PSimHit>::iterator lemma;
  float pmax = 0.;
  int i = 0;
  int boundary = simHits.size();
  for(i=0; i < boundary; i++) {
     for(vector<PSimHit>::iterator simHit = simHits.begin();
         simHit!= simHits.end(); simHit++) {
        if(simHit->pabs() > pmax)
          { earliest = &(*simHit); pmax=simHit->pabs(); lemma = simHit; }
     }
     pmax = 0.;
     simHits.erase(lemma);
     ordered.push_back(*earliest);
  }
  return ordered;
}

/*****************************************************************************/
void ChargedMultiplicityAnalyzer_new::analyze
  (const edm::Event& ev, const edm::EventSetup& es)
{
//  std::cerr<<"[ChargedMultiplicityAnalyzer_new] (1)" << std::endl;

  // Get tracker geometry
  edm::ESHandle<TrackerGeometry> tracker;
  es.get<TrackerDigiGeometryRecord>().get(tracker);
  theTracker = tracker.product();

  // Beam spot
  edm::Handle<BeamSpot>      beamSpotHandle;
  ev.getByLabel("offlineBeamSpot", beamSpotHandle);
  theBeamSpot = beamSpotHandle.product();

/*
  // Get magnetic field
  edm::ESHandle<MagneticField> magField;
  es.get<IdealMagneticFieldRecord>().get(magField);
  const MagneticField* theMagField = magField.product();
  vector<float> magf;
  magf.push_back(theMagField->inTesla(GlobalPoint(0,0,0)).x());
  magf.push_back(theMagField->inTesla(GlobalPoint(0,0,0)).y());
  magf.push_back(theMagField->inTesla(GlobalPoint(0,0,0)).z());
  nMagField->Fill(&magf[0]);
*/
  // Get simulated
  edm::Handle<vector<PSimHit> > simHits;
  ev.getByLabel("g4SimHits","TrackerHitsPixelBarrelLowTof", simHits);

  // Get reconstructed
    //tracks
  edm::Handle<reco::TrackCollection>  recCollection;
  ev.getByLabel("hltPixelTracksForMinBias", recCollection);
//  ev.getByLabel(trackCollectionLabel, recCollection);

    //calorimeter
    //Richard
  Handle<HcalTrigPrimDigiCollection> tpg;
//  ev.getByType(tpg);
//  ev.getByLabel("hcaldigi",tpg);
  ev.getByLabel("hcalDigis",tpg);

  edm::Handle<CaloTowerCollection> towers; 
//  ev.getByLabel("towerMaker",towers); 
//  ev.getByLabel("hltTowerMakerForAll",towers); 
//  ev.getByLabel("hltTowerMakerForJets",towers);
//  ev.getByLabel("hltTowerMakerForMuons",towers);
//  ev.getByType(towers);
  ev.getByLabel("towerMaker",towers);

  // Get siPixelRecHits
  edm::Handle<SiPixelRecHitCollection> siPixelRecCollection;
//  ev.getByType(siPixelRecCollection);
  ev.getByLabel(src_,siPixelRecCollection);

  // Get vertices
//  edm::Handle<TrackingVertexCollection> TVCollection;
//  ev.getByType(TVCollection);
//  ev.getByLabel("trackingtruth","VertexTruth",TVCollection);
//  ev.getByLabel("mergedtruth","VertexTruth",TVCollection);
//  ev.getByLabel("mergedtruth","MergedTrackTruth",TVCollection);
/*
  edm::Handle<reco::VertexCollection> vertexCollection;
  ev.getByType(vertexCollection);
  const reco::VertexCollection * vertices = vertexCollection.product();
*/
//  std::cerr<<"Number of vertices: "<< vertices->size()<<std::endl;

  //MC
  Handle<HepMCProduct> evt;
  ev.getByType(evt);
//  ev.getByLabel("source",evt); //give strange procID number: 1,4,5,6,7
//  ev.getByLabel("generator",evt); /give strange procID number: 1,4,5,6,7
  HepMC::GenEvent * myGenEvent = new  HepMC::GenEvent(*(evt->GetEvent()));

//  std::cerr<<"[ChargedMultiplicityAnalyzer_new] (2)" << std::endl;

  // Analyze
//  checkVertices(vertices, TVCollection, recCollection, myGenEvent);

//  checkVertices(TVCollection, recCollection, myGenEvent);

//  FirstSimOnFirst(siPixelRecCollection, vertices, ev, es);
  FirstSimOnFirst(siPixelRecCollection, ev, es);

//  multiplicityProperties(ev, es, towers, siPixelRecCollection, vertices, myGenEvent, recCollection, tpg, 1);
//  multiplicityProperties(ev, es, towers, siPixelRecCollection, vertices, myGenEvent, recCollection, tpg, 2);
//  multiplicityProperties(ev, es, towers, siPixelRecCollection, vertices, myGenEvent, recCollection, tpg, 3);
  multiplicityProperties(ev, es, towers, siPixelRecCollection, myGenEvent, recCollection, tpg, 1);
  multiplicityProperties(ev, es, towers, siPixelRecCollection, myGenEvent, recCollection, tpg, 2);
  multiplicityProperties(ev, es, towers, siPixelRecCollection, myGenEvent, recCollection, tpg, 3);

//  checkEta(ev, es, towers, siPixelRecCollection, vertices, myGenEvent);
//  checkSimTracks(ev, es, siPixelRecCollection);

//  clusterVertices(ev, es, vertices, siPixelRecCollection);
  clusterVertices(ev, es, siPixelRecCollection);
}


