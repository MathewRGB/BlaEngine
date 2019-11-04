#include <thread>

#include "helper_for_tests.h"
#include "uci.h"

using namespace blaengine;
using namespace blaengine::communication;

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

  ASSERT_TRUE(result_string.find("byebye") != string::npos);
}

TEST(Uci, test_uci_call) {
  setup_std_mock_io();

  auto blaengine = make_shared<BlaEngine>();
  auto uci_module = Uci(blaengine);

  thread uci_com_thread(uci_module);

  mock_cin.str("uci\nquit");

  sleep(1);
  string result_string_name, result_string_author, result_string_uciok;
  getline(mock_cout, result_string_name);
  getline(mock_cout, result_string_author);
  getline(mock_cout, result_string_uciok);

  teardown_std_mock_io();
  uci_com_thread.join();

  ASSERT_TRUE(result_string_name.find("id name") != string::npos);
  ASSERT_TRUE(result_string_author.find("id author") != string::npos);
  ASSERT_TRUE(result_string_uciok.find("uciok") != string::npos);
}
