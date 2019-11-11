#include "helper_for_tests.h"
#include "source/calculation/calculator.h"

using namespace blaengine::calculation;

bool compare_game_states(GameState state1, GameState state2);
vector<string> getEmptyMovesVector();

bool compare_game_states(GameState state1, GameState state2) {
  for (int i = 0; i < FIELD_NUMBER; i++) {
    if (state1.board.fields[i] != state2.board.fields[i]) {
      return false;
    }
  }
  for (int i = 0; i < CASTLING_NUMBER; i++) {
    if (state1.board.castling[i] != state2.board.castling[i]) {
      return false;
    }
  }
  if (state1.en_passant_move != state2.en_passant_move) {
    return false;
  }
  if (state1.half_moves_40_move_rule != state2.half_moves_40_move_rule) {
    return false;
  }
  if (state1.next_half_move != state2.next_half_move) {
    return false;
  }
  if (state1.next_turn != state2.next_turn) {
    return false;
  }

  return true;
}

vector<string> getEmptyMovesVector() {
  auto comparison_moves = vector<string>();
  return comparison_moves;
}

TEST(Calculator, test_set_fen_string) {
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

  auto fen = "r2r2k1/pppqbppp/1nn1p3/8/1PPPN3/P3BN2/4QPPP/3R1RK1 b - b3 0 15";
  auto calc_module = Calculator();
  calc_module.setCurrentGameState(fen, getEmptyMovesVector());

  ASSERT_TRUE(compare_game_states(calc_module.current_game_state,
                                  comp_calc_module.current_game_state));
}

TEST(Calculator, test_set_game_state) {
  auto comparison_fen =
      "r2r2k1/pppqbppp/1nn1p3/8/1PPPN3/P3BN2/4QPPP/3R1RK1 b - b3 0 15";
  auto fen = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w - - 0 1";
  vector<string> moves = {"e2e4", "d7d5", "e4d5", "g8f6", "d2d4", "f6d5",
                          "g1f3", "c8f5", "f1d3", "f5d3", "d1d3", "b8c6",
                          "e1g1", "e7e6", "d3e2", "f8e7", "c2c4", "d5b6",
                          "c1e3", "e8g8", "b1c3", "e7b4", "c3e4", "b4e7",
                          "a1d1", "d8d7", "a2a3", "f8d8", "b2b4"};
  auto calc_module = Calculator();
  calc_module.setCurrentGameState(fen, moves);
  auto comp_calc_module = Calculator();
  comp_calc_module.setCurrentGameState(comparison_fen, getEmptyMovesVector());

  ASSERT_TRUE(compare_game_states(calc_module.current_game_state,
                                  comp_calc_module.current_game_state));
}
