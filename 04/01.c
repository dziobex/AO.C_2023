#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define BSIZE 150

int main( int argc, char **argv ) {
    FILE *in = fopen( "in.txt", "r" );

    if (in == NULL)
        return puts("Nie udalo sie otworzyc pliku!"), EXIT_FAILURE;

    char buffer[ BSIZE ];
    int wins_sum = 0;

    while ( fgets( buffer, BSIZE, in ) != NULL ) {

        int states[ 100 ] = {};
        int wins = 0;

        char *tmp_buff;

        tmp_buff = strtok( buffer, " " );
        tmp_buff = strtok( NULL, " " );

        while ( 1 ) {
            tmp_buff = strtok ( NULL, " " );

            if (tmp_buff[0] == '|' )
                break;
            
            int in_number = atoi( tmp_buff );
            states[ in_number ] = 1;
        }

        while ( 1 ) {
            tmp_buff = strtok ( NULL, " " );

            if (tmp_buff == NULL )
                break;
            
            int in_number = atoi( tmp_buff );
            
            if (states[ in_number ] == 1)
                ++wins;
        }

        if ( wins != 0 )
            wins_sum += pow( 2, wins - 1 );
    }

    fclose( in );

    printf( "%i\n", wins_sum );

    return EXIT_SUCCESS;
}