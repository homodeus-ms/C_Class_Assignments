#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "hashmap.h"

#define DEFAULT_ARRAY_LENGTH (20)

static unsigned int hash_function(const char* key);

void print_node(hashmap_t* hashmap);

int main(void)
{
    size_t i = 0;
    hashmap_t* hashmap = NULL;

    hashmap = init_hashmap_malloc(DEFAULT_ARRAY_LENGTH, hash_function);

#if 1
    for (i = 0; i < 100; ++i) {
        char key[100];
        int value = (int)i;
        int c;
        int dummy = 512;

        sprintf(key, "key%zu", i);

        assert(add_key(hashmap, key, value) == TRUE);

        c = get_value(hashmap, key);
        
        assert(c == value);

        assert(add_key(hashmap, key, dummy) == FALSE);

        c = get_value(hashmap, key);
        assert(c == value);
    }
    
    

    for (i = 0; i < 100; ++i) {
        char key[100];
        int value = (int)(i * i * i);
        int c;

        sprintf(key, "key%zu", i);

        assert(update_value(hashmap, key, value) == TRUE);
        c = get_value(hashmap, key);

        assert(c == value);
    }

    

    for (i = 0; i < 100; ++i) {
        char key[100];
        int c;

        sprintf(key, "key%zu", i);

        assert(remove_key(hashmap, key) == TRUE);
        c = get_value(hashmap, key);

        assert(c == -1);

        assert(remove_key(hashmap, key) == FALSE);
    }
    

    for (i = 0; i < DEFAULT_ARRAY_LENGTH; ++i) {
        assert((hashmap->plist)[i] == NULL);
    }
#endif

    

    destroy(hashmap);

    printf("No Assert!!\n");

    return 0;
}

static unsigned int hash_function(const char* key)
{
    unsigned int code = 0;
    const char* c = key;

    while (*c != '\0') {
        code += *c++;
    }

    return code;
}

void print_node(hashmap_t* hashmap)
{
    size_t i;
    node_t* p;

    for (i = 0; i < hashmap->length; ++i) {
        p = hashmap->plist[i];
        while (p != NULL) {
            printf("[idx : %d] [key : %s] [value : %d]\n", i, p->key, p->value);
            p = p->next;
        }  
        puts("");
    }
}




