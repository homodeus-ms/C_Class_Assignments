#ifndef MACROS_H
#define MACROS_H

#define MAX(x, y) (x > y ? x : y)

#define MIN(x, y) (x > y ? y : x)

#define ABS(x) (x < 0 ? -1 * x : x)

#define RANGE(curr, min, max) for (i = min; i <= max; ++i)

#define RANGE_DESC(curr, max, min) for (i = max; i >= min; --i)

#define SET(ary, start, count, value) for (i = start; i < start + count; ++i) { \
                                                   arr[i] = value;                            \
                                               } \

#endif /* MACROS_H */
