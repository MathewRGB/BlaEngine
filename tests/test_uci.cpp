#include <thread>

#include "helper_for_tests.h"
#include "blaengine.h"
#include "uci.h"


using namespace blaengine;
using namespace blaengine::communication;

TEST(Uci, test_quit)
{
  auto blaengine = make_shared<BlaEngine>();
  auto uci_module = Uci(blaengine);

  thread uci_com_thread(uci_module);

  uci_com_thread.join();
}
