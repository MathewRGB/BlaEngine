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

void BlaEngine::interpretAndSetFen(string fen){
  this->engine_calculator.interpretAndSetFen(fen);
}

void BlaEngine::makeMovesFromFieldStrings(vector<string> moves){
  this->engine_calculator.makeMovesFromFieldStrings(moves);
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