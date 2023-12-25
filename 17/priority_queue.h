#ifndef _PRIORITY_QUEUE_
#define _PRIORITY_QUEUE_

#include "day17.h"

#define P_QUEUE_MAX_SIZE 25000

// własna implementacja kopca (kolejki priorytetowej)
// priorytet - minimalna ścieżka: im mniejsza, tym pierwsza

typedef struct {
    int size;
    cell* cells[P_QUEUE_MAX_SIZE];
} p_queue;

void init_queue( p_queue* pq );             // jakieś inicjalizacje raczkującego kopca
void push_q( p_queue* pq, cell* push_me );  // dodaj element do kopca
cell* pop_q( p_queue* pq );                 // zdjemij i pokaż pierwszy element z kopca

#endif