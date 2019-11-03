#include "helper_for_tests.h"
#include "blaengine.h"

using namespace blaengine;

TEST(BlaEngineInfo, test_info_content)
{
  auto blaengineInfo = BlaEngineInfo();

  ASSERT_TRUE(blaengineInfo.name == ENGINE_NAME);
  ASSERT_TRUE(blaengineInfo.author == AUTHOR);
  ASSERT_FALSE(blaengineInfo.version == "unversioned");
}

TEST(BlaEngine, test_get_info)
{
  auto blaengine = new BlaEngine();
  auto blaengineInfo = blaengine->getEngineInfo();

  ASSERT_TRUE(blaengineInfo.name == ENGINE_NAME);
  ASSERT_TRUE(blaengineInfo.author == AUTHOR);
  ASSERT_FALSE(blaengineInfo.version == "unversioned");

  blaengine->~BlaEngine();
}