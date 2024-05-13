#ifndef BACKTRACKINGSOLVER_H
#define BACKTRACKINGSOLVER_H

#include "../Solver.h"

class BacktrackingSolver : public Solver {
public:
    BacktrackingSolver(int n) : Solver(n) {}
    void solve() override;  // Override the solve function
    void placeQueens(int row);
    vector<vector<bool>> getRandomSolution() override;
    vector<vector<bool>> placeQueensOnce(int row);
};

#endif
