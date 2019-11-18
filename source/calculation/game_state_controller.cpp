#include "game_state_controller.h"

namespace blaengine::calculation {

GameStateController::GameStateController() {
  current_game_state = GameState();
  current_game_state.board = Board();
  current_game_state.next_turn = NextTurn::white;
  current_game_state.next_half_move = 0;
  current_game_state.half_moves_for_draw = 0;
  current_game_state.en_passant_field = -1;
}

GameStateController::~GameStateController() {}

void GameStateController::extractFenCastling(string fen_castling) {
  for (uint i = 0; i < fen_castling.size(); i++) {
    this->current_game_state.board.castling[i] = fen_castling[i];
  }
}

void GameStateController::extractFenPosition(string fen_position) {
  uint field_idx = 0;

  for (uint fen_idx = 0; fen_idx < fen_position.length(); fen_idx++) {
    if (fen_position[fen_idx] == '/') {
      continue;
    } else if (isdigit(fen_position[fen_idx])) {
      field_idx += fen_position[fen_idx] - '0';
      continue;
    } else {
      int transformed_field_idx =
          (FIELD_NUMBER - (uint)(field_idx / 8 + 1) * 8) + field_idx % 8;
      this->current_game_state.board.fields[transformed_field_idx] =
          fen_position[fen_idx];
      field_idx++;
    }
  }
}

ushort GameStateController::getFieldIndex(string field) {
  ushort line_index = field[0] - 'a';
  ushort row_index = field[1] - '1';

  return row_index * 8 + line_index;
}

void GameStateController::makeMove(ushort field_before, ushort field_after,
                          Pieces piece_got) {
  char piece_to_move = this->current_game_state.board.fields[field_before];

  // TODO function for this 40 moves rule
  if (piece_to_move != Pieces::black_pawn &&
      piece_to_move != Pieces::white_pawn &&
      this->current_game_state.board.fields[field_after] == Pieces::left_piece) {
    this->current_game_state.half_moves_for_draw++;
  } else{
    this->current_game_state.half_moves_for_draw = 0;
  }

  this->current_game_state.board.fields[field_after] = piece_to_move;
  this->current_game_state.board.fields[field_before] = Pieces::left_piece;

  // TODO function checking_castling (Rook move problem is not implemented yet!)
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
  if (rochade && piece_to_move == 'K') {
    this->current_game_state.board.castling[0] = Pieces::left_piece;
    this->current_game_state.board.castling[1] = Pieces::left_piece;
  }
  if (rochade && piece_to_move == 'k') {
    this->current_game_state.board.castling[2] = Pieces::left_piece;
    this->current_game_state.board.castling[3] = Pieces::left_piece;
  }

  // TODO function checking_for_en_passant
  bool en_passant = (piece_to_move == 'p' || piece_to_move == 'P') &&
                    std::abs(field_before - field_after) == 16;
  if ((piece_to_move == 'p' || piece_to_move == 'P') &&
      field_after == this->current_game_state.en_passant_field &&
      (field_after - field_before) > 0) {
    this->current_game_state.board.fields[field_after - 8] = Pieces::left_piece;
  }
  if ((piece_to_move == 'p' || piece_to_move == 'P') &&
      field_after == this->current_game_state.en_passant_field &&
      (field_after - field_before) < 0) {
    this->current_game_state.board.fields[field_after + 8] = Pieces::left_piece;
  }
  if (en_passant && (field_after - field_before) > 0) {
    this->current_game_state.en_passant_field = field_after - 8;
  }
  if (en_passant && (field_after - field_before) < 0) {
    this->current_game_state.en_passant_field = field_after + 8;
  }
  if (!en_passant) {
    this->current_game_state.en_passant_field = -1;
  }

  // TODO function transformation move
  if (piece_got != Pieces::left_piece) {
    this->current_game_state.board.fields[field_after] = piece_got;
  }
}

}  // namespace blaengine::calculation