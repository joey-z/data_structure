/*************************************************************************
	> File Name: 27.AVL.c
	> Author: Zoe 
	> Mail: 
	> Created Time: 2019年01月25日 星期五 15时06分36秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>

#define max(a, b) ({ __typeof(a) __a = (a); __typeof(b) __b = (b); __a > __b ? __a : __b; })

//与普通的二叉排序树结构相同　结构定义
typedef struct Node {
    int key;
    int height;//AVL树根据高度调整
    struct Node *lchild, *rchild;
} Node;

Node *NIL = NULL;//为了方便设置一个虚拟节点　
//在Node *insert()函数中　对于当前的root来讲如果我插入一个节点　root的高度会改变　
//所以要调整当前根节点的高度　当前节点的高度 = 左/右子孩子高度＋１　但是左右子孩子有可能为空
//要加特殊判断　所以为了方便设置虚拟节点　虚拟节点高度为０

//结构操作
Node *init(int key) {
    Node *p = (Node *)calloc(sizeof(Node), 1);//calloc malloc区别
    p->key = key;
    p->height = 1;//AVL树根据高度调整
    p->lchild = p->rchild = NIL;
    return p;
}

//让这个函数自己全局运行一次
__attribute__((constructor)) //attribute__((性质))
void init_NIL() {//虚拟节点初始化
    NIL = init(0);
    NIL->height = 0;//虚拟节点的高度特殊设置成０
    NIL->lchild = NIL->rchild = NIL;//NIL的左孩子和右孩子都指向它自己
    return ;
}

//计算节点的高度
void calc_height(Node *root) {
    root->height = max(root->lchild->height, root->rchild->height) + 1;
    return ;
}

//左旋　旋转之后的根节点应该是当前节点的右孩子
Node *left_rotate(Node *root) {
    Node *temp = root->rchild;
    //原来根节点的右孩子变成temp->lchild
    root->rchild = temp->lchild;
    //当前节点的左孩子变成原来的根节点
    temp->lchild = root;
    calc_height(root);//计算原来根节点的高度
    calc_height(temp);//计算新根节点的高度
    return temp;
}

//右旋　旋转之后的根节点应该是当前节点的左孩子
Node *right_rotate(Node *root) {
    Node *temp = root->lchild;
    root->lchild = temp->rchild;
    temp->rchild = root;
    calc_height(root);
    calc_height(temp);
    return temp;
}

//AVL树调整代码
Node *maintain(Node *root) {    //首先判断是否失衡　平衡则直接return root
    if (abs(root->lchild->height - root->rchild->height) <= 1) return root;    
    //判断左子树的高度是否大于右子树的高度
    //L类型
    if (root->lchild->height > root->rchild->height) {
        //LR
        //小左旋
        if (root->lchild->lchild->height < root->lchild->rchild->height) {
            root->lchild = left_rotate(root->lchild);
        }
        //大右旋
        root = right_rotate(root);
    } else {
    //R类型
        if (root->rchild->rchild->height < root->rchild->lchild->height) {
            //RL
            //小右旋
            root->rchild = right_rotate(root->rchild);
        }
        //大左旋
        root = left_rotate(root);
    }
    return root;
}


Node *insert(Node *root, int key) {
    if (root == NIL) return init(key);
    if (root->key == key) return root;
    else if (root->key < key) root->rchild = insert(root->rchild, key);
    else root->lchild = insert(root->lchild, key);
    //根节点的高度为左孩子/右孩子的节点高度加１
    //root->height = max(root->lchild->height, root->rchild->height) + 1;
    calc_height(root);
    return maintain(root); //完成插入操作的此根节点有可能失衡　　所以对此根节点调整
}

//前驱节点
Node *predecessor(Node *root) {
    //前驱应该是左子树的最右节点
    Node *temp = root->lchild;
    //有右孩子　
    while (temp->rchild != NIL) temp = temp->rchild;
    return temp;
}

//删除操作也可能改变根节点
Node *erase(Node *root, int key) {
    if (root == NIL) return root;//在本代码中没有空节点　
    if (root->key < key) {
        root->rchild = erase(root->rchild, key);
    } else if (root->key > key) {
        root->lchild = erase(root->lchild, key);
    } else {
        //找到了要删除的节点　（本质是二叉排序树　删除参考二叉排序树）
        //出度为０　直接删除
        if (root->lchild == NIL && root->rchild == NIL) {
            free(root);
            return NIL;
        //度为１　
        } else if (root->lchild == NIL || root->rchild == NIL) {
            //找到它的唯一子孩子
            Node *temp = (root->lchild != NIL ? root->lchild : root->rchild);
            free(root);
            return temp;
        //度为２
        } else {
            //找到待删除节点的前驱节点
            Node *temp = predecessor(root); 
            root->key = temp->key;
            root->lchild = erase(root->lchild, temp->key);
        }
    }
    calc_height(root);
    return maintain(root);
}

void clear(Node *node) {
    if (node == NIL) return ;
    clear(node->lchild);
    clear(node->rchild);
    free(node);
    return ;
    //递归　递推　
}

void output(Node *root) {
    if (root == NIL) return ;
    printf("(%d, %d, %d)\n", root->key, root->lchild->key, root->rchild->key);
    output(root->lchild);
    output(root->rchild);
    return ;
}

int main() {
    int op, val;
    Node *root = NIL;
    while (scanf("%d%d", &op, &val) != EOF) {
        switch (op) {
            case 1: root = insert(root, val); break;
            case 2: root = erase(root, val); break;
        }
        output(root);
    }
    return 0;
}
