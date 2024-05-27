#include "Board.h"
#include <iostream>

Board::Board(int n) : size(n), board(n, std::vector<bool>(n, false)) {}

bool Board::isSafe(int row, int col) const {
    // Check the row
    for (int i = 0; i < size; i++)
        if (board[row][i])
            return false;

    // Check the col
    for (int i = 0; i < size; i++)
        if (board[i][col])
            return false;

    // Check upper diagonal on left side
    for (int i = row, j = col; i >= 0 && j >= 0 ; i--, j--)
        if (board[i][j])
            return false;

    // Check upper diagonal on right side
    for (int i = row, j = col; i < size && j < size; i++, j++)
        if (board[i][j])
            return false;

    // Check lower diagonal on left side
    for (int i = row, j = col; j >= 0 && i < size; i++, j--)
        if (board[i][j])
            return false;

    // Check lower diagonal on right side
    for (int i = row, j = col; j < size && i >= 0; i--, j++)
        if (board[i][j])
            return false;

    return true;
}

void Board::placeQueen(int row, int col) {
    board[row][col] = true;
}

void Board::removeQueen(int row, int col) {
    board[row][col] = false;
}

void Board::printBoard() const {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++)
            std::cout << (board[i][j] ? "Q " : ". ");
        std::cout << std::endl;
    }
}

int Board::getRow(int col) const {
    for (int row = 0; row < size; row++) {
        if (board[row][col]) {
            return row;
        }
    }
    return -1;
}
