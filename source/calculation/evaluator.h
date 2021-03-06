#ifndef BLAENGINE_EVALUATOR_H_
#define BLAENGINE_EVALUATOR_H_

#include "source/calculation/gstate_translator.h"

#define MINIMUM_DEPTH 2

using namespace std;

namespace blaengine::calculation {

class Evaluator {
 public:
  Evaluator(ushort max_depth = MINIMUM_DEPTH);

  ushort searching_depth;

  void startSearching(GameState game_state);

  int evaluateGameState(GameState game_state,
                        vector<Move> possible_moves = vector<Move>());

  int evaluateByPieceValues(GameState game_state,
                            vector<Move> possible_moves = vector<Move>());

  int getRandomValue(int range);

  int negamaxAndAlphaBeta(GameState game_state, ushort depth,
                          int alpha = -INT32_MAX, int beta = INT32_MAX);

  Move bestMove;
};

}  // namespace blaengine::calculation

#endif  // BLAENGINE_EVALUATOR_H_
