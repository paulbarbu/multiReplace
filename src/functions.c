/**
 * Function implementations for mR
 *
 * (C) Copyright 2011, 2012 Barbu Paul - Gheorghe
 */
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <dirent.h>
#include <magic.h>

#include "./includes/functions.h"

const int NULL_SETS = -1, INVALID_SETS = -2, VALID_SETS = 1;

/**
 * long int empty_file(FILE *file)
 *
 * Returns -1 if the file is empty, else returns the file size in long int
 */
long int file_size(FILE *file){
    long int current_pos, size;

    current_pos = ftell(file);

    fseek(file, 0, SEEK_END);
    size = ftell(file);

    fseek(file, current_pos, SEEK_SET);

    if(0 == size){
        return -1;
    }

    return size;
}

/**
 * long int lang_search(char *needle, FILE *haystack)
 *
 * Search for string needle in file haystack
 * If needle is found return starting position, else return NULL
 */
long int lang_search(char *needle, FILE *haystack){
    long int size, pos;
    char *line = malloc(256 * sizeof(char));

    size = file_size(haystack);

    rewind(haystack); //set pointer in file at beginning

    while(!feof(haystack)){
        fgets(line, 256 , haystack);
        if('[' == line[0] && ']' == line[strlen(line)-2]){

            for(int i=1;i<strlen(line)-2;i++){
                line[i] = toupper(line[i]);
            }

            if(NULL != strstr(line, needle)){
                break;
            }
        }
    }

    pos = ftell(haystack);

    if(pos == size){ //if the file pointer is at the end of the haystack
                        //then the needle was not found
        pos = -1;
    }

    free(line);

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
    int n = 0,
        k = 0,
        equal_pos = 0;

    char *line = malloc(256 * sizeof(char)),
        **sets = NULL,
        *equal;

    line[0] = '\0';

    do{
        fgets(line, 256, source);
        if('[' != line[0] && !feof(source)){

            //line not commented and valid
            if(';' != line[0] && '\n' != line[0] && '\0' != line[0]){
                if(NULL != (equal = strstr(line, "="))){
                    equal_pos = equal - line;
                }
                else{
                    continue;
                }

                n += 2;
                if(n == 2){
                    sets = malloc((n+1) * sizeof(char*));
                }
                else{
                    sets = realloc(sets, (n+1) * sizeof(char*));
                }

                for(int i=n-2;i<n;i++){
                    if(0 == i%2){
                        sets[i] = malloc(equal_pos+1 * sizeof(char));
                    }
                    else{
                        sets[i] = malloc((strlen(line) - equal_pos-1)
                                                    * sizeof(char));
                    }
                }

                for(int i=0;i<equal_pos;i++){
                    sets[n-2][i] = line[i];
                }

                sets[n-2][equal_pos] = '\0';

                k=0;
                for(int i=equal_pos + 1;i<strlen(line)-1;i++){
                    sets[n-1][k++] = line[i];
                }

                sets[n-1][strlen(line) - equal_pos - 2] = '\0';

                sets[n] = NULL;
            }
        }
        else{
            break;
        }
    }while(!feof(source));

    free(line);

    return sets;
}

/**
 * long int replace_in_file(char **sets, FILE *file, char *path, const char *mode){
 *
 * Search for sets[even_number] in file stream *file and replace with
 * sets[uneven_number]
 *
 * Returns a long int representing number of replacements made
 */
long int replace_in_file(char **sets, FILE *file, char *path, const char *mode){
    long int n = 0, size = 0, len, remaining_len, after_len;

    char *buffer,
         *found,
         *before,
         *after;

    size = file_size(file);
    if(-1 != size){

        buffer = malloc((size+1) * sizeof(char));

        memset(buffer, '\0', size+1);

        rewind(file);
        fread(buffer, sizeof(char), size, file);

        int i=0;
        do{ //search through all char sets
            do{ //search for a character until found becomes NULL
                found = strstr(buffer, sets[i]);
                if(NULL != found && '\0' != sets[i][0]){

                    //replace
                    if(strlen(sets[i]) == strlen(sets[i+1])){
                        strncpy(found, sets[i+1], strlen(sets[i+1]));
                    }
                    else{
                        len = found - buffer,
                        remaining_len = len + strlen(sets[i]);
                        after_len = size - len - strlen(sets[i]);

                        before = malloc((len+1) * sizeof(char));
                        after = malloc((after_len +1) * sizeof(char));

                        memset(before, '\0', len+1);
                        memset(after, '\0', after_len+1);

                        strncpy(before, buffer, len); //part before occurrence
                        strcpy(after, buffer + remaining_len); //part after occurrence

                        size += (strlen(sets[i+1]) - strlen(sets[i]));

                        buffer = realloc(buffer, (size+1) * sizeof(char));

                        memset(buffer, '\0', size+1);
                        /*buffer[0] = '\0';*/

                        strcat(buffer, before);
                        /*buffer[len] = '\0';*/

                        strcat(buffer, sets[i+1]);
                        /*buffer[len+strlen(sets[i+1])] = '\0';*/

                        strcat(buffer, after);
                        /*buffer[size] = '\0';*/

                        free(before);
                        free(after);
                    }

                    n++;
                }
            }while(NULL != found && '\0' != sets[i][0]);

            i+=2; //next char set
        }while(NULL != sets[i] && '\0' != sets[i][0]);

        freopen(path, "w", file);
        fwrite(buffer, 1, size, file);

        free(buffer);
    }

    return n;
}

/**
 * void parse_dir(char** sets, DIR *dir, char *path, long int* stats)
 *
 * Tries to open every file in the *dir directory and its subdirectories to edit
 * them, the *dir must be already opened by opendir() as: dir = opendir(); and
 * it will be closed by the function, this is needed by the recursion
 *
 * Modifies the stats array of long ints, first is the number of files
 * edited and the second one is the number of replacements made
 */
void parse_dir(char** sets, DIR *dir, char *path, long int* stats){
    char *name = malloc((strlen(path)+1) * sizeof(char)),
         *def_name = malloc((strlen(path)+2) * sizeof(char));

    struct dirent *entry;
    DIR *sub_dir;

    strcpy(def_name, path);
    if('/' != def_name[strlen(def_name) - 1]){
        strcat(def_name, "/");
    }

    while(NULL != (entry = readdir(dir))){
        if(0 != strcmp(entry->d_name, ".") && 0 != strcmp(entry->d_name, "..")){

            name = realloc(name,
                strlen(def_name) * sizeof(char) + strlen(entry->d_name) + 1);
            strcpy(name, def_name);

            strcat(name, entry->d_name);

            if(NULL != (sub_dir = opendir(name))){
                parse_dir(sets, sub_dir, name, stats);
            }
            else{
                FILE *file;

                file = fopen(name, "r+");
                if(NULL != file){

                    stats[0]++;
                    stats[1] += replace_in_file(sets, file, name, "w");
                    fclose(file);
                }
            }
        }
    }

    free(name);
    free(def_name);

    closedir(dir);
}

/**
 * int check_sets(char **sets)
 *
 * Checks if a the given character sets of replacee and replacement are valid.
 *
 * If sets is NULL  return NULL_SETS
 * If parts of the replacee are found in the replacement the
 * sets are invalid and INVALID_SETS is returned.
 * If the sets are valid OK is returned.
 */
int check_sets(char**sets){
    if(NULL == sets){
        return NULL_SETS;
    }

    int i=0;

    while(NULL != sets[i]){
        if(NULL != strstr(sets[i+1],sets[i])){
            return INVALID_SETS;
        }

        i+=2;
    }

    return VALID_SETS;
}

/**
 * char *get_file_encoding(const char *filename)
 *
 * Get the encoding of a file by using libmagic
 *
 * Return a string containing the file's encoding or NULL on failure
 *
 * Note: assuming the magic database file is located at: /usr/share/misc/magic
 * due to a bug in libmagic
 */
char *get_file_encoding(const char *filename){
    const char *encoding;
    char *e;
    magic_t cookie;

    cookie = magic_open(MAGIC_MIME_ENCODING);

    if(NULL == cookie){
        magic_close(cookie);
        return NULL;
    }

    int load_status;
    load_status = magic_load(cookie, "/usr/share/misc/magic");

    if(-1 == load_status){
        magic_close(cookie);
        return NULL;
    }

    encoding = magic_file(cookie, filename);

    e = malloc((strlen(encoding)+1) * sizeof(char));

    strcpy(e, encoding);

    magic_close(cookie);

    return e;
}
