#include "blaengine.h"
#include "calculation/move_generator.h"

namespace blaengine {

int dummy_counter = 1;

BlaEngine::BlaEngine() { this->engine_calculator = Calculator(); }

BlaEngine::~BlaEngine() {}

void BlaEngine::startEngine() {}

void BlaEngine::shutdownEngine() { this->~BlaEngine(); }

void BlaEngine::interpretAndSetFen(string fen) {
  this->engine_calculator.interpretAndSetFen(fen);
}

void BlaEngine::makeMovesFromFieldStrings(vector<string> moves) {
  this->engine_calculator.makeMovesFromFieldStrings(moves);
}

string BlaEngine::getBestMove() {
  auto move_generator = MoveGenerator();
  move_generator.startSearching(
     this->engine_calculator.game_state_controller.current_game_state);

  return move_generator.bestMove.toString();
}

BlaEngineInfo BlaEngine::getEngineInfo() { return BlaEngineInfo(); }

}  // namespace blaengine