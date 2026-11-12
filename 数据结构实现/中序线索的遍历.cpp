#include <iostream>

typedef int ElemType;
typedef struct ThreadNode
{
    ElemType data;
    struct ThreadNode *lchild, *rchild;
    int ltag, rtag;
} ThreadNode, *ThreadTree;

void InOrderTraverse_Thread(ThreadTree T)
{
    if (T == nullptr)
    {
        return;
    }

    ThreadNode *p = T;

    //
    while (p != nullptr)
    {
        // 找到最左下的节点，最左节点的前驱为空
        while (p->ltag == 0)
        {
            p = p->lchild;
        }
        // 此时p是最左下的节点，前驱为空，所以访问p
        std::cout << p->data << " ";

        /**
         * 因为从最左下的节点开始访问，所以前驱没用了，只用持续找后继节点即可
         */

        // 这里要注意检查，p->rchild是否为空
        // 因为最后一个节点，虽然rtag==1，但是rchild指向nullptr
        while (p->rtag == 1 && p->rchild != nullptr)
        {
            // p已经访问过了，所以有后继则访问后继
            p = p->rchild;
            std::cout << p->data << " ";
        }
        // p->rtag == 0，说明p有右孩子, 此时访问右孩子
        p = p->rchild;
        /** 注意前面说过，二叉树是一个典型的递归结构
         *  此时等价于递归访问右子树，右子树的根为p
         * */
    }
}