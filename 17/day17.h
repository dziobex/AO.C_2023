#ifndef _DAY_17_
#define _DAY_17_

#define BUFFER_SIZE 150
#define GRID_DIM 150
#define MAX_CONS_BLOCKS 3
#define MAX_CELLS_LOOKS 10000

typedef struct {
    int heat_loss;      // informacja o utracie ciepła (z pliku wejściowego)
    int y, x;           // położenie na gridzie
    char dir;           // kierunek | - w którym znajduje się trasa do komórki
    int visited;        // flaga, czy dana komórka została już odwiedzona
    int min_path;       // minimalna droga do TEJ komórki
} cell;

void init_cell( cell *_cell, int y, int x, int heat_loss, char dir );      // inicjacja komórki (jej 'oryginału') i jej kopii uwzgl. kierunki skąd porusza się ścieżka

#endif