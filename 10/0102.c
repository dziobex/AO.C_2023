#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 150
#define MATRIX_SIZE 150
#define minimum( a, b ) ( ( (a) < (b) ) ? (a) : (b) )

typedef struct node node;

struct node {
    char label;
    int path_one, path_two;
    node *dirs[4];
};

void init_node( node *n, char label,
    node *top, node *right, node *bottom, node *left ) {
        n->label = label;
        n->path_one = -1;
        n->path_two = -1;
        n->dirs[0] = top;
        n->dirs[1] = right;
        n->dirs[2] = bottom;
        n->dirs[3] = left;
}

typedef struct {
    node **nodes;
    int size;
} node_stack;

node_stack create_stack() {
    return (node_stack) { .size = 0 };
}

void init_stack( node_stack *stack, node *first_n ) {
    stack->size = 1;
    stack->nodes = ( node** )malloc( sizeof( node* ) );
    stack->nodes[0] = first_n;
}

void push_node( node_stack *stack, node *n ) {
    stack->nodes = ( node** )realloc( stack->nodes, sizeof( node* ) * ( stack->size + 1 ) );
    stack->nodes[ stack->size ] = n;
    stack->size++;
}

node *pop_node(node_stack *stack) {
    node *to_get = stack->nodes[ --stack->size ];
    stack->nodes = ( node** )realloc( stack->nodes, sizeof( node* ) * ( stack->size ) );
    return to_get;
}

int main( int argc, char **argv ) {

    FILE *in = fopen( "in.txt", "r" );

    if ( in == NULL )
        return EXIT_FAILURE;

    char buffer[ BUFFER_SIZE ];
    
    node matrix[ MATRIX_SIZE ][ MATRIX_SIZE ];
    node *s_node;

    int line = 0;
    int lines = 0;

    while( fgets( buffer, BUFFER_SIZE, in ) != NULL ) {
        int line_size = strlen( buffer );
        if ( buffer[ line_size - 1 ] == '\n')
            buffer[ --line_size ] = '\0';
        
        for( int i = 0; i < line_size; ++i ) {
            init_node(&matrix[ lines ][ i ], buffer[ i ], NULL, NULL, NULL, NULL );
            if ( buffer[i] == 'S' )
                s_node = &matrix[ lines ][ i ]; 
        }

        ++lines;
        if (line == 0) line = line_size;
    }

    for ( int y = 0; y < lines; ++y ) {
        for( int x = 0; x < line; ++x ) {
            node *top = NULL;
            if ( y > 0  && strchr("F|7", matrix[ y - 1 ][ x ].label ) != NULL
                && (matrix[ y ][ x ].label == 'S' || strchr("L|J", matrix[ y ][ x ].label)  != NULL) )
                top = &matrix[ y - 1][ x ];
            node *right = NULL;
            if ( x + 1 < line && strchr( "J-7", matrix[ y ][x + 1].label ) != NULL
                && (matrix[ y ][ x ].label == 'S' || strchr( "L-F", matrix[ y ][ x ].label) != NULL ))
                right = &matrix[ y ][ x + 1 ];
            node *bottom = NULL;
            if ( y + 1 < lines && strchr( "L|J", matrix[ y + 1 ][ x ].label ) != NULL
                && (matrix[ y ][ x ].label == 'S' || strchr("F|7", matrix[ y ][ x ].label ) != NULL) )
                bottom = &matrix[ y + 1 ][ x ];
            node *left = NULL;
            if ( x > 0 && strchr( "L-F", matrix[ y ][ x - 1 ].label ) != NULL
                && (matrix[ y ][ x ].label == 'S' || strchr( "J-7", matrix[ y ][x ].label ) != NULL))
                left = &matrix[ y ][ x - 1 ];
            init_node(&matrix[ y ][ x ], matrix[ y ][ x ].label, top, right, bottom, left );
        }
    }

    node_stack stack_one = create_stack(), stack_two = create_stack();

    for ( int i = 0; i < 4; ++i ) {
        if ( s_node->dirs[i] != NULL ) {
            if ( stack_one.size == 0 )
                init_stack( &stack_one, s_node->dirs[i] );
            else {
                init_stack( &stack_two, s_node->dirs[i] );
                break;
            }
        }
    }

    /* ---- PART 1 ---- */

    int step = 1, max = 0;

    while ( stack_one.size > 0 || stack_two.size > 0 ) {

        // st 1
        if ( stack_one.size > 0 ) {
            node *node_one = pop_node ( &stack_one );

            if (node_one->path_one == -1 ) {
                node_one->path_one = step;
                for ( int i = 0; i < 4; ++i )
                    if ( node_one->dirs[i] != NULL && node_one->dirs[i]->path_one == -1 )
                        push_node( &stack_one, node_one->dirs[i] );
            }
        }

        // st 2
        if ( stack_two.size > 0 ) {
            node *node_two = pop_node ( &stack_two );

            if (node_two->path_two == -1 ) {
                node_two->path_two = step;

                if ( node_two->path_one != -1 ) {
                    int value = node_two->path_one > node_two->path_two ? node_two->path_two : node_two->path_one;
                    if (value > max)
                        max = value;
                }
                for ( int i = 0; i < 4; ++i )
                    if ( node_two->dirs[i] != NULL && node_two->dirs[i]->path_two == -1 )
                        push_node( &stack_two, node_two->dirs[i] );
            }
        }

        ++step;
    }

    /* ---- PART 2 ---- */

    int inside_rope = 0;

    /* put start node in rope nodes crowd (it loses its unique identity!) */
    char change = '|'; // top + bottom

    if ( s_node->dirs[0] != NULL && s_node->dirs[1] != NULL )
        change = 'L';
    else if ( s_node->dirs[0] != NULL && s_node->dirs[3] != NULL )
        change = 'J';
    else if ( s_node->dirs[1] != NULL && s_node->dirs[3] != NULL )
        change = '-';
    else if ( s_node->dirs[2] != NULL && s_node->dirs[3] != NULL )
        change = '7';
    else if ( s_node->dirs[2] != NULL && s_node->dirs[1] != NULL )
        change = 'F';

    s_node->label = change;
    s_node->path_one = s_node->path_two = 0;

    for ( int y = 0; y < lines; ++y ) {
        for ( int x = 0; x < line; ++x ) {
            int part_of_rope = minimum( matrix[y][x].path_one, matrix[y][x].path_two ) != -1;
            
            if ( part_of_rope == 1 || matrix[y][x].label == 'S')
                continue;
            
            int in_rope = 0;

            for ( int z = 0; z < x; ++z ) {
                int por = minimum( matrix[y][z].path_one, matrix[y][z].path_two ) != -1;

                if ( por != 0 && strchr( "|F7", matrix[y][z].label ) != NULL)
                    ++in_rope;
            }
            
            if ( in_rope % 2 != 0 )
                inside_rope++;
        }
    }

    printf("01: %i\n02: %i\n", max, inside_rope);
    
    return EXIT_SUCCESS;
}