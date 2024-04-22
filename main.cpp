// Imagine++ project
// Project:  Tp7
// Student(s): 

#include "utils.h"
#include "board.h"
#include "snake.h"

#include <Imagine/Graphics.h>
using namespace Imagine;

//======================================
// Snake
void game_1p() {
	// Initialization of the game
	Board board;
    board.width = w;
    board.height = h;
    for (int i = 0; i < board.width; i++) {
        for (int j = 0; j < board.height; j++) {
            board.board[i][j] = WHITE;
        }
    }

    Snake snake1(RED, w/4, h/4);
    board.board[0][0] = RED;

	// Main loop
    bool game_over = false;
    point dir = {1, 0};
    int its = 0;
	while (!game_over) {
        its++;

		// Get the direction from the keyboard
        int key = keyboard();
		switch (key) {
			case KEY_LEFT:
				dir = { -1, 0 };
				break;
			case KEY_RIGHT:
				dir = { 1, 0 };
				break;
			case KEY_UP:
				dir = { 0, -1 };
				break;
			case KEY_DOWN:
				dir = { 0, 1 };
                break;
		}

		// Move the snake
        if (its % 10 == 0)
            game_over = !snake1.grow(board, dir);
        else
            game_over = !snake1.move(board, dir);

		// Wait a bit
		milliSleep(100);
    }

    drawString(w/2 - 50, "Game over !", RED);
    snake1.explode();
}

//======================================
// Tron
void game_2p() {
    // Initialization of the game
    Board board;
    board.width = w;
    board.height = h;
    for (int i = 0; i < board.width; i++) {
        for (int j = 0; j < board.height; j++) {
            board.board[i][j] = WHITE;
        }
    }

    Snake snake1(RED, w/5, h/5);
    board.board[0][0] = RED;

    Snake snake2(BLUE, 4*w/5, 4*h/5);
    board.board[board.width-1][board.height-1] = BLUE;

    // Main loop
    bool snake1_lose = false, snake2_lose = false;
    point dir1 = {1, 0}, dir2 = {-1, 0};
    int its = 0;
    while (!snake1_lose && !snake2_lose) {
        its++;

        // Get the direction from the keyboard
        int key = keyboard();
        switch (key) {
            case KEY_LEFT:
                dir1 = { -1, 0 };
                break;
            case KEY_RIGHT:
                dir1 = { 1, 0 };
                break;
            case KEY_UP:
                dir1 = { 0, -1 };
                break;
            case KEY_DOWN:
                dir1 = { 0, 1 };
                break;
        }

        switch (key) {
            case int('s'):
            case int('S'):
                dir2 = { -1, 0 };
                break;
            case int('x'):
            case int('X'):
                dir2 = { 0, 1 };
                break;
            case int('d'):
            case int('D'):
                dir2 = { 0, -1 };
                break;
            case int('f'):
            case int('F'):
                dir2 = { 1, 0 };
                break;
        }

        // Move the snake
        snake1_lose = !snake1.grow(board, dir1);
        snake2_lose = !snake2.grow(board, dir2);

        // Wait a bit
        milliSleep(100);
    }


    int w,h;
    byte* rgb ;
    loadColorImage(srcPath("explosion.bmp"), rgb, w, h);
    NativeBitmap expl(w, h);
    delete [] rgb;

    if (snake1_lose) {
        snake1.explode();
        drawString(board.width/2 - 50, "BLUE player is the winner !", BLUE);
    } else {
        snake2.explode();
        drawString(board.width/2 - 50, "RED player is the winner !", RED);
    }
}


int main() {
	openWindow(w*z,h*z);

    game_2p();

	endGraphics();
	return 0;
}
