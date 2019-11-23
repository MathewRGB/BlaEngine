#include "move_generator.h"

namespace blaengine::calculation {

MoveGenerator::MoveGenerator() {}
MoveGenerator::~MoveGenerator() {}

void MoveGenerator::startSearching(GameState game_state) {
  auto possible_moves = vector<Move>();

  for (int i = 0; i < FIELD_NUMBER; i++) {
    auto current_piece = game_state.board.fields[i];
    if ((current_piece == Piece::black_pawn ||
         current_piece == Piece::white_pawn) &&
        isWhite((Piece)current_piece) ==
            (game_state.next_turn == NextTurn::white)) {
      auto pawn_moves = this->getPawnMoves(game_state, i);
      possible_moves.insert(possible_moves.end(), pawn_moves.begin(),
                            pawn_moves.end());
    }
  }

  this->bestMove = possible_moves[0];
}

void MoveGenerator::stopSearching() {}

short MoveGenerator::moveForward(short field_index, short number) {
  return field_index + 8 * number;
}

short MoveGenerator::moveBackward(short field_index, short number) {
  return field_index - 8 * number;
}

short MoveGenerator::moveRight(short field_index, short number) {
  return field_index + number;
}

short MoveGenerator::moveLeft(short field_index, short number) {
  return field_index - number;
}

bool MoveGenerator::isWhite(Piece piece) {
  return (piece > 'A' && piece < 'Z');
}

vector<Move> MoveGenerator::getPawnMoves(GameState game_state,
                                         ushort field_index) {
  auto all_moves = vector<Move>();
  auto piece = (Piece)game_state.board.fields[field_index];
  bool is_white = (piece == Piece::white_pawn) ? true : false;
  short piece_direction = is_white ? 1 : -1;

  auto f_field = moveForward(field_index, 1 * piece_direction);
  auto ff_field = moveForward(field_index, 2 * piece_direction);
  auto fr_field = moveRight(f_field, 1 * piece_direction);
  auto fl_field = moveLeft(f_field, 1 * piece_direction);

  auto f_piece = (Piece)game_state.board.fields[f_field];
  auto ff_piece = (Piece)game_state.board.fields[ff_field];
  auto fr_piece = (Piece)game_state.board.fields[fr_field];
  auto fl_piece = (Piece)game_state.board.fields[fl_field];

  auto promo_bishop = is_white ? Piece::white_bishop : Piece::black_bishop;
  auto promo_queen = is_white ? Piece::white_queen : Piece::black_queen;
  auto promo_knight = is_white ? Piece::white_knight : Piece::black_knight;
  auto promo_rook = is_white ? Piece::white_rook : Piece::black_rook;

  if (f_piece == Piece::left_piece) {
    if (f_field < (short)(36 + 28 * piece_direction) &&
        f_field > (short)(27 + 28 * piece_direction)) {
      all_moves.push_back({field_index, (ushort)f_field, promo_bishop});
      all_moves.push_back({field_index, (ushort)f_field, promo_knight});
      all_moves.push_back({field_index, (ushort)f_field, promo_queen});
      all_moves.push_back({field_index, (ushort)f_field, promo_rook});
    } else {
      all_moves.push_back({field_index, (ushort)f_field, Piece::left_piece});
    }
    if (ff_piece == Piece::left_piece &&
        field_index > (27 - 20 * piece_direction) &&
        field_index < (36 - 20 * piece_direction)) {
      all_moves.push_back({field_index, (ushort)ff_field, Piece::left_piece});
    }
  }
  if ((is_white && (field_index + 1) % 8 != 0 && !isWhite(fr_piece)) ||
      (!is_white && field_index % 8 != 0 && isWhite(fr_piece))) {
    if (fr_field < (short)(36 + 28 * piece_direction) &&
        fr_field > (short)(27 + 28 * piece_direction)) {
      all_moves.push_back({field_index, (ushort)fr_field, promo_bishop});
      all_moves.push_back({field_index, (ushort)fr_field, promo_knight});
      all_moves.push_back({field_index, (ushort)fr_field, promo_queen});
      all_moves.push_back({field_index, (ushort)fr_field, promo_rook});
    } else {
      all_moves.push_back({field_index, (ushort)fr_field, Piece::left_piece});
    }
  }
  if ((is_white && field_index % 8 != 0 && !isWhite(fl_piece)) ||
      (!is_white && (field_index + 1) % 8 != 0 && isWhite(fl_piece))) {
    if (fl_field < (short)(36 + 28 * piece_direction) &&
        fl_field > (short)(27 + 28 * piece_direction)) {
      all_moves.push_back({field_index, (ushort)fl_field, promo_bishop});
      all_moves.push_back({field_index, (ushort)fl_field, promo_knight});
      all_moves.push_back({field_index, (ushort)fl_field, promo_queen});
      all_moves.push_back({field_index, (ushort)fl_field, promo_rook});
    } else {
      all_moves.push_back({field_index, (ushort)fl_field, Piece::left_piece});
    }
  }

  return all_moves;
}

}  // namespace blaengine::calculation
