/**
 * Main file for subEDIT
 *
 * (C) Copyright 2011 PauLLiK
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

//#include "./includes/functions.h"
#include "./includes/const.h"

int main(int argc, char *argv[]){

    int argNum = 1;

    char path[] = DEF_PATH,
         config[] = DEF_CONFIG,
         lang[] = "";

    FILE *config_file = NULL;

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

    if(NULL != config_file){
        //call function to parse the config file
    }
    else{
        printf("Invalid configuration file!\n");
        exit(ERR_CFG_FILE);
    }

    fclose(config_file);

    /**
     * Check if the path is a directory, a file or none
     */
    DIR *path_dir;
    path_dir = opendir(path);

    if(NULL != path_dir){
        //path is a directory so handle it recursively
        printf("\n--DIR--\n");
    }
    else{
        //path was not a directory, checking for file

        closedir(path_dir);
        free(path_dir);

        FILE *path_file;
        path_file = fopen(path, "r+");

        if(NULL != path_file){
            //handle path as a single file

            printf("\n--FILE--\n");
        }
        else{
            printf("Invalid path!\n");
            exit(ERR_PATH);
        }
        fclose(path_file);
    }

    return OK;
}
