#ifndef BOARD_H
#define BOARD_H

#include <vector>

using namespace std;

class Board {
private:
    int size;
    vector<vector<bool>> board;

public:
    Board(int n);
    bool isSafe(int row, int col) const;
    void placeQueen(int row, int col);
    void removeQueen(int row, int col);
    void printBoard() const;
    int getRow(int col) const;

    int getSize() { return size; };
};

#endif
