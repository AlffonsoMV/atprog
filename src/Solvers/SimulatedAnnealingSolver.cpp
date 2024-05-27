#include "SimulatedAnnealingSolver.h"
#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <ctime>

SimulatedAnnealingSolver::SimulatedAnnealingSolver(int n, double initialTemp, double coolingRate)
        : Solver(n), initialTemp(initialTemp), coolingRate(coolingRate) {
    srand(static_cast<unsigned int>(time(0)));
}

void SimulatedAnnealingSolver::solve() {
    initializeSolution();
    double temperature = initialTemp;

    while (temperature > 1) {
        std::vector<int> newSolution = generateNeighbor(currentSolution);
        int newCost = computeCost(newSolution);

        if (acceptanceProbability(currentCost, newCost, temperature) > (static_cast<double>(rand()) / RAND_MAX)) {
            currentSolution = newSolution;
            currentCost = newCost;
        }

        if (currentCost == 0) {
            minConflictsBoard = currentSolution;
            totalMinConflicts = getConflicts(currentSolution);
            std::cout << "Solution found:" << std::endl;
            printSolution(currentSolution);
            return;
        }

        temperature *= coolingRate;
    }

    minConflictsBoard = currentSolution;
    totalMinConflicts = getConflicts(currentSolution);
    solutions = 0;

    std::cout << "No solution found. Best attempt ("<< totalMinConflicts <<" conflicts):" << std::endl;
    printSolution(currentSolution);
}

void SimulatedAnnealingSolver::initializeSolution() {
    currentSolution.resize(board.getSize());
    for (int i = 0; i < board.getSize(); ++i) {
        currentSolution[i] = i;
    }
    std::random_shuffle(currentSolution.begin(), currentSolution.end());
    currentCost = computeCost(currentSolution);
}

int SimulatedAnnealingSolver::computeCost(const std::vector<int>& solution) {
    int cost = 0;
    for (int i = 0; i < board.getSize(); ++i) {
        for (int j = i + 1; j < board.getSize(); ++j) {
            if (solution[i] == solution[j] || abs(solution[i] - solution[j]) == j - i) {
                ++cost;
            }
        }
    }
    return cost;
}

std::vector<int> SimulatedAnnealingSolver::generateNeighbor(const std::vector<int>& solution) {
    std::vector<int> neighbor = solution;
    int i = rand() % board.getSize();
    int j = rand() % board.getSize();
    std::swap(neighbor[i], neighbor[j]);
    return neighbor;
}

double SimulatedAnnealingSolver::acceptanceProbability(int oldCost, int newCost, double temperature) {
    if (newCost < oldCost) {
        return 1.0;
    }
    return exp((oldCost - newCost) / temperature);
}

void SimulatedAnnealingSolver::printSolution(const std::vector<int>& solution) {
    for (int i = 0; i < board.getSize(); ++i) {
        board.placeQueen(i, solution[i]);
    }
    board.printBoard();
}

int SimulatedAnnealingSolver::getConflicts(const std::vector<int>& solution) {
    int conflicts = 0;
    for (int i = 0; i < board.getSize(); ++i) {
        for (int j = i + 1; j < board.getSize(); ++j) {
            if (solution[i] == solution[j] || abs(solution[i] - solution[j]) == abs(j - i)) {
                ++conflicts;
            }
        }
    }
    return conflicts;
}
