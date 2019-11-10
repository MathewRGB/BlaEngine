#include <fstream>
#include <thread>

#include "helper_for_tests.h"
#include "uci.h"

#define RND_DELAY 1.5

using namespace blaengine;
using namespace blaengine::communication;

void setup_std_mock_io();
void teardown_std_mock_io();

std::stringstream mock_cin, mock_cout;
std::streambuf *cin_backup, *cout_backup;

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

TEST(Uci, test_quit_call) {
  setup_std_mock_io();

  auto blaengine = make_shared<BlaEngine>();
  auto uci_module = Uci(blaengine);

  thread uci_com_thread(uci_module);

  mock_cin.str("quit");

  sleep(RND_DELAY);
  string result_string;
  getline(mock_cout, result_string);

  teardown_std_mock_io();
  uci_com_thread.join();

  ASSERT_NE(result_string.find("byebye"), string::npos);
}

TEST(Uci, test_uci_call) {
  setup_std_mock_io();

  auto blaengine = make_shared<BlaEngine>();
  auto uci_module = Uci(blaengine);

  thread uci_com_thread(uci_module);

  mock_cin.str("uci\nquit");

  sleep(RND_DELAY);
  string result_string[4];

  for (int i = 0; i < 4; i++) {
    getline(mock_cout, result_string[i]);
  }

  teardown_std_mock_io();
  uci_com_thread.join();

  ASSERT_NE(result_string[0].find("id name"), string::npos);
  ASSERT_NE(result_string[1].find("id author"), string::npos);
  ASSERT_NE(result_string[2].find("uciok"), string::npos);
  ASSERT_NE(result_string[3].find("byebye"), string::npos);
}

TEST(Uci, test_isready) {
  setup_std_mock_io();

  auto blaengine = make_shared<BlaEngine>();
  auto uci_module = Uci(blaengine);

  thread uci_com_thread(uci_module);

  mock_cin.str("isready\nquit");

  sleep(RND_DELAY);
  string result_string[2];
  getline(mock_cout, result_string[0]);
  getline(mock_cout, result_string[1]);

  teardown_std_mock_io();
  uci_com_thread.join();

  ASSERT_EQ(result_string[0], "readyok");
  ASSERT_NE(result_string[1].find("byebye"), string::npos);
}

TEST(Uci, test_go_move) {
  setup_std_mock_io();

  auto blaengine = make_shared<BlaEngine>();
  auto uci_module = Uci(blaengine);

  thread uci_com_thread(uci_module);

  mock_cin.str("go \nquit");

  sleep(RND_DELAY);
  string result_string[2];
  getline(mock_cout, result_string[0]);
  getline(mock_cout, result_string[1]);

  teardown_std_mock_io();
  uci_com_thread.join();

  ASSERT_NE(result_string[0].find("bestmove"), string::npos);
  ASSERT_NE(result_string[1].find("byebye"), string::npos);
}

TEST(Uci, test_go_thinking_info) {
  setup_std_mock_io();

  auto blaengine = make_shared<BlaEngine>();
  auto uci_module = Uci(blaengine);

  thread uci_com_thread(uci_module);

  mock_cin.str("go infinite\nquit");

  sleep(RND_DELAY);
  string result_string[2];
  getline(mock_cout, result_string[0]);
  getline(mock_cout, result_string[1]);

  teardown_std_mock_io();
  uci_com_thread.join();

  ASSERT_NE(result_string[0].find("info currmove"), string::npos);
  ASSERT_NE(result_string[1].find("byebye"), string::npos);
}

TEST(Uci, test_position_cmd) {
  setup_std_mock_io();

  auto blaengine = make_shared<BlaEngine>();
  auto uci_module = Uci(blaengine);

  thread uci_com_thread(uci_module);

  mock_cin.str("position startpos\nquit");

  sleep(RND_DELAY);
  string result_string[2];
  getline(mock_cout, result_string[0]);
  getline(mock_cout, result_string[1]);

  teardown_std_mock_io();
  uci_com_thread.join();

  ASSERT_NE(result_string[0].find("position was set"), string::npos);
  ASSERT_NE(result_string[1].find("byebye"), string::npos);
}

TEST(Uci, test_extract_game_state) {
  auto pgn_moves = vector<string>();
  auto calc_module = Calculator();
  auto blaengine = make_shared<BlaEngine>();
  auto uci_module = Uci(blaengine);
  ifstream file;
  file.open("mock_data/test_gamestates.txt");
  string test_string;

  if (file.is_open()) getline(file, test_string);
  auto gs_tuple1 = uci_module.extractGameState(test_string);
  ASSERT_EQ(get<0>(gs_tuple1),
            "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w - - 0 1");
  ASSERT_TRUE(get<1>(gs_tuple1).empty());

  getline(file, test_string);
  auto gs_tuple2 = uci_module.extractGameState(test_string);
  ASSERT_EQ(get<0>(gs_tuple2),
            "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w - - 0 1");
  ASSERT_TRUE(get<1>(gs_tuple2).empty());

  getline(file, test_string);
  auto gs_tuple3 = uci_module.extractGameState(test_string);
  ASSERT_EQ(get<0>(gs_tuple3),
            "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w - - 0 1");
  ASSERT_EQ(get<1>(gs_tuple3).size(), 63);

  getline(file, test_string);
  auto gs_tuple4 = uci_module.extractGameState(test_string);
  ASSERT_EQ(get<0>(gs_tuple4),
            "8/6pk/5pn1/1q5p/7P/3P2P1/4QP2/4N1K1 b - - 0 1");
  ASSERT_TRUE(get<1>(gs_tuple4).empty());

  getline(file, test_string);
  auto gs_tuple5 = uci_module.extractGameState(test_string);
  ASSERT_EQ(get<0>(gs_tuple5),
            "8/6pk/5pn1/1q5p/7P/3P2P1/4QP2/4N1K1 b - - 0 1");
  ASSERT_EQ(get<1>(gs_tuple5).size(), 6);

  file.close();
}
