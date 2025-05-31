#include <gtest/gtest.h>
#include "hello.h"

class MyTestFixture : public ::testing::Test {
protected:
    int common_value;

    void SetUp() override {
        common_value = 42;
    }
};

TEST_F(MyTestFixture, Test1) {
    EXPECT_EQ(common_value, 42);
}

TEST_F(MyTestFixture, Test2) {
    EXPECT_GT(common_value, 10);
}