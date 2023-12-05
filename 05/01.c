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
    ll *seeds;
    seeds = NULL;

    if (fgets(buffer, BSIZE, in) != NULL) {
        buffer[ strlen(buffer) - 1] = '\0';

        char *tmp;
        tmp = strtok(buffer, " ");

        while (1) {
            tmp = strtok(NULL, " ");
            if (tmp == NULL)
                break;
            ++seeds_count;
            if (seeds_count == 1)
                seeds = (ll*)malloc( sizeof( ll ) );
            else
                seeds = (ll*)realloc( seeds, seeds_count * sizeof( ll ) );
            seeds[ seeds_count - 1] = atoll( tmp );
        }
        free( tmp );
    }
    fgets( buffer, BSIZE, in); // biore zagubionego next linea

    while ( fgets( buffer, BSIZE, in) != NULL ) {
        //printf("%s", buffer);

        int *seeded;
        seeded = malloc( sizeof(int) * seeds_count );
        for (int i = 0; i < seeds_count; ++i)
            seeded[i] = 0;

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

            for ( int i = 0; i < seeds_count; ++i ) {
                if ( seeded[i] == 0 && map[1] <= seeds[i] && seeds[i] < map[1] + map[2]) {
                    seeds[i] = map[0] + seeds[i] - map[1];
                    seeded[i] = 1;
                }
            }

            free( dig_numbers );
        }

        free (seeded);
    }

    ll min = seeds[0];
    for ( int i = 0; i < seeds_count; ++i ) {
        if (seeds[i] < min)
            min = seeds[i];
    }
    printf("%llu\n", min);

    free( seeds );

    fclose( in );

    return EXIT_SUCCESS;
}