#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 150
#define CELLS_GRID_DIM 150
#define MAX_BEANS_COUNT 10000

typedef struct {
    char label;
    int visited;    // 0 = nieodwiedzona, 1 = odwiedzona
    char visits[120];
} cell;

typedef struct {
    char dir;
    int x, y;
    int to_kill;    // flaga: czy dany strumień trzeba usunąć?
} bean;

void init_cell( cell *c, char label ) {
    c->label = label;
    c->visited = 0;
    c->visits['^'] = c->visits['v'] = c->visits['<'] = c->visits['>'] = 0;
}

bean init_bean( char dir, int x, int y ) {
    return (bean){ .dir = dir, .x = x, .y = y, .to_kill = 0 };
}

static cell grid[CELLS_GRID_DIM][CELLS_GRID_DIM];
static bean beans[MAX_BEANS_COUNT];
static int grid_size = 0, beans_count = 0;

void move_bean( bean* b ) {
    switch ( b->dir ) {
        case '>': b->x++; break;
        case '<': b->x--; break;
        case 'v': b->y++; break;
        case '^': b->y--; break;
        default: break;
    }

    if ( b->x < 0 || b->x >= grid_size || b->y < 0 || b->y >= grid_size ) { // wychód poza mapę
        b->to_kill = 1;
        return;
    }

    grid[ b->y ][b ->x ].visited = 1;
    if ( grid[ b->y ][b ->x ].visits[ b->dir ] > 0) // po co wynajdywać koło na nowo?
        b->to_kill = 1;
    grid[ b->y ][b->x ].visits[ b->dir ] = 1; // flaga że tu byłem dla kolejnych odkrywców :-)
}

void remove_bean( int nth ) {
    --beans_count;
    for ( int i = nth; i < beans_count; ++i )
        beans[i] = beans[i + 1];
}

void act_bean( bean* b ) {  // rotacja strumienia, ewentualnie rozszczepienie go
    char on_map = grid[ b->y ][ b->x ].label;
    
    if ( on_map == '.' || (on_map == '-' && ( b->dir == '>' || b->dir == '<' )) || (on_map == '|' && ( b->dir == '^' || b->dir == 'v' )) )
        return;
    
    if ( on_map == '\\' ) {
        if ( b->dir == '>' ) { b->dir = 'v'; return; }
        if ( b->dir == '<' ) { b->dir = '^'; return; }
        if ( b->dir == '^' ) { b->dir = '<'; return; }
        if ( b->dir == 'v' ) { b->dir = '>'; return; }
    }
    if ( on_map == '/' ) {
        if ( b->dir == '>' ) { b->dir = '^'; return; }
        if ( b->dir == '<' ) { b->dir = 'v'; return; }
        if ( b->dir == '^' ) { b->dir = '>'; return; }
        if ( b->dir == 'v' ) { b->dir = '<'; return; }
    }
    if ( on_map == '|' ) {
        b->dir = '^';
        beans[beans_count++] = init_bean( 'v', b->x, b->y );
    }
    if ( on_map == '-' ) {
        b->dir = '<';
        beans[beans_count++] = init_bean( '>', b->x, b->y );
    }
}

void reset( void ) {
    beans_count = 0;
    for ( int i = 0; i < grid_size; ++i )
        for ( int j = 0; j < grid_size; ++j )
            init_cell( &grid[i][j], grid[i][j].label );
}

void bean_soup( int *max_en, int py, int px, char ls ) {
    reset();

    beans[beans_count++] = init_bean( ls, px, py );
    grid[py][px].visited = 1;

    while ( beans_count > 0 ) {
        // reagowanie strumieńków na poszczególne 'specjalne' kafelki siatki: /\|-
        int old_count = beans_count;
        for ( int i = 0; i < old_count; ++i )
            act_bean( &beans[i] );

        // przesunięcie wszystkich strumieni wg ich kierunków
        for ( int i = 0; i < beans_count; ++i )
            move_bean( &beans[i] );
        
        // usunięcie strumieni oznaczonych jako 'do usunięcia'
        for ( int i = 0; i < beans_count; ++i )
            if ( beans[i].to_kill == 1 ) {
                remove_bean( i );
                --i;
            }
    }

    int energized = 0;  // 'szybkie' sumowanie ile kafelków jest pod napięciem po całej akcji
    for ( int i = 0; i < grid_size; ++i )
        for ( int j = 0; j < grid_size; ++j )
            energized += grid[i][j].visited;

    if ( energized > *max_en )  // ustawienie wartości maksymalnej
        *max_en = energized;
}

int main( int argc, char **argv ) {
    FILE *in = fopen( "in.txt", "r" );

    if ( in == NULL )
        return fprintf( stderr, "Nie udalo sie otworzyc pliku :(" ), EXIT_FAILURE;

    char buffer[ BUFFER_SIZE ];
    int line = 0;

    while ( fgets(buffer, BUFFER_SIZE, in ) != NULL ) {
        if ( grid_size == 0 )
            grid_size = strlen( buffer) - 1;
        for ( int i = 0; i < grid_size; ++i )
            init_cell( &grid[line][i], buffer[i] );
        ++line;
    }
    fclose( in );

    int max_en = 0;

    bean_soup( &max_en, 0, 0, '>' );    // start dla p.1 znajduje się w tym punkcie
    printf( "Part 1: %i\n", max_en );
    
    for ( int a = 0; a < grid_size; ++a ) { // całe szczęście że to nie jest wolne!
        bean_soup( &max_en, 0, a, 'v' );
        bean_soup( &max_en, grid_size - 1, a, '^' );
        bean_soup( &max_en, a, 0, '>' );
        bean_soup( &max_en, a, grid_size - 1, '<' );
    }

    printf( "Part 2: %i", max_en );

    return EXIT_SUCCESS;
}