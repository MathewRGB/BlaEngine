#include "helper_for_tests.h"
#include "source/calculation/calculator.h"


using namespace blaengine::calculation;

TEST(Calculator, test_set_game_state)
{
  auto fen_string = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR";
  auto pgn_moves = vector<string>();
  auto calc_module = Calculator();
  calc_module.setCurrentGameState(fen_string, pgn_moves);

  ASSERT_TRUE(true);
}
