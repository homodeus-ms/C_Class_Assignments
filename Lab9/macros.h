#ifndef MACROS_H
#define MACROS_H

#define MAX(x, y) ((x) > (y) ? (x) : (y))

#define MIN(x, y) ((x) > (y) ? (y) : (x))

#define ABS(x) ((x) >= (0) ? (x) : (-1 * (x)))

#define RANGE(curr, min, max) for ((curr) = (min); (curr) <= (max); ++(curr))

#define RANGE_DESC(curr, max, min) for ((curr) = (max); (curr) >= (min); --(curr))

#define SET(ary, start, count, value)                                                       \
    (1);                                                                                             \
    {                                                                                                \
        size_t temp_idx;                                                                        \
        for (temp_idx = (start); temp_idx < ((start) + (count)); ++temp_idx) {    \
            (ary)[temp_idx] = (value);                                                         \
        }                                                                                            \
    } if (count)                                                                                   \




#endif /* MACROS_H */
