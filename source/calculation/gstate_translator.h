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
  static GameState interpretAndSetFen(string fen);

  static GameState makeMovesFromFieldStrings(GameState game_state,
                                             vector<string> moves);

  static void validateFenString(string fen);

  static void validateMoveString(string move);
};

}  // namespace blaengine::calculation

#endif  // GAME_STATE_TRANSLATOR_H_
