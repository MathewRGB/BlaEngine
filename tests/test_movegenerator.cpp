#include "gtest/gtest.h"
#include "helper_for_tests.h"
#include "source/calculation/game_state_controller.h"
#include "source/calculation/move_generator.h"

using namespace blaengine::calculation;

TEST(MoveGenerator, test_expectedMovesInMoves1) {
  vector<Move> moves = {{10, 0, Piece::white_pawn},
                        {0, 0, Piece::black_king},
                        {0, 1, Piece::left_piece}};
  vector<Move> expected_moves = {{0, 0, Piece::black_king},
                                 {0, 1, Piece::left_piece},
                                 {10, 0, Piece::white_pawn}};

  ASSERT_TRUE(expectedMovesInMoves(moves, expected_moves));
}

TEST(MoveGenerator, test_expectedMovesInMoves2) {
  vector<Move> moves = {{10, 0, Piece::white_pawn},
                        {0, 1, Piece::left_piece}};
  vector<Move> expected_moves = {{0, 0, Piece::black_king},
                                 {0, 1, Piece::left_piece},
                                 {10, 0, Piece::white_pawn}};

  ASSERT_FALSE(expectedMovesInMoves(moves, expected_moves));
}

TEST(MoveGenerator, test_expectedMovesInMoves3) {
  vector<Move> moves = {{10, 0, Piece::white_pawn},
                        {0, 0, Piece::black_king},
                        {0, 1, Piece::left_piece}};
  vector<Move> expected_moves = {{0, 0, Piece::black_king},
                                 {10, 0, Piece::white_pawn}};

  ASSERT_TRUE(expectedMovesInMoves(moves, expected_moves));
}

TEST(MoveGenerator, test_expectedMovesInMoves4) {
  vector<Move> moves = {{10, 0, Piece::white_pawn},
                        {0, 0, Piece::black_king},
                        {0, 1, Piece::left_piece}};
  vector<Move> expected_moves = {{0, 0, Piece::black_king},
                                 {21, 63, Piece::white_pawn}};

  ASSERT_FALSE(expectedMovesInMoves(moves, expected_moves));
}

TEST(MoveGenerator, test_w_pawn_moves1) {
  auto move_generator = MoveGenerator();
  auto game_state = GameState();
  game_state.board.fields[10] = Piece::white_pawn;

  auto pawn_moves = move_generator.getPawnMoves(game_state, 10);
  vector<Move> expected_moves = {{10, 18, Piece::left_piece},
                                 {10, 26, Piece::left_piece}};

  ASSERT_TRUE(true);
}
