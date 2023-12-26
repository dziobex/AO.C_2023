#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define GRID_SIZE 1000

// Zastosowany algorytm: FLOOD FILL

typedef struct {
    char* sign;
    int y, x;
} cell;

cell init_cell( char* s, int y, int x ) {
    return (cell) { .sign = s, .y = y, .x = x };
}

int main( int argc, char **argv ) {
    FILE *in = fopen( "in.txt", "r" );

    if ( in == NULL )
        return fprintf( stderr, "Nie udalo sie otworzyc pliku :(" ), EXIT_FAILURE;

    char dir;
    int value;
    char* color[9];

    char grid[GRID_SIZE][GRID_SIZE];

    int s_x = GRID_SIZE / 2, s_y = GRID_SIZE / 2, width = 0, height = 0;
    int x = s_x, y = s_y;

    grid[y][x] = '#';
    int trench = 0;

    while( fscanf( in, "%c %d %s\n", &dir, &value, color) == 3) {
        trench += value;

        for( int i = 1; i <= value; ++i ) {
            switch (dir) {
                case 'U':
                    --y;
                    break;
                case 'R':
                    ++x;
                    break;
                case 'D':
                    ++y;
                    break;
                case 'L':
                    --x;
                    break;
                default: break;
            }
            grid[y][x] = '#';

            if ( y < s_y) s_y = y;
            if ( x < s_x ) s_x = x;

            if ( width < x ) width = x;
            if ( height < y) height = y;
        }
    }

    fclose( in );

    int s_e_x = ( s_x + width ) / 2;
    int s_e_y = ( s_y + height ) / 2;
    cell start_element = init_cell( &grid[s_e_y][s_e_x], s_e_y, s_e_x );
    
    cell stack[80000];
    int stack_size = 0;
    stack[stack_size++] = start_element;

    while ( stack_size-- > 0 ) {
        cell pop = stack[stack_size];

        if ( *(pop.sign) == '#' )
            continue;
        *(pop.sign) = '#';
        ++trench;

        int px = pop.x, py = pop.y;

        for( int i = -1; i <= 1; i += 2 ) {
            if ( px + i < s_x || px + i > width || py + i < s_y || py + i > height )
                continue;
            if ( grid[py + i][px] != '#' )
                stack[stack_size++] = init_cell( &grid[py + i][px], py + i, px );
            if ( grid[py][px + i] != '#' )
                stack[stack_size++] = init_cell( &grid[py][px + i], py, px + i );
        } 
    }

    printf( "%i\n", trench);

    return EXIT_SUCCESS;
}