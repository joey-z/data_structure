/*************************************************************************
	> File Name: 1queue.c
	> Author: zoe
	> Mail: 
	> Created Time: 2018年10月21日 星期日 22时37分11秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
//定义一个空的结构体作为队列的数据结构类型
typedef struct Queue {
    int *data; //保存队列中每个元素的编号
    //头 尾 长度 队列中的所有元素都是介于head tail之间 并且连续存放的
    int head, tail, length; 
} Queue;

// 请在下面实现队列 Queu

// 请在下面实现初始化函数 init
void init(Queue *q, int length) {
    //首先要给q->data数组分配length个int类型的内存 
    q->data =(int *)malloc(sizeof(int) * length);
    //然后将length的值赋给q->length
    q->length = length;
    //初始化队首和队尾标记 初始队列为空 所以将队首标记q->head设置为0
    q->head = 0;
    //再将队尾标记q->tail设置为-1
	q->tail = -1;
}

// 请在下面实现 clear 函数
void clear(Queue *q) {
    free(q->data); //要释放q->data 和 q指向的内存空间
	free(q);
}

int main() {
    //主函数里定义一个Queue的指针 并动态申请一个Queue大小的内存 
    Queue *q = (Queue *)malloc(sizeof(Queue));
    //调用初始化函数完成初始化
    init(q, 150);
    //调用clear函数
    clear(q);
    return 0;
}
