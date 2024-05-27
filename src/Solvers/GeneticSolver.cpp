#include "GeneticSolver.h"
#include <iostream>
#include <algorithm>
#include <random>
#include <ctime>

// Constructor: Initializes the solver with the given parameters and seeds the random number generator
GeneticSolver::GeneticSolver(int n, int populationSize, int maxGenerations, double mutationRate)
        : Solver(n), populationSize(populationSize), generations(maxGenerations), mutationRate(mutationRate) {
    srand(static_cast<unsigned int>(time(0)));
}

// Main solving function that implements the Genetic Algorithm
void GeneticSolver::solve() {
    initializePopulation(); // Initialize the population
    int minConflicts = board.getSize();
    std::vector<int> bestSolution = population[0];

    // Evolve the population over a number of generations
    for (int gen = 0; gen < generations; ++gen) {
        evolvePopulation(); // Evolve the population

        // Evaluate the fitness of each individual in the population
        for (const auto& individual : population) {
            int conflicts = getConflicts(individual);
            // Update the best solution found
            if (conflicts < minConflicts) {
                minConflicts = conflicts;
                bestSolution = individual;
            }
            // Check if a solution with no conflicts is found
            if (isSolution(individual)) {
                minConflictsBoard = individual;
                totalMinConflicts = 0;

                std::cout << "Solution found in generation " << gen + 1 << ": " << std::endl;
                printIndividual(individual); // Print the solution
                return;
            }
        }
    }

    // If no solution found, print the best attempt
    solutions = 0;
    minConflictsBoard = bestSolution;
    totalMinConflicts = minConflicts;

    std::cout << "No solution found after " << generations << " generations. Best attempt (" << minConflicts << " conflicts):" << std::endl;
    printIndividual(bestSolution); // Print the best solution found
}

// Initialize the population with random individuals
void GeneticSolver::initializePopulation() {
    population.clear();
    for (int i = 0; i < populationSize; ++i) {
        population.push_back(createIndividual());
    }
}

// Create a single individual with a random permutation of the board indices
std::vector<int> GeneticSolver::createIndividual() {
    std::vector<int> individual(board.getSize());
    std::iota(individual.begin(), individual.end(), 0); // Fill with 0, 1, ..., n-1
    std::random_shuffle(individual.begin(), individual.end()); // Shuffle to create a random permutation
    return individual;
}

// Evolve the population by selecting parents, performing crossover, and applying mutations
void GeneticSolver::evolvePopulation() {
    std::vector<std::vector<int>> newPopulation;
    while (newPopulation.size() < populationSize) {
        auto parents = selectParents(); // Select parents
        auto offspring1 = crossover(parents.first, parents.second); // Perform crossover
        auto offspring2 = crossover(parents.second, parents.first); // Perform crossover
        mutate(offspring1); // Apply mutation
        mutate(offspring2); // Apply mutation
        newPopulation.push_back(offspring1); // Add offspring to the new population
        newPopulation.push_back(offspring2); // Add offspring to the new population
    }
    population = std::move(newPopulation); // Replace the old population with the new population
}

// Select two parents from the population using a fitness-proportionate selection method
std::pair<std::vector<int>, std::vector<int>> GeneticSolver::selectParents() {
    std::vector<int> fitnessScores(populationSize);
    for (int i = 0; i < populationSize; ++i) {
        fitnessScores[i] = fitness(population[i]); // Compute fitness for each individual
    }
    std::discrete_distribution<> dist(fitnessScores.begin(), fitnessScores.end()); // Create a distribution based on fitness
    std::mt19937 gen(rand());
    int parent1Index = dist(gen); // Select first parent
    int parent2Index = dist(gen); // Select second parent
    return { population[parent1Index], population[parent2Index] };
}

// Perform crossover between two parents to produce a child
std::vector<int> GeneticSolver::crossover(const std::vector<int>& parent1, const std::vector<int>& parent2) {
    std::vector<int> child(board.getSize(), -1);
    int crossoverPoint = rand() % board.getSize(); // Determine crossover point

    // Copy first part from parent1
    for (int i = 0; i < crossoverPoint; ++i) {
        child[i] = parent1[i];
    }

    // Fill remaining part from parent2 ensuring no duplicates
    for (int i = crossoverPoint; i < board.getSize(); ++i) {
        if (std::find(child.begin(), child.end(), parent2[i]) == child.end()) {
            child[i] = parent2[i];
        } else {
            for (int j = 0; j < board.getSize(); ++j) {
                if (std::find(child.begin(), child.end(), j) == child.end()) {
                    child[i] = j;
                    break;
                }
            }
        }
    }
    return child;
}

// Apply mutation to an individual by randomly swapping elements
void GeneticSolver::mutate(std::vector<int>& individual) {
    for (int i = 0; i < board.getSize(); ++i) {
        if (static_cast<double>(rand()) / RAND_MAX < mutationRate) {
            int swapIndex = rand() % board.getSize();
            std::swap(individual[i], individual[swapIndex]);
        }
    }
}

// Compute the fitness of an individual based on the number of non-attacking pairs of queens
int GeneticSolver::fitness(const std::vector<int>& individual) {
    int nonAttackingPairs = 0;
    for (int i = 0; i < board.getSize(); ++i) {
        for (int j = i + 1; j < board.getSize(); ++j) {
            if (individual[i] != individual[j] && abs(individual[i] - individual[j]) != j - i) {
                ++nonAttackingPairs;
            }
        }
    }
    return nonAttackingPairs; // Return the fitness score
}

// Check if an individual is a solution (i.e., has no conflicts)
bool GeneticSolver::isSolution(const std::vector<int>& individual) {
    return fitness(individual) == (board.getSize() * (board.getSize() - 1)) / 2;
}

// Print the individual's board configuration
void GeneticSolver::printIndividual(const std::vector<int>& individual) {
    for (int i = 0; i < board.getSize(); ++i) {
        board.placeQueen(i, individual[i]);
    }
    board.printBoard(); // Print the board with the individual's configuration
}

// Get the number of conflicts in a given solution
int GeneticSolver::getConflicts(const std::vector<int>& solution) {
    int conflicts = 0;
    for (int i = 0; i < board.getSize(); ++i) {
        for (int j = i + 1; j < board.getSize(); ++j) {
            if (solution[i] == solution[j] || abs(solution[i] - solution[j]) == abs(j - i)) {
                ++conflicts;
            }
        }
    }
    return conflicts; // Return the total number of conflicts
}
