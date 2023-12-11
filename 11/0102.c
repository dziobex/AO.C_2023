#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define ull unsigned long long

#define BUFFER_SIZE 150
#define MATRIX_SIZE 150
#define EXPANSIONS_COUNT 150
#define GALAXIES_COUNT 500

typedef struct {
    int y, x;
} galaxy;

galaxy init_galaxy( int x, int y ) {
    return (galaxy) { .x = x, .y = y };
}

ull exp_rows_between( ull EXP_VALUE, ull exp_rows[ EXPANSIONS_COUNT ], galaxy g1, galaxy g2 ) {
    ull count = 0;
    int mn = g1.y < g2.y ? g1.y : g2.y, mx = g1.y < g2.y ? g2.y : g1.y;

    for( int y = mn; y < mx; ++y )
        count += exp_rows[ y ] * (EXP_VALUE-1);
    return count;
}

ull exp_cols_between( ull EXP_VALUE, ull exp_cols[ EXPANSIONS_COUNT ], galaxy g1, galaxy g2 ) {
    ull count = 0;
    int mn = g1.x < g2.x ? g1.x : g2.x, mx = g1.x < g2.x ? g2.x : g1.x;

    for( int x = mn; x < mx; ++x )
        count += exp_cols[ x ] * (EXP_VALUE-1);
    return count;
}

int main( int argc, char **argv ) {
    FILE *in = fopen( "in.txt", "r" );

    if ( in == NULL )
        return fprintf(stderr, "Nie udalo sie otworzyc pliku!"), EXIT_FAILURE;
    
    char buffer[BUFFER_SIZE], matrix[ MATRIX_SIZE ][ MATRIX_SIZE ] = {0};

    galaxy galaxies[GALAXIES_COUNT];
    int galaxies_count = 0;

    ull exp_rows[ EXPANSIONS_COUNT ] = {0}, exp_cols[ EXPANSIONS_COUNT ] = {0};
    int rows = 0, cols = 0;

    while( fgets( buffer, BUFFER_SIZE, in) != NULL ) {
        if ( cols == 0 )
            cols = strlen( buffer ) - 1;
        
        for( int i = 0; i < cols; ++i )
            if ( buffer[i] == '#' )
                galaxies[ galaxies_count++ ] = init_galaxy( rows, i );
        
        strncpy( matrix[ rows ], buffer, cols );

        ++rows;
    }

    fclose( in );

    for( int y = 0; y < rows; ++y ) {
        exp_rows[ y ] = 1;
        for (int x = 0; x < cols; ++x )
            if ( matrix[y][x] != '.' ) {
                exp_rows[ y ] = 0;
                break;
            }
    }

    for( int x = 0; x < cols; ++x ) {
        exp_cols[ x ] = 1;
        for (int y = 0; y < cols; ++y )
            if ( matrix[y][x] != '.' ) {
                exp_cols[ x ] = 0;
                break;
            }
    }

    ull exp_value[2] = { 2, 1000000 };

    for ( int p = 0; p < 2; ++p ) {
        ull sum = 0;
        for( int i = 0; i < galaxies_count; ++i )
            for( int j = i + 1; j < galaxies_count; ++j ) {
                ull d_rows = abs( galaxies[i].y - galaxies[j].y ) + exp_rows_between( exp_value[p], exp_cols, galaxies[ j ], galaxies[ i ] );
                ull d_cols = abs( galaxies[i].x - galaxies[j].x ) + exp_cols_between( exp_value[p], exp_rows, galaxies[ j ], galaxies[ i ] );
                sum += d_rows + d_cols;
            }
        printf( "%i: %llu\n", p+1, sum );
    }

    return EXIT_SUCCESS;
}