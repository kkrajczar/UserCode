import FWCore.ParameterSet.Config as cms

process = cms.Process('ANALYZE')

# import of standard configurations
process.load('Configuration.StandardSequences.Services_cff')
process.load('SimGeneral.HepPDTESSource.pythiapdt_cfi')
process.load('FWCore.MessageService.MessageLogger_cfi')
process.load('Configuration.EventContent.EventContentHeavyIons_cff')
process.load('Configuration.StandardSequences.GeometryDB_cff')
process.load('Configuration.StandardSequences.MagneticField_0T_cff')
process.load('Configuration.StandardSequences.RawToDigi_Repacked_cff')
process.load('Configuration.StandardSequences.ReconstructionHeavyIons_cff')
process.load('Configuration.StandardSequences.EndOfProcess_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')

#EXTRA
#process.load('RecoVertex.BeamSpotProducer.BeamSpot_cfi')

############################################################
# Message logger
#process.MessageLogger = cms.Service("MessageLogger",
#    cerr = cms.untracked.PSet(
##        threshold = cms.untracked.string('WARNING'),
##        threshold = cms.untracked.string('DEBUG'),
#        threshold = cms.untracked.string('ERROR'),
##        DEBUG = cms.untracked.PSet(
#        ERROR = cms.untracked.PSet(
#            limit = cms.untracked.int32(1)
#        )
#    ),
#    destinations = cms.untracked.vstring('cerr')
#)
############################################################

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(100)
)
process.options = cms.untracked.PSet(
    Rethrow = cms.untracked.vstring('ProductNotFound')
)
# Input source
process.source = cms.Source("PoolSource",
#    skipEvents = cms.untracked.uint32(1),
#    fileNames = cms.untracked.vstring('file:dcap:///pnfs/cmsaf.mit.edu/t2bat/cmsfile:dcap:///pnfs/cmsaf.mit.edu/t2bat/cms/store/relval/CMSSW_3_1_0_pre10/RelValMinBias/GEN-SIM-DIGI-RAW-HLTDEBUG/IDEAL_31X_v1/0008/6EC01FA9-8A57-DE11-ABDA-001D09F2983F.root')
    duplicateCheckMode = cms.untracked.string('noDuplicateCheck'),
    fileNames  = cms.untracked.vstring(
       #/RelValHydjetQ_MinBias_2760GeV/CMSSW_4_4_0-STARTHI44_V4-v2/GEN-SIM-RECO
       '/store/relval/CMSSW_4_4_0/RelValHydjetQ_MinBias_2760GeV/GEN-SIM-RECO/STARTHI44_V4-v2/0045/56A7BCDE-5CE6-E011-A5A3-001A92971B92.root'
#       'file:rfio://'
    )
)

# GLOBAL TAG
# BEWARE: EXPRESS global tag?
process.GlobalTag.globaltag = 'START44_V6::All'
process.GlobalTag.toGet = cms.VPSet()
process.GlobalTag.toGet.append(cms.PSet(tag=cms.string("L1GtTriggerMenu_L1Menu_CollisionsHeavyIons2011_v0_mc"),record=cms.string("L1GtTriggerMenuRcd"),connect=cms.untracked.string("frontier://FrontierProd/CMS_COND_31X_L1T"),))

# CENTRALITY - updated infos from Yetkin, 08.02.2011
from CmsHi.Analysis2010.CommonFunctions_cff import *
overrideGlobalTag(process)

#process.HeavyIonGlobalParameters = cms.PSet(
#    centralitySrc = cms.InputTag("hiCentrality"),
#    centralityVariable = cms.string("HFtowers"),
#    nonDefaultGlauberModel = cms.string("")
#)
process.HeavyIonGlobalParameters = cms.PSet(
    centralitySrc = cms.InputTag("hiCentrality"),
    centralityVariable = cms.string("HFhits"),
    nonDefaultGlauberModel = cms.string("")
)

################################
#
#  ANALYZER
#
################################

process.analyzer = cms.EDAnalyzer("HI_simple_nosiminfo",
    src = cms.InputTag("siPixelRecHits"),
    file = cms.string('test_Data_FromRAW.root'),
    hasL1Triggers = cms.bool( True ),
    produceVertexLocally = cms.bool( False ),
    vertexColl = cms.InputTag("hiPixelClusterVertex"),
    triggerLabel = cms.InputTag( 'TriggerResults','',"HLT")
)

process.load("HLTrigger.HLTfilters.hltHighLevel_cfi")
process.hltMinBiasHfORBSC = process.hltHighLevel.clone()
process.hltMinBiasHfORBSC.HLTPaths = ["HLT_HIMinBiasHfOrBSC_v1"]

process.load("HeavyIonsAnalysis.Configuration.collisionEventSelection_cff")

# PATH
process.myfilter = cms.Path(process.hltMinBiasHfORBSC*process.collisionEventSelection)
process.raw2digi_step = cms.Path(process.RawToDigi)
#process.reconstruction_step = cms.Path(process.localReco) #no centrality this way
process.reconstruction_step = cms.Path(process.reconstructionHeavyIons)
process.myanalyzer_step = cms.Path(process.hiPixelClusterVertex*process.analyzer)
#process.endjob_step = cms.EndPath(process.endOfProcess)

process.schedule = cms.Schedule(
                      process.raw2digi_step,
                      process.reconstruction_step,
                      process.myanalyzer_step
                      )
