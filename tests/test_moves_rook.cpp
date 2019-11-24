#include "gtest/gtest.h"
#include "helper_for_tests.h"
#include "source/calculation/game_state_controller.h"
#include "source/calculation/move_generator.h"

using namespace blaengine::calculation;

TEST(RookMoves, test_general_moves_pos35) {
  auto move_generator = MoveGenerator();
  auto game_state = GameState();
  ushort field_before = 35;
  vector<ushort> possible_fields = {43, 51, 59, 27, 19, 11, 3,
                                    36, 37, 38, 39, 32, 33, 34};
  game_state.board.fields[field_before] = Piece::white_rook;

  auto knight_moves = move_generator.getKnightMoves(game_state, field_before);
  auto expected_moves = createMovesFromFieldList(field_before, possible_fields);

  ASSERT_TRUE(expectedMovesInMoves(knight_moves, expected_moves));
}
