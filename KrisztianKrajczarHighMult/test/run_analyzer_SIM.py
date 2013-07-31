import FWCore.ParameterSet.Config as cms

process = cms.Process("DigitizationReconstruction")

process.load("Configuration.StandardSequences.Services_cff")
process.load("Configuration.StandardSequences.MixingNoPileUp_cff")
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
process.load("Configuration.StandardSequences.Geometry_cff")
process.load("Configuration.StandardSequences.MagneticField_38T_cff")
process.load("Configuration.StandardSequences.Reconstruction_cff")

process.load("Configuration.StandardSequences.Simulation_cff")
process.load("Configuration.StandardSequences.RawToDigi_cff")

process.load("SimGeneral.TrackingAnalysis.trackingParticles_cfi")
process.load("SimTracker.TrackAssociation.TrackAssociatorByHits_cfi")

process.load("Validation.RecoTrack.cuts_cff")
process.load("RecoLocalTracker.Configuration.RecoLocalTracker_cff")
#process.load("RecoVertex.BeamSpotProducer.BeamSpot_cfi")

###############################################################################
# Source
process.source = cms.Source("PoolSource",
    skipEvents = cms.untracked.uint32(0),
    fileNames  = cms.untracked.vstring(
    #/RelValMinBias/CMSSW_3_8_3-START38_V9-v1/GEN-SIM-DIGI-RAW-HLTDEBUG 
       '/store/relval/CMSSW_3_8_3/RelValMinBias/GEN-SIM-DIGI-RAW-HLTDEBUG/START38_V9-v1/0022/A263E1D8-F3BF-DF11-82D0-00304867C136.root',
       '/store/relval/CMSSW_3_8_3/RelValMinBias/GEN-SIM-DIGI-RAW-HLTDEBUG/START38_V9-v1/0022/A0A6A900-F5BF-DF11-AC88-0018F3D0965E.root',
       '/store/relval/CMSSW_3_8_3/RelValMinBias/GEN-SIM-DIGI-RAW-HLTDEBUG/START38_V9-v1/0022/6E609717-3BC0-DF11-BA1C-00261894393D.root',
       '/store/relval/CMSSW_3_8_3/RelValMinBias/GEN-SIM-DIGI-RAW-HLTDEBUG/START38_V9-v1/0022/60730564-F4BF-DF11-87B1-003048678F8A.root',
       '/store/relval/CMSSW_3_8_3/RelValMinBias/GEN-SIM-DIGI-RAW-HLTDEBUG/START38_V9-v1/0021/423925E3-99BF-DF11-8AF4-0018F3D09626.root'
    )
)

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(100)
)

###############################################################################
# Associator
process.TrackAssociatorByHits.SimToRecoDenominator = cms.string('reco')

###############################################################################
# Cuts
#process.cutsRecoTracks.algorithm = cms.vstring(ALGORITHM)
#process.cutsRecoTracks.quality = cms.vstring(QUALITY)

###############################################################################
# Track analyzer
process.highMultAnalyzer = cms.EDAnalyzer("HighMultAnalyzer",
    hasSIMInfo = cms.bool(True),
    writeASCII = cms.bool(False),
    multiplicityCut = cms.int32(1),
    fileName_ASCII = cms.string('particles_SIM.txt'),
    fileName_ROOT = cms.string('particles_SIM.root')
)

###############################################################################
# Global tag
process.GlobalTag.globaltag = 'START38_V9::All'

###############################################################################
# Paths

process.simu  = cms.Path(
                         process.mix*
                         process.trackingParticles
                        )

process.rawToDigi = cms.Path(
                             process.siPixelDigis*
                             process.SiStripRawToDigis
                            )

process.lreco = cms.Path(
                         process.trackerlocalreco
                        )

process.greco = cms.Path(
                         process.offlineBeamSpot+
                         process.recopixelvertexing*
                         process.ckftracks*
#                         process.cutsRecoTracks*
                         process.offlinePrimaryVerticesWithBS ##simple pixelVertices looks bad?
                        )

process.analyze = cms.Path(
                           process.highMultAnalyzer
                          )

###############################################################################
# Schedule
process.schedule = cms.Schedule(
                                 process.simu,
                                 process.rawToDigi,
                                 process.lreco,
                                 process.greco,
                                 process.analyze
                                )


