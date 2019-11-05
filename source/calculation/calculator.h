#ifndef CALCULATOR_H_
#define CALCULATOR_H_

#include <iostream>
#include <string>

using namespace std;

namespace blaengine::calculation {

struct Board {
  char fields[64];
  char casteling[4];
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
  black_pawn = 'p'
};

enum NextTurn { 
  white = 0,
  black = 1
};

struct GameState {
  Board board;
  NextTurn next_turn;
  ushort white_half_moves;
  ushort black_half_moves;
};

class Calculator {
 public:
  Calculator();

 private:
  GameState current_game_state;
};

}  // namespace blaengine::calculation

#endif  // CALCULATOR_H_
