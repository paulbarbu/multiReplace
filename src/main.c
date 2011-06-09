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
    char *path = DEF_PATH,
         *config = DEF_CONFIG,
         *lang = "";
    FILE *config_file = NULL;

    /**
     * Process arguments here
     * if they are set the defaults change
     * if they are set wrong the defaults persist
     */
    while((argNum < argc) && (argv[argNum][0] == '-')){

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

            if(argv[argNum][0] == '-'){
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

    printf("%s\n%s\n%s\n", path, lang, config);

    config_file = fopen(config, "r");

    if(config_file != NULL){
        //call function to parse the config file
    }
    else{
        printf("Invalid configuration file!\n");
        exit(ERR_CFG_FILE);
    }

    return OK;
}
