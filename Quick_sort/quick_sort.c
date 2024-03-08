#include <assert.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "list.h"


typedef struct __node {
    struct list_head list;
    long value;
} node_t;

struct list_head *list_tail(struct list_head *head)
{
    if(!head || list_empty(head))
        return NULL;
    return head->prev;
}

int list_length(struct list_head *head)
{
    if(!head || list_empty(head))
        return 0;
    int n = 0;
    struct list_head *node;
    list_for_each(node, head){
        n++;
    }
    return n;
}

struct list_head *list_construct(struct list_head *head, int n)
{
    if(!head)
        return head;
    node_t *node = malloc(sizeof(node_t));
    list_add(&(node->list),head);
    node->value = n;
    return head;
}

struct list_head *new_head()
{
    struct list_head *head = malloc(sizeof(struct list_head));
    if(!head)
        return NULL;
    INIT_LIST_HEAD(head);
    return head;
}

void list_free(struct list_head *head)
{
    if(!head)
        return ;
    struct list_head *next = head->next;
    node_t *entry, *safe;
    list_for_each_entry_safe (entry, safe, head, list) {
        list_del(&(entry->list));
        free(entry);
    }
    free(head);
}

void show_list(struct list_head *head)
{
    if(!head || list_empty(head))
        return;
    node_t *cur;
    list_for_each_entry (cur, head, list)
        printf("%ld ", cur->value);
    printf("\n");
}

void quick_sort(struct list_head **list)
{
    struct list_head *head = (*list);
    int n = list_length(head);
    int value;
    int i = 0;
    int max_level = 2*n;
    struct list_head *begin[max_level];
    struct list_head *result = new_head(), *left = new_head(), *right = new_head();
    
    begin[0] = head;
    for(int j=1 ; j<max_level ; j++){
        begin[j] = new_head();
    }       
    while (i >= 0) {
        struct list_head *L = begin[i]->next, *R = begin[i]->prev;
        if (L != R) {
            struct list_head *pivot = begin[i]->next;
            value = list_entry(pivot, node_t, list)->value;
            list_del(pivot);
            node_t *entry, *safe;
            list_for_each_entry_safe (entry, safe, begin[i],list) {
                list_move(&(entry->list),entry->value > value ? right : left);
            }
            list_splice_init(left, begin[i]);
            list_add(pivot,begin[i + 1]);
            list_splice_init(right, begin[i+2]);

            i += 2;
        } else {
            if (list_is_singular(begin[i]))
                list_splice_init(begin[i],result);
            i--;
        }
    }
    *list = result;
    for(int j=1 ; j<max_level ; j++){
        free(begin[j]);
    }
    free(right);
    free(left);
    
}

/* Verify if list is order */
static bool list_is_ordered(struct list_head *list)
{       
    bool first = true;
    int value;
    struct list_head *node;
    list_for_each(node,list) {
        int this_value = list_entry(node, node_t, list)->value;
        if (first) {
            value = this_value;
            first = false;
        } else {
            if (this_value < value)
                return false;
            value = this_value;
        }
    }
    return true;
}

/* shuffle array, only work if n < RAND_MAX */
void shuffle(int *array, size_t n)
{
    if (n <= 0)
        return;

    for (size_t i = 0; i < n - 1; i++) {
        size_t j = i + rand() / (RAND_MAX / (n - i) + 1);
        int t = array[j];
        array[j] = array[i];
        array[i] = t;
    }
}

int main(int argc, char **argv)
{
    struct list_head node, *head = &node;
    INIT_LIST_HEAD(head);

    size_t count = 10;

    int *test_arr = malloc(sizeof(int) * count);

    for (int i = 0; i < count; ++i)
        test_arr[i] = i;
    shuffle(test_arr, count);

    while (count--)
        head = list_construct(head, test_arr[count]);
    quick_sort(&head);
    assert(list_is_ordered(head));
    list_free(head);

    free(test_arr);

}