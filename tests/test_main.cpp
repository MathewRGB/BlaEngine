#include <iostream>
#include "gtest/gtest.h"

#include "test_blaengine.cpp"
#include "test_uci.cpp"
#include "test_uci_cin(disabled).cpp"
#include "test_gstate_translator.cpp"
#include "test_movegenerator.cpp"
#include "test_gamestates.cpp"
#include "test_moves_pawn.cpp"
#include "test_moves_knight.cpp"
#include "test_moves_rook.cpp"
#include "test_moves_bishop.cpp"
#include "test_moves_queen.cpp"
#include "test_moves_king.cpp"
#include "test_evaluator.cpp"

using namespace std;

// This is the main entry point for our google-test files. gtest.h has to be
// included and additionally all .cpp files you want to be tested.
int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}