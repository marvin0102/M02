#include "lru_cache.h"


static void INIT_HLIST_HEAD(struct hlist_head *h)
{
    h->first = NULL;
}

static void hlist_add_head(struct hlist_node *n, struct hlist_head *h)
{
    if (h->first)
        h->first->pprev = &n->next;
    n->next = h->first;
    n->pprev = &h->first;
    h->first = n;
}

static void hlist_del(struct hlist_node *n)
{
    struct hlist_node *next = n->next, **pprev = n->pprev;
    *pprev = next;
    if (next)
        next->pprev = pprev;
}



static void INIT_LIST_HEAD(struct list_head *list)
{
    list->next = list->prev = list;
}

static void __list_add(struct list_head *new,
                struct list_head *prev,
                struct list_head *next)
{
    next->prev = new;
    new->next = next;
    new->prev = prev;
    prev->next = new;
}

static void list_add(struct list_head *_new, struct list_head *head)
{
    __list_add(_new, head, head->next);
}

static void __list_del(struct list_head *entry)
{
    entry->next->prev = entry->prev;
    entry->prev->next = entry->next;
}

static void list_del(struct list_head *entry)
{
    __list_del(entry);
    entry->next = entry->prev = NULL;
}

static void list_move(struct list_head *entry, struct list_head *head)
{
    __list_del(entry);
    list_add(entry, head);
}

LRUCache *lRUCacheCreate(int capacity)
{
    LRUCache *cache = malloc(2 * sizeof(int) + sizeof(struct list_head) +
                             capacity * sizeof(struct list_head));
    cache->capacity = capacity;
    cache->count = 0;
    INIT_LIST_HEAD(&cache->dhead);
    for (int i = 0; i < capacity; i++)
        INIT_HLIST_HEAD(&cache->hhead[i]);
    return cache;
}

void lRUCacheFree(LRUCache *obj)
{
    struct list_head *pos, *n;
    list_for_each_safe (pos, n, &obj->dhead) {
        LRUNode *cache = list_entry(pos, LRUNode, link);
        list_del(&cache->link);
        free(cache);
    }
    free(obj);
}

int lRUCacheGet(LRUCache *obj, int key)
{
    int hash = key % obj->capacity;
    struct hlist_node *pos;
    hlist_for_each (pos, &obj->hhead[hash]) {
        LRUNode *cache = list_entry(pos, LRUNode, node);
        if (cache->key == key) {
            list_move(&cache->link, &obj->dhead);
            hlist_del(&cache->node);
            hlist_add_head(&cache->node, &obj->hhead[hash]);
            return cache->value;
        }
    }
    return -1;
}

void lRUCachePut(LRUCache *obj, int key, int value)
{
    LRUNode *cache = NULL;
    int hash = key % obj->capacity;
    struct hlist_node *pos;
    hlist_for_each (pos, &obj->hhead[hash]) {
        LRUNode *c = list_entry(pos, LRUNode, node);
        if (c->key == key) {
            list_move(&c->link, &obj->dhead);
            cache = c;
        }
    }

    if (!cache) {
        if (obj->count == obj->capacity) {
            cache = list_last_entry(&obj->dhead, LRUNode, link);
            list_move(&cache->link, &obj->dhead);
            hlist_del(&cache->node);
            hlist_add_head(&cache->node, &obj->hhead[hash]);
        } else {
            cache = malloc(sizeof(LRUNode));
            hlist_add_head(&cache->node, &obj->hhead[hash]);
            list_add(&cache->link, &obj->dhead);
            obj->count++;
        }
        cache->key = key;
    } else {
        hlist_del(&cache->node);
        hlist_add_head(&cache->node, &obj->hhead[hash]);
    }
    cache->value = value;
}