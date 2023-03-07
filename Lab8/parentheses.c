#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "parentheses.h"

size_t find_matching_parentheses(ringbuffer_t* ringbuffer, const char* str)
{
    const char** stack;

    size_t stack_count = 0;
    size_t res = 0;
    size_t str_len;
    
    const char* str_p = str;
    size_t q_back = 0;
    
    parenthesis_t new_pa;

    ringbuffer->start_index = 0;

    str_len = strlen(str);
    stack = malloc(str_len * sizeof(char*));

    while (*str_p != '\0') {
        char ch;
        int pair_idx;
        if (stack_count != 0 && (*str_p == ')' || *str_p == '}' || *str_p == ']' || *str_p == '>')) {
            ch = *str_p;
            pair_idx = find_pair_index(ch, str, stack, &stack_count);
            
            if (pair_idx == -1) {
                ++str_p;
                continue;
            } else {
                new_pa.opening_index = pair_idx;
                new_pa.closing_index = str_p - str;
                ringbuffer->parentheses[q_back] = new_pa;

                q_back = (q_back + 1) % ringbuffer->max_size;
                ++res;
                ringbuffer->start_index = res <= ringbuffer->max_size ? 0 : res % ringbuffer->max_size;
            }
        } else if (*str_p == '(' || *str_p == '{' || *str_p == '[' || *str_p == '<') {
            push(stack, &stack_count, str_p);
        }
        str_p++;
    }

    free(stack);

    return res;    
}
int find_pair_index(char ch, const char* str, const char** stack, size_t* stack_count)
{
    const char** tmp_stack;
    size_t tmp_count = 0;
    const char* tmp_pop;
    char target_ch;

    tmp_stack = malloc(*stack_count * sizeof(char*));

    assert(ch == ')' || ch == '}' || ch == ']' || ch == '>');
    
    switch (ch) {
    case ')':
        target_ch = '(';
        break;
    case '}':
        target_ch = '{';
        break;
    case ']':
        target_ch = '[';
        break;
    case '>':
        target_ch = '<';
        break;
    default:
        printf("input closing parenthesis is wrong!");
        target_ch = 0;
        break;
    }

    do {
        tmp_pop = pop(stack, stack_count);
        push(tmp_stack, &tmp_count, tmp_pop);
    } while (*tmp_pop != target_ch && *stack_count != 0);
    
    if (*stack_count == 0 && *tmp_pop != target_ch) {
        while (tmp_count != 0) {
            tmp_pop = pop(tmp_stack, &tmp_count);
            push(stack, stack_count, tmp_pop);
        }
        free(tmp_stack);
        tmp_stack = NULL;
    
        return -1;
    } else {
        const char* res = pop(tmp_stack, &tmp_count);

        while (tmp_count != 0) {
            tmp_pop = pop(tmp_stack, &tmp_count);
            push(stack, stack_count, tmp_pop);
        }
        free(tmp_stack);
        tmp_stack = NULL;

        return (res - str);
    }
}
void push(const char** stack, size_t* stack_count, const char* p)
{
    /* assert(*stack_count < STACK_SIZE); */
    stack[(*stack_count)++] = p;
}
int is_empty(size_t* stack_count)
{
    return (*stack_count == 0);
}
const char* pop(const char** stack, size_t* stack_count)
{
    assert(is_empty(stack_count) == FALSE);
    return stack[--*stack_count];
}



     

