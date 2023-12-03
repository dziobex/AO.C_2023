#ifndef _DAY_3_H_
#define _DAY_3_H_

#define BSIZE 300

typedef struct {
    int row;
    int s_index;
    int f_index;

    int value;
    int in_engine;
} number;

number create_number( char buffer[BSIZE], int row, int s_index, int f_index );

typedef struct {
    number *set;
    int length;
} number_set;

void init_number_set( number_set *ns );
void add_number( number_set *ns, number *n );
void clear_number_set( number_set *ns );

typedef struct {
    char rep;
    int row;
    int s_index;
    int f_index;

    int adj;
    int adj_value;
} sign;

sign create_sign( int row, int s_i, int f_i, char rep );

typedef struct {
    sign *set;
    int length;
} sign_set;

void init_sign_set( sign_set *ss );
void add_sign( sign_set *ss, sign *s );
void clear_sign_set( sign_set *ss );

int overlap( number num, sign sgn );

#endif