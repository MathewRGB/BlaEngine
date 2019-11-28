#include <fstream>
#include <thread>
#include "gtest/gtest.h"

#include "helper_for_tests.h"
#include "uci.h"

#define RND_DELAY 1.5

using namespace blaengine;
using namespace blaengine::communication;

TEST(Uci, test_quit_call) {
  auto blaengine = make_shared<BlaEngine>();
  auto uci_module = Uci(blaengine);

  auto response = uci_module.translateInput("quit");

  ASSERT_NE(response[0].find("byebye"), string::npos);
}

TEST(Uci, test_uci_call) {
  auto blaengine = make_shared<BlaEngine>();
  auto uci_module = Uci(blaengine);
  auto uci_response = vector<string>();
  auto quit_response = vector<string>();

  uci_response = uci_module.translateInput("uci");
  quit_response = uci_module.translateInput("quit");

  ASSERT_NE(uci_response[0].find("id name"), string::npos);
  ASSERT_NE(uci_response[1].find("id author"), string::npos);
  ASSERT_NE(uci_response[2].find("uciok"), string::npos);
  ASSERT_NE(quit_response[0].find("byebye"), string::npos);
}

TEST(Uci, test_isready) {
  auto blaengine = make_shared<BlaEngine>();
  auto uci_module = Uci(blaengine);
  auto response = vector<string>();

  response = uci_module.translateInput("isready");

  ASSERT_EQ(response[0], "readyok");
}

TEST(Uci, test_go_move) {
  auto blaengine = make_shared<BlaEngine>();
  auto uci_module = Uci(blaengine);
  auto response = vector<string>();

  uci_module.translateInput("position startpos");
  response = uci_module.translateInput("go ");

  ASSERT_NE(response[0].find("bestmove"), string::npos);
}

TEST(Uci, test_go_thinking_info) {
  auto blaengine = make_shared<BlaEngine>();
  auto uci_module = Uci(blaengine);
  auto response = vector<string>();

  uci_module.translateInput("position startpos");
  response = uci_module.translateInput("go infinite");

  ASSERT_NE(response[0].find("info currmove"), string::npos);
}

TEST(Uci, test_position_cmd) {
  auto blaengine = make_shared<BlaEngine>();
  auto uci_module = Uci(blaengine);
  auto response = vector<string>();

  response = uci_module.translateInput("position startpos");

  ASSERT_NE(response[0].find("position was set"), string::npos);
}

TEST(Uci, test_position_cmd_black_bug) {
  auto blaengine = make_shared<BlaEngine>();
  auto uci_module = Uci(blaengine);
  auto response = vector<string>();

  response = uci_module.translateInput("position startpos moves e2e3");
  response =
      uci_module.translateInput("go wtime 300000 btime 300000 winc 0 binc 0");

  ASSERT_EQ(blaengine->gstate_translator.gstate_controller.current_game_state
                .next_turn,
            Color::black);
  ASSERT_EQ(response[0].find("bestmove b2c3"), string::npos);
}

TEST(Uci, test_extract_game_state) {
  auto pgn_moves = vector<string>();
  auto blaengine = make_shared<BlaEngine>();
  auto uci_module = Uci(blaengine);
  ifstream file;
  file.open("mock_data/test_gamestates.txt");
  string test_string;

  if (file.is_open()) getline(file, test_string);
  auto gs_tuple1 = uci_module.extractGameState(test_string);
  ASSERT_EQ(get<0>(gs_tuple1),
            "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
  ASSERT_TRUE(get<1>(gs_tuple1).empty());

  getline(file, test_string);
  auto gs_tuple2 = uci_module.extractGameState(test_string);
  ASSERT_EQ(get<0>(gs_tuple2),
            "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w - - 0 1");
  ASSERT_TRUE(get<1>(gs_tuple2).empty());

  getline(file, test_string);
  auto gs_tuple3 = uci_module.extractGameState(test_string);
  ASSERT_EQ(get<0>(gs_tuple3),
            "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
  ASSERT_EQ(get<1>(gs_tuple3).size(), 63);

  getline(file, test_string);
  auto gs_tuple4 = uci_module.extractGameState(test_string);
  ASSERT_EQ(get<0>(gs_tuple4), "8/6pk/5pn1/1q5p/7P/3P2P1/4QP2/4N1K1 b - - 0 1");
  ASSERT_TRUE(get<1>(gs_tuple4).empty());

  getline(file, test_string);
  auto gs_tuple5 = uci_module.extractGameState(test_string);
  ASSERT_EQ(get<0>(gs_tuple5), "8/6pk/5pn1/1q5p/7P/3P2P1/4QP2/4N1K1 b - - 0 1");
  ASSERT_EQ(get<1>(gs_tuple5).size(), 6);

  file.close();
}

TEST(Uci, test_position_full_game) {
  // get position strings for testing from file
  ifstream file;
  file.open("mock_data/test_gamestates.txt");
  string test_position;
  string comparison_position;

  for (int i = 0; i < 6 && file.is_open(); i++) {
    getline(file, test_position);
  }
  getline(file, comparison_position);
  file.close();

  // first instance
  auto blaengine = make_shared<BlaEngine>();
  auto uci_module = Uci(blaengine);
  auto response = vector<string>();

  response = uci_module.translateInput(test_position);

  // second instance
  setup_std_mock_io();
  auto cmp_blaengine = make_shared<BlaEngine>();
  auto cmp_uci_module = Uci(cmp_blaengine);
  auto cmp_response = vector<string>();

  cmp_response = cmp_uci_module.translateInput(comparison_position);

  ASSERT_NE(cmp_response[0].find("position was set"), string::npos);
  ASSERT_TRUE(compare_game_states(
      cmp_blaengine->gstate_translator.gstate_controller.current_game_state,
      blaengine->gstate_translator.gstate_controller.current_game_state));
}

TEST(Uci, test_game_state_reset_after_new_pos) {
  // get position strings for testing from file
  ifstream file;
  file.open("mock_data/test_gamestates.txt");
  string test_position;
  string reset_position = "position startpos";
  string comparison_position;

  for (int i = 0; i < 6 && file.is_open(); i++) {
    getline(file, test_position);
  }
  file.close();

  auto blaengine = make_shared<BlaEngine>();
  auto uci_module = Uci(blaengine);
  auto& game_state =
      blaengine->gstate_translator.gstate_controller.current_game_state;

  uci_module.translateInput(test_position);
  uci_module.translateInput(reset_position);

  ASSERT_EQ(game_state.en_passant_field, -1);
  ASSERT_EQ(game_state.half_moves_for_draw, 0);
  ASSERT_EQ(game_state.next_half_move, 1);
  ASSERT_EQ(game_state.next_turn, Color::white);
}
