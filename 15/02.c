#include <stdio.h>
#include <stdlib.h>

#include <string.h>

#define BUFFER_SIZE 25000
#define DRAWER_SIZE 256

typedef struct {
    char *label;
    int value;
} lens;

lens init_len( char *lbl, int vl ) {
    lens new_len;
    int length = strlen( lbl ) + 1;
    new_len.label = malloc( length );
    memcpy( new_len.label, lbl, length );
    new_len.value = vl;
    return new_len;
}

typedef struct {
    lens *lenses;
    int size;
} box;

box init_box() {
    box bx;
    bx.lenses = NULL;
    bx.size = 0;
    return bx;
}

int get_box_number( char *label) {
    int sum = 0;
    for ( char* p = label; *p != '\0'; ++p )
        sum = (( sum + *p) * 17 ) % 256;
    return sum;
}

int find_in_box( box *box, lens l ) {
    if ( box->lenses != NULL)
        for ( int i = 0; i < box->size; ++i)
            if ( strcmp( box->lenses[i].label, l.label ) == 0 )
                return i;
    return -1; // nie znaleziono
}

void update_box( box *box, lens l ) {
    if ( box->lenses == NULL ) {
        box->lenses = (lens*)malloc( sizeof(lens) );
        box->lenses[0] = l;
        box->size++;
        return;
    }
    int l_index = find_in_box( box, l );
    if ( l_index != -1 ) {
        box->lenses[ l_index ] = l;
        return;
    }
    box->lenses = realloc( box->lenses, sizeof( lens) * ( box->size + 1) );
    box->lenses[ box->size++ ] = l;
}

void remove_from_box( box *box, lens l ) {
    int l_index = find_in_box( box, l );
    if (l_index == -1 )
        return;
    box->size--;
    for ( int i = l_index; i < box->size; ++i )
        box->lenses[i] = box->lenses[i + 1];
    box->lenses = ( lens* )realloc( box->lenses, sizeof(lens) * box->size );
}

int main( int argc, char **argv ) {
    FILE *in = fopen( "input.txt", "r" );
    if ( in == NULL )
        return fprintf( stderr, "Nie udalo sie otworzyc pliku!" ), EXIT_FAILURE;
    
    char buffer[ BUFFER_SIZE ];
    if ( fgets( buffer, BUFFER_SIZE, in ) == NULL )
        return fprintf( stderr, "Cos jest nie tak z plikiem :/" ), EXIT_FAILURE;
    fclose( in );
    
    char *temp, *inner, *outer;
    temp = strtok_s( buffer, ",", &outer );

    box boxes[DRAWER_SIZE] = {};
    for ( int i = 0; i < DRAWER_SIZE; ++i )
        boxes[i] = init_box();

    while ( temp != NULL ) {
        char sign = strchr( temp, '=' ) == NULL ? '-' : '=';

        int value = sign == '=' ? temp[ strlen(temp) - 1] - '0' : 0;
        char *label = strtok_s( temp, "=-", &inner);
    
        int box_nr = get_box_number( label );
        lens len = init_len( label, value );

        if ( sign == '=' )
            update_box( &boxes[box_nr], len );
        else
            remove_from_box( &boxes[box_nr], len );

        temp = strtok_s( NULL, ",", &outer );
        free( label );
    }

    int total_sum = 0;

    for ( int i = 0; i < DRAWER_SIZE; ++i ) {
        if ( boxes[i].size == 0 )
            continue;
        for ( int j = 0; j < boxes[i].size; ++j )
            total_sum += ( i + 1 ) * ( j + 1 ) * boxes[i].lenses[j].value;
        free( boxes[i].lenses );
    }

    printf( "%i", total_sum );

    free( temp );
    free( inner );
    free( outer );

    return EXIT_SUCCESS;
}