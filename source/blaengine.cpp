#include "blaengine.h"

namespace blaengine {

BlaEngine::BlaEngine() {
  this->gstate_controller = GameStateController();
  this->evaluator = Evaluator();
}

void BlaEngine::shutdownEngine() { this->~BlaEngine(); }

void BlaEngine::interpretAndSetFen(string fen) {
  auto gstate_translator = GSateTranslator();
  this->gstate_controller.current_game_state =
      gstate_translator.interpretAndSetFen(fen);
}

void BlaEngine::makeMovesFromFieldStrings(vector<string> moves) {
  auto gstate_translator = GSateTranslator();
  auto& current_gstate = this->gstate_controller.current_game_state;

  current_gstate =
      gstate_translator.makeMovesFromFieldStrings(current_gstate, moves);
}

string BlaEngine::getBestMove() {
  auto& current_gstate = this->gstate_controller.current_game_state;
  this->evaluator.startSearching(current_gstate);

  return this->evaluator.bestMove.toString();
}

BlaEngineInfo BlaEngine::getEngineInfo() { return BlaEngineInfo(); }

}  // namespace blaengine