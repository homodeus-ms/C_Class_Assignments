#ifndef MACROS_H
#define MACROS_H

#define MAX(x, y) ((x) > (y) ? (x) : (y))

#define MIN(x, y) ((x) > (y) ? (y) : (x))

#define ABS(x) ((x) < (0) ? -1 * (x) : (x))

#define RANGE(curr, min, max) for ((curr) = (min); (curr) <= (max); ++(curr))

#define RANGE_DESC(curr, max, min) for ((curr) = (max); (curr) >= (min); --(curr))

#define SET(ary, start, count, value) (put_values((ary), (start), (count), (value)))

int put_values(int* arr, int start, int count, int value)
{
    size_t i;
    for (i = start; i < count + start; ++i) {
        arr[i] = value;
    }
    return count;
}

#endif /* MACROS_H */
