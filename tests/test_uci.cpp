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

TEST(Uci, test_quit) {
  setup_std_mock_io();

  auto blaengine = make_shared<BlaEngine>();
  auto uci_module = Uci(blaengine);

  thread uci_com_thread(uci_module);

  mock_cin.str("quit");

  sleep(1);
  string result_cout;
  getline(mock_cout, result_cout);

  
  teardown_std_mock_io();
  uci_com_thread.join();

  ASSERT_TRUE(result_cout == "BlaEngine says byebye");
}
