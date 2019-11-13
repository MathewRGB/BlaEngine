#ifndef CALCULATOR_H_
#define CALCULATOR_H_

#include <iostream>
#include <string>
#include <vector>

#define FIELD_NUMBER 64
#define CASTLING_NUMBER 4

using namespace std;

namespace blaengine::calculation {

struct Board {
  char fields[FIELD_NUMBER] = {'0'};
  char castling[CASTLING_NUMBER] = {'0'};
};

enum Pieces : char {
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
  left_piece = '0'
};

enum class NextTurn : ushort { white, black };

struct GameState {
  Board board;
  NextTurn next_turn;
  short en_passant_field;
  ushort next_half_move;
  ushort half_moves_40_move_rule;
};

class Calculator {
 public:
  Calculator();
  ~Calculator();

  void interpretAndSetFen(string fen);

  void makeMovesFromFieldStrings(vector<string> moves);
  GameState current_game_state;

  private:

    void extractFenPosition(string fen_position);

    void extractFenCastling(string fen_castling);


    ushort getFieldIndex(string field);

    void makeMove(ushort field_before, ushort field_after);

    void validateMoveString(string move);

    void validateFenString(string fen);
};

}  // namespace blaengine::calculation

#endif  // CALCULATOR_H_
