import FWCore.ParameterSet.Config as cms

from RecoTracker.TkSeedingLayers.PixelLayerTriplets_cfi import *
import RecoPixelVertexing.PixelLowPtUtilities.AllPixelTracks_cfi

############################
# Pixel-3 proto tracks
pixel3ProtoTracks = RecoPixelVertexing.PixelLowPtUtilities.AllPixelTracks_cfi.allPixelTracks.clone()
pixel3ProtoTracks.passLabel = 'Pixel triplet tracks for vertexing'
pixel3ProtoTracks.RegionFactoryPSet.ptMin = cms.double(0.2)

############################
# Vertexing
#import UserCode.FerencSiklerVertexing.NewVertexProducer_cfi
#pixel3Vertices = UserCode.FerencSiklerVertexing.NewVertexProducer_cfi.newVertices.clone()
#pixel3Vertices.TrackCollection = 'pixel3ProtoTracks'

# INACTIVATE 
#dNdpTVertexing = cms.Sequence(pixel3ProtoTracks
#                             * pixel3Vertices)

