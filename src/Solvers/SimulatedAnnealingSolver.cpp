#include "SimulatedAnnealingSolver.h"
#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <ctime>

// Constructor: Initializes the solver with the given parameters and seeds the random number generator
SimulatedAnnealingSolver::SimulatedAnnealingSolver(int n, double initialTemp, double coolingRate)
        : Solver(n), initialTemp(initialTemp), coolingRate(coolingRate) {
    srand(static_cast<unsigned int>(time(0)));
}

// Main solving function that implements the Simulated Annealing algorithm
void SimulatedAnnealingSolver::solve() {
    initializeSolution(); // Initialize the solution
    double temperature = initialTemp; // Set initial temperature

    // Loop until temperature is greater than 1
    while (temperature > 1) {
        std::vector<int> newSolution = generateNeighbor(currentSolution); // Generate a neighbor solution
        int newCost = computeCost(newSolution); // Compute the cost of the new solution

        // Decide whether to accept the new solution based on acceptance probability
        if (acceptanceProbability(currentCost, newCost, temperature) > (static_cast<double>(rand()) / RAND_MAX)) {
            currentSolution = newSolution; // Accept the new solution
            currentCost = newCost; // Update the current cost
        }

        // Check if a perfect solution is found
        if (currentCost == 0) {
            minConflictsBoard = currentSolution; // Update the solution with minimal conflicts
            totalMinConflicts = getConflicts(currentSolution); // Get total conflicts
            std::cout << "Solution found:" << std::endl;
            printSolution(currentSolution); // Print the solution
            return;
        }

        temperature *= coolingRate; // Decrease the temperature
    }

    // If no perfect solution found, print the best attempt
    minConflictsBoard = currentSolution;
    totalMinConflicts = getConflicts(currentSolution);
    solutions = 0;

    std::cout << "No solution found. Best attempt ("<< totalMinConflicts <<" conflicts):" << std::endl;
    printSolution(currentSolution); // Print the best solution found
}

// Initialize the solution by generating a random permutation of the board indices
void SimulatedAnnealingSolver::initializeSolution() {
    currentSolution.resize(board.getSize());
    for (int i = 0; i < board.getSize(); ++i) {
        currentSolution[i] = i;
    }
    std::random_shuffle(currentSolution.begin(), currentSolution.end());
    currentCost = computeCost(currentSolution); // Compute initial cost
}

// Compute the cost of a given solution based on the number of conflicts
int SimulatedAnnealingSolver::computeCost(const std::vector<int>& solution) {
    int cost = 0;
    for (int i = 0; i < board.getSize(); ++i) {
        for (int j = i + 1; j < board.getSize(); ++j) {
            // Check for conflicts
            if (solution[i] == solution[j] || abs(solution[i] - solution[j]) == j - i) {
                ++cost;
            }
        }
    }
    return cost; // Return total cost
}

// Generate a neighbor solution by swapping two random elements
std::vector<int> SimulatedAnnealingSolver::generateNeighbor(const std::vector<int>& solution) {
    std::vector<int> neighbor = solution;
    int i = rand() % board.getSize();
    int j = rand() % board.getSize();
    std::swap(neighbor[i], neighbor[j]); // Swap two elements
    return neighbor; // Return the neighbor solution
}

// Calculate the acceptance probability for a new solution
double SimulatedAnnealingSolver::acceptanceProbability(int oldCost, int newCost, double temperature) {
    if (newCost < oldCost) {
        return 1.0; // Always accept if the new solution is better
    }
    return exp((oldCost - newCost) / temperature); // Calculate acceptance probability
}

// Print the solution on the board
void SimulatedAnnealingSolver::printSolution(const std::vector<int>& solution) {
    for (int i = 0; i < board.getSize(); ++i) {
        board.placeQueen(i, solution[i]);
    }
    board.printBoard(); // Print the board with the solution
}

// Get the number of conflicts in a given solution
int SimulatedAnnealingSolver::getConflicts(const std::vector<int>& solution) {
    int conflicts = 0;
    for (int i = 0; i < board.getSize(); ++i) {
        for (int j = i + 1; j < board.getSize(); ++j) {
            // Check for conflicts
            if (solution[i] == solution[j] || abs(solution[i] - solution[j]) == abs(j - i)) {
                ++conflicts;
            }
        }
    }
    return conflicts; // Return total number of conflicts
}
