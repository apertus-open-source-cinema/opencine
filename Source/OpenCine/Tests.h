#ifndef TESTS_H
#define TESTS_H

#define CATCH_CONFIG_RUNNER
#include "catch.hpp"

#include "IDataTransfer.h"

void RunUnitTests()
{
    int result = Catch::Session().run();
}

TEST_CASE( "File copying and MD5 check", "[General]" )
{
    IDataTransfer* dataTransfer = new DriveTransfer();

    int checkSum = 0;
    REQUIRE( checkSum == 123);
}

enum class TestEnum
{
    Idle,
    Acceleration
};

TestEnum TestFunc()
{
    return TestEnum::Acceleration;
}

TEST_CASE( "Check C++11 enum", "[enum]" )
{
    REQUIRE( TestFunc() == TestEnum::Idle );
}

#endif // TESTS_H

