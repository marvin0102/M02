#include <stdio.h>

#include "lru_cache.h" // 假设 LRUCache 相关的头文件为 lru_cache.h

int main() {
    // 创建一个容量为 3 的 LRUCache
    LRUCache *cache = lRUCacheCreate(3);

    // 添加一些键值对
    lRUCachePut(cache, 1, 10);
    lRUCachePut(cache, 2, 20);
    lRUCachePut(cache, 3, 30);

    // 测试获取值
    printf("Value for key 1: %d\n", lRUCacheGet(cache, 1)); // 应该输出 10
    printf("Value for key 2: %d\n", lRUCacheGet(cache, 2)); // 应该输出 20

    // 添加新的键值对
    lRUCachePut(cache, 4, 40);

    // 测试获取值
    printf("Value for key 3: %d\n", lRUCacheGet(cache, 3)); // 应该输出 -1，因为 key 3 已经被淘汰
    printf("Value for key 4: %d\n", lRUCacheGet(cache, 4)); // 应该输出 40

    // 释放 LRUCache
    lRUCacheFree(cache);

    return 0;
}