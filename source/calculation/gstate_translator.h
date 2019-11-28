#ifndef GAME_STATE_TRANSLATOR_H_
#define GAME_STATE_TRANSLATOR_H_

#include "gstate_controller.h"

#define WHITE_SPACE " "
#define DEFAULT_HYPHEN "-"
#define W_FOR_WHITE 'w'

using namespace std;

namespace blaengine::calculation {

class GSateTranslator {
 public:
  GSateTranslator();
  ~GSateTranslator();

  void interpretAndSetFen(string fen);

  void makeMovesFromFieldStrings(vector<string> moves);

  GameStateController game_state_controller;

  void validateFenString(string fen);

  void validateMoveString(string move);
};

}  // namespace blaengine::calculation

#endif  // GAME_STATE_TRANSLATOR_H_
