/*************************************************************************
	> File Name: 1stack.c
	> Author: zoe
	> Mail: 
	> Created Time: 2018年10月20日 星期六 00时09分04秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>

// 请在下面定义结构体栈 Stack
typedef struct Stack {
    int *elements; //int型指针变量来存储栈的数据
    //定义两个int型变量 表示栈里最多可以有max_size个元素 和 栈顶元素位置
    int max_size, top_index;
} Stack;

// 请在下面实现初始化函数 init
void init(Stack *s, int length_input) {//指针类型s int类型length_input代表栈的最多元素个数
    //给element数组分配内存
    s->elements = (int *)malloc(sizeof(int) * length_input);
    //将length_input值赋给max_size 
    s->max_size = length_input;
    //top_index 初始化为-1 ???
    s->top_index = -1;
}

// 请在下面实现 clear 函数
void clear(Stack *s) {
    free(s->elements);
    free(s);
}

int main() {
    //主函数里创建栈
    int n; //表示栈设定的最多元素个数
    scanf("%d", &n);
    Stack *stack = (Stack *)malloc(sizeof(Stack));//分配Stack类型大小的内存
    init(stack, n);
    clear(stack);
    return 0;
