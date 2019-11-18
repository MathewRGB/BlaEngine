#ifndef CALCULATOR_H_
#define CALCULATOR_H_

#include "game_state_controller.h"

using namespace std;

namespace blaengine::calculation {

class Calculator {
 public:
  Calculator();
  ~Calculator();

  void interpretAndSetFen(string fen);

  void makeMovesFromFieldStrings(vector<string> moves);

  GameStateController game_state_controller;

  void validateFenString(string fen);

  void validateMoveString(string move);
};

}  // namespace blaengine::calculation

#endif  // CALCULATOR_H_
