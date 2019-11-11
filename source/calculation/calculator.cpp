#include "calculator.h"

namespace blaengine::calculation {

Calculator::Calculator() {
  current_game_state = GameState();
  current_game_state.board = Board();
  current_game_state.next_turn = NextTurn::white;
  current_game_state.half_moves = 0;
  current_game_state.half_moves_40_move_rule = 0;
}

void Calculator::setCurrentGameState(string fen, vector<string> moves) {
  this->interpretAndSetFen(fen);
  this->makeMovesFromFieldStrings(moves);
}

void Calculator::interpretAndSetFen(string fen) {
  // TODO fen validator needed
  int fen_idx = 0;
  int field_idx = 0;

  for (; fen_idx < FIELD_NUMBER; fen_idx++, field_idx++) {
    if (fen[fen_idx] == '/') {
      field_idx--;
      continue;
    } else if (isdigit(fen[fen_idx])) {
      field_idx += fen[fen_idx] - '1';
      continue;
    }
    this->current_game_state.board.fields[field_idx] = fen[fen_idx];
  }
}

void Calculator::makeMovesFromFieldStrings(vector<string> moves) {
  // TODO validator needed
  for (uint i = 0; i < moves.size(); i++) {
    ushort field_before = this->getFieldIndex(moves[i].substr(0, 2));
    ushort field_after = this->getFieldIndex(moves[i].substr(2, 3));
    char piece_to_move = this->current_game_state.board.fields[field_before];

    this->current_game_state.board.fields[field_after] = piece_to_move;
    this->current_game_state.board.fields[field_before] = Pieces::left_piece;
  }
}

ushort Calculator::getFieldIndex(string field) {
  ushort line_index = field[0] - 'a';
  ushort row_index = field[1] - '1';

  return row_index * 8 + line_index;
}

}  // namespace blaengine::calculation