#include <iostream>
#include "gtest/gtest.h"

#include "test_blaengine.cpp"
#include "test_uci.cpp"

// This is the main entry point for our google-test files. gtest.h has to be
// included and additionally all .cpp files you want to be tested.
int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}