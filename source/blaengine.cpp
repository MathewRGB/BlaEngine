#include "blaengine.h"

namespace blaengine {

int dummy_counter = 1;


BlaEngine::BlaEngine() {
  this->engine_calculator = Calculator();
}

BlaEngine::~BlaEngine() {
}

void BlaEngine::startEngine() {}

void BlaEngine::shutdownEngine() {
  this->~BlaEngine();
}

void BlaEngine::setGameState(string fen, vector<string> moves){
  this->engine_calculator.setCurrentGameState(fen, moves);
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