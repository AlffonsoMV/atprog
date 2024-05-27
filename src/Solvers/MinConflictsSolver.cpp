#include "MinConflictsSolver.h"
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

// Constructor: Initializes the solver with the given parameters and seeds the random number generator
MinConflictsSolver::MinConflictsSolver(int n, int maxSteps)
        : Solver(n), maxSteps(maxSteps) {
    srand(static_cast<unsigned int>(time(0)));
}

// Main solving function that implements the Min-Conflicts algorithm
void MinConflictsSolver::solve() {
    initializeSolution(); // Initialize the solution

    int conflicts = 0;
    for (int step = 0; step < maxSteps; ++step) {
        conflicts = 0;
        // Calculate the total number of conflicts in the current solution
        for (int row = 0; row < board.getSize(); ++row) {
            conflicts += computeConflicts(row, currentSolution[row]);
        }
        // Check if a solution with no conflicts is found
        if (conflicts == 0) {
            minConflictsBoard = currentSolution; // Update the solution with minimal conflicts
            totalMinConflicts = 0;

            std::cout << "Solution found:" << std::endl;
            printSolution(); // Print the solution
            return;
        }

        // Choose a random row and find the column with the minimum conflicts for that row
        int row = rand() % board.getSize();
        int minConflictCol = findMinConflictColumn(row);
        currentSolution[row] = minConflictCol; // Update the solution with the column of minimum conflicts
    }

    // If no solution found, print the best attempt
    minConflictsBoard = currentSolution;
    totalMinConflicts = conflicts / 2;
    solutions = 0;

    std::cout << "No solution found within " << maxSteps << " steps. Best attempt (" << conflicts / 2 << " conflicts):" << std::endl;
    printSolution(); // Print the best solution found
}

// Initialize the solution by randomly placing queens in each row
void MinConflictsSolver::initializeSolution() {
    currentSolution.resize(board.getSize());
    for (int i = 0; i < board.getSize(); ++i) {
        currentSolution[i] = rand() % board.getSize();
    }
}

// Compute the number of conflicts for a queen placed at a specific row and column
int MinConflictsSolver::computeConflicts(int row, int col) {
    int conflicts = 0;
    for (int i = 0; i < board.getSize(); ++i) {
        if (i == row) continue;
        int j = currentSolution[i];
        // Check for conflicts
        if (j == col || abs(j - col) == abs(i - row)) {
            conflicts++;
        }
    }
    return conflicts; // Return total number of conflicts
}

// Find the column with the minimum conflicts for a given row
int MinConflictsSolver::findMinConflictColumn(int row) {
    int minConflicts = board.getSize();
    int bestCol = -1;
    for (int col = 0; col < board.getSize(); ++col) {
        int conflicts = computeConflicts(row, col);
        // Update the best column if the current column has fewer conflicts
        if (conflicts < minConflicts) {
            minConflicts = conflicts;
            bestCol = col;
        }
    }
    return bestCol; // Return the column with the minimum conflicts
}

// Print the solution on the board
void MinConflictsSolver::printSolution() {
    for (int i = 0; i < board.getSize(); ++i) {
        board.placeQueen(i, currentSolution[i]);
    }
    board.printBoard(); // Print the board with the solution
}
