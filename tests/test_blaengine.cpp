#include "helper_for_tests.h"
#include "blaengine.h"

using namespace blaengine;

TEST(BlaEngineInfo, test_info_content)
{
  auto blaengineInfo = new BlaEngineInfo;

  ASSERT_TRUE(blaengineInfo->name == ENGINE_NAME);
  ASSERT_TRUE(blaengineInfo->author == AUTHOR);
  ASSERT_FALSE(blaengineInfo->version == "unversioned");
}