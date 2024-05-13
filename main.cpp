#include "src/Solvers/BacktrackingSolver.h"
#include <iostream>

int main() {
    int n;
    std::cout << "Enter the size of the board: ";

    std::cin >> n;

    Solver *solver = new BacktrackingSolver(n);

    vector<vector<bool>> b = solver->getRandomSolution();
    std::cout << "Random board:" << std::endl;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            std::cout << (b[i][j] ? "Q " : ". ");
        std::cout << std::endl;
    }


    delete solver;



    return 0;
}
