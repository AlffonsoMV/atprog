#ifndef BOARD_H
#define BOARD_H

#endif // BOARD_H

#include <Imagine/Graphics.h>
using namespace Imagine;

const int w = 150;
const int h = 100;
const int z = 4;

struct Board {
    int width = w;
    int height = h;
    Color board[w][h];
};
