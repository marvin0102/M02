#include <stdio.h>

#include "B_tree.h"


// 递归打印二叉树
void printTree(struct TreeNode *root) {
    if (root == NULL)
        return;
    printf("%d ", root->val);
    printTree(root->left);
    printTree(root->right);
}

int main() {
    // 构造测试用的 preorder 和 inorder 数组
    int preorder[] = {3, 9, 20, 15, 7};
    int inorder[] = {9, 3, 15, 20, 7};
    int preorderSize = sizeof(preorder) / sizeof(preorder[0]);
    int inorderSize = sizeof(inorder) / sizeof(inorder[0]);

    // 调用 buildTree 函数构建二叉树
    struct TreeNode *root = buildTree(preorder, preorderSize, inorder, inorderSize);

    // 打印构建的二叉树
    printf("Constructed binary tree: ");
    printTree(root);
    printf("\n");

    return 0;
}