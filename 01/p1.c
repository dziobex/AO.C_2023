#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BSIZE 100

int get_number(char buf[BSIZE], int n) {
    int first = -1;
    int last = -1;

    for (int i = 0; i < n; ++i) {
        char frag = *(buf + i);

        if (frag < '0' || frag > '9')
            continue;
        if (first == -1)
            first = frag - '0';
        last = frag - '0';
    }

    if (first == -1)
        first = last = 0;

    return first * 10 + last;
}

int main (int argc, char ** argv) {
    FILE *in = fopen("input.txt", "r");

    if (in == NULL)
        return fputs("Nie udalo sie otworzyc pliku!", stderr), EXIT_FAILURE;

    char buffer[BSIZE];
    int total = 0;

    while (fgets(buffer, BSIZE, in) != NULL) {
        total += get_number(buffer, strlen(buffer));
    }

    fclose(in);
    printf("%i\n", total);

    return EXIT_SUCCESS;
}