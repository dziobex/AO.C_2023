#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#include "day3.h"

number create_number( char buffer[BSIZE], int row, int s_index, int f_index ) {
    number n;

    n.value = 0;
    n.in_engine = 0;

    n.row = row;
    n.s_index = s_index;
    n.f_index = f_index;

    for (int i = s_index; i <= f_index; ++i)
        n.value = ( n.value * 10 ) + ( buffer[i] - '0' ); 

    return n;
}

void init_number_set(number_set *ns) {
    ns->length = 0;
    ns->set = NULL;
}

void add_number( number_set *ns, number *n ) {
    ns->length++;

    if (ns->set == NULL) {
        ns->set = ( number* )malloc( sizeof( number ));
        ns->set[ ns->length - 1 ] = (*n);
        return;
    }
    ns->set = ( number* )realloc( ns->set, ns->length * sizeof (number) );
    ns->set[ ns->length - 1 ] = (*n);

}

void clear_number_set( number_set *ns ) {
    free( ns->set );
}

sign create_sign( int row, int s_i, int f_i, char rep ) {
    sign s;

    s.row = row;
    s.s_index = s_i;
    s.f_index = f_i;
    s.rep = rep;

    s.adj = 0;
    s.adj_value = 1;

    return s;
}

void init_sign_set( sign_set *ss ) {
    ss->length = 0;
    ss->set = NULL;
}

void add_sign( sign_set *ss, sign *s ) {
    ss->length++;

    if (ss->set == NULL) {
        ss->set = (sign*)malloc( sizeof(sign) );
        ss->set[0] = *s;
        return;
    }
    ss->set = (sign*)realloc( ss->set, sizeof( sign ) * ss->length);
    ss->set[ ss->length - 1 ] = *s;
}

void clear_sign_set( sign_set *ss ) {
    free( ss->set );
}

int overlap( number num, sign sgn ) {

    if ( abs( num.row - sgn.row ) > 1 )
        return 0;

    if ( num.f_index < sgn.s_index || sgn.f_index < num.s_index)
        return 0; // nie

    return 1; // tak
}