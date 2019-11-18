#ifndef GAMESTATECONTROLLER_H_
#define GAMESTATECONTROLLER_H_

#include <iostream>
#include <string>
#include <vector>

#define FEN_POS_SEPARATOR '/'
#define FIELD_NUMBER 64
#define CASTLING_NUMBER 4

using namespace std;

namespace blaengine::calculation {

struct Board {
  char fields[FIELD_NUMBER]{0};
  char castling[CASTLING_NUMBER]{0};
};

enum Piece : char {
  white_king = 'K',
  black_king = 'k',
  white_queen = 'Q',
  black_queen = 'q',
  white_rook = 'R',
  black_rook = 'r',
  white_bishop = 'B',
  black_bishop = 'b',
  white_knight = 'N',
  black_knight = 'n',
  white_pawn = 'P',
  black_pawn = 'p',
  left_piece = 0
};

enum class NextTurn : ushort { white, black };

struct GameState {
  Board board;
  NextTurn next_turn;
  short en_passant_field;
  ushort next_half_move;
  ushort half_moves_for_draw;
};

class GameStateController {
 public:
  GameStateController();
  ~GameStateController();

  GameState current_game_state;

  void extractFenPosition(string fen_position);

  void makeMove(ushort field_before, ushort field_after,
                Piece piece_got = Piece::left_piece);

  void extractFenCastling(string fen_castling);

  ushort getFieldIndex(string field);

  Piece transformPiece(string move);

  void changeMovesForDraw(Piece moving_piece, ushort field_after);

  void checkAndPerformCastling(ushort field_before, ushort field_after,
                               Piece moving_piece);

  void checkAndPerformEnPassant(ushort field_before, ushort field_after,
                                Piece moving_piece);

  void checkAndTransformPiece(ushort field_after, Piece piece_got);

  ushort getMappedFieldIndex(ushort field_index);
};

}  // namespace blaengine::calculation

#endif  // GAMESTATECONTROLLER_H_
