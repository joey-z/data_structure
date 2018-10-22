/*************************************************************************
	> File Name: 3.queue.cpp
	> Author: zoe
	> Mail: 
	> Created Time: 2018年10月21日 星期日 18时14分35秒
 ************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//结构定义
typedef struct Queue {
    int *data;
    int head, tail, length;
} Queue;

Queue *init(int n) {
    Queue *q = (Queue *)malloc(sizeof(Queue));
    q->data = (int *)malloc(sizeof(int) * n);
    q->length = n;
    //q->cnt = 0;
    q->data = (int *)malloc(sizeof(int) * (n + 1));
    q->head = 0; 
    q->tail = -1; //入队列操作 尾指针向后移动一位 所以初始化为-1
    return q;
}
//入队
int push(Queue *q, int value) {
    if (q->tail + 1 == q->length) return 0;
    q->tail += 1;
    q->data[q->tail] = value;
    return 1;
}

int empty(Queue *q) {
    return q->head > q->tail;
}
//出队
void pop(Queue *q) {
    if (empty(q)) return ;
    q->head += 1;
    return ;
}
//查看队列头部元素
int front(Queue *q) {
    if (empty(q)) return 0;
    return q->data[q->head];
}

void clear(Queue *q) {
    if (q == NULL) return ;
    free(q->data);
    free(q);
    return ;
}

void output(Queue *q) {
    printf("Queue = [");
    for (int i = q->head; i <= q->tail; i++) {
        printf(" %d", q->data[i]);
        i == q->tail || printf(",");
    }
    printf("]\n");
    return ;
}

int main() {
    #define MAX_OP 20
    srand(time(0));
    Queue *q = init(MAX_OP);
    for (int i = 0; i < MAX_OP; i++) {
        int op = rand() % 4, value = rand() % 100;
        switch (op) {
            case 0 :
            case 1 :
            case 2 :
                push(q, value);
                printf("push %d to queue\n", value);
                output(q);
                break;
            case 3 :
                printf("pop %d from queue\n", front(q));
                pop(q);
                output(q);
                break;
        }
    }
    return 0;
}
