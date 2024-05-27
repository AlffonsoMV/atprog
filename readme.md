# ♟️ N-Queens Problem Solver

This project is a comprehensive solution to the classic N-Queens problem, developed for the course "Atelier de programmation" by Quang and Alfonso Mateos Vicente. The project features multiple algorithms to solve the N-Queens problem, all implemented in C++.

![Screenshot.png](images%2FScreenshot.png)

## 📁 Project Structure

- **`main.cpp`**: The main file that handles the user interface and coordinates between the different solvers.
- **`src/Solver.h`**: The base class for all solvers, providing a common interface.
- **`src/Solvers/BacktrackingSolver.h`**: A solver that uses the backtracking algorithm.
- **`src/Solvers/SimulatedAnnealingSolver.h`**: A solver that uses the simulated annealing algorithm.
- **`src/Solvers/MinConflictsSolver.h`**: A solver that uses the min-conflicts algorithm.
- **`src/Solvers/GeneticSolver.h`**: A solver that uses a genetic algorithm.
- **`Google_tests/SolversTests.cpp`**: Implement 16 tests to verify that the code works properly.

## 🧠 Algorithms Implemented

### Backtracking
A classical recursive algorithm that systematically places queens one by one in different columns, starting from the leftmost column, and backtracks when a conflict is detected.

### Simulated Annealing
A probabilistic technique that approximates the global optimum of a function. It is particularly effective for large and complex search spaces.

### Min-Conflicts
A heuristic search algorithm designed for solving constraint satisfaction problems by minimizing the number of conflicts in the current state.

### Genetic Algorithm
An evolutionary algorithm inspired by the process of natural selection. It utilizes techniques such as mutation, crossover, and selection to evolve solutions over generations.

## 📝 Code Overview

### `main.cpp`

Handles the graphical user interface, user inputs, and integrates the different solving algorithms. Key functions include:
- `drawChessboard()`: Draws the chessboard.
- `drawQueens()`: Places queens on the board.
- `drawGUI()`: Renders the GUI components.
- `solveNQueens()`: Initiates the solving process based on user selections.

### `src/Solver.h`

Defines the abstract base class `Solver`, which declares the interface for all specific solver implementations:
- `solve()`: Pure virtual function to be implemented by derived classes.

### `src/Solvers/BacktrackingSolver.h`

Implements the backtracking algorithm:
- `solve()`: Places queens on the board using a recursive approach.
- `isSafe()`: Checks if a queen can be placed on a given position without conflicts.

### `src/Solvers/SimulatedAnnealingSolver.h`

Implements the simulated annealing algorithm:
- `solve()`: Executes the simulated annealing process.
- `initializeSolution()`: Initializes a random solution.
- `generateNeighbor()`: Generates a neighboring solution.
- `acceptanceProbability()`: Determines the probability of accepting a worse solution based on the temperature.

### `src/Solvers/MinConflictsSolver.h`

Implements the min-conflicts algorithm:
- `solve()`: Solves the problem by iteratively minimizing conflicts.
- `initializeSolution()`: Initializes a solution with a random configuration.
- `computeConflicts()`: Computes the number of conflicts for a queen's position.

### `src/Solvers/GeneticSolver.h`

Implements the genetic algorithm:
- `solve()`: Runs the genetic algorithm to evolve solutions.
- `initializePopulation()`: Creates an initial population of random solutions.
- `selectParents()`: Selects parent solutions for crossover.
- `crossover()`: Combines two parent solutions to produce offspring.
- `mutate()`: Mutates a solution to introduce variation.
- `fitness()`: Evaluates the fitness of a solution.

## 👥 Authors

- **Quang**
- **Alfonso Mateos Vicente**

This project is part of the "Atelier de programmation" course.