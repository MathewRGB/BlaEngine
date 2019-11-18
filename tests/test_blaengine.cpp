#include "gtest/gtest.h"
#include "blaengine.h"

using namespace blaengine;

TEST(BlaEngineInfo, test_info_content)
{
  auto blaengineInfo = BlaEngineInfo();

  ASSERT_EQ(blaengineInfo.name, ENGINE_NAME);
  ASSERT_EQ(blaengineInfo.author, AUTHOR);
  ASSERT_NE(blaengineInfo.version, "unversioned");
}

TEST(BlaEngine, test_get_info)
{
  auto blaengine = new BlaEngine();
  auto blaengineInfo = blaengine->getEngineInfo();

  ASSERT_EQ(blaengineInfo.name, ENGINE_NAME);
  ASSERT_EQ(blaengineInfo.author, AUTHOR);
  ASSERT_NE(blaengineInfo.version, "unversioned");

  blaengine->~BlaEngine();
}