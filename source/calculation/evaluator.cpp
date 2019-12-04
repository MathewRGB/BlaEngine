#include <random>

#include "evaluator.h"
#include "move_generator.h"

namespace blaengine::calculation {

Evaluator::Evaluator() {}
Evaluator::~Evaluator() {}

void Evaluator::startSearching(GameState game_state) {
  auto possible_moves = MoveGenerator::getAllMightPossibleMoves(game_state);
  this->bestMove = this->chooseBestMove(possible_moves);
}

int Evaluator::evaluateGameState(GameState game_state) {
  int rating = 0;
  auto piece_value = PieceValue();

  for (ushort i = 0; i < FIELD_NUMBER; i++) {
    switch (game_state.board[i]) {
      case Piece::white_pawn:
        rating += piece_value.pawn_value;
        break;
      case Piece::black_pawn:
        rating -= piece_value.pawn_value;
        break;
      case Piece::white_knight:
        rating += piece_value.knight_value;
        break;
      case Piece::black_knight:
        rating -= piece_value.knight_value;
        break;
      case Piece::white_bishop:
        rating += piece_value.bishop_value;
        break;
      case Piece::black_bishop:
        rating -= piece_value.bishop_value;
        break;
      case Piece::white_rook:
        rating += piece_value.rook_value;
        break;
      case Piece::black_rook:
        rating -= piece_value.rook_value;
        break;
      case Piece::white_queen:
        rating += piece_value.queen_value;
        break;
      case Piece::black_queen:
        rating -= piece_value.queen_value;
        break;
      case Piece::white_king:
        rating += piece_value.king_value;
        break;
      case Piece::black_king:
        rating -= piece_value.king_value;
        break;
      default:
        break;
    }
  }
  return rating;
}

Move Evaluator::chooseBestMove(vector<Move> moves) {
  random_device rd;
  mt19937 gen(rd());
  uniform_int_distribution<> dist(0, moves.size() - 1);
  ushort rnd_idx = dist(gen);

  return moves[rnd_idx];
}

}  // namespace blaengine::calculation