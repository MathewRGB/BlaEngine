#include "blaengine.h"

using BlaEngine = blaengine::BlaEngine;

int main()
{
  auto blaengine = new BlaEngine();

  blaengine->startEngine();
  blaengine->~BlaEngine();

  return 0;
}