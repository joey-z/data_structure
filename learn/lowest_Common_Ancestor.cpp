/*************************************************************************
	> File Name: test.cpp
	> Author: zoe
	> Mail: 
	> Created Time: 2018年10月23日 星期二 19时35分46秒
 ************************************************************************/
//最近公共祖先
//如果两点在同一深度 一起往上走 每走到一个点就判断你是否相交
//(类似于交叉链表找相同值)
//如果深度不相同 将较深的向上提 直到两个对齐变同一深度
//树的0节点是不用的 从1开始
//异或运算 已知两个就能还原第三个
#include <stdio.h>
#include <stdlib.h>
#define MAX_N 1000
#define MAX_K 20
//2^k == 
struct Edge {
    //边的结构 假设树形结构的边是双向的
    int v, n;//边 点??
} g[MAX_N << 1];

int head[MAX_N + 5] = {0}, cnt = 0;
inline void add(int a, int b) {
    g[++cnt].v = b;
    g[cnt].n = head[a];
    head[a] = cnt;
    return ;
}

//gas[i][j] i 点往上走2的j次方步 所能到达的祖先节点编号
int gas[MAX_N][MAX_K] = {0}, dep[MAX_N] = {0};

void dfs(int u, int father) {
    //伸缩式
    gas[u][0] = father; //u节点上往上走一步
    dep[u] = dep[father] + 1;
    for (int i = 1; i < MAX_K; i++) {
        //关键
        gas[u][i] = gas[gas[u][i - 1]][i - 1];
    }
    //遍历u的所有出边
    for (int i = head[u]; i; i = g[i].n) {
        if (g[i].v == father) continue;
        dfs(g[i].v, u);
    }
}

int lca(int a, int b) {
    //求最近公共祖先
    if (dep[a] < dep[b]) {
        //交换a b 异或运算 让b成为较深的点
        a ^= b;
        b ^= a;
        a ^= b;
    }
    //求深度差 然后对齐
    int l = dep[b] - dep[a];
    for (int i = 0; i < MAX_K; i++) {
        if ((l & (1 << i))) b = gas[b][i]; //l & (1 << i)分次数 往上跳2^i步
    //位运算速度快 只需要处理两次 这种做法叫倍增 
    }
    //此时深度相同 对齐了之后
    if (a == b) return a;
    //当往上跳2^i步时跳到的是不同的节点才往上跳
    //(只有在公共祖先之下的节点才会不相同)
    for (int i = MAX_K - 1; i >= 0; i--) {
        //这种遍历方式 遍历二进制的每一位 例如:0101 为1才判断
        //而二进制的每一位组合在一起 可以遍历任意的层数深度
        if (gas[a][i] != gas[b][i]) a = gas[a][i], b = gas[b][i]; //这里不懂
    }
    return gas[a][0];
}
int main() {
//怎么用
    int n, a, b;
    scanf("%d", &n);
    for (int i = 1; i < n; i++) {
        int a, b;
        scanf("%d%d", &a, &b);
        add(a, b);
        add(b, a);
    }
    //此时我们已经有一棵树了 确定根节点 
    //选取任何一个节点作为根节点 不会影响相对路径??
    dfs(1, 0); //1号节点的父节点为0号节点  0是不用的节点
    while (scanf("%d%d", &a, &b) != EOF) {
        printf("lca(%d, %d) = %d, a -> b = %d\n", a, b, lca(a, b), dep[a] + dep[b] - 2 * dep[lca(a, b)]);
    }
    return 0;
}
