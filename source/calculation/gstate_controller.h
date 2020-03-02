#ifndef GAMESTATECONTROLLER_H_
#define GAMESTATECONTROLLER_H_

#include <string>
#include <vector>

#include "game_state.h"

#define FEN_POS_SEPARATOR '/'

using namespace std;

namespace blaengine::calculation {

class GameStateController {
 public:
  GameStateController();

  GameState current_game_state;

  void initializeGameSate();

  void extractFenPosition(string fen_position);

  void makeMove(Move move);

  void makeMove(ushort field_before, ushort field_after,
                Piece promotion = Piece::left_piece);

  void extractFenCastling(string fen_castling);

  void changeMovesForDraw(Piece moving_piece, ushort field_after);

  bool checkAndPerformCastling(ushort field_before, ushort field_after,
                               Piece moving_piece);

  void checkAndPerformEnPassant(ushort field_before, ushort field_after,
                                Piece moving_piece);

  void checkAndTransformPiece(ushort field_after, Piece piece_change);

  Piece transformPiece(string move);

  static ushort getFieldIndex(string field);

  static ushort getMappedFieldIndex(ushort field_index);
};

}  // namespace blaengine::calculation

#endif  // GAMESTATECONTROLLER_H_
