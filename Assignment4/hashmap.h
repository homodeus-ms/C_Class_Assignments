#ifndef HASHMAP_H
#define HASHMAP_H

#include <stddef.h>
#include "node.h"

#define TRUE (1)
#define FALSE (0)

typedef struct hashmap {
    unsigned int (*hash_func)(const char* key);
    node_t** plist;
    size_t length;
} hashmap_t;

hashmap_t* init_hashmap_malloc(size_t length, unsigned int (*p_hash_func)(const char* key));

int add_key(hashmap_t* hashmap, const char* key, const int value);

int get_value(const hashmap_t* hashmap, const char* key);

int update_value(hashmap_t* hashmap, const char* key, int value);

int remove_key(hashmap_t* hashmap, const char* key);

void destroy(hashmap_t* hashmap);

size_t get_hash_idx(size_t n, size_t d);

size_t is_prime_number(size_t n);

size_t get_prime_number(size_t n);

node_t* init_new_node_malloc(const char* key, const int value);

#endif /* HASHMAP_H */

