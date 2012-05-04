/**
 * Main file for mR
 *
 * (C) Copyright 2011 PauLLiK
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <dirent.h>

#include "./includes/functions.h"
#include "./includes/const.h"

int main(int argc, char *argv[]){

    int argNum = 1;
    long int position = -1, *file_stats;

    char *path = malloc((strlen(DEF_PATH)+1) * sizeof(char)),
         *config = malloc((strlen(DEF_CONFIG)+1) * sizeof(char)),
         *lang = malloc((strlen(DEF_LANG)+1) * sizeof(char)),
         **sets = NULL;

    FILE *config_file = NULL,
        *path_file;

    strcpy(path, DEF_PATH);
    strcpy(config, DEF_CONFIG);
    strcpy(lang, DEF_LANG);

    /**
     * Process arguments here
     * if they are set the defaults change
     * if they are set wrong the defaults persist
     */
    while((argNum < argc) && ('-' == argv[argNum][0])){

        /**
         * Path to subtitle(s)
         */
        if(0 == strcmp(argv[argNum], "-p")){
            argNum++;
            if(argNum >= argc){
                printf("Not enough options!\n");

                free(path);
                free(config);
                free(lang);

                exit(ERR_ARG);
            }

            if(argv[argNum][0] == '-'){
                printf("Path not specified!\n");

                free(path);
                free(config);
                free(lang);

                exit(ERR_ARG);
            }
            else{
                path = realloc(path, (strlen(argv[argNum])+1) * sizeof(char));
                strcpy(path, argv[argNum]);

                if('.' == path[0] && '/' == path[1]){
                    strcpy(path, path + 2);
                }
            }
        }
        /**
         * Path to config file
         */
        else if(0 == strcmp(argv[argNum], "-c")){
            argNum++;
            if(argNum >= argc){
                printf("Not enough options!\n");

                free(path);
                free(config);
                free(lang);

                exit(ERR_ARG);
            }

            if(argv[argNum][0] == '-'){
                printf("Configuration path not specified!\n");

                free(path);
                free(config);
                free(lang);

                exit(ERR_ARG);
            }
            else{
                config = realloc(config, (strlen(argv[argNum])+1) * sizeof(char));
                strcpy(config, argv[argNum]);
            }
        }
        /**
         * Language to look for in config
         */
        else if(0 == strcmp(argv[argNum], "-l")){
            argNum++;
            if(argNum >= argc){
                printf("Not enough options!\n");

                free(path);
                free(config);
                free(lang);

                exit(ERR_ARG);
            }

            if('-' == argv[argNum][0]){
                printf("Language not specified!\n");

                free(path);
                free(config);
                free(lang);

                exit(ERR_ARG);
            }
            else{
                lang = realloc(lang, (strlen(argv[argNum])+1) * sizeof(char));
                strcpy(lang, argv[argNum]);
                for(int i=0;i<strlen(lang);i++){
                    lang[i] = toupper(lang[i]);
                }
            }
        }
        else{
            printf("Unknown argument: %s\n", argv[argNum]);

            free(path);
            free(config);
            free(lang);

            exit(ERR_ARG);
        }
        argNum++;
    } //finished processing arguments

    /**
     * Check if the config file is a valid file
     */
    config_file = fopen(config, "r");

    if(NULL != config_file){
        if(-1 != file_size(config_file)){
            position = lang_search(lang, config_file);

            if(-1 == position){
                rewind(config_file);

                char *comment = malloc(82 * sizeof(char));
                char *status;
                status = fgets(comment, 82, config_file);
                while((';' == comment[0] || '\n' == comment[0]
                        || '\0' == comment[0]) && status != NULL){
                    status = fgets(comment, 82, config_file);
                }
                fseek(config_file, -1 * strlen(comment), SEEK_SET);

                free(comment);
            }

            sets = get_char_sets(config_file);

            fclose(config_file);

            int sets_state = check_sets(sets);

            if(NULL_SETS == sets_state || INVALID_SETS == sets_state){
                printf("Invalid configuration file: %s\nCheck for inexistent "
                "replacee/replacements pairs in the specified section!\n"
                "Check if the replacee appears in the replacement!\n", config);

                free(path);
                free(config);
                free(lang);

                if(INVALID_SETS == sets_state){
                    int i = 0;
                    while(sets[i]){
                        free(sets[i]);
                        i++;
                    }
                    free(sets);
                }

                exit(ERR_CFG_FILE);
            }
        }
        else{
            fclose(config_file);
            printf("Invalid configuration file: %s\n", config);

            free(path);
            free(config);
            free(lang);

            exit(ERR_CFG_FILE);
        }
    }
    else{
        printf("Invalid configuration file: %s\n", config);

        free(path);
        free(config);
        free(lang);

        exit(ERR_CFG_FILE);
    }

    /**
     * Check if the path is a directory, a file or none
     */
    DIR *path_dir;
    path_dir = opendir(path);

    file_stats = malloc(2 * sizeof(long int));
    file_stats[0] = 0;
    file_stats[1] = 0;

    if(NULL != path_dir){
        parse_dir(sets, path_dir, path, file_stats);
    }
    else{
        path_file = fopen(path, "r+");

        if(NULL != path_file){
            file_stats[0]++;
            file_stats[1] = replace_in_file(sets, path_file, path, "w");

            fclose(path_file);
        }
        else{
            printf("Invalid path: %s\n", path);

            free(file_stats);
            free(path_dir);
            free(path);
            free(config);
            free(lang);

            int i = 0;
            while(sets[i]){
                free(sets[i]);
                i++;
            }
            free(sets);

            exit(ERR_PATH);
        }
    }

    printf("Path: %s\n", path);
    printf("Config: %s\n", config);

    if(-1 != position){
        printf("Lang(section): %s\n", lang);
    }
    else{
        printf("Lang(section): First section from config\n");
    }

    printf("Total files processed: %ld\n", file_stats[0]);
    printf("Total replacements: %ld\n", file_stats[1]);

    free(file_stats);
    free(path);
    free(config);
    free(lang);

    int i = 0;
    while(sets[i]){
        free(sets[i]);
        i++;
    }
    free(sets);

    exit(OK);
}
