#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "tokenize.h"

int main(void)
{
    const char* str = "I like cookies. Do you like cookies? Cookies are good!";
    char** tokens = tokenize_malloc(str, "\0");
    char** tt = tokens;

    printf("%s\n", *tt++);
    assert(*tt == NULL);

    tt = tokens;
    while (*tt != NULL) {
        free(*tt++);
    }

    free(tokens);

    printf("No Assert!");

    return 0;
}





