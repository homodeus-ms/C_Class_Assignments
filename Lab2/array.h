#ifndef ARRAY_H
#define ARRAY_H

#include <stddef.h>

#define TRUE (1)
#define FALSE (0)

int get_index_of(const int numbers[], const size_t element_count, const int num);

int get_last_index_of(const int numbers[], const size_t element_count, const int num);

int get_max_index(const int numbers[], const size_t element_count);

int get_min_index(const int numbers[], const size_t element_count);

int is_all_positive(const int numbers[], const size_t element_count);

int has_even(const int numbers[], const size_t element_count);

int insert(int numbers[], const size_t element_count, const int num, const size_t pos);

int remove_at(int numbers[], const size_t element_count, const size_t index);

int is_array_empty(const int numbers[]);

#endif /* ARRAY_H */

