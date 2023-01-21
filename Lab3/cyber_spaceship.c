#include <stdio.h>

#include "cyber_spaceship.h"

const char* get_longest_safe_zone_or_null(const char* const cab_start_location, const size_t cab_length, const char* const cluster_start_locations[], const size_t cluster_lengths[], const size_t cluster_count, size_t* out_longest_safe_area_length)
{
    size_t i;
    size_t j;
    size_t nested_cluster;
    size_t continued_safe_area = 0;
    size_t longest_safe_area_start_offset = 0;
    *out_longest_safe_area_length = 0;    

    if (cluster_count == 0) {
        *out_longest_safe_area_length = cab_length;
        return cab_start_location;
    }

    for (i = 0; i < cab_length; ++i) {
        nested_cluster = 0;
        for (j = 0; j < cluster_count; ++j) {
            if (is_cluster_exist(cab_start_location + i, cluster_start_locations[j], cluster_lengths[j])) {
                nested_cluster++;
            }
        }

        if (is_here_safe(nested_cluster)) {
            continued_safe_area++;
        } else {
            continued_safe_area = 0;
            continue;
        }

        if (continued_safe_area >= *out_longest_safe_area_length) {
            *out_longest_safe_area_length = continued_safe_area;
            longest_safe_area_start_offset = i - (continued_safe_area - 1);
        }
    }

    if (*out_longest_safe_area_length == 0) {
        return NULL;
    }

    return cab_start_location + longest_safe_area_start_offset;
}

int get_travel_time(const char* const cab_start_location, const size_t cab_length, const char* const cluster_start_locations[], const size_t cluster_lengths[], const size_t cluster_count)
{
    size_t i;
    size_t j;
    size_t nested_cluster;
    size_t safe_area_count = 0;

    double travel_time = 0.0;

    if (cluster_count == 0) {
        travel_time = cab_length / 10.0;
        
        return do_round(travel_time);
    }

    for (i = 0; i < cab_length; ++i) {
        nested_cluster = 0;
        for (j = 0; j < cluster_count; ++j) {
            if (is_cluster_exist(cab_start_location + i, cluster_start_locations[j], cluster_lengths[j])) {
                nested_cluster++;
            }
        }

        if (is_here_safe(nested_cluster)) {
            safe_area_count++;
        } 
    }

    travel_time = safe_area_count / 10.0 + (cab_length - safe_area_count) / 5.0;

    return do_round(travel_time);
}

int is_cluster_exist(const char* current_location, const char* const cluster_start_location, const size_t cluster_length)
{
    return current_location >= cluster_start_location ? current_location < cluster_start_location + cluster_length : FALSE;
}

int is_here_safe(const size_t nested_cluster)
{
    return (nested_cluster & 0x1) == 0 ? TRUE : FALSE;
}

int do_round(double num)
{
    int integer_part = (int)num;

    return num - integer_part >= 0.5 ? num + 1 : num;
}




        
            
    

    

