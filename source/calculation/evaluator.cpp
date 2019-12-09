#include <random>

#include "evaluator.h"
#include "move_generator.h"

namespace blaengine::calculation {

Evaluator::Evaluator(ushort max_depth) { this->searching_depth = max_depth; }

void Evaluator::startSearching(GameState game_state) {
  this->miniMax(game_state, this->searching_depth);
  // TODO alpha-beta, transposition tables, q-search, search selectivity,
  // bitboards
}

int Evaluator::evaluateByPieceValues(GameState game_state,
                                     vector<Move> possible_moves) {
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

  rating += (game_state.next_turn == Color::white) ? possible_moves.size()
                                                   : -possible_moves.size();
  return rating;
}

int Evaluator::evaluateGameState(GameState game_state,
                                 vector<Move> possible_moves) {
  int rating = this->evaluateByPieceValues(game_state, possible_moves);
  return rating;
}

int Evaluator::miniMax(GameState game_state, ushort depth) {
  auto possible_moves = MoveGenerator::getAllMightPossibleMoves(game_state);
  int maximized_value = -INT32_MAX;
  short negamax_sign = game_state.next_turn;

  if (depth == 0 || possible_moves.size() == 0) {
    return negamax_sign * this->evaluateGameState(game_state, possible_moves);
  }

  for (uint i = 0; i < possible_moves.size(); i++) {
    auto gstate_controller = GameStateController();
    gstate_controller.current_game_state = game_state;
    gstate_controller.makeMove(possible_moves[i]);

    if (negamax_sign * this->evaluateGameState(game_state, possible_moves) <
        MIN_SANITY_VALUE) {
      continue;
    }

    int rating = -miniMax(gstate_controller.current_game_state, depth - 1);

    if (rating > maximized_value) {
      maximized_value = rating;
      if (depth == this->searching_depth) this->bestMove = possible_moves[i];
    }
  }
  return maximized_value;
}

int Evaluator::getRandomValue(int range) {
  random_device rd;
  mt19937 gen(rd());
  uniform_int_distribution<> dist(-range, range);
  int random_value = dist(gen);

  return random_value;
}

}  // namespace blaengine::calculation