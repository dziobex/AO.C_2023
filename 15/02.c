#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 25000

typedef struct {
    char **labels;
    int *focals;
    int size;
} box;

int main( int argc, char **argv ) {
    FILE *in = fopen( "sample.txt", "r" );
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
        char sign = strchr( temp, '=' ) == NULL ? '-' : '=';

        char *label = malloc( strlen(temp));
        int value = 0;

        if ( sign == '=' ) {
            memcpy( label, temp, strlen( temp) - 2 );
            value = temp[ strlen( temp ) - 1] - '0';
        } else
            memcpy( label, temp, strlen( temp) - 1 );
        
        label[ strlen(label) - 1] = '\0';
        

            printf("%s: %s of %i [%c]\n", temp, label, value, sign);

        free( label );
        temp = strtok( NULL, "," );
    }

    free( temp );

    return EXIT_SUCCESS;
}