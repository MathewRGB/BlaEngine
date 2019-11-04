#include <thread>

#include "helper_for_tests.h"
#include "uci.h"

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

  sleep(1);
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

  sleep(1);
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

  sleep(1);
  string result_string[2];
  getline(mock_cout, result_string[0]);
  getline(mock_cout, result_string[1]);

  teardown_std_mock_io();
  uci_com_thread.join();

  ASSERT_EQ(result_string[0], "readyok");
  ASSERT_NE(result_string[1].find("byebye"), string::npos);
}
