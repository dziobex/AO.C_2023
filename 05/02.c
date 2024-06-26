#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define BSIZE 300
#define ll unsigned long long

typedef struct {
    ll a, b;
} range;

int intersects( range st, range nd ) {
    if (st.b < nd.a || nd.b < st.a)
        return 0;
    return 1;
}

int translate( range seeds[1000], int seed_index,  range trans, ll step, int *seeds_count, range new_seeds[1000], int *new_seeds_count ) {
    range current_seed = seeds[ seed_index ];

    /* totalnie nie zwiazane ze soba przedzialy */
    if ( intersects( current_seed, trans ) == 0)
        return 0;

    /* caly przedzial znajduje sie w przedziale przenoszalnym - przeniesc! */
    if ( trans.a <= current_seed.a && current_seed.b <= trans.b ) {

        current_seed.a = ( current_seed.a - trans.a ) + step;
        current_seed.b = ( current_seed.b - trans.a ) + step;

        new_seeds[ *new_seeds_count ] = current_seed;
        (*new_seeds_count)++;

        for (int i = seed_index; i < *seeds_count - 1; ++i)
            seeds[i] = seeds[i + 1];
        --(*seeds_count);

        return 1;
    }

    /* czesc przedzialu - caly od poczatku do pewnego momentu - do przeniesienia! */
    if ( trans.a <= current_seed.a && trans.b < current_seed.b ) {
        range new_one;
        new_one.a = ( current_seed.a - trans.a ) + step;
        new_one.b = ( trans.b - trans.a ) + step;

        current_seed.a = trans.b + 1;
        seeds[ seed_index ] = current_seed;
        new_seeds[ *new_seeds_count ] = new_one;
        (*new_seeds_count)++;

        return 0;
    }

    /* czesc przedzialu - od pewnego poczatku do calego konca - do przeniesienia! */
    if ( current_seed.a < trans.a && current_seed.b <= trans.b ) {
        range new_one;
        new_one.a = step;
        new_one.b = ( current_seed.b - trans.a ) + step;
        
        current_seed.b = trans.a - 1;

        seeds[ seed_index ] = current_seed;
        new_seeds[ *new_seeds_count ] = new_one;
        (*new_seeds_count)++;

        return 0;
    }

    /* czesc przenoszalna znajduje sie w srodku przedzialu - przeniesc ta przenoszalna, reszte oddzielic, zostawic! */

    new_seeds[ *new_seeds_count ].a = step;
    new_seeds[ *new_seeds_count ].b = trans.b - trans.a + step;
    (*new_seeds_count)++;
    
    range new_one;
    new_one.a = trans.b + 1;
    new_one.b = current_seed.b;
    current_seed.b = trans.a - 1;

    seeds[ seed_index ] = current_seed;
    seeds[*seeds_count] = new_one;
    (*seeds_count)++;

    return 0;
}

int main( int argc, char **argv ) {
    FILE *in = fopen( "in.txt", "r" );

    if ( in == NULL )
        return fputs("Nie mozna zaladowac pliku!", stderr), EXIT_FAILURE;
    
    char buffer[BSIZE];

    int seeds_count = 0;
    range seeds[1000];

    if (fgets(buffer, BSIZE, in) != NULL) {
        buffer[ strlen(buffer) - 1] = '\0';

        char *tmp;
        tmp = strtok(buffer, " ");

        while (1) {
            if ( (tmp = strtok(NULL, " ")) == NULL)
                break;
            ll start = atoll( tmp );
            tmp = strtok(NULL, " ");
            ll end = atoll( tmp );

            range new_seed;
            new_seed.a = start;
            new_seed.b = start + end - 1;
            seeds[ seeds_count++ ] = new_seed;
        }

        free( tmp );
    }
    fgets( buffer, BSIZE, in); // biore zagubionego next linea

    while ( fgets( buffer, BSIZE, in) != NULL ) {
        
        seeds;
        int new_seeds_count = 0;
        range next_gen[1000] = {};

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

            range translation;
            translation.a = map[1];
            translation.b = map[1] + map[2] - 1;

            // for loop, pozamieniaj
            for ( int i = 0; i < seeds_count; ++i)
                if ( translate(seeds, i, translation, map[0], &seeds_count, next_gen, &new_seeds_count ) == 1)
                    --i;
            free( dig_numbers );
        }

        for (int i = 0; i < new_seeds_count; ++i) {
            seeds[seeds_count] = next_gen[i];
            seeds_count++;

        }
    }

    ll min_e = seeds[0].a;

    for (int i = 0; i < seeds_count; ++i)
        if (seeds[i].a < min_e)
            min_e = seeds[i].a;
    
    printf( "%llu", min_e );

    fclose( in );

    return EXIT_SUCCESS;
}