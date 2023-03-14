#ifndef MACROS_H
#define MACROS_H

int put_values_into_array(void* arr, int start, int count, int value)
{
    size_t i;
    int* p = (int*)arr;
    for (i = start; i < count + start; ++i) {
        p[i] = value;
    }
    return count;
}

#define MAX(x, y) ((x) > (y) ? (x) : (y))

#define MIN(x, y) ((x) > (y) ? (y) : (x))

#define ABS(x) ((x) < (0) ? -1 * (x) : (x))

#define RANGE(curr, min, max) for ((curr) = (min); (curr) <= (max); ++(curr))

#define RANGE_DESC(curr, max, min) for ((curr) = (max); (curr) >= (min); --(curr))

#define SET(ary, start, count, value) (put_values_into_array((ary), (start), (count), (value)))

#endif /* MACROS_H */
