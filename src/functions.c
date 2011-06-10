/**
 * Function implementations for subEDIT
 *
 * (C) Copyright 2011 PauLLiK
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/**
 * long int lang_search(const char *needle, FILE *haystack)
 *
 * Search for string needle in file haystack
 * If needle is found return starting position, else return NULL
 */
long int lang_search(const char *needle, FILE *haystack){
    long int file_size, pos;
    char *line = malloc(5 * sizeof(char));

    fseek(haystack, 0, SEEK_END);
    file_size = ftell(haystack);

    rewind(haystack); //set pointer in file at beginning

    while(!feof(haystack)){
        fgets(line, 5 , haystack);
        if('[' == line[0] && NULL != strstr(line, needle)
                && ']' == line[strlen(line)-1]){
            break;
        }
    }

    pos = ftell(haystack);

    if(pos == file_size){ //if the file pointer is at the end of the haystack
                        //then the needle was not found
        pos = -1;
    }

    return pos;
}

/**
 * char** get_char_sets(FILE *source)
 *
 * Tries to assign the characters to be replaced and the replace-with characters
 * into a bidimensional array starting from the file pointer until '[' is met at
 * the beginning of a line or feof(), lines starting with ';' will be ignored
 *
 * Returns an array of pointers to strings(bidimensional array of strings)
 */
char** get_char_sets(FILE *source){
    int n=1;
    char *line = malloc(5 * sizeof(char));
    char **sets = malloc(2 * sizeof(char*));

    for(int i=0;i<2;i++){
        sets[i] = malloc(n * sizeof(char));
    }

    fgets(line, 5, source);
    while(!feof(source)){

        if('[' != line[0]){
            if(';' != line[0] && '\n' != line[0] && '\0' != line[0]
                    && '=' == line[1]){ //line not commented and valid

                for(int i=0;i<2;i++){
                    sets[i] = realloc(sets[i], n * sizeof(char));
                }

                sets[0][n-1] = line[0];
                sets[1][n-1] = line[2];

                n++;
            }
            fgets(line, 5, source);
        }
        else{
            break;
        }
    }

    sets[0][n-1] = '\0';
    sets[1][n-1] = '\0';

    return sets;
}
