#ifndef MY_STRING_H
#define MY_STRING_H

void reverse(char* str);

int index_of(const char* str, const char* word);

void reverse_by_words(char* str);

char* tokenize(char* str_or_null, const char* delims);

char* reverse_tokenize(char* str_or_null, const char* delims);

int get_string_length(const char* str);

void swap_letters(char* ptr1, char* ptr2);

char* get_blank_or_end_address(char* str);

void reverse_by_end_address(char* str, char* end);

#endif /* MY_STRING_H */


