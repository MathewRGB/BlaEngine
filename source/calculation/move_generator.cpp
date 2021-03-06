#include "move_generator.h"

namespace blaengine::calculation {

vector<Move> MoveGenerator::getAllMightPossibleMoves(GameState game_state) {
  auto next_turn = game_state.next_turn;
  auto possible_moves = vector<Move>();

  for (int i = 0; i < FIELD_NUMBER; i++) {
    auto current_piece = game_state.board[i];
    if (isWhite((Piece)current_piece) != (next_turn == Color::white)) {
      continue;
    }

    if (current_piece == Piece::black_pawn ||
        current_piece == Piece::white_pawn) {
      auto pawn_moves = getPawnMoves(game_state, i);
      possible_moves.insert(possible_moves.end(), pawn_moves.begin(),
                            pawn_moves.end());
    }
    if (current_piece == Piece::black_knight ||
        current_piece == Piece::white_knight) {
      auto knight_moves = getKnightMoves(game_state, i);
      possible_moves.insert(possible_moves.end(), knight_moves.begin(),
                            knight_moves.end());
    }
    if (current_piece == Piece::black_rook ||
        current_piece == Piece::white_rook) {
      auto knight_moves = getRookMoves(game_state, i);
      possible_moves.insert(possible_moves.end(), knight_moves.begin(),
                            knight_moves.end());
    }
    if (current_piece == Piece::black_bishop ||
        current_piece == Piece::white_bishop) {
      auto knight_moves = getBishopMoves(game_state, i);
      possible_moves.insert(possible_moves.end(), knight_moves.begin(),
                            knight_moves.end());
    }
    if (current_piece == Piece::black_queen ||
        current_piece == Piece::white_queen) {
      auto knight_moves = getQueenMoves(game_state, i);
      possible_moves.insert(possible_moves.end(), knight_moves.begin(),
                            knight_moves.end());
    }
    if (current_piece == Piece::black_king ||
        current_piece == Piece::white_king) {
      auto knight_moves = getKingMoves(game_state, i);
      possible_moves.insert(possible_moves.end(), knight_moves.begin(),
                            knight_moves.end());
    }
  }

  return possible_moves;
}

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

Color MoveGenerator::getPieceColor(Piece piece) {
  if (piece > 'A' && piece < 'Z') {
    return Color::white;
  } else if (piece > 'a' && piece < 'z') {
    return Color::black;
  }

  return Color::none;
}

bool MoveGenerator::isCastlingSide(GameState game_state, Piece piece) {
  for (int i = 0; i < CASTLING_NUMBER; i++) {
    if (piece == (Piece)game_state.castling[i]) {
      return true;
    }
  }

  return false;
}

vector<Move> MoveGenerator::getPawnMoves(GameState game_state,
                                         ushort field_index) {
  auto all_moves = vector<Move>();
  auto piece = (Piece)game_state.board[field_index];
  bool is_white = (piece == Piece::white_pawn) ? true : false;
  short piece_direction = is_white ? 1 : -1;

  auto f_field = moveForward(field_index, 1 * piece_direction);
  auto ff_field = moveForward(field_index, 2 * piece_direction);
  auto fr_field = moveRight(f_field, 1 * piece_direction);
  auto fl_field = moveLeft(f_field, 1 * piece_direction);

  auto f_piece = (Piece)game_state.board[f_field];
  auto ff_piece = (Piece)game_state.board[ff_field];
  auto fr_piece = (Piece)game_state.board[fr_field];
  auto fl_piece = (Piece)game_state.board[fl_field];

  auto promo_bishop = is_white ? Piece::white_bishop : Piece::black_bishop;
  auto promo_queen = is_white ? Piece::white_queen : Piece::black_queen;
  auto promo_knight = is_white ? Piece::white_knight : Piece::black_knight;
  auto promo_rook = is_white ? Piece::white_rook : Piece::black_rook;

  // general moves
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
  // piece taking
  if ((is_white && (field_index + 1) % 8 != 0 && !isWhite(fr_piece) &&
       fr_piece != Piece::left_piece) ||
      (!is_white && field_index % 8 != 0 && isWhite(fr_piece) &&
       fr_piece != Piece::left_piece)) {
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
  if ((is_white && field_index % 8 != 0 && !isWhite(fl_piece) &&
       fl_piece != Piece::left_piece) ||
      (!is_white && (field_index + 1) % 8 != 0 && isWhite(fl_piece) &&
       fl_piece != Piece::left_piece)) {
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
  // en passant
  if ((is_white && (field_index + 1) % 8 != 0 &&
       fr_field == game_state.en_passant_field) ||
      (!is_white && field_index % 8 != 0 &&
       fr_field == game_state.en_passant_field)) {
    all_moves.push_back({field_index, (ushort)fr_field, Piece::left_piece});
  }
  if ((is_white && field_index % 8 != 0 &&
       fl_field == game_state.en_passant_field) ||
      (!is_white && (field_index + 1) % 8 != 0 &&
       fl_field == game_state.en_passant_field)) {
    all_moves.push_back({field_index, (ushort)fl_field, Piece::left_piece});
  }

  return all_moves;
}

vector<Move> MoveGenerator::getKnightMoves(GameState game_state,
                                           ushort field_index) {
  auto all_moves = vector<Move>();
  auto possible_moves = vector<short>();
  auto piece = (Piece)game_state.board[field_index];

  auto ff_field = moveForward(field_index, 2);
  auto bb_field = moveBackward(field_index, 2);
  auto ll_field = moveLeft(field_index, 2);
  auto rr_field = moveRight(field_index, 2);

  possible_moves.push_back(moveLeft(ff_field, 1));
  possible_moves.push_back(moveRight(ff_field, 1));
  possible_moves.push_back(moveLeft(bb_field, 1));
  possible_moves.push_back(moveRight(bb_field, 1));

  possible_moves.push_back(moveForward(ll_field, 1));
  possible_moves.push_back(moveBackward(ll_field, 1));
  possible_moves.push_back(moveForward(rr_field, 1));
  possible_moves.push_back(moveBackward(rr_field, 1));

  for (uint i = 0; i < possible_moves.size(); i++) {
    if (possible_moves[i] > 63 || possible_moves[i] < 0) {
      continue;
    }
    if ((field_index - 1) % 8 == 0 && (field_index + 6 == possible_moves[i] ||
                                       field_index - 10 == possible_moves[i])) {
      continue;
    }
    if (field_index % 8 == 0 && (field_index + 6 == possible_moves[i] ||
                                 field_index - 10 == possible_moves[i] ||
                                 field_index + 15 == possible_moves[i] ||
                                 field_index - 17 == possible_moves[i])) {
      continue;
    }
    if ((field_index + 2) % 8 == 0 && (field_index + 10 == possible_moves[i] ||
                                       field_index - 6 == possible_moves[i])) {
      continue;
    }
    if ((field_index + 1) % 8 == 0 && (field_index + 10 == possible_moves[i] ||
                                       field_index - 6 == possible_moves[i] ||
                                       field_index + 17 == possible_moves[i] ||
                                       field_index - 15 == possible_moves[i])) {
      continue;
    }

    auto taking_piece = (Piece)game_state.board[possible_moves[i]];
    if (isWhite(taking_piece) && isWhite(piece) &&
        taking_piece != Piece::left_piece) {
      continue;
    }
    if (!isWhite(taking_piece) && !isWhite(piece) &&
        taking_piece != Piece::left_piece) {
      continue;
    }

    all_moves.push_back(
        {field_index, (ushort)possible_moves[i], Piece::left_piece});
  }

  return all_moves;
}

vector<Move> MoveGenerator::getRookMoves(GameState game_state,
                                         ushort field_index) {
  auto all_moves = vector<Move>();
  auto possible_moves = vector<short>();
  auto piece = (Piece)game_state.board[field_index];
  bool piece_blocked = false;

  // right direction
  for (uint i = 1; !piece_blocked; i++) {
    auto current_field = moveRight(field_index, i);

    if (((field_index + 1) % 8 == 0) || current_field > 63 ||
        current_field % 8 == 0) {
      break;
    }

    auto current_piece = (Piece)game_state.board[current_field];
    if (isWhite(current_piece) == isWhite(piece) &&
        current_piece != Piece::left_piece) {
      break;
    }
    if (isWhite(current_piece) != isWhite(piece) &&
        current_piece != Piece::left_piece) {
      all_moves.push_back(
          {field_index, (ushort)current_field, Piece::left_piece});
      break;
    }

    all_moves.push_back(
        {field_index, (ushort)current_field, Piece::left_piece});
  }
  // left direction
  for (uint i = 1; !piece_blocked; i++) {
    auto current_field = moveLeft(field_index, i);

    if ((field_index % 8 == 0) || current_field < 0 ||
        (current_field + 1) % 8 == 0) {
      break;
    }

    auto current_piece = (Piece)game_state.board[current_field];
    if (isWhite(current_piece) == isWhite(piece) &&
        current_piece != Piece::left_piece) {
      break;
    }
    if (isWhite(current_piece) != isWhite(piece) &&
        current_piece != Piece::left_piece) {
      all_moves.push_back(
          {field_index, (ushort)current_field, Piece::left_piece});
      break;
    }

    all_moves.push_back(
        {field_index, (ushort)current_field, Piece::left_piece});
  }
  // forward direction
  for (uint i = 1; !piece_blocked; i++) {
    auto current_field = moveForward(field_index, i);

    if (current_field > 63) {
      break;
    }

    auto current_piece = (Piece)game_state.board[current_field];
    if (isWhite(current_piece) == isWhite(piece) &&
        current_piece != Piece::left_piece) {
      break;
    }
    if (isWhite(current_piece) != isWhite(piece) &&
        current_piece != Piece::left_piece) {
      all_moves.push_back(
          {field_index, (ushort)current_field, Piece::left_piece});
      break;
    }

    all_moves.push_back(
        {field_index, (ushort)current_field, Piece::left_piece});
  }
  // backward direction
  for (uint i = 1; !piece_blocked; i++) {
    auto current_field = moveBackward(field_index, i);

    if (current_field < 0) {
      break;
    }

    auto current_piece = (Piece)game_state.board[current_field];
    if (isWhite(current_piece) == isWhite(piece) &&
        current_piece != Piece::left_piece) {
      break;
    }
    if (isWhite(current_piece) != isWhite(piece) &&
        current_piece != Piece::left_piece) {
      all_moves.push_back(
          {field_index, (ushort)current_field, Piece::left_piece});
      break;
    }

    all_moves.push_back(
        {field_index, (ushort)current_field, Piece::left_piece});
  }

  return all_moves;
}

vector<Move> MoveGenerator::getBishopMoves(GameState game_state,
                                           ushort field_index) {
  auto all_moves = vector<Move>();
  auto possible_moves = vector<short>();
  auto piece = (Piece)game_state.board[field_index];
  bool piece_blocked = false;

  // right forward direction
  for (uint i = 1; !piece_blocked; i++) {
    auto r_field = moveRight(field_index, i);
    auto current_field = moveForward(r_field, i);

    if (((field_index + 1) % 8 == 0) || current_field > 63 ||
        current_field % 8 == 0) {
      break;
    }

    auto current_piece = (Piece)game_state.board[current_field];
    if (isWhite(current_piece) == isWhite(piece) &&
        current_piece != Piece::left_piece) {
      break;
    }
    if (isWhite(current_piece) != isWhite(piece) &&
        current_piece != Piece::left_piece) {
      all_moves.push_back(
          {field_index, (ushort)current_field, Piece::left_piece});
      break;
    }

    all_moves.push_back(
        {field_index, (ushort)current_field, Piece::left_piece});
  }
  // right backward direction
  for (uint i = 1; !piece_blocked; i++) {
    auto r_field = moveRight(field_index, i);
    auto current_field = moveBackward(r_field, i);

    if (((field_index + 1) % 8 == 0) || current_field < 0 ||
        current_field % 8 == 0) {
      break;
    }

    auto current_piece = (Piece)game_state.board[current_field];
    if (isWhite(current_piece) == isWhite(piece) &&
        current_piece != Piece::left_piece) {
      break;
    }
    if (isWhite(current_piece) != isWhite(piece) &&
        current_piece != Piece::left_piece) {
      all_moves.push_back(
          {field_index, (ushort)current_field, Piece::left_piece});
      break;
    }

    all_moves.push_back(
        {field_index, (ushort)current_field, Piece::left_piece});
  }
  // left forward direction
  for (uint i = 1; !piece_blocked; i++) {
    auto l_field = moveLeft(field_index, i);
    auto current_field = moveForward(l_field, i);

    if ((field_index % 8 == 0) || current_field > 63 ||
        (current_field + 1) % 8 == 0) {
      break;
    }

    auto current_piece = (Piece)game_state.board[current_field];
    if (isWhite(current_piece) == isWhite(piece) &&
        current_piece != Piece::left_piece) {
      break;
    }
    if (isWhite(current_piece) != isWhite(piece) &&
        current_piece != Piece::left_piece) {
      all_moves.push_back(
          {field_index, (ushort)current_field, Piece::left_piece});
      break;
    }

    all_moves.push_back(
        {field_index, (ushort)current_field, Piece::left_piece});
  }
  // left backward direction
  for (uint i = 1; !piece_blocked; i++) {
    auto l_field = moveLeft(field_index, i);
    auto current_field = moveBackward(l_field, i);

    if ((field_index % 8 == 0) || current_field < 0 ||
        (current_field + 1) % 8 == 0) {
      break;
    }

    auto current_piece = (Piece)game_state.board[current_field];
    if (isWhite(current_piece) == isWhite(piece) &&
        current_piece != Piece::left_piece) {
      break;
    }
    if (isWhite(current_piece) != isWhite(piece) &&
        current_piece != Piece::left_piece) {
      all_moves.push_back(
          {field_index, (ushort)current_field, Piece::left_piece});
      break;
    }

    all_moves.push_back(
        {field_index, (ushort)current_field, Piece::left_piece});
  }

  return all_moves;
}

vector<Move> MoveGenerator::getQueenMoves(GameState game_state,
                                          ushort field_index) {
  auto all_moves = getRookMoves(game_state, field_index);
  auto bishop_moves = getBishopMoves(game_state, field_index);
  all_moves.insert(end(all_moves), begin(bishop_moves), end(bishop_moves));

  return all_moves;
}

vector<Move> MoveGenerator::getKingMoves(GameState game_state,
                                         ushort field_index) {
  auto all_moves = vector<Move>();
  auto piece = (Piece)game_state.board[field_index];
  bool castling_king =
      (field_index == 4 || field_index == 60) &&
      ((Piece)game_state.board[field_index + 1] == Piece::left_piece) &&
      ((Piece)game_state.board[field_index + 2] == Piece::left_piece) &&
      (((Piece)game_state.board[field_index + 3] == Piece::black_rook &&
        piece == Piece::black_king &&
        isCastlingSide(game_state, Piece::black_king)) ||
       ((Piece)game_state.board[field_index + 3] == Piece::white_rook &&
        piece == Piece::white_king &&
        isCastlingSide(game_state, Piece::white_king)));
  bool castling_queen =
      (field_index == 4 || field_index == 60) &&
      ((Piece)game_state.board[field_index - 1] == Piece::left_piece) &&
      ((Piece)game_state.board[field_index - 2] == Piece::left_piece) &&
      ((Piece)game_state.board[field_index - 3] == Piece::left_piece) &&
      (((Piece)game_state.board[field_index - 4] == Piece::black_rook &&
        piece == Piece::black_king &&
        isCastlingSide(game_state, Piece::black_queen)) ||
       ((Piece)game_state.board[field_index - 4] == Piece::white_rook &&
        piece == Piece::white_king &&
        isCastlingSide(game_state, Piece::white_queen)));

  auto r_field = moveRight(field_index, 1);
  auto l_field = moveLeft(field_index, 1);
  auto f_field = moveForward(field_index, 1);
  auto b_field = moveBackward(field_index, 1);
  auto rf_field = moveForward(r_field, 1);
  auto lf_field = moveForward(l_field, 1);
  auto rb_field = moveBackward(r_field, 1);
  auto lb_field = moveBackward(l_field, 1);

  auto r_piece = (Piece)game_state.board[r_field];
  auto l_piece = (Piece)game_state.board[l_field];
  auto f_piece = (Piece)game_state.board[f_field];
  auto b_piece = (Piece)game_state.board[b_field];
  auto rf_piece = (Piece)game_state.board[rf_field];
  auto lf_piece = (Piece)game_state.board[lf_field];
  auto rb_piece = (Piece)game_state.board[rb_field];
  auto lb_piece = (Piece)game_state.board[lb_field];

  if ((field_index + 1) % 8 != 0 &&
      (Piece::left_piece || getPieceColor(piece) != getPieceColor(r_piece))) {
    all_moves.push_back({field_index, (ushort)r_field, Piece::left_piece});
  }
  if ((field_index + 1) % 8 != 0 && rf_field < 64 &&
      (Piece::left_piece || getPieceColor(piece) != getPieceColor(rf_piece))) {
    all_moves.push_back({field_index, (ushort)rf_field, Piece::left_piece});
  }
  if ((field_index + 1) % 8 != 0 && rb_field > -1 &&
      (Piece::left_piece || getPieceColor(piece) != getPieceColor(rb_piece))) {
    all_moves.push_back({field_index, (ushort)rb_field, Piece::left_piece});
  }
  if (f_field < 64 &&
      (Piece::left_piece || getPieceColor(piece) != getPieceColor(f_piece))) {
    all_moves.push_back({field_index, (ushort)f_field, Piece::left_piece});
  }
  if (b_field > -1 &&
      (Piece::left_piece || getPieceColor(piece) != getPieceColor(b_piece))) {
    all_moves.push_back({field_index, (ushort)b_field, Piece::left_piece});
  }
  if (field_index % 8 != 0 &&
      (Piece::left_piece || getPieceColor(piece) != getPieceColor(l_piece))) {
    all_moves.push_back({field_index, (ushort)l_field, Piece::left_piece});
  }
  if (field_index % 8 != 0 && lf_field < 64 &&
      (Piece::left_piece || getPieceColor(piece) != getPieceColor(lf_piece))) {
    all_moves.push_back({field_index, (ushort)lf_field, Piece::left_piece});
  }
  if (field_index % 8 != 0 && lb_field > -1 &&
      (Piece::left_piece || getPieceColor(piece) != getPieceColor(lb_piece))) {
    all_moves.push_back({field_index, (ushort)lb_field, Piece::left_piece});
  }
  if (castling_king) {
    all_moves.push_back(
        {field_index, (ushort)(field_index + 2), Piece::left_piece});
  }
  if (castling_queen) {
    all_moves.push_back(
        {field_index, (ushort)(field_index - 2), Piece::left_piece});
  }

  return all_moves;
}

}  // namespace blaengine::calculation
