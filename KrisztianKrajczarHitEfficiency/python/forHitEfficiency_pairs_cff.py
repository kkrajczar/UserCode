import FWCore.ParameterSet.Config as cms

from RecoTracker.TkSeedingLayers.PixelLayerTriplets_cfi import *
import RecoPixelVertexing.PixelLowPtUtilities.AllPixelTracks_cfi

############################
# Pixel-3 proto tracks
pixel3ProtoTracks = RecoPixelVertexing.PixelLowPtUtilities.AllPixelTracks_cfi.allPixelTracks.clone()
pixel3ProtoTracks.passLabel = 'Pixel triplet tracks for vertexing'
pixel3ProtoTracks.RegionFactoryPSet.ptMin = cms.double(0.2)

############################
# Pixel vertexing
 
import UserCode.FerencSiklerVertexing.NewVertexProducer_cfi
pixel3Vertices = UserCode.FerencSiklerVertexing.NewVertexProducer_cfi.newVertices.clone()
pixel3Vertices.TrackCollection = 'pixel3ProtoTracks'
 
############################
# Pixel-2 layers

from UserCode.KrisztianKrajczarHitEfficiency.common_cff import BPixError
from UserCode.KrisztianKrajczarHitEfficiency.common_cff import FPixError
pixellayerpairs = cms.ESProducer("SeedingLayersESProducer",
    ComponentName = cms.string('PixelLayerPairs_hitEff'),
    layerList = cms.vstring(
        'BPix1+BPix2'
#        'BPix1+BPix3'
#        'BPix2+BPix3'
#        'BPix1+FPix1_pos',
#        'BPix1+FPix1_neg',
#        'BPix1+FPix2_pos',
#        'BPix1+FPix2_neg',
#        'BPix2+FPix1_pos',
#        'BPix2+FPix1_neg',
#        'BPix2+FPix1_neg',
#        'BPix2+FPix2_pos',
#        'BPix2+FPix2_neg'),
#	'FPix1_pos+FPix2_pos',
#	'FPix1_neg+FPix2_neg'),
    ),
    BPix = cms.PSet(
        BPixError,
        TTRHBuilder = cms.string('TTRHBuilderWithoutAngle4PixelTriplets'),
        HitProducer = cms.string('siPixelRecHits')
    ),
    FPix = cms.PSet(
        FPixError,
        TTRHBuilder = cms.string('TTRHBuilderWithoutAngle4PixelTriplets'),
        HitProducer = cms.string('siPixelRecHits')
    )
)

#################################
# Pixel-2 tracks
import RecoPixelVertexing.PixelLowPtUtilities.AllPixelTracks_cfi
pixel2tracks = RecoPixelVertexing.PixelLowPtUtilities.AllPixelTracks_cfi.allPixelTracks.clone()
pixel2tracks.passLabel = 'Pixel pair tracks with vertex constraint'
pixel2tracks.RegionFactoryPSet.RegionPSet.originRadius = 0.2
pixel2tracks.FilterPSet.ptMin = cms.double(0.2)
pixel2tracks.RegionFactoryPSet.RegionPSet.useFoundVertices = True
pixel2tracks.OrderedHitsFactoryPSet.ComponentName = 'StandardHitPairGenerator'
pixel2tracks.OrderedHitsFactoryPSet.SeedingLayers = 'PixelLayerPairs_hitEff'
pixel2tracks.OrderedHitsFactoryPSet.GeneratorPSet.ComponentName = 'StandardHitPairGenerator'

