#include <random>

#include "evaluator.h"
#include "move_generator.h"

namespace blaengine::calculation {

Evaluator::Evaluator(ushort searching_depth) {
  this->searching_depth = searching_depth;
}

void Evaluator::startSearching(GameState game_state) {
  int rating = this->negamaxAndAlphaBeta(game_state, this->searching_depth);

  if (rating < MIN_SANITY_VALUE) {
    int depth_backup = this->searching_depth;
    this->searching_depth = 2;
    this->negamaxAndAlphaBeta(game_state, this->searching_depth);
    this->searching_depth = depth_backup;
  }
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

int Evaluator::negamaxAndAlphaBeta(GameState game_state, ushort depth,
                                   int alpha, int beta) {
  auto possible_moves = MoveGenerator::getAllMightPossibleMoves(game_state);
  int maximized_value = -INT32_MAX;
  short negamax_sign = game_state.next_turn;
  int current_rating =
      negamax_sign * this->evaluateGameState(game_state, possible_moves);

  if (current_rating > -MIN_SANITY_VALUE) {
    return INT32_MAX;
  }
  if (depth == 0 || possible_moves.size() == 0) {
    return current_rating;
  }

  for (uint i = 0; i < possible_moves.size(); i++) {
    auto gstate_controller = GameStateController();
    gstate_controller.current_game_state = game_state;
    gstate_controller.makeMove(possible_moves[i]);

    int rating = -negamaxAndAlphaBeta(gstate_controller.current_game_state,
                                      depth - 1, -beta, -alpha);
    if (rating > maximized_value) {
      maximized_value = rating;
      if (depth == this->searching_depth) {
        this->bestMove = possible_moves[i];
      }
    }
    if (rating > alpha) {
      alpha = rating;
    }
    if (alpha >= beta) {
      break;
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