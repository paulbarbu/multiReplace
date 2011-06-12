/**
 * Function headers for mR
 *
 * (C) Copyright 2011 PauLLiK
 */

#pragma once
#ifndef H_FUNCTIONS_GUARD
#define H_FUNCTIONS_GUARD

long int lang_search(char *needle, FILE *haystack);
char** get_char_sets(FILE *source);
long int replace_in_file(char **sets, FILE *file, char *path, char *mode);
long int file_size(FILE *file);
long int parse_dir(char **sets, DIR *dir, char *path);
#endif
