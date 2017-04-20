#include "gtest/gtest.h"
#include "utils.h"

namespace {
    class UtilsTest : public ::testing::Test
    {
    protected:
        void SetUp()
        {
        }

        void TearDown()
        {
        }
    };

    TEST_F( UtilsTest, getTestNumber)
    {
        QString number = Utils::getSetting("test_number", QDir::currentPath()+"/test_res/test_settings.ini");
        EXPECT_EQ(1234, number.toInt());
    }

    TEST_F( UtilsTest, getTestMessage)
    {
        QString message = Utils::getSetting("test_message", QDir::currentPath()+"/test_res/test_settings.ini");
        EXPECT_EQ("the_test_message", message);
    }
}
