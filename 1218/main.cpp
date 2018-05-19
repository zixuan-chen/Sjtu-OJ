#include <iostream>
#include <cstdio>
#include <stdlib.h>
using namespace std;

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
    void midOrder(Node *t);

  public:
    BinarySearchTree() : root(NULL) {}
    bool isEmpty() { return root == NULL; }
    bool find(const Type &x) const;
    void insert(const Type &x);
    void remove(const Type &x);
    void traverse() const;
    void exchange(BinarySearchTree<Type> &tmpbt);
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
    else if (x > t->data)
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
void BinarySearchTree<Type>::clear(Node *t)
{
    if (t == NULL)
        return;
    clear(t->left);
    clear(t->right);
    delete t;
}
template <class Type>
void BinarySearchTree<Type>::midOrder(Node *t)
{
    if (t == NULL)
        return;
    midOrder(t->left);
    cout << t->data << ' ';
    midOrder(t->right);
}
template <class Type>
void BinarySearchTree<Type>::traverse() const
{
    midOrder(root);
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
void BinarySearchTree<Type>::exchange(BinarySearchTree<Type> &tmpbt)
{
    Node *tmp;
    tmp = root;
    root = tmpbt.root;
    tmpbt.root = tmp;
}
int main()
{
    freopen("in", "r", stdin);
    int N, n, tmp;
    char cmd;
    BinarySearchTree<int> bt;
    cin >> N;
    cin.get();
    while (N-- > 0)
    {
        cin >> cmd;
        switch (cmd)
        {
        case '+':
            cin >> n;
            while (n-- > 0)
            {
                cin >> tmp;
                bt.insert(tmp);
            }
            cin.get();
            bt.traverse();
            cout << endl;
            break;
        case '-':
            cin >> n;
            while (n-- > 0)
            {
                cin >> tmp;
                if (bt.find(tmp))
                    bt.remove(tmp);
            }
            cin.get();
            bt.traverse();
            cout << endl;
            break;
        case '*':
        {
            cin >> n;
            BinarySearchTree<int> tmpbt;
            while (n-- > 0)
            {
                cin >> tmp;
                if (bt.find(tmp))
                    tmpbt.insert(tmp);
            }
            bt.exchange(tmpbt);
            cin.get();
            bt.traverse();
            cout << endl;
            break;
        }

        default:
            cout << "invalid command!\n";
        }
    }
    cin.get();
    fclose(stdin);
    return 0;
}