#ifndef CYBER_SPACESHIP_H
#define CYBER_SPACESHIP_H

#define ARRAY_LENGTH(arr) (sizeof(arr) / sizeof(arr[0]))

#define TRUE (1)
#define FALSE (0)

#include <stddef.h>

const char* get_longest_safe_zone_or_null(const char* const cab_start_location, const size_t cab_length, const char* const cluster_start_locations[], const size_t cluster_lengths[], const size_t cluster_count, size_t* out_longest_safe_area_length);

int get_travel_time(const char* const cab_start_location, const size_t cab_length, const char* const cluster_start_locations[], const size_t cluster_lengths[], const size_t cluster_count);

int is_cluster_exist(const char* current_location, const char* const cluster_start_location, const size_t cluster_length);
 
int is_here_safe(const size_t nested_cluster);

int do_round(double num);

#endif /* CYBER_SPACESHIP */



