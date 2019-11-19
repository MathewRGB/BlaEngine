#ifndef MOVEGENERATOR_H_
#define MOVEGENERATOR_H_

#include <tuple>
#include "game_state.h"

using namespace std;

namespace blaengine::calculation {

class MoveGenerator {
 public:
  MoveGenerator();
  ~MoveGenerator();

  void startSearching();

  void stopSearching();

  tuple<ushort,ushort,Piece> bestMove;

};

}  // namespace blaengine::calculation

#endif  // MOVEGENERATOR_H_
