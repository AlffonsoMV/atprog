#ifndef SOLVER_H
#define SOLVER_H

#include "Board.h"

class Solver {
protected:
    Board board;
    int solutions = 0;

public:
    Solver(int n) : board(n) {}
    virtual void solve() = 0;  // Make `solve` a pure virtual function
    virtual ~Solver() {}  // Virtual destructor for proper cleanup
};

#endif
