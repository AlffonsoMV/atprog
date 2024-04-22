#pragma once

#include <Imagine/Graphics.h>
using namespace Imagine;

struct point {
	int x;
	int y;
};

const int right = 0;
const int bottom = 1;
const int left = 2;
const int up = 3;
const point dir[4] = {{1,0},{0,1},{-1,0},{0,-1}};

int keyboard();
