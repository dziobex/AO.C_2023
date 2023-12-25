#include "priority_queue.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

void init_queue( p_queue* pq ) {
    pq->size = 0;
}

void push_q( p_queue* pq, cell* push_me ) {
    int index_put = 0;

    while ( index_put < pq->size && pq->cells[index_put]->min_path < push_me->min_path)
        ++index_put;

    pq->size++;
    for ( int i = pq->size - 1; i > index_put; --i )
        pq->cells[i] = pq->cells[i - 1];

    pq->cells[index_put] = push_me;
}

cell* pop_q( p_queue* pq ) {
    cell* tr = pq->cells[0];

    pq->size--;
    for( int i = 0; i < pq->size; ++i )
        pq->cells[i] = pq->cells[i+1];

    return tr;
}
