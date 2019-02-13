/*************************************************************************
	> File Name: 15.trie.cpp
	> Author: Zoe 
	> Mail: 
	> Created Time: 2018年12月30日 星期日 20时39分01秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#define BASE_CNT 26 
#define BASE 'a' 

typedef struct Node {
    int flag;
    struct Node *next[26];
} Node;

Node *getNewNode() {
    Node *p = (Node *)malloc(sizeof(Node));
    for (int i = 0; i < BASE_CNT; i++) {
        p->next[i] = NULL;
    }
    p->flag = 0;
    return p;
}


//字典树的插入操作　不会改变根节点
void insert(Node *node, const char *str) {
    Node *p = node;
    for (int i = 0; str[i]; i++) {
        if (p->next[str[i] - BASE] == NULL) p->next[str[i] - BASE] = getNewNode();
        p = p->next[str[i] - BASE];
    }
    p->flag = 1;
    return ;
}

int search(Node *node, const char *str) {
    Node *p = node;
    for (int i = 0; str[i]; i++) {
        if (p->next[str[i] - BASE] == NULL) {
            return 0;
        }
        p = p->next[str[i] - BASE];
    }
    return p->flag;
}

void clear(Node *node) {
    if (node == NULL) return ;
    for (int i = 0; i < BASE_CNT; i++) {
        clear(node->next[i]);
    }
    free(node);
    return ;
}

int main() {
    Node *root = getNewNode();
    char str[100];
    int op;
    while (scanf("%d%s", &op, &str) != EOF) {
        switch (op) {
            
        }
    }
    return 0;
}
