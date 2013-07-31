////////////////////
//
//  EXPECT ONLY ONE VERTEX!!
//  ==> CHECK getVertexZ
//
////////////////////


// $Id: HI_simple_nosiminfo.cc,v 1.11 2011/11/09 14:00:58 krajczar Exp $

#include "../interface/HI_simple_nosiminfo.h"

/*****************************************************************************/
HI_simple_nosiminfo::HI_simple_nosiminfo(const edm::ParameterSet& pset)
{
  resultFileLabel       = pset.getParameter<string>("file");
  hasL1Triggers_        = pset.getParameter<bool>("hasL1Triggers");
  produceVertexLocally_ = pset.getParameter<bool>("produceVertexLocally");
  src_                  = pset.getParameter<edm::InputTag>("src");
  vertexColl_           = pset.getParameter<edm::InputTag>("vertexColl");
  triggerLabel_         = pset.getParameter<edm::InputTag>("triggerLabel");
}

/*****************************************************************************/
HI_simple_nosiminfo::~HI_simple_nosiminfo()
{
}

/*****************************************************************************/
void HI_simple_nosiminfo::beginJob()
{
  // Root
  resultFile = new TFile(resultFileLabel.c_str(),"recreate","",6);
  TDirectory::TContext context(resultFile);

  // HF
  nHF_towers = new TNtuple("nHF_towers","nHF_towers",
     "centBin_KK:centBin:energy:eta:rver_z:isTrigger_3");
  nHF_event = new TNtuple("nHF_event","nHF_event",
     "centBin_KK:centBin:posTowers:posTowers_3:posTowers_20:negTowers:negTowers_3:negTowers_20:posET:posET_3:posET_20:negET:negET_3:negET_20:posEnergy:posEnergy_3:posEnergy_20:negEnergy:negEnergy_3:negEnergy_20:rver_z:isTrigger_3");
  nHF_Y_event = new TNtuple("nHF_Y_event","nHF_Y_event",
     "centBin:posET:negET:posEnergy:negEnergy:posPT:negPT:rver_z:isTrigger_3");

  //multiplicity
  hNum_nd = new TH1F("hNum_nd","hNum_nd",1,-0.5,0.5);
  hNum_nsd = new TH1F("hNum_nsd","hNum_nsd",1,-0.5,0.5);
  hNum_nsd_trig = new TH1F("hNum_nsd_trig","hNum_nsd_trig",1,-0.5,0.5);
  hNum_sd_trig = new TH1F("hNum_sd_trig","hNum_sd_trig",1,-0.5,0.5);

  multProp = new TNtuple("multProp","multProp",
     "EdVert:EtHFhitSum:EtHFhitSumPlus:EtHFhitSumMinus:EtHFtowerSum:EtHFtowerSumPlus:EtHFtowerSumMinus:centBin_KK:centBin:lowEdge:NPart:NPartSigma:NColl:NCollSigma:NHard:NHardSigma:B:BSigma:clusters:rver_z:CandMaker_coinc_1:CandMaker_coinc_2:CandMaker_coinc_3:CandMaker_coinc_4:isTrigger_1:isTrigger_2:isTrigger_3:HLT_HIMinBiasHfOrBSC_Core:HLT_HIMinBiasHfOrBSC_v1:HLT_HIZeroBias_v1:HLT_HIZeroBiasPixel_SingleTrack:HLT_HIMinBiasBSC_v1:HLT_HIMinBiasBSC_OR_v1:HLT_HIMinBiasBSC_Core:HLT_HIMinBiasBSC_OR_Core:HLT_HIMinBiasHF_v1:HLT_HIMinBiasPixel_SingleTrack:HLT_HIL1Tech_BSC_minBias:HLT_HIL1Tech_BSC_minBias_OR:HLT_HIL1Tech_BSC_HighMultiplicity:HLT_HIL1Tech_HCAL_HF:HLT_HIClusterVertexCompatibility_v1:HLT_HICentralityVeto_v1:HLT_HIL1ETT30:HLT_HIL1ETT30_Core:HLT_HIL1ETT60:HLT_HIL1ETT60_Core:bit0:bit1:bit2:bit3:bit4:bit5:bit6:bit7:bit8:bit9:bit10:bit11:bit12:bit32:bit33:bit34:bit35:bit36:bit37:bit38:bit39:bit40:bit41:bit42:bit43:bit55:bit60:bit61:bit62:bit63:L1_ZeroBias:L1_BscMinBiasOR_BptxAND:L1_BscMinBiasInnerThreshold1_BptxAND:L1_BscMinBiasInnerThreshold2_BptxAND:L1_BscMinBiasThreshold1_BptxAND:L1_BscMinBiasThreshold2_BptxAND:L1_DoubleHfBitCountsRing1_P1N1:L1_DoubleHfBitCountsRing2_P1N1:L1_DoubleHfRingEtSumsRing1_P4N4:L1_DoubleHfRingEtSumsRing1_P200N200:L1_DoubleHfRingEtSumsRing2_P4N4:L1_DoubleHfRingEtSumsRing2_P200N200:L1_ZdcScintTightVertex_BptxAND:L1_ZdcScintLooseVertex_BptxAND:L1_BscMinBiasThreshold1:L1_ZdcCaloPlus:L1_ZdcCaloMinus:L1_ZdcCaloPlus_BptxAND:L1_ZdcCaloMinus_BptxAND:L1_ZdcCaloPlus_ZdcCaloMinus_BptxAND:L1_HcalHfMmOrPpOrPm:L1_HcalHfCoincidencePm:L1_HcalHfMmpOrMpp:L1_HcalHoTotalOR:L1_ETT60:L1_ETT60_BptxAND:L1_ZdcCaloPlus_ZdcCaloMinus:L1_BptxMinus:L1_BptxPlus:L1_BptxPlusORMinus:L1_ETT30_BptxAND:L1_ETT30:L1_ZdcScintTightVertex:L1_ZdcScintPlus:L1_ZdcScintMinus:L1_BscMinBiasInnerThreshold1:L1_BptxPlusANDMinus:L1_BscMinBiasOR_BptxPlusORMinus:L1_HcalHfCoincPmORBscMinBiasThresh1_BptxAND:L1_HcalHfCoincPmORBscMinBiasThresh2_BptxAND:numVtx:numEv:clusters_on_layers:clustSizeY_etaP6:clustSizeY_etaP5:clustSizeY_etaP4:clustSizeY_etaP3:clustSizeY_etaP2:clustSizeY_etaP1:clustSizeY_etaN1:clustSizeY_etaN2:clustSizeY_etaN3:clustSizeY_etaN4:clustSizeY_etaN5:clustSizeY_etaN6:cluster_counter");
  nd_multProp = new TNtuple("nd_multProp","nd_multProp",
     "EdVert:EtHFhitSum:EtHFhitSumPlus:EtHFhitSumMinus:EtHFtowerSum:EtHFtowerSumPlus:EtHFtowerSumMinus:centBin_KK:centBin:lowEdge:NPart:NPartSigma:NColl:NCollSigma:NHard:NHardSigma:B:BSigma:clusters:rver_z:CandMaker_coinc_1:CandMaker_coinc_2:CandMaker_coinc_3:CandMaker_coinc_4:isTrigger_1:isTrigger_2:isTrigger_3:HLT_HIMinBiasHfOrBSC_Core:HLT_HIMinBiasHfOrBSC_v1:HLT_HIZeroBias_v1:HLT_HIZeroBiasPixel_SingleTrack:HLT_HIMinBiasBSC_v1:HLT_HIMinBiasBSC_OR_v1:HLT_HIMinBiasBSC_Core:HLT_HIMinBiasBSC_OR_Core:HLT_HIMinBiasHF_v1:HLT_HIMinBiasPixel_SingleTrack:HLT_HIL1Tech_BSC_minBias:HLT_HIL1Tech_BSC_minBias_OR:HLT_HIL1Tech_BSC_HighMultiplicity:HLT_HIL1Tech_HCAL_HF:HLT_HIClusterVertexCompatibility_v1:HLT_HICentralityVeto_v1:HLT_HIL1ETT30:HLT_HIL1ETT30_Core:HLT_HIL1ETT60:HLT_HIL1ETT60_Core:bit0:bit1:bit2:bit3:bit4:bit5:bit6:bit7:bit8:bit9:bit10:bit11:bit12:bit32:bit33:bit34:bit35:bit36:bit37:bit38:bit39:bit40:bit41:bit42:bit43:bit55:bit60:bit61:bit62:bit63:L1_ZeroBias:L1_BscMinBiasOR_BptxAND:L1_BscMinBiasInnerThreshold1_BptxAND:L1_BscMinBiasInnerThreshold2_BptxAND:L1_BscMinBiasThreshold1_BptxAND:L1_BscMinBiasThreshold2_BptxAND:L1_DoubleHfBitCountsRing1_P1N1:L1_DoubleHfBitCountsRing2_P1N1:L1_DoubleHfRingEtSumsRing1_P4N4:L1_DoubleHfRingEtSumsRing1_P200N200:L1_DoubleHfRingEtSumsRing2_P4N4:L1_DoubleHfRingEtSumsRing2_P200N200:L1_ZdcScintTightVertex_BptxAND:L1_ZdcScintLooseVertex_BptxAND:L1_BscMinBiasThreshold1:L1_ZdcCaloPlus:L1_ZdcCaloMinus:L1_ZdcCaloPlus_BptxAND:L1_ZdcCaloMinus_BptxAND:L1_ZdcCaloPlus_ZdcCaloMinus_BptxAND:L1_HcalHfMmOrPpOrPm:L1_HcalHfCoincidencePm:L1_HcalHfMmpOrMpp:L1_HcalHoTotalOR:L1_ETT60:L1_ETT60_BptxAND:L1_ZdcCaloPlus_ZdcCaloMinus:L1_BptxMinus:L1_BptxPlus:L1_BptxPlusORMinus:L1_ETT30_BptxAND:L1_ETT30:L1_ZdcScintTightVertex:L1_ZdcScintPlus:L1_ZdcScintMinus:L1_BscMinBiasInnerThreshold1:L1_BptxPlusANDMinus:L1_BscMinBiasOR_BptxPlusORMinus:L1_HcalHfCoincPmORBscMinBiasThresh1_BptxAND:L1_HcalHfCoincPmORBscMinBiasThresh2_BptxAND:numVtx:numEv:clusters_on_layers:clustSizeY_etaP6:clustSizeY_etaP5:clustSizeY_etaP4:clustSizeY_etaP3:clustSizeY_etaP2:clustSizeY_etaP1:clustSizeY_etaN1:clustSizeY_etaN2:clustSizeY_etaN3:clustSizeY_etaN4:clustSizeY_etaN5:clustSizeY_etaN6:cluster_counter");
  rd_multProp = new TNtuple("rd_multProp","rd_multProp",
     "EdVert:EtHFhitSum:EtHFhitSumPlus:EtHFhitSumMinus:EtHFtowerSum:EtHFtowerSumPlus:EtHFtowerSumMinus:centBin_KK:centBin:lowEdge:NPart:NPartSigma:NColl:NCollSigma:NHard:NHardSigma:B:BSigma:clusters:rver_z:CandMaker_coinc_1:CandMaker_coinc_2:CandMaker_coinc_3:CandMaker_coinc_4:isTrigger_1:isTrigger_2:isTrigger_3:HLT_HIMinBiasHfOrBSC_Core:HLT_HIMinBiasHfOrBSC_v1:HLT_HIZeroBias_v1:HLT_HIZeroBiasPixel_SingleTrack:HLT_HIMinBiasBSC_v1:HLT_HIMinBiasBSC_OR_v1:HLT_HIMinBiasBSC_Core:HLT_HIMinBiasBSC_OR_Core:HLT_HIMinBiasHF_v1:HLT_HIMinBiasPixel_SingleTrack:HLT_HIL1Tech_BSC_minBias:HLT_HIL1Tech_BSC_minBias_OR:HLT_HIL1Tech_BSC_HighMultiplicity:HLT_HIL1Tech_HCAL_HF:HLT_HIClusterVertexCompatibility_v1:HLT_HICentralityVeto_v1:HLT_HIL1ETT30:HLT_HIL1ETT30_Core:HLT_HIL1ETT60:HLT_HIL1ETT60_Core:bit0:bit1:bit2:bit3:bit4:bit5:bit6:bit7:bit8:bit9:bit10:bit11:bit12:bit32:bit33:bit34:bit35:bit36:bit37:bit38:bit39:bit40:bit41:bit42:bit43:bit55:bit60:bit61:bit62:bit63:L1_ZeroBias:L1_BscMinBiasOR_BptxAND:L1_BscMinBiasInnerThreshold1_BptxAND:L1_BscMinBiasInnerThreshold2_BptxAND:L1_BscMinBiasThreshold1_BptxAND:L1_BscMinBiasThreshold2_BptxAND:L1_DoubleHfBitCountsRing1_P1N1:L1_DoubleHfBitCountsRing2_P1N1:L1_DoubleHfRingEtSumsRing1_P4N4:L1_DoubleHfRingEtSumsRing1_P200N200:L1_DoubleHfRingEtSumsRing2_P4N4:L1_DoubleHfRingEtSumsRing2_P200N200:L1_ZdcScintTightVertex_BptxAND:L1_ZdcScintLooseVertex_BptxAND:L1_BscMinBiasThreshold1:L1_ZdcCaloPlus:L1_ZdcCaloMinus:L1_ZdcCaloPlus_BptxAND:L1_ZdcCaloMinus_BptxAND:L1_ZdcCaloPlus_ZdcCaloMinus_BptxAND:L1_HcalHfMmOrPpOrPm:L1_HcalHfCoincidencePm:L1_HcalHfMmpOrMpp:L1_HcalHoTotalOR:L1_ETT60:L1_ETT60_BptxAND:L1_ZdcCaloPlus_ZdcCaloMinus:L1_BptxMinus:L1_BptxPlus:L1_BptxPlusORMinus:L1_ETT30_BptxAND:L1_ETT30:L1_ZdcScintTightVertex:L1_ZdcScintPlus:L1_ZdcScintMinus:L1_BscMinBiasInnerThreshold1:L1_BptxPlusANDMinus:L1_BscMinBiasOR_BptxPlusORMinus:L1_HcalHfCoincPmORBscMinBiasThresh1_BptxAND:L1_HcalHfCoincPmORBscMinBiasThresh2_BptxAND:numVtx:numEv:clusters_on_layers:clustSizeY_etaP6:clustSizeY_etaP5:clustSizeY_etaP4:clustSizeY_etaP3:clustSizeY_etaP2:clustSizeY_etaP1:clustSizeY_etaN1:clustSizeY_etaN2:clustSizeY_etaN3:clustSizeY_etaN4:clustSizeY_etaN5:clustSizeY_etaN6:cluster_counter");
  multProp_looper = new TNtuple("multProp_looper","multProp_looper",
      "EdVert:centBin_KK:centBin:lowEdge:NPart:NPartSigma:NColl:NCollSigma:NHard:NHardSigma:B:BSigma:CandMaker_coinc_1:CandMaker_coinc_2:CandMaker_coinc_3:CandMaker_coinc_4:isTrigger_1:isTrigger_2:isTrigger_3:rver_z:eta:eta_det:phi:eloss:numVtx:clustSizeY:clustSizeX:length:pixels:cluster_counter:HLT_HIMinBiasHfOrBSC_Core:HLT_HIMinBiasHfOrBSC_v1:HLT_HIZeroBias_v1:HLT_HIZeroBiasPixel_SingleTrack:HLT_HIMinBiasBSC_v1:HLT_HIMinBiasBSC_OR_v1:HLT_HIMinBiasBSC_Core:HLT_HIMinBiasBSC_OR_Core:HLT_HIMinBiasHF_v1:HLT_HIMinBiasPixel_SingleTrack:HLT_HIL1Tech_BSC_minBias:HLT_HIL1Tech_BSC_minBias_OR:HLT_HIL1Tech_BSC_HighMultiplicity:HLT_HIL1Tech_HCAL_HF:HLT_HIClusterVertexCompatibility_v1:HLT_HICentralityVeto_v1:HLT_HIL1ETT30:HLT_HIL1ETT30_Core:HLT_HIL1ETT60:HLT_HIL1ETT60_Core:bit0:bit1:bit2:bit3:bit4:bit5:bit6:bit7:bit8:bit9:bit10:bit11:bit12:bit32:bit33:bit34:bit35:bit36:bit37:bit38:bit39:bit40:bit41:bit42:bit43:bit55:bit60:bit61:bit62:bit63:L1_ZeroBias:L1_BscMinBiasOR_BptxAND:L1_BscMinBiasInnerThreshold1_BptxAND:L1_BscMinBiasInnerThreshold2_BptxAND:L1_BscMinBiasThreshold1_BptxAND:L1_BscMinBiasThreshold2_BptxAND:L1_DoubleHfBitCountsRing1_P1N1:L1_DoubleHfBitCountsRing2_P1N1:L1_DoubleHfRingEtSumsRing1_P4N4:L1_DoubleHfRingEtSumsRing1_P200N200:L1_DoubleHfRingEtSumsRing2_P4N4:L1_DoubleHfRingEtSumsRing2_P200N200:L1_ZdcScintTightVertex_BptxAND:L1_ZdcScintLooseVertex_BptxAND:L1_BscMinBiasThreshold1:L1_ZdcCaloPlus:L1_ZdcCaloMinus:L1_ZdcCaloPlus_BptxAND:L1_ZdcCaloMinus_BptxAND:L1_ZdcCaloPlus_ZdcCaloMinus_BptxAND:L1_HcalHfMmOrPpOrPm:L1_HcalHfCoincidencePm:L1_HcalHfMmpOrMpp:L1_HcalHoTotalOR:L1_ETT60:L1_ETT60_BptxAND:L1_ZdcCaloPlus_ZdcCaloMinus:L1_BptxMinus:L1_BptxPlus:L1_BptxPlusORMinus:L1_ETT30_BptxAND:L1_ETT30:L1_ZdcScintTightVertex:L1_ZdcScintPlus:L1_ZdcScintMinus:L1_BscMinBiasInnerThreshold1:L1_BptxPlusANDMinus:L1_BscMinBiasOR_BptxPlusORMinus:L1_HcalHfCoincPmORBscMinBiasThresh1_BptxAND:L1_HcalHfCoincPmORBscMinBiasThresh2_BptxAND");
  nd_multProp_looper = new TNtuple("nd_multProp_looper","nd_multProp_looper",
      "EdVert:centBin_KK:centBin:lowEdge:NPart:NPartSigma:NColl:NCollSigma:NHard:NHardSigma:B:BSigma:CandMaker_coinc_1:CandMaker_coinc_2:CandMaker_coinc_3:CandMaker_coinc_4:isTrigger_1:isTrigger_2:isTrigger_3:rver_z:eta:eta_det:phi:eloss:numVtx:clustSizeY:clustSizeX:length:pixels:cluster_counter:HLT_HIMinBiasHfOrBSC_Core:HLT_HIMinBiasHfOrBSC_v1:HLT_HIZeroBias_v1:HLT_HIZeroBiasPixel_SingleTrack:HLT_HIMinBiasBSC_v1:HLT_HIMinBiasBSC_OR_v1:HLT_HIMinBiasBSC_Core:HLT_HIMinBiasBSC_OR_Core:HLT_HIMinBiasHF_v1:HLT_HIMinBiasPixel_SingleTrack:HLT_HIL1Tech_BSC_minBias:HLT_HIL1Tech_BSC_minBias_OR:HLT_HIL1Tech_BSC_HighMultiplicity:HLT_HIL1Tech_HCAL_HF:HLT_HIClusterVertexCompatibility_v1:HLT_HICentralityVeto_v1:HLT_HIL1ETT30:HLT_HIL1ETT30_Core:HLT_HIL1ETT60:HLT_HIL1ETT60_Core:bit0:bit1:bit2:bit3:bit4:bit5:bit6:bit7:bit8:bit9:bit10:bit11:bit12:bit32:bit33:bit34:bit35:bit36:bit37:bit38:bit39:bit40:bit41:bit42:bit43:bit55:bit60:bit61:bit62:bit63:L1_ZeroBias:L1_BscMinBiasOR_BptxAND:L1_BscMinBiasInnerThreshold1_BptxAND:L1_BscMinBiasInnerThreshold2_BptxAND:L1_BscMinBiasThreshold1_BptxAND:L1_BscMinBiasThreshold2_BptxAND:L1_DoubleHfBitCountsRing1_P1N1:L1_DoubleHfBitCountsRing2_P1N1:L1_DoubleHfRingEtSumsRing1_P4N4:L1_DoubleHfRingEtSumsRing1_P200N200:L1_DoubleHfRingEtSumsRing2_P4N4:L1_DoubleHfRingEtSumsRing2_P200N200:L1_ZdcScintTightVertex_BptxAND:L1_ZdcScintLooseVertex_BptxAND:L1_BscMinBiasThreshold1:L1_ZdcCaloPlus:L1_ZdcCaloMinus:L1_ZdcCaloPlus_BptxAND:L1_ZdcCaloMinus_BptxAND:L1_ZdcCaloPlus_ZdcCaloMinus_BptxAND:L1_HcalHfMmOrPpOrPm:L1_HcalHfCoincidencePm:L1_HcalHfMmpOrMpp:L1_HcalHoTotalOR:L1_ETT60:L1_ETT60_BptxAND:L1_ZdcCaloPlus_ZdcCaloMinus:L1_BptxMinus:L1_BptxPlus:L1_BptxPlusORMinus:L1_ETT30_BptxAND:L1_ETT30:L1_ZdcScintTightVertex:L1_ZdcScintPlus:L1_ZdcScintMinus:L1_BscMinBiasInnerThreshold1:L1_BptxPlusANDMinus:L1_BscMinBiasOR_BptxPlusORMinus:L1_HcalHfCoincPmORBscMinBiasThresh1_BptxAND:L1_HcalHfCoincPmORBscMinBiasThresh2_BptxAND");
  rd_multProp_looper = new TNtuple("rd_multProp_looper","rd_multProp_looper",
      "EdVert:centBin_KK:centBin:lowEdge:NPart:NPartSigma:NColl:NCollSigma:NHard:NHardSigma:B:BSigma:CandMaker_coinc_1:CandMaker_coinc_2:CandMaker_coinc_3:CandMaker_coinc_4:isTrigger_1:isTrigger_2:isTrigger_3:rver_z:eta:eta_det:phi:eloss:numVtx:clustSizeY:clustSizeX:length:pixels:cluster_counter:HLT_HIMinBiasHfOrBSC_Core:HLT_HIMinBiasHfOrBSC_v1:HLT_HIZeroBias_v1:HLT_HIZeroBiasPixel_SingleTrack:HLT_HIMinBiasBSC_v1:HLT_HIMinBiasBSC_OR_v1:HLT_HIMinBiasBSC_Core:HLT_HIMinBiasBSC_OR_Core:HLT_HIMinBiasHF_v1:HLT_HIMinBiasPixel_SingleTrack:HLT_HIL1Tech_BSC_minBias:HLT_HIL1Tech_BSC_minBias_OR:HLT_HIL1Tech_BSC_HighMultiplicity:HLT_HIL1Tech_HCAL_HF:HLT_HIClusterVertexCompatibility_v1:HLT_HICentralityVeto_v1:HLT_HIL1ETT30:HLT_HIL1ETT30_Core:HLT_HIL1ETT60:HLT_HIL1ETT60_Core:bit0:bit1:bit2:bit3:bit4:bit5:bit6:bit7:bit8:bit9:bit10:bit11:bit12:bit32:bit33:bit34:bit35:bit36:bit37:bit38:bit39:bit40:bit41:bit42:bit43:bit55:bit60:bit61:bit62:bit63:L1_ZeroBias:L1_BscMinBiasOR_BptxAND:L1_BscMinBiasInnerThreshold1_BptxAND:L1_BscMinBiasInnerThreshold2_BptxAND:L1_BscMinBiasThreshold1_BptxAND:L1_BscMinBiasThreshold2_BptxAND:L1_DoubleHfBitCountsRing1_P1N1:L1_DoubleHfBitCountsRing2_P1N1:L1_DoubleHfRingEtSumsRing1_P4N4:L1_DoubleHfRingEtSumsRing1_P200N200:L1_DoubleHfRingEtSumsRing2_P4N4:L1_DoubleHfRingEtSumsRing2_P200N200:L1_ZdcScintTightVertex_BptxAND:L1_ZdcScintLooseVertex_BptxAND:L1_BscMinBiasThreshold1:L1_ZdcCaloPlus:L1_ZdcCaloMinus:L1_ZdcCaloPlus_BptxAND:L1_ZdcCaloMinus_BptxAND:L1_ZdcCaloPlus_ZdcCaloMinus_BptxAND:L1_HcalHfMmOrPpOrPm:L1_HcalHfCoincidencePm:L1_HcalHfMmpOrMpp:L1_HcalHoTotalOR:L1_ETT60:L1_ETT60_BptxAND:L1_ZdcCaloPlus_ZdcCaloMinus:L1_BptxMinus:L1_BptxPlus:L1_BptxPlusORMinus:L1_ETT30_BptxAND:L1_ETT30:L1_ZdcScintTightVertex:L1_ZdcScintPlus:L1_ZdcScintMinus:L1_BscMinBiasInnerThreshold1:L1_BptxPlusANDMinus:L1_BscMinBiasOR_BptxPlusORMinus:L1_HcalHfCoincPmORBscMinBiasThresh1_BptxAND:L1_HcalHfCoincPmORBscMinBiasThresh2_BptxAND");

  //cluster vertices
  nCLusterVertices = new TNtuple("nCLusterVertices","nCLusterVertices",
     "numRecHits_l1:rver_z");
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
  ResElseSimRecClusterY = new TH1F("ResElseSimRecClusterY","ResElseSimRecClusterY",60,0.,30.);

  full = 0;
  restricted = 0;

  PureCorrEta = new TH1F("PureCorrEta","PureCorrEta",30,-3.,3.);
  PureCutCorrEta = new TH1F("PureCutCorrEta","PureCutCorrEta",30,-3.,3.);
  DesiredEtaDist = new TH1F("DesiredEtaDist","DesiredEtaDist",30,-3.,3.);
  RecAdc = new TH1F("RecAdc","RecAdc",2550,0.,2550.);
  ResCentralAdc = new TH1F("ResCentralAdc","ResCentralAdc",50,0.,2550.);
  ResCentralAdcFine = new TH1F("ResCentralAdcFine","ResCentralAdcFine",50,0.,500.);
  ResElseCentralAdc = new TH1F("ResElseCentralAdc","ResElseCentralAdc",50,0.,2550.);
  ResPureAdc = new TH1F("ResPureAdc","ResPureAdc",50,0.,2550.);
  ResPureAdc_det = new TH1F("ResPureAdc_det","ResPureAdc_det",50,0.,2550.);
  ResPureCentralAdc = new TH1F("ResPureCentralAdc","ResPureCentralAdc",50,0.,2550.);
  ResPureCutAdc = new TH1F("ResPureCutAdc","ResPureCutAdc",50,0.,2550.);
  ResPureCutCentralAdc = new TH1F("ResPureCutCentralAdc","ResPureCutCentralAdc",50,0.,2550.);

  RecAdcvsCorrEta = new TH2F("RecAdcvsCorrEta","RecAdcvsCorrEta",300,-3.,3.,25500,0.,2550.);
  PureAdcvsCorrEta = new TH2F("PureAdcvsCorrEta","PureAdcvsCorrEta",300,-3.,3.,2550,0.,2550.);
  PureCutAdcvsCorrEta = new TH2F("PureCutAdcvsCorrEta","PureCutAdcvsCorrEta",300,-3.,3.,25000,0.,2550.);
  hAdcPerCoshCorrEta = new TH2F("hAdcPerCoshCorrEta","hAdcPerCoshCorrEta",300,-3.,3.,25500,0.,2550.);

  test = 0;
  proba = 0;

}

/*****************************************************************************/
void HI_simple_nosiminfo::endJob()
{
  TDirectory::TContext context(resultFile);

  nHF_towers->Write();
  nHF_event->Write();
  nHF_Y_event->Write();

  hNum_nd->Write();
  hNum_nsd->Write();
  hNum_nsd_trig->Write();
  hNum_sd_trig->Write();
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

  //clusters
//  nCLusterVertices->Write();
//  nClusterPrim->Write();
//  nClusterAll->Write();
//  nClusterUnused->Write();
  hCorrEtaSizeY->Write();
  hCorrEtaADC->Write();
  hClusterZSizeY->Write();
//  ResPureClusterY->Write();

  PureCorrEta->Write();
  PureCutCorrEta->Write();
  DesiredEtaDist->Write();
  RecAdc->Write();
  ResCentralAdc->Write();
  ResCentralAdcFine->Write();
  ResElseCentralAdc->Write();
  ResPureAdc->Write();
  ResPureAdc_det->Write();
  ResPureCentralAdc->Write();
  ResPureCutAdc->Write();
  ResPureCutCentralAdc->Write();

  RecAdcvsCorrEta->Write();
  PureAdcvsCorrEta->Write();
  PureCutAdcvsCorrEta->Write();
  hAdcPerCoshCorrEta->Write();

  resultFile->Close();
  delete resultFile;
/*
  cerr<<"Test the number of events: filling RecCut: "<<test<<endl;
  cerr<<"Test the number of events: filling SimPrim: "<<proba<<endl;
  cerr<<"FULL: "<<full<<endl;
  cerr<<"RESTRICTED: "<<restricted<<endl;
*/
}

/*****************************************************************************/
bool HI_simple_nosiminfo::getEdwardVertex(const edm::Event& ev)
{
  edm::Handle<reco::VertexCollection> vertexCollection;
  ev.getByLabel(vertexColl_,vertexCollection);
  const reco::VertexCollection * vertices = vertexCollection.product();
  for(reco::VertexCollection::const_iterator
      vertex = vertices->begin(); vertex!= vertices->end(); vertex++) {
      if(vertex->position().Rho()<2. && !(vertex->isFake()) && TMath::Abs(vertex->z())<=25. && vertex->tracksSize()>=2)
        return true;
  }
  return false;
}

/*****************************************************************************/
float HI_simple_nosiminfo::getVertexZ
     (edm::Handle<SiPixelRecHitCollection> siPixelRecCollection, const edm::Event& ev)
{
  float rver_z = 0.;
  if(!produceVertexLocally_) {
    edm::Handle<reco::VertexCollection> vertexCollection;
    ev.getByLabel(vertexColl_,vertexCollection);
    const reco::VertexCollection * vertices = vertexCollection.product();
//    unsigned int vertex_tracks = 0;
    for(reco::VertexCollection::const_iterator
        vertex = vertices->begin(); vertex!= vertices->end(); vertex++)
    {
//       if(vertex->tracksSize()>vertex_tracks) {
//         vertex_tracks = vertex->tracksSize();
         rver_z = vertex->z();
//       }
    }
  } else {
    rver_z = produceClusterVertex(siPixelRecCollection);
  }
  return rver_z;
}

/*****************************************************************************/
int HI_simple_nosiminfo::getContainedHits
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
float HI_simple_nosiminfo::produceClusterVertex
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
void HI_simple_nosiminfo::clusterVertices
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
int HI_simple_nosiminfo::KK_B0_cent(edm::Handle<CaloTowerCollection> towers)
{
  float posET = 0., negET = 0.;

  for(CaloTowerCollection::const_iterator cal = towers->begin(); cal != towers->end(); ++cal) {
     for(unsigned int i = 0; i < cal->constituentsSize(); i++) {
        const DetId id = cal->constituent(i);
        if(id.det() == DetId::Hcal) {
          HcalSubdetector subdet=(HcalSubdetector(id.subdetId()));
          if(subdet == HcalForward) {

            if(cal->eta()>3.)
               posET += cal->energy()/cosh(cal->eta());
            if(cal->eta()<-3.)
               negET += cal->energy()/cosh(cal->eta());

          }
        }
     }    
  }

  float Summ_ET = posET+negET;
  if(Summ_ET < 13.5325)
    return 39;
  else if(Summ_ET < 17.5025)
    return 38;
  else if(Summ_ET < 22.7875)
    return 37;
  else if(Summ_ET < 30.3225)
    return 36;
  else if(Summ_ET < 38.5725)
    return 35;
  else if(Summ_ET < 50.3275)
    return 34;
  else if(Summ_ET < 65.0875)
    return 33;
  else if(Summ_ET < 82.7575)
    return 32;
  else if(Summ_ET < 107.092)
    return 31;
  else if(Summ_ET < 135.113)
    return 30;
  else if(Summ_ET < 172.173)
    return 29;
  else if(Summ_ET < 213.887)
    return 28;
  else if(Summ_ET < 267.138)
    return 27;
  else if(Summ_ET < 333.217)
    return 26;
  else if(Summ_ET < 411.677)
    return 25;
  else if(Summ_ET < 494.948)
    return 24;
  else if(Summ_ET < 596.823)
    return 23;
  else if(Summ_ET < 720.562)
    return 22;
  else if(Summ_ET < 865.297)
    return 21;
  else if(Summ_ET < 1014.59)
    return 20;
  else if(Summ_ET < 1179.22)
    return 19;
  else if(Summ_ET < 1363.1)
    return 18;
  else if(Summ_ET < 1580.24)
    return 17;
  else if(Summ_ET < 1800.3)
    return 16;
  else if(Summ_ET < 2054.62)
    return 15;
  else if(Summ_ET < 2348.19)
    return 14;
  else if(Summ_ET < 2652.56)
    return 13;
  else if(Summ_ET < 2967.41)
    return 12;
  else if(Summ_ET < 3308.97)
    return 11;
  else if(Summ_ET < 3683.79)
    return 10;
  else if(Summ_ET < 4047.91)
    return 9;
  else if(Summ_ET < 4444.38)
    return 8;
  else if(Summ_ET < 4890.99)
    return 7;
  else if(Summ_ET < 5331.46)
    return 6;
  else if(Summ_ET < 5830.74)
    return 5;
  else if(Summ_ET < 6350.84)
    return 4;
  else if(Summ_ET < 6922.97)
    return 3;
  else if(Summ_ET < 7522.33)
    return 2;
  else if(Summ_ET < 8163.68)
    return 1;
  else
    return 0;
}

/*****************************************************************************/
void HI_simple_nosiminfo::HF_details(edm::Handle<CaloTowerCollection> towers,
                                     CentralityProvider * centrality_,
                                     const edm::Event& ev,
                                     edm::Handle<SiPixelRecHitCollection> siPixelRecCollection)
{
  float rver_z = getVertexZ(siPixelRecCollection, ev);
  int centBin = centrality_->getBin();
  int centBin_KK = KK_B0_cent(towers);
  float posET = 0., negET = 0., posET_Y = 0., negET_Y = 0.;
  float posET_3 = 0., negET_3 = 0.;
  float posET_20 = 0., negET_20 = 0.;
  float posEnergy = 0., negEnergy = 0., posEnergy_Y = 0., negEnergy_Y = 0.;
  float posEnergy_3 = 0., negEnergy_3 = 0.;
  float posEnergy_20 = 0., negEnergy_20 = 0.;
  float posPT = 0., negPT = 0., posPT_Y = 0., negPT_Y = 0.;
  int posTowers = 0, negTowers = 0;
  int posTowers_3 = 0, negTowers_3 = 0;
  int posTowers_20 = 0, negTowers_20 = 0;
  bool isTrigger_3 = aboveTriggerThreshold_3(towers);

  //Yetkin
  //Gives only barrel???
  for( size_t i = 0; i < towers->size(); ++ i){
     const CaloTower & tower = (*towers)[ i ];
     double eta = tower.eta();
     HcalDetId hcalId(tower.id().rawId());
     bool isHF = (hcalId.subdetId() == HcalForward);

     const DetId id_KK = tower.id();
//     HcalSubdetector subdet_KK=(HcalSubdetector(id_KK.subdetId()));
/*
     std::cerr<<" isHF: " << isHF << std::endl;
     std::cerr<<" subdet: " << hcalId.subdetId() << std::endl;
     std::cerr<<" subdet_KK: " << subdet_KK << std::endl;

     if(isHF) {
        std::cerr<<"  --  eta(): " << eta << std::endl;
        std::cerr<<"  --  pt(): " << tower.pt() << std::endl;
     }
*/
     if(isHF && eta > 0) {
        posET_Y += tower.energy()/cosh(eta);
        posEnergy_Y += tower.energy();
        posPT_Y += tower.pt();
     }
     if(isHF && eta < 0) {
        negET_Y += tower.energy()/cosh(eta);
        negEnergy_Y += tower.energy();
        negPT_Y += tower.pt();
     }
  }
  nHF_Y_event->Fill(centBin,posET_Y,negET_Y,posEnergy_Y,negEnergy_Y,posPT_Y,negPT_Y,rver_z,isTrigger_3);

  //Krisztian
  for(CaloTowerCollection::const_iterator cal = towers->begin(); cal != towers->end(); ++cal) {
//     std::cerr<<"  NEW TOWER ========== " << std::endl;
     for(unsigned int i = 0; i < cal->constituentsSize(); i++) {
        const DetId id = cal->constituent(i);
        if(id.det() == DetId::Hcal) {
          HcalSubdetector subdet=(HcalSubdetector(id.subdetId()));
//          std::cerr<<" subdet NALAM: " << subdet << std::endl;
          if(subdet == HcalForward) {

            if(cal->eta()>3.) {
               posET += cal->energy()/cosh(cal->eta());
               posEnergy += cal->energy();
               posPT += cal->pt();
               posTowers++;
            }
            if(cal->eta()<-3.) {
               negET += cal->energy()/cosh(cal->eta());
               negEnergy += cal->energy();
               negPT += cal->pt();
               negTowers++;
            }

            if(cal->energy()>20. && cal->eta()>3.) {
              posET_20 += cal->energy()/cosh(cal->eta());
              posEnergy_20 += cal->energy();
              posTowers_20++;
            }
            if(cal->energy()>3. && cal->eta()>3.) {
              posET_3 += cal->energy()/cosh(cal->eta());
              posEnergy_3 += cal->energy();
              posTowers_3++;
            }
            if(cal->energy()>20. && cal->eta()<-3.) {
              negET_20 += cal->energy()/cosh(cal->eta());
              negEnergy_20 += cal->energy();
              negTowers_20++;
            }
            if(cal->energy()>3. && cal->eta()<-3.) {
              negET_3 += cal->energy()/cosh(cal->eta());
              negEnergy_3 += cal->energy();
              negTowers_3++;
            }

            nHF_towers->Fill(centBin_KK,centBin,cal->energy(),cal->eta(),rver_z,isTrigger_3);
          }
        }
     }    
  }
  vector<float> result_KK;
  result_KK.push_back(centBin_KK);
  result_KK.push_back(centBin);
  result_KK.push_back(posTowers);
  result_KK.push_back(posTowers_3);
  result_KK.push_back(posTowers_20);
  result_KK.push_back(negTowers);
  result_KK.push_back(negTowers_3);
  result_KK.push_back(negTowers_20);
  result_KK.push_back(posET);
  result_KK.push_back(posET_3);
  result_KK.push_back(posET_20);
  result_KK.push_back(negET);
  result_KK.push_back(negET_3);
  result_KK.push_back(negET_20);
  result_KK.push_back(posEnergy);
  result_KK.push_back(posEnergy_3);
  result_KK.push_back(posEnergy_20);
  result_KK.push_back(negEnergy);
  result_KK.push_back(negEnergy_3);
  result_KK.push_back(negEnergy_20);
  result_KK.push_back(rver_z);
  result_KK.push_back(isTrigger_3);

  nHF_event->Fill(&result_KK[0]);
}

/*****************************************************************************/
bool HI_simple_nosiminfo::aboveTriggerThreshold_CandMaker(edm::Handle<CaloTowerCollection> towers, double threshold_)
{
  unsigned int posTowers = 0;
  unsigned int negTowers = 0;

  bool accept = false;
  unsigned idx = 0;
  double mEThreshold = 3.;

  for(; idx < towers->size (); idx++) {
     const CaloTower* cal = &((*towers) [idx]);
     if(TMath::Abs(cal->eta())>6. || TMath::Abs(cal->eta())<3. || cal->energy() <= mEThreshold)
        continue;
     if(cal->eta()>0)
       posTowers++;
     if(cal->eta()<0)
       negTowers++;
  }
  if(posTowers>threshold_ && negTowers>threshold_)
     accept = true;

  return accept;
}

/*****************************************************************************/
bool HI_simple_nosiminfo::aboveTriggerThreshold_1(edm::Handle<CaloTowerCollection> towers)
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
bool HI_simple_nosiminfo::aboveTriggerThreshold_2(edm::Handle<CaloTowerCollection> towers)
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
bool HI_simple_nosiminfo::aboveTriggerThreshold_3(edm::Handle<CaloTowerCollection> towers)
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
bool HI_simple_nosiminfo::isRecHitAtTheEdge(SiPixelRecHitCollection::DataContainer::const_iterator iPRH,
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
void HI_simple_nosiminfo::onFirst(edm::Handle<SiPixelRecHitCollection>& siPixelRecCollection,
//                                                const reco::VertexCollection* vertices,
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
bool HI_simple_nosiminfo::compareRecHits
  (const SiPixelRecHit * hit1, const SiPixelRecHit * hit2)
{
  return hit1->geographicalId() == hit2->geographicalId() &&
        (hit1->cluster())->charge() == (hit2->cluster())->charge() &&
        (hit1->cluster())->size() == (hit2->cluster())->size() &&
        (hit1->cluster())->sizeX() == (hit2->cluster())->sizeX() &&
        (hit1->cluster())->sizeY() == (hit2->cluster())->sizeY();
}

/*****************************************************************************/
void HI_simple_nosiminfo::multiplicityProperties
   (const edm::Event& ev, const edm::EventSetup& es, edm::Handle<CaloTowerCollection> towers,
    edm::Handle<SiPixelRecHitCollection> siPixelRecCollection,
    edm::Handle<reco::TrackCollection>& recCollection,
    Handle<HcalTrigPrimDigiCollection>& tpg,
    CentralityProvider * centrality_,
    int desLayer)
{
  vector<float> result;

  bool EdVertex = getEdwardVertex(ev);

  result.push_back(EdVertex); //EdVert

  double EtHFhitSum = centrality_->raw()->EtHFhitSum();
  double EtHFhitSumPlus = centrality_->raw()->EtHFhitSumPlus();
  double EtHFhitSumMinus = centrality_->raw()->EtHFhitSumMinus();
  double EtHFtowerSum = centrality_->raw()->EtHFtowerSum();
  double EtHFtowerSumPlus = centrality_->raw()->EtHFtowerSumPlus();
  double EtHFtowerSumMinus = centrality_->raw()->EtHFtowerSumMinus();

  result.push_back(EtHFhitSum);
  result.push_back(EtHFhitSumPlus);
  result.push_back(EtHFhitSumMinus);
  result.push_back(EtHFtowerSum);
  result.push_back(EtHFtowerSumPlus);
  result.push_back(EtHFtowerSumMinus);

  int centBin_KK = KK_B0_cent(towers);

  int centBin = centrality_->getBin();
  float lowEdge = centrality_->lowEdge();

  float npartMean = centrality_->NpartMean();
  float npartSigma = centrality_->NpartSigma();
  float ncollMean = centrality_->NcollMean();
  float ncollSigma = centrality_->NcollSigma();
  float nhardMean = centrality_->NhardMean();
  float nhardSigma = centrality_->NhardSigma();
  float bMean = centrality_->bMean();
  float bSigma = centrality_->bSigma();

  result.push_back(centBin_KK); //centBin_KK
  result.push_back(centBin); //centBin
  result.push_back(lowEdge); //lowEdge
  result.push_back(npartMean); //NPart
  result.push_back(npartSigma);//NPartSigma
  result.push_back(ncollMean); //NColl
  result.push_back(ncollSigma);//NCollSigma
  result.push_back(nhardMean); //NHard
  result.push_back(nhardSigma);//NHardSigma
  result.push_back(bMean);     //B
  result.push_back(bSigma);    //BSigma

/*
  //test
  edm::Handle<TriggerResults> HLTR;
  ev.getByLabel(triggerLabel_,HLTR);
  std::vector<std::string>  hlNames_;
  if(HLTR.isValid()) {
      const edm::TriggerNames & triggerNames = ev.triggerNames(*HLTR);
      hlNames_=triggerNames.triggerNames();
      const unsigned int n(hlNames_.size());
      for(unsigned int i=0; i!=n; ++i) {
              if(HLTR->accept(i)) 
                 std::cout << hlNames_[i] << std::endl;
      }
  }
*/
  // Triggers
  edm::Handle<edm::TriggerResults> triggerResults;
  ev.getByLabel(triggerLabel_,triggerResults);

  const edm::TriggerNames & triggerNames = ev.triggerNames(*triggerResults);

  bool is_HLT_HIMinBiasHfOrBSC_Core = false;
  bool is_HLT_HIMinBiasHfOrBSC_v1 = false;
  bool is_HLT_HIZeroBias_v1 = false;
  bool is_HLT_HIZeroBiasPixel_SingleTrack = false;
  bool is_HLT_HIMinBiasBSC_v1 = false;
  bool is_HLT_HIMinBiasBSC_OR_v1 = false;
  bool is_HLT_HIMinBiasBSC_Core = false;
  bool is_HLT_HIMinBiasBSC_OR_Core = false;
  bool is_HLT_HIMinBiasHF_v1 = false;
  bool is_HLT_HIMinBiasPixel_SingleTrack = false;
  bool is_HLT_HIL1Tech_BSC_minBias = false;
  bool is_HLT_HIL1Tech_BSC_minBias_OR = false;
  bool is_HLT_HIL1Tech_BSC_HighMultiplicity = false;
  bool is_HLT_HIL1Tech_HCAL_HF = false;
  bool is_HLT_HIClusterVertexCompatibility_v1 = false;
  bool is_HLT_HICentralityVeto_v1 = false;
  bool is_HLT_HIL1ETT30 = false;
  bool is_HLT_HIL1ETT30_Core = false;
  bool is_HLT_HIL1ETT60 = false;
  bool is_HLT_HIL1ETT60_Core = false;

  bool is_bit0 = false;
  bool is_bit1 = false;
  bool is_bit2 = false;
  bool is_bit3 = false;
  bool is_bit4 = false;
  bool is_bit5 = false;
  bool is_bit6 = false;
  bool is_bit7 = false;
  bool is_bit8 = false;
  bool is_bit9 = false;
  bool is_bit10 = false;
  bool is_bit11 = false;
  bool is_bit12 = false;
  bool is_bit32 = false;
  bool is_bit33 = false;
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
  bool is_bit55 = false;
  bool is_bit60 = false;
  bool is_bit61 = false;
  bool is_bit62 = false;
  bool is_bit63 = false;

  bool is_L1_ZeroBias = false;
  bool is_L1_BscMinBiasOR_BptxAND = false;
  bool is_L1_BscMinBiasInnerThreshold1_BptxAND = false;
  bool is_L1_BscMinBiasInnerThreshold2_BptxAND = false;
  bool is_L1_BscMinBiasThreshold1_BptxAND = false;
  bool is_L1_BscMinBiasThreshold2_BptxAND = false;
  bool is_L1_DoubleHfBitCountsRing1_P1N1 = false;
  bool is_L1_DoubleHfBitCountsRing2_P1N1 = false;
  bool is_L1_DoubleHfRingEtSumsRing1_P4N4 = false;
  bool is_L1_DoubleHfRingEtSumsRing1_P200N200  = false;
  bool is_L1_DoubleHfRingEtSumsRing2_P4N4 = false;
  bool is_L1_DoubleHfRingEtSumsRing2_P200N200 = false;
  bool is_L1_ZdcScintTightVertex_BptxAND = false;
  bool is_L1_ZdcScintLooseVertex_BptxAND = false;
  bool is_L1_BscMinBiasThreshold1 = false;
  bool is_L1_ZdcCaloPlus = false;
  bool is_L1_ZdcCaloMinus = false;
  bool is_L1_ZdcCaloPlus_BptxAND = false;
  bool is_L1_ZdcCaloMinus_BptxAND = false;
  bool is_L1_ZdcCaloPlus_ZdcCaloMinus_BptxAND = false;
  bool is_L1_HcalHfMmOrPpOrPm = false;
  bool is_L1_HcalHfCoincidencePm = false;
  bool is_L1_HcalHfMmpOrMpp = false;
  bool is_L1_HcalHoTotalOR = false;
  bool is_L1_ETT60 = false;
  bool is_L1_ETT60_BptxAND = false;
  bool is_L1_ZdcCaloPlus_ZdcCaloMinus = false;
  bool is_L1_BptxMinus = false;
  bool is_L1_BptxPlus = false;
  bool is_L1_BptxPlusORMinus = false;
  bool is_L1_ETT30_BptxAND = false;
  bool is_L1_ETT30  = false;
  bool is_L1_ZdcScintTightVertex = false;
  bool is_L1_ZdcScintPlus = false;
  bool is_L1_ZdcScintMinus = false;
  bool is_L1_BscMinBiasInnerThreshold1 = false;
  bool is_L1_BptxPlusANDMinus = false;
  bool is_L1_BscMinBiasOR_BptxPlusORMinus = false;
  bool is_L1_HcalHfCoincPmORBscMinBiasThresh1_BptxAND = false;
  bool is_L1_HcalHfCoincPmORBscMinBiasThresh2_BptxAND = false;

  if(triggerResults.product()->wasrun())
  if(triggerResults.product()->accept())
  for(unsigned int itrig = 0; itrig < triggerResults.product()->size(); ++itrig) {
    if(triggerResults.product()->accept(itrig))
    {
//      std::cerr<<"   what is it?: " <<  triggerNames.triggerName(itrig).c_str() << std::endl;

      if(strcmp(triggerNames.triggerName(itrig).c_str(),"HLT_HIMinBiasHfOrBSC_Core") == 0)
        is_HLT_HIMinBiasHfOrBSC_Core = true;
      if(strcmp(triggerNames.triggerName(itrig).c_str(),"HLT_HIMinBiasHfOrBSC_v1") == 0)
        is_HLT_HIMinBiasHfOrBSC_v1 = true;
      if(strcmp(triggerNames.triggerName(itrig).c_str(),"HLT_HIZeroBias_v1") == 0)
        is_HLT_HIZeroBias_v1 = true;
      if(strcmp(triggerNames.triggerName(itrig).c_str(),"HLT_HIZeroBiasPixel_SingleTrack") == 0)
        is_HLT_HIZeroBiasPixel_SingleTrack = true;
      if(strcmp(triggerNames.triggerName(itrig).c_str(),"HLT_HIMinBiasBSC_v1") == 0)
        is_HLT_HIMinBiasBSC_v1 = true;
      if(strcmp(triggerNames.triggerName(itrig).c_str(),"HLT_HIMinBiasBSC_OR_v1") == 0)
        is_HLT_HIMinBiasBSC_OR_v1 = true;
      if(strcmp(triggerNames.triggerName(itrig).c_str(),"HLT_HIMinBiasBSC_Core") == 0)
        is_HLT_HIMinBiasBSC_Core = true;
      if(strcmp(triggerNames.triggerName(itrig).c_str(),"HLT_HIMinBiasBSC_OR_Core") == 0)
        is_HLT_HIMinBiasBSC_OR_Core = true;
      if(strcmp(triggerNames.triggerName(itrig).c_str(),"HLT_HIMinBiasHF_v1") == 0)
        is_HLT_HIMinBiasHF_v1 = true;
      if(strcmp(triggerNames.triggerName(itrig).c_str(),"HLT_HIMinBiasPixel_SingleTrack") == 0)
        is_HLT_HIMinBiasPixel_SingleTrack = true;
      if(strcmp(triggerNames.triggerName(itrig).c_str(),"HLT_HIL1Tech_BSC_minBias") == 0)
        is_HLT_HIL1Tech_BSC_minBias = true;
      if(strcmp(triggerNames.triggerName(itrig).c_str(),"HLT_HIL1Tech_BSC_minBias_OR") == 0)
        is_HLT_HIL1Tech_BSC_minBias_OR = true;
      if(strcmp(triggerNames.triggerName(itrig).c_str(),"HLT_HIL1Tech_BSC_HighMultiplicity") == 0)
        is_HLT_HIL1Tech_BSC_HighMultiplicity = true;
      if(strcmp(triggerNames.triggerName(itrig).c_str(),"HLT_HIL1Tech_HCAL_HF") == 0)
        is_HLT_HIL1Tech_HCAL_HF = true;
      if(strcmp(triggerNames.triggerName(itrig).c_str(),"HLT_HIClusterVertexCompatibility_v1") == 0)
        is_HLT_HIClusterVertexCompatibility_v1 = true;
      if(strcmp(triggerNames.triggerName(itrig).c_str(),"HLT_HICentralityVeto_v1") == 0)
        is_HLT_HICentralityVeto_v1 = true;
      if(strcmp(triggerNames.triggerName(itrig).c_str(),"HLT_HIL1ETT30") == 0)
        is_HLT_HIL1ETT30 = true;
      if(strcmp(triggerNames.triggerName(itrig).c_str(),"HLT_HIL1ETT30_Core") == 0)
        is_HLT_HIL1ETT30_Core = true;
      if(strcmp(triggerNames.triggerName(itrig).c_str(),"HLT_HIL1ETT60") == 0)
        is_HLT_HIL1ETT60 = true;
      if(strcmp(triggerNames.triggerName(itrig).c_str(),"HLT_HIL1ETT60_Core") == 0)
        is_HLT_HIL1ETT60_Core = true;
    }
  }

  if(hasL1Triggers_) {
    edm::Handle< L1GlobalTriggerReadoutRecord > gtReadoutRecord;
    ev.getByLabel( edm::InputTag("gtDigis"), gtReadoutRecord);
    const TechnicalTriggerWord&  technicalTriggerWord = gtReadoutRecord->technicalTriggerWord();
    is_bit0 = technicalTriggerWord.at(0);
    is_bit1 = technicalTriggerWord.at(1);
    is_bit2 = technicalTriggerWord.at(2);
    is_bit3 = technicalTriggerWord.at(3);
    is_bit4 = technicalTriggerWord.at(4);
    is_bit5 = technicalTriggerWord.at(5);
    is_bit6 = technicalTriggerWord.at(6);
    is_bit7 = technicalTriggerWord.at(7);
    is_bit8 = technicalTriggerWord.at(8);
    is_bit9 = technicalTriggerWord.at(9);
    is_bit10 = technicalTriggerWord.at(10);
    is_bit11 = technicalTriggerWord.at(11);
    is_bit12 = technicalTriggerWord.at(12);
    is_bit32 = technicalTriggerWord.at(32);
    is_bit33 = technicalTriggerWord.at(33);
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
    is_bit55 = technicalTriggerWord.at(55);
    is_bit60 = technicalTriggerWord.at(60);
    is_bit61 = technicalTriggerWord.at(61);
    is_bit62 = technicalTriggerWord.at(62);
    is_bit63 = technicalTriggerWord.at(63);

    edm::ESHandle<L1GtTriggerMenu> menuRcd;
    es.get<L1GtTriggerMenuRcd>().get(menuRcd) ;
    const L1GtTriggerMenu* menu = menuRcd.product();

    const DecisionWord& gtDecisionWordBeforeMask = gtReadoutRecord->decisionWord();
    is_L1_ZeroBias = menu->gtAlgorithmResult( "L1_ZeroBias", gtDecisionWordBeforeMask);
    is_L1_BscMinBiasOR_BptxAND = menu->gtAlgorithmResult( "L1_BscMinBiasOR_BptxAND", gtDecisionWordBeforeMask);
    is_L1_BscMinBiasInnerThreshold1_BptxAND = menu->gtAlgorithmResult( "L1_BscMinBiasInnerThreshold1_BptxAND", gtDecisionWordBeforeMask);
    is_L1_BscMinBiasInnerThreshold2_BptxAND = menu->gtAlgorithmResult( "L1_BscMinBiasInnerThreshold2_BptxAND", gtDecisionWordBeforeMask);
    is_L1_BscMinBiasThreshold1_BptxAND = menu->gtAlgorithmResult( "L1_BscMinBiasThreshold1_BptxAND", gtDecisionWordBeforeMask);
    is_L1_BscMinBiasThreshold2_BptxAND = menu->gtAlgorithmResult( "L1_BscMinBiasThreshold2_BptxAND", gtDecisionWordBeforeMask);
    is_L1_DoubleHfBitCountsRing1_P1N1 = menu->gtAlgorithmResult( "L1_DoubleHfBitCountsRing1_P1N1", gtDecisionWordBeforeMask);
    is_L1_DoubleHfBitCountsRing2_P1N1 = menu->gtAlgorithmResult( "L1_DoubleHfBitCountsRing2_P1N1", gtDecisionWordBeforeMask);
    is_L1_DoubleHfRingEtSumsRing1_P4N4 = menu->gtAlgorithmResult( "L1_DoubleHfRingEtSumsRing1_P4N4", gtDecisionWordBeforeMask);
    is_L1_DoubleHfRingEtSumsRing1_P200N200 = menu->gtAlgorithmResult( "L1_DoubleHfRingEtSumsRing1_P200N200", gtDecisionWordBeforeMask);
    is_L1_DoubleHfRingEtSumsRing2_P4N4 = menu->gtAlgorithmResult( "L1_DoubleHfRingEtSumsRing2_P4N4", gtDecisionWordBeforeMask);
    is_L1_DoubleHfRingEtSumsRing2_P200N200 = menu->gtAlgorithmResult( "L1_DoubleHfRingEtSumsRing2_P200N200", gtDecisionWordBeforeMask);
    is_L1_ZdcScintTightVertex_BptxAND = menu->gtAlgorithmResult( "L1_ZdcScintTightVertex_BptxAND", gtDecisionWordBeforeMask);
    is_L1_ZdcScintLooseVertex_BptxAND = menu->gtAlgorithmResult( "L1_ZdcScintLooseVertex_BptxAND", gtDecisionWordBeforeMask);
    is_L1_BscMinBiasThreshold1 = menu->gtAlgorithmResult( "L1_BscMinBiasThreshold1", gtDecisionWordBeforeMask);
    is_L1_ZdcCaloPlus = menu->gtAlgorithmResult( "L1_ZdcCaloPlus", gtDecisionWordBeforeMask);
    is_L1_ZdcCaloMinus = menu->gtAlgorithmResult( "L1_ZdcCaloMinus", gtDecisionWordBeforeMask);
    is_L1_ZdcCaloPlus_BptxAND = menu->gtAlgorithmResult( "L1_ZdcCaloPlus_BptxAND", gtDecisionWordBeforeMask);
    is_L1_ZdcCaloMinus_BptxAND = menu->gtAlgorithmResult( "L1_ZdcCaloMinus_BptxAND", gtDecisionWordBeforeMask);
    is_L1_ZdcCaloPlus_ZdcCaloMinus_BptxAND = menu->gtAlgorithmResult( "L1_ZdcCaloPlus_ZdcCaloMinus_BptxAND", gtDecisionWordBeforeMask);
    is_L1_HcalHfMmOrPpOrPm = menu->gtAlgorithmResult( "L1_HcalHfMmOrPpOrPm", gtDecisionWordBeforeMask);
    is_L1_HcalHfCoincidencePm = menu->gtAlgorithmResult( "L1_HcalHfCoincidencePm", gtDecisionWordBeforeMask);
    is_L1_HcalHfMmpOrMpp = menu->gtAlgorithmResult( "L1_HcalHfMmpOrMpp", gtDecisionWordBeforeMask);
    is_L1_HcalHoTotalOR = menu->gtAlgorithmResult( "L1_HcalHoTotalOR", gtDecisionWordBeforeMask);
    is_L1_ETT60 = menu->gtAlgorithmResult( "L1_ETT60", gtDecisionWordBeforeMask);
    is_L1_ETT60_BptxAND = menu->gtAlgorithmResult( "L1_ETT60_BptxAND", gtDecisionWordBeforeMask);
    is_L1_ZdcCaloPlus_ZdcCaloMinus = menu->gtAlgorithmResult( "L1_ZdcCaloPlus_ZdcCaloMinus", gtDecisionWordBeforeMask);
    is_L1_BptxMinus = menu->gtAlgorithmResult( "L1_BptxMinus", gtDecisionWordBeforeMask);
    is_L1_BptxPlus = menu->gtAlgorithmResult( "L1_BptxPlus", gtDecisionWordBeforeMask);
    is_L1_BptxPlusORMinus = menu->gtAlgorithmResult( "L1_BptxPlusORMinus", gtDecisionWordBeforeMask);
    is_L1_ETT30_BptxAND = menu->gtAlgorithmResult( "L1_ETT30_BptxAND", gtDecisionWordBeforeMask);
    is_L1_ETT30 = menu->gtAlgorithmResult( "L1_ETT30", gtDecisionWordBeforeMask);
    is_L1_ZdcScintTightVertex = menu->gtAlgorithmResult( "L1_ZdcScintTightVertex", gtDecisionWordBeforeMask);
    is_L1_ZdcScintPlus = menu->gtAlgorithmResult( "L1_ZdcScintPlus", gtDecisionWordBeforeMask);
    is_L1_ZdcScintMinus = menu->gtAlgorithmResult( "L1_ZdcScintMinus", gtDecisionWordBeforeMask);
    is_L1_BscMinBiasInnerThreshold1 = menu->gtAlgorithmResult( "L1_BscMinBiasInnerThreshold1", gtDecisionWordBeforeMask);
    is_L1_BptxPlusANDMinus = menu->gtAlgorithmResult( "L1_BptxPlusANDMinus", gtDecisionWordBeforeMask);
    is_L1_BscMinBiasOR_BptxPlusORMinus = menu->gtAlgorithmResult( "L1_BscMinBiasOR_BptxPlusORMinus", gtDecisionWordBeforeMask);
    is_L1_HcalHfCoincPmORBscMinBiasThresh1_BptxAND = menu->gtAlgorithmResult( "L1_HcalHfCoincPmORBscMinBiasThresh1_BptxAND", gtDecisionWordBeforeMask);
    is_L1_HcalHfCoincPmORBscMinBiasThresh2_BptxAND = menu->gtAlgorithmResult( "L1_HcalHfCoincPmORBscMinBiasThresh2_BptxAND", gtDecisionWordBeforeMask);
  }

  edm::ESHandle<TrackerGeometry> geom;
  es.get<TrackerDigiGeometryRecord>().get(geom);

  const SiPixelRecHitCollection pixelRecHits = *(siPixelRecCollection.product());

  result.push_back(pixelRecHits.size());

  // get vertex_z
  double rver_z = (double)getVertexZ(siPixelRecCollection, ev);

  result.push_back(rver_z); //rver_z

  //simulate triggers
  result.push_back(aboveTriggerThreshold_CandMaker(towers,1.));  //CandMaker_coinc_1
  result.push_back(aboveTriggerThreshold_CandMaker(towers,2.));  //CandMaker_coinc_2
  result.push_back(aboveTriggerThreshold_CandMaker(towers,3.));  //CandMaker_coinc_3
  result.push_back(aboveTriggerThreshold_CandMaker(towers,4.));  //CandMaker_coinc_4
  result.push_back(aboveTriggerThreshold_1(towers));  //isTrigger_1
  result.push_back(aboveTriggerThreshold_2(towers));  //isTrigger_2
  result.push_back(aboveTriggerThreshold_3(towers));  //isTrigger_3

  result.push_back(is_HLT_HIMinBiasHfOrBSC_Core);
  result.push_back(is_HLT_HIMinBiasHfOrBSC_v1);
  result.push_back(is_HLT_HIZeroBias_v1);
  result.push_back(is_HLT_HIZeroBiasPixel_SingleTrack);
  result.push_back(is_HLT_HIMinBiasBSC_v1);
  result.push_back(is_HLT_HIMinBiasBSC_OR_v1);
  result.push_back(is_HLT_HIMinBiasBSC_Core);
  result.push_back(is_HLT_HIMinBiasBSC_OR_Core);
  result.push_back(is_HLT_HIMinBiasHF_v1);
  result.push_back(is_HLT_HIMinBiasPixel_SingleTrack);
  result.push_back(is_HLT_HIL1Tech_BSC_minBias);
  result.push_back(is_HLT_HIL1Tech_BSC_minBias_OR);
  result.push_back(is_HLT_HIL1Tech_BSC_HighMultiplicity);
  result.push_back(is_HLT_HIL1Tech_HCAL_HF);
  result.push_back(is_HLT_HIClusterVertexCompatibility_v1);
  result.push_back(is_HLT_HICentralityVeto_v1);
  result.push_back(is_HLT_HIL1ETT30);
  result.push_back(is_HLT_HIL1ETT30_Core);
  result.push_back(is_HLT_HIL1ETT60);
  result.push_back(is_HLT_HIL1ETT60_Core);

  result.push_back(is_bit0);
  result.push_back(is_bit1);
  result.push_back(is_bit2);
  result.push_back(is_bit3);
  result.push_back(is_bit4);
  result.push_back(is_bit5);
  result.push_back(is_bit6);
  result.push_back(is_bit7);
  result.push_back(is_bit8);
  result.push_back(is_bit9);
  result.push_back(is_bit10);
  result.push_back(is_bit11);
  result.push_back(is_bit12);
  result.push_back(is_bit32);
  result.push_back(is_bit33);
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
  result.push_back(is_bit55);
  result.push_back(is_bit60);
  result.push_back(is_bit61);
  result.push_back(is_bit62);
  result.push_back(is_bit63);

  result.push_back(is_L1_ZeroBias);
  result.push_back(is_L1_BscMinBiasOR_BptxAND);
  result.push_back(is_L1_BscMinBiasInnerThreshold1_BptxAND);
  result.push_back(is_L1_BscMinBiasInnerThreshold2_BptxAND);
  result.push_back(is_L1_BscMinBiasThreshold1_BptxAND);
  result.push_back(is_L1_BscMinBiasThreshold2_BptxAND);
  result.push_back(is_L1_DoubleHfBitCountsRing1_P1N1);
  result.push_back(is_L1_DoubleHfBitCountsRing2_P1N1);
  result.push_back(is_L1_DoubleHfRingEtSumsRing1_P4N4);
  result.push_back(is_L1_DoubleHfRingEtSumsRing1_P200N200);
  result.push_back(is_L1_DoubleHfRingEtSumsRing2_P4N4);
  result.push_back(is_L1_DoubleHfRingEtSumsRing2_P200N200);
  result.push_back(is_L1_ZdcScintTightVertex_BptxAND);
  result.push_back(is_L1_ZdcScintLooseVertex_BptxAND);
  result.push_back(is_L1_BscMinBiasThreshold1);
  result.push_back(is_L1_ZdcCaloPlus);
  result.push_back(is_L1_ZdcCaloMinus);
  result.push_back(is_L1_ZdcCaloPlus_BptxAND);
  result.push_back(is_L1_ZdcCaloMinus_BptxAND);
  result.push_back(is_L1_ZdcCaloPlus_ZdcCaloMinus_BptxAND);
  result.push_back(is_L1_HcalHfMmOrPpOrPm);
  result.push_back(is_L1_HcalHfCoincidencePm);
  result.push_back(is_L1_HcalHfMmpOrMpp);
  result.push_back(is_L1_HcalHoTotalOR);
  result.push_back(is_L1_ETT60);
  result.push_back(is_L1_ETT60_BptxAND);
  result.push_back(is_L1_ZdcCaloPlus_ZdcCaloMinus);
  result.push_back(is_L1_BptxMinus);
  result.push_back(is_L1_BptxPlus);
  result.push_back(is_L1_BptxPlusORMinus);
  result.push_back(is_L1_ETT30_BptxAND);
  result.push_back(is_L1_ETT30);
  result.push_back(is_L1_ZdcScintTightVertex);
  result.push_back(is_L1_ZdcScintPlus);
  result.push_back(is_L1_ZdcScintMinus);
  result.push_back(is_L1_BscMinBiasInnerThreshold1);
  result.push_back(is_L1_BptxPlusANDMinus);
  result.push_back(is_L1_BscMinBiasOR_BptxPlusORMinus);
  result.push_back(is_L1_HcalHfCoincPmORBscMinBiasThresh1_BptxAND);
  result.push_back(is_L1_HcalHfCoincPmORBscMinBiasThresh2_BptxAND);

  result.push_back(1);  //numVtx
  result.push_back(1);    //numEv

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
  float clusters_on_layers = 0.;
  for(SiPixelRecHitCollection::DataContainer::const_iterator iPRH = pixelRecHits.data().begin(); iPRH != pixelRecHits.data().end(); ++iPRH ) {
     const PixelGeomDetUnit* pgdu = dynamic_cast<const PixelGeomDetUnit*>(geom->idToDetUnit((*iPRH).geographicalId()));

     if(pgdu->subDetector() != GeomDetEnumerators::PixelBarrel)
        continue;

     PXBDetId pdetId = PXBDetId((*iPRH).geographicalId());
     int layer=pdetId.layer();

     if(layer != desLayer)
        continue;

     clusters_on_layers++;

     GlobalPoint globalPosition = pgdu->toGlobal((*iPRH).localPosition());
     float x = fabs(globalPosition.x() - theBeamSpot->position().x());
     float y = fabs(globalPosition.y() - theBeamSpot->position().y());
     double R = TMath::Sqrt(x*x + y*y);
     double eta_corr = -log(tan(atan2(R,(globalPosition.z()-rver_z))/2.));
     int clustSizeY = (iPRH)->cluster()->sizeY();

     if(eta_corr<3.0 && eta_corr>=2.5 && clustSizeY>8.5)   
       { clustSizeY_etaP6++; passedClusters.push_back(&(*iPRH)); }
     if(eta_corr<2.5 && eta_corr>2.0 && clustSizeY>5.5)   //Positive etas
       { clustSizeY_etaP5++; passedClusters.push_back(&(*iPRH)); }
     if(eta_corr<=2.0 && eta_corr>1.5 && clustSizeY>3.5)   //Positive etas
       { clustSizeY_etaP4++; passedClusters.push_back(&(*iPRH)); }
     if(eta_corr<=1.5 && eta_corr>1.0 && clustSizeY>2.5)   //Positive etas
       { clustSizeY_etaP3++; passedClusters.push_back(&(*iPRH)); }
     if(eta_corr<=1.0 && eta_corr>0.5 && clustSizeY>1.5)   //Positive etas
       { clustSizeY_etaP2++; passedClusters.push_back(&(*iPRH)); }
     if(eta_corr<=0.5 && eta_corr>0.0)   //Positive etas + no cut
       { clustSizeY_etaP1++; passedClusters.push_back(&(*iPRH)); }
     if(eta_corr<=0.0 && eta_corr>-0.5)   //Negative etas + no cut
       { clustSizeY_etaN1++; passedClusters.push_back(&(*iPRH)); }
     if(eta_corr<=-0.5 && eta_corr>-1.0 && clustSizeY>1.5)   //Negative etas
       { clustSizeY_etaN2++; passedClusters.push_back(&(*iPRH)); }
     if(eta_corr<=-1.0 && eta_corr>-1.5 && clustSizeY>2.5)   //Negative etas
       { clustSizeY_etaN3++; passedClusters.push_back(&(*iPRH)); }
     if(eta_corr<=-1.5 && eta_corr>-2.0 && clustSizeY>3.5)   //Negative etas
       { clustSizeY_etaN4++; passedClusters.push_back(&(*iPRH)); }
     if(eta_corr<=-2.0 && eta_corr>-2.5 && clustSizeY>5.5)   //Negative etas
       { clustSizeY_etaN5++; passedClusters.push_back(&(*iPRH)); }
     if(eta_corr<=-2.5 && eta_corr>-3.0 && clustSizeY>8.5)   
       { clustSizeY_etaN6++; passedClusters.push_back(&(*iPRH)); }

  }
  result.push_back(clusters_on_layers); //clusters_on_layers

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

  // fill the ntuple
  if(desLayer==1)
    multProp->Fill(&result[0]);
  if(desLayer==2)
    nd_multProp->Fill(&result[0]);
  if(desLayer==3)
    rd_multProp->Fill(&result[0]);

//  std::cerr<<"   [HI_siple::...yprop] 1A" << std::endl;

//  if(vertices->size()==1) {
  if(1) {

    // Get pixel hits
    theHits = siPixelRecCollection.product();
    // result vector

//    std::cerr<<"      [HI_siple::...yprop] 4" << std::endl;
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
        // Look at a certain barrel only
        if(pid.layer() == (unsigned)desLayer)
        for(SiPixelRecHitCollection::DetSet::const_iterator recHit = range.begin();
                             recHit!= range.end(); recHit++)
        {
          GlobalPoint gpos = pixelDet->toGlobal(recHit->localPosition());
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

          vector<float> result_looper;

          result_looper.push_back(EdVertex); //EdVert

          result_looper.push_back(centBin_KK); //centBin_KK
          result_looper.push_back(centBin); //centBin
          result_looper.push_back(lowEdge); //lowEdge
          result_looper.push_back(npartMean); //NPart
          result_looper.push_back(npartSigma);//NPartSigma
          result_looper.push_back(ncollMean); //NColl
          result_looper.push_back(ncollSigma);//NCollSigma
          result_looper.push_back(nhardMean); //NHard
          result_looper.push_back(nhardSigma);//NHardSigma
          result_looper.push_back(bMean);     //B
          result_looper.push_back(bSigma);    //BSigma

          result_looper.push_back(aboveTriggerThreshold_CandMaker(towers,1.));  //CandMaker_coinc_1
          result_looper.push_back(aboveTriggerThreshold_CandMaker(towers,2.));  //CandMaker_coinc_2
          result_looper.push_back(aboveTriggerThreshold_CandMaker(towers,3.));  //CandMaker_coinc_3
          result_looper.push_back(aboveTriggerThreshold_CandMaker(towers,4.));  //CandMaker_coinc_4
          result_looper.push_back(aboveTriggerThreshold_1(towers));
          result_looper.push_back(aboveTriggerThreshold_2(towers));
          result_looper.push_back(aboveTriggerThreshold_3(towers));

          result_looper.push_back(rver_z);
          result_looper.push_back(eta);
          result_looper.push_back(eta_det);
          result_looper.push_back(phi);
          result_looper.push_back(eloss);
//          result_looper.push_back(type*(isAtEdge(topology,*recHit) ? -1 : 1));
//          result_looper.push_back(vertices->size());
          result_looper.push_back(1);
          result_looper.push_back(clustSizeY);
          result_looper.push_back(clustSizeX);
          result_looper.push_back(length);
          result_looper.push_back(pixels);
          result_looper.push_back(cluster_counter);

          result_looper.push_back(is_HLT_HIMinBiasHfOrBSC_Core);
          result_looper.push_back(is_HLT_HIMinBiasHfOrBSC_v1);
          result_looper.push_back(is_HLT_HIZeroBias_v1);
          result_looper.push_back(is_HLT_HIZeroBiasPixel_SingleTrack);
          result_looper.push_back(is_HLT_HIMinBiasBSC_v1);
          result_looper.push_back(is_HLT_HIMinBiasBSC_OR_v1);
          result_looper.push_back(is_HLT_HIMinBiasBSC_Core);
          result_looper.push_back(is_HLT_HIMinBiasBSC_OR_Core);
          result_looper.push_back(is_HLT_HIMinBiasHF_v1);
          result_looper.push_back(is_HLT_HIMinBiasPixel_SingleTrack);
          result_looper.push_back(is_HLT_HIL1Tech_BSC_minBias);
          result_looper.push_back(is_HLT_HIL1Tech_BSC_minBias_OR);
          result_looper.push_back(is_HLT_HIL1Tech_BSC_HighMultiplicity);
          result_looper.push_back(is_HLT_HIL1Tech_HCAL_HF);
          result_looper.push_back(is_HLT_HIClusterVertexCompatibility_v1);
          result_looper.push_back(is_HLT_HICentralityVeto_v1);
          result_looper.push_back(is_HLT_HIL1ETT30);
          result_looper.push_back(is_HLT_HIL1ETT30_Core);
          result_looper.push_back(is_HLT_HIL1ETT60);
          result_looper.push_back(is_HLT_HIL1ETT60_Core);

          result_looper.push_back(is_bit0);
          result_looper.push_back(is_bit1);
          result_looper.push_back(is_bit2);
          result_looper.push_back(is_bit3);
          result_looper.push_back(is_bit4);
          result_looper.push_back(is_bit5);
          result_looper.push_back(is_bit6);
          result_looper.push_back(is_bit7);
          result_looper.push_back(is_bit8);
          result_looper.push_back(is_bit9);
          result_looper.push_back(is_bit10);
          result_looper.push_back(is_bit11);
          result_looper.push_back(is_bit12);
          result_looper.push_back(is_bit32);
          result_looper.push_back(is_bit33);
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
          result_looper.push_back(is_bit55);
          result_looper.push_back(is_bit60);
          result_looper.push_back(is_bit61);
          result_looper.push_back(is_bit62);
          result_looper.push_back(is_bit63);

          result_looper.push_back(is_L1_ZeroBias);
          result_looper.push_back(is_L1_BscMinBiasOR_BptxAND);
          result_looper.push_back(is_L1_BscMinBiasInnerThreshold1_BptxAND);
          result_looper.push_back(is_L1_BscMinBiasInnerThreshold2_BptxAND);
          result_looper.push_back(is_L1_BscMinBiasThreshold1_BptxAND);
          result_looper.push_back(is_L1_BscMinBiasThreshold2_BptxAND);
          result_looper.push_back(is_L1_DoubleHfBitCountsRing1_P1N1);
          result_looper.push_back(is_L1_DoubleHfBitCountsRing2_P1N1);
          result_looper.push_back(is_L1_DoubleHfRingEtSumsRing1_P4N4);
          result_looper.push_back(is_L1_DoubleHfRingEtSumsRing1_P200N200);
          result_looper.push_back(is_L1_DoubleHfRingEtSumsRing2_P4N4);
          result_looper.push_back(is_L1_DoubleHfRingEtSumsRing2_P200N200);
          result_looper.push_back(is_L1_ZdcScintTightVertex_BptxAND);
          result_looper.push_back(is_L1_ZdcScintLooseVertex_BptxAND);
          result_looper.push_back(is_L1_BscMinBiasThreshold1);
          result_looper.push_back(is_L1_ZdcCaloPlus);
          result_looper.push_back(is_L1_ZdcCaloMinus);
          result_looper.push_back(is_L1_ZdcCaloPlus_BptxAND);
          result_looper.push_back(is_L1_ZdcCaloMinus_BptxAND);
          result_looper.push_back(is_L1_ZdcCaloPlus_ZdcCaloMinus_BptxAND);
          result_looper.push_back(is_L1_HcalHfMmOrPpOrPm);
          result_looper.push_back(is_L1_HcalHfCoincidencePm);
          result_looper.push_back(is_L1_HcalHfMmpOrMpp);
          result_looper.push_back(is_L1_HcalHoTotalOR);
          result_looper.push_back(is_L1_ETT60);
          result_looper.push_back(is_L1_ETT60_BptxAND);
          result_looper.push_back(is_L1_ZdcCaloPlus_ZdcCaloMinus);
          result_looper.push_back(is_L1_BptxMinus);
          result_looper.push_back(is_L1_BptxPlus);
          result_looper.push_back(is_L1_BptxPlusORMinus);
          result_looper.push_back(is_L1_ETT30_BptxAND);
          result_looper.push_back(is_L1_ETT30);
          result_looper.push_back(is_L1_ZdcScintTightVertex);
          result_looper.push_back(is_L1_ZdcScintPlus);
          result_looper.push_back(is_L1_ZdcScintMinus);
          result_looper.push_back(is_L1_BscMinBiasInnerThreshold1);
          result_looper.push_back(is_L1_BptxPlusANDMinus);
          result_looper.push_back(is_L1_BscMinBiasOR_BptxPlusORMinus);
          result_looper.push_back(is_L1_HcalHfCoincPmORBscMinBiasThresh1_BptxAND);
          result_looper.push_back(is_L1_HcalHfCoincPmORBscMinBiasThresh2_BptxAND);

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
  }

}

/*****************************************************************************/
bool HI_simple_nosiminfo::isAtEdge
  (const RectangularPixelTopology* topology, const SiPixelRecHit & recHit)
{
  return topology->isItEdgePixelInX(recHit.cluster()->minPixelCol()) ||
         topology->isItEdgePixelInX(recHit.cluster()->maxPixelCol()) ||
         topology->isItEdgePixelInY(recHit.cluster()->minPixelRow()) ||
         topology->isItEdgePixelInY(recHit.cluster()->maxPixelRow());
}

/*****************************************************************************/
void HI_simple_nosiminfo::analyze
  (const edm::Event& ev, const edm::EventSetup& es)
{
//  std::cerr<<"[HI_simple_nosiminfo] started" << std::endl;

  // Get centrality
  centrality_ = new CentralityProvider(es);
  centrality_->newEvent(ev,es);

  // Get tracker geometry
  edm::ESHandle<TrackerGeometry> tracker;
  es.get<TrackerDigiGeometryRecord>().get(tracker);
  theTracker = tracker.product();

//  std::cerr<<"[HI_simple_nosiminfo] alive 2" << std::endl;

  // Beam spot
  edm::Handle<BeamSpot>      beamSpotHandle;
  ev.getByLabel("offlineBeamSpot", beamSpotHandle);
  theBeamSpot = beamSpotHandle.product();

//  std::cerr<<"[HI_simple_nosiminfo] alive 3" << std::endl;

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

//  std::cerr<<"[HI_simple_nosiminfo] alive 5" << std::endl;

  // Get siPixelRecHits
  edm::Handle<SiPixelRecHitCollection> siPixelRecCollection;
  ev.getByLabel(src_,siPixelRecCollection);

//  std::cerr<<"[HI_simple_nosiminfo] alive 6" << std::endl;

  // Analyze
//  FirstSimOnFirst(siPixelRecCollection, ev, es);

//  std::cerr<<"   [HI_simple_nosiminfo] collections loaded..." << std::endl;
//  std::cerr<<"   [HI_simple_nosiminfo] layer1 started" << std::endl;

  multiplicityProperties(ev, es, towers, siPixelRecCollection, recCollection, tpg, centrality_, 1);
  multiplicityProperties(ev, es, towers, siPixelRecCollection, recCollection, tpg, centrality_, 2);
  multiplicityProperties(ev, es, towers, siPixelRecCollection, recCollection, tpg, centrality_, 3);

  HF_details(towers,centrality_,ev,siPixelRecCollection);
//  std::cerr<<"   [HI_simple_nosiminfo] layer3 finished" << std::endl;

//  clusterVertices(ev, es, siPixelRecCollection);
}
DEFINE_FWK_MODULE(HI_simple_nosiminfo);

