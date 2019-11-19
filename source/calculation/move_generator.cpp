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
}

void MoveGenerator::stopSearching() {}

vector<Move> MoveGenerator::getPawnMoves(GameState game_state,
                                         ushort field_index) {
  auto possible_moves = vector<Move>();
  return possible_moves;
}

}  // namespace blaengine::calculation
