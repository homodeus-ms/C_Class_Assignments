#include <stdio.h>
#include <assert.h>
#include <string.h>

#include "my_string.h"

void print_str(char* str);

int main(void)
{
    /*  해당 테스트를 통과하더라도 연속된 공백문자를 제대로 처리하지 않을 경우
        빌드테스트에서 크래시가 발생할 수 있습니다
    */  
    { /* reverse_by_words */

        char test1[] = "  ";
        char test2[] = "a  bc";
        char test3[] = "ab  c";
        char test4[] = "  a  b";
        char test5[] = "  a  bc  ";

        reverse_by_words(test1);
        assert(strcmp(test1, "  ") == 0);
        printf("test1 pass\n");

        reverse_by_words(test2);
        assert(strcmp(test2, "a  cb") == 0);
        printf("test2 pass\n");

        reverse_by_words(test3);
        assert(strcmp(test3, "ba  c") == 0);
        printf("test3 pass\n");

        reverse_by_words(test4);
        assert(strcmp(test4, "  a  b") == 0);
        printf("test4 pass\n");

        reverse_by_words(test5);
        assert(strcmp(test5, "  a  cb  ") == 0);
        printf("test5 pass\n");

        printf("done\n");
    }

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
