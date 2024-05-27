#include "MinConflictsSolver.h"
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

MinConflictsSolver::MinConflictsSolver(int n, int maxSteps)
        : Solver(n), maxSteps(maxSteps) {
    srand(static_cast<unsigned int>(time(0)));
}

void MinConflictsSolver::solve() {
    initializeSolution();

    int conflicts = 0;
    for (int step = 0; step < maxSteps; ++step) {
        conflicts = 0;
        for (int row = 0; row < board.getSize(); ++row) {
            conflicts += computeConflicts(row, currentSolution[row]);
        }
        if (conflicts == 0) {
            minConflictsBoard = currentSolution;
            totalMinConflicts = 0;

            std::cout << "Solution found:" << std::endl;
            printSolution();
            return;
        }

        int row = rand() % board.getSize();
        int minConflictCol = findMinConflictColumn(row);
        currentSolution[row] = minConflictCol;
    }

    minConflictsBoard = currentSolution;
    totalMinConflicts = conflicts/2;
    solutions = 0;

    std::cout << "No solution found within " << maxSteps << " steps. Best attempt ("<< conflicts/2 <<" conflicts):" << std::endl;
    printSolution();
}

void MinConflictsSolver::initializeSolution() {
    currentSolution.resize(board.getSize());
    for (int i = 0; i < board.getSize(); ++i) {
        currentSolution[i] = rand() % board.getSize();
    }
}

int MinConflictsSolver::computeConflicts(int row, int col) {
    int conflicts = 0;
    for (int i = 0; i < board.getSize(); ++i) {
        if (i == row) continue;
        int j = currentSolution[i];
        if (j == col || abs(j - col) == abs(i - row)) {
            conflicts++;
        }
    }
    return conflicts;
}

int MinConflictsSolver::findMinConflictColumn(int row) {
    int minConflicts = board.getSize();
    int bestCol = -1;
    for (int col = 0; col < board.getSize(); ++col) {
        int conflicts = computeConflicts(row, col);
        if (conflicts < minConflicts) {
            minConflicts = conflicts;
            bestCol = col;
        }
    }
    return bestCol;
}

void MinConflictsSolver::printSolution() {
    for (int i = 0; i < board.getSize(); ++i) {
        board.placeQueen(i, currentSolution[i]);
    }
    board.printBoard();
}