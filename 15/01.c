#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 25000

int main( int argc, char **argv ) {
    FILE *in = fopen( "in.txt", "r" );
    if ( in == NULL )
        return fprintf( stderr, "Nie udalo sie otworzyc pliku!" ), EXIT_FAILURE;
    
    char buffer[ BUFFER_SIZE ];
    if ( fgets( buffer, BUFFER_SIZE, in ) == NULL )
        return fprintf( stderr, "Cos jest nie tak z plikiem :/" ), EXIT_FAILURE;
    fclose( in );
    
    char *temp;
    temp = strtok( buffer, "," );
    int global_sum = 0;

    while ( temp != NULL ) {
        int local_sum = 0;
        for ( char* p = temp; *p != '\0'; ++p )
            local_sum = (( local_sum + *p) * 17 ) % 256;
        global_sum += local_sum;
        temp = strtok( NULL, "," );
    }

    free( temp );
    printf( "%i", global_sum );

    return EXIT_SUCCESS;
}