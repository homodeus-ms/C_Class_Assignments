#ifndef PARENTHESES_H
#define PARENTHESES_H

#include <stddef.h>

#define TRUE (1)
#define FALSE (0)

typedef struct {
    size_t opening_index;
    size_t closing_index;
} parenthesis_t;

typedef struct {
    size_t start_index;
    parenthesis_t* parentheses;
    size_t max_size;
} ringbuffer_t;

size_t find_matching_parentheses(ringbuffer_t* ringbuffer, const char* str);

void push(const char** stack, size_t* stack_count, const char* p);

int is_empty(size_t*);

const char* pop(const char** stack, size_t* stack_count); 

int find_pair_index(char ch, const char* str, const char** stack, size_t* stack_count);

#endif /* PARENTHESES_H */

