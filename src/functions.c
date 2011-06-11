/**
 * Function implementations for subEDIT
 *
 * (C) Copyright 2011 PauLLiK
 */
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
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
        if('[' == line[0] && ']' == line[strlen(line)-1]){

            line[1] = toupper(line[1]);
            line[2] = toupper(line[2]);

            if(NULL != strstr(line, needle)){
                break;
            }
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
 * into a multi-dimensional array starting from the file pointer until '[' is met at
 * the beginning of a line or feof(), lines starting with ';' will be ignored
 *
 * Each even( %2 == 0) line is the replace_me string and the uneven
 * lines( %2 == 1) are the strings to replace the last even line
 *
 * If we have:
 * a=b -> sets[0] == a and sets[1] == b
 * x=r -> sets[2] == x and sets[3] == r
 *
 * Sometimes the position of the equal sign varies because some characters are
 * made by two ASCII codes put together(this is k's role, to indicate if our
 * first char is made of two ASCII codes depending on equal's position)
 *
 * Returns an array of pointers to strings(multi-dimensional array of strings)
 */
char** get_char_sets(FILE *source){
    int n=2, k;
    char *line = malloc(6 * sizeof(char)),
         **sets = malloc(n * sizeof(char*));

    for(int i=0;i<n;i++){
        sets[i] = malloc(1 * sizeof(char));
    }

    do{
        fgets(line, 6, source);
        if('[' != line[0]){

            //line not commented and valid
            if(';' != line[0] && '\n' != line[0] && '\0' != line[0]){
                if('=' == line[1]){
                    k=1;
                }
                else if('=' == line[2]){
                    k=2;
                }
                else{
                    continue;
                }

                for(int i=n-2;i<n;i++){
                    sets[i] = realloc(sets[i], k * sizeof(char));
                }

                if(1 == k){
                    sets[n-2][0] = line[0];
                    sets[n-1][0] = line[2];
                }
                else{
                    sets[n-2][0] = line[0];
                    sets[n-2][1] = line[1];

                    sets[n-1][0] = line[3];
                }

                n+=2;
                sets = realloc(sets, n * sizeof(char*));
            }
        }
        else{
            break;
        }

    }while(!feof(source));

    return sets;
}
