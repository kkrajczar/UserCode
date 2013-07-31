import FWCore.ParameterSet.Config as cms

process = cms.Process('ANALYZESIM')

# import of standard configurations
process.load('Configuration/StandardSequences/Services_cff')
process.load('FWCore/MessageService/MessageLogger_cfi')
process.load('Configuration/StandardSequences/MixingNoPileUp_cff')
process.load('Configuration/StandardSequences/GeometryIdeal_cff')
process.load('Configuration/StandardSequences/MagneticField_38T_cff')
process.load('Configuration/StandardSequences/RawToDigi_cff')
process.load('Configuration/StandardSequences/Reconstruction_cff')
process.load('Configuration/StandardSequences/FrontierConditions_GlobalTag_cff')
process.load('Configuration/EventContent/EventContent_cff')

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(10)
)
process.options = cms.untracked.PSet(
    Rethrow = cms.untracked.vstring('ProductNotFound')
)
# Input source
process.source = cms.Source("PoolSource",
#    fileNames = cms.untracked.vstring('/store/relval/CMSSW_3_1_0_pre10/RelValMinBias/GEN-SIM-DIGI-RAW-HLTDEBUG/IDEAL_31X_v1/0008/6EC01FA9-8A57-DE11-ABDA-001D09F2983F.root')
    fileNames  = cms.untracked.vstring(
       #/RelValMinBias/CMSSW_3_3_4-STARTUP3X_V8A-v1/GEN-SIM-DIGI-RAW-HLTDEBUG
       '/store/relval/CMSSW_3_3_4/RelValMinBias/GEN-SIM-DIGI-RAW-HLTDEBUG/STARTUP3X_V8A-v1/0001/40328DFC-3ED5-DE11-B704-0018F3D0960A.root',
       '/store/relval/CMSSW_3_3_4/RelValMinBias/GEN-SIM-DIGI-RAW-HLTDEBUG/STARTUP3X_V8A-v1/0001/12B371B2-6AD5-DE11-AA6F-0026189438D3.root',
       '/store/relval/CMSSW_3_3_4/RelValMinBias/GEN-SIM-DIGI-RAW-HLTDEBUG/STARTUP3X_V8A-v1/0000/AA9DB2E5-3CD5-DE11-A0A8-00261894386D.root',
       '/store/relval/CMSSW_3_3_4/RelValMinBias/GEN-SIM-DIGI-RAW-HLTDEBUG/STARTUP3X_V8A-v1/0000/7262F574-3DD5-DE11-A41C-0018F3D096EE.root',
       '/store/relval/CMSSW_3_3_4/RelValMinBias/GEN-SIM-DIGI-RAW-HLTDEBUG/STARTUP3X_V8A-v1/0000/4C50D939-36D5-DE11-9885-003048678DA2.root'
    )
)

# Other statements
process.GlobalTag.globaltag = 'STARTUP3X_V8A::All'

################################
#
#  ANALYZER
#
################################

#process.analyzeTracks = cms.EDAnalyzer("QCDTrackAnalyzer_tracks",
#    file = cms.string('test.root')
#)
process.analyzeTracks = cms.EDAnalyzer("ChargedMultiplicityAnalyzer_new",
    src = cms.InputTag("siPixelRecHits"),
    file = cms.string('test_SIM_TrackVertexing_NewBeamSpot.root'),
    simulateTriggers = cms.bool( False ),
    hasL1Triggers = cms.bool( False ),
    produceVertexLocally = cms.bool( False ),
    vertexColl = cms.InputTag("pixel3Vertices")
)

################################
#
#  BEAMSPOT
#
################################

process.BeamSpotDBSource = cms.ESSource("PoolDBESSource",
       process.CondDBSetup,
       toGet = cms.VPSet(cms.PSet(
          record = cms.string('BeamSpotObjectsRcd'),
          tag = cms.string('Early900GeVCollision_7p4cm_STARTUP3X_V8E'))
       ),
       connect = cms.string('sqlite_file:EarlyCollision.db')
)
process.es_prefer_beamspot = cms.ESPrefer("PoolDBESSource","BeamSpotDBSource")

################################
#
#  PixelTracks
#
################################
#process.load('HLTrigger/Configuration/PixelTracks_cfi')
process.load('UserCode/KrisztianKrajczarPixelCounting/PixelTracks_cfi')
process.load("RecoLocalCalo.Configuration.RecoLocalCalo_cff")
process.load("RecoJets.Configuration.CaloTowersRec_cff")

# SHOULD BE USED FOR AGGLOMERATIVE VETEXING
#process.load("UserCode.KrisztianKrajczarPixelCounting.forTrackVertexing_cff")
process.load("RecoVertex.BeamSpotProducer.BeamSpot_cfi")

process.raw2digi_step = cms.Path(process.RawToDigi)
#process.reconstruction_step = cms.Path(process.trackerlocalreco*process.offlineBeamSpot*process.hltPixelTracksForMinBias*process.hltPixelCands)
process.reconstruction_step = cms.Path(process.trackerlocalreco*process.calolocalreco*process.caloTowersRec*process.offlineBeamSpot*process.hltPixelTracksForMinBias*process.hltPixelCands)

# VERTEXING SKIPPED!!
#process.analyze_step = cms.Path(process.dNdpTVertexing*process.analyzeTracks)
process.analyze_step = cms.Path(process.analyzeTracks)

process.beamS = cms.Path(process.offlineBeamSpot)
process.mixing = cms.Path(process.mix)

# Schedule definition
#process.schedule = cms.Schedule(process.raw2digi_step,process.reconstruction_step,process.analyze_step)#,process.endjob_step)
process.schedule = cms.Schedule(process.mixing,process.beamS,process.raw2digi_step,process.reconstruction_step,process.analyze_step)#,process.endjob_step)

