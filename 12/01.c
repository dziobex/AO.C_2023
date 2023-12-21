#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 150
#define RECORD_SIZE 50

int valid_record( char record[ RECORD_SIZE ], int record_size, int info[ RECORD_SIZE ], int info_size) {
    int values_size = 0;
    int values[ RECORD_SIZE ] = {0};

    for( int i = 0; i < record_size; ++i ) {
        if ( record[i] == '#' )
            ++values[ values_size ];
        else if ( values[values_size] != 0)
            ++values_size;
    }
    if ( values[ values_size ] != 0)
        ++values_size;
    if ( values_size != info_size )
        return 1;
    for ( int i = 0; i < values_size; ++i )
        if ( values[i] != info[i] )
            return 1;
    return 0;
}

void brute( char record[ RECORD_SIZE ], int record_size, int info[ RECORD_SIZE ], int info_size, int index, int *ways ) {
    if ( index >= record_size ) {
        if ( valid_record(record, record_size, info, info_size ) == 0 )
            (*ways)++;
        return;
    }

    if ( record[ index ] != '?' ) {
        brute( record, record_size, info, info_size, index + 1, ways );
        return;
    }

    // as '#'
    record[ index ] = '#';
    brute( record, record_size, info, info_size, index + 1, ways );

    // as '.'
    record[ index ] = '.';
    brute( record, record_size, info, info_size, index + 1, ways );

    record[ index ] = '?';

}

int main( int argc, char **argv ) {
    FILE *in = fopen( "in.txt", "r" );

    if ( in == NULL )
        return fprintf( stderr, "Nie udalo sie otworzyc pliku :(" ), EXIT_FAILURE;

    char buffer[ BUFFER_SIZE ];

    char record[ RECORD_SIZE ], dets[ RECORD_SIZE ];

    int ways = 0;

    while( fscanf( in, "%s %s", record, dets) == 2 ) {
        int info_size = 0, record_size = strlen( record );

        int info[ RECORD_SIZE ] = {0};
        char *tmp;
        tmp = strtok( dets, "," );

        while ( tmp != NULL ) {
            info[ info_size++ ] = atoi( tmp );
            tmp = strtok( NULL, "," );
        }
    
        brute( record, record_size, info, info_size, 0, &ways );
    }
    fclose( in );

    printf( "%i", ways );

    return EXIT_SUCCESS;
}