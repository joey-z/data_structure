/*************************************************************************
	> File Name: 11.stable_sort.cpp
	> Author: Zoe 
	> Mail: 
	> Created Time: 2018年11月04日 星期日 19时45分54秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define swap(a, b) { \
    a ^= b; b ^= a; a ^= b; \
}

//变参宏
#define TEST(arr, n, func, args...) {\
    int *num= (int *)malloc(sizeof(int) * n);\
    memcpy(num, arr, sizeof(int) * n);\
    output(num, n);\
    printf("%s = ", #func);\
    func(args);\
    free(num);\
    output(num, n);\
}

void insert_sort(int *num, int n) {
    for (int i = 1; i < n; i++) {
        for (int j = i; j > 0 && num[j] < num[j - 1]; --j) {
            swap(num[j], num[j - 1]);
        }
    }
    return ;
}

void bubble_sort(int *num, int n) {
    int times = 1;
    for  (int i = 1; i < n & times; i++) {//加入了优化
        times = 0;
        for (int j = 0; j < n; j++) {
            if (num[j] <=  num[j + 1]) continue;  
            swap(num[j], num[j + 1]);
            times++;
            
        }
    }
    return ;
}

void merge_sort(int *num, int l, int r) {
    if (r - l <= 1) {
        if (r - l == 1 && num[l] > num[r]) {
            swap(num[l], num[r]);
        }
    }
    int mid = (l + r) >> 1;
    merge_sort(num, l, mid);
    merge_sort(num, mid + 1, r);
    //归并过程需要一段新的存储区
    int *temp = (int *)malloc(sizeof(int) * (r - l + 1));
    int p1 = l, p2 = mid + 1, k = 0;
    //第一个数组的头部元素　第二个数组的头部元素　
    //临时存储区的第一个位置（当前可以存储的位置）
    
    while (p1 <= mid || p2 <= r) {//第一个数组有元素或者第二个数组有元素
    //继续进行归并操作
    //将第一个数组的元素放入临时存储区的条件：
    //第二个数组为空或者第一个数组不为空并且第一个数组的当前元素小于等于第二个数组中的当前元素
        if (p2 > r || p1 <= mid && num[p1] <= num[p2]) {
            temp[k++] = num[p1++];
        } else {
            temp[k++] = num[p2++];//将第二个数组的元素放入临时存储区
        }
    }
    //将临时存储区的数据拷贝到num数组中
    memcpy(num + l, temp, sizeof(int) * (r - l + 1));
    free(temp);
    return ;
}

void randint(int *num, int n) {
    while (n--) num[n] = rand() % 100;
    return ;
}

void output(int *num, int n) {
    printf("[");
    for (int i = 0; i < n; i++) {
        printf("%d", num[i]);
    }
    printf("]\n");
    return ;
}

int main() {
    srand(time(0));
    #define MAX_OP 20
    int arr[MAX_OP];

    randint(arr, MAX_OP);
    TEST(arr, MAX_OP, insert_sort, num, MAX_OP);
    TEST(arr, MAX_OP, bubble_sort, num, MAX_OP);
    TEST(arr, MAX_OP, merge_sort, num, 0, MAX_OP - 1);
    return 0;
}

