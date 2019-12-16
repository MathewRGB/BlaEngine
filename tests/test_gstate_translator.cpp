#include "gtest/gtest.h"

#include "helper_for_tests.h"
#include "source/calculation/gstate_translator.h"

using namespace blaengine::calculation;

TEST(Calculator, test_set_fen_string) {
  auto translator = GSateTranslator();
  auto gstate_controller = GameStateController();
  GameState& current_game_state = gstate_controller.current_game_state;
  auto fen = "r2r2k1/pppqbppp/1nn1p3/8/1PPPN3/P3BN2/4QPPP/3R1RK1 b - b3 0 15";
  current_game_state = translator.interpretAndSetFen(fen);

  auto comp_gstate_controller = GameStateController();
  GameState& comp_game_state = comp_gstate_controller.current_game_state;
  comp_game_state.board[3] = 'R';
  comp_game_state.board[5] = 'R';
  comp_game_state.board[6] = 'K';
  comp_game_state.board[12] = 'Q';
  comp_game_state.board[13] = 'P';
  comp_game_state.board[14] = 'P';
  comp_game_state.board[15] = 'P';
  comp_game_state.board[16] = 'P';
  comp_game_state.board[20] = 'B';
  comp_game_state.board[21] = 'N';
  comp_game_state.board[25] = 'P';
  comp_game_state.board[26] = 'P';
  comp_game_state.board[27] = 'P';
  comp_game_state.board[28] = 'N';
  comp_game_state.board[41] = 'n';
  comp_game_state.board[42] = 'n';
  comp_game_state.board[44] = 'p';
  comp_game_state.board[48] = 'p';
  comp_game_state.board[49] = 'p';
  comp_game_state.board[50] = 'p';
  comp_game_state.board[51] = 'q';
  comp_game_state.board[52] = 'b';
  comp_game_state.board[53] = 'p';
  comp_game_state.board[54] = 'p';
  comp_game_state.board[55] = 'p';
  comp_game_state.board[56] = 'r';
  comp_game_state.board[59] = 'r';
  comp_game_state.board[62] = 'k';
  comp_game_state.en_passant_field = 17;
  comp_game_state.half_moves_for_draw = 0;
  comp_game_state.next_turn = Color::black;
  comp_game_state.next_half_move = 30;

  ASSERT_TRUE(compare_game_states(current_game_state, comp_game_state));
}

TEST(Calculator, test_set_game_state_2_moves) {
  auto comparison_fen =
      "rnbqkbnr/pppp1ppp/4p3/8/4P3/8/PPPP1PPP/RNBQKBNR w KQkq - 0 2";
  auto fen = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
  vector<string> moves{"e2e4", "e7e6"};

  auto comp_translator = GSateTranslator();
  auto comp_gstate_controller = GameStateController();
  auto& comp_game_state = comp_gstate_controller.current_game_state;
  comp_game_state = comp_translator.interpretAndSetFen(comparison_fen);

  auto translator = GSateTranslator();
  auto gstate_controller = GameStateController();
  auto& game_state = gstate_controller.current_game_state;
  game_state = translator.interpretAndSetFen(fen);
  game_state = translator.makeMovesFromFieldStrings(game_state, moves);

  ASSERT_TRUE(compare_game_states(game_state, comp_game_state));
}

TEST(GSateTranslator, test_set_game_state_29_moves) {
  auto comparison_fen =
      "r2r2k1/pppqbppp/1nn1p3/8/1PPPN3/P3BN2/4QPPP/3R1RK1 b - b3 0 15";
  auto fen = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
  vector<string> moves{"e2e4", "d7d5", "e4d5", "g8f6", "d2d4", "f6d5",
                       "g1f3", "c8f5", "f1d3", "f5d3", "d1d3", "b8c6",
                       "e1g1", "e7e6", "d3e2", "f8e7", "c2c4", "d5b6",
                       "c1e3", "e8g8", "b1c3", "e7b4", "c3e4", "b4e7",
                       "a1d1", "d8d7", "a2a3", "f8d8", "b2b4"};

  auto comp_translator = GSateTranslator();
  auto comp_gstate_controller = GameStateController();
  auto& comp_game_state = comp_gstate_controller.current_game_state;
  comp_game_state = comp_translator.interpretAndSetFen(comparison_fen);

  auto translator = GSateTranslator();
  auto gstate_controller = GameStateController();
  auto& game_state = gstate_controller.current_game_state;
  game_state = translator.interpretAndSetFen(fen);
  game_state = translator.makeMovesFromFieldStrings(game_state, moves);

  ASSERT_TRUE(compare_game_states(game_state, comp_game_state));
}

TEST(Calculator, test_en_passant_move_black) {
  auto comparison_fen = "7k/8/5p2/6p1/8/6p1/8/1K6 w - - 0 2";
  auto fen = "7k/8/5p2/6p1/7p/8/6P1/1K6 w - - 0 1";
  vector<string> moves{"g2g4", "h4g3"};

  auto comp_translator = GSateTranslator();
  auto comp_gstate_controller = GameStateController();
  auto& comp_game_state = comp_gstate_controller.current_game_state;
  comp_game_state = comp_translator.interpretAndSetFen(comparison_fen);

  auto translator = GSateTranslator();
  auto gstate_controller = GameStateController();
  auto& game_state = gstate_controller.current_game_state;
  game_state = translator.interpretAndSetFen(fen);
  game_state = translator.makeMovesFromFieldStrings(game_state, moves);

  ASSERT_TRUE(compare_game_states(game_state, comp_game_state));
}

TEST(Calculator, test_piece_transformation_white_Q) {
  auto comparison_fen = "5Q2/8/6k1/8/8/8/6PP/5K2 b - - 2 5";
  auto fen = "8/p6k/8/1P6/8/8/6PP/5K2 b - - 0 1";
  vector<string> moves{"a7a5", "b5a6",  "h7g7", "a6a7",
                       "g7f7", "a7a8q", "f7g6", "a8f8"};

  auto comp_translator = GSateTranslator();
  auto comp_gstate_controller = GameStateController();
  auto& comp_game_state = comp_gstate_controller.current_game_state;
  comp_game_state = comp_translator.interpretAndSetFen(comparison_fen);

  auto translator = GSateTranslator();
  auto gstate_controller = GameStateController();
  auto& game_state = gstate_controller.current_game_state;
  game_state = translator.interpretAndSetFen(fen);
  game_state = translator.makeMovesFromFieldStrings(game_state, moves);

  ASSERT_TRUE(compare_game_states(game_state, comp_game_state));
}

TEST(Calculator, test_piece_transformation_black_q) {
  auto comparison_fen = "7k/6pp/8/8/8/6PK/7P/5q2 w - - 2 5";
  auto fen = "7k/6pp/8/8/1p6/8/P5PP/7K w - - 0 1";
  vector<string> moves{"a2a4", "b4a3",  "g2g3", "a3a2",
                       "h1g2", "a2a1q", "g2h3", "a1f1"};

  auto comp_translator = GSateTranslator();
  auto comp_gstate_controller = GameStateController();
  auto& comp_game_state = comp_gstate_controller.current_game_state;
  comp_game_state = comp_translator.interpretAndSetFen(comparison_fen);

  auto translator = GSateTranslator();
  auto gstate_controller = GameStateController();
  auto& game_state = gstate_controller.current_game_state;
  game_state = translator.interpretAndSetFen(fen);
  game_state = translator.makeMovesFromFieldStrings(game_state, moves);

  ASSERT_TRUE(compare_game_states(game_state, comp_game_state));
}
