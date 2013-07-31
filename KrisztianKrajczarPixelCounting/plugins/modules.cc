#include "FWCore/PluginManager/interface/ModuleDef.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/Framework/interface/ModuleFactory.h"
#include "FWCore/Framework/interface/ESProducer.h"

#include "VertexProducerClusterCounting.h"
DEFINE_FWK_MODULE(VertexProducerClusterCounting);

#include "ChargedMultiplicityAnalyzer_new.h"
DEFINE_FWK_MODULE(ChargedMultiplicityAnalyzer_new);

#include "ChargedMultiplicityAnalyzerNoSimInfo_new.h"
DEFINE_FWK_MODULE(ChargedMultiplicityAnalyzerNoSimInfo_new);

#include "HIChargedMultiplicityAnalyzer_new.h"
DEFINE_FWK_MODULE(HIChargedMultiplicityAnalyzer_new);

#include "HITriggerAnalyzer.h"
DEFINE_FWK_MODULE(HITriggerAnalyzer);
