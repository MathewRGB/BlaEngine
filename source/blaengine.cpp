#include <random>

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
  this->startSearching(
      this->engine_calculator.game_state_controller.current_game_state);

  return this->bestMove.toString();
}

void BlaEngine::startSearching(GameState game_state) {
  auto possible_moves = MoveGenerator::getAllMightPossibleMoves(game_state);
  this->bestMove = this->chooseBestMove(possible_moves);
}

void BlaEngine::stopSearching() {}

Move BlaEngine::chooseBestMove(vector<Move> moves) {
  random_device rd;
  mt19937 gen(rd());
  uniform_int_distribution<> dist(0, moves.size() - 1);
  ushort rnd_idx = dist(gen);

  return moves[rnd_idx];
}

BlaEngineInfo BlaEngine::getEngineInfo() { return BlaEngineInfo(); }

}  // namespace blaengine