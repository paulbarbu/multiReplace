/**
 * Function headers for subEDIT
 *
 * (C) Copyright 2011 PauLLiK
 */

#pragma once
#ifndef H_FUNCTIONS_GUARD
#define H_FUNCTIONS_GUARD

long int lang_search(const char *needle, FILE *haystack);
char** get_char_sets(FILE *source);
long int replace_in_file(char **sets, FILE *file);
int empty_file(FILE *file);
#endif
