#include <iostream>
#include <cstdio>
using namespace std;

template <class Type>
class hfTree
{
  private:
    struct Node
    {
        Type data;
        int weight;
        int parent, left, right;
    };

    int length;
    Node *elem;

  public:
    struct hfCode
    {
        Type data;
        int codeLength;
    };
    hfTree(const Type *x, const int *w, int size);
    void getCode(hfCode result[]);
    int getTotalLength();
    ~hfTree() { delete[] elem; }
};

template <class Type>
hfTree<Type>::hfTree(const Type *d, const int *w, int size)
{
    const int MAX_INT = 32767;
    int min1, min2;
    int x, y;
    length = 2 * size;
    elem = new Node[length];
    for (int i = size; i < length; ++i)
    {
        elem[i].data = d[i - size];
        elem[i].weight = w[i - size];
        elem[i].parent = elem[i].left = elem[i].right = 0;
    }

    for (int i = size - 1; i > 0; --i)
    {
        min2 = min1 = MAX_INT;
        x = y = 0;
        for (int j = i + 1; j < length; ++j)
        {
            if (elem[j].parent == 0)
            {
                if (elem[j].weight < min1)
                {
                    min2 = min1;
                    min1 = elem[j].weight;
                    y = x;
                    x = j;
                }
                else if (elem[j].weight < min2)
                {
                    min2 = elem[j].weight;
                    y = j;
                }
            }
        }

        elem[i].weight = min1 + min2;
        elem[i].left = x;
        elem[i].right = y;
        elem[i].parent = 0;
        elem[x].parent = i;
        elem[y].parent = i;
    }
}

template <class Type>
void hfTree<Type>::getCode(hfCode result[])
{
    int size = length / 2, p, s;
    for (int i = size; i < length; ++i)
    {
        result[i - size].data = elem[i].data;
        result[i - size].codeLength = 0;
        p = elem[i].parent;
        s = i;
        while (p != 0)
        {
            if (elem[p].left == s)
                result[i - size].codeLength += 1;
            else
                result[i - size].codeLength += 1;
            s = p;
            p = elem[p].parent;
        }
    }
}

int main()
{
    //freopen("in", "r", stdin);
    const int MAX_SIZE = 50001;
    int N, i = 0, sum = 0;
    cin >> N;
    int datas[MAX_SIZE];
    int frequency[MAX_SIZE];
    while (i < N)
    {
        datas[i] = i;
        cin >> frequency[i];
        i++;
    }
    hfTree<int> tree(datas, frequency, N);
    hfTree<int>::hfCode res[MAX_SIZE];
    tree.getCode(res);

    for (int j = 0; j < N; j++)
    {
        sum += res[j].codeLength * frequency[j];
    }
    cout << sum;
    //cin.get();
    //fclose(stdin);
    return 0;
}