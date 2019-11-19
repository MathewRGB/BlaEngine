#ifndef MOVEGENERATOR_H_
#define MOVEGENERATOR_H_

#include <vector>

#include "game_state.h"

using namespace std;

namespace blaengine::calculation {

class MoveGenerator {
 public:
  MoveGenerator();
  ~MoveGenerator();

  void startSearching(GameState game_state);

  void stopSearching();

  vector<Move> getPawnMoves(GameState game_state, ushort field_index);

  vector<Move> getRookMoves(GameState game_state, ushort field_index);

  vector<Move> getKnightMoves(GameState game_state, ushort field_index);

  vector<Move> getBishopMoves(GameState game_state, ushort field_index);    

  vector<Move> getQueenMoves(GameState game_state, ushort field_index); 

  vector<Move> getKingMoves(GameState game_state, ushort field_index); 

  Move bestMove;

};

}  // namespace blaengine::calculation

#endif  // MOVEGENERATOR_H_
