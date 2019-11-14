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
  comp_calc_module.current_game_state.board.fields[3] = 'R';
  comp_calc_module.current_game_state.board.fields[5] = 'R';
  comp_calc_module.current_game_state.board.fields[6] = 'K';
  comp_calc_module.current_game_state.board.fields[12] = 'Q';
  comp_calc_module.current_game_state.board.fields[13] = 'P';
  comp_calc_module.current_game_state.board.fields[14] = 'P';
  comp_calc_module.current_game_state.board.fields[15] = 'P';
  comp_calc_module.current_game_state.board.fields[16] = 'P';
  comp_calc_module.current_game_state.board.fields[20] = 'B';
  comp_calc_module.current_game_state.board.fields[21] = 'N';
  comp_calc_module.current_game_state.board.fields[25] = 'P';
  comp_calc_module.current_game_state.board.fields[26] = 'P';
  comp_calc_module.current_game_state.board.fields[27] = 'P';
  comp_calc_module.current_game_state.board.fields[28] = 'N';
  comp_calc_module.current_game_state.board.fields[41] = 'n';
  comp_calc_module.current_game_state.board.fields[42] = 'n';
  comp_calc_module.current_game_state.board.fields[44] = 'p';
  comp_calc_module.current_game_state.board.fields[48] = 'p';
  comp_calc_module.current_game_state.board.fields[49] = 'p';
  comp_calc_module.current_game_state.board.fields[50] = 'p';
  comp_calc_module.current_game_state.board.fields[51] = 'q';
  comp_calc_module.current_game_state.board.fields[52] = 'b';
  comp_calc_module.current_game_state.board.fields[53] = 'p';
  comp_calc_module.current_game_state.board.fields[54] = 'p';
  comp_calc_module.current_game_state.board.fields[55] = 'p';
  comp_calc_module.current_game_state.board.fields[56] = 'r';
  comp_calc_module.current_game_state.board.fields[59] = 'r';
  comp_calc_module.current_game_state.board.fields[62] = 'k';
  comp_calc_module.current_game_state.en_passant_field = 17;
  comp_calc_module.current_game_state.half_moves_40_move_rule = 0;
  comp_calc_module.current_game_state.next_turn = NextTurn::black;
  comp_calc_module.current_game_state.next_half_move = 30;

  ASSERT_TRUE(compare_game_states(calc_module.current_game_state,
                                  comp_calc_module.current_game_state));
}

TEST(Calculator, test_set_game_state_2_moves) {
  auto comparison_fen =
      "rnbqkbnr/pppp1ppp/4p3/8/4P3/8/PPPP1PPP/RNBQKBNR w KQkq - 0 2";
  auto fen = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
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
  auto fen = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
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
