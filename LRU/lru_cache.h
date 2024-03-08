#include <stdbool.h>
#include <stdlib.h>

#define container_of(ptr, type, member) \
    ((type *) ((char *) (ptr) - (size_t) & (((type *) 0)->member)))

#define list_entry(ptr, type, member) container_of(ptr, type, member)

#define hlist_for_each(pos, head) \
    for (pos = (head)->first; pos; pos = pos->next)

#define hlist_for_each_safe(pos, n, head)        \
    for (pos = (head)->first; pos && ({          \
                                  n = pos->next; \
                                  true           \
                              });                \
         pos = n)

#define list_first_entry(ptr, type, field) list_entry((ptr)->next, type, field)
#define list_last_entry(ptr, type, field) list_entry((ptr)->prev, type, field)

#define list_for_each(p, head) for (p = (head)->next; p != head; p = p->next)

#define list_for_each_safe(p, n, head) \
    for (p = (head)->next, n = p->next; p != (head); p = n, n = p->next)

struct hlist_node;

struct hlist_head {
    struct hlist_node *first;
};

struct hlist_node {
    struct hlist_node *next, **pprev;
};

struct list_head {
    struct list_head *next, *prev;
};

typedef struct {
    int capacity;
    int count;
    struct list_head dhead;
    struct hlist_head hhead[];
} LRUCache;

typedef struct {
    int key;
    int value;
    struct hlist_node node;
    struct list_head link;
} LRUNode;

LRUCache *lRUCacheCreate(int capacity);

void lRUCacheFree(LRUCache *obj);

int lRUCacheGet(LRUCache *obj, int key);

void lRUCachePut(LRUCache *obj, int key, int value);