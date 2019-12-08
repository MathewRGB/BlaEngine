#ifndef BLAENGINE_EVALUATOR_H_
#define BLAENGINE_EVALUATOR_H_

#include "source/calculation/gstate_translator.h"

using namespace std;

namespace blaengine::calculation {

class Evaluator {
 public:
  ushort searching_depth = 2;

  void startSearching(GameState game_state);

  int evaluateGameState(GameState game_state,
                        vector<Move> possible_moves = vector<Move>());

  int evaluateByPieceValues(GameState game_state,
                            vector<Move> possible_moves = vector<Move>());

  int getRandomValue(int range);

  int miniMax(GameState game_state, ushort depth);

  Move bestMove;
};

}  // namespace blaengine::calculation

#endif  // BLAENGINE_EVALUATOR_H_
