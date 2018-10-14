/*************************************************************************
	> File Name: vector2.c
	> Author: zoe
	> Mail: 
	> Created Time: 2018年10月12日 星期五 14时54分49秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>

#define ERROR 0
#define OK 1

typedef struct Vector {
	int size, length;
    int *data;
} Vector;

void init(Vector *vector, int size) {
	vector->size = size;
    vector->length = 0;
    vector->data = (int *)malloc(sizeof(int) * size);
}

void expand(Vector *vector) {
	int *temp_data = vector->data;
    vector->size = vector->size * 2;
    vector->data = (int *)malloc(sizeof(int) * vector->size);
    for (int i = 0; i < vector->length; i++) {
        vector->data[i] = temp_data[i];
    }
    free(temp_data);
}

int insert(Vector *vector, int loc, int num) {
	if (loc < 0 || loc > vector->length) {
        printf("failed\n");
        return ERROR;
    }
    if (vector->length >= vector->size) {
        expand(vector);
        printf("expand\n");
    }
    for (int i = vector->length; i > loc; i--) {
        vector->data[i] = vector->data[i - 1];
    }
    vector->data[loc] = num;
    vector->length++;
    printf("success\n");
    return OK;
}


void clear(Vector *vector) {
	free(vector->data);
    free(vector);
}

int main() {
    Vector *a = (Vector *)malloc(sizeof(Vector));
    init(a, 5);
    /*int n;  这里代码会出先内存溢出
    scanf("%d", &n);
    int loc[n + 5];
    int num[n + 5];
    for (int i = 0; i < n; i++) {
        scanf("%d %d", loc[i], num[i]);
    }
    for (int i = 0; i < n; i++) {
        printf("%d %d\n", loc[i], num[i]);
        insert(a, loc[i], num[i]);
    }*/
    int n, loc, num;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &loc, &num);
        insert(a, loc, num);
    }
	free(a);
    return 0;
}
