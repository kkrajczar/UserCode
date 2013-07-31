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
# Pixel-3 tracks
import RecoPixelVertexing.PixelLowPtUtilities.AllPixelTracks_cfi

from UserCode.KrisztianKrajczarHitEfficiency.forHitEfficiencyTripletLayers_cfi import *

pixel3tracks = RecoPixelVertexing.PixelLowPtUtilities.AllPixelTracks_cfi.allPixelTracks.clone()
pixel3tracks.passLabel = 'Pixel triplet tracks with vertex constraint'
pixel3tracks.RegionFactoryPSet.RegionPSet.originRadius = 0.2
pixel3tracks.FilterPSet.ptMin = cms.double(0.2)
pixel3tracks.RegionFactoryPSet.RegionPSet.useFoundVertices = True
pixel3tracks.OrderedHitsFactoryPSet.ComponentName = 'StandardHitTripletGenerator'
pixel3tracks.OrderedHitsFactoryPSet.SeedingLayers = 'PixelLayerTriplets_KK'
pixel3tracks.OrderedHitsFactoryPSet.GeneratorPSet.ComponentName = 'PixelTripletLowPtGenerator'

