#include "gtest/gtest.h"
#include "helper_for_tests.h"
#include "source/calculation/move_generator.h"

using namespace blaengine::calculation;

TEST(QueenMoves, test_general_moves_pos35) {
  auto move_generator = MoveGenerator();
  auto game_state = GameState();
  ushort field_before = 35;
  game_state.board[field_before] = Piece::white_queen;
  game_state.board[51] = Piece::black_rook;
  game_state.board[42] = Piece::white_knight;
  game_state.board[62] = Piece::black_bishop;
  game_state.board[21] = Piece::white_pawn;

  vector<ushort> possible_fields = {43, 51, 44, 53, 62, 36, 37, 38, 39, 28,
                                    27, 19, 11, 3,  26, 17, 8,  34, 33, 32};

  auto knight_moves = move_generator.getQueenMoves(game_state, field_before);
  auto expected_moves = createMovesFromFieldList(field_before, possible_fields);

  ASSERT_TRUE(expectedMovesInMoves(knight_moves, expected_moves));
}