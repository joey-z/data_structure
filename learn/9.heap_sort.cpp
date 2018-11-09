/*************************************************************************
	> File Name: 9.heap_sort.cpp
	> Author: Zoe 
	> Mail: 
	> Created Time: 2018年10月30日 星期二 20时27分47秒
 ************************************************************************/
//堆排序
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//swap函数的宏定义
#define swap(a, b) { \
    __typeof(a) __temp = a; a = b; b = __temp;\
}

void heap_sort(int *arr, int n) {
    //对具有N个元素的数组进行排序 先建堆 再排序
    int *p = arr - 1; //假设从1开始编号 
    //指针P指向数组的前一位 这样p1指向的就是arr[0] 对下标进行重新映射
    //原来是从0到n-1 现在是从1到n 访问P数组时下标就是从1到n了 
    for (int i = 2; i <= n; i++) { //从第二个元素开始
        //新进入堆里的元素是pi
        int ind = i;
        while (ind > 1) {//插入调整
            if (p[ind] <= p[ind >> 1]) break;
            swap(p[ind], p[ind >> 1]);
            ind >>= 1;
        }
    }
    for (int i = n; i > 1; i--) {
        swap(p[i], p[1]);
        int ind = 1;
        while ((ind << 1) <= i - 1) {
            int temp = ind ;
            if (p[temp] < p[ind << 1]) temp = ind << 1;
            if ((ind << 1 | 1) <= i - 1 && p[temp] < p[ind << 1 | 1]) temp = ind << 1 | 1;
            if (temp == ind) break;
            swap(p[temp], p[ind]);
            ind = temp;
        } 
    }
    return ;
}
void output(int *num, int n) {
    printf("arr = [");
    for (int i = 0; i < n; i++) {
        printf(" %d", num[i]);
        i == n - 1 == printf(",");
    }
    printf("]\n");
    return ;
}

int main() {
    srand(time(0));
    #define MAX_N 20 
    int arr[MAX_N];
    for (int i = 0; i < MAX_N; i++) arr[i] = rand() % 100;
    output(arr, MAX_N);
    heap_sort(arr, MAX_N);
    output(arr, MAX_N);
    return 0;
}

