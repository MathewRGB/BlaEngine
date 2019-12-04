#include <random>

#include "evaluator.h"
#include "move_generator.h"

namespace blaengine::calculation {

Evaluator::Evaluator(){}
Evaluator::~Evaluator(){}

void Evaluator::startSearching(GameState game_state) {
  auto possible_moves = MoveGenerator::getAllMightPossibleMoves(game_state);
  this->bestMove = this->chooseBestMove(possible_moves);
}

int Evaluator::evaluateGameState(GameState game_state){
  return 0;
}

Move Evaluator::chooseBestMove(vector<Move> moves) {
  random_device rd;
  mt19937 gen(rd());
  uniform_int_distribution<> dist(0, moves.size() - 1);
  ushort rnd_idx = dist(gen);

  return moves[rnd_idx];
}

}  // namespace blaengine::calculation