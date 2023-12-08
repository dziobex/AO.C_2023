#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct element element;

struct element {
    char my_label[4];
    char l_label[4], r_label[4];

    element *right;
    element *left;
};

element create_element( char label[4], char left[4], char right[4] ) {
    element e;
    strncpy( e.my_label, label, 4);
    strncpy( e.l_label, left, 4);
    strncpy( e.r_label, right, 4);

    e.right = NULL;
    e.left = NULL;

    return e;
}

int main( int argc, char **argv ) {

    FILE *in = fopen( "in.txt", "r" );

    if ( in == NULL )
        return EXIT_FAILURE;

    char commands[300];

    fscanf(in, "%s\n", commands);

    char _label[4], _left[4], _right[4];
    element elements[1000];
    int elements_count = 0;

    while (fscanf(in, "%3s = (%3s, %3s)\n", _label, _left, _right) == 3)
        elements[ elements_count++ ] = create_element( _label, _left, _right );

    for ( int i = 0; i < elements_count; ++i ) {
        int found = 0;

        for ( int j = 0; j < elements_count; ++j ) {
            if ( found == 2 ) break;

            if ( strcmp( elements[ i ].l_label, elements[ j ].my_label ) == 0) {
                elements[i].left = &elements[j];
                ++found;
            }
            if ( strcmp( elements[ i ].r_label, elements[ j ].my_label ) == 0) {
                elements[i].right = &elements[j];
                ++found;
            }
        }
    }
    
    fclose( in );

    int steps = 0;
    int commands_count = strlen( commands );
    int c_el = 0;
    element *curr = NULL;

    for ( int i = 0; i < elements_count; ++i )
        if ( strcmp( elements[ i ].my_label, "AAA" ) == 0) {
            curr = &elements[ i ];
            break;
        }

    while ( 1 ) {
        curr = commands[ c_el ] == 'L' ? curr->left : curr->right;
        
        ++steps;

        if ( strcmp(curr->my_label, "ZZZ") == 0 ) break;

        if ( ++c_el >= commands_count )
            c_el = 0;
    }

    printf("%i\n", steps);

    free( curr );

    return EXIT_SUCCESS;
}