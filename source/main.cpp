#include <thread>

#include "blaengine.h"
#include "uci.h"
#include <unistd.h>

using BlaEngine = blaengine::BlaEngine;
using Uci = blaengine::communication::Uci;

int main()
{
  auto blaengine = make_shared<BlaEngine>(5);
  auto uci_module = Uci(blaengine);

  thread uci_com_thread(uci_module);

  uci_com_thread.join();

  return 0;
}