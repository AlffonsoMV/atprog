#include "src/Solvers/GeneticSolver.h"
#include <iostream>

int main() {
    int n;
    std::cout << "Enter the size of the board: ";
    std::cin >> n;

    Solver* solver = new GeneticSolver(n, 100, 100, 0.9);
    solver->solve();

    delete solver;

    return 0;
}
