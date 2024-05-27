#include <Imagine/Graphics.h>
#include <Imagine/Images.h>
#include "Solvers/BacktrackingSolver.h"
#include "Solvers/GeneticSolver.h"
#include "Solvers/MinConflictsSolver.h"
#include "Solvers/SimulatedAnnealingSolver.h"
#include <string>
#include <sstream>
#include <iostream>

using namespace Imagine;
using namespace std;

const int cellSize = 50;
const int offsetX = 300;
const int offsetY = 20;

const int offsetYParams = 300;
int boardSize = 8;
string selectedSolver = "Backtracking";

bool solveRequested = false;
bool changeParameters = true;
bool changeSolver = true;
bool changeBoardSize = true;

vector<int> board;
int conflicts = -1;

int populationSize = 100;
int generations = 1000;
double mutationRate = 0.01;
int maxSteps = 10000;
int maxIterations = 1000;
double coolingRate = 0.99;

Color LIGHT_GRAY(222, 219, 211);
Image<Color> queenImage;

void drawChessboard();
void drawQueens(const vector<int>& board);
void drawGUI();
void handleEvent(const Event& ev);
void solveNQueens();
void drawMessage(const string& message);

void drawChessboard() {
    // Refresh chessboard
    fillRect(offsetX, 0, boardSize * cellSize + offsetX * 2 + 250 - offsetX, boardSize * cellSize + offsetY * 2 + 250, WHITE);

    for (int i = 0; i < boardSize; i++) {
        for (int j = 0; j < boardSize; j++) {
            Color color = (i + j) % 2 == 0 ? WHITE : LIGHT_GRAY;
            fillRect(offsetX + j * cellSize, offsetY + i * cellSize, cellSize, cellSize, color);
        }
    }

    // If there is a solutions => Draw the number of conflicts
    if (conflicts != -1){
        string message = "Best solution (" + to_string(conflicts) + " conflicts)";
        drawMessage(message);
    }
}

void drawQueens(const vector<int>& board) {
    for (int i = 0; i < board.size(); i++) {
        int row = i;
        int col = board[i];
        if (col >= 0) {
            display(queenImage, offsetX + col * cellSize, offsetY + row * cellSize, false, double(cellSize) / queenImage.width());
        }
    }
}

void drawSolverSelector() {
    // Refresh GUI
    fillRect(0, 0, offsetX,500, WHITE);

    // Draw Board Size controls
    drawRect(10, 10, 270, 270, BLACK);
    drawString(20, 40, "Board Size:", BLACK);
    stringstream ss;
    ss << boardSize;
    drawString(170, 40, ss.str(), BLACK);
    drawRect(190, 20, 30, 30, LIGHT_GRAY);
    drawString(200, 40, "+", BLACK);
    drawRect(230, 20, 30, 30, LIGHT_GRAY);
    drawString(240, 40, "-", BLACK);

    // Draw solver options
    drawRect(20, 70, 240, 30, selectedSolver == "Backtracking" ? RED : WHITE);
    drawString(30, 90, "Backtracking", BLACK);
    drawRect(20, 110, 240, 30, selectedSolver == "Genetic" ? RED : WHITE);
    drawString(30, 130, "Genetic Algorithm", BLACK);
    drawRect(20, 150, 240, 30, selectedSolver == "MinConflicts" ? RED : WHITE);
    drawString(30, 170, "MinConflicts", BLACK);
    drawRect(20, 190, 240, 30, selectedSolver == "SimulatedAnnealing" ? RED : WHITE);
    drawString(30, 210, "SimulatedAnnealing", BLACK);

    // Draw solve button
    drawRect(20, 230, 240, 30, solveRequested ? GREEN : WHITE);
    drawString(30, 250, "Solve", BLACK);

}

void drawParametersSelector() {
    // Refresh GUI
    fillRect(0, offsetYParams + 270, offsetX, boardSize * cellSize + offsetY * 2 + 250, WHITE);

    stringstream ss;
    ss << boardSize;

    // Draw solver parameters
    if (selectedSolver == "Genetic") {
        drawString(20, offsetYParams + 290, "Population Size:", BLACK);
        ss.str("");
        ss << populationSize;
        drawString(150, offsetYParams + 290, ss.str(), BLACK);
        drawRect(200, offsetYParams + 270, 30, 30, LIGHT_GRAY);
        drawString(210, offsetYParams + 290, "+", BLACK);
        drawRect(240, offsetYParams + 270, 30, 30, LIGHT_GRAY);
        drawString(250, offsetYParams + 290, "-", BLACK);

        drawString(20, offsetYParams + 320, "Generations:", BLACK);
        ss.str("");
        ss << generations;
        drawString(150, offsetYParams + 320, ss.str(), BLACK);
        drawRect(200, offsetYParams + 300, 30, 30, LIGHT_GRAY);
        drawString(210, offsetYParams + 320, "+", BLACK);
        drawRect(240, offsetYParams + 300, 30, 30, LIGHT_GRAY);
        drawString(250, offsetYParams + 320, "-", BLACK);

        drawString(20, offsetYParams + 350, "Mutation Rate:", BLACK);
        ss.str("");
        ss << mutationRate;
        drawString(150, offsetYParams + 350, ss.str(), BLACK);
        drawRect(200, offsetYParams + 330, 30, 30, LIGHT_GRAY);
        drawString(210, offsetYParams + 350, "+", BLACK);
        drawRect(240, offsetYParams + 330, 30, 30, LIGHT_GRAY);
        drawString(250, offsetYParams + 350, "-", BLACK);
    } else if (selectedSolver == "MinConflicts") {
        drawString(20, offsetYParams + 290, "Max Steps:", BLACK);
        ss.str("");
        ss << maxSteps;
        drawString(150, offsetYParams + 290, ss.str(), BLACK);
        drawRect(200, offsetYParams + 270, 30, 30, LIGHT_GRAY);
        drawString(210, offsetYParams + 290, "+", BLACK);
        drawRect(240, offsetYParams + 270, 30, 30, LIGHT_GRAY);
        drawString(250, offsetYParams + 290, "-", BLACK);
    } else if (selectedSolver == "SimulatedAnnealing") {
        drawString(20, offsetYParams + 290, "Max Iterations:", BLACK);
        ss.str("");
        ss << maxIterations;
        drawString(150, offsetYParams + 290, ss.str(), BLACK);
        drawRect(200, offsetYParams + 270, 30, 30, LIGHT_GRAY);
        drawString(210, offsetYParams + 290, "+", BLACK);
        drawRect(240, offsetYParams + 270, 30, 30, LIGHT_GRAY);
        drawString(250, offsetYParams + 290, "-", BLACK);

        drawString(20, offsetYParams + 320, "Cooling Rate:", BLACK);
        ss.str("");
        ss << coolingRate;
        drawString(150, offsetYParams + 320, ss.str(), BLACK);
        drawRect(200, offsetYParams + 300, 30, 30, LIGHT_GRAY);
        drawString(210, offsetYParams + 320, "+", BLACK);
        drawRect(240, offsetYParams + 300, 30, 30, LIGHT_GRAY);
        drawString(250, offsetYParams + 320, "-", BLACK);
    }
}

void handleEvent(const Event& ev) {
    // Refresh previous selections
    changeSolver = false;
    changeBoardSize = false;
    changeParameters = false;
    solveRequested = false;

    if (ev.type == EVT_BUT_ON) {
        int x = ev.pix.x();
        int y = ev.pix.y();

        // Handle solver selection
        if (x > 20 && x < 200) {
            if (y > 70 && y < 100) {
                changeSolver = true;
                selectedSolver = "Backtracking";
                board.assign(boardSize, -1); // Reset board
                conflicts = -1;
            } else if (y > 110 && y < 140) {
                changeSolver = true;
                selectedSolver = "Genetic";
                board.assign(boardSize, -1); // Reset board
                conflicts = -1;
            } else if (y > 150 && y < 180) {
                changeSolver = true;
                selectedSolver = "MinConflicts";
                board.assign(boardSize, -1); // Reset board
                conflicts = -1;
            } else if (y > 190 && y < 220) {
                changeSolver = true;
                selectedSolver = "SimulatedAnnealing";
                board.assign(boardSize, -1); // Reset board
                conflicts = -1;
            } else if (y > 230 && y < 260) {
                solveRequested = true;
            }
        }

        // Handle board size adjustment
        if (x > 190 && x < 220 && y > 20 && y < 50) {
            changeBoardSize = true;
            boardSize = min(boardSize + 1, 20);
            board.assign(boardSize, -1);
            conflicts = -1;
        } else if (x > 230 && x < 260 && y > 20 && y < 50) {
            changeBoardSize = true;
            boardSize = max(boardSize - 1, 1);
            board.assign(boardSize, -1);
            conflicts = -1;
        }

        // Handle solver parameter adjustment
        if (selectedSolver == "Genetic") {
            if (x > 200 && x < 230 && y > offsetYParams + 270 && y < offsetYParams + 300) {
                changeParameters = true;
                populationSize = min(populationSize + 10, 1000);
            } else if (x > 240 && x < 270 && y > offsetYParams + 270 && y < offsetYParams + 300) {
                changeParameters = true;
                populationSize = max(populationSize - 10, 10);
            } else if (x > 200 && x < 230 && y > offsetYParams + 300 && y < offsetYParams + 330) {
                changeParameters = true;
                generations = min(generations + 100, 10000);
            } else if (x > 240 && x < 270 && y > offsetYParams + 300 && y < offsetYParams + 330) {
                changeParameters = true;
                generations = max(generations - 100, 100);
            } else if (x > 200 && x < 230 && y > offsetYParams + 330 && y < offsetYParams + 360) {
                changeParameters = true;
                mutationRate = min(mutationRate + 0.01, 1.0);
            } else if (x > 240 && x < 270 && y > offsetYParams + 330 && y < offsetYParams + 360) {
                changeParameters = true;
                mutationRate = max(mutationRate - 0.01, 0.01);
            }
        } else if (selectedSolver == "MinConflicts") {
            if (x > 200 && x < 230 && y > offsetYParams + 270 && y < offsetYParams + 300) {
                changeParameters = true;
                maxSteps = min(maxSteps + 100, 100000);
            } else if (x > 240 && x < 270 && y > offsetYParams + 270 && y < offsetYParams + 300) {
                changeParameters = true;
                maxSteps = max(maxSteps - 100, 100);
            }
        } else if (selectedSolver == "SimulatedAnnealing") {
            if (x > 200 && x < 230 && y > offsetYParams + 270 && y < offsetYParams + 300) {
                changeParameters = true;
                maxIterations = min(maxIterations + 100, 10000);
            } else if (x > 240 && x < 270 && y > offsetYParams + 270 && y < offsetYParams + 300) {
                changeParameters = true;
                maxIterations = max(maxIterations - 100, 100);
            } else if (x > 200 && x < 230 && y > offsetYParams + 300 && y < offsetYParams + 330) {
                changeParameters = true;
                coolingRate = min(coolingRate + 0.01, 1.0);
            } else if (x > 240 && x < 270 && y > offsetYParams + 300 && y < offsetYParams + 330) {
                changeParameters = true;
                coolingRate = max(coolingRate - 0.01, 0.01);
            }
        }
    }
}

void solveNQueens() {
    Solver* solver;
    if (selectedSolver == "Backtracking") {
        solver = new BacktrackingSolver(boardSize);
    } else if (selectedSolver == "Genetic") {
        solver = new GeneticSolver(boardSize, populationSize, generations, mutationRate);
    } else if (selectedSolver == "MinConflicts") {
        solver = new MinConflictsSolver(boardSize, maxSteps);
    } else if (selectedSolver == "SimulatedAnnealing") {
        solver = new SimulatedAnnealingSolver(boardSize, maxIterations, coolingRate);
    }

    solver->solve();
    board = solver->getMinConflictsBoard();

    conflicts = solver->getMinConflicts();
    string message = "Best solution (" + to_string(conflicts) + " conflicts)";
    drawMessage(message);
    delete solver;
}

void drawMessage(const string& message) {
    drawString(offsetX, boardSize * cellSize + offsetY * 2 + 20, message, BLUE);
}

void refreshWindow() {
    fillRect(0, 0, boardSize * cellSize + offsetX * 2 + 250, boardSize * cellSize + offsetY * 2 + 250, WHITE);
}

int main() {
    openWindow(boardSize * cellSize + offsetX * 2 + 250, boardSize * cellSize + offsetY * 2 + 250);

    // Load the queen image
    if (!load(queenImage, srcPath("images/queen.png"))) {
        cerr << "Failed to load queen image!" << endl;
        return 1;
    }

    board.assign(boardSize, -1);

    Event ev;
    while (true) {
        if (changeSolver || changeBoardSize)
            drawSolverSelector();

        if (changeParameters || changeSolver)
            drawParametersSelector();

        if (changeBoardSize || solveRequested || changeSolver) {
            drawChessboard();
            if (!changeSolver)
                drawQueens(board);
        }
        getEvent(-1, ev);
        handleEvent(ev);

        if (solveRequested) {
            solveNQueens();
        }
    }

    endGraphics();
    return 0;
}
