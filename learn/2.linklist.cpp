/*************************************************************************
	> File Name: 2.linklist.cpp
	> Author: zoe
	> Mail: 
	> Created Time: 2018年10月11日 星期四 20时23分25秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct LinkNode { //链表的结构定义
    int data;
    struct LinkNode *next;
} LinkNode;

typedef struct LinkList {
    LinkNode head; //代替虚拟节点的作用 
    int length;
} LinkList;

LinkList *init() {
    LinkList *p = (LinkList *)malloc(sizeof(LinkList));
    p->head.next = NULL;
    p->length = 0;
    return p;
}

LinkNode *getNewNode(int value) {
    LinkNode *p = (LinkNode *)malloc(sizeof(LinkNode));
    p->data = value;
    p->next = NULL;
    return p;
}

//向链表的某个位置添加一个
void insert(LinkList *l, int value, int ind) {
    //虚拟节点 
    LinkNode *p = &(l->head);
    while (ind--) {
        p = p->next;
        if (p == NULL) return ;
    }
    LinkNode *new_node = getNewNode(value);
    new_node->next = p->next;
    p->next = new_node;
    l->length += 1;
    return ;
}//以上

//链表删除 找到待删除位置的前一个节点 //也引入虚拟节点
void erase(LinkList *l, int ind) {
    LinkNode *p = &(l->head);
    while (ind--) {
        p = p->next;
        if (p == NULL) return ;
    }
    if (p->next == NULL) return ;
    LinkNode *q = p->next;
    p->next = p->next->next;
    free(q);
    l->length -= 1;
    return ;
}

void clear(LinkList *l) {
    if (l->head.next == NULL) return ;
    LinkNode *p = l->head.next, *q;
    while (p) {
        q = p;
        p = p->next;
        free(q);
    }
    free(l);
    return ;
}

void output(LinkList *l) {
    printf("[%d] ", l->length);
    LinkNode *p = l->head.next;
    while (p != NULL) {
        printf("%d->", p->data);
        p = p->next;
    }
    printf("NULL\n");
    return ;
}
int main() {
    srand(time(0));
    LinkList *l = init();
    #define MAX_OP 20
    for (int i = 0; i < MAX_OP; i++) {
        int op = rand() % 4, value, ind;
        switch (op) {
            case 0 :
            case 1 :
            case 2 : {
                ind = rand() % (l->length + 1);
                value = rand() % 100;
                printf("insert(%d, %d) to LinkList\n", value, ind);
                insert(l, value, ind);
                output(l);
            } break;
            case 3 : {
                if (l->length == 0) break;
                ind  = rand() % l->length;
                printf("erase(%d) from LinkList\n", ind);
                erase(l, ind);
                output(l);
            } break;
        }
    }
    clear(l);
    return 0;
}

