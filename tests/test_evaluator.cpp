#include "gtest/gtest.h"
#include "source/calculation/evaluator.h"

using namespace blaengine::calculation;

TEST(Evaluator, test_evaluate_game_state_1)
{
  auto evaluator = Evaluator();
  auto gstate_translator = GSateTranslator();
  auto fen = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
  auto& game_state = gstate_translator.gstate_controller.current_game_state;
  
  gstate_translator.interpretAndSetFen(fen);
  int rating = evaluator.evaluateGameState(game_state);

  ASSERT_EQ(rating, 0);
}

TEST(Evaluator, test_evaluate_game_state_2)
{
  auto evaluator = Evaluator();
  auto gstate_translator = GSateTranslator();
  auto fen = "1nbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/1NBQKBNR w KQkq - 0 1";
  auto& game_state = gstate_translator.gstate_controller.current_game_state;
  
  gstate_translator.interpretAndSetFen(fen);
  int rating = evaluator.evaluateGameState(game_state);

  ASSERT_EQ(rating, 0);
}

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

  ASSERT_LT(rating, 0);
}

TEST(Evaluator, test_evaluate_game_state_5)
{
  auto evaluator = Evaluator();
  auto gstate_translator = GSateTranslator();
  auto fen = "1nb1kbnr/pppppppp/8/8/8/8/PPPPPPPP/1NB1KB1R w KQkq - 0 1";
  auto& game_state = gstate_translator.gstate_controller.current_game_state;
  
  gstate_translator.interpretAndSetFen(fen);
  int rating = evaluator.evaluateGameState(game_state);

  ASSERT_GT(rating, 0);
}
