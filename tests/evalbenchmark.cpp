#include "gtest/gtest.h"
#include "source/calculation/evaluator.h"

using namespace blaengine::calculation;


TEST(DISABLED_benchmark, test_benchmark1) {
  auto gstate_translator = GSateTranslator();
  auto gstate_controller = GameStateController();
  auto evaluator =Evaluator(6);
  auto& game_state = gstate_controller.current_game_state;

  game_state = gstate_translator.interpretAndSetFen(
      "b1r3k1/p3p1p1/1p2p3/4P2p/P1Pp4/4q3/B1P1P1PP/4R1KR w - - 5 21");
  evaluator.startSearching(gstate_controller.current_game_state);

}

TEST(DISABLED_benchmark, test_benchmark2) {
  auto gstate_translator = GSateTranslator();
  auto gstate_controller = GameStateController();
  auto evaluator =Evaluator(6);
  auto& game_state = gstate_controller.current_game_state;

  game_state = gstate_translator.interpretAndSetFen(
      "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
  evaluator.startSearching(gstate_controller.current_game_state);

}
