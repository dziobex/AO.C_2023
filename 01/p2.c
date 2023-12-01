#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define BSIZE 100
const char *replacable [9] = {"one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};

char *remake (char buffer[BSIZE], int n) {
    char *result = malloc(n);

    int nth = 0;
    for (int i = 0; i < n; ++i) {
        char frag = *(buffer + i);

        // szukamy liczb o cyfrach zapisanych standardowo

        if (isdigit(frag)) {
            result[nth++] = frag;
            continue;
        }
        
        // szukamy slownych liczb

        for (int r = 0; r < 9; ++r) {
            int ln = strlen(replacable[r]);

            if (i + ln < n) {
                char *sub_str;
                sub_str = malloc (ln + 1);
                memcpy(sub_str, &buffer[i], ln);
                sub_str[ln] = '\0';

                if (strstr(sub_str, replacable[r]) != NULL) {
                    result[nth++] = (char)(r + 1 + '0');
                    i += 1;
                }

                free (sub_str);
            }
        }
    }
    result[nth] = '\0';
    return result;
}

int main (int argc, char ** argv) {
    FILE *in = fopen("input.txt", "r");

    if (in == NULL)
        return fputs("Nie udalo sie otworzyc pliku!", stderr), EXIT_FAILURE;

    char buffer[BSIZE];
    int total = 0;

    while (fgets(buffer, BSIZE, in) != NULL) {
        char *remade;
        remade = remake(buffer, strlen(buffer));
        total += (remade[0] - '0') * 10 + (remade[strlen(remade) - 1] - '0');
        free (remade);
    }

    fclose(in);
    printf("%i\n", total);

    return EXIT_SUCCESS;
}