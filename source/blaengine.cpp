#include "blaengine.h"

namespace blaengine {

BlaEngine::BlaEngine() {
  
}

BlaEngine::~BlaEngine() {
}

void BlaEngine::startEngine() {}

void BlaEngine::shutdownEngine() {
  this->~BlaEngine();
}

BlaEngineInfo BlaEngine::getEngineInfo() { 
  return BlaEngineInfo(); 
}

}  // namespace blaengine