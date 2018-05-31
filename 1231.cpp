#include <iostream>
#include <stdio.h>
using namespace std;

class outOfBound
{
};
class illegalSize
{
};

template <class elemType>
class seqStack
{
  private:
    elemType *elem;

    int maxSize;
    int head;
    void doubleSpace()
    {
        elemType *tmp = new elemType[2 * maxSize];
        for (int i = 0; i < maxSize; i++)
            tmp[i] = elem[i];
        delete elem;
        elem = tmp;
        maxSize *= 2;
    }

  public:
    seqStack(int initSize = 10)
    {
        if (initSize < 0)
            throw illegalSize();
        elem = new elemType[initSize];
        maxSize = initSize;
        head = -1;
    }
    int getLength() const
    {
        return head + 1;
    }
    bool isEmpty() const { return head == -1; }
    elemType top() const
    {
        if (isEmpty())
            throw outOfBound();
        return elem[head];
    }

    elemType pop()
    {
        if (isEmpty())
            throw outOfBound();
        return elem[head--];
    }
    void push(const elemType &x)
    {
        if (head == maxSize - 1)
            doubleSpace();
        elem[++head] = x;
    }

    ~seqStack() { delete elem; }
};

struct Node
{
    Node *left;
    Node *right;
    int data;
    Node() : left(NULL), right(NULL) {}
    Node(int d, Node *l = NULL, Node *r = NULL) : data(d), left(l), right(r) {}
    ~Node() {}
};

int main(int argc, char const *argv[])
{

    freopen("in", "r", stdin);
    int N, A, B, x, y;
    cin >> N >> A >> B;
    Node **nodeList = new Node *[N];
    bool isChild[N]{false};
    bool jumpOut;
    seqStack<Node *> sA, sB;
    seqStack<int> fA, fB;
    Node *tmp, *root;
    int flag, noChildVisited = 0, oneChildVisited = 1, twoChildVisited = 2;

    for (int i = 0; i < N; i++)
        nodeList[i] = new Node(i + 1);
    for (int i = 0; i < N; i++)
    {
        cin >> x >> y;
        if (x != 0)
        {
            nodeList[i]->left = nodeList[x - 1];
            isChild[x - 1] = true;
        }
        if (y != 0)
        {
            nodeList[i]->right = nodeList[y - 1];
            isChild[y - 1] = true;
        }
    }

    for (int i = 0; i < N; i++)
    {
        if (!isChild[i])
        {
            root = nodeList[i];
            break;
        }
    }

    //find path to A
    jumpOut = false;
    sA.push(root);
    fA.push(noChildVisited);
    while (!sA.isEmpty() && !jumpOut)
    {
        tmp = sA.pop();
        flag = fA.pop();
        switch (flag)
        {
        case 0:
            sA.push(tmp);
            fA.push(oneChildVisited);
            if (tmp->left != NULL)
            {
                sA.push(tmp->left);
                fA.push(noChildVisited);
            }
            break;
        case 1:
            sA.push(tmp);
            fA.push(twoChildVisited);
            if (tmp->right != NULL)
            {
                sA.push(tmp->right);
                fA.push(noChildVisited);
            }
            break;
        case 2:
            if (tmp->data == A)
            {
                sA.push(tmp);
                jumpOut = true;
            }
        }
    }

    //find path to B
    jumpOut = false;
    sB.push(root);
    fB.push(noChildVisited);
    while (!sB.isEmpty() && !jumpOut)
    {
        tmp = sB.pop();
        flag = fB.pop();
        switch (flag)
        {
        case 0:
            sB.push(tmp);
            fB.push(oneChildVisited);
            if (tmp->left != NULL)
            {
                sB.push(tmp->left);
                fB.push(noChildVisited);
            }
            break;
        case 1:
            sB.push(tmp);
            fB.push(twoChildVisited);
            if (tmp->right != NULL)
            {
                sB.push(tmp->right);
                fB.push(noChildVisited);
            }
            break;
        case 2:
            if (tmp->data == B)
            {
                sB.push(tmp);
                jumpOut = true;
            }
        }
    }

    while (!sA.isEmpty() && !sB.isEmpty())
    {

        if (sA.getLength() > sB.getLength())
            sA.pop();
        else if (sA.getLength() < sB.getLength())
            sB.pop();
        else
        {
            if (sA.top()->data == sB.top()->data)
            {
                cout << sA.top()->data;
                break;
            }
            sA.pop();
            sB.pop();
        }
    }

    fclose(stdin);
    return 0;
}
