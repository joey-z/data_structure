/*************************************************************************
	> File Name: linkedlist2.c
	> Author: zoe
	> Mail: 
	> Created Time: 2018年10月13日 星期六 11时06分28秒
 ************************************************************************/
//链表 看做火车 
#include <stdio.h>
#include <stdlib.h>

typedef struct Node { //定义一个结构体Node 命名为Node 和*LinkedList
    int data; //链表由数据域和指针域组成
    struct Node *next; //定义Node类型的指针next,来指向下一个节点
} Node, *LinkedList;

// 请在下面实现插入函数 insert
LinkedList insert(LinkedList head, Node *node, int index) {
    if (head == NULL) { //头指针为空指针 就让node成为头指针
        if (index != 0) { 
            return head; //index不为0 直接return head结束
        } //如果头指针为空指针则当且仅当index为0的时候 才能执行插入操作
        //否则这是一个非法的操作 结束函数
        head = node; //node赋值给head 让node成为头指针
        return head;
    }
    if (index == 0) { //如果插入结点后的位置是链表首位 也就是index == 0的时候 
        node->next = head; //只要把node插入到head前面即可 让node指针指向当前表头
		//完成node插入
        head = node; //然后让node成为头结点head 完成表头的更新
        return head;
    }
    Node *current_node = head; //Node类型的指针用来遍历链表 初始指向头指针
    int count = 0; //统计遍历了多少个结点
    //用while循环找目标位置的前一个位置
    //current_node下一个结点不能为空 如果为空表示已经到表尾了
    //count要小于index - 1 index有可能远大于链表的长度 这样就不符合条件了
    while (current_node->next != NULL && count < index - 1) {
		current_node = current_node->next;
        count++;
    }
    //此时我们找到了目标位置的前一位 可以开始插入新结点
    if (count == index - 1) {
        node->next = current_node->next; //新结点node的指针指向目标位置的后一个位置
        								//也就是current_node的下一个结点
        current_node->next = node; //目标位置的前一个结点指向新结点 current_node指向新结点
    }
    return head;
}
// 请在下面实现输出函数 output
void output(LinkedList head) {
    if (head == NULL) { //判断链表是否为空 如果链表为空 也就是head为空 退出函数
        return ;
    }
    Node *current_node = head; //定义一个Node类型的指针node 先指向头指针
    while (current_node != NULL) { //循环遍历链表
        //满足条件说明是链表里的元素 输出结点的数据域 
        printf("%d ", current_node->data);
        current_node = current_node->next; //current_node指针指向下一个结点 
    } 
    printf("\n");
}

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
    LinkedList linkedlist = NULL;//定义空链表 并初始指向空
	
     //链表 主函数里调用插入函数
    for (int i = 1; i <= 10; i++) {
        Node *node = (Node *)malloc(sizeof(Node)); //定义一个Node类型的指针变量node
                                       //申请一个Node大小的内存单元
        node->data = i; //node数据域设置为i
        node->next = NULL; //next的指针指向空 完成初始化
        linkedlist = insert(linkedlist, node, i - 1); //每个结点都插入到链表的最后
    }
    //主函数调用输出函数 输出刚刚创建的链表linkedlist
    output(linkedlist);
    clear(linkedlist); //调用clear函数
    return 0;
}
