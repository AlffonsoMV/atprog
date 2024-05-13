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

vector<vector<bool>> BacktrackingSolver::placeQueensOnce(int row) {
    vector<vector<bool>> b = {};
    if (row == board.getSize()) {
        return board.getBoard();
    }

    for (int col = 0; col < board.getSize(); col++) {
        if (board.isSafe(row, col)) {
            board.placeQueen(row, col);
            b = placeQueensOnce(row + 1);
            if (!b.empty()) return b;
            board.removeQueen(row, col);
        }
    }

    return {};
}


vector<vector<bool>> BacktrackingSolver::getRandomSolution() {
    return placeQueensOnce(0);
}


