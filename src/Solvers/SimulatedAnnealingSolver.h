#ifndef SIMULATEDANNEALINGSOLVER_H
#define SIMULATEDANNEALINGSOLVER_H

#include "../Solver.h"
#include <vector>

class SimulatedAnnealingSolver : public Solver {
public:
    SimulatedAnnealingSolver(int n, double initialTemp, double coolingRate);
    void solve() override;  // Override the solve function

private:
    double initialTemp;
    double coolingRate;
    std::vector<int> currentSolution;
    int currentCost;

    void initializeSolution();
    int computeCost(const std::vector<int>& solution);
    std::vector<int> generateNeighbor(const std::vector<int>& solution);
    double acceptanceProbability(int oldCost, int newCost, double temperature);
    void printSolution(const std::vector<int>& solution);
    int getConflicts(const std::vector<int>& solution);
};

#endif