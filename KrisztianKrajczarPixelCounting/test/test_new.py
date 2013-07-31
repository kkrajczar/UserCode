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
#    fileNames = cms.untracked.vstring('file:dcap:///pnfs/cmsaf.mit.edu/t2bat/cms/store/relval/CMSSW_3_1_0_pre10/RelValMinBias/GEN-SIM-DIGI-RAW-HLTDEBUG/IDEAL_31X_v1/0008/6EC01FA9-8A57-DE11-ABDA-001D09F2983F.root')
    duplicateCheckMode = cms.untracked.string('noDuplicateCheck'),
    fileNames  = cms.untracked.vstring(
      #/Hydjet_Quenched_MinBias_2760GeV_STARTUP39V2_GEN_SIM_RAWDEBUG_390/davidlw-Hydjet_Quenched_MinBias_2760GeV_STARTUP39V2_GEN_SIM_RECODEBUG_390-e91272bc2b91d5f6eefc8e1f2c112a67/USER
       'file:dcap:///pnfs/cmsaf.mit.edu/t2bat/cms/store/user/davidlw/Hydjet_Quenched_MinBias_2760GeV_STARTUP39V2_GEN_SIM_RAWDEBUG_390/Hydjet_Quenched_MinBias_2760GeV_STARTUP39V2_GEN_SIM_RECODEBUG_390/e91272bc2b91d5f6eefc8e1f2c112a67/hiReco_RAW2DIGI_RECO_9_1_klj.root',
       'file:dcap:///pnfs/cmsaf.mit.edu/t2bat/cms/store/user/davidlw/Hydjet_Quenched_MinBias_2760GeV_STARTUP39V2_GEN_SIM_RAWDEBUG_390/Hydjet_Quenched_MinBias_2760GeV_STARTUP39V2_GEN_SIM_RECODEBUG_390/e91272bc2b91d5f6eefc8e1f2c112a67/hiReco_RAW2DIGI_RECO_99_1_bJF.root',
       'file:dcap:///pnfs/cmsaf.mit.edu/t2bat/cms/store/user/davidlw/Hydjet_Quenched_MinBias_2760GeV_STARTUP39V2_GEN_SIM_RAWDEBUG_390/Hydjet_Quenched_MinBias_2760GeV_STARTUP39V2_GEN_SIM_RECODEBUG_390/e91272bc2b91d5f6eefc8e1f2c112a67/hiReco_RAW2DIGI_RECO_98_1_J2H.root',
       'file:dcap:///pnfs/cmsaf.mit.edu/t2bat/cms/store/user/davidlw/Hydjet_Quenched_MinBias_2760GeV_STARTUP39V2_GEN_SIM_RAWDEBUG_390/Hydjet_Quenched_MinBias_2760GeV_STARTUP39V2_GEN_SIM_RECODEBUG_390/e91272bc2b91d5f6eefc8e1f2c112a67/hiReco_RAW2DIGI_RECO_97_1_U2M.root',
       'file:dcap:///pnfs/cmsaf.mit.edu/t2bat/cms/store/user/davidlw/Hydjet_Quenched_MinBias_2760GeV_STARTUP39V2_GEN_SIM_RAWDEBUG_390/Hydjet_Quenched_MinBias_2760GeV_STARTUP39V2_GEN_SIM_RECODEBUG_390/e91272bc2b91d5f6eefc8e1f2c112a67/hiReco_RAW2DIGI_RECO_96_1_xLX.root',
       'file:dcap:///pnfs/cmsaf.mit.edu/t2bat/cms/store/user/davidlw/Hydjet_Quenched_MinBias_2760GeV_STARTUP39V2_GEN_SIM_RAWDEBUG_390/Hydjet_Quenched_MinBias_2760GeV_STARTUP39V2_GEN_SIM_RECODEBUG_390/e91272bc2b91d5f6eefc8e1f2c112a67/hiReco_RAW2DIGI_RECO_95_1_7XN.root',
       'file:dcap:///pnfs/cmsaf.mit.edu/t2bat/cms/store/user/davidlw/Hydjet_Quenched_MinBias_2760GeV_STARTUP39V2_GEN_SIM_RAWDEBUG_390/Hydjet_Quenched_MinBias_2760GeV_STARTUP39V2_GEN_SIM_RECODEBUG_390/e91272bc2b91d5f6eefc8e1f2c112a67/hiReco_RAW2DIGI_RECO_94_1_O8c.root',
       'file:dcap:///pnfs/cmsaf.mit.edu/t2bat/cms/store/user/davidlw/Hydjet_Quenched_MinBias_2760GeV_STARTUP39V2_GEN_SIM_RAWDEBUG_390/Hydjet_Quenched_MinBias_2760GeV_STARTUP39V2_GEN_SIM_RECODEBUG_390/e91272bc2b91d5f6eefc8e1f2c112a67/hiReco_RAW2DIGI_RECO_93_1_nxB.root',
       'file:dcap:///pnfs/cmsaf.mit.edu/t2bat/cms/store/user/davidlw/Hydjet_Quenched_MinBias_2760GeV_STARTUP39V2_GEN_SIM_RAWDEBUG_390/Hydjet_Quenched_MinBias_2760GeV_STARTUP39V2_GEN_SIM_RECODEBUG_390/e91272bc2b91d5f6eefc8e1f2c112a67/hiReco_RAW2DIGI_RECO_92_1_i92.root',
       'file:dcap:///pnfs/cmsaf.mit.edu/t2bat/cms/store/user/davidlw/Hydjet_Quenched_MinBias_2760GeV_STARTUP39V2_GEN_SIM_RAWDEBUG_390/Hydjet_Quenched_MinBias_2760GeV_STARTUP39V2_GEN_SIM_RECODEBUG_390/e91272bc2b91d5f6eefc8e1f2c112a67/hiReco_RAW2DIGI_RECO_91_1_GJQ.root',
       'file:dcap:///pnfs/cmsaf.mit.edu/t2bat/cms/store/user/davidlw/Hydjet_Quenched_MinBias_2760GeV_STARTUP39V2_GEN_SIM_RAWDEBUG_390/Hydjet_Quenched_MinBias_2760GeV_STARTUP39V2_GEN_SIM_RECODEBUG_390/e91272bc2b91d5f6eefc8e1f2c112a67/hiReco_RAW2DIGI_RECO_90_1_Hxc.root',
       'file:dcap:///pnfs/cmsaf.mit.edu/t2bat/cms/store/user/davidlw/Hydjet_Quenched_MinBias_2760GeV_STARTUP39V2_GEN_SIM_RAWDEBUG_390/Hydjet_Quenched_MinBias_2760GeV_STARTUP39V2_GEN_SIM_RECODEBUG_390/e91272bc2b91d5f6eefc8e1f2c112a67/hiReco_RAW2DIGI_RECO_8_1_V1q.root',
       'file:dcap:///pnfs/cmsaf.mit.edu/t2bat/cms/store/user/davidlw/Hydjet_Quenched_MinBias_2760GeV_STARTUP39V2_GEN_SIM_RAWDEBUG_390/Hydjet_Quenched_MinBias_2760GeV_STARTUP39V2_GEN_SIM_RECODEBUG_390/e91272bc2b91d5f6eefc8e1f2c112a67/hiReco_RAW2DIGI_RECO_89_1_bqH.root',
       'file:dcap:///pnfs/cmsaf.mit.edu/t2bat/cms/store/user/davidlw/Hydjet_Quenched_MinBias_2760GeV_STARTUP39V2_GEN_SIM_RAWDEBUG_390/Hydjet_Quenched_MinBias_2760GeV_STARTUP39V2_GEN_SIM_RECODEBUG_390/e91272bc2b91d5f6eefc8e1f2c112a67/hiReco_RAW2DIGI_RECO_88_1_VbF.root',
       'file:dcap:///pnfs/cmsaf.mit.edu/t2bat/cms/store/user/davidlw/Hydjet_Quenched_MinBias_2760GeV_STARTUP39V2_GEN_SIM_RAWDEBUG_390/Hydjet_Quenched_MinBias_2760GeV_STARTUP39V2_GEN_SIM_RECODEBUG_390/e91272bc2b91d5f6eefc8e1f2c112a67/hiReco_RAW2DIGI_RECO_87_1_dP3.root',
       'file:dcap:///pnfs/cmsaf.mit.edu/t2bat/cms/store/user/davidlw/Hydjet_Quenched_MinBias_2760GeV_STARTUP39V2_GEN_SIM_RAWDEBUG_390/Hydjet_Quenched_MinBias_2760GeV_STARTUP39V2_GEN_SIM_RECODEBUG_390/e91272bc2b91d5f6eefc8e1f2c112a67/hiReco_RAW2DIGI_RECO_86_1_uyJ.root',
       'file:dcap:///pnfs/cmsaf.mit.edu/t2bat/cms/store/user/davidlw/Hydjet_Quenched_MinBias_2760GeV_STARTUP39V2_GEN_SIM_RAWDEBUG_390/Hydjet_Quenched_MinBias_2760GeV_STARTUP39V2_GEN_SIM_RECODEBUG_390/e91272bc2b91d5f6eefc8e1f2c112a67/hiReco_RAW2DIGI_RECO_85_1_sJG.root',
       'file:dcap:///pnfs/cmsaf.mit.edu/t2bat/cms/store/user/davidlw/Hydjet_Quenched_MinBias_2760GeV_STARTUP39V2_GEN_SIM_RAWDEBUG_390/Hydjet_Quenched_MinBias_2760GeV_STARTUP39V2_GEN_SIM_RECODEBUG_390/e91272bc2b91d5f6eefc8e1f2c112a67/hiReco_RAW2DIGI_RECO_84_1_sHz.root',
       'file:dcap:///pnfs/cmsaf.mit.edu/t2bat/cms/store/user/davidlw/Hydjet_Quenched_MinBias_2760GeV_STARTUP39V2_GEN_SIM_RAWDEBUG_390/Hydjet_Quenched_MinBias_2760GeV_STARTUP39V2_GEN_SIM_RECODEBUG_390/e91272bc2b91d5f6eefc8e1f2c112a67/hiReco_RAW2DIGI_RECO_83_1_5WI.root',
       'file:dcap:///pnfs/cmsaf.mit.edu/t2bat/cms/store/user/davidlw/Hydjet_Quenched_MinBias_2760GeV_STARTUP39V2_GEN_SIM_RAWDEBUG_390/Hydjet_Quenched_MinBias_2760GeV_STARTUP39V2_GEN_SIM_RECODEBUG_390/e91272bc2b91d5f6eefc8e1f2c112a67/hiReco_RAW2DIGI_RECO_82_1_Ofd.root',
       'file:dcap:///pnfs/cmsaf.mit.edu/t2bat/cms/store/user/davidlw/Hydjet_Quenched_MinBias_2760GeV_STARTUP39V2_GEN_SIM_RAWDEBUG_390/Hydjet_Quenched_MinBias_2760GeV_STARTUP39V2_GEN_SIM_RECODEBUG_390/e91272bc2b91d5f6eefc8e1f2c112a67/hiReco_RAW2DIGI_RECO_81_1_nwk.root',
       'file:dcap:///pnfs/cmsaf.mit.edu/t2bat/cms/store/user/davidlw/Hydjet_Quenched_MinBias_2760GeV_STARTUP39V2_GEN_SIM_RAWDEBUG_390/Hydjet_Quenched_MinBias_2760GeV_STARTUP39V2_GEN_SIM_RECODEBUG_390/e91272bc2b91d5f6eefc8e1f2c112a67/hiReco_RAW2DIGI_RECO_80_1_S3M.root',
       'file:dcap:///pnfs/cmsaf.mit.edu/t2bat/cms/store/user/davidlw/Hydjet_Quenched_MinBias_2760GeV_STARTUP39V2_GEN_SIM_RAWDEBUG_390/Hydjet_Quenched_MinBias_2760GeV_STARTUP39V2_GEN_SIM_RECODEBUG_390/e91272bc2b91d5f6eefc8e1f2c112a67/hiReco_RAW2DIGI_RECO_7_1_dtD.root',
       'file:dcap:///pnfs/cmsaf.mit.edu/t2bat/cms/store/user/davidlw/Hydjet_Quenched_MinBias_2760GeV_STARTUP39V2_GEN_SIM_RAWDEBUG_390/Hydjet_Quenched_MinBias_2760GeV_STARTUP39V2_GEN_SIM_RECODEBUG_390/e91272bc2b91d5f6eefc8e1f2c112a67/hiReco_RAW2DIGI_RECO_79_1_9Uq.root',
       'file:dcap:///pnfs/cmsaf.mit.edu/t2bat/cms/store/user/davidlw/Hydjet_Quenched_MinBias_2760GeV_STARTUP39V2_GEN_SIM_RAWDEBUG_390/Hydjet_Quenched_MinBias_2760GeV_STARTUP39V2_GEN_SIM_RECODEBUG_390/e91272bc2b91d5f6eefc8e1f2c112a67/hiReco_RAW2DIGI_RECO_78_1_OVa.root',
       'file:dcap:///pnfs/cmsaf.mit.edu/t2bat/cms/store/user/davidlw/Hydjet_Quenched_MinBias_2760GeV_STARTUP39V2_GEN_SIM_RAWDEBUG_390/Hydjet_Quenched_MinBias_2760GeV_STARTUP39V2_GEN_SIM_RECODEBUG_390/e91272bc2b91d5f6eefc8e1f2c112a67/hiReco_RAW2DIGI_RECO_77_1_LTv.root',
       'file:dcap:///pnfs/cmsaf.mit.edu/t2bat/cms/store/user/davidlw/Hydjet_Quenched_MinBias_2760GeV_STARTUP39V2_GEN_SIM_RAWDEBUG_390/Hydjet_Quenched_MinBias_2760GeV_STARTUP39V2_GEN_SIM_RECODEBUG_390/e91272bc2b91d5f6eefc8e1f2c112a67/hiReco_RAW2DIGI_RECO_76_1_a4Z.root',
       'file:dcap:///pnfs/cmsaf.mit.edu/t2bat/cms/store/user/davidlw/Hydjet_Quenched_MinBias_2760GeV_STARTUP39V2_GEN_SIM_RAWDEBUG_390/Hydjet_Quenched_MinBias_2760GeV_STARTUP39V2_GEN_SIM_RECODEBUG_390/e91272bc2b91d5f6eefc8e1f2c112a67/hiReco_RAW2DIGI_RECO_75_1_Ncs.root',
       'file:dcap:///pnfs/cmsaf.mit.edu/t2bat/cms/store/user/davidlw/Hydjet_Quenched_MinBias_2760GeV_STARTUP39V2_GEN_SIM_RAWDEBUG_390/Hydjet_Quenched_MinBias_2760GeV_STARTUP39V2_GEN_SIM_RECODEBUG_390/e91272bc2b91d5f6eefc8e1f2c112a67/hiReco_RAW2DIGI_RECO_74_1_bJo.root',
       'file:dcap:///pnfs/cmsaf.mit.edu/t2bat/cms/store/user/davidlw/Hydjet_Quenched_MinBias_2760GeV_STARTUP39V2_GEN_SIM_RAWDEBUG_390/Hydjet_Quenched_MinBias_2760GeV_STARTUP39V2_GEN_SIM_RECODEBUG_390/e91272bc2b91d5f6eefc8e1f2c112a67/hiReco_RAW2DIGI_RECO_73_1_X8G.root',
       'file:dcap:///pnfs/cmsaf.mit.edu/t2bat/cms/store/user/davidlw/Hydjet_Quenched_MinBias_2760GeV_STARTUP39V2_GEN_SIM_RAWDEBUG_390/Hydjet_Quenched_MinBias_2760GeV_STARTUP39V2_GEN_SIM_RECODEBUG_390/e91272bc2b91d5f6eefc8e1f2c112a67/hiReco_RAW2DIGI_RECO_72_1_Rq9.root',
       'file:dcap:///pnfs/cmsaf.mit.edu/t2bat/cms/store/user/davidlw/Hydjet_Quenched_MinBias_2760GeV_STARTUP39V2_GEN_SIM_RAWDEBUG_390/Hydjet_Quenched_MinBias_2760GeV_STARTUP39V2_GEN_SIM_RECODEBUG_390/e91272bc2b91d5f6eefc8e1f2c112a67/hiReco_RAW2DIGI_RECO_71_1_fKr.root',
       'file:dcap:///pnfs/cmsaf.mit.edu/t2bat/cms/store/user/davidlw/Hydjet_Quenched_MinBias_2760GeV_STARTUP39V2_GEN_SIM_RAWDEBUG_390/Hydjet_Quenched_MinBias_2760GeV_STARTUP39V2_GEN_SIM_RECODEBUG_390/e91272bc2b91d5f6eefc8e1f2c112a67/hiReco_RAW2DIGI_RECO_70_1_SBm.root',
       'file:dcap:///pnfs/cmsaf.mit.edu/t2bat/cms/store/user/davidlw/Hydjet_Quenched_MinBias_2760GeV_STARTUP39V2_GEN_SIM_RAWDEBUG_390/Hydjet_Quenched_MinBias_2760GeV_STARTUP39V2_GEN_SIM_RECODEBUG_390/e91272bc2b91d5f6eefc8e1f2c112a67/hiReco_RAW2DIGI_RECO_6_1_ZfY.root',
       'file:dcap:///pnfs/cmsaf.mit.edu/t2bat/cms/store/user/davidlw/Hydjet_Quenched_MinBias_2760GeV_STARTUP39V2_GEN_SIM_RAWDEBUG_390/Hydjet_Quenched_MinBias_2760GeV_STARTUP39V2_GEN_SIM_RECODEBUG_390/e91272bc2b91d5f6eefc8e1f2c112a67/hiReco_RAW2DIGI_RECO_69_1_gaK.root',
       'file:dcap:///pnfs/cmsaf.mit.edu/t2bat/cms/store/user/davidlw/Hydjet_Quenched_MinBias_2760GeV_STARTUP39V2_GEN_SIM_RAWDEBUG_390/Hydjet_Quenched_MinBias_2760GeV_STARTUP39V2_GEN_SIM_RECODEBUG_390/e91272bc2b91d5f6eefc8e1f2c112a67/hiReco_RAW2DIGI_RECO_68_1_O7c.root',
       'file:dcap:///pnfs/cmsaf.mit.edu/t2bat/cms/store/user/davidlw/Hydjet_Quenched_MinBias_2760GeV_STARTUP39V2_GEN_SIM_RAWDEBUG_390/Hydjet_Quenched_MinBias_2760GeV_STARTUP39V2_GEN_SIM_RECODEBUG_390/e91272bc2b91d5f6eefc8e1f2c112a67/hiReco_RAW2DIGI_RECO_67_1_ztr.root',
       'file:dcap:///pnfs/cmsaf.mit.edu/t2bat/cms/store/user/davidlw/Hydjet_Quenched_MinBias_2760GeV_STARTUP39V2_GEN_SIM_RAWDEBUG_390/Hydjet_Quenched_MinBias_2760GeV_STARTUP39V2_GEN_SIM_RECODEBUG_390/e91272bc2b91d5f6eefc8e1f2c112a67/hiReco_RAW2DIGI_RECO_66_1_0lQ.root',
       'file:dcap:///pnfs/cmsaf.mit.edu/t2bat/cms/store/user/davidlw/Hydjet_Quenched_MinBias_2760GeV_STARTUP39V2_GEN_SIM_RAWDEBUG_390/Hydjet_Quenched_MinBias_2760GeV_STARTUP39V2_GEN_SIM_RECODEBUG_390/e91272bc2b91d5f6eefc8e1f2c112a67/hiReco_RAW2DIGI_RECO_65_1_4Wy.root',
       'file:dcap:///pnfs/cmsaf.mit.edu/t2bat/cms/store/user/davidlw/Hydjet_Quenched_MinBias_2760GeV_STARTUP39V2_GEN_SIM_RAWDEBUG_390/Hydjet_Quenched_MinBias_2760GeV_STARTUP39V2_GEN_SIM_RECODEBUG_390/e91272bc2b91d5f6eefc8e1f2c112a67/hiReco_RAW2DIGI_RECO_64_1_jNV.root',
       'file:dcap:///pnfs/cmsaf.mit.edu/t2bat/cms/store/user/davidlw/Hydjet_Quenched_MinBias_2760GeV_STARTUP39V2_GEN_SIM_RAWDEBUG_390/Hydjet_Quenched_MinBias_2760GeV_STARTUP39V2_GEN_SIM_RECODEBUG_390/e91272bc2b91d5f6eefc8e1f2c112a67/hiReco_RAW2DIGI_RECO_63_1_gQk.root',
       'file:dcap:///pnfs/cmsaf.mit.edu/t2bat/cms/store/user/davidlw/Hydjet_Quenched_MinBias_2760GeV_STARTUP39V2_GEN_SIM_RAWDEBUG_390/Hydjet_Quenched_MinBias_2760GeV_STARTUP39V2_GEN_SIM_RECODEBUG_390/e91272bc2b91d5f6eefc8e1f2c112a67/hiReco_RAW2DIGI_RECO_62_1_btM.root',
       'file:dcap:///pnfs/cmsaf.mit.edu/t2bat/cms/store/user/davidlw/Hydjet_Quenched_MinBias_2760GeV_STARTUP39V2_GEN_SIM_RAWDEBUG_390/Hydjet_Quenched_MinBias_2760GeV_STARTUP39V2_GEN_SIM_RECODEBUG_390/e91272bc2b91d5f6eefc8e1f2c112a67/hiReco_RAW2DIGI_RECO_61_1_gov.root',
       'file:dcap:///pnfs/cmsaf.mit.edu/t2bat/cms/store/user/davidlw/Hydjet_Quenched_MinBias_2760GeV_STARTUP39V2_GEN_SIM_RAWDEBUG_390/Hydjet_Quenched_MinBias_2760GeV_STARTUP39V2_GEN_SIM_RECODEBUG_390/e91272bc2b91d5f6eefc8e1f2c112a67/hiReco_RAW2DIGI_RECO_60_1_jEA.root',
       'file:dcap:///pnfs/cmsaf.mit.edu/t2bat/cms/store/user/davidlw/Hydjet_Quenched_MinBias_2760GeV_STARTUP39V2_GEN_SIM_RAWDEBUG_390/Hydjet_Quenched_MinBias_2760GeV_STARTUP39V2_GEN_SIM_RECODEBUG_390/e91272bc2b91d5f6eefc8e1f2c112a67/hiReco_RAW2DIGI_RECO_5_1_EC0.root',
       'file:dcap:///pnfs/cmsaf.mit.edu/t2bat/cms/store/user/davidlw/Hydjet_Quenched_MinBias_2760GeV_STARTUP39V2_GEN_SIM_RAWDEBUG_390/Hydjet_Quenched_MinBias_2760GeV_STARTUP39V2_GEN_SIM_RECODEBUG_390/e91272bc2b91d5f6eefc8e1f2c112a67/hiReco_RAW2DIGI_RECO_59_1_cBF.root',
       'file:dcap:///pnfs/cmsaf.mit.edu/t2bat/cms/store/user/davidlw/Hydjet_Quenched_MinBias_2760GeV_STARTUP39V2_GEN_SIM_RAWDEBUG_390/Hydjet_Quenched_MinBias_2760GeV_STARTUP39V2_GEN_SIM_RECODEBUG_390/e91272bc2b91d5f6eefc8e1f2c112a67/hiReco_RAW2DIGI_RECO_58_1_HJc.root',
       'file:dcap:///pnfs/cmsaf.mit.edu/t2bat/cms/store/user/davidlw/Hydjet_Quenched_MinBias_2760GeV_STARTUP39V2_GEN_SIM_RAWDEBUG_390/Hydjet_Quenched_MinBias_2760GeV_STARTUP39V2_GEN_SIM_RECODEBUG_390/e91272bc2b91d5f6eefc8e1f2c112a67/hiReco_RAW2DIGI_RECO_57_1_XL5.root',
       'file:dcap:///pnfs/cmsaf.mit.edu/t2bat/cms/store/user/davidlw/Hydjet_Quenched_MinBias_2760GeV_STARTUP39V2_GEN_SIM_RAWDEBUG_390/Hydjet_Quenched_MinBias_2760GeV_STARTUP39V2_GEN_SIM_RECODEBUG_390/e91272bc2b91d5f6eefc8e1f2c112a67/hiReco_RAW2DIGI_RECO_56_1_a5g.root',
       'file:dcap:///pnfs/cmsaf.mit.edu/t2bat/cms/store/user/davidlw/Hydjet_Quenched_MinBias_2760GeV_STARTUP39V2_GEN_SIM_RAWDEBUG_390/Hydjet_Quenched_MinBias_2760GeV_STARTUP39V2_GEN_SIM_RECODEBUG_390/e91272bc2b91d5f6eefc8e1f2c112a67/hiReco_RAW2DIGI_RECO_54_1_Mza.root',
       'file:dcap:///pnfs/cmsaf.mit.edu/t2bat/cms/store/user/davidlw/Hydjet_Quenched_MinBias_2760GeV_STARTUP39V2_GEN_SIM_RAWDEBUG_390/Hydjet_Quenched_MinBias_2760GeV_STARTUP39V2_GEN_SIM_RECODEBUG_390/e91272bc2b91d5f6eefc8e1f2c112a67/hiReco_RAW2DIGI_RECO_53_1_0iD.root',
       'file:dcap:///pnfs/cmsaf.mit.edu/t2bat/cms/store/user/davidlw/Hydjet_Quenched_MinBias_2760GeV_STARTUP39V2_GEN_SIM_RAWDEBUG_390/Hydjet_Quenched_MinBias_2760GeV_STARTUP39V2_GEN_SIM_RECODEBUG_390/e91272bc2b91d5f6eefc8e1f2c112a67/hiReco_RAW2DIGI_RECO_52_1_rBS.root',
       'file:dcap:///pnfs/cmsaf.mit.edu/t2bat/cms/store/user/davidlw/Hydjet_Quenched_MinBias_2760GeV_STARTUP39V2_GEN_SIM_RAWDEBUG_390/Hydjet_Quenched_MinBias_2760GeV_STARTUP39V2_GEN_SIM_RECODEBUG_390/e91272bc2b91d5f6eefc8e1f2c112a67/hiReco_RAW2DIGI_RECO_51_1_prN.root',
       'file:dcap:///pnfs/cmsaf.mit.edu/t2bat/cms/store/user/davidlw/Hydjet_Quenched_MinBias_2760GeV_STARTUP39V2_GEN_SIM_RAWDEBUG_390/Hydjet_Quenched_MinBias_2760GeV_STARTUP39V2_GEN_SIM_RECODEBUG_390/e91272bc2b91d5f6eefc8e1f2c112a67/hiReco_RAW2DIGI_RECO_50_1_ygi.root',
       'file:dcap:///pnfs/cmsaf.mit.edu/t2bat/cms/store/user/davidlw/Hydjet_Quenched_MinBias_2760GeV_STARTUP39V2_GEN_SIM_RAWDEBUG_390/Hydjet_Quenched_MinBias_2760GeV_STARTUP39V2_GEN_SIM_RECODEBUG_390/e91272bc2b91d5f6eefc8e1f2c112a67/hiReco_RAW2DIGI_RECO_4_1_K5e.root',
       'file:dcap:///pnfs/cmsaf.mit.edu/t2bat/cms/store/user/davidlw/Hydjet_Quenched_MinBias_2760GeV_STARTUP39V2_GEN_SIM_RAWDEBUG_390/Hydjet_Quenched_MinBias_2760GeV_STARTUP39V2_GEN_SIM_RECODEBUG_390/e91272bc2b91d5f6eefc8e1f2c112a67/hiReco_RAW2DIGI_RECO_49_1_39V.root',
       'file:dcap:///pnfs/cmsaf.mit.edu/t2bat/cms/store/user/davidlw/Hydjet_Quenched_MinBias_2760GeV_STARTUP39V2_GEN_SIM_RAWDEBUG_390/Hydjet_Quenched_MinBias_2760GeV_STARTUP39V2_GEN_SIM_RECODEBUG_390/e91272bc2b91d5f6eefc8e1f2c112a67/hiReco_RAW2DIGI_RECO_48_1_juX.root',
       'file:dcap:///pnfs/cmsaf.mit.edu/t2bat/cms/store/user/davidlw/Hydjet_Quenched_MinBias_2760GeV_STARTUP39V2_GEN_SIM_RAWDEBUG_390/Hydjet_Quenched_MinBias_2760GeV_STARTUP39V2_GEN_SIM_RECODEBUG_390/e91272bc2b91d5f6eefc8e1f2c112a67/hiReco_RAW2DIGI_RECO_47_1_ji6.root',
       'file:dcap:///pnfs/cmsaf.mit.edu/t2bat/cms/store/user/davidlw/Hydjet_Quenched_MinBias_2760GeV_STARTUP39V2_GEN_SIM_RAWDEBUG_390/Hydjet_Quenched_MinBias_2760GeV_STARTUP39V2_GEN_SIM_RECODEBUG_390/e91272bc2b91d5f6eefc8e1f2c112a67/hiReco_RAW2DIGI_RECO_46_1_SvW.root',
       'file:dcap:///pnfs/cmsaf.mit.edu/t2bat/cms/store/user/davidlw/Hydjet_Quenched_MinBias_2760GeV_STARTUP39V2_GEN_SIM_RAWDEBUG_390/Hydjet_Quenched_MinBias_2760GeV_STARTUP39V2_GEN_SIM_RECODEBUG_390/e91272bc2b91d5f6eefc8e1f2c112a67/hiReco_RAW2DIGI_RECO_45_1_5ie.root',
       'file:dcap:///pnfs/cmsaf.mit.edu/t2bat/cms/store/user/davidlw/Hydjet_Quenched_MinBias_2760GeV_STARTUP39V2_GEN_SIM_RAWDEBUG_390/Hydjet_Quenched_MinBias_2760GeV_STARTUP39V2_GEN_SIM_RECODEBUG_390/e91272bc2b91d5f6eefc8e1f2c112a67/hiReco_RAW2DIGI_RECO_44_1_m3A.root',
       'file:dcap:///pnfs/cmsaf.mit.edu/t2bat/cms/store/user/davidlw/Hydjet_Quenched_MinBias_2760GeV_STARTUP39V2_GEN_SIM_RAWDEBUG_390/Hydjet_Quenched_MinBias_2760GeV_STARTUP39V2_GEN_SIM_RECODEBUG_390/e91272bc2b91d5f6eefc8e1f2c112a67/hiReco_RAW2DIGI_RECO_43_1_4cW.root',
       'file:dcap:///pnfs/cmsaf.mit.edu/t2bat/cms/store/user/davidlw/Hydjet_Quenched_MinBias_2760GeV_STARTUP39V2_GEN_SIM_RAWDEBUG_390/Hydjet_Quenched_MinBias_2760GeV_STARTUP39V2_GEN_SIM_RECODEBUG_390/e91272bc2b91d5f6eefc8e1f2c112a67/hiReco_RAW2DIGI_RECO_42_1_ObQ.root',
       'file:dcap:///pnfs/cmsaf.mit.edu/t2bat/cms/store/user/davidlw/Hydjet_Quenched_MinBias_2760GeV_STARTUP39V2_GEN_SIM_RAWDEBUG_390/Hydjet_Quenched_MinBias_2760GeV_STARTUP39V2_GEN_SIM_RECODEBUG_390/e91272bc2b91d5f6eefc8e1f2c112a67/hiReco_RAW2DIGI_RECO_41_1_5Zx.root',
       'file:dcap:///pnfs/cmsaf.mit.edu/t2bat/cms/store/user/davidlw/Hydjet_Quenched_MinBias_2760GeV_STARTUP39V2_GEN_SIM_RAWDEBUG_390/Hydjet_Quenched_MinBias_2760GeV_STARTUP39V2_GEN_SIM_RECODEBUG_390/e91272bc2b91d5f6eefc8e1f2c112a67/hiReco_RAW2DIGI_RECO_3_1_ttF.root',
       'file:dcap:///pnfs/cmsaf.mit.edu/t2bat/cms/store/user/davidlw/Hydjet_Quenched_MinBias_2760GeV_STARTUP39V2_GEN_SIM_RAWDEBUG_390/Hydjet_Quenched_MinBias_2760GeV_STARTUP39V2_GEN_SIM_RECODEBUG_390/e91272bc2b91d5f6eefc8e1f2c112a67/hiReco_RAW2DIGI_RECO_39_1_tjW.root',
       'file:dcap:///pnfs/cmsaf.mit.edu/t2bat/cms/store/user/davidlw/Hydjet_Quenched_MinBias_2760GeV_STARTUP39V2_GEN_SIM_RAWDEBUG_390/Hydjet_Quenched_MinBias_2760GeV_STARTUP39V2_GEN_SIM_RECODEBUG_390/e91272bc2b91d5f6eefc8e1f2c112a67/hiReco_RAW2DIGI_RECO_38_1_EFQ.root',
       'file:dcap:///pnfs/cmsaf.mit.edu/t2bat/cms/store/user/davidlw/Hydjet_Quenched_MinBias_2760GeV_STARTUP39V2_GEN_SIM_RAWDEBUG_390/Hydjet_Quenched_MinBias_2760GeV_STARTUP39V2_GEN_SIM_RECODEBUG_390/e91272bc2b91d5f6eefc8e1f2c112a67/hiReco_RAW2DIGI_RECO_37_1_uvh.root',
       'file:dcap:///pnfs/cmsaf.mit.edu/t2bat/cms/store/user/davidlw/Hydjet_Quenched_MinBias_2760GeV_STARTUP39V2_GEN_SIM_RAWDEBUG_390/Hydjet_Quenched_MinBias_2760GeV_STARTUP39V2_GEN_SIM_RECODEBUG_390/e91272bc2b91d5f6eefc8e1f2c112a67/hiReco_RAW2DIGI_RECO_36_1_BfR.root',
       'file:dcap:///pnfs/cmsaf.mit.edu/t2bat/cms/store/user/davidlw/Hydjet_Quenched_MinBias_2760GeV_STARTUP39V2_GEN_SIM_RAWDEBUG_390/Hydjet_Quenched_MinBias_2760GeV_STARTUP39V2_GEN_SIM_RECODEBUG_390/e91272bc2b91d5f6eefc8e1f2c112a67/hiReco_RAW2DIGI_RECO_35_1_Mmh.root',
       'file:dcap:///pnfs/cmsaf.mit.edu/t2bat/cms/store/user/davidlw/Hydjet_Quenched_MinBias_2760GeV_STARTUP39V2_GEN_SIM_RAWDEBUG_390/Hydjet_Quenched_MinBias_2760GeV_STARTUP39V2_GEN_SIM_RECODEBUG_390/e91272bc2b91d5f6eefc8e1f2c112a67/hiReco_RAW2DIGI_RECO_34_1_s6O.root',
       'file:dcap:///pnfs/cmsaf.mit.edu/t2bat/cms/store/user/davidlw/Hydjet_Quenched_MinBias_2760GeV_STARTUP39V2_GEN_SIM_RAWDEBUG_390/Hydjet_Quenched_MinBias_2760GeV_STARTUP39V2_GEN_SIM_RECODEBUG_390/e91272bc2b91d5f6eefc8e1f2c112a67/hiReco_RAW2DIGI_RECO_33_1_zoB.root',
       'file:dcap:///pnfs/cmsaf.mit.edu/t2bat/cms/store/user/davidlw/Hydjet_Quenched_MinBias_2760GeV_STARTUP39V2_GEN_SIM_RAWDEBUG_390/Hydjet_Quenched_MinBias_2760GeV_STARTUP39V2_GEN_SIM_RECODEBUG_390/e91272bc2b91d5f6eefc8e1f2c112a67/hiReco_RAW2DIGI_RECO_32_1_aay.root',
       'file:dcap:///pnfs/cmsaf.mit.edu/t2bat/cms/store/user/davidlw/Hydjet_Quenched_MinBias_2760GeV_STARTUP39V2_GEN_SIM_RAWDEBUG_390/Hydjet_Quenched_MinBias_2760GeV_STARTUP39V2_GEN_SIM_RECODEBUG_390/e91272bc2b91d5f6eefc8e1f2c112a67/hiReco_RAW2DIGI_RECO_31_1_hiR.root',
       'file:dcap:///pnfs/cmsaf.mit.edu/t2bat/cms/store/user/davidlw/Hydjet_Quenched_MinBias_2760GeV_STARTUP39V2_GEN_SIM_RAWDEBUG_390/Hydjet_Quenched_MinBias_2760GeV_STARTUP39V2_GEN_SIM_RECODEBUG_390/e91272bc2b91d5f6eefc8e1f2c112a67/hiReco_RAW2DIGI_RECO_30_1_6bd.root',
       'file:dcap:///pnfs/cmsaf.mit.edu/t2bat/cms/store/user/davidlw/Hydjet_Quenched_MinBias_2760GeV_STARTUP39V2_GEN_SIM_RAWDEBUG_390/Hydjet_Quenched_MinBias_2760GeV_STARTUP39V2_GEN_SIM_RECODEBUG_390/e91272bc2b91d5f6eefc8e1f2c112a67/hiReco_RAW2DIGI_RECO_29_1_Ki0.root',
       'file:dcap:///pnfs/cmsaf.mit.edu/t2bat/cms/store/user/davidlw/Hydjet_Quenched_MinBias_2760GeV_STARTUP39V2_GEN_SIM_RAWDEBUG_390/Hydjet_Quenched_MinBias_2760GeV_STARTUP39V2_GEN_SIM_RECODEBUG_390/e91272bc2b91d5f6eefc8e1f2c112a67/hiReco_RAW2DIGI_RECO_28_1_Czi.root',
       'file:dcap:///pnfs/cmsaf.mit.edu/t2bat/cms/store/user/davidlw/Hydjet_Quenched_MinBias_2760GeV_STARTUP39V2_GEN_SIM_RAWDEBUG_390/Hydjet_Quenched_MinBias_2760GeV_STARTUP39V2_GEN_SIM_RECODEBUG_390/e91272bc2b91d5f6eefc8e1f2c112a67/hiReco_RAW2DIGI_RECO_27_1_5q9.root',
       'file:dcap:///pnfs/cmsaf.mit.edu/t2bat/cms/store/user/davidlw/Hydjet_Quenched_MinBias_2760GeV_STARTUP39V2_GEN_SIM_RAWDEBUG_390/Hydjet_Quenched_MinBias_2760GeV_STARTUP39V2_GEN_SIM_RECODEBUG_390/e91272bc2b91d5f6eefc8e1f2c112a67/hiReco_RAW2DIGI_RECO_26_1_zQ0.root',
       'file:dcap:///pnfs/cmsaf.mit.edu/t2bat/cms/store/user/davidlw/Hydjet_Quenched_MinBias_2760GeV_STARTUP39V2_GEN_SIM_RAWDEBUG_390/Hydjet_Quenched_MinBias_2760GeV_STARTUP39V2_GEN_SIM_RECODEBUG_390/e91272bc2b91d5f6eefc8e1f2c112a67/hiReco_RAW2DIGI_RECO_25_1_oMa.root',
       'file:dcap:///pnfs/cmsaf.mit.edu/t2bat/cms/store/user/davidlw/Hydjet_Quenched_MinBias_2760GeV_STARTUP39V2_GEN_SIM_RAWDEBUG_390/Hydjet_Quenched_MinBias_2760GeV_STARTUP39V2_GEN_SIM_RECODEBUG_390/e91272bc2b91d5f6eefc8e1f2c112a67/hiReco_RAW2DIGI_RECO_24_1_XmH.root',
       'file:dcap:///pnfs/cmsaf.mit.edu/t2bat/cms/store/user/davidlw/Hydjet_Quenched_MinBias_2760GeV_STARTUP39V2_GEN_SIM_RAWDEBUG_390/Hydjet_Quenched_MinBias_2760GeV_STARTUP39V2_GEN_SIM_RECODEBUG_390/e91272bc2b91d5f6eefc8e1f2c112a67/hiReco_RAW2DIGI_RECO_23_1_tLU.root',
       'file:dcap:///pnfs/cmsaf.mit.edu/t2bat/cms/store/user/davidlw/Hydjet_Quenched_MinBias_2760GeV_STARTUP39V2_GEN_SIM_RAWDEBUG_390/Hydjet_Quenched_MinBias_2760GeV_STARTUP39V2_GEN_SIM_RECODEBUG_390/e91272bc2b91d5f6eefc8e1f2c112a67/hiReco_RAW2DIGI_RECO_22_1_6RI.root',
       'file:dcap:///pnfs/cmsaf.mit.edu/t2bat/cms/store/user/davidlw/Hydjet_Quenched_MinBias_2760GeV_STARTUP39V2_GEN_SIM_RAWDEBUG_390/Hydjet_Quenched_MinBias_2760GeV_STARTUP39V2_GEN_SIM_RECODEBUG_390/e91272bc2b91d5f6eefc8e1f2c112a67/hiReco_RAW2DIGI_RECO_21_1_yGb.root',
       'file:dcap:///pnfs/cmsaf.mit.edu/t2bat/cms/store/user/davidlw/Hydjet_Quenched_MinBias_2760GeV_STARTUP39V2_GEN_SIM_RAWDEBUG_390/Hydjet_Quenched_MinBias_2760GeV_STARTUP39V2_GEN_SIM_RECODEBUG_390/e91272bc2b91d5f6eefc8e1f2c112a67/hiReco_RAW2DIGI_RECO_20_1_zJp.root',
       'file:dcap:///pnfs/cmsaf.mit.edu/t2bat/cms/store/user/davidlw/Hydjet_Quenched_MinBias_2760GeV_STARTUP39V2_GEN_SIM_RAWDEBUG_390/Hydjet_Quenched_MinBias_2760GeV_STARTUP39V2_GEN_SIM_RECODEBUG_390/e91272bc2b91d5f6eefc8e1f2c112a67/hiReco_RAW2DIGI_RECO_1_1_laq.root',
       'file:dcap:///pnfs/cmsaf.mit.edu/t2bat/cms/store/user/davidlw/Hydjet_Quenched_MinBias_2760GeV_STARTUP39V2_GEN_SIM_RAWDEBUG_390/Hydjet_Quenched_MinBias_2760GeV_STARTUP39V2_GEN_SIM_RECODEBUG_390/e91272bc2b91d5f6eefc8e1f2c112a67/hiReco_RAW2DIGI_RECO_19_1_r4z.root',
       'file:dcap:///pnfs/cmsaf.mit.edu/t2bat/cms/store/user/davidlw/Hydjet_Quenched_MinBias_2760GeV_STARTUP39V2_GEN_SIM_RAWDEBUG_390/Hydjet_Quenched_MinBias_2760GeV_STARTUP39V2_GEN_SIM_RECODEBUG_390/e91272bc2b91d5f6eefc8e1f2c112a67/hiReco_RAW2DIGI_RECO_18_1_h5s.root',
       'file:dcap:///pnfs/cmsaf.mit.edu/t2bat/cms/store/user/davidlw/Hydjet_Quenched_MinBias_2760GeV_STARTUP39V2_GEN_SIM_RAWDEBUG_390/Hydjet_Quenched_MinBias_2760GeV_STARTUP39V2_GEN_SIM_RECODEBUG_390/e91272bc2b91d5f6eefc8e1f2c112a67/hiReco_RAW2DIGI_RECO_17_1_2V6.root',
       'file:dcap:///pnfs/cmsaf.mit.edu/t2bat/cms/store/user/davidlw/Hydjet_Quenched_MinBias_2760GeV_STARTUP39V2_GEN_SIM_RAWDEBUG_390/Hydjet_Quenched_MinBias_2760GeV_STARTUP39V2_GEN_SIM_RECODEBUG_390/e91272bc2b91d5f6eefc8e1f2c112a67/hiReco_RAW2DIGI_RECO_16_1_iVo.root',
       'file:dcap:///pnfs/cmsaf.mit.edu/t2bat/cms/store/user/davidlw/Hydjet_Quenched_MinBias_2760GeV_STARTUP39V2_GEN_SIM_RAWDEBUG_390/Hydjet_Quenched_MinBias_2760GeV_STARTUP39V2_GEN_SIM_RECODEBUG_390/e91272bc2b91d5f6eefc8e1f2c112a67/hiReco_RAW2DIGI_RECO_15_1_Bmr.root',
       'file:dcap:///pnfs/cmsaf.mit.edu/t2bat/cms/store/user/davidlw/Hydjet_Quenched_MinBias_2760GeV_STARTUP39V2_GEN_SIM_RAWDEBUG_390/Hydjet_Quenched_MinBias_2760GeV_STARTUP39V2_GEN_SIM_RECODEBUG_390/e91272bc2b91d5f6eefc8e1f2c112a67/hiReco_RAW2DIGI_RECO_14_1_ERJ.root',
       'file:dcap:///pnfs/cmsaf.mit.edu/t2bat/cms/store/user/davidlw/Hydjet_Quenched_MinBias_2760GeV_STARTUP39V2_GEN_SIM_RAWDEBUG_390/Hydjet_Quenched_MinBias_2760GeV_STARTUP39V2_GEN_SIM_RECODEBUG_390/e91272bc2b91d5f6eefc8e1f2c112a67/hiReco_RAW2DIGI_RECO_13_1_AIe.root',
       'file:dcap:///pnfs/cmsaf.mit.edu/t2bat/cms/store/user/davidlw/Hydjet_Quenched_MinBias_2760GeV_STARTUP39V2_GEN_SIM_RAWDEBUG_390/Hydjet_Quenched_MinBias_2760GeV_STARTUP39V2_GEN_SIM_RECODEBUG_390/e91272bc2b91d5f6eefc8e1f2c112a67/hiReco_RAW2DIGI_RECO_12_1_dxr.root',
       'file:dcap:///pnfs/cmsaf.mit.edu/t2bat/cms/store/user/davidlw/Hydjet_Quenched_MinBias_2760GeV_STARTUP39V2_GEN_SIM_RAWDEBUG_390/Hydjet_Quenched_MinBias_2760GeV_STARTUP39V2_GEN_SIM_RECODEBUG_390/e91272bc2b91d5f6eefc8e1f2c112a67/hiReco_RAW2DIGI_RECO_11_1_PWY.root',
       'file:dcap:///pnfs/cmsaf.mit.edu/t2bat/cms/store/user/davidlw/Hydjet_Quenched_MinBias_2760GeV_STARTUP39V2_GEN_SIM_RAWDEBUG_390/Hydjet_Quenched_MinBias_2760GeV_STARTUP39V2_GEN_SIM_RECODEBUG_390/e91272bc2b91d5f6eefc8e1f2c112a67/hiReco_RAW2DIGI_RECO_10_1_c6n.root'
    )
)

# GLOBAL TAG
process.GlobalTag.globaltag = 'START39_V2::All'

# CENTRALITY
process.GlobalTag.toGet = cms.VPSet(
    cms.PSet(record = cms.string("HeavyIonRcd"),
             tag = cms.string("CentralityTable_HFhits40_Hydjet2760GeV_v0_mc"),
             connect = cms.untracked.string("frontier://FrontierPrep/CMS_COND_PHYSICSTOOLS")
    )
)

################################
#
#  ANALYZER
#
################################

process.analyzer = cms.EDAnalyzer("HI_simple",
    src = cms.InputTag("siPixelRecHits"),
    file = cms.string('test_new.root'),
    simulateTriggers = cms.bool( False ),
    hasL1Triggers = cms.bool( True ),
    produceVertexLocally = cms.bool( False ),
    vertexColl = cms.InputTag("hiSelectedVertex")
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

#valahogymixel = cms.Sequence(process.g4SimHits)
valahogymixel = cms.Sequence(cms.SequencePlaceholder("randomEngineStateProducer")*process.LHCTransport*process.g4SimHits)
#anyad = cms.Sequence(cms.SequencePlaceholder("randomEngineStateProducer")*cms.SequencePlaceholder("mix")*process.simSiPixelDigis)
anyad = cms.Sequence(cms.SequencePlaceholder("randomEngineStateProducer")*cms.SequencePlaceholder("mix"))


process.all = cms.Path(
#                       process.mix # CrossingFrame not found?? It should produce it...
                      valahogymixel
                      *anyad
#                      anyad
                      *process.siPixelRecHits
#                      process.siPixelRecHits
#                      process.analyzer # siPixelRecHits is needed
                      +process.analyzer
                      )
