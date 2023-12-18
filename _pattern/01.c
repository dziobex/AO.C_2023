#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 150

int main( int argc, char **argv ) {
    FILE *in = fopen( "sample.txt", "r" );
    if ( in == NULL )
        return fprintf( stderr, "Nie udalo sie otworzyc pliku :(" ), EXIT_FAILURE;
    fclose( in );

    return EXIT_FAILURE;
}
