#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tokenize.h"

char** tokenize_malloc(const char* str, const char* delim)
{
    char** result = NULL;
    char* copied_str;
    char* p;
    
    const char* delim_start = delim;
    size_t i = 0;
    char* token;
    size_t result_size;
    size_t str_size = strlen(str);
    copied_str = malloc(str_size + 1);

    result_size = str_size <= 1 ? 8 : str_size * 4;

    result = malloc(result_size);
    
    p = copied_str;
    token = copied_str;
    strcpy(p, str);

    while (*p != '\0') {
        while (*delim != '\0') {
            if (*p == *delim) {
                *p = '\0';

                if (p != token) {
                    char* token_malloc = malloc(p - token + 1);
                    memcpy(token_malloc, token, p - token + 1);
                    result[i++] = token_malloc;
                    token = p + 1;
                    break;
                } else {
                    token++;
                    break;
                }
                
            } else {
                delim++;
            }
        }

        p++;
        delim = delim_start;
    }

    if (*token != '\0') {
        char* token_malloc = malloc(sizeof(char*));
        token_malloc = token;
        result[i++] = token_malloc;
    }
    
    result[i] = NULL;

    free(copied_str);

    return result;
}

