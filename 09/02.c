#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BSIZE 200
#define NSIZE 25
#define ll long long

int main( int argc, char **argv ) {

    FILE *in = fopen( "in.txt", "r" );

    if ( in == NULL )
        return EXIT_FAILURE;

    char buffer[ BSIZE ];
    int lines_count = 0;

    int matrix[NSIZE][NSIZE] = {};

    ll total_sum = 0;

    while( fgets( buffer, BSIZE, in ) != NULL ) {
        int length = strlen( buffer );
        if ( buffer[length - 1] == '\n' )
            buffer[ length - 1] = '\0';
        
        char *tmp;
        tmp = strtok( buffer, " " );

        int numbers_count = 0;

        while ( tmp != NULL ) {
            matrix[0][numbers_count] = atoi( tmp );
            tmp = strtok( NULL, " " );
            numbers_count++;
        }

        int rows = 1;
        for ( int i = 1; i < numbers_count; ++i ) {

            int zeros = 0;
            for ( int j = 0; j < numbers_count - i; ++j ) {
                if ( (matrix[i][j] = matrix[i - 1][j + 1] - matrix[i - 1][j]) == 0 )
                    ++zeros;
                    
            }
            ++rows;
            if ( zeros >= numbers_count - 1 - i)
                break;
        }

        ll sum = 0;

        for ( int i = rows - 1; i >= 0; --i )
            sum = matrix[i][0] - sum;

        total_sum += sum;

        ++lines_count;

        free( tmp );
    }

    printf("%i", total_sum);
    
    fclose( in );

    return EXIT_SUCCESS;
}