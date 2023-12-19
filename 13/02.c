#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MIN( a, b ) ( ( (a) < (b) ) ? (a) : (b) )

#define BUFFER_SIZE 150
#define MIRROR_H 50
#define MIRROR_W 50

int cmpcol( char mirror[MIRROR_H][MIRROR_W], int i_1, int i_2, int height ) {
    int diffs = 0;
    for ( int i = 0; i < height; ++i )
        if ( mirror[i][i_1] != mirror[i][i_2] )
            ++diffs;
    return diffs;
}

int cmprow( char mirror[MIRROR_H][MIRROR_W], int i_1, int i_2, int width ) {
    int diffs = 0;
    for ( int i = 0; i < width; ++i )
        if ( mirror[i_1][i] != mirror[i_2][i] )
            ++diffs;
    return diffs;
}

int main( int argc, char **argv ) {
    FILE *in = fopen( "in.txt", "r" );

    if ( in == NULL )
        return fprintf( stderr, "Nie udalo sie otworzyc pliku :(" ), EXIT_FAILURE;

    char buffer[ BUFFER_SIZE ];
    int sum_total = 0;

    while( fgets( buffer, BUFFER_SIZE, in ) != NULL ) {
        int width = 0, height = 0;
        char mirror[ MIRROR_H ][ MIRROR_W ] = {};

        while( 1 ) {
            if ( width == 0 )
                width = strlen( buffer ) - 1;
            if ( buffer[ width ] == '\n')
                buffer[ width ] = '\0';
            memcpy( mirror[ height++ ], buffer, width );
            if ( fgets( buffer, BUFFER_SIZE, in ) == NULL || strlen( buffer ) == 1 )
                break;
        }

        /* rows - BY HEIGHT */
        for( int b = 0; b < height - 1; ++b ) {
            int d = b + 1, min_dist = MIN( b + 1, height - d ), diffs = 0;
            for( int i = 0; i < min_dist; ++i )
                diffs += cmprow( mirror, b - i, d + i, width );
            if (diffs == 1) {
                sum_total += ( b + 1 ) * 100;
                break;
            }
        }

        /* columns - BY WIDTH */
        for( int b = 0; b < width - 1; ++b ) {
            int d = b + 1, diffs = 0, min_dist = MIN( b + 1, width - d );
            for( int i = 0; i < min_dist; ++i )
                diffs += cmpcol( mirror, b - i, d + i, height );
            if (diffs == 1) {
                sum_total += ( b + 1 );
                break;
            }
        }
    } fclose( in );

    printf( "%i", sum_total );

    return EXIT_SUCCESS;
}