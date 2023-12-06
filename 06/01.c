#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BSIZE 100

typedef struct {
    int time;
    int distance;
} race;

int main( int argc, char **argv ) {

    FILE *in = fopen( "in.txt", "r" );

    if ( in == NULL )
        return EXIT_FAILURE;
    
    char buffer[ BSIZE ];
    char *tmp;

    int records = 0;

    race *races;
    races = NULL;
    
    for (int i = 0; i < 2; ++i) {

        fgets( buffer, BSIZE, in );
        if (buffer[ strlen( buffer ) - 1] == '\n')
            buffer[ strlen( buffer ) - 1] = '\0';
        
        tmp = strtok( buffer, " " );
        int r_index = 0;

        while ( 1 ) {
            if (( tmp = strtok( NULL, " " ) ) == NULL)
                break;

            int numeric = atoi( tmp );
            ++r_index;

            /* pierwsza linia czytana - zainicjalizowac wszystko */
            if ( i == 0 ) {
                if ( races == NULL )
                    races = (race*)malloc( sizeof( race ) );
                else
                    races = (race*)realloc( races, sizeof( race ) * r_index );
                races[ r_index - 1].time = numeric;
            } else
                races[ r_index - 1].distance = numeric;
        }

        if (records == 0)
            records = r_index;

        free (tmp);
    }
    
    fclose( in );

    int beat_total = 1;

    for (int i = 0; i < records; ++i) {

        int beat = 0;

        for (int h = 0; h <= races[i].time; ++h ) {
            /* h = speed (per ms) */
            int total_dist = h * (races[i].time - h);

            if (total_dist > races[i].distance)
                ++beat;
            else if (beat > 0)
                break;
        }

        if (beat != 0)
            beat_total *= beat;
    }

    printf("%i\n", beat_total);

    return EXIT_SUCCESS;
}