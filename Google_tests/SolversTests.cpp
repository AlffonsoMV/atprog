#include "gtest/gtest.h"
#include "../src/Solvers/BacktrackingSolver.h"


class SolversFixture : public ::testing::Test {

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

TEST_F(SolversFixture, SolutionsOf8Queens){ // Expected 92 solutions
    Solver *solver1 = new BacktrackingSolver(8);
    EXPECT_EQ(solver1->getSolutions(),92);
    delete solver1;

    Solver *solver2 = new BacktrackingSolver(8);
    solver2->solve();
    EXPECT_EQ(solver2->getSolutions(),92);
    delete solver2;
}