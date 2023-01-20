#include <stdio.h>
#include <limits.h>
#include <assert.h>

#include "pomoku.h"

#define MAX_ROW (20)
#define MAX_COL (20)
#define INIT_LENGTH (15)
#define MIN_ROW (10)
#define MIN_COL (10)
#define B (0)
#define W (1)

static unsigned int s_row_count = 15;
static unsigned int s_col_count = 15;

static int s_player_black_score = 0;  
static int s_player_white_score = 0;

static int board[MAX_ROW][MAX_COL];

void init_game(void)
{ 
    size_t i;
    size_t j;

    s_row_count = 15;
    s_col_count = 15;

    s_player_black_score = 0;  
    s_player_white_score = 0;

    for (i = 0; i < MAX_ROW; ++i) {
        for (j = 0; j < MAX_COL; ++j) {
            if (i < INIT_LENGTH && j < INIT_LENGTH) {
                board[i][j] = -1;
            }
            else {
                board[i][j] = INT_MIN;
            }
        }
    }
}

unsigned int get_row_count(void)
{
    return s_row_count;
}

unsigned int get_column_count(void)
{
    return s_col_count;
}

int get_score(const color_t color)
{
    switch (color) {
    case COLOR_BLACK :
        return s_player_black_score;
    case COLOR_WHITE :
        return s_player_white_score;
    default :
        return -1;
    }
}

int get_color(const unsigned int row, const unsigned int col)
{
    switch (board[row][col]) {
    case B :
        return B;
    case W : 
        return W;
    default :
        return -1;
    }
}

int is_placeable(const unsigned int row, const unsigned int col)
{
    return board[row][col] == -1 ? TRUE : FALSE;
}

int place_stone(const color_t color, const unsigned int row, const unsigned int col)
{
    if (is_placeable(row, col) == FALSE) {
        return FALSE;
    }

    switch (color) {
    case COLOR_BLACK :
        board[row][col] = B;
        break;
    case COLOR_WHITE :
        board[row][col] = W;
        break;
    default :
        return FALSE;
    }

    check_score(color, row, col);

    return TRUE;
}

int insert_row(const color_t color, const unsigned int row)
{
    int score = get_score(color); 
    int* inserted_start_point_p = &board[row][0]; 
    int* last_value_p = &board[s_row_count - 1][s_col_count - 1]; 

    if (!(color <= 1) || s_row_count == 20 || row >= s_row_count || score < 3) {
        return FALSE;
    }

    while (last_value_p >= inserted_start_point_p) {
        *(last_value_p + MAX_COL) = *last_value_p;
        last_value_p--;
    }

    while (inserted_start_point_p < last_value_p + s_col_count) {
        *inserted_start_point_p = -1;    /* -1 is placeable */
        inserted_start_point_p++;
    }

    subtract_score_after_skill_used(color, 3);
    s_row_count++;

    return TRUE;
}     

int insert_column(const color_t color, const unsigned int col)
{
    int score = get_score(color); 
    int* inserted_col_first_row_p = &board[0][col];
    int* inserted_col_last_row_p = &board[s_row_count - 1][col]; 
    int* last_value_p = inserted_col_last_row_p + (s_col_count - 1 - col);  

    if (!(color <= 1) || s_col_count == 20 || col >= s_col_count || score < 3) {
        return FALSE;
    }

    while (inserted_col_last_row_p >= inserted_col_first_row_p) {
        *(last_value_p + 1) = *last_value_p;
        last_value_p--;

        if (inserted_col_last_row_p == last_value_p) {
            *(last_value_p + 1) = *last_value_p;
            *inserted_col_last_row_p = -1;
            inserted_col_last_row_p -= MAX_COL;
            last_value_p = inserted_col_last_row_p + (s_col_count - 1 - col); 
        }
    }

    subtract_score_after_skill_used(color, 3);
    s_col_count++;

    return TRUE;
}

int remove_row(const color_t color, const unsigned int row)
{
    int score = get_score(color); 
    int* target_row_first_col_p = &board[row][0];

    if (!(color <= 1) || s_row_count == 10 || row >= s_row_count || score < 3) {
        return FALSE;
    }

    while (target_row_first_col_p <= &board[s_row_count - 1][s_col_count - 1]) {
        *target_row_first_col_p = *(target_row_first_col_p + MAX_COL);
        target_row_first_col_p++;
    }
    
    subtract_score_after_skill_used(color, 3);
    s_row_count--;

    return TRUE;
}


int remove_column(const color_t color, const unsigned int col)
{
    int score = get_score(color); 
    int* target_col_first_row_p = &board[0][col];
    const int* const loop_end = &board[s_row_count - 1][s_col_count -1];
    size_t i = 0;

    if (!(color <= 1) || s_col_count == 10 || col >= s_col_count || score < 3) {
        return FALSE;
    }
    
    while (target_col_first_row_p <= loop_end) {
        *(target_col_first_row_p) = *(target_col_first_row_p + 1);
        
        if ((target_col_first_row_p - &board[i][0]) % (s_col_count - 1) == 0) {
            target_col_first_row_p += (MAX_COL - s_col_count) + col;
            i++;
        }

        target_col_first_row_p++;
    }

    subtract_score_after_skill_used(color, 3);
    s_col_count--;

    return TRUE;
}

int swap_rows(const color_t color, const unsigned int row0, const unsigned int row1)
{
    int score = get_score(color); 
    size_t j;

    if (!(color <= 1) || row0 >= s_row_count || row1 >= s_row_count || score < 2) {
        return FALSE;
    }

    for (j = 0; j < s_col_count; ++j) {
        swap_value(&board[row0][j], &board[row1][j]);
    }

    subtract_score_after_skill_used(color, 2);

    return TRUE;
} 

int swap_columns(const color_t color, const unsigned int col0, const unsigned int col1)
{
    int score = get_score(color); 
    size_t i;

    if (!(color <= 1) || col0 >= s_col_count || col1 >= s_col_count || score < 2) {
        return FALSE;
    }

    for (i = 0; i < s_row_count; ++i) {
        swap_value(&board[i][col0], &board[i][col1]);
    }

    subtract_score_after_skill_used(color, 2);

    return TRUE;
}

int copy_row(const color_t color, const unsigned int src, const unsigned int dst)
{
    int score = get_score(color); 
    size_t j;
    int* src_p = &board[src][0];

    if (!(color <= 1) || src >= s_row_count || dst >= s_row_count || score < 4) {
        return FALSE;
    }

    for (j = 0; j < s_col_count; ++j) {
        *(src_p + ((dst - src) * MAX_COL)) = *src_p;
        src_p++;
    }

    subtract_score_after_skill_used(color, 4);

    return TRUE;
}

int copy_column(const color_t color, const unsigned int src, const unsigned int dst)
{
    int score = get_score(color); 
    size_t i;
    int* src_p = &board[0][src];

    if (!(color <= 1) || src >= s_col_count || dst >= s_col_count || score < 4) {
        return FALSE;
    }

    for (i = 0; i < s_row_count; ++i) {
        *(src_p + (dst - src)) = *src_p;
        src_p += MAX_COL;
    }

    subtract_score_after_skill_used(color, 4);

    return TRUE;
}

void check_score(const color_t color, const unsigned int row, const unsigned int col)
{
    unsigned int chained_count;
    unsigned int copied_row;
    unsigned int copied_col;
    int i = -1;
    int j = -1;

    while (!(i == 0 && j == 0)) {
        copied_row = row;
        copied_col = col;
        chained_count = 1;

        while (TRUE) {
            copied_row += i;
            copied_col += j;

            if (copied_row >= 0 && copied_col >= 0 && copied_row < s_row_count && copied_col < s_col_count) {
                if (board[row][col] == board[copied_row][copied_col]) {
                    chained_count++;
                }
                else {
                    break;
                }
            }
            else {
                break;
            }
        }

        copied_row = row;
        copied_col = col;

        while (TRUE) {
            copied_row -= i;
            copied_col -= j;

            if (copied_row >= 0 && copied_col >= 0 && copied_row < s_row_count && copied_col < s_col_count) {
                if (board[row][col] == board[copied_row][copied_col]) {
                    chained_count++;
                }
                else {
                    break;
                }
            }
            else {
                break;
            }
        }

        if (chained_count >= 5) {
            add_score_after_chaining(color, chained_count);
        }

        if (j != 1) {
            j++;
        }
        else {
            i++;
            j = -1;
        }
    }      
}

void add_score_after_chaining(const color_t color, const unsigned int chained_count)
{
    assert(color == COLOR_BLACK || color == COLOR_WHITE); 
    
    if (color == COLOR_BLACK) {
        s_player_black_score += chained_count - 4;
    }
    else {
        s_player_white_score += chained_count - 4;
    }
}
void subtract_score_after_skill_used(const color_t color, const unsigned int score)
{
    assert(color == COLOR_BLACK || color == COLOR_WHITE);    

    if (color == COLOR_BLACK) {
        s_player_black_score -= score;
    }
    else {
        s_player_white_score -= score;
    }
}

void swap_value(int* num1, int* num2)
{
    int temp = *num1;
    *num1 = *num2;
    *num2 = temp;
}

void print_array(void)
{
    size_t i;
    size_t j;

    printf("\n");
    for (i = 0; i < MAX_ROW; ++i) {
        for (j = 0; j <MAX_COL; ++j) {
            printf("%d ", board[i][j]);
        }
        printf("\n");
    }
}











