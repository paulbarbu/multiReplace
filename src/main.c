/**
 * Main file for subEDIT
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
    long int position = -1, replacements;

    char *path = malloc((strlen(DEF_PATH)+1) * sizeof(char)),
         *config = malloc((strlen(DEF_CONFIG)+1) * sizeof(char)),
         *lang = malloc(3 * sizeof(char)),
         **sets;

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
                exit(ERR_ARG);
            }

            if(argv[argNum][0] == '-'){
                printf("Path not specified!\n");
                exit(ERR_ARG);
            }
            else{
                path = realloc(path, (strlen(argv[argNum])+1) * sizeof(char));
                strcpy(path, argv[argNum]);
            }
        }
        /**
         * Path to config file
         */
        else if(0 == strcmp(argv[argNum], "-c")){
            argNum++;
            if(argNum >= argc){
                printf("Not enough options!\n");
                exit(ERR_ARG);
            }

            if(argv[argNum][0] == '-'){
                printf("Configuration path not specified!\n");
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
                exit(ERR_ARG);
            }

            if(2 != strlen(argv[argNum])){
                printf("Language string must be two characters long!\n");
                exit(ERR_ARG);
            }

            if('-' == argv[argNum][0]){
                printf("Language not specified!\n");
                exit(ERR_ARG);
            }
            else{
                strcpy(lang, argv[argNum]);
                for(int i=0;i<strlen(lang);i++){
                    lang[i] = toupper(lang[i]);
                }
            }
        }
        else{
            printf("Unknown argument\n");
            exit(ERR_ARG);
        }
        argNum++;
    } //finished processing arguments

    printf("%s\n%s\n%s\n", path, lang, config); //delete this when publishing

    /**
     * Check if the config file is a valid file
     */
    config_file = fopen(config, "r");

    if(NULL != config_file && !empty_file(config_file)){
        position = lang_search(lang, config_file);

        if(-1 == position){
            rewind(config_file);

            char *comment = malloc(82 * sizeof(char));
            do{
                fgets(comment, 82, config_file);
            }while(';' == comment[0] || '\n' == comment[0]
                    || '\0' == comment[0]);
        }

        sets = get_char_sets(config_file);
    }
    else{
        printf("Invalid configuration file!\n");
        exit(ERR_CFG_FILE);
    }


    /**
     * Check if the path is a directory, a file or none
     */
    DIR *path_dir;
    path_dir = opendir(path);

    if(NULL != path_dir){
        //int** nr_files_changes;
        //nr_file_changes = parse_dir(path_dir);
    }
    else{
        //path was not a directory, checking for file

        closedir(path_dir);
        free(path_dir);

        path_file = fopen(path, "r+");

        if(NULL != path_file){
            replacements = replace_in_file(sets, path_file);
        }
        else{
            printf("Invalid path!\n");
            exit(ERR_PATH);
        }
    }

    printf("\n---%d---\n", replacements);

    exit(OK);
}
