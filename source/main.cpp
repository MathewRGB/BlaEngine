#include <thread>

#include "blaengine.h"
#include "uci.h"
#include <unistd.h>

using BlaEngine = blaengine::BlaEngine;
using Uci = blaengine::communication::Uci;

int main(int argc, char *argv[])
{
  ushort searching_depth = (argc == 2) ? stoi(argv[1]) : 2;
  auto blaengine = make_shared<BlaEngine>(searching_depth);
  auto uci_module = Uci(blaengine);

  thread uci_com_thread(uci_module);

  uci_com_thread.join();

  return 0;
}