/*************************************************************************
	> File Name: 2.LinkList.cpp
	> Author: Zoe 
	> Mail: 
	> Created Time: 2018年10月30日 星期二 16时07分55秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>

typedef struct LinkNode {
    int data;
    struct LinkNode *next;
} *LinkList,LinkNode; 

LinkNode *getNewNode(int value) {
    LinkNode *p = (LinkNode *)malloc(sizeof(LinkNode));
    p->data = value;
    p->next = NULL;
    return p;
}

//插入
LinkNode *insert(LinkList l, int value, int ind) {
    LinkNode ret *p = &ret;
    ret.next = l; //虚拟节点指向原来的链表
    while (ind --) {
        p = p->next;
        if (p == NULL) return l;
    }
    //此时p已经指向带插入位置的前一个节点
    LinkNode *new_node = getNewNode(value);
    new_node->next = p->next;
    p->next = new_node;
    return ret.next;
}

//删除 (也有可能改变头节点 也要找到待删除位置的前一个节点)
//加虚拟节点就是为了方便找到待操作节点的前一个节点
LinkNode *erase(LinkList l, int ind) {
    //删除操作可能会改变投递至，所以返回一个新的链表头部的地址
    LinkNode ret, *p = &ret;
    ret.next = l;
    while (ind--) {
        p = p->next;
        if (p == NULL) return l;
    } 
    if (p->next == NULL) return l;//待删除节点为空
    LinkNode *q = p->next;
    p->next = p->next->next;
    free(q);
    return ret.next;
}

void clear(LinkList head) { //这里为甚么不写*
    if (head == NULL) return ;
    LinkNode *p = head, *q;
    while (p) {
        q = p;
        p = p->next;
        free(q);
    }
    return ;
}

int main() {
    LinkList l;
    #define MAX_op 20
    int length = 0;
    for (int i = 0; i < MAX_op; i++) {
        //75%的插入概率
        int op = rand() % 4, value, ind;
        swutch (op) {
            case 0:
            case 1:
            case 2: {
                ind = rand() % (length + 1);
                value = rand() % 100;//随机一个100以内的值
                printf()
            } break;
            case 3: {

            } break;
        }
    }
    clear(l);
    return 0;
}

