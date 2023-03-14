#include "macros.h"

int get_bool_from_count_make_arr(void* arr, int start, int count, int value)
{
    size_t i;
    int* p = (int*)arr;

    for (i = start; i < start + count; ++i) {
        p[i] = value;
    }

    return count;
}


    
