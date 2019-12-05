#include <random>

#include "evaluator.h"
#include "move_generator.h"

namespace blaengine::calculation {

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

int Evaluator::miniMax(GameState game_state, ushort depth) {
  auto possible_moves = MoveGenerator::getAllMightPossibleMoves(game_state);
  int maxWert = -INT32_MAX;

  if (depth == 0 || possible_moves.size() == 0) {
    return this->evaluateGameState(game_state);
  }

  for (uint i = 0; i < possible_moves.size(); i++) {
    auto gstate_controller = GameStateController();
    gstate_controller.current_game_state = game_state;
    gstate_controller.makeMove(possible_moves[i]);

    int wert = -miniMax(gstate_controller.current_game_state, depth - 1);

    if (wert > maxWert) {
      maxWert = wert;
      if (depth == this->searching_depth) this->bestMove = possible_moves[i];
    }
  }
  return maxWert;
}

Move Evaluator::chooseBestMove(vector<Move> moves) {
  random_device rd;
  mt19937 gen(rd());
  uniform_int_distribution<> dist(0, moves.size() - 1);
  ushort rnd_idx = dist(gen);

  return moves[rnd_idx];
}

}  // namespace blaengine::calculation