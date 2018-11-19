/*************************************************************************
	> File Name: binary_search.cpp
	> Author: Zoe 
	> Mail: 
	> Created Time: 2018年11月03日 星期六 21时55分26秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

double f(double x, double a, double b, double c) {
    return a * x * x + b * x + c;
}

double three_point_search(double a, double b, double c) {
    #define EPS 1e-6
    double head = -10000, tail = 10000, m1, m2;
    if (a > 0) {
        a = -a, b = -b, c = -c;
    }
    while (fabs(tail - head) > EPS) {
        m1 = (tail - head) / 3 + head;
        m2 = (tail - head) / 3 * 2 + head;
        if (f(m1, a, b, c) < f(m2, a, b, c)) {
            head = m1;
        } else {
            tail = m2;
        }
    }
    return head;
}

int binary_search1(int *num, int n, int x) {
    int head = 0, tail = n - 1, mid;
    while (head <= tail) {
        mid = (head + tail) >> 1;
        if (num[mid] == x) return mid;
        if (num[mid] < x) {
            head = mid + 1;
        } else {
            tail = mid - 1;
        }
    }
    return -1;
}

// 11111000000
int binary_search2(int *num, int n, int x) {
    int head = -1, tail = n - 1, mid;
    while (head < tail) {
        mid = (head + tail + 1) >> 1;
        if (num[mid] == 1) {
            head = mid;
        } else {
            tail = mid - 1;
        }
    }
    return head;
}

// 000001111111
int binary_search3(int *num, int n, int x) {
    int head = 0, tail = n, mid;
    while (head < tail) {
        mid = (head + tail) >> 1;
        if (num[mid] == 1) {
            tail = mid;
        } else {
            head = mid + 1;
        }
    }
    return head == n ? -1 : head;
}

int main() {
    double a, b, c;
    while (scanf("%lf%lf%lf", &a, &b, &c) != EOF) {
        printf("%lf\n", three_point_search(a, b, c));
    }
    return 0;
}
