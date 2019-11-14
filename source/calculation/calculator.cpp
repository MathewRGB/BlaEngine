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
  string next_full_move = fen.substr(0, fen.find(" "));
  this->current_game_state.next_half_move += std::stoi(next_full_move)*2;
  if (this->current_game_state.next_turn == NextTurn::white){
    this->current_game_state.next_half_move--;
  }
}

void Calculator::extractFenCastling(string fen_castling) {
  for (uint i = 0; i < fen_castling.size(); i++) {
    this->current_game_state.board.castling[i] = fen_castling[i];
  }
}

void Calculator::extractFenPosition(string fen_position) {
  int field_idx = 0;

  for (int fen_idx = 0; fen_idx < fen_position.length(); fen_idx++) {
    if (fen_position[fen_idx] == '/') {
      continue;
    } else if (isdigit(fen_position[fen_idx])) {
      field_idx += fen_position[fen_idx] - '0';
      continue;
    } else {
      int transformed_field_idx =
          (FIELD_NUMBER - (int)(field_idx / 8 + 1) * 8) + field_idx % 8;
      this->current_game_state.board.fields[transformed_field_idx] =
          fen_position[fen_idx];
      field_idx++;
    }
  }
}

void Calculator::makeMovesFromFieldStrings(vector<string> moves) {
  for (uint i = 0; i < moves.size(); i++) {
    this->validateMoveString(moves[i]);
    ushort field_before = this->getFieldIndex(moves[i].substr(0, 2));
    ushort field_after = this->getFieldIndex(moves[i].substr(2, 3));
    this->makeMove(field_before, field_after);

    this->current_game_state.next_half_move++;
    this->current_game_state.next_turn =
        (this->current_game_state.next_turn == NextTurn::white)
            ? NextTurn::black
            : NextTurn::white;
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

  if (rochade && field_after == 2) {
    this->makeMove(0, 3);
  }
  if (rochade && field_after == 6) {
    this->makeMove(7, 5);
  }
  if (rochade && field_after == 58) {
    this->makeMove(56, 59);
  }
  if (rochade && field_after == 62) {
    this->makeMove(63, 61);
  }
  if (rochade && piece_to_move == 'K'){
    this->current_game_state.board.castling[0] = Pieces::left_piece;
    this->current_game_state.board.castling[1] = Pieces::left_piece;
  }
  if (rochade && piece_to_move == 'k'){
    this->current_game_state.board.castling[2] = Pieces::left_piece;
    this->current_game_state.board.castling[3] = Pieces::left_piece;
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