#include "blaengine.h"

namespace blaengine {

BlaEngine::BlaEngine() {
  this->gstate_controller = GameStateController();
  this->evaluator = Evaluator();
}

void BlaEngine::shutdownEngine() { this->~BlaEngine(); }

void BlaEngine::interpretAndSetFen(string fen) {
  this->gstate_controller.current_game_state =
      GSateTranslator::interpretAndSetFen(fen);
}

void BlaEngine::makeMovesFromFieldStrings(vector<string> moves) {
  auto& current_gstate = this->gstate_controller.current_game_state;
  current_gstate =
      GSateTranslator::makeMovesFromFieldStrings(current_gstate, moves);
}

string BlaEngine::getBestMove() {
  auto& current_gstate = this->gstate_controller.current_game_state;
  this->evaluator.startSearching(current_gstate);

  return this->evaluator.bestMove.toString();
}

BlaEngineInfo BlaEngine::getEngineInfo() { return BlaEngineInfo(); }

}  // namespace blaengine