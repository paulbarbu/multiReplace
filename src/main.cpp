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
    string path = "", lang = "", config = "";

    while((argNum < argc) && (argv[argNum][0] == '-')){
        string argument = argv[argNum];

        if(argument == "-p"){
            path = argv[++argNum];
        }
        else{
            printf("Unknown argument\n");
            return ERR_ARG;
        }
    }

    printf("%s\n", path.c_str());

    return OK;
}
