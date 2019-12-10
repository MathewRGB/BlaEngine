#include "gtest/gtest.h"
#include "source/calculation/evaluator.h"

using namespace blaengine::calculation;

TEST(Evaluator, test_evaluate_game_state_3) {
  auto evaluator = Evaluator();
  auto gstate_translator = GSateTranslator();
  auto gstate_controller = GameStateController();
  auto fen = "rnbqkbnr/pppp1ppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
  auto& game_state = gstate_controller.current_game_state;

  game_state = gstate_translator.interpretAndSetFen(fen);
  int rating = evaluator.evaluateGameState(game_state);

  ASSERT_GT(rating, 0);
}

TEST(Evaluator, test_evaluate_game_state_4) {
  auto evaluator = Evaluator();
  auto gstate_translator = GSateTranslator();
  auto gstate_controller = GameStateController();
  auto fen = "1nb1kbnr/pppppppp/8/8/8/8/PPPPPPPP/1NBQKBNR w KQkq - 0 1";
  auto& game_state = gstate_controller.current_game_state;

  game_state = gstate_translator.interpretAndSetFen(fen);
  int rating = evaluator.evaluateGameState(game_state);

  ASSERT_GT(rating, 0);
}

TEST(Evaluator, test_evaluate_game_state_5) {
  auto evaluator = Evaluator();
  auto gstate_translator = GSateTranslator();
  auto gstate_controller = GameStateController();
  auto fen = "1nb1kbnr/pppppppp/8/8/8/8/PPPPPPPP/1NB1KB1R w KQkq - 0 1";
  auto& game_state = gstate_controller.current_game_state;

  game_state = gstate_translator.interpretAndSetFen(fen);
  int rating = evaluator.evaluateGameState(game_state);

  ASSERT_LT(rating, 0);
}

TEST(Evaluator, test_check_move_away) {
  auto gstate_translator = GSateTranslator();
  auto gstate_controller = GameStateController();
  auto evaluator = Evaluator();
  auto& game_state = gstate_controller.current_game_state;

  game_state = gstate_translator.interpretAndSetFen(
      "rnQ1k1nr/1p1p1ppp/p2bp3/8/8/4P3/PP1P1PPP/R1B1KBNR b KQkq - 0 6");
  evaluator.startSearching(gstate_controller.current_game_state);

  ASSERT_EQ(evaluator.bestMove.field_before, 60);
  ASSERT_EQ(evaluator.bestMove.field_after, 52);
}

TEST(Evaluator, test_check_move_away2) {
  auto gstate_translator = GSateTranslator();
  auto gstate_controller = GameStateController();
  auto evaluator = Evaluator();
  auto& game_state = gstate_controller.current_game_state;

  game_state = gstate_translator.interpretAndSetFen(
      "r6r/1p1nnpp1/2p3k1/p3B3/3P3p/P1N4P/1PPK1P1P/R5R1 b - - 2 27");
  evaluator.startSearching(gstate_controller.current_game_state);

  ASSERT_EQ(evaluator.bestMove.field_before, 46);
  ASSERT_TRUE(evaluator.bestMove.field_after == 37 ||
              evaluator.bestMove.field_after == 39 ||
              evaluator.bestMove.field_after == 47 ||
              evaluator.bestMove.field_after == 55);
}

TEST(Evaluator, test_check_move_away3) {
  auto gstate_translator = GSateTranslator();
  auto gstate_controller = GameStateController();
  auto evaluator =Evaluator(4);
  auto& game_state = gstate_controller.current_game_state;

  game_state = gstate_translator.interpretAndSetFen(
      "8/4ppp1/2P1nk2/8/6K1/8/1B3R2/7N b - - 1 87");
  evaluator.startSearching(gstate_controller.current_game_state);

  ASSERT_EQ(evaluator.bestMove.field_before, 45);
  ASSERT_EQ(evaluator.bestMove.field_after, 46);
}

TEST(Evaluator, test_check_move_away4_alpha_beta_negamax) {
  auto gstate_translator = GSateTranslator();
  auto gstate_controller = GameStateController();
  auto evaluator =Evaluator();
  auto& game_state = gstate_controller.current_game_state;

  game_state = gstate_translator.interpretAndSetFen(
      "4Bk2/N1n4p/1r1pp3/2p3p1/1pPb4/3PKP2/q3P1PP/1R5R w - - 1 23");
  evaluator.negamaxAndAlphaBeta(gstate_controller.current_game_state, 4);

  ASSERT_EQ(evaluator.bestMove.field_before, 20);
  ASSERT_EQ(evaluator.bestMove.field_after, 28);
}

TEST(Evaluator, test_check_move_away5_alpha_beta_negamax) {
  auto gstate_translator = GSateTranslator();
  auto gstate_controller = GameStateController();
  auto evaluator =Evaluator();
  auto& game_state = gstate_controller.current_game_state;

  game_state = gstate_translator.interpretAndSetFen(
      "b1r3k1/p3p1p1/1p2p3/4P2p/P1Pp4/4q3/B1P1P1PP/4R1KR w - - 5 21");
  evaluator.negamaxAndAlphaBeta(gstate_controller.current_game_state, 5);

  ASSERT_EQ(evaluator.bestMove.field_before, 6);
  ASSERT_EQ(evaluator.bestMove.field_after, 5);
}
