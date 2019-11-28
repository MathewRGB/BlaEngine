#ifndef BLAENGINE_EVALUATOR_H_
#define BLAENGINE_EVALUATOR_H_

#include "source/calculation/gstate_translator.h"

using namespace std;

namespace blaengine::calculation {

class Evaluator {
 public:
  Evaluator();
  ~Evaluator();

  void startSearching(GameState game_state);

  Move chooseBestMove(vector<Move> moves);

  Move bestMove;
};

}  // namespace blaengine::calculation

#endif  // BLAENGINE_EVALUATOR_H_
