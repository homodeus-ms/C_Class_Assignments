#include <limits.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "todo_list.h"

enum { TODO_LIST_SIZE = 16 };

todo_list_t init_todo_list(size_t max_size)
{
    todo_list_t new_list;
    char** new_tasks;
    int32_t* new_priorities;
    
    new_tasks = malloc(max_size * sizeof(char*));
    new_priorities = malloc(max_size * sizeof(int32_t));

    new_list.tasks = new_tasks;
    new_list.priorities = new_priorities;
    new_list.count = 0;
    new_list.max_count = max_size;

    return new_list;
}

void finalize_todo_list(todo_list_t* todo_list)
{
    size_t i;

    for (i = 0; i < todo_list->count; ++i) {
        free(todo_list->tasks[i]);
    }

    free(todo_list->tasks);
    free(todo_list->priorities);
}

bool add_todo(todo_list_t* todo_list, const int32_t priority, const char* task)
{
    if (todo_list->count >= todo_list->max_count) {
        return false;
    }

    size_t str_len = strlen(task);
    char* buffer;
    buffer = malloc(str_len + 1);
    
    const char* p = task;
    char* q = buffer;

    while (*p != 0) {
        *q++ = *p++;
    }
    *q = '\0';

    todo_list->tasks[todo_list->count] = buffer;
    todo_list->priorities[todo_list->count++] = priority;

    return true;
}

bool complete_todo(todo_list_t* todo_list)
{
    if (todo_list->count == 0) {
        return false;
    }
    
    size_t i;
    size_t idx;
    idx = get_index_highest_priority(todo_list);

    free(todo_list->tasks[idx]);
    todo_list->tasks[idx] = NULL;

    for (i = idx; i < (todo_list->count) - 1; ++i) {
        todo_list->tasks[i] = todo_list->tasks[i + 1];
        todo_list->priorities[i] = todo_list->priorities[i + 1];
    }
    todo_list->tasks[i] = NULL;
    todo_list->priorities[i] = INT32_MIN;

    todo_list->count--;

    return true;
}

const char* peek_or_null(const todo_list_t* todo_list)
{
    if (todo_list->count == 0) {
        return NULL;
    }

    size_t idx;
    idx = get_index_highest_priority(todo_list);

    return todo_list->tasks[idx];
}

size_t get_count(const todo_list_t* todo_list)
{
    return todo_list->count;
}

bool is_empty(const todo_list_t* todo_list)
{
    return todo_list->count == 0 ? true : false;
}

size_t get_index_highest_priority(const todo_list_t* todo_list)
{
    size_t i;
    size_t result = 0;
    int32_t value = todo_list->priorities[0];

    for (i = 0; i < todo_list->max_count; ++i) {
        if (value < todo_list->priorities[i]) {
            value = todo_list->priorities[i];
            result = i;
        }
    }
    
    return result;
}












