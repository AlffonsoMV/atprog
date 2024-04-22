//
// Created by Alfonso Mateos on 24/11/23.
//


#include "snake.h"
#include "board.h"

Snake::Snake(Color col, int x, int y) {
    c = col;
    length = 1;
    positions[0] = {x, y};

    byte * rgb;
    if (c == RED)
        loadColorImage(srcPath("moto_red.bmp"), rgb, headWidth, headHeight);
    else
        loadColorImage(srcPath("moto_blue.bmp"), rgb, headWidth, headHeight);

    NativeBitmap my_native_bitmap (headWidth, headHeight);
    my_native_bitmap.setColorImage(0, 0, rgb, headWidth, headHeight) ;
    nb = my_native_bitmap;
    delete [] rgb;
}

bool Snake::collides(Board b, point dir) {
    return  (positions[length-1].x + dir.x < 0 || positions[length-1].x + dir.x >= b.width) || // Check if x + dir.x is in bounds
            (positions[length-1].y + dir.y < 0 || positions[length-1].y + dir.y >= b.height) || // Check if y + dir.y is in bounds
            (b.board[positions[length-1].x + dir.x][positions[length-1].y + dir.y] != WHITE); // Check if it is free
}

bool Snake::move(Board & b, point dir) {
    if (collides(b, dir))
        return false;

    // Move the head of the snake in the direction dir
    // and move the rest of the body one position forward

    const point head = positions[length - 1];

    // Convert head to square
    fillRect(positions[length-1].x*z, positions[length-1].y*z, headWidth, headHeight, WHITE);
    fillRect(positions[length-1].x*z, positions[length-1].y*z, z, z, c);

    // Remove last
    b.board[positions[0].x][positions[0].y] = WHITE;
    fillRect(positions[0].x*z, positions[0].y*z, z, z, WHITE);

    // Move the rest of the body
    for (int i = 0; i < length - 1; i++) {
        positions[i].x = positions[i + 1].x;
        positions[i].y = positions[i + 1].y;
    }

    // Move the head
    positions[length - 1].x = head.x + dir.x;
    positions[length - 1].y = head.y + dir.y;
    b.board[positions[length - 1].x][positions[length - 1].y] = c;

    // Draw in board
    for (int i = 0; i < length-1; i++)
        fillRect(positions[i].x*z, positions[i].y*z, z, z, c);
    putNativeBitmap(positions[length - 1].x*z, positions[length - 1].y*z, nb);

    return true;
}

bool Snake::grow(Board & b, point dir) {
    if (collides(b, dir))
        return false;

    // Convert head to square
    fillRect(positions[length-1].x*z, positions[length-1].y*z, headWidth, headHeight, WHITE);
    fillRect(positions[length-1].x*z, positions[length-1].y*z, z, z, c);

    // Instead of moving the head, add a new head in the direction dir
    positions[length] = positions[length - 1];
    positions[length].x += dir.x;
    positions[length].y += dir.y;
    length++;

    b.board[positions[length - 1].x][positions[length - 1].y] = c;

    // Draw in board
    for (int i = 0; i < length-1; i++)
        fillRect(positions[i].x*z, positions[i].y*z, z, z, c);
    putNativeBitmap(positions[length - 1].x*z, positions[length - 1].y*z, nb);

    return true;
}

void Snake::explode() {
    fillRect(positions[length-1].x*z, positions[length-1].y*z, headWidth, headHeight, WHITE);
    int w,h;
    byte* rgb ;
    loadColorImage(srcPath("explosion.bmp"),rgb ,w,h);
    NativeBitmap expl(w, h);
    expl.setColorImage (0, 0, rgb, w, h);
    delete [] rgb;
    putNativeBitmap(positions[length - 1].x*z, positions[length - 1].y*z, expl);
}
