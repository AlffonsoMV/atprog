#ifndef MINCONFLICTSSOLVER_H
#define MINCONFLICTSSOLVER_H

#include "../Solver.h"
#include <vector>

class MinConflictsSolver : public Solver {
public:
    MinConflictsSolver(int n, int maxSteps);
    void solve() override;  // Override the solve function

private:
    int maxSteps;
    std::vector<int> currentSolution;

    void initializeSolution();
    int computeConflicts(int row, int col);
    int findMinConflictColumn(int row);
    void printSolution();
};

#endif