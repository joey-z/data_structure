/*************************************************************************
	> File Name: binary_tree.cpp
	> Author: zoe
	> Mail: 
	> Created Time: 2018年10月23日 星期二 19时17分38秒
 ************************************************************************/
//二叉树的简单操作 自己定义的二叉树 
//1 2 6 12 7 3 5 10 11 9前序遍历 
//6 12 2 7 1 10 5 11 3 9中序遍历 
//12 6 7 2 10 11 5 9 3 1后序遍历
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *lchild, *rchild;
} Node;

Node *init(int data) {
    Node *p = (Node *)malloc(sizeof(Node));
    p->data = data;
    p->lchild = p->rchild = NULL;
    return p;
}

Node *build() {
    Node *root = init(1);
    root->lchild = init(2);
    root->rchild = init(3);
    root->lchild->lchild = init(6);
    root->lchild->rchild = init(7);
    root->lchild->lchild->rchild = init(12);
    root->rchild->lchild = init(5);
    root->rchild->rchild = init(9);
    root->rchild->lchild->lchild = init(10);
    root->lchild->lchild->rchild = init(11);
    return root;
}

void clear(Node *node) {
    if (node == NULL) return ;
    clear(node->lchild);
    clear(node->rchild);
    free(node);
    return ;
}

int height_tree(Node *root) {
    if (root == NULL) return 0;
    int lh = height_tree(root->lchild), rh = height_tree(root->rchild);
    return (lh > rh ? lh : rh) + 1;
}

void preorder(Node *root) {
    //前序遍历
    if (root == NULL) return ;
    printf("%d ", root->data);
    preorder(root->lchild);
    preorder(root->rchild);
    return ;
}

//中序遍历
void inorder(Node *root) {
    if (root == NULL) return ;
    inorder(root->lchild);
    printf("%d ", root->data);
    inorder(root->rchild);
    return ;
}

void postorder(Node *root) {
    //后序遍历
    if (root == NULL) return ;
    postorder(root->lchild);
    postorder(root->rchild);
    printf("%d ", root->data);
    return ;
}

int main() {
    Node *root = build();
    printf("height_tree(root) = %d\n", height_tree(root));
    preorder(root);  printf("\n");
    inorder(root);  printf("\n");
    postorder(root);  printf("\n");
    return 0;
}

