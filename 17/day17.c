#include "day17.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

void init_cell( cell *_cell, int y, int x, int heat_loss, char dir ) {
    _cell->y = y;
    _cell->x = x;
    _cell->dir = dir;
    _cell->heat_loss = heat_loss;

    _cell->visited = 0;
    _cell->min_path = INT_MAX;
}