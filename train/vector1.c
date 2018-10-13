/*************************************************************************
	> File Name: vector1.c
	> Author: zoe
	> Mail: 
	> Created Time: 2018年10月11日 星期四 22时33分24秒
 ************************************************************************/
//顺序表的构造

#include <stdio.h>
#include <stdlib.h>

typedef struct Vector {
    int size, length;
    int *data; //定义一个int型的指针用来指向存储元素的数组
} Vector;

void init(Vector *vector, int size) {
    vector->size = size; //把size的值设为顺序表的容量
    vector->length = 0; //把当前顺序表的元素个数设为0
    //借助malloc让data指向一段连续size个int空间
    vector->data = (int *)malloc(sizeof(int) * size);
}

void clear(Vector *vector) {
    //函数结束前要释放占用的空间否则会发生内存泄露
    free(vector->data); //clear函数中使用free释放vector->data
    free(vector);       //以及指针vector指向的内存空间
}

int main() {
    Vector *a = (Vector *)malloc(sizeof(Vector));
    init(a, 100);
    clear(a);
    
    return 0;
}
