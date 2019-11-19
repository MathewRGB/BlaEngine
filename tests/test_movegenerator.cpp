#include "gtest/gtest.h"
#include "source/calculation/move_generator.h"
#include "source/calculation/game_state_controller.h"

using namespace blaengine::calculation;

TEST(MoveGenerator, test_pawn_moves)
{
  auto move_generator = MoveGenerator();
  auto gstate_controller = GameStateController();

  ASSERT_TRUE(true);
}
