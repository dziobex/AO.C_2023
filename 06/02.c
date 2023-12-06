#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define BSIZE 100
#define ll long long

int main( int argc, char **argv ) {

    FILE *in = fopen( "in.txt", "r" );

    if ( in == NULL )
        return EXIT_FAILURE;
    
    char buffer[ BSIZE ];
    char *tmp;

    ll time = 1;
    ll dist = 1;
    
    for (int i = 0; i < 2; ++i) {

        fgets( buffer, BSIZE, in );
        if (buffer[ strlen( buffer ) - 1] == '\n')
            buffer[ strlen( buffer ) - 1] = '\0';
        
        tmp = strtok( buffer, " " );
        
        ll whole_num = 0;

        while ( 1 ) {
            if (( tmp = strtok( NULL, " " ) ) == NULL)
                break;

            whole_num = whole_num * pow(10, strlen(tmp)) + atoll( tmp );
        }

        if ( i == 0)
            time = whole_num;
        else
            dist = whole_num;

        free (tmp);
    }
    
    fclose( in );

    ll beat = 0;

    for (int h = 0; h <= time; ++h ) {
        /* h = speed (per ms) */
        ll total_dist = h * (time - h);

        if (total_dist > dist)
            ++beat;
        else if (beat > 0)
            break;
    }

    printf("%llu", beat);

    return EXIT_SUCCESS;
}