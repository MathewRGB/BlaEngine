#include "blaengine.h"

using BlaEngine = blaengine::BlaEngine;

int main()
{
  auto blaengine = new BlaEngine();

  blaengine->StartEngine();
  blaengine->~BlaEngine();

  return 0;
}