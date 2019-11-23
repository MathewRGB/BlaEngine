#include "move_generator.h"

namespace blaengine::calculation {

MoveGenerator::MoveGenerator() {}
MoveGenerator::~MoveGenerator() {}

void MoveGenerator::startSearching(GameState game_state) {
  auto possible_moves = vector<Move>();

  for (int i = 0; i < FIELD_NUMBER; i++) {
    if (game_state.board.fields[i] == Piece::black_pawn ||
        game_state.board.fields[i] == Piece::white_pawn) {
      auto pawn_moves = this->getPawnMoves(game_state, i);
      possible_moves.insert(possible_moves.end(), pawn_moves.begin(),
                            pawn_moves.end());
    }
  }

  this->bestMove = possible_moves[0];
}

void MoveGenerator::stopSearching() {}

ushort MoveGenerator::moveForward(ushort field_index, ushort number) {
  return field_index + 8 * number;
}

ushort MoveGenerator::moveBackward(ushort field_index, ushort number) {
  return field_index - 8 * number;
}

ushort MoveGenerator::moveRight(ushort field_index, ushort number) {
  return field_index + number;
}

ushort MoveGenerator::moveLeft(ushort field_index, ushort number) {
  return field_index - number;
}

bool MoveGenerator::isWhite(Piece piece) {
  return (piece > 'A' && piece < 'Z');
}

vector<Move> MoveGenerator::getPawnMoves(GameState game_state,
                                         ushort field_index) {
  auto possible_moves = vector<Move>();
  auto piece = (Piece)game_state.board.fields[field_index];
  bool white_piece = (piece == Piece::white_pawn) ? true : false;

  if (white_piece) {
    ushort common_field = moveForward(field_index, 1);
    auto piece_common_field = (Piece)game_state.board.fields[common_field];

    if (field_index < 48 && piece_common_field == Piece::left_piece) {
      possible_moves.push_back({field_index, common_field, Piece::left_piece});
    }
    if (field_index < 56 && field_index > 40 &&
        piece_common_field == Piece::left_piece) {
      possible_moves.push_back(
          {field_index, common_field, Piece::white_bishop});
      possible_moves.push_back(
          {field_index, common_field, Piece::white_knight});
      possible_moves.push_back({field_index, common_field, Piece::white_queen});
      possible_moves.push_back({field_index, common_field, Piece::white_rook});
    }

    ushort double_move = moveForward(field_index, 2);
    auto piece_double_move = (Piece)game_state.board.fields[double_move];
    if (field_index > 7 && field_index < 16 &&
        piece_double_move == Piece::left_piece &&
        piece_common_field == Piece::left_piece) {
      possible_moves.push_back({field_index, double_move, Piece::left_piece});
    }

    // ushort left_forward = moveLeft(common_field, 1);
    // auto left_forward_piece = (Piece)game_state.board.fields[left_forward];

    // ushort right_forward = moveRight(common_field, 1);
    // auto left_forward_piece = (Piece)game_state.board.fields[left_forward];


  } else {
  }

  return possible_moves;
}

}  // namespace blaengine::calculation
