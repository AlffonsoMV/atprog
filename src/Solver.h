#ifndef SOLVER_H
#define SOLVER_H

#include "Board.h"

class Solver {
protected:
    Board board;
    int solutions = -1;

public:
    Solver(int n) : board(n) {}
    virtual void solve() = 0;  // Make `solve` a pure virtual function
    virtual ~Solver() {}  // Virtual destructor for proper cleanup

    virtual vector<vector<bool>> getRandomSolution() = 0;

    int getSolutions() { if (solutions != -1 ) return solutions; else { solve(); return solutions; } }
};

#endif
