import FWCore.ParameterSet.Config as cms

process = cms.Process('ANALYZE')

# import of standard configurations
process.load('Configuration/StandardSequences/Simulation_cff')
process.load('Configuration/StandardSequences/Services_cff')
process.load('FWCore/MessageService/MessageLogger_cfi')
process.load('Configuration/StandardSequences/Mixing')
process.load('Configuration/StandardSequences/GeometryIdeal_cff')
process.load('Configuration/StandardSequences/MagneticField_0T_cff')
process.load('Configuration/StandardSequences/RawToDigi_cff')
process.load("Configuration.StandardSequences.ReconstructionHeavyIons_cff")
process.load('Configuration/StandardSequences/FrontierConditions_GlobalTag_cff')
process.load('Configuration/EventContent/EventContent_cff')

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
    input = cms.untracked.int32(10)
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
       'file:rfio:///castor/cern.ch/user/y/yjlee/HIData2011/recoTest/reco-Run180892-D2E86FE1-FA06-E111-99DC-003048D2C01E.root'
    )
)

# GLOBAL TAG
# BEWARE: EXPRESS global tag?
process.GlobalTag.globaltag = 'GR_E_V22::All'

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
    file = cms.string('test_B0_100Eff.root'),
    hasL1Triggers = cms.bool( True ),
    produceVertexLocally = cms.bool( False ),
    vertexColl = cms.InputTag("hiPixelClusterVertex"),
    triggerLabel = cms.InputTag( 'TriggerResults','',"HLT")
)

process.load("HLTrigger.HLTfilters.hltHighLevel_cfi")
process.hltMinBiasHfORBSC = process.hltHighLevel.clone()
process.hltMinBiasHfORBSC.HLTPaths = ["HLT_HIMinBiasHfOrBSC_Core"]

# NO VTX
process.load("HeavyIonsAnalysis.Configuration.collisionEventSelection_cff")

# PATH
process.all = cms.Path(
                      process.hltMinBiasHfORBSC
                      *process.collisionEventSelection
#                      *process.siPixelRecHits
                      *process.hiPixelClusterVertex
                      +process.analyzer
                      )
