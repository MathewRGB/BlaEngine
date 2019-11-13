#include "calculator.h"

namespace blaengine::calculation {

Calculator::Calculator() {
  current_game_state = GameState();
  current_game_state.board = Board();
  current_game_state.next_turn = NextTurn::white;
  current_game_state.next_half_move = 0;
  current_game_state.half_moves_40_move_rule = 0;
  current_game_state.en_passant_field = -1;
}

Calculator::~Calculator() {}

void Calculator::interpretAndSetFen(string fen) {
  this->validateFenString(fen);

  string fen_position = fen.substr(0, fen.find(" "));
  this->extractFenPosition(fen_position);

  fen.erase(0, fen.find(" ") + 1);
  this->current_game_state.next_turn =
      (fen[0] == 'w') ? NextTurn::white : NextTurn::black;

  fen.erase(0, fen.find(" ") + 1);
  string castling_info = fen.substr(0, fen.find(" "));
  if (castling_info.compare("-") != 0) {
    this->extractFenCastling(castling_info);
  }

  fen.erase(0, fen.find(" ") + 1);
  string en_passant = fen.substr(0, fen.find(" "));
  if (en_passant[0] != '-') {
    this->current_game_state.en_passant_field = this->getFieldIndex(en_passant);
  }

  fen.erase(0, fen.find(" ") + 1);
  string rule_40_moves = fen.substr(0, fen.find(" "));
  this->current_game_state.half_moves_40_move_rule = std::stoi(rule_40_moves);

  fen.erase(0, fen.find(" ") + 1);
  string next_half_move = fen.substr(0, fen.find(" "));
  this->current_game_state.next_half_move = std::stoi(next_half_move);
}

void Calculator::extractFenCastling(string fen_castling) {
  for (uint i = 0; i < fen_castling.size(); i++) {
    this->current_game_state.board.castling[i] = fen_castling[i];
  }
}

void Calculator::extractFenPosition(string fen_position) {
  int fen_idx = 0;
  int field_idx = 0;

  for (; fen_idx < FIELD_NUMBER; fen_idx++, field_idx++) {
    if (fen_position[fen_idx] == '/') {
      field_idx--;
      continue;
    } else if (isdigit(fen_position[fen_idx])) {
      field_idx += fen_position[fen_idx] - '1';
      continue;
    }
    this->current_game_state.board.fields[field_idx] = fen_position[fen_idx];
  }
}

void Calculator::makeMovesFromFieldStrings(vector<string> moves) {
  for (uint i = 0; i < moves.size(); i++) {
    this->validateMoveString(moves[i]);
    ushort field_before = this->getFieldIndex(moves[i].substr(0, 2));
    ushort field_after = this->getFieldIndex(moves[i].substr(2, 3));
    this->makeMove(field_before, field_after);
  }
}

ushort Calculator::getFieldIndex(string field) {
  ushort line_index = field[0] - 'a';
  ushort row_index = field[1] - '1';

  return row_index * 8 + line_index;
}

void Calculator::makeMove(ushort field_before, ushort field_after) {
  char piece_to_move = this->current_game_state.board.fields[field_before];

  this->current_game_state.board.fields[field_after] = piece_to_move;
  this->current_game_state.board.fields[field_before] = Pieces::left_piece;

  bool rochade = (piece_to_move == 'k' || piece_to_move == 'K') &&
                 std::abs(field_before - field_after) == 2;
  if (rochade && field_after < 4) {
    this->makeMove(0, 3);
  }
  if (rochade && field_after > 4) {
    this->makeMove(7, 5);
  }
  if (rochade && field_after < 60) {
    this->makeMove(56, 59);
  }
  if (rochade && field_after > 60) {
    this->makeMove(63, 61);
  }
}

void Calculator::validateFenString(string fen) {
  if (fen.empty()) {
    throw("FEN string was not in the right format or even empty.");
  }
}

void Calculator::validateMoveString(string move) {
  if (move.empty() || move.size() < 4) {
    throw("move was in a wrong format. It has to be e.g. e2e3");
  }
}

}  // namespace blaengine::calculation