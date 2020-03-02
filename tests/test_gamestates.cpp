#include "gtest/gtest.h"
#include "source/calculation/game_state.h"

using namespace blaengine::calculation;

TEST(Move, test_to_string1)
{
  auto move = Move();
  move.field_before = 11;
  move.field_after = 27;


  ASSERT_EQ(move.toString(), "d2d4");
}

TEST(Move, test_to_string2)
{
  auto move = Move();
  move.field_before = 0;
  move.field_after = 63;


  ASSERT_EQ(move.toString(), "a1h8");
}

TEST(Move, test_to_string3)
{
  auto move = Move();
  move.field_before = 0;
  move.field_after = 63;


  ASSERT_EQ(move.toString(), "a1h8");
}

TEST(Move, test_to_string4)
{
  auto move = Move();
  move.field_before = 50;
  move.field_after = 58;
  move.promotion=Piece::white_queen;


  ASSERT_EQ(move.toString(), "c7c8Q");
}

TEST(Move, test_to_string5)
{
  auto move = Move();
  move.field_before = 54;
  move.field_after = 62;
  move.promotion=Piece::black_queen;


  ASSERT_EQ(move.toString(), "g7g8q");
}
