// test_whatever.cpp
//
// Created on: Jan 27, 2019
//     Author: Mathias Kuhlmey

#include "helper_for_tests.h"

// dummy test
TEST(Whatever, whatevertest)
{
  float value = 0;

  ASSERT_TRUE(value == 0);
}