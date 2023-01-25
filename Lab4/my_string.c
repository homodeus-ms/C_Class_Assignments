#include <stdio.h>
#include <assert.h>

#include "my_string.h"

void reverse(char* str)
{
    int length = get_string_length(str);
    char* last_letter = str + length - 1;

    while (str < last_letter) {
        swap_letters(str++, last_letter--);
    }
}

int index_of(const char* str, const char* word)
{
    const char* str_start = str;
    const char* word_start = word;

    if (*word == '\0') {
        return -1;
    }
    
    while (*str != '\0') {
        while (*str++ == *word++) {
            if (*word == '\0') {
                return (str - str_start) - (word - word_start);
            }
        }

        word = word_start;
    }   

    return -1;
}

void reverse_by_words(char* str)
{
    char* blank = NULL;

    while (*str != '\0') {
        blank = get_blank_or_end_address(str);
        reverse_by_end_address(str, blank - 1);
        str = *blank == '\0' ? blank : blank + 1;
    }
}

char* tokenize(char* str_or_null, const char* delims)
{
    static char* str_ptr = NULL;
    static char* str_ptr_start = NULL;
    const char* delims_start = delims;
    
    if (str_or_null != NULL) {
        str_ptr = str_or_null;
        str_ptr_start = str_or_null;
    } else if (str_ptr != NULL) {
        str_ptr_start = str_ptr;
    } else {
        return NULL;
    }

    while (*str_ptr != '\0') {
        while (*(str_ptr - 1) != '\0' && *delims != '\0') {
            if (*str_ptr == *delims) {
                *str_ptr = '\0';
                str_ptr++;
                return str_ptr_start;
            } else {
                delims++;
            }
        }
        str_ptr++;
        delims = delims_start;
    }
 
    return NULL;
}

char* reverse_tokenize(char* str_or_null, const char* delims)
{
    char* token = tokenize(str_or_null, delims);
    if (token != NULL) {
        reverse_by_words(token);
        return token;
    } else {
        return NULL;
    }
    
}

int get_string_length(const char* str)
{
    const char* start = str; 

    while (*start++ != '\0') {
    }

    return start - str -1;
}

char* get_blank_or_end_address(char* str)
{
    char* start = str;

    while (*start != ' ' && *start != '\0') {
        start++;
    }

    return start;
}

void reverse_by_end_address(char* str, char* end)
{
    while (str < end) {
        swap_letters(str++, end--);
    }
}

void swap_letters(char* ptr1, char* ptr2)
{
    char temp = *ptr1;
    *ptr1 = *ptr2;
    *ptr2 = temp;
}



