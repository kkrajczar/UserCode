import FWCore.ParameterSet.Config as cms

process = cms.Process("DigitizationReconstruction")

process.load("Configuration.StandardSequences.Services_cff")
process.load("Configuration.StandardSequences.MixingNoPileUp_cff")
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
process.load("Configuration.StandardSequences.Geometry_cff")
process.load("Configuration.StandardSequences.MagneticField_cff")
process.load("Configuration.StandardSequences.Reconstruction_cff")

process.load("Configuration.StandardSequences.Simulation_cff")
process.load("Configuration.StandardSequences.RawToDigi_cff")

process.load("SimGeneral.TrackingAnalysis.trackingParticles_cfi")
process.load("SimTracker.TrackAssociation.TrackAssociatorByHits_cfi")

process.load("Validation.RecoTrack.cuts_cff")
process.load("RecoLocalTracker.Configuration.RecoLocalTracker_cff")
process.load("RecoVertex.BeamSpotProducer.BeamSpot_cfi")

###############################################################################
# Source
process.source = cms.Source("PoolSource",
    skipEvents = cms.untracked.uint32(0),
    fileNames  = cms.untracked.vstring(
       'rfio:/castor/cern.ch/user/k/krajczar/Jul26thReReco_2EBFAA6D-F898-DF11-8968-003048D476BA.root',
       'rfio:/castor/cern.ch/user/k/krajczar/Jul26thReReco_DA833C5C-F898-DF11-8577-0025B3E063BA.root'
#       '/store/relval/CMSSW_3_8_2/RelValMinBias/GEN-SIM-RECO/MC_38Y_V9-v1/0019/FEC5BB4D-BFAF-DF11-A52A-001A92810AD2.root',
#       '/store/relval/CMSSW_3_8_2/RelValMinBias/GEN-SIM-RECO/MC_38Y_V9-v1/0018/92EFBB25-93AF-DF11-B346-002618943829.root',
#       '/store/relval/CMSSW_3_8_2/RelValMinBias/GEN-SIM-RECO/MC_38Y_V9-v1/0017/02C8A512-83AF-DF11-B903-0030486792B4.root'
    )
)

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(10)
)

###############################################################################
# Global tag
process.GlobalTag.globaltag = 'GR_R_38X_V13A::All'

###############################################################################
# Track analyzer
process.highMultAnalyzer = cms.EDAnalyzer("HighMultAnalyzer",
    hasSIMInfo = cms.bool(False),
    multiplicityCut = cms.int32(1),
    fileName_ASCII = cms.string('particles_DATA.txt'),
    fileName_ROOT = cms.string('particles_DATA.root')
)

###############################################################################
# Paths

process.load('Configuration.EventContent.EventContent_cff')
process.output = cms.OutputModule("PoolOutputModule",
#    splitLevel = cms.untracked.int32(0),
#    outputCommands = process.RECOEventContent.outputCommands,
    fileName = cms.untracked.string('test.root')
#    dataset = cms.untracked.PSet(
#        dataTier = cms.untracked.string('RECO'),
#        filterName = cms.untracked.string('')
#    )
)
#process.out_step = cms.EndPath(process.output)

process.load("MitEdm.Producers.evtSelData_cfi")
process.load("MitEdm.Filters.FilterLumi_cfi")
process.load("MitEdm.Filters.FilterL1_cff")
process.load("UserCode.KrisztianKrajczarHighMult.FilterHLT_cff")
process.load("MitEdm.Filters.FilterEvtSel_cff")

process.all = cms.Path(
                       process.L1BscORBptxOR
                       * process.hltMinBiasBSCORBPTXPlusORMinus
                       * ~process.L1BscHalo
                       * process.L1BptxAND
                       * process.siPixelRecHits
                       * process.evtSelData
                       * process.hfEvtSelFilter                       
                       * process.highMultAnalyzer
                       * process.output
                      )
