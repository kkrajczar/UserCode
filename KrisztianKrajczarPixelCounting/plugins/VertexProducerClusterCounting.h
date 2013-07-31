#ifndef VertexProducerClusterCounting_H
#define VertexProducerClusterCounting_H

#include "FWCore/Framework/interface/EDProducer.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"

namespace edm { class Event; class EventSetup; }

class TrackerGeometry;
class VertexHit;

class VertexProducerClusterCounting : public edm::EDProducer
{
public:
  explicit VertexProducerClusterCounting(const edm::ParameterSet& ps);
  ~VertexProducerClusterCounting();
  int getContainedHits(std::vector<VertexHit> hits, float z0, float & chi);
  virtual void produce(edm::Event& ev, const edm::EventSetup& es);
 
private:
  void beginJob(const edm::EventSetup& es);

  edm::ParameterSet theConfig;
};
#endif
