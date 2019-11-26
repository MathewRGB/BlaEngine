#ifndef MOVEGENERATOR_H_
#define MOVEGENERATOR_H_

#include <vector>

#include "game_state.h"

using namespace std;

namespace blaengine::calculation {

class MoveGenerator {
 public:
  static vector<Move> getAllMightPossibleMoves(GameState game_state);

  static vector<Move> getPawnMoves(GameState game_state, ushort field_index);

  static vector<Move> getRookMoves(GameState game_state, ushort field_index);

  static vector<Move> getKnightMoves(GameState game_state, ushort field_index);

  static vector<Move> getBishopMoves(GameState game_state, ushort field_index);

  static vector<Move> getQueenMoves(GameState game_state, ushort field_index);

  static vector<Move> getKingMoves(GameState game_state, ushort field_index);

  static short moveForward(short field_index, short number);

  static short moveBackward(short field_index, short number);

  static short moveRight(short field_index, short number);

  static short moveLeft(short field_index, short number);

  static bool isWhite(Piece piece);

  static Color getPieceColor(Piece piece);
};

}  // namespace blaengine::calculation

#endif  // MOVEGENERATOR_H_
