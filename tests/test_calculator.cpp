#include "helper_for_tests.h"
#include "source/calculation/calculator.h"

using namespace blaengine::calculation;

TEST(Calculator, test_set_game_state) {
  auto fen_string = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w - - 0 1";
  vector<string> pgn_moves = {
      "e2e4", "c7c5", "g1f3", "b8c6", "f1b5", "e7e6", "e1g1", "g8e7", "b5a4",
      "a7a6", "c2c4", "d8b6", "d2d3", "e7g6", "h2h4", "h7h5", "b1c3", "f8e7",
      "g2g3", "d7d6", "a1b1", "e7f6", "c1d2", "c8d7", "b2b4", "c5b4", "a4c6",
      "d7c6", "a2a3", "a6a5", "a3b4", "a5b4", "c3b5", "e8g8", "d2b4", "c6b5",
      "b4d2", "b6c6", "b1b5", "d6d5", "e4d5", "e6d5", "b5d5", "f8d8", "d5d8",
      "a8d8", "d2g5", "f6g5", "f3g5", "f7f6", "g5f3", "b7b5", "d1e2", "d8e8",
      "c4b5", "c6b5", "e2a2", "g8h7", "f1e1", "e8e1", "f3e1", "b5f5", "a2e2"};
  auto calc_module = Calculator();
  calc_module.setCurrentGameState(fen_string, pgn_moves);

  ASSERT_TRUE(true);
}
