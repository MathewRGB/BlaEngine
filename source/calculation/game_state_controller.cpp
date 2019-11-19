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
  auto fields = this->current_game_state.board.fields;

  for (uint fen_idx = 0; fen_idx < fen_position.length(); fen_idx++) {
    if (fen_position[fen_idx] == FEN_POS_SEPARATOR) {
      continue;
    } else if (isdigit(fen_position[fen_idx])) {
      field_idx += fen_position[fen_idx] - '0';
      continue;
    } else {
      ushort mapped_field_idx = this->getMappedFieldIndex(field_idx);
      fields[mapped_field_idx] = fen_position[fen_idx];
      field_idx++;
    }
  }
}

void GameStateController::makeMove(ushort field_before, ushort field_after,
                                   Piece piece_change) {
  Piece moving_piece =
      (Piece)this->current_game_state.board.fields[field_before];

  this->changeMovesForDraw(moving_piece, field_after);

  this->current_game_state.board.fields[field_after] = moving_piece;
  this->current_game_state.board.fields[field_before] = Piece::left_piece;

  this->checkAndPerformCastling(field_before, field_after, (Piece)moving_piece);
  this->checkAndPerformEnPassant(field_before, field_after, moving_piece);
  this->checkAndTransformPiece(field_after, piece_change);
}

ushort GameStateController::getFieldIndex(string field) {
  ushort line_index = field[0] - 'a';
  ushort row_index = field[1] - '1';

  return row_index * 8 + line_index;
}

Piece GameStateController::transformPiece(string move) {
  Piece piece_got =
      (move.length() == 5) ? (Piece)(move.at(4)) : Piece::left_piece;
  if (piece_got == Piece::black_queen &&
      this->current_game_state.next_turn == NextTurn::white) {
    piece_got = Piece::white_queen;
  }
  if (piece_got == Piece::black_knight &&
      this->current_game_state.next_turn == NextTurn::white) {
    piece_got = Piece::white_knight;
  }
  if (piece_got == Piece::black_rook &&
      this->current_game_state.next_turn == NextTurn::white) {
    piece_got = Piece::white_rook;
  }
  if (piece_got == Piece::black_bishop &&
      this->current_game_state.next_turn == NextTurn::white) {
    piece_got = Piece::white_bishop;
  }

  return piece_got;
}

void GameStateController::changeMovesForDraw(Piece moving_piece,
                                             ushort field_after) {
  if (moving_piece != Piece::black_pawn && moving_piece != Piece::white_pawn &&
      this->current_game_state.board.fields[field_after] == Piece::left_piece) {
    this->current_game_state.half_moves_for_draw++;
  } else {
    this->current_game_state.half_moves_for_draw = 0;
  }
}

void GameStateController::checkAndPerformCastling(ushort field_before,
                                                  ushort field_after,
                                                  Piece moving_piece) {
  bool castling = (moving_piece == Piece::black_king ||
                   moving_piece == Piece::white_king) &&
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
  if (castling && moving_piece == Piece::white_king) {
    this->current_game_state.board.castling[0] = Piece::left_piece;
    this->current_game_state.board.castling[1] = Piece::left_piece;
  }
  if (castling && moving_piece == Piece::black_king) {
    this->current_game_state.board.castling[2] = Piece::left_piece;
    this->current_game_state.board.castling[3] = Piece::left_piece;
  }
}

void GameStateController::checkAndPerformEnPassant(ushort field_before,
                                                   ushort field_after,
                                                   Piece moving_piece) {
  auto fields = this->current_game_state.board.fields;
  ushort& en_passant_field = (ushort&)this->current_game_state.en_passant_field;
  bool en_passant = (moving_piece == Piece::black_pawn ||
                     moving_piece == Piece::white_pawn) &&
                    std::abs(field_before - field_after) == 16;

  if ((moving_piece == Piece::black_pawn ||
       moving_piece == Piece::white_pawn) &&
      field_after == en_passant_field && (field_after - field_before) > 0) {
    fields[field_after - 8] = Piece::left_piece;
  }
  if ((moving_piece == Piece::black_pawn ||
       moving_piece == Piece::white_pawn) &&
      field_after == en_passant_field && (field_after - field_before) < 0) {
    fields[field_after + 8] = Piece::left_piece;
  }
  if (en_passant && (field_after - field_before) > 0) {
    en_passant_field = field_after - 8;
  }
  if (en_passant && (field_after - field_before) < 0) {
    en_passant_field = field_after + 8;
  }
  if (!en_passant) {
    en_passant_field = -1;
  }
}

void GameStateController::checkAndTransformPiece(ushort field_after,
                                                 Piece piece_change) {
  if (piece_change != Piece::left_piece) {
    this->current_game_state.board.fields[field_after] = piece_change;
  }
}

ushort GameStateController::getMappedFieldIndex(ushort field_index) {
  return (FIELD_NUMBER - (ushort)(field_index / 8 + 1) * 8) + field_index % 8;
}

}  // namespace blaengine::calculation