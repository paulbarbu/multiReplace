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
        if('[' == line[0] && NULL != strstr(line, needle) && ']' == line[strlen(line)-1]){
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
 * the beginning of a line or feof(), also lines starting with '#' will be ignored
 *
 * Returns an array of pointers to strings(bidimensional array of strings)
 */
char** get_char_sets(FILE *source){
    int n=1;
    char **sets = malloc(2 * n * sizeof(char));
    char *line = malloc(5 * sizeof(char));

    //file pointer will be set on the [section], we must move it down by a line
    fgets(line, 5, source);

    fgets(line, 5, source);
    while(!feof(source)){
        if('[' != line[0]){
            if('#' != line[0] && '=' == line[1]){ //line not commented and valid
                sets = realloc(sets, 2 * ++n * sizeof(char));
                sets[0][n-1] = line[0];
                sets[1][n-1] = line[2];
            }
            fgets(line, 5, source);
        }
        else{
            break;
        }
    }

    return sets;
}
