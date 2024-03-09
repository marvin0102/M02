#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "lru_cache.h"

#define MAX_CAPACITY 5 // Maximum capacity of the cache
#define NUM_OPERATIONS 10 // Number of random operations to perform

bool check_cache(LRUCache *obj, int key, int value){
    struct list_head *ptr = obj->dhead.next;
    LRUNode *cache = list_entry(ptr, LRUNode, link);


    cache = list_first_entry(&obj->dhead, LRUNode, link);
    if (cache->key != key || cache->value != value) {
        printf("FAIL: (Expected: %d, Actual: %d)\n", value, cache->value);
        return false;
    }
    return true;
}

// Function to generate a random number between min and max
int random_int(int min, int max) {
    return min + rand() % (max - min + 1);
}

int main() {
    srand(time(NULL)); // Seed the random number generator

    LRUCache *cache = lRUCacheCreate(MAX_CAPACITY);

    for (int i = 0; i < NUM_OPERATIONS; i++) {
        int operation = random_int(0, 1); // 0 for put, 1 for get
        int key = random_int(1, 10); // Random key between 1 and 100
        int value = random_int(1, 100); // Random value between 1 and 1000

        if (operation == 0) {
            // Put operation
            printf("Operation %d: Put (%d, %d)\n", i+1, key, value);
            lRUCachePut(cache, key, value);
        } else {
            // Get operation
            printf("Operation %d: Get (%d)\n", i+1, key);
            int retrieved_value = lRUCacheGet(cache, key);
            printf("Retrieved value: %d\n", retrieved_value);
        }


    }

    lRUCacheFree(cache);

    return 0;
}