#include "blaengine.h"

using BlaEngine = blaengine::BlaEngine;

int main(int argc, char **argv)
{
  auto blaengine = new BlaEngine();

  blaengine->StartEngine();
  blaengine->~BlaEngine();

  return 0;
}