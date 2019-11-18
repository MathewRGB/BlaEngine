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
  char moving_piece = this->current_game_state.board.fields[field_before];

  this->changeMovesForDraw((Pieces)moving_piece, field_after);

  this->current_game_state.board.fields[field_after] = moving_piece;
  this->current_game_state.board.fields[field_before] = Pieces::left_piece;

  this->checkAndPerformCastling(field_before, field_after,
                                (Pieces)moving_piece);

  this->checkAndPerformEnPassant(field_before, field_after,
                                 (Pieces)moving_piece);

  this->checkAndTransformPiece(field_after, piece_got);
}

Pieces GameStateController::transformPiece(string move) {
  Pieces piece_got =
      (move.length() == 5) ? (Pieces)(move.at(4)) : Pieces::left_piece;
  if (piece_got == Pieces::black_queen &&
      this->current_game_state.next_turn == NextTurn::white) {
    piece_got = Pieces::white_queen;
  }
  if (piece_got == Pieces::black_knight &&
      this->current_game_state.next_turn == NextTurn::white) {
    piece_got = Pieces::white_knight;
  }
  if (piece_got == Pieces::black_rook &&
      this->current_game_state.next_turn == NextTurn::white) {
    piece_got = Pieces::white_rook;
  }
  if (piece_got == Pieces::black_bishop &&
      this->current_game_state.next_turn == NextTurn::white) {
    piece_got = Pieces::white_bishop;
  }

  return piece_got;
}

void GameStateController::changeMovesForDraw(Pieces moving_piece,
                                             ushort field_after) {
  if (moving_piece != Pieces::black_pawn &&
      moving_piece != Pieces::white_pawn &&
      this->current_game_state.board.fields[field_after] ==
          Pieces::left_piece) {
    this->current_game_state.half_moves_for_draw++;
  } else {
    this->current_game_state.half_moves_for_draw = 0;
  }
}

void GameStateController::checkAndPerformCastling(ushort field_before,
                                                  ushort field_after,
                                                  Pieces moving_piece) {
  bool castling = (moving_piece == 'k' || moving_piece == 'K') &&
                  std::abs(field_before - field_after) == 2;

  if (castling && field_after == 2) {
    this->makeMove(0, 3);
  }
  if (castling && field_after == 6) {
    this->makeMove(7, 5);
  }
  if (castling && field_after == 58) {
    this->makeMove(56, 59);
  }
  if (castling && field_after == 62) {
    this->makeMove(63, 61);
  }
  if (castling && moving_piece == 'K') {
    this->current_game_state.board.castling[0] = Pieces::left_piece;
    this->current_game_state.board.castling[1] = Pieces::left_piece;
  }
  if (castling && moving_piece == 'k') {
    this->current_game_state.board.castling[2] = Pieces::left_piece;
    this->current_game_state.board.castling[3] = Pieces::left_piece;
  }
}

void GameStateController::checkAndPerformEnPassant(ushort field_before,
                                                   ushort field_after,
                                                   Pieces moving_piece) {
  bool en_passant = (moving_piece == 'p' || moving_piece == 'P') &&
                    std::abs(field_before - field_after) == 16;
  if ((moving_piece == 'p' || moving_piece == 'P') &&
      field_after == this->current_game_state.en_passant_field &&
      (field_after - field_before) > 0) {
    this->current_game_state.board.fields[field_after - 8] = Pieces::left_piece;
  }
  if ((moving_piece == 'p' || moving_piece == 'P') &&
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
}

void GameStateController::checkAndTransformPiece(ushort field_after,
                                                 Pieces piece_got) {
  if (piece_got != Pieces::left_piece) {
    this->current_game_state.board.fields[field_after] = piece_got;
  }
}

}  // namespace blaengine::calculation