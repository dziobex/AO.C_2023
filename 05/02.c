#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define BSIZE 300
#define ll long long

int main( int argc, char **argv ) {
    FILE *in = fopen( "in.txt", "r" );

    if ( in == NULL )
        return fputs("Nie mozna zaladowac pliku!", stderr), EXIT_FAILURE;
    
    char buffer[BSIZE];

    int seeds_count = 0;

    if (fgets(buffer, BSIZE, in) != NULL) {
        buffer[ strlen(buffer) - 1] = '\0';

        char *tmp;
        tmp = strtok(buffer, " ");

        while (1) {
            tmp = strtok(NULL, " ");
            if (tmp == NULL)
                break;
            ll start = atoll( tmp );
            tmp = strtok(NULL, " ");
            ll end = atoll( tmp );
        }

        free( tmp );
    }
    fgets( buffer, BSIZE, in); // biore zagubionego next linea

    ll min = -1;

    while ( fgets( buffer, BSIZE, in) != NULL ) {

        while ( fgets( buffer, BSIZE, in) != NULL && buffer[0] != '\n' ) {
            int last_digit = strlen( buffer ) - 1;
            if (buffer[ last_digit ] == '\n')
                buffer[ last_digit ] = '\0';

            char *dig_numbers;
            dig_numbers = strtok( buffer, " " );

            ll map[3];

            for (int i = 0; i < 3; ++i) {
                map[i] = atoll( dig_numbers );
                dig_numbers = strtok ( NULL, " " );
            }

            if (min == -1)
                min = map[0];
            else if (map[0] != 0 && map[0] < min)
                min = map[0];

            free( dig_numbers );
        }
    }

    printf("%llu\n", min);

    fclose( in );

    return EXIT_SUCCESS;
}