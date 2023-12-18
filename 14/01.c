#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 150
#define WIDTH 150
#define HEIGHT 150

int main( int argc, char **argv ) {
    FILE *in = fopen( "input.txt", "r" );

    if ( in == NULL )
        return fprintf( stderr, "Nie udalo sie otworzyc pliku :(" ), EXIT_FAILURE;

    char buffer[ BUFFER_SIZE ];
    char matrix[ HEIGHT ][ WIDTH ] = {};
    int width = 0, height = 0, total_sum = 0;

    while ( fgets( buffer, BUFFER_SIZE, in ) != NULL ) {
        if ( width == 0 && height == 0 )
            width = strlen( buffer ) - 1; // assuming that height > 0 and all lines < height are ending with '\n'
        memcpy( matrix[height], buffer, width );
        ++height;
    } fclose( in );

    for ( int x = 0; x < width; ++x ) {
        for ( int y = 0; y < height; ++y ) {
            while( y > 0 && matrix[y][x] == 'O' && matrix[y - 1][x] == '.' ) {
                matrix[y - 1][x] = 'O';
                matrix[y][x] = '.';
                --y;
            }
            if ( matrix[y][x] == 'O')
                total_sum += ( height - y );
        }
    }

    printf( "%i\n", total_sum );

    return EXIT_SUCCESS;
}