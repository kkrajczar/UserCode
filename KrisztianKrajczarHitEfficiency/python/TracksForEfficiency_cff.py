import FWCore.ParameterSet.Config as cms

from UserCode.KrisztianKrajczarHitEfficiency.common_cff import *
from UserCode.KrisztianKrajczarHitEfficiency.forHitEfficiency_triplets_cff import *
from UserCode.KrisztianKrajczarHitEfficiency.forHitEfficiency_pairs_cff import *

###################################
triplets  = cms.Sequence(pixel3ProtoTracks
                        * pixel3Vertices
                        * pixel3tracks)

###################################
pairs  = cms.Sequence(pixel3ProtoTracks
                        * pixel3Vertices
                        * pixel2tracks)

###################################
# run
minBiasTracking_hitEff = cms.Sequence(
                                     triplets
                                     *pairs)

