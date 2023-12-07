#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define B_SIZE 100
#define H_SIZE 5 
#define H_COUNT 1001
#define ll long long

typedef struct {
    char hand[ H_SIZE + 1];
    int bid;
    int type;
} card;

card create_card( char hand[H_SIZE], int bid, int type ) {
    card n_card = (card) { .bid = bid, .type = type };
    strncpy(n_card.hand + 1, hand, H_SIZE);
    n_card.hand[0] = (char)(type + '0');
    return n_card;
}

int calculate_type( char hand[H_SIZE] ) {
    char monitor[ 100 ] = {};

    for ( int i = 0; i < H_SIZE; ++i )
        monitor[ (int)hand[i] ]++;
    
    int max = 0;
    int min = H_SIZE;
    for ( int i = 0; i < 100; ++i) {
        if ( monitor[i] > max)
            max = monitor[i];
        if ( monitor[i] != 0 && monitor[i] < min)
            min = monitor[ i ];
    }
    
    if ( max >= 4)
        return max + 2; // czyli typy 6, 7
    if ( max == 3 && min == 2)
        return 5;
    if (max == 3 && min == 1)
        return 4;
    if (min == 1 && max == 1)
        return 1;
    
    int count_pairs = 0;
    for ( int i = 0; i < 100; ++i )
        if ( monitor[i] == 2 )
            ++count_pairs;
    
    if (count_pairs == 2)
        return 3; // 2 pary, 1 inny
    return 2; // 1 para, 3 inne
}

static char compare[100] = {};

int cmp_cards(const void *c1, const void *c2) {
    const card *card_1 = (const card *)c1;
    const card *card_2 = (const card *)c2;

    for (int i = 0; i <= H_SIZE; ++i) {
        if (compare[card_1->hand[i]] > compare[card_2->hand[i]])
            return 1;
        else if (compare[card_1->hand[i]] < compare[card_2->hand[i]])
            return -1;
    }

    return 0;
}

int main( int argc, char **argv ) {
    // zainicjuj compare wartosci
    for ( int i = 2; i <= 9; ++i )
        compare[ i + (int)'0' ] = i;
    compare['T'] = 10;
    compare['J'] = 11;
    compare['Q'] = 12;
    compare['K'] = 13;
    compare['A'] = 14;

    FILE *in = fopen( "in.txt", "r" );

    if ( in == NULL )
        return EXIT_FAILURE;
    
    char buffer[B_SIZE];

    card deck[ H_COUNT ];
    int cards_count = 0;

    while ( fgets( buffer, B_SIZE, in ) != NULL ) {
        int last_index = strlen( buffer ) - 1;
        if ( buffer[last_index] == '\n' )
            buffer[last_index] = '\0';
        
        char *temp_buff;

        temp_buff = strtok( buffer, " " );
        char hand[ H_SIZE ];
        strncpy(hand, temp_buff, H_SIZE );

        temp_buff = strtok( NULL, " " );
        int bid = atoi( temp_buff );

        int type = calculate_type( hand );

        deck[ cards_count ] = create_card( hand, bid, type );
        cards_count++;

        free( temp_buff );
    }

    qsort( deck, cards_count, sizeof(card), cmp_cards );
    ll sum = 0;

    for ( int i = 0; i < cards_count; ++i ) {
        sum += (i + 1) * deck[i].bid;
    }

    printf("%i\n", sum);

    fclose( in );

    return EXIT_SUCCESS;
}