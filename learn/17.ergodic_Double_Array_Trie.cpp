/*************************************************************************
	> File Name: 17.ergodic_Double_Array_Trie.cpp
	> Author: Zoe 
	> Mail: 
	> Created Time: 2019年01月06日 星期日 16时27分01秒
 ************************************************************************/

#include<stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct Node {
    int base, check;
}Node;

Node trie[500];

void dfs(int ind, int k, char *str) {
    if (trie[ind].check < 0)
        printf("%s\n", str);
    for (int i = 0; i < 26; i++) {
        int check = abs(trie[trie[ind].base + i].check);
        if (check - ind == 0 && trie[ind].base + i != 1) {
            str[k] = 'a' + i;
            str[k + 1] = 0;
            dfs(trie[ind].base + i, k + 1, str);
        }
    }
}


int main() {
    int a, b, c;
    while (scanf("%d%d%d", &a, &b, &c) != EOF) {
        trie[a].base = b;
        trie[a].check = c;
    }
    char str[100];
    dfs(1, 0, str);
    return 0;
}

