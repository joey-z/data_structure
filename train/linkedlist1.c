/*************************************************************************
	> File Name: linkedlist.c
	> Author: zoe
	> Mail: 
	> Created Time: 2018年10月13日 星期六 10时12分06秒
 ************************************************************************/
//链表 看做火车
#include <stdio.h>
#include <stdlib.h>

typedef struct Node { //定义一个结构体Node 命名为Node 和*LinkedList
    int data; //链表由数据域和指针域组成
    struct Node *next; //定义Node类型的指针next,来指向下一个节点
} Node, *LinkedList;

void clear(LinkedList head) { //创建了链表之后,在程序结束之前需要释放它所占用的内存空间 
    Node *current_node = head; //定义一个Node类型的指针变量current_node,初始让它指向head 
    while (current_node != NULL) { //current_node不断指向后一个节点来遍历整个链表来释放所有结点的内存空间 直到current_node为空 即已经到最后一个结点
        //定义一个Node类型的指针变量delete_node来保存当前的结点
        Node *delete_node = current_node;
        current_node = current_node->next;//让当前结点指向他后一个结点
        free(delete_node); //最后释放delete_node指向的内存空间
    }
}

int main() {
    LinkedList linkedlist = NULL; //定义空链表 并初始指向空NULL
    clear(linkedlist); //调用clear函数
    return 0;
}

