/**
 * Function implementations for subEDIT
 *
 * (C) Copyright 2011 PauLLiK
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/**
 * long int lang_search(const char *needle, FILE *haystack);
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

    if(pos == file_size){ //if the file pointer is at the end the needle was not found
        pos = -1;
    }

    return pos;
}
