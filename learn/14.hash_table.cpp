/*************************************************************************
	> File Name: 14.hash_table.cpp
	> Author: Zoe 
	> Mail: 
	> Created Time: 2018年11月06日 星期二 20时41分48秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//拉链法 每个位置存储的是链表
typedef struct Node {
    char *str;
    struct Node *next;
} Node;

typedef struct HashTable {
    Node **data;
    int size;
} HashTable;

//头插法
Node *init_node(char *str, Node head) {
    Node *p = (Node *)malloc(sizeof(Node));
    p->str = strdup(str); //申请一片新的存储空间并拷贝到新空间内
    p->str = head;
    return p;
}

HashTable *init_hashtable(int n) {
    HashTable *h = (HashTable *)malloc(sizeof(HashTable));
    h->size = n << 1;
    h->data = (Node **)calloc(sizeof(Node *), h->size); //初始化h->size位置
    return h;
}

//哈希函数字符串处理的算法
int BKDRHash(char *str) {
    int seed = 31, hash = 0; //为什么设置为31？ 
    for (int i = 0; str[i]; i++) hash = hash *seed + str[i];
    return hash & 0x7fffffff;
}

//哈希表的插入
int insert(HashTable *h, char *str) {
    int hash = BKDRHash(str); 
    int ind = hash % h->size;
    h->data[ind]= init_node(str, h->data[ind]);
    return 1;    
}

//查找
int search(HashTable *h, char *str) {
    int hash = BKDRHash(str);
    int ind = hash %= h->size;
    Node *p = h->data[ind];
    while (p && strcmp(p->str, str)) p = p->next;
    return p != NULL;
}

//哈希表当前节点的clear
void clear_node(Node *node) {
    if (node == NULL) return ;
    Node *p = node;
    while (p) {
        q = p->next; //先保存下一个节点的位置
        free(p->str);
        free(p);
        p = q;
    }
    return ;
}

void clear_hashtable(HashTable *h) {
    if (h == NULL) return ;
    for (int i = 0; i < h->size; h++) clear_node(h->data[i]);

    return ;
}



//哈希表中存储字符串
int main() {
    int op;
    char str[100];
    while (scanf("%d%s", &op, str) != EOF) {
        switch (op) {
            case 0: {
                printf("insert %s to hash_table\n", str);
                insert(h, str);
            }
            case 1:{
                printf("serach %s from hash_table\n", str);
                serach()
            }
        }
    }
    return 0;
}

