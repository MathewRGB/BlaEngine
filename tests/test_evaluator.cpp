#include "gtest/gtest.h"
#include "source/calculation/evaluator.h"

using namespace blaengine::calculation;

TEST(Evaluator, test_evaluate_game_state)
{
  auto evaluator = Evaluator();
  auto gstate_translator = GSateTranslator();
  auto fen = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
  auto& game_state = gstate_translator.gstate_controller.current_game_state;
  
  gstate_translator.interpretAndSetFen(fen);
  int rating = evaluator.evaluateGameState(game_state);

  ASSERT_EQ(rating, 0);
}
