#include "GeneticSolver.h"
#include <iostream>
#include <algorithm>
#include <random>
#include <ctime>

GeneticSolver::GeneticSolver(int n, int populationSize, int maxGenerations, double mutationRate)
        : Solver(n), populationSize(populationSize), generations(maxGenerations), mutationRate(mutationRate) {
    srand(static_cast<unsigned int>(time(0)));
}

void GeneticSolver::solve() {
    initializePopulation();
    int minConflicts = board.getSize();
    vector<int> bestSolution = population[0];
    for (int gen = 0; gen < generations; ++gen) {
        evolvePopulation();
        for (const auto& individual : population) {
            int conflicts = getConflicts(individual);
            if (conflicts < minConflicts) {
                minConflicts = conflicts;
                bestSolution = individual;
            }
            if (isSolution(individual)) {
                minConflictsBoard = individual;
                totalMinConflicts = 0;

                std::cout << "Solution found in generation " << gen + 1 << ": " << std::endl;
                printIndividual(individual);
                return;
            }
        }
    }

    solutions = 0;

    minConflictsBoard = bestSolution;
    totalMinConflicts = minConflicts;

    std::cout << "No solution found after " << generations << " generations. Best attempt ("<< minConflicts <<" conflicts):" << std::endl;
    printIndividual(bestSolution);
}

void GeneticSolver::initializePopulation() {
    population.clear();
    for (int i = 0; i < populationSize; ++i) {
        population.push_back(createIndividual());
    }
}

std::vector<int> GeneticSolver::createIndividual() {
    std::vector<int> individual(board.getSize());
    std::iota(individual.begin(), individual.end(), 0);
    std::random_shuffle(individual.begin(), individual.end());
    return individual;
}

void GeneticSolver::evolvePopulation() {
    std::vector<std::vector<int>> newPopulation;
    while (newPopulation.size() < populationSize) {
        auto parents = selectParents();
        auto offspring1 = crossover(parents.first, parents.second);
        auto offspring2 = crossover(parents.second, parents.first);
        mutate(offspring1);
        mutate(offspring2);
        newPopulation.push_back(offspring1);
        newPopulation.push_back(offspring2);
    }
    population = std::move(newPopulation);
}

std::pair<std::vector<int>, std::vector<int>> GeneticSolver::selectParents() {
    std::vector<int> fitnessScores(populationSize);
    for (int i = 0; i < populationSize; ++i) {
        fitnessScores[i] = fitness(population[i]);
    }
    std::discrete_distribution<> dist(fitnessScores.begin(), fitnessScores.end());
    std::mt19937 gen(rand());
    int parent1Index = dist(gen);
    int parent2Index = dist(gen);
    return { population[parent1Index], population[parent2Index] };
}

std::vector<int> GeneticSolver::crossover(const std::vector<int>& parent1, const std::vector<int>& parent2) {
    std::vector<int> child(board.getSize(), -1);
    int crossoverPoint = rand() % board.getSize();
    for (int i = 0; i < crossoverPoint; ++i) {
        child[i] = parent1[i];
    }
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

void GeneticSolver::mutate(std::vector<int>& individual) {
    for (int i = 0; i < board.getSize(); ++i) {
        if (static_cast<double>(rand()) / RAND_MAX < mutationRate) {
            int swapIndex = rand() % board.getSize();
            std::swap(individual[i], individual[swapIndex]);
        }
    }
}

int GeneticSolver::fitness(const std::vector<int>& individual) {
    int nonAttackingPairs = 0;
    for (int i = 0; i < board.getSize(); ++i) {
        for (int j = i + 1; j < board.getSize(); ++j) {
            if (individual[i] != individual[j] && abs(individual[i] - individual[j]) != j - i) {
                ++nonAttackingPairs;
            }
        }
    }
    return nonAttackingPairs;
}

bool GeneticSolver::isSolution(const std::vector<int>& individual) {
    return fitness(individual) == (board.getSize() * (board.getSize() - 1)) / 2;
}

void GeneticSolver::printIndividual(const std::vector<int>& individual) {
    for (int i = 0; i < board.getSize(); ++i) {
        board.placeQueen(i, individual[i]);
    }
    board.printBoard();
}

int GeneticSolver::getConflicts(const std::vector<int>& solution) {
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

