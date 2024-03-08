#include <stdio.h>
#include <stdlib.h>

#define container_of(ptr, type, member) \
    ((type *) ((char *) (ptr) - (size_t) & (((type *) 0)->member)))

#define list_entry(ptr, type, member) container_of(ptr, type, member)

#define list_for_each(pos, head) \
    for (pos = (head)->right; pos!=head ; pos = pos->right)

struct TreeNode {
    int val;
    struct TreeNode *left, *right;
};

struct order_node {
    struct TreeNode node;
    int idx;
};


struct TreeNode *buildTree(int *preorder,
                                  int preorderSize,
                                  int *inorder,
                                  int inorderSize);


