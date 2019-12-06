#include "gtest/gtest.h"
#include "source/calculation/evaluator.h"

using namespace blaengine::calculation;

TEST(Evaluator, test_evaluate_game_state_3)
{
  auto evaluator = Evaluator();
  auto gstate_translator = GSateTranslator();
  auto fen = "rnbqkbnr/pppp1ppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
  auto& game_state = gstate_translator.gstate_controller.current_game_state;
  
  gstate_translator.interpretAndSetFen(fen);
  int rating = evaluator.evaluateGameState(game_state);

  ASSERT_GT(rating, 0);
}

TEST(Evaluator, test_evaluate_game_state_4)
{
  auto evaluator = Evaluator();
  auto gstate_translator = GSateTranslator();
  auto fen = "1nb1kbnr/pppppppp/8/8/8/8/PPPPPPPP/1NBQKBNR w KQkq - 0 1";
  auto& game_state = gstate_translator.gstate_controller.current_game_state;
  
  gstate_translator.interpretAndSetFen(fen);
  int rating = evaluator.evaluateGameState(game_state);

  ASSERT_GT(rating, 0);
}

TEST(Evaluator, test_evaluate_game_state_5)
{
  auto evaluator = Evaluator();
  auto gstate_translator = GSateTranslator();
  auto fen = "1nb1kbnr/pppppppp/8/8/8/8/PPPPPPPP/1NB1KB1R w KQkq - 0 1";
  auto& game_state = gstate_translator.gstate_controller.current_game_state;
  
  gstate_translator.interpretAndSetFen(fen);
  int rating = evaluator.evaluateGameState(game_state);

  ASSERT_LT(rating, 0);
}

TEST(Evaluator, test_check_move_away) {
  auto gstate_translator = GSateTranslator();
  auto evaluator = Evaluator();

  gstate_translator.interpretAndSetFen(
      "rnQ1k1nr/1p1p1ppp/p2bp3/8/8/4P3/PP1P1PPP/R1B1KBNR b KQkq - 0 6");
  evaluator.startSearching(gstate_translator.gstate_controller.current_game_state);

  ASSERT_EQ(evaluator.bestMove.field_before, 60);
  ASSERT_EQ(evaluator.bestMove.field_after, 52);
}
