//
// Created by Alfonso Mateos on 24/11/23.
//

#ifndef SNAKE_H
#define SNAKE_H

#include <vector>
#include "utils.h"

class Snake {
    Color c;
    int length;
    point positions[15000];
    int headWidth, headHeight;
    NativeBitmap nb;
private:
    bool collides(struct Board b, point dir);
public:
    bool move(struct Board & b, point dir);
    bool grow(struct Board & b, point dir);
    void explode();
    Snake(Color col, int x, int y);
};

#endif //SNAKE_H
