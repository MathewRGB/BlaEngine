#ifndef GAMESTATE_H_
#define GAMESTATE_H_

#include <iostream>

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

enum class Color : ushort { white, black, none };

struct GameState {
  Board board;
  Color next_turn = Color::white;
  short en_passant_field = -1;
  ushort next_half_move = 1;
  ushort half_moves_for_draw = 0;
};

struct Move {
  ushort field_before;
  ushort field_after;
  Piece promotion;

  bool operator==(const Move& _move) {
    return field_before == _move.field_before &&
           field_after == _move.field_after && promotion == _move.promotion;
  }

  string toString() {
    string response = {
        (char)('a' + (field_before % 8)), (char)('1' + (field_before / 8)),
        (char)('a' + (field_after % 8)), (char)('1' + (field_after / 8))};

    if (promotion != Piece::left_piece) {
      response += promotion;
    }
    return response;
  }
};

}  // namespace blaengine::calculation

#endif  // GAMESTATE_H_
