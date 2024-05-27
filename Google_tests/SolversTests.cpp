#include "gtest/gtest.h"
#include "../src/Solvers/BacktrackingSolver.h"
#include "../src/Solvers/SimulatedAnnealingSolver.h"
#include "../src/Solvers/GeneticSolver.h"
#include "../src/Solvers/MinConflictsSolver.h"


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

// Backtracking Solver Tests

TEST_F(SolversFixture, BacktrackingSolver_4Queens) {
    Solver *solver = new BacktrackingSolver(4);
    solver->solve();
    EXPECT_EQ(solver->getSolutions(), 2); // 4-Queens problem has 2 solutions
    delete solver;
}

TEST_F(SolversFixture, BacktrackingSolver_8Queens) {
    Solver *solver = new BacktrackingSolver(8);
    solver->solve();
    EXPECT_EQ(solver->getSolutions(), 92); // 8-Queens problem has 92 solutions
    delete solver;
}

TEST_F(SolversFixture, BacktrackingSolver_2Queens) {
    Solver *solver = new BacktrackingSolver(2);
    solver->solve();
    EXPECT_EQ(solver->getSolutions(), 0); // 2-Queens problem has no solution
    delete solver;
}

TEST_F(SolversFixture, BacktrackingSolver_3Queens) {
    Solver *solver = new BacktrackingSolver(3);
    solver->solve();
    EXPECT_EQ(solver->getSolutions(), 0); // 3-Queens problem has no solution
    delete solver;
}

// Simulated Annealing Solver Tests

TEST_F(SolversFixture, SimulatedAnnealingSolver_4Queens) {
    Solver *solver = new SimulatedAnnealingSolver(4, 1000, 0.95);
    solver->solve();
    EXPECT_LT(solver->getMinConflicts(), 2);
    delete solver;
}

TEST_F(SolversFixture, SimulatedAnnealingSolver_8Queens) {
    Solver *solver = new SimulatedAnnealingSolver(8, 1000, 0.95);
    solver->solve();
    EXPECT_LT(solver->getMinConflicts(), 4);
    delete solver;
}

TEST_F(SolversFixture, SimulatedAnnealingSolver_2Queens) {
    Solver *solver = new SimulatedAnnealingSolver(2, 1000, 0.95);
    solver->solve();
    EXPECT_EQ(solver->getSolutions(), 0); // No solution exists
    delete solver;
}

TEST_F(SolversFixture, SimulatedAnnealingSolver_3Queens) {
    Solver *solver = new SimulatedAnnealingSolver(3, 1000, 0.95);
    solver->solve();
    EXPECT_EQ(solver->getSolutions(), 0); // No solution exists
    delete solver;
}

// Genetic Algorithm Solver Tests

TEST_F(SolversFixture, GeneticAlgorithmSolver_4Queens) {
    Solver *solver = new GeneticSolver(4, 100, 1000, 0.99);
    solver->solve();
    EXPECT_LT(solver->getMinConflicts(), 2);
    delete solver;
}

TEST_F(SolversFixture, GeneticAlgorithmSolver_8Queens) {
    Solver *solver = new GeneticSolver(8, 100, 1000, 0.99);
    solver->solve();
    EXPECT_LT(solver->getMinConflicts(), 2);
    delete solver;
}

TEST_F(SolversFixture, GeneticAlgorithmSolver_2Queens) {
    Solver *solver = new GeneticSolver(2, 100, 1000, 0.99);
    solver->solve();
    EXPECT_LT(solver->getMinConflicts(), 2);
    delete solver;
}

TEST_F(SolversFixture, GeneticAlgorithmSolver_3Queens) {
    Solver *solver = new GeneticSolver(3, 100, 1000, 0.99);
    solver->solve();
    EXPECT_LT(solver->getMinConflicts(), 2);
    delete solver;
}

// Min Conflicts Algorithm Solver Tests

TEST_F(SolversFixture, MinConflictsSolver_2Queens) {
    Solver *solver = new MinConflictsSolver(2, 1000);
    solver->solve();
    EXPECT_EQ(solver->getSolutions(), 0); // 2-Queens problem has no solution
    delete solver;
}

TEST_F(SolversFixture, MinConflictsSolver_4Queens) {
    Solver *solver = new MinConflictsSolver(4, 1000);
    solver->solve();
    EXPECT_LT(solver->getMinConflicts(), 2);
    delete solver;
}

TEST_F(SolversFixture, MinConflictsSolver_8Queens) {
    Solver *solver = new MinConflictsSolver(8, 1000);
    solver->solve();
    EXPECT_LT(solver->getMinConflicts(), 3);
    delete solver;
}

TEST_F(SolversFixture, MinConflictsSolver_20Queens) {
    Solver *solver = new MinConflictsSolver(20, 1000);
    solver->solve();
    EXPECT_LT(solver->getMinConflicts(), 6);
    delete solver;
}

