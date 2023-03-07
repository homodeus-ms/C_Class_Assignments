#include <assert.h>
#include <stdio.h>

#include "parentheses.h"

#define MAX_SIZE (5)

int main(void)
{
    parenthesis_t parentheses[MAX_SIZE];
    ringbuffer_t ringbuffer;
    size_t len;

    ringbuffer.max_size = MAX_SIZE;
    ringbuffer.parentheses = parentheses;

    len = find_matching_parentheses(&ringbuffer, "");
    assert(len == 0);
    assert(ringbuffer.start_index == 0);

    printf("NO ASSERT!");

    return 0;
}



