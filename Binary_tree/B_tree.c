#include <stdio.h>
#include <stdlib.h>

#include "B_tree.h"

static inline void INIT_HLIST_HEAD(struct TreeNode *h)
{
    h->right = h;
    h->left = h;
}

static inline void list_del(struct TreeNode *node)
{
    struct TreeNode *next = node->right;
    struct TreeNode *prev = node->left;

    next->left = prev;
    prev->right = next;
}

static inline void list_add_head(struct TreeNode *n, struct TreeNode *h)
{
    struct TreeNode *next = h->right;

    next->left = n;
    n->right = next;
    n->left = h;
    h->right = n;
}

static struct TreeNode* find(int num, int size, const struct TreeNode *heads)
{
    struct TreeNode *p;
    int hash = (num < 0 ? -num : num) % size;
    list_for_each (p, &heads[hash]) {
        struct order_node *on = list_entry(p, struct order_node, node);
        if (num == on->node.val){
            list_del(p);
            return p;
        }    
    }
    return NULL;
}

static struct TreeNode *dfs(int *preorder,
                            int pre_low,
                            int pre_high,
                            int *inorder,
                            int in_low,
                            int in_high,
                            struct TreeNode *in_heads,
                            int size)
{
    if (in_low > in_high || pre_low > pre_high)
        return NULL;

    struct TreeNode *tn = find(preorder[pre_low], size, in_heads);
    int idx = list_entry(tn, struct order_node, node)->idx;
    tn->left = dfs(preorder, pre_low + 1, pre_low + (idx - in_low), inorder,
                   in_low, idx - 1, in_heads, size);
    tn->right = dfs(preorder, pre_high - (in_high - idx - 1), pre_high, inorder,
                    idx + 1, in_high, in_heads, size);
    return tn;
}

static inline void node_add(int val,
                            int idx,
                            int size,
                            struct TreeNode *heads)
{
    struct order_node *on = malloc(sizeof(*on));
    on->node.val = val;
    on->idx = idx;
    int hash = (val < 0 ? -val : val) % size;
    list_add_head(&on->node, &heads[hash]);
}

struct TreeNode *buildTree(int *preorder,
                                  int preorderSize,
                                  int *inorder,
                                  int inorderSize)
{
    struct TreeNode *in_heads = malloc(inorderSize * sizeof(*in_heads));
    for (int i = 0; i < inorderSize; i++)
        INIT_HLIST_HEAD(&in_heads[i]);
    for (int i = 0; i < inorderSize; i++)
        node_add(inorder[i], i, inorderSize, in_heads);

    return dfs(preorder, 0, preorderSize - 1, inorder, 0, inorderSize - 1,
               in_heads, inorderSize);
}