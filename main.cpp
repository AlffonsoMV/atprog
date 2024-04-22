#include "src/Solvers/BacktrackingSolver.h"
#include <iostream>

int main() {
    int n;
    std::cout << "Enter the size of the board: ";
    std::cin >> n;

    Solver *solver = new BacktrackingSolver(n);
    solver->solve();
    delete solver;

    return 0;
}
