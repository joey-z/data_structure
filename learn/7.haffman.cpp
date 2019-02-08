/*************************************************************************
	> File Name: 7.haffman.cpp
	> Author: Zoe 
	> Mail: 
	> Created Time: 2018年10月28日 星期日 20时02分36秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <string.h>

//freq 节点的总次数

typedef struct Node {
    int key, freq;
    struct Node *lchild, *rchild;
} Node;

Node *getNewNode(int key, int freq) {
    Node *p = (Node *)malloc(sizeof(Node));
    p->key = key;
    p->freq = freq;
    p->lchild = p->rchild = NULL;
    return p;
}

void clear(Node *root) {
    if (root == NULL) return ;
    clear(root->lchild);
    clear(root->rchild);
    free(root);
    return ;
}

//交换值
void swap_node(Node **p, Node **q) {
    Node *temp = *p;
    *p = *q;
    *q = temp;    
    return ;
}

Node *build_haffman(Node **arr, int n) {
    //合并n-1次 将频次最小的放入末尾
    Node INIT_NODE = {0, INT32_MAX, NULL, NULL}; 
    //建立一个新的节点key, freq, 左右孩子
    for (int i = 1; i < n - 1; i++) {
        for (int j = 0; j < n - i - 2; j++) {
            if (arr[i]->freq < arr[n - i - 1]->freq) {
                swap_node(arr + j, arr + n - i - 1);
            }   
            if (arr[j]->freq < arr[n - i - 2]->freq) {
                swap_node(arr + j, arr + n - i - 2);
            }
            if (arr[n - i - 1]->freq > arr[n - i - 2]->freq) {
                swap_node(arr + n - i - 1, arr + n - i - 2);
            }
        }
        printf("first:->%d, second:->%d\n", arr[n - i - 1]->freq, arr[n - i - 2]->freq);
        //已经找到最小节点
        Node *temp = getNewNode(0, arr[n - i - 1]->freq + arr[n - i - 2]->freq);
        temp->lchild = arr[n - i - 1];
        temp->rchild = arr[n - i - 2];
        arr[n - i - 2] = temp;
    }
    return arr[0];
}
//提取编码
void extract_code(Node *root, char (*code)[20], int k, char *buffer) {
    buffer[k] = 0; //暂存编码信息的字符串
    if (root->key) {
        strcpy(code[root->key], buffer);
        return ;
    }
    buffer[k] = '0';
    extract_code(root->lchild, code, k + 1, buffer);
    buffer[k] = '1';
    extract_code(root->rchild, code, k + 1, buffer);
    return ; //
}

int main() {
    int n;
    Node **arr = (Node **)malloc(sizeof(Node *) * n);
    Node *root;
    scanf("%d", &n);
    //初始化数据 
    for (int i = 0; i < n; i++) {
        char key[10]; //方便处理
        int freq;
        scanf("%s%d", key, &freq);
        arr[i] = getNewNode(key[0], freq);
    }
    root = build_haffman(arr, n);
    char code[256][20] = {0}, buffer[20]; //编码256位 最长不超过20
    //要传递层号进去，第i层编码对应原字符编码的第i位
    //提取编码
    extract_code(root, code, 0, buffer);
    for (int i = 0; i < 256; i++) {
        if (code[i][0] == 0) continue;
        printf("%c : %s\n", i, code[i]);
    }
    return 0;
}
