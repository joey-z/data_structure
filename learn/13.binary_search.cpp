/*************************************************************************
	> File Name: 13.binary_search.cpp
	> Author: Zoe 
	> Mail: 
	> Created Time: 2018年11月06日 星期二 19时38分35秒
 ************************************************************************/

#include <stdio.h>
#define P(func) {\
    printf("%s = %d\n", #func, func);\
}


//通常情况下 1 2 3 4 5 
int binary_search1(int *num, int n, int x) {
    int head = 0, tail = n, mid;
    while (head <= tail) { //找位置 不是等于某个值的元素
        mid = (head + tail) >> 1;
        if (num[mid] == x) return mid;
        if (num[mid] > x) tail = mid - 1;
        else head = mid + 1;
    }
    return -1;
}

//1111100000
int binary_search2(int *num, int n) {
    int head = -1, tail = n, mid;
    while (head < tail) {//注意代码的不同   找位置 
        //printf("head : %d, tail : %d, mid = %d\n", head, tail, mid);
        mid  = (head + tail) >> 1;
        if (num[mid] == 1) head = mid;
        else tail = mid - 1;
    }
    return head;
}

//00000111111
int binary_search3(int *num, int n) {
    int head = 0, tail = n, mid;
    while (head < tail) {
        mid = (head + tail) >> 1;
        if (num[mid] == 1) tail = mid;
        else head = mid + 1;
    }
    return head == n ? -1 : head;
}
int main() {
    int arr1[10] = {1, 3, 5, 7, 11, 13, 17, 19, 23,29};
    int arr2[10] = {1, 1, 1, 1, 0, 0, 0, 0, 0, 0};
    int arr3[10] = {0, 0, 0, 0, 1, 1, 1, 1, 1, 1};
    binary_search1(arr1, 10, 17);
    binary_search2(arr1, 10);
    binary_search3(arr3, 10);
    return 0;
}


