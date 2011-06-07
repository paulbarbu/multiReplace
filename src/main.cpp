/**
 * Main file for subEDIT
 *
 * (C) Copyright 2011 PauLLiK
 */

#include <stdio.h>
#include <string>

#include "./includes/functions.h"
#include "./includes/const.h"

using namespace std;

int main(int argc, char *argv[]){

    int argNum = 1;
    string path = "", lang = "", config = ""; //TODO: set defaults

    while((argNum < argc) && (argv[argNum][0] == '-')){
        string argument = argv[argNum];

        /**
         * Path to subsitle(s)
         */
        if(argument == "-p"){
            path = argv[++argNum];
        }
        /**
         * Path to config file
         */
        else if(argument == "-c"){
            config = argv[++argNum];
        }
        /**
         * Language to look for in config
         */
        else if(argument == "-l"){
            lang =  argv[++argNum];
        }
        else{
            printf("Unknown argument\n");
            return ERR_ARG;
        }
        argNum++;
    }

    printf("%s\n%s\n%s\n", path.c_str(), lang.c_str(), config.c_str());

    return OK;
}
