#ifndef MACROS_H
#define MACROS_H

#define MAX(x, y) ((x) > (y) ? (x) : (y))

#define MIN(x, y) ((x) > (y) ? (y) : (x))

#define ABS(x) ((x) < (0) ? -1 * (x) : (x))

#define RANGE(curr, min, max) for ((curr) = (min); (curr) <= (max); ++(curr))

#define RANGE_DESC(curr, max, min) for ((curr) = (max); (curr) >= (min); --(curr))

#define SET(ary, start, count, value) { \
                                                   int idx = 0; \
                                                   while (idx != (count)) { \
                                                       ary[(start) + idx++] = (value); \
                                                   } \
                                               } \

#endif /* MACROS_H */
