#include "gtest/gtest.h"

class UtilsFixture : public ::testing::Test {

protected:
    virtual void SetUp()
    {
        testing = 1;
    }

    virtual void TearDown() {
        // delete hola;
    }

    int testing;
};

TEST_F(UtilsFixture, FirstDayEver){ // 1/1/1 -> 1/3/1
    testing += 1;

    EXPECT_EQ(testing,2);

}