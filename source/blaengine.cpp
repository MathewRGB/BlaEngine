#include "blaengine.h"

namespace blaengine {

BlaEngine::BlaEngine() { 
  this->gstate_translator = GSateTranslator(); 
  this->evaluator = Evaluator();  
}

void BlaEngine::startEngine() {}

void BlaEngine::shutdownEngine() { this->~BlaEngine(); }

void BlaEngine::interpretAndSetFen(string fen) {
  this->gstate_translator.interpretAndSetFen(fen);
}

void BlaEngine::makeMovesFromFieldStrings(vector<string> moves) {
  this->gstate_translator.makeMovesFromFieldStrings(moves);
}

string BlaEngine::getBestMove() {
  this->evaluator.startSearching(
      this->gstate_translator.gstate_controller.current_game_state);

  return this->evaluator.bestMove.toString();
}

BlaEngineInfo BlaEngine::getEngineInfo() { return BlaEngineInfo(); }

}  // namespace blaengine