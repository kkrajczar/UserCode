import FWCore.ParameterSet.Config as cms

process = cms.Process('ANALYZESIM')

# import of standard configurations
process.load('Configuration/StandardSequences/Simulation_cff')
process.load('Configuration/StandardSequences/Services_cff')
process.load('FWCore/MessageService/MessageLogger_cfi')
process.load('Configuration/StandardSequences/MixingNoPileUp_cff')
process.load('Configuration/StandardSequences/GeometryIdeal_cff')
process.load('Configuration/StandardSequences/MagneticField_38T_cff')
process.load('Configuration/StandardSequences/RawToDigi_cff')
process.load('Configuration/StandardSequences/Reconstruction_cff')
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
       #Hydjet_Quenched_MinBias_2760GeV_STARTUP39V3_L1Menu_CollisionsHeavyIons2010_v0_391v1 ... RECO ...
       'file:dcap:///pnfs/cmsaf.mit.edu/t2bat/cms/store/user/nart/Hydjet_Quenched_MinBias_2760GeV_STARTUP39V3_L1Menu_CollisionsHeavyIons2010_v0_391v1/Hydjet_Quenched_MinBias_2760GeV_STARTUP39V3_L1Menu_CollisionsHeavyIons2010_v0_391v1_RECO/4fa2e3ec03e211b495652e2ed26839f0/output_9_1_mJS.root',
       'file:dcap:///pnfs/cmsaf.mit.edu/t2bat/cms/store/user/nart/Hydjet_Quenched_MinBias_2760GeV_STARTUP39V3_L1Menu_CollisionsHeavyIons2010_v0_391v1/Hydjet_Quenched_MinBias_2760GeV_STARTUP39V3_L1Menu_CollisionsHeavyIons2010_v0_391v1_RECO/4fa2e3ec03e211b495652e2ed26839f0/output_8_1_l4L.root',
       'file:dcap:///pnfs/cmsaf.mit.edu/t2bat/cms/store/user/nart/Hydjet_Quenched_MinBias_2760GeV_STARTUP39V3_L1Menu_CollisionsHeavyIons2010_v0_391v1/Hydjet_Quenched_MinBias_2760GeV_STARTUP39V3_L1Menu_CollisionsHeavyIons2010_v0_391v1_RECO/4fa2e3ec03e211b495652e2ed26839f0/output_7_1_l2o.root',
       'file:dcap:///pnfs/cmsaf.mit.edu/t2bat/cms/store/user/nart/Hydjet_Quenched_MinBias_2760GeV_STARTUP39V3_L1Menu_CollisionsHeavyIons2010_v0_391v1/Hydjet_Quenched_MinBias_2760GeV_STARTUP39V3_L1Menu_CollisionsHeavyIons2010_v0_391v1_RECO/4fa2e3ec03e211b495652e2ed26839f0/output_6_1_C7x.root',
       'file:dcap:///pnfs/cmsaf.mit.edu/t2bat/cms/store/user/nart/Hydjet_Quenched_MinBias_2760GeV_STARTUP39V3_L1Menu_CollisionsHeavyIons2010_v0_391v1/Hydjet_Quenched_MinBias_2760GeV_STARTUP39V3_L1Menu_CollisionsHeavyIons2010_v0_391v1_RECO/4fa2e3ec03e211b495652e2ed26839f0/output_5_1_KIi.root',
       'file:dcap:///pnfs/cmsaf.mit.edu/t2bat/cms/store/user/nart/Hydjet_Quenched_MinBias_2760GeV_STARTUP39V3_L1Menu_CollisionsHeavyIons2010_v0_391v1/Hydjet_Quenched_MinBias_2760GeV_STARTUP39V3_L1Menu_CollisionsHeavyIons2010_v0_391v1_RECO/4fa2e3ec03e211b495652e2ed26839f0/output_4_1_qG8.root',
       'file:dcap:///pnfs/cmsaf.mit.edu/t2bat/cms/store/user/nart/Hydjet_Quenched_MinBias_2760GeV_STARTUP39V3_L1Menu_CollisionsHeavyIons2010_v0_391v1/Hydjet_Quenched_MinBias_2760GeV_STARTUP39V3_L1Menu_CollisionsHeavyIons2010_v0_391v1_RECO/4fa2e3ec03e211b495652e2ed26839f0/output_3_1_oWF.root',
       'file:dcap:///pnfs/cmsaf.mit.edu/t2bat/cms/store/user/nart/Hydjet_Quenched_MinBias_2760GeV_STARTUP39V3_L1Menu_CollisionsHeavyIons2010_v0_391v1/Hydjet_Quenched_MinBias_2760GeV_STARTUP39V3_L1Menu_CollisionsHeavyIons2010_v0_391v1_RECO/4fa2e3ec03e211b495652e2ed26839f0/output_2_1_uII.root',
       'file:dcap:///pnfs/cmsaf.mit.edu/t2bat/cms/store/user/nart/Hydjet_Quenched_MinBias_2760GeV_STARTUP39V3_L1Menu_CollisionsHeavyIons2010_v0_391v1/Hydjet_Quenched_MinBias_2760GeV_STARTUP39V3_L1Menu_CollisionsHeavyIons2010_v0_391v1_RECO/4fa2e3ec03e211b495652e2ed26839f0/output_1_1_2Ll.root',
       'file:dcap:///pnfs/cmsaf.mit.edu/t2bat/cms/store/user/nart/Hydjet_Quenched_MinBias_2760GeV_STARTUP39V3_L1Menu_CollisionsHeavyIons2010_v0_391v1/Hydjet_Quenched_MinBias_2760GeV_STARTUP39V3_L1Menu_CollisionsHeavyIons2010_v0_391v1_RECO/4fa2e3ec03e211b495652e2ed26839f0/output_11_1_iJR.root',
       'file:dcap:///pnfs/cmsaf.mit.edu/t2bat/cms/store/user/nart/Hydjet_Quenched_MinBias_2760GeV_STARTUP39V3_L1Menu_CollisionsHeavyIons2010_v0_391v1/Hydjet_Quenched_MinBias_2760GeV_STARTUP39V3_L1Menu_CollisionsHeavyIons2010_v0_391v1_RECO/4fa2e3ec03e211b495652e2ed26839f0/output_10_1_YtH.root' 
    )
)

# GLOBAL TAG
process.GlobalTag.globaltag = 'START39_V4HI::All'

# CENTRALITY
process.HeavyIonGlobalParameters = cms.PSet(
    centralityVariable = cms.string("HFhits"),
    nonDefaultGlauberModel = cms.string("Hydjet_2760GeV"),
    centralitySrc = cms.InputTag("hiCentrality")
)

################################
#
#  ANALYZER
#
################################

process.analyzer = cms.EDAnalyzer("HI_simple_sim",
    src = cms.InputTag("siPixelRecHits"),
    file = cms.string('test_sim.root'),
    hasL1Triggers = cms.bool( True ),
    simulateTriggers = cms.bool( False ),
    produceVertexLocally = cms.bool( False ),
    vertexColl = cms.InputTag("hiSelectedVertex"),
    triggerLabel = cms.InputTag( 'TriggerResults','',"HLT")
)

################################
#
#  BEAMSPOT
#
################################

#process.BeamSpotDBSource = cms.ESSource("PoolDBESSource",
#       process.CondDBSetup,
#       toGet = cms.VPSet(cms.PSet(
#          record = cms.string('BeamSpotObjectsRcd'),
#          tag = cms.string('Early900GeVCollision_124023_STARTUP3X_V8I'))
#       ),
#       connect = cms.string('sqlite_file:EarlyCollision_124023.db')
#)
#process.es_prefer_beamspot = cms.ESPrefer("PoolDBESSource","BeamSpotDBSource")

process.all = cms.Path(
                      process.mix
                      *process.siPixelRecHits
                      +process.analyzer
                      )
