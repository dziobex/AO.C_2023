#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define ll long long
#define CORDS_COUNT 1000

// Zastosowane algorytmy: Wzory Gaussa, wzór Picka

typedef struct {
    ll y, x;
} cord;

cord init_cord( ll y, ll x ) {
    return (cord) { .y = y, .x = x };
}

int main( int argc, char **argv ) {
    FILE *in = fopen( "in.txt", "r" );

    if ( in == NULL )
        return fprintf( stderr, "Nie udalo sie otworzyc pliku :(" ), EXIT_FAILURE;

    char dir, d;
    int value, col;

    ll x = 0, y = 0, perimeter = 0;

    cord cords[CORDS_COUNT];
    int n = 0;
    cords[n++] = init_cord( y, x );

    while( fscanf( in, "%c %d (#%5x%1s)\n", &dir, &value, &col, &d) == 4) {
        // 0 means R, 1 means D, 2 means L, and 3 means U
        d = d == '0' ? 'R' : ( d == '1' ? 'D' : ( d == '2' ? 'L' : 'U' ) );

        value = col;
        dir = d;

        perimeter += value;

        if ( dir == 'U' )
            y -= (ll)value;
        else if ( dir == 'D' )
            y += (ll)value;
        else if ( dir == 'L')
            x -= (ll)value;
        else if ( dir == 'R' )
            x += (ll)value;

        cords[n++] = init_cord( y, x );
    }
    
    // gauss' formula
    ll field = 0;
    for ( int i = 0; i < n; ++i ) {
        int prev = i - 1 < 0 ? n - 1 : i - 1;
        int next = i + 1 >= n ? 0 : i + 1;
        field += ( cords[i].x ) * ( cords[next].y - cords[prev].y );
    }

    // gauss formula & pick's theorem
    field = field / 2 + perimeter / 2 + 1;
    printf( "%lld", field);

    fclose( in );

    return EXIT_SUCCESS;
}