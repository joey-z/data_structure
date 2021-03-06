/*************************************************************************
	> File Name: 6.build_tree.cpp
	> Author: Zoe 
	> Mail: 
	> Created Time: 2018年10月28日 星期日 18时18分34秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int key;
    struct Node *lchild, *rchild;
} Node;

//碰到，切换为右子树 碰到（入栈     ）出栈 
typedef struct Stack {
    Node **data;
    int top, size;
} Stack;

Stack *initStack(int n) {
    Stack *s = (Stack *)malloc(sizeof(Stack));
    s->data = (Node **)malloc(sizeof(Node *) * n);
    s->size = n;
    s->top = -1;
    return s;
}

int empty(Stack *s) {
    return s == NULL || s->top == -1;
}

void pop(Stack *s) {
    if (empty(s)) return ;
    s->top -= 1;
    return ;
}

void push(Stack *s, Node *root) {
    if (s->top + 1 == s->size) return ;
    s->data[++(s->top)] = root;
    return ;
}

Node *top(Stack *s) {
    if (empty(s)) return NULL;
    return s->data[s->top];
}

void clearStack(Stack *s) {
    if (s == NULL) return ;
    free(s->data);
    free(s);
    return ;
}

Node *getNode(int key) {
    Node *p = (Node *)malloc(sizeof(Node));
    p->key = key;
    p->lchild = p->rchild = NULL;
    return p;
}

void clearTree(Node *root) {
    if (root == NULL) return ;
    clearTree(root->lchild);
    clearTree(root->rchild);
    free(root);
    return ;
}

//将字符串转化为二叉树 返回地址
Node *build(const char *str) {
    Node *p = NULL, *root = NULL;
    Stack *s = initStack(100); //假设节点层数不超过
    int k = 0;
    while (str[0]) {
    //根据当前位置的字符判断该做什么操作
        switch (str[0]) {
            case '(': {
                push(s, p);
                k = 0;
            } break;
            case ')': {
                pop(s);    
            } break;
            case ',': {
                k = 1;
            } break;
            case ' ': break;
            default: {
                p = getNode(str[0]);
                if (root == NULL) root = p;
                if (empty(s)) break;
                if (k == 0) top(s)->lchild = p;
                else top(s)->rchild = p;
            } break;
        }
        str++;
    }
    return root; //返回建好的二叉树
}
void output(Node *root, const char *last_output) {
    if (root == NULL) return ;
    printf("%c", root->key);
    output(root->lchild, "");
    output(root->rchild, "");
    printf("%s", last_output);
    return ;
}

int main() {
    char str[100];
    Node *root;
    while (scanf("%[^\n]s", str) != EOF) {
        getchar(); //吞掉行尾回车
        output(root = build(str), "\n");
        //printf("\n");
        clearTree(root);
    }
    return 0;
}
