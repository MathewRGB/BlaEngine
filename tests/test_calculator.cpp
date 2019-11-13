#include "helper_for_tests.h"
#include "source/calculation/calculator.h"

using namespace blaengine::calculation;

bool compare_game_states(GameState state1, GameState state2);

bool compare_game_states(GameState state1, GameState state2) {
  for (int i = 0; i < FIELD_NUMBER; i++) {
    if (state1.board.fields[i] != state2.board.fields[i]) {
      cout << "board comparison failed" << endl;
      return false;
    }
  }
  for (int i = 0; i < CASTLING_NUMBER; i++) {
    if (state1.board.castling[i] != state2.board.castling[i]) {
      cout << "castling comparison failed" << endl;
      return false;
    }
  }
  if (state1.en_passant_field != state2.en_passant_field) {
    cout << "en_passant_field is wrong" << endl;
    return false;
  }
  if (state1.half_moves_40_move_rule != state2.half_moves_40_move_rule) {
    cout << "half_moves_40_move_rule is wrong" << endl;
    return false;
  }
  if (state1.next_half_move != state2.next_half_move) {
    cout << "next_half_move is wrong" << endl;
    return false;
  }
  if (state1.next_turn != state2.next_turn) {
    cout << "next_turn is wrong" << endl;
    return false;
  }

  return true;
}

TEST(Calculator, test_set_fen_string) {
  auto calc_module = Calculator();
  auto fen = "r2r2k1/pppqbppp/1nn1p3/8/1PPPN3/P3BN2/4QPPP/3R1RK1 b - b3 0 15";
  calc_module.interpretAndSetFen(fen);

  auto comp_calc_module = Calculator();
  comp_calc_module.current_game_state.board.fields[0] = 'r';
  comp_calc_module.current_game_state.board.fields[3] = 'r';
  comp_calc_module.current_game_state.board.fields[6] = 'k';
  comp_calc_module.current_game_state.board.fields[8] = 'p';
  comp_calc_module.current_game_state.board.fields[9] = 'p';
  comp_calc_module.current_game_state.board.fields[10] = 'p';
  comp_calc_module.current_game_state.board.fields[11] = 'q';
  comp_calc_module.current_game_state.board.fields[12] = 'b';
  comp_calc_module.current_game_state.board.fields[13] = 'p';
  comp_calc_module.current_game_state.board.fields[14] = 'p';
  comp_calc_module.current_game_state.board.fields[15] = 'p';
  comp_calc_module.current_game_state.board.fields[17] = 'n';
  comp_calc_module.current_game_state.board.fields[18] = 'n';
  comp_calc_module.current_game_state.board.fields[20] = 'p';
  comp_calc_module.current_game_state.board.fields[33] = 'P';
  comp_calc_module.current_game_state.board.fields[34] = 'P';
  comp_calc_module.current_game_state.board.fields[35] = 'P';
  comp_calc_module.current_game_state.board.fields[36] = 'N';
  comp_calc_module.current_game_state.board.fields[40] = 'P';
  comp_calc_module.current_game_state.board.fields[44] = 'B';
  comp_calc_module.current_game_state.board.fields[45] = 'N';
  comp_calc_module.current_game_state.board.fields[52] = 'Q';
  comp_calc_module.current_game_state.board.fields[53] = 'P';
  comp_calc_module.current_game_state.board.fields[54] = 'P';
  comp_calc_module.current_game_state.board.fields[55] = 'P';
  comp_calc_module.current_game_state.board.fields[59] = 'R';
  comp_calc_module.current_game_state.board.fields[61] = 'R';
  comp_calc_module.current_game_state.board.fields[62] = 'K';
  comp_calc_module.current_game_state.en_passant_field = 17;
  comp_calc_module.current_game_state.half_moves_40_move_rule = 0;
  comp_calc_module.current_game_state.next_turn = NextTurn::black;
  comp_calc_module.current_game_state.next_half_move = 15;

  ASSERT_TRUE(compare_game_states(calc_module.current_game_state,
                                  comp_calc_module.current_game_state));
}

TEST(Calculator, test_set_game_state_2_moves) {
  auto comparison_fen =
      "rnbqkbnr/pppp1ppp/4p3/8/4P3/8/PPPP1PPP/RNBQKBNR w KQkq - 0 2";
  auto fen = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w - - 0 1";
  vector<string> moves{"e2e4", "e7e6"};

  auto comp_calc_module = Calculator();
  comp_calc_module.interpretAndSetFen(comparison_fen);

  auto calc_module = Calculator();
  calc_module.interpretAndSetFen(fen);
  calc_module.makeMovesFromFieldStrings(moves);

  ASSERT_TRUE(compare_game_states(calc_module.current_game_state,
                                  comp_calc_module.current_game_state));
}

TEST(Calculator, test_set_game_state_29_moves) {
  auto comparison_fen =
      "r2r2k1/pppqbppp/1nn1p3/8/1PPPN3/P3BN2/4QPPP/3R1RK1 b - b3 0 15";
  auto fen = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w - - 0 1";
  vector<string> moves{"e2e4", "d7d5", "e4d5", "g8f6", "d2d4", "f6d5",
                       "g1f3", "c8f5", "f1d3", "f5d3", "d1d3", "b8c6",
                       "e1g1", "e7e6", "d3e2", "f8e7", "c2c4", "d5b6",
                       "c1e3", "e8g8", "b1c3", "e7b4", "c3e4", "b4e7",
                       "a1d1", "d8d7", "a2a3", "f8d8", "b2b4"};

  auto comp_calc_module = Calculator();
  comp_calc_module.interpretAndSetFen(comparison_fen);

  auto calc_module = Calculator();
  calc_module.interpretAndSetFen(fen);
  calc_module.makeMovesFromFieldStrings(moves);

  ASSERT_TRUE(compare_game_states(calc_module.current_game_state,
                                  comp_calc_module.current_game_state));
}
