#ifndef HELPERFORTESTS_H_
#define HELPERFORTESTS_H_

#include "source/calculation/calculator.h"

using namespace std;
using namespace blaengine;
using namespace blaengine::calculation;

bool compare_game_states(GameState state1, GameState state2);
void setup_std_mock_io();
void teardown_std_mock_io();

std::stringstream mock_cin, mock_cout;
std::streambuf *cin_backup, *cout_backup;


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
  if (state1.half_moves_for_draw != state2.half_moves_for_draw) {
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

void setup_std_mock_io() {
  cin_backup = std::cin.rdbuf();
  cout_backup = std::cout.rdbuf();

  std::cin.rdbuf(mock_cin.rdbuf());
  std::cout.rdbuf(mock_cout.rdbuf());
}

void teardown_std_mock_io() {
  std::cin.rdbuf(cin_backup);
  std::cout.rdbuf(cout_backup);
}

#endif  // HELPERFORTESTS_H_