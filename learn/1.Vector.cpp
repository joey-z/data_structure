/*************************************************************************
	> File Name: 1.Vector.cpp
	> Author: zoe
	> Mail: 
	> Created Time: 2018年10月11日 星期四 18时56分54秒
 ************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define DEFAULT_ARG(a, b) ((#a)[0] ? a + 0 : b) // + 0 代码解析不会出错
#define init(a) __init(DEFAULT_ARG(a, 10))

//结构定义
typedef struct vector {
    int *data;
    int size, length;
} Vector;
vector *__init(int n) {
    vector *p = (vector *)malloc(sizeof(vector)); //声明
    p->data = (int *)malloc(sizeof(int) * n);
    p->size = n;
    p->length = 0;
    return p;
}

//扩容 realloc 重新申请内存
int expand(Vector *v) {
    int *p  = (int *)realloc(v->data, sizeof(int) * 2 * v->size);
    //第二个参数放新申请的空间
    if (p == NULL) return 0;
    v->data = p;
    v->size *= 2;
    return 1;
    printf("[%p] expand vector success, the new size : %d\n", v->data, v->size);
}

//插入操作
int insert(Vector *v, int value, int ind) {
    //插入位置不合法 两种情况 
    if (v->length == v->size) {
        //顺序表扩容
        if (expand(v) == 0) {
            return 0;
        }
    }
    if (ind < 0 || ind > v->length) return 0;
    //移动数据
    for (int i = v->length - 1; i >= ind; --i) {
        v->data[i + 1] = v->data[i];
    }
    v->data[ind] = value;
    v->length += 1;
    return 1;
}

//删除操作 delet是c++关键字 所以不用
int erase(Vector *v, int ind) {
    if (v->length <= 0) return 0;
    if (ind < 0 || ind >= v->length) return 0;
    for (int i = ind + 1; i < v->length; i++) {
        v->data[i - 1] = v->data[i];
    }
    
    v->length -= 1;
    return 1;
}

//回收
void clear(Vector *v) {
    if (v == NULL) return ;
    free(v->data);
    free(v);
    return ;
}

void output(Vector *v) {
    printf("Vector = [");
    for (int i = 0; i < v->length; i++) {
        printf("%d ", v->data[i]);
    }
    printf("]\n");
}

int main() {
    Vector *v = init();
    #define MAX_OP 40
    for (int t = 0; t < MAX_OP; t++) {
        int op = rand() % 5, ind, value;
        switch(op) {
            case 4 :
            case 2 :
            case 3 :
            case 0 : {
                ind = rand() % (v->length + 3) - 1;
                value = rand() % 100;
                printf("[%d]insert(%d, %d) to vector\n", insert(v, value, ind), value, ind);
                output(v); //
            } break;
            case 1 : {
                ind = rand() % (v->length + 3) - 1;
                printf("[%d] erase(%d) from vector\n", erase(v, ind), ind);
            }break;
        }
    }
    clear(v);
    return 0;
}
