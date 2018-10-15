/*************************************************************************
	> File Name: vector3.c
	> Author: zoe
	> Mail: 
	> Created Time: 2018年10月13日 星期六 10时01分27秒
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
    }
    for (int i = vector->length; i > loc; i--) {
        vector->data[i] = vector->data[i - 1];
    }
    vector->data[loc] = num;
    vector->length++;
    printf("success\n");
    return OK;    	
}

int search(Vector *vector, int value) {
	for (int i = 0; i < vector->length; i++) {
        if (vector->data[i] == value) {
            printf("success\n");
            return OK;
        }
    }
    printf("failed\n");
    return ERROR;
}

int delete_node(Vector *vector, int index) {
	if (index < 0 || index >= vector->length) {
        printf("failed\n");
        return ERROR;
    }
	for (int i = index + 1; i < vector->length; i++) {
        vector->data[i - 1] = vector->data[i];
    }
    vector->length--;
    printf("success\n");
    return OK;
}

void print(Vector *vector) {
	for (int i = 0; i < vector->length; i++) {
        if (i > 0) {
			printf(" ");
        }
        printf("%d", vector->data[i]);
    }
    printf("\n");
}

void clear(Vector *vector) {
	free(vector->data);
    free(vector);
}

int main() {
    Vector *a = (Vector *)malloc(sizeof(Vector));
    init(a, 20);
	int m, t, j, k;
    scanf("%d", &m);
    for (int i = 0; i < m; i++) {
    	scanf("%d", &t);
        if (t == 1) {
            scanf("%d %d", &j, &k);
            insert(a, j, k);
            j = 0, k = 0;
        }
        if (t == 2) {
            scanf("%d", &j);
            delete_node(a, j);
            j = 0;
        }
        if (t == 3) {
            scanf("%d", &j);
            search(a, j);
            j = 0;
        }
        if (t == 4) {
            print(a);
        }
    }
    free(a);
    return 0;
}

