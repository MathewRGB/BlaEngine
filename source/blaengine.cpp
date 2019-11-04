#include "blaengine.h"

namespace blaengine {

int dummy_counter = 1;


BlaEngine::BlaEngine() {
  
}

BlaEngine::~BlaEngine() {
}

void BlaEngine::startEngine() {}

void BlaEngine::shutdownEngine() {
  this->~BlaEngine();
}

string BlaEngine::getBestMove() {
  string bestmove;
  bestmove += (char(105-dummy_counter));
  bestmove += "7";
  bestmove += (char(105-dummy_counter));
  bestmove += "6";
  dummy_counter++;

  return bestmove;
}

BlaEngineInfo BlaEngine::getEngineInfo() { 
  return BlaEngineInfo(); 
}

}  // namespace blaengine