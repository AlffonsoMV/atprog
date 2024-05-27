#ifndef GENETICALGORITHMSOLVER_H
#define GENETICALGORITHMSOLVER_H

#include "../Solver.h"
#include <vector>
#include <utility>

class GeneticSolver : public Solver {
public:
    GeneticSolver(int n, int populationSize, int maxGenerations, double mutationRate);
    void solve() override;  // Override the solve function

private:
    int populationSize;
    int generations;
    double mutationRate;
    std::vector<std::vector<int>> population;

    void initializePopulation();
    std::vector<int> createIndividual();
    void evolvePopulation();
    std::pair<std::vector<int>, std::vector<int>> selectParents();
    std::vector<int> crossover(const std::vector<int>& parent1, const std::vector<int>& parent2);
    void mutate(std::vector<int>& individual);
    int fitness(const std::vector<int>& individual);
    bool isSolution(const std::vector<int>& individual);
    void printIndividual(const std::vector<int>& individual);
    int getConflicts(const std::vector<int>& solution);
};

#endif