#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 150
#define NAME_SIZE 10
#define RULE_SIZE 20
#define RULE_COUNT 10

typedef struct {
    /* var sign comp (np. a>2137) --- wzięte z rule_name */
    char var, sign;
    int comp;
    
    struct workflow* is_true_ptr;
} rule;

typedef struct {
    char w_name[3];

    rule ruleset[5];
    int ruleset_count;

    struct workflow* ending_ptr;
} workflow; // 172 bytes

workflow* get_place( workflow workflows[26][26][26], char index[3] ) {
    if ( strstr( index, "A" ) != NULL )
        return &workflows[0][0][0];
    if ( strstr( index, "R" ) != NULL )
        return &workflows[17][17][17];

    int xyz[3] = {0};
    for ( int i = strlen( index ) - 1, j = 2; i >= 0 && j >= 0; --i, --j ) {
        xyz[j] = index[i] - 'a';
    }

    //  printf( "%i %i %i\n", xyz[0], xyz[1], xyz[2] );

    return &workflows[ xyz[0] ][ xyz[1] ][ xyz[2] ];
}

int main( int argc, char **argv ) {
    FILE *in = fopen( "in.txt", "r" );

    if ( in == NULL )
        return fprintf( stderr, "Nie udalo sie otworzyc pliku :(" ), EXIT_FAILURE;

    char buffer[ BUFFER_SIZE ];

    workflow workflows[26][26][26];
    workflows[0][0][0].w_name[0] = 'A';
    workflows[17][17][17].w_name[0] = 'R';

    int wf_count = 0;

    while( fgets( buffer, BUFFER_SIZE, in ) != NULL && buffer[0] != '\n' ) {
        if( buffer[ strlen( buffer ) - 1 ] == '\n' )
            buffer[ strlen( buffer ) - 1 ] = '\0';
        
        for ( int i = 0; i < strlen( buffer ); ++i )
            if ( strchr( ",{}:", buffer[i] ) != 0 )
                buffer[i] = ' ';
        
        //  printf( "%s\n", buffer );

        /** nazwa jednostki */    
        char* tmp;
        tmp = strtok( buffer, " " );

        /** indeks jednostki w mapie workflows */
        int xyz[3] = {0};
        for ( int i = strlen( tmp ) - 1, j = 2; i >= 0 && j >= 0; --i, --j ) {
            xyz[j] = tmp[i] - 'a';
        }

        workflow* wf_c = get_place( workflows, tmp ); // &workflows[ xyz[0] ][ xyz[1] ][ xyz[2] ];
        strcpy( wf_c->w_name, tmp );


        /** zasady w niej */
        char *stack[RULE_SIZE];
        int stack_count = 0;

        tmp = strtok( NULL, " " );
        while ( tmp != NULL ) {
            stack[stack_count] = malloc( sizeof( tmp ) );
            strcpy( stack[stack_count++], tmp );
            tmp = strtok( NULL, " " );
        }
        
        wf_c->ruleset_count = 0;

        for ( int i = 0; i + 2 < stack_count; i += 2 ) {
            // strcpy( ruleset[ ruleset_count ].rule_name, stack[i] );
            // strcpy( ruleset[ ruleset_count ].is_true, stack[i + 1] );
            if ( i + 1 >= stack_count)
                break;

            wf_c->ruleset[ wf_c->ruleset_count ].var = stack[i][0] - 'a';
            wf_c->ruleset[ wf_c->ruleset_count ].sign = stack[i][1];

            char sbuf[10] = {0};
            for ( int j = 2; j < strlen( stack[i] ); ++j )
                sbuf[ j - 2 ] = stack[i][j];
            
            wf_c->ruleset[ wf_c->ruleset_count ].comp = atoi( sbuf );

            wf_c->ruleset[ wf_c->ruleset_count ].is_true_ptr = (struct workflow*)get_place( workflows, stack[i + 1] );

            wf_c->ruleset_count++;
        }

        /** końcówka */
        wf_c->ending_ptr = (struct workflow*)get_place( workflows, stack[ stack_count - 1] );

        for( int i = 0; i < stack_count; ++i )
            free( stack[i] );
        
        free( wf_c );
    }

    int xmas[26] = {0};
    int _xmas[4] = { 'x' - 'a', 'm' - 'a', 'a' - 'a', 's' - 'a' };
    int sum = 0;
    while( fgets( buffer, BUFFER_SIZE, in ) != NULL ) {
        for ( int i = 0; i < strlen( buffer ); ++i )
            if ( strchr( "=,{}:\n", buffer[i] ) != 0 )
                buffer[i] = ' ';
        
        char* tmp;
        tmp = strtok( buffer, " ");
        for ( int i = 0; i < 4; ++i ) {
            tmp = strtok( NULL, " ");
            xmas[ _xmas[i] ] = atoi( tmp );
            if ( i < 3)  tmp = strtok( NULL, " ");
        }
        
        // printf( "%s\n", buffer );
        
        workflow* cwf = &workflows[0]['i' - 'a']['n' - 'a'];
        int work = 1;

        while ( work == 1 ) {
            work = 0;

            if ( strstr( cwf->w_name, "A" ) != NULL || strstr( cwf->w_name, "R" ) != NULL ) {
                if ( strstr( cwf->w_name, "A" ) != NULL )
                    sum += xmas[ _xmas[0] ] + xmas[ _xmas[1] ] + xmas[ _xmas[2] ] + xmas[ _xmas[3] ];
                break;
            }

            for ( int i = 0; i < cwf->ruleset_count; ++i ) {
                rule* r;
                r = &cwf->ruleset[i];

                if ( ( r->sign == '>' && xmas[ r->var ] > r->comp)
                || ( r->sign == '<' && xmas[ r->var ] < r->comp ) ) {
                    work = 1;
                    cwf = (workflow*)r->is_true_ptr;
                    free( r );
                    break;
                }

                free( r );
            }

            if ( work == 0 ) {
                cwf = (workflow*)cwf->ending_ptr;
                work = 1;
            }
        }

        free( cwf );
    }

    printf( "%i", sum );

    fclose( in );

    return EXIT_SUCCESS;
}
