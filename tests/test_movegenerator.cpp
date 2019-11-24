#include "gtest/gtest.h"
#include "helper_for_tests.h"
#include "source/calculation/game_state_controller.h"
#include "source/calculation/move_generator.h"

using namespace blaengine::calculation;

TEST(MoveGenerator, test_expectedMovesInMoves0) {
  vector<Move> moves = {{10, 0, Piece::white_pawn},
                        {0, 0, Piece::black_king},
                        {0, 1, Piece::left_piece}};
  vector<Move> expected_moves = {{0, 0, Piece::black_king},
                                 {0, 1, Piece::left_piece}};

  ASSERT_FALSE(expectedMovesInMoves(moves, expected_moves));
}

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
                        {0, 1, Piece::left_piece},
                        {5, 1, Piece::left_piece}};
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
                                 {10, 0, Piece::white_pawn},
                                 {0, 1, Piece::left_piece}};

  ASSERT_TRUE(expectedMovesInMoves(moves, expected_moves));
}

TEST(MoveGenerator, test_expectedMovesInMoves4) {
  vector<Move> moves = {{10, 0, Piece::white_pawn},
                        {0, 0, Piece::black_king},
                        {0, 1, Piece::left_piece}};
  vector<Move> expected_moves = {{0, 0, Piece::black_king},
                                 {21, 63, Piece::white_pawn},
                                 {1, 66, Piece::white_pawn}};

  ASSERT_FALSE(expectedMovesInMoves(moves, expected_moves));
}
