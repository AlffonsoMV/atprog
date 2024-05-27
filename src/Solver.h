#ifndef SOLVER_H
#define SOLVER_H

#include "Board.h"

class Solver {
protected:
    Board board;
    int solutions = -1;
    int totalMinConflicts = 800;
    vector<int> minConflictsBoard = {};

public:
    Solver(int n) : board(n) {}
    virtual void solve() = 0;  // Make `solve` a pure virtual function
    virtual ~Solver() {}  // Virtual destructor for proper cleanup

    int getSolutions() { if (solutions != -1 ) return solutions; else { solve(); return solutions; } }
    int getMinConflicts() { return totalMinConflicts; }
    vector<int> getMinConflictsBoard() { return minConflictsBoard; }
};

#endif
