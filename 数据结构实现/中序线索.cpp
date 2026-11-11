#include <iostream>

typedef int ElemType;
typedef struct ThreadNode
{
    ElemType data;
    struct ThreadNode *lchild, *rchild;
    int ltag, rtag;
} ThreadNode, *ThreadTree;

/**
 * 这里有一个容易出错的点：
 * pre不能按值传递
 * 如果pre按值传递，那么在递归调用中，pre的值改变后，递归返回后
 * pre的值会恢复为原来的值，例如处理完左子树后，返回后，pre仍然为nullptr
 */
void InThread(ThreadTree p, ThreadNode *&pre)
{
    /**
     * 树为一个递归的结构
     * 初始时，p为空，则当前是空树，没必要继续了
     */
    if (p == nullptr)
    {
        return;
    }

    /**
     * 当树不为空时，因为遵循 左根右 的顺序
     * 所以最前面访问的是左子树，所以先要处理完左子树
     */
    InThread(p->lchild, pre);

    if (p->lchild == nullptr)
    { // 当前孩子的左孩子为空，可以设置指向前驱
      // 包含了第一个节点的前驱为空的情况，ltag仍然为1
        p->lchild = pre;
        p->ltag = 1;
    }

    /**
     * 空的右孩子指向后继
     * 而pre刚好是p的前驱，则p是pre的后继
     * 而前驱开始时可能为空，当pre为空时，说明当前节点是第一个访问的节点，则不需要设置前驱的后继
     */
    if (pre != nullptr && pre->rchild == nullptr)
    {
        pre->rchild = p;
        pre->rtag = 1;
    }

    pre = p; // 更新前驱节点为当前节点，为下一次访问做准备

    InThread(p->rchild, pre);
}
