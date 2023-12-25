#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#include "day17.h"
#include "priority_queue.h"

int get_best_path( cell grid[GRID_DIM][GRID_DIM][2], int grid_size, int _min, int _max ) {
    for ( int y = 0; y < grid_size; ++y )                           // czyszczę cały grid - resetuję wcześniej ustawione dane
        for ( int x = 0; x < grid_size; ++x ){
            init_cell( &grid[y][x][0], y, x, grid[y][x][0].heat_loss, '-' );
            init_cell( &grid[y][x][1], y, x, grid[y][x][1].heat_loss, '|' );
        }
    
    grid[0][0][0].min_path = 0;                                     // postój na 1. komórce jest BEZPŁATNY
    grid[0][0][1].min_path = 0;

    p_queue pq;                                                     // inicjacja kopca na kolejne kierunki z komórek
    init_queue( &pq );

    push_q( &pq, &grid[0][0][0] );                                  // dodaję 2 pierwsze kierunki z pierwszej komórki
    push_q( &pq, &grid[0][0][1] );

    while( pq.size > 0 ) {                                          // dijkstra
        cell *popped = pop_q( &pq );

        if ( popped->visited == 1 )
            continue;
        popped->visited = 1;

        int x = popped->x, y = popped->y;

        for ( int sg = -1; sg <= 1; sg += 2 ) {
            int dist = popped->min_path;
            
            for ( int i = 1; i <= _max; ++i ) {
                int n_x = x + sg * i, n_y = y + sg * i;

                if ( popped->dir == '|'                             // teraz sprawdzamy elementy poziome ---
                && n_x >= 0 && n_x < grid_size ) { 
                    dist += grid[y][n_x][0].heat_loss;
                    if ( i >= _min && grid[y][n_x][0].min_path > dist ) {
                        grid[y][n_x][0].min_path = dist;
                        push_q( &pq, &grid[y][n_x][0] );
                    }
                }

                if ( popped->dir == '-'                             // teraz sprawdzamy elementy pionowe |||
                && n_y >= 0 && n_y < grid_size ) {
                    dist += grid[n_y][x][1].heat_loss;
                    if ( i >= _min && grid[n_y][x][1].min_path > dist ) {
                        grid[n_y][x][1].min_path = dist;
                        push_q( &pq, &grid[n_y][x][1] );
                    }
                }
            }
        }
    }

    int le = grid_size - 1;
    return grid[le][le][0].min_path < grid[le][le][1].min_path
        ? grid[le][le][0].min_path : grid[le][le][1].min_path;      // zwracam minimalną odległość (z kierunków |- z komórki mety)
}

int main( int argc, char **argv ) {
    FILE *in = fopen( "in.txt", "r" );

    if ( in == NULL )
        return fprintf( stderr, "Nie udalo sie otworzyc pliku :(" ), EXIT_FAILURE;

    char buffer[ BUFFER_SIZE ];
    int grid_size = 0, line = 0;
    cell grid[GRID_DIM][GRID_DIM][2];

    while ( fgets( buffer, BUFFER_SIZE, in ) != NULL ) {
        if ( grid_size == 0 )
            grid_size = strlen( buffer ) - 1;
        for( int i = 0; i < grid_size; ++i ) {
            init_cell( &grid[line][i][0], line, i, buffer[i] - '0', '-' );
            init_cell( &grid[line][i][1], line, i, buffer[i] - '0', '|' );
        }
        ++line;
    }
    
    fclose( in );

    printf( "Part 1: %i\n", get_best_path( grid, grid_size, 1, 3 ) );
    printf( "Part 2: %i", get_best_path( grid, grid_size, 4, 10 ) );

    return EXIT_SUCCESS;
}