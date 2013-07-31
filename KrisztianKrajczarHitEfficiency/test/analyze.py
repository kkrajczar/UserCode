import FWCore.ParameterSet.Config as cms

process = cms.Process("DigitizationReconstruction")

process.load("Configuration.StandardSequences.Services_cff")
process.load("Configuration.StandardSequences.MixingNoPileUp_cff")
process.load("Configuration.StandardSequences.Simulation_cff")
process.load("Configuration.StandardSequences.Digi_cff")
process.load("Configuration.StandardSequences.Geometry_cff")
process.load("Configuration.StandardSequences.MagneticField_cff")
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
process.load("Configuration.StandardSequences.RawToDigi_cff")
process.load("Configuration.StandardSequences.DigiToRaw_cff")
process.load("SimGeneral.TrackingAnalysis.trackingParticles_cfi")
process.load("RecoLocalTracker.Configuration.RecoLocalTracker_cff")
process.load("RecoVertex.BeamSpotProducer.BeamSpot_cfi")
process.load("UserCode.KrisztianKrajczarHitEfficiency.TracksForEfficiency_cff")

process.load("FWCore.MessageService.MessageLogger_cfi")

###############################################################################
# Source
process.source = cms.Source("PoolSource",
    duplicateCheckMode = cms.untracked.string('noDuplicateCheck'),
    skipEvents = cms.untracked.uint32(0),
    fileNames  = cms.untracked.vstring(
       #/RelValMinBias/CMSSW_3_3_4-STARTUP3X_V8A-v1/GEN-SIM-DIGI-RAW-HLTDEBUG
       '/store/relval/CMSSW_3_3_4/RelValMinBias/GEN-SIM-DIGI-RAW-HLTDEBUG/STARTUP3X_V8A-v1/0001/40328DFC-3ED5-DE11-B704-0018F3D0960A.root',
       '/store/relval/CMSSW_3_3_4/RelValMinBias/GEN-SIM-DIGI-RAW-HLTDEBUG/STARTUP3X_V8A-v1/0001/12B371B2-6AD5-DE11-AA6F-0026189438D3.root',
       '/store/relval/CMSSW_3_3_4/RelValMinBias/GEN-SIM-DIGI-RAW-HLTDEBUG/STARTUP3X_V8A-v1/0000/AA9DB2E5-3CD5-DE11-A0A8-00261894386D.root',
       '/store/relval/CMSSW_3_3_4/RelValMinBias/GEN-SIM-DIGI-RAW-HLTDEBUG/STARTUP3X_V8A-v1/0000/7262F574-3DD5-DE11-A41C-0018F3D096EE.root',
       '/store/relval/CMSSW_3_3_4/RelValMinBias/GEN-SIM-DIGI-RAW-HLTDEBUG/STARTUP3X_V8A-v1/0000/4C50D939-36D5-DE11-9885-003048678DA2.root'
    )
)

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(10)
)

###############################################################################
# BeamSpot for 900 Gev
process.BeamSpotDBSource = cms.ESSource("PoolDBESSource",
       process.CondDBSetup,
       toGet = cms.VPSet(cms.PSet(
          record = cms.string('BeamSpotObjectsRcd'),
          tag = cms.string('Early900GeVCollision_7p4cm_STARTUP3X_V8E'))
       ),
       connect = cms.string('sqlite_file:EarlyCollision.db')
)
process.es_prefer_beamspot = cms.ESPrefer("PoolDBESSource","BeamSpotDBSource")

###############################################################################
# Analyzer
process.analyzeTracks = cms.EDAnalyzer("TrackAnalyzer",
    file = cms.string('test.root')
)

###############################################################################
# Paths
process.r2d   = cms.Path(process.RawToDigi)

process.beamS  = cms.Path(process.offlineBeamSpot)

process.lreco = cms.Path(process.trackerlocalreco)

process.greco = cms.Path(
                         process.minBiasTracking_hitEff
                        * process.analyzeTracks)

###############################################################################
# Global tag
process.GlobalTag.globaltag = 'STARTUP3X_V8A::All'

###############################################################################
# Schedule

process.schedule = cms.Schedule(
                                process.r2d,
                                process.beamS,
                                process.lreco,
                                process.greco)
