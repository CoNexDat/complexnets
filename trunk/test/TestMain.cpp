
#include <gtest/gtest.h>
//#include <gmock/gmock.h>

namespace
{
int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    ::testing::GTEST_FLAG(throw_on_failure) = true;
    //::testing::InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
}
}