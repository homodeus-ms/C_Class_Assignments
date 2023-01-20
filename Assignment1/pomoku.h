#ifndef POMOKU_H
#define POMOKU_H

#include "color.h"

#define TRUE (1)
#define FALSE (0)

void init_game(void);

unsigned int get_row_count(void);

unsigned int get_column_count(void);

int get_score(const color_t color);

int get_color(const unsigned int row, const unsigned int col);

int is_placeable(const unsigned int row, const unsigned int col);

int place_stone(const color_t color, const unsigned int row, const unsigned int col);

/* special moves */
int insert_row(const color_t color, const unsigned int row);

int insert_column(const color_t color, const unsigned int col);

int remove_row(const color_t color, const unsigned int row);

int remove_column(const color_t color, const unsigned int col);

int swap_rows(const color_t color, const unsigned int row0, const unsigned int row1);

int swap_columns(const color_t color, const unsigned int col0, const unsigned int col1);

int copy_row(const color_t color, const unsigned int src, const unsigned int dst);

int copy_column(const color_t color, const unsigned int src, const unsigned int dst);

/* support functions */

void print_array(void);

void check_score(const color_t color, const unsigned int row, const unsigned int col);

void add_score_after_chaining(const color_t color, const unsigned int chained_count);

void subtract_score_after_skill_used(const color_t color, const unsigned int score);

void swap_value(int* num1, int* num2);


#endif /* POMOKU_H */

