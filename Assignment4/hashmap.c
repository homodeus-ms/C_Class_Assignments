#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hashmap.h"

hashmap_t* init_hashmap_malloc(size_t length, unsigned int (*p_hash_func)(const char* key))
{
    hashmap_t* new_map;
    new_map = malloc(sizeof(hashmap_t));
    
    if (length == 0) {
        new_map->hash_func = p_hash_func;
        new_map->plist = NULL;
        new_map->length = 0;
    
        return new_map;
    }
    
    length = get_prime_number(length);

    node_t** new_list;
    new_list = malloc(length * sizeof(node_t*));

    size_t i;
    for (i = 0; i < length; ++i) {
        new_list[i] = NULL;
    }

    new_map->hash_func = p_hash_func;
    new_map->plist = new_list;
    new_map->length = length;

    return new_map;
}
    
int add_key(hashmap_t* hashmap, const char* key, const int value)
{
    if (hashmap->plist == NULL) {
        return FALSE;
    }

    size_t idx = hashmap->hash_func(key);
    idx = get_hash_idx(idx, hashmap->length);

    node_t* new_node;

    if (hashmap->plist[idx] == NULL) {
        new_node = init_new_node_malloc(key, value);
        hashmap->plist[idx] = new_node; 

        return TRUE;
    }
    
    node_t* p = hashmap->plist[idx];
    node_t* keep_p;

    while (p != NULL) {
        if (!strcmp(p->key, key)) {
            return FALSE;
        }

        keep_p = p;
        p = p->next;
    }

    new_node = init_new_node_malloc(key, value);
    keep_p->next = new_node;

    return TRUE;
}

int get_value(const hashmap_t* hashmap, const char* key)
{
    size_t idx;

    idx = hashmap->hash_func(key);
    idx = get_hash_idx(idx, hashmap->length);

    node_t* p;
    p = hashmap->plist[idx];

    while (p != NULL) {
        if (!strcmp(p->key, key)) {
            return p->value;
        }
        p = p->next;
    }

    return -1;
}

int update_value(hashmap_t* hashmap, const char* key, int value)
{
    size_t idx;

    idx = hashmap->hash_func(key);
    idx = get_hash_idx(idx, hashmap->length);

    node_t* p = hashmap->plist[idx];

    while (p != NULL) {
        if (!strcmp(p->key, key)) {
            p->value = value;
            return TRUE;
        }
        p = p->next;
    }

    return FALSE;
}

int remove_key(hashmap_t* hashmap, const char* key)
{
    size_t idx;

    idx = hashmap->hash_func(key);
    idx = get_hash_idx(idx, hashmap->length);

    node_t** pp = &(hashmap->plist[idx]);

    while (*pp != NULL) {
        node_t** tmp = pp;

        if (!strcmp((*pp)->key, key)) {
            *pp = (*pp)->next;
            free(*tmp);
            
            return TRUE;
        }
        pp = &((*pp)->next);
    }

    return FALSE;
}

void destroy(hashmap_t* hashmap)
{
    size_t i;
    node_t* p;

    for (i = 0; i < hashmap->length; ++i) {
        p = hashmap->plist[i];

        while (p != NULL) {
            node_t* tmp = p->next;
            free(p->key);
            free(p);
            p = tmp;
        }
    }

    free(hashmap->plist);

    free(hashmap);
}

size_t get_hash_idx(size_t n, size_t d)
{
    return n % d;
}

size_t is_prime_number(size_t n)
{
    size_t i;
    size_t is_prime_number = TRUE;

    for (i = 3; i < n / 2; i += 2) {
        if (n % 2 == 0) {
            is_prime_number = FALSE;
            break;
        }
    }

    return is_prime_number;
}

size_t get_prime_number(size_t n)
{
    n = n * 2 + 1;
    
    if (is_prime_number(n)) {
        return n;
    }

    while (TRUE) {
        n += 2;
        if (is_prime_number(n)) {
            break;
        }
    }

    return n;
}

node_t* init_new_node_malloc(const char* key, const int value)
{
    size_t key_len = strlen(key);
    node_t* new_node;
    new_node = malloc(sizeof(node_t));

    char* pkey;
    pkey = malloc(key_len + 1);
    strncpy(pkey, key, key_len);
    pkey[key_len] = '\0'; 

    new_node->key = pkey;
    new_node->value = value;
    new_node->next = NULL;

    return new_node;
}






