#include <iostream>
#include <cstdio>

using namespace std;
const int MAX_INT = 300001;
const int MIN_INT = (-2147483647 - 1);

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

template <class Type>
class BinarySearchTree
{
  private:
    struct Node
    {
        Node *left;
        Node *right;
        Type data;
        Node() : left(NULL), right(NULL) {}
        Node(Type d, Node *l = NULL, Node *r = NULL) : data(d), left(l), right(r) {}
        ~Node() {}
    };

    Node *root;

    bool find(const Type &x, Node *t) const;
    void insert(const Type &x, Node *&t);
    void remove(const Type &x, Node *&t);
    void clear(Node *t);
    void midOrder(Node *t) const;
    void delete_interval(const Type &a, const Type &b, Node *t);

  public:
    BinarySearchTree() : root(NULL) {}
    bool isEmpty() { return root == NULL; }
    bool find(const Type &x) const;
    void insert(const Type &x);
    void remove(const Type &x);
    void delete_interval(const Type &a, const Type &b);
    bool find_ith(int i, Type &res);
    ~BinarySearchTree();
};
template <class Type>
bool BinarySearchTree<Type>::find(const Type &x, Node *t) const
{
    if (t == NULL)
        return false;
    else if (x < t->data)
        return find(x, t->left);
    else if (x > t->data)
        return find(x, t->right);
    else
        return true;
}
template <class Type>
void BinarySearchTree<Type>::insert(const Type &x, Node *&t)
{
    if (t == NULL)
        t = new Node(x);
    else if (x < t->data)
        insert(x, t->left);
    else
        insert(x, t->right);
}
template <class Type>
void BinarySearchTree<Type>::remove(const Type &x, Node *&t)
{
    if (t == NULL)
        return;
    else if (x < t->data)
        remove(x, t->left);
    else if (x > t->data)
        remove(x, t->right);
    else
    {
        if (t->left != NULL && t->right != NULL)
        {
            Node *tmp = t->right;
            while (tmp->left != NULL)
                tmp = tmp->left;
            t->data = tmp->data;
            remove(t->data, t->right);
        }
        else
        {
            Node *tmp = t;
            t = (t->left != NULL) ? t->left : t->right;
            delete tmp;
        }
    }
}
template <class Type>
void BinarySearchTree<Type>::delete_interval(const Type &a, const Type &b, Node *t)
{
    if (t == NULL)
        return;
    if (t->data <= a)
        delete_interval(a, b, t->right);
    else if (t->data >= b)
        delete_interval(a, b, t->left);
    else
    {
        remove(t->data, t);
        delete_interval(a, b, t);
    }
}

template <class Type>
void BinarySearchTree<Type>::clear(Node *t)
{
    if (t == NULL)
        return;
    clear(t->left);
    clear(t->right);
    delete t;
}
template <class Type>
void BinarySearchTree<Type>::midOrder(Node *t) const
{
    if (t == NULL)
        return;
    midOrder(t->left);
    cout << t->data << ' ';
    midOrder(t->right);
}

template <class Type>
bool BinarySearchTree<Type>::find(const Type &x) const
{
    return find(x, root);
}
template <class Type>
void BinarySearchTree<Type>::insert(const Type &x)
{
    insert(x, root);
}
template <class Type>
void BinarySearchTree<Type>::remove(const Type &x)
{
    remove(x, root);
}
template <class Type>
BinarySearchTree<Type>::~BinarySearchTree()
{
    clear(root);
}

template <class Type>
void BinarySearchTree<Type>::delete_interval(int a, int b)
{
    delete_interval(a, b, root);
}
template <class Type>
bool BinarySearchTree<Type>::find_ith(int i, Type &res)
{
    int order = 0;
    seqStack<Node *> s;
    Node *tmp = root;
    while (tmp != NULL)
    {
        s.push(tmp);
        tmp = tmp->left;
    }
    while (!s.empty() && order < i)
    {
        res = tmp = s.pop();
        order++;
        tmp = tmp->right;
        while (tmp != NULL)
            s.push(tmp);
    }
    if (order == i)
        return true;
    else
        return false;
}

int detectCommand()
{
    char cmd[20];
    cin.getline(cmd, 20, ' ');
    switch (cmd[0])
    {
    case 'i':
        return 1;
    case 'f':
        if (cmd[4] == '_')
            return 7;
        else
            return 6;
    case 'd':
        if (cmd[7] == 'l')
            return 3;
        if (cmd[7] == 'g')
            return 4;
        if (cmd[7] == 'i')
            return 5;
        else
            return 2;
    }
}

int main()
{
    //freopen("in", "r", stdin);
    int N, op1, op2;
    char cmd;
    BinarySearchTree<int> bt;
    cin >> N;
    cin.get();
    while (N-- > 0)
    {
        switch (detectCommand())
        {
        case 1:
            cin >> op1;
            cin.get();
            bt.insert(op1);
            break;
        case 2:
            cin >> op1;
            cin.get();
            bt.remove(op1);
            break;
        case 3:
            cin >> op1;
            cin.get();
            bt.delete_interval(MIN_INT, op1);
            break;
        case 4:
            cin >> op1;
            cin.get();
            bt.delete_interval(op1, MAX_INT);
            break;
        case 5:
            cin >> op1 >> op2;
            cin.get();
            bt.delete_interval(op1, op2);
            break;
        case 6:
            cin >> op1;
            cin.get();
            if (bt.find(op1))
                cout << 'Y' << endl;
            else
                cout << 'N' << endl;
        case 7:
            cin >> op1;
            cin.get();
            int res;
            bool isHere = bt.find_ith(op1, res);
            if (isHere)
                cout << res << endl;
            else
                cout << 'N' << endl;
        default:
            break;
        }
    }

    //cin.get();
    //fclose(stdin);
    return 0;
}
