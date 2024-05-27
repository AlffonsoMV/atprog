#include "BacktrackingSolver.h"
#include <iostream>

// Main solving function that uses Backtracking to find all solutions
void BacktrackingSolver::solve() {
    solutions = 0; // Initialize the number of solutions found
    placeQueens(0); // Start placing queens from the first row

    totalMinConflicts = 0; // No conflicts in a valid solution

    std::cout << "Total solutions using Backtracking: " << solutions << std::endl; // Print the total number of solutions found
}

// Recursive function to place queens on the board
void BacktrackingSolver::placeQueens(int row) {
    // If all rows are filled, a solution is found
    if (row == board.getSize()) {
        board.printBoard(); // Print the current board configuration
        minConflictsBoard = std::vector<int>(board.getSize(), -1);
        for (int i = 0; i < board.getSize(); i++) {
            minConflictsBoard[i] = board.getRow(i); // Store the solution
        }
        std::cout << "Solution found." << std::endl;
        solutions++; // Increment the number of solutions found
        return;
    }

    // Try placing a queen in each column of the current row
    for (int col = 0; col < board.getSize(); col++) {
        if (board.isSafe(row, col)) { // Check if placing a queen here is safe
            board.placeQueen(row, col); // Place the queen
            placeQueens(row + 1); // Recur to place queens in the next row
            board.removeQueen(row, col); // Backtrack: remove the queen
        }
    }
}
