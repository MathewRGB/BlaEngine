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

  vector<Move> getAllMightPossibleMoves(GameState game_state);

  vector<Move> getPawnMoves(GameState game_state, ushort field_index);

  vector<Move> getRookMoves(GameState game_state, ushort field_index);

  vector<Move> getKnightMoves(GameState game_state, ushort field_index);

  vector<Move> getBishopMoves(GameState game_state, ushort field_index);

  vector<Move> getQueenMoves(GameState game_state, ushort field_index);

  vector<Move> getKingMoves(GameState game_state, ushort field_index);

  Move bestMove;

 private:
  short moveForward(short field_index, short number);

  short moveBackward(short field_index, short number);

  short moveRight(short field_index, short number);

  short moveLeft(short field_index, short number);

  bool isWhite(Piece piece);

  Color getPieceColor(Piece piece);

  Move chooseBestMove(vector<Move> moves);
};

}  // namespace blaengine::calculation

#endif  // MOVEGENERATOR_H_
