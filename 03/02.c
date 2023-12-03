#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#include "day3.h"

int main( int argc, char **argv ) {
    FILE *in = fopen( "in.txt", "r" );

    if (in == NULL)
        return fputs("Nie udalo sie otworzyc pliku!", stderr), EXIT_FAILURE;

    char buffer[BSIZE];
    int row = 0;

    number_set n_set;
    init_number_set( &n_set );
    sign_set s_set;
    init_sign_set( &s_set );

    while ( fgets( buffer, BSIZE, in ) != NULL ) {
        // usuniecie znaku nowej linii
        if (buffer[ strlen( buffer ) - 1] == '\n')
            buffer[ strlen( buffer ) - 1] = '\0';

        int line_width = strlen( buffer );

        // skanujemy w poszukiwaniu liczb ORAZ dodajemy ja do agregatora gdy liczba sie 'skonczy'
        for (int i = 0; i < line_width; ++i) {

            if ( isdigit( buffer[i] ) ) {
                int s_i = i;

                while ( isdigit ( buffer[i] ) && i < line_width)
                    ++i;

                number num;
                num = create_number( buffer, row, s_i, i - 1 );

                add_number( &n_set, &num );
            }

            if ( !isdigit( buffer[i] ) && buffer[i] != '.' && buffer[i] != '\0' ) {
                // dodaj znak!
                sign sgn;

                int s_i = i > 0 ? i - 1 : i;
                int f_i = i + 1 >= line_width ? i : i + 1;

                sgn = create_sign( row, s_i, f_i, buffer[i] );
                add_sign( &s_set, &sgn );
            }
        }

        ++row;
    }

    int sum = 0;
    for ( int i = 0; i < s_set.length; ++i ) {

        if (s_set.set[i].rep == '*') {

            for ( int j = 0; j < n_set.length; ++j ) {
                if ( overlap( n_set.set[j], s_set.set[i] ) == 1 ) {
                    s_set.set[i].adj++;
                    s_set.set[i].adj_value *= n_set.set[j].value;
                }
            }
        }
    }

    for ( int i = 0; i < s_set.length; ++i ) {
        if ( s_set.set[i].rep != '*' )
            continue;
        if (s_set.set[i].adj >= 2)
            sum += s_set.set[i].adj_value;
    }

    printf( "%i\n", sum );

    clear_number_set( &n_set );
    clear_sign_set( &s_set );

    return EXIT_SUCCESS;
}