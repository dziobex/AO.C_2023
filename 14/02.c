#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 150
#define WIDTH 150
#define HEIGHT 150

#define LIMIT 200
#define CYCLES 1000000000

int main( int argc, char **argv ) {
    FILE *in = fopen( "input.txt", "r" );

    if ( in == NULL )
        return fprintf( stderr, "Nie udalo sie otworzyc pliku :(" ), EXIT_FAILURE;

    char buffer[ BUFFER_SIZE ];
    char matrix[ HEIGHT ][ WIDTH ] = {};
    int width = 0, height = 0;

    while ( fgets( buffer, BUFFER_SIZE, in ) != NULL ) {
        if ( width == 0 && height == 0 )
            width = strlen( buffer ) - 1; // assuming that height > 0 and all lines < height are ending with '\n'
        memcpy( matrix[height], buffer, width );
        ++height;
    } fclose( in );

    int cycles[ LIMIT ] = {};

    for ( int c = 0; c < LIMIT; ++c ) {
        for ( int x = 0; x < width; ++x )
            for ( int y = 0; y < height; ++y )
                while( y > 0 && matrix[y][x] == 'O' && matrix[y - 1][x] == '.' ) {
                    matrix[y - 1][x] = 'O';
                    matrix[y][x] = '.';
                    --y;
                }
        for ( int x = 0; x < width; ++x )
            for ( int y = 0; y < height; ++y )
                while( x > 0 && matrix[y][x] == 'O' && matrix[y][x - 1] == '.' ) {
                    matrix[y][x - 1] = 'O';
                    matrix[y][x] = '.';
                    --x;
                }
        for ( int x = 0; x < width; ++x )
            for ( int y = height - 1; y >= 0; --y )
                while( y < height && matrix[y][x] == 'O' && matrix[y + 1][x] == '.' ) {
                    matrix[y + 1][x] = 'O';
                    matrix[y][x] = '.';
                    ++y;
                }
        for ( int x = width - 1; x >= 0; --x )
            for ( int y = 0; y < height; ++y )
                while( x < width && matrix[y][x] == 'O' && matrix[y][x + 1] == '.' ) {
                    matrix[y][x + 1] = 'O';
                    matrix[y][x] = '.';
                    ++x;
                }

        for ( int x = 0; x < width; ++x )
            for ( int y = 0; y < height; ++y )
                if ( matrix[y][x] == 'O')
                    cycles[ c ] += ( height - y );
    }

    for ( int i = 0; i < LIMIT - 3; ++i ) {
        int st_cycle = -1;

        for ( int j = i + 2; j < LIMIT - 3; ++j )
            if ( cycles[i] == cycles[j] && cycles[i + 1] == cycles[j + 1] && cycles[i + 2] == cycles[j + 2] ) {
                st_cycle = j;
                break;
            }

        if ( st_cycle != -1 ) {
            printf( "%i\n", cycles[ i + ( CYCLES - i ) % ( st_cycle - i ) - 1]);
            break;
        }
    }

    return EXIT_SUCCESS;
}