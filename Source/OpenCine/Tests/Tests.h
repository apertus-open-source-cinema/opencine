#ifndef TESTS_H
#define TESTS_H

#include "DataTransferTests.h"

void RunUnitTests()
{
    Catch::Session().run();
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

