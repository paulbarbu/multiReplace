/**
 * Function implementations for mR
 *
 * (C) Copyright 2011 PauLLiK
 */
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <dirent.h>

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
 * long int lang_search(const char *needle, FILE *haystack)
 *
 * Search for string needle in file haystack
 * If needle is found return starting position, else return NULL
 */
long int lang_search(const char *needle, FILE *haystack){
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
    int n = 2,
        k = 0,
        equal_pos = 0;

    char *line = malloc(256 * sizeof(char)),
        **sets = malloc((n + 1) * sizeof(char*)),
        *equal;


    for(int i=0;i<=n;i++){
        sets[i] = malloc(1 * sizeof(char));
    }

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

                for(int i=n-2;i<=n;i++){
                    if(0 == i%2){
                        sets[i] = realloc(sets[i], equal_pos+1 * sizeof(char));
                    }
                    else{
                        sets[i] = realloc(sets[i], (strlen(line) - equal_pos)
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

                n+=2;
                sets = realloc(sets, (n + 1) * sizeof(char*));
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
 * long int replace_in_file(const char **sets, FILE *file, const char *path,
 *                          const char *mode){
 *
 * Search for sets[even_number] in file stream *file and replace with
 * sets[uneven_number]
 *
 * Returns a long int representing number of replacements made
 */
long int replace_in_file(const char **sets, FILE *file, const char *path,
                            const char *mode){
    long int n = 0, size = 0, len, remaining_len;

    char *buffer,
         *found,
         *before,
         *after;

    size = file_size(file);
    if(-1 != size){

        buffer = malloc(size * sizeof(char));
        found = malloc(size * sizeof(char));

        rewind(file);
        fread(buffer, 1, size, file);

        int i=0;
        do{ //search through all char sets
                do{ //search for a character until found becomes NULL
                    found = strstr(buffer, sets[i]);
                    if(NULL != found && '\0' != sets[i][0]){

                        //replace
                        if(strlen(sets[i]) == strlen(sets[i+1])){
                            strncpy(found, sets[i+1], strlen(sets[i+1]));
                        }
                        else{ //we have to modify the buffer's size
                           len = found - buffer,
                           remaining_len = len + strlen(sets[i]);

                            before = malloc(len * sizeof(char));
                            after = malloc(size - len - strlen(sets[i]));

                            strncpy(before, buffer, len); //part before occurrence
                            strcpy(after, buffer + remaining_len); //part after occurrence

                            size += (strlen(sets[i+1]) - strlen(sets[i]));

                            buffer = realloc(buffer, size * sizeof(char));
                            buffer[0] = '\0';

                            strcat(buffer, before);
                            buffer[len] = '\0';

                            strcat(buffer, sets[i+1]);
                            buffer[len+strlen(sets[i+1])] = '\0';

                            strcat(buffer, after);
                            buffer[size] = '\0';

                            free(before);
                            free(after);
                        }

                        n++;
                    }
                }while(NULL != found && '\0' != sets[i][0]);

                i+=2; //next char set
        }while(NULL != sets[i] && '\0' != sets[i][0]);

        freopen(path, "w" ,file);
        fwrite(buffer, 1, size, file);

        free(buffer);
    }

    return n;
}

/**
 * long int** parse_dir(const char** sets, DIR *dir)
 *
 * Tries to open every file in the *dir directory and its subdirectories to edit
 * it
 *
 * Returns a bidimensional array of long ints, first if the number of files
 * edited and the second one is number of replacements made
 */
long int* parse_dir(const char** sets, DIR *dir, char *path){
    long int *info = malloc(2 * sizeof(long int));

    char *name = malloc(strlen(path) * sizeof(char) +1),
         *def_name = malloc(strlen(path) * sizeof(char) +1);

    struct dirent *entry;

    info[0] = 0;
    info[1] = 0;

    strcpy(def_name, path);
    if('/' != def_name[strlen(def_name) - 1]){
        strcat(def_name, "/");
    }

    while(NULL != (entry = readdir(dir))){
        if(0 != strcmp(entry->d_name, ".") && 0 != strcmp(entry->d_name, "..")){

            name = realloc(name,
                    strlen(def_name) * sizeof(char) + strlen(entry->d_name));
            strcpy(name, def_name);

            strcat(name, entry->d_name);

            if(opendir(name)){
                DIR *sub_dir;
                long int *info_sub = malloc(2 * sizeof(long int));

                sub_dir = opendir(name);

                info_sub = parse_dir(sets, sub_dir, name);

                info[0] += info_sub[0];
                info[1] += info_sub[1];
            }
            else{
                FILE *file;

                file = fopen(name, "r+");
                if(NULL != file){

                    info[1] += replace_in_file(sets, file, name, "w");
                    info[0]++;
                    fclose(file);
                }
            }
        }
    }

    closedir(dir);
    return info;
}
