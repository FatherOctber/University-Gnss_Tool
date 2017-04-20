#include "gtest/gtest.h"


namespace {
    class MicroserviceTest : public ::testing::Test
    {
    protected:
        void SetUp()
        {
        }

        void TearDown()
        {
        }
    };

    TEST_F( MicroserviceTest, example )
    {
        int a = 4 + 4;
        EXPECT_EQ(8,a);
    }
}
