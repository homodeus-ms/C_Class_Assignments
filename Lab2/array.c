#include <stdio.h>
#include "array.h"

int get_index_of(const int numbers[], const size_t element_count, const int num)
{
    const int* ARR_ADDRESS = numbers;
    size_t i;
    
    if (is_array_empty(numbers)) {
        return -1;
    }

    for (i = 0; i < element_count; ++i) {
        if (num == *(ARR_ADDRESS + i)) {
            return i;
        }
    }

    return -1;
}

int get_last_index_of(const int numbers[], const size_t element_count, const int num)
{
    const int* ARR_ADDRESS = numbers;
    size_t index = element_count;
    
    if (is_array_empty(numbers)) {
        return -1;
    }
 
    while (index-- > 0) {
        if (num == *(ARR_ADDRESS + index)) {
            return index;
        }
    }

    return -1;
}

int get_max_index(const int numbers[], const size_t element_count)
{
    const int* ARR_ADDRESS = numbers;
    size_t max_value_Idx = 0;

    if (element_count == 0 || is_array_empty(numbers)) {
        return -1;
    }
    
    while (++ARR_ADDRESS < numbers + element_count) {
        if (*ARR_ADDRESS > numbers[max_value_Idx]) {
            max_value_Idx = ARR_ADDRESS - numbers;
        }
    }

    return max_value_Idx;
}

int get_min_index(const int numbers[], const size_t element_count)
{
    const int* ARR_ADDRESS = numbers;
    size_t min_Value_Idx = 0;

    if (is_array_empty(numbers)) {
        return -1;
    }

    while (++ARR_ADDRESS < numbers + element_count) {
        if (*ARR_ADDRESS < numbers[min_Value_Idx]) {
            min_Value_Idx = ARR_ADDRESS - numbers;
        }
    }

    return min_Value_Idx;
}

int is_all_positive(const int numbers[], const size_t element_count)
{
    const int* ARR_ADDRESS = numbers;    
    size_t i;

    if (is_array_empty(numbers)) {
        return FALSE;
    }

    for (i = 0; i < element_count; ++i) {
        if (*(ARR_ADDRESS + i) < 0) {
            return FALSE;
        }
    }
         
    return TRUE;
}

int has_even(const int numbers[], const size_t element_count)
{
    const int* ARR_ADDRESS = numbers;
    size_t i;

    if (is_array_empty(numbers)) {
        return FALSE;
    }
    
    for (i = 0; i < element_count; ++i) {
        if (*(ARR_ADDRESS) != 0 && (*(ARR_ADDRESS + i) & 1) == 0) {
            return TRUE;
        }
    }

    return FALSE;
}

int insert(int numbers[], const size_t element_count, const int num, const size_t pos)
{
    int* const ARR_ADDRESS = numbers;
    size_t index = element_count;

    if (pos > element_count) {
        return FALSE;
    }

    while (index > pos) {
        *(ARR_ADDRESS + index) = *(ARR_ADDRESS + index - 1); 
        index--;
    }

    *(ARR_ADDRESS + pos) = num;
    
    return TRUE;
}

int remove_at(int numbers[], const size_t element_count, const size_t index)
{
    int* const ARR_ADDRESS = numbers;
    size_t i;

    if (index >= element_count) {
        return FALSE;
    }

    for (i = index; i < element_count - 1; ++i) {
        *(ARR_ADDRESS + i) = *(ARR_ADDRESS + i + 1);
    }

    numbers[element_count - 1] = 0x80000000;
    
    return TRUE;
}

int is_array_empty(const int numbers[])
{
    return numbers[0] == 0x80000000 ? TRUE : FALSE;
}

