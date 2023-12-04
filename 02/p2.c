#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BSIZE 200

int main (int argc, char **argv) {

    FILE *in = fopen("input.txt", "r");

    if (in == NULL)
        return fputs("Nie udalo sie otworzyc pliku!", stderr), EXIT_FAILURE;

    char buffer[BSIZE];
    char signs[] = " ,.-:";
    int lines = 0;
    

    while (fgets(buffer, BSIZE, in) != NULL) {
        char *temp_buffer;
        
        // pozyskuje: nazwe, nr gry
        temp_buffer = strtok(buffer, signs);
        temp_buffer = strtok(NULL, signs);

        int red = 0, green = 0, blue = 0;
        while( 1 ) {
            temp_buffer = strtok(NULL, signs);

            if (temp_buffer == NULL)
                break;
            
            int color = atoi(temp_buffer);
            temp_buffer = strtok(NULL, signs);

            switch(temp_buffer[0]) {
                case 'r':
                    red = color > red ? color : red;
                    break;
                case 'g':
                    green = color > green ? color : green;
                    break;
                case 'b':
                    blue = color > blue ? color : blue;
                    break;
                default:
                    break;
            }
        }

        lines += red * green * blue;

        free (temp_buffer);
    }
    
    fclose( in );

    printf("%i\n", lines);

    return EXIT_SUCCESS;
}