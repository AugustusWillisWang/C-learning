//bintree write on my own;
//example : bintree
//Just do not want to copy the ppt........

typedef struct node Node;
#include "lazy.h"

struct node
{
    int data;
    int cnt;
    Node *left;
    Node *right;
};

Node *proot;

Node *AddToTree(int data, Node *proot)
{
    Node *pnodenew;
    pnodenew = (Node *)malloc(sizeof(Node));
    pnodenew->left = 0;
    pnodenew->right = 0;
    pnodenew->cnt = 1;
    pnodenew->data = data;
    if (proot == 0)
    {
        proot = pnodenew;
        return proot;
    }
    Node *pnodenow = proot;
    while (1)
    {

        if (data < pnodenow->data)
        {
            if (pnodenow->left == 0)
            {
                pnodenow->left = pnodenew;
                return proot;
            }
            else
            {
                pnodenow = pnodenow->left;
            }
        }
        else if (data > pnodenow->data)
        {
            if (pnodenow->right == 0)
            {
                pnodenow->right = pnodenew;
                return proot;
            }
            else
            {
                pnodenow = pnodenow->right;
            }
        }
        else
        {
            pnodenow->cnt++;
            free(pnodenew);
            return proot;
        }
    }
}

int FindInBinTree(int data, Node *proot)
{
    Node *pnow = proot;
    while (pnow->data != data)
    {
        if (pnow->data > data)
        {
            if (pnow->left)
                pnow = pnow->left;
            else
                return 0;
        }
        if (pnow->data < data)
            if (pnow->right)
                pnow = pnow->right;
            else
                return 0;
    }
    return pnow->cnt;
}

Node *FindNodeInBinTree(int data, Node *proot)
{
    Node *pnow = proot;
    while (pnow->data != data)
    {
        if (pnow->data > data)
        {
            if (pnow->left)
                pnow = pnow->left;
            else
                return 0;
        }
        if (pnow->data < data)
            if (pnow->right)
                pnow = pnow->right;
            else
                return 0;
    }
    return pnow;
}

int PrintTree(Node *p)
{
    if (p)
    {
        PrintTree(p->left);
        printf("data: %d, cnt:%d\n", p->data, p->cnt);
        PrintTree(p->right);
    }
}

int main()
{
    proot = AddToTree(3, proot);
    AddToTree(1, proot);
    AddToTree(5, proot);
    AddToTree(5, proot);
    FindInBinTree(5, proot);
    PrintTree(proot);
}