/*************************************************************************
	> File Name: 29.RBTree.cpp
	> Author: Zoe 
	> Mail: 
	> Created Time: 2019年02月17日 星期日 18时03分39秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define RED 0
#define BLACK 1
#define DOUBLE_BLACK 2

typedef struct RBTNode {
    int key, color; //0 red 　１ black　2 double black
    struct RBTNode *lchild, *rchild;
} RBTNode;

RBTNode *NIL;

__attribute__((constructor))
void init_NIL() {
    NIL = (RBTNode *)malloc(sizeof(RBTNode));
    NIL->key = -1;
    NIL->color = BLACK;
    NIL->rchild = NIL->rchild = NIL;
    return ;
}

RBTNode *init(int key) {
    //红黑树中没有真正的空节点
    RBTNode *p = (RBTNode *)malloc(sizeof(RBTNode));
    p->key = key;
    p->lchild = p->rchild = NIL; 
    p->color = RED;
    return p;
}

//判断是是否有红色节点
int has_red_child(RBTNode *root) {
    return  root->lchild->color == RED || root->rchild->color == RED;
}

//左旋
RBTNode *left_rotate(RBTNode *node) {
    RBTNode *temp = node->rchild;
    node->rchild = temp->lchild;
    temp->lchild = node;
    return temp;
}

//右旋
RBTNode *right_rotate(RBTNode *node) {
    RBTNode *temp = node->lchild;
    node->lchild = temp->rchild;
    temp->rchild = node;
    return temp;
}

//插入调整　有可能改变根节点的地址 root祖父节点
RBTNode *insert_maintain(RBTNode *root) {
    //站在祖父节点向下看是否失衡　当前节点下边没有红色子节点，不可能失衡
    if (!has_red_child(root)) return root;
    //左孩子和右孩子都为红色时
    if (root->lchild->color == RED && root->rchild->color == RED) {
        //左子树是红色，左子树还有红色孩子
        if (!has_red_child(root->lchild) && !has_red_child(root->rchild)) return root;
        /*root->color = RED;
        * root->lchild->color = root->rchild->color = BLACK*/
    } else if (root->lchild->color == RED && has_red_child(root->lchild)) {
        //右孩子是红色　LR
        if (root->lchild->rchild->color == RED) {
            root->lchild = left_rotate(root->lchild);
        } 
        root = right_rotate(root);
        //右子树是红色，右子树还有红色孩子
    } else if (root->rchild->color == RED && has_red_child(root->rchild)) {
        if (root->rchild->lchild->color == RED) {
            root->rchild = right_rotate(root->rchild);
        } 
        root = left_rotate(root);
    } else {
        return root;
    }
    //红色下沉
    //root->color = BLACK;
    //root->lchild->color = root->rchild->color = BLACK;
    //红色上顶
    root->color = RED;
    root->lchild->color = root->rchild->color = BLACK;
    return root;
}

RBTNode *__insert(RBTNode *root, int key) {
    if (root == NIL) return init(key);
    if (root->key == key) return root;
    if (root->key > key) {
        root->lchild = __insert(root->lchild, key);
    } else {
        root->rchild = __insert(root->rchild, key);
    }
    return insert_maintain(root);
}

//没有办法保证根节点一定是黑色
RBTNode *insert(RBTNode *root, int key) {
    root = __insert(root, key);
    root->color = BLACK;
    return root;
}

//找到前驱
RBTNode *predecessor(RBTNode *root) {
    RBTNode *temp = root->lchild;
    while (temp->rchild != NIL) temp = temp->rchild;
    return temp;
}

//删除调整
RBTNode *erase_maintain(RBTNode *root) {
    //首选判断root的子孩子是否有双重黑
    if (root->lchild->color != DOUBLE_BLACK && root->rchild->color != DOUBLE_BLACK) return root;
    //情况一：当前节点是双重黑，他的兄弟节点是黑色，并且它的兄弟节点的子节点是黑色节点
     #define UNBALANCE(a, b) (root->a->color == DOUBLE_BLACK && !has_red_child(root->b) && root->b->color == BLACK)
    if(UNBALANCE(lchild, rchild) || UNBALANCE(rchild, lchild)) {
        root->color += 1;
        root->lchild->color -= 1;
        root->rchild->color -= 1;
        return root;
    }
    #undef UNBALANCE

    if (root->lchild->color == DOUBLE_BLACK) {
        //双重黑在左，兄弟节点（右孩子）是红色
        if (root->rchild->color == RED) {
            root = left_rotate(root);
            root->color = BLACK;
            root->lchild->color = RED;
            root->lchild = erase_maintain(root->lchild);
            return root;
        }
        //去掉双重黑　（早晚都要去掉，就直接去掉了）
        root->lchild->color = BLACK;//去掉双重黑
        //右子树有红色孩子　判断是左孩子还是右孩子
//情况二：父节点的右孩子的右孩子是黑色节点（兄弟节点的右孩子是黑色节点）
        if (root->rchild->rchild->color != RED) {
            root->rchild = right_rotate(root->rchild);
            root->rchild->color = BLACK;
            root->rchild->rchild->color = RED;
        }
        //情况三
        root = left_rotate(root);
        root->color = root->lchild->color;
        root->lchild->color = root->rchild->color = BLACK;
    } else {
        //双重黑在右　兄弟节点（左孩子）是红色
        if (root->lchild->color == RED) {
            root = right_rotate(root);
            root->color = BLACK;
            root->rchild->color = RED;
            root->rchild =  erase_maintain(root->rchild);
            return root;
        }
        //去掉双重黑　
        root->rchild->color = BLACK;
        //右子树有红色孩子　判断是左孩子还是右孩子
        //情况二
        if (root->lchild->lchild->color != RED) {
            root->lchild = left_rotate(root->lchild);
            root->lchild->color = BLACK;
            root->lchild->lchild->color = RED;
        }
        //情况三　
        root = right_rotate(root);
        root->color = root->rchild->color; 
        root->lchild->color = root->rchild->color = BLACK;        
    } 
    return root;
}

//封装，根节点容易变成双重黑
RBTNode *__erase(RBTNode *root, int key) {
    if (root == NIL) return NIL;
    if (root->key > key) {
        root->lchild = __erase(root->lchild, key);
    } else if (root->key < key) {
        root->rchild = __erase(root->rchild, key);
    //判断度
    } else {
        //同时处理了度为０和度为１的情况(有改动)
        if (root->lchild == NIL || root->rchild == NIL) {
            RBTNode *temp = (root->lchild == NIL ? root->rchild : root->lchild);
            temp->color += root->color;
            free(root);
            return temp;
        } else {
            //度为２
            RBTNode *temp = predecessor(root);
            root->key = temp->key;
            root->lchild = __erase(root->lchild, temp->key);
        }
    }
    return erase_maintain(root);
}

RBTNode *erase(RBTNode *root, int key) {
    root = __erase(root, key);
    root->color = BLACK;
    return root;
}

void clear(RBTNode *node) {
    if (node == NIL) return ;
    clear(node->lchild);
    clear(node->rchild);
    free(node);
    return ;
}

void output(RBTNode *root) {
    if (root == NIL) return ;
    printf("(%d, %d, %d) = %d\n", root->key, root->lchild->key, root->rchild->key, root->color);
    output(root->lchild);
    output(root->rchild);
}

int main() {
    srand(time(0));
    int op, val;
    RBTNode *root = NIL;
    #define MAX_OP 20
    for (int i = 0; i < MAX_OP; i++) {
        op = rand() % 5, val = rand() % 10;
        switch (op) {
            case 0:
                printf("delete val %d from RBT\n", val);
                root = erase(root, val);
                break; 
            case 1:
            case 2:
            case 3:
            case 4:
                printf("insert val %d to RBT\n", val);
                root = insert(root, val);
                break;
        }
        output(root);
    }
    clear(root);
    return 0;
}
