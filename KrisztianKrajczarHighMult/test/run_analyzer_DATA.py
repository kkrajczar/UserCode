import FWCore.ParameterSet.Config as cms

process = cms.Process("Analysis")

process.load("Configuration.StandardSequences.Services_cff")
#process.load("Configuration.StandardSequences.MixingNoPileUp_cff")
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
process.load("Configuration.StandardSequences.Geometry_cff")
process.load("Configuration.StandardSequences.MagneticField_38T_cff")
process.load("Configuration.StandardSequences.Reconstruction_cff")

#process.load("Configuration.StandardSequences.Simulation_cff")
process.load("Configuration.StandardSequences.RawToDigi_cff")

process.load("Validation.RecoTrack.cuts_cff")
#process.load("RecoLocalTracker.Configuration.RecoLocalTracker_cff")
#process.load("RecoVertex.BeamSpotProducer.BeamSpot_cfi")

###############################################################################
# Source
process.source = cms.Source("PoolSource",
    skipEvents = cms.untracked.uint32(0),
    fileNames  = cms.untracked.vstring(
       'rfio:/castor/cern.ch/user/k/krajczar/crab/test_1_1_iEv.root',
       'rfio:/castor/cern.ch/user/k/krajczar/crab/test_2_1_lgg.root',
       'rfio:/castor/cern.ch/user/k/krajczar/crab/test_3_1_wPm.root'
    )
)

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(1000)
)

###############################################################################
# Cuts
#process.cutsRecoTracks.algorithm = cms.vstring(ALGORITHM)
#process.cutsRecoTracks.quality = cms.vstring(QUALITY)

###############################################################################
# Track analyzer
process.highMultAnalyzer = cms.EDAnalyzer("HighMultAnalyzer",
    hasSIMInfo = cms.bool(False),
    writeASCII = cms.bool(False),
    multiplicityCut = cms.int32(1),
    fileName_ASCII = cms.string('particles_DATA.txt'),
    fileName_ROOT = cms.string('particles_DATA.root')
)

###############################################################################
# Global tag
# Jul26th rerec (from https://twiki.cern.ch/twiki/bin/viewauth/CMS/Collisions2010Analysis):
process.GlobalTag.globaltag = 'GR_R_37X_V6D::All'

###############################################################################
# Path
process.analyze = cms.Path(
                           process.highMultAnalyzer
                          )

###############################################################################
# Schedule
process.schedule = cms.Schedule(
                                 process.analyze
                                )


