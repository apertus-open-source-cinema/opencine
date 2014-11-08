#include "FFmpegDataProvider.h"

#define CATCH_CONFIG_RUNNER
#include <catch.hpp>

enum class TestEnum
{
  Idle,
  Acceleration
};

//std::ostream& operator<<( std::ostream& os, const TestEnum& item )
//{
//  os << static_cast<std::underlying_type<TestEnum>::type>(item);
//  return os;
//}

TestEnum TestFunc()
{
  return TestEnum::Acceleration;
}

TEST_CASE( "Check C++11 enum", "[enum]" )
{
  REQUIRE( TestFunc() == TestEnum::Idle );
}

void TestCatch()
{
  int result = Catch::Session().run(/* argc, argv */);
}
