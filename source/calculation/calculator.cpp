#include "calculator.h"

namespace blaengine::calculation {

Calculator::Calculator() {
  current_game_state = GameState();
  current_game_state.board = Board();
  current_game_state.next_turn = NextTurn::white;
  current_game_state.white_half_moves = 0;
  current_game_state.black_half_moves = 0;
}

void Calculator::setCurrentGameState(string fen_string,
                                     vector<string> pgn_moves) {
  for (int fen_idx = 0, board_idx = 0; fen_idx < FIELD_NUMBER;
       fen_idx++, board_idx++) {
    if (fen_string[fen_idx] == '/') {
      board_idx--;
      continue;
    } else if (isdigit(fen_string[fen_idx])) {
      board_idx += fen_string[fen_idx] - '0' - 1;
      continue;
    }
    current_game_state.board.fields[board_idx] = fen_string[fen_idx];
  }
}

}  // namespace blaengine::calculation