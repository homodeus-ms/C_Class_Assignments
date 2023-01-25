#include <stdio.h>
#include <assert.h>
#include <string.h>

#include "my_string.h"

void print_str(char* str);

int main(void)
{
    const char* str = "We all live in a yellow submarine";
    char str_cpy[34];
    const char* token;
    int res;

    strncpy(str_cpy, str, 33);
    str_cpy[33] = '\0';

    reverse(str_cpy);
    assert(strcmp("enirambus wolley a ni evil lla eW", str_cpy) == 0);

    assert(index_of(str, "all ") == 3);
    res = index_of(str, "marine");
    printf("marine : [%d]\n", res);

    assert(index_of(str, "marine") == 27);
    assert(index_of(str, "all good") == -1);
    assert(index_of(str, "marinett") == -1);

    reverse(str_cpy);

    assert(strcmp(str_cpy, str) == 0);

    reverse_by_words(str_cpy);

    assert(strcmp("eW lla evil ni a wolley enirambus", str_cpy) == 0);
    reverse_by_words(str_cpy);

    assert(strcmp(str_cpy, str) == 0);

    assert(tokenize(NULL, " ") == NULL);

    token = tokenize(str_cpy, " ");
    assert(token == str_cpy);
    assert(strcmp(token, "We") == 0);

    token = tokenize(NULL, " ");
    assert(token == str_cpy + 3);
    assert(strcmp(token, "all") == 0);

    token = tokenize(NULL, " ");
    assert(token == str_cpy + 7);
    assert(strcmp(token, "live") == 0);

    token = reverse_tokenize(NULL, " ");
    assert(token == str_cpy + 12);
    assert(strcmp(token, "ni") == 0);

    token = reverse_tokenize(NULL, " ");
    token = reverse_tokenize(NULL, " ");
    assert(token == str_cpy + 17);
    assert(strcmp(token, "wolley") == 0);

    printf("everthing!");

    return 0;
}

void print_str(char* str)
{
    while(*str != '\0') {
        printf("%c", *str);
        str++;
    }
    printf("\n");
}
