import FWCore.ParameterSet.Config as cms

process = cms.Process("Analysis")

process.load("Configuration.StandardSequences.Services_cff")
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
#process.load("Configuration.StandardSequences.Geometry_cff")
process.load("Configuration.StandardSequences.MagneticField_38T_cff")
process.load("Configuration.StandardSequences.Reconstruction_cff")

#process.load("Configuration.StandardSequences.RawToDigi_cff")

#process.load("Validation.RecoTrack.cuts_cff")
#process.load("RecoLocalTracker.Configuration.RecoLocalTracker_cff")
#process.load("RecoVertex.BeamSpotProducer.BeamSpot_cfi")

###############################################################################
# Source
process.source = cms.Source("PoolSource",
    skipEvents = cms.untracked.uint32(0),
    fileNames  = cms.untracked.vstring(
       #/RelValProdTTbar/CMSSW_5_3_6-START53_V14-v2/AODSIM
       '/store/relval/CMSSW_5_3_6-START53_V14/RelValProdTTbar/AODSIM/v2/00000/76ED0FA6-1E2A-E211-B8F1-001A92971B72.root'
    )
)

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(-1)
)


###############################################################################
# NTuple maker
process.MakeAlignmentNTuple = cms.EDAnalyzer("MakeAlignmentNTuple",
    fileName_ROOT = cms.string('AlignmentNtuple.root')
)

###############################################################################
# Global tag
process.GlobalTag.globaltag = 'START53_V14::All'

###############################################################################
# Path
process.alignmentNtuple = cms.Path(
                           process.MakeAlignmentNTuple
                          )

###############################################################################
# Schedule
process.schedule = cms.Schedule(
                                 process.alignmentNtuple
                                )


