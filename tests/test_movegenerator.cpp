#include "gtest/gtest.h"
#include "source/calculation/game_state_controller.h"
#include "source/calculation/move_generator.h"

using namespace blaengine::calculation;

TEST(MoveGenerator, test_w_pawn_moves1) {
  auto move_generator = MoveGenerator();
  auto game_state = GameState();
  game_state.board.fields[10] = Piece::white_pawn;

  auto pawn_moves = move_generator.getPawnMoves(game_state, 10);

  ASSERT_EQ(pawn_moves.size(), 2);
  ASSERT_TRUE(
      (pawn_moves[0].field_after == 18 || pawn_moves[0].field_after == 26) &&
      (pawn_moves[1].field_after == 18 || pawn_moves[1].field_after == 26));
}
