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
  char fields[FIELD_NUMBER] = {0};
  char castling[CASTLING_NUMBER] = {0};
};

enum class Pieces : char {
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
  ushort white_half_moves;
  ushort black_half_moves;
};

class Calculator {
 public:
  Calculator();

  void setCurrentGameState(string fen_string, vector<string> pgn_moves);

  GameState current_game_state;
};

}  // namespace blaengine::calculation

#endif  // CALCULATOR_H_
