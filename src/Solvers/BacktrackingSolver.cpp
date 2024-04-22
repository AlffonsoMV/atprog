#include "BacktrackingSolver.h"
#include <iostream>

void BacktrackingSolver::solve() {
    solutions = 0;
    placeQueens(0);
    std::cout << "Total solutions using Backtracking: " << solutions << std::endl;
}

void BacktrackingSolver::placeQueens(int row) {
    if (row == board.getSize()) {
        board.printBoard();
        std::cout << "Solution found." << std::endl;
        solutions++;
        return;
    }

    for (int col = 0; col < board.getSize(); col++) {
        if (board.isSafe(row, col)) {
            board.placeQueen(row, col);
            placeQueens(row + 1);
            board.removeQueen(row, col);
        }
    }
}

