#include <iostream>
#include <queue>
#include <vector>
#include <cstdio>
using namespace std;
#define INF 0x7FFFFFFF
//--------------------------------priorityQueue-------------------------------
template <class Type>
class priorityQueue
{
  private:
    Type *array;
    int currentSize;
    int maxSize;

    void doubleSpace();
    void buildHeap();
    void percolateDown(int hole);
    void percolateUp(int hole);

  public:
    priorityQueue(int capacity = 100)
    {
        array = new Type[capacity];
        maxSize = capacity;
        currentSize = 0;
    }
    priorityQueue(const Type *data, int size);
    ~priorityQueue() { delete array; }
    bool isEmpty() const { return currentSize == 0; }
    void enQueue(const Type &x);
    Type deQueue();
    Type getHead() { return array[1]; }
};

template <class Type>
void priorityQueue<Type>::doubleSpace()
{
    Type *tmp = new Type[2 * maxSize];
    for (int i = 0; i <= currentSize; ++i)
        tmp[i] = array[i];
    maxSize *= 2;
    delete[] array;
    array = tmp;
}

template <class Type>
void priorityQueue<Type>::percolateUp(int hole)
{
    Type tmp = array[hole];
    for (; hole > 1 && tmp < array[(hole >> 1)]; hole = (hole >> 1))
    {
        array[hole] = array[(hole >> 1)];
    }
    array[hole] = tmp;
}

template <class Type>
void priorityQueue<Type>::enQueue(const Type &x)
{
    if (currentSize == maxSize)
        doubleSpace();
    int hole = ++currentSize;
    array[hole] = x;
    percolateUp(hole);
}

template <class Type>
void priorityQueue<Type>::percolateDown(int hole)
{
    if (hole < 1 || currentSize < hole)
        return;
    Type tmp = array[hole];
    int child;
    while (hole * 2 <= currentSize)
    {
        child = hole * 2;
        if (child != currentSize && array[child + 1] < array[child])
            child++;

        if (array[child] < tmp)
        {
            array[hole] = array[child];
            hole = child;
        }
        else
            break;
    }
    array[hole] = tmp;
}

template <class Type>
Type priorityQueue<Type>::deQueue()
{
    Type tmp = array[1];
    array[1] = array[currentSize];
    --currentSize;
    percolateDown(1);
    return tmp;
}

template <class Type>
void priorityQueue<Type>::buildHeap()
{
    for (int i = currentSize / 2; i > 0; --i)
        percolateDown(i);
}

template <class Type>
priorityQueue<Type>::priorityQueue(const Type *data, int size)
{
    maxSize = size + 10;

    currentSize = size;
    array = new Type[maxSize];

    for (int i = 0; i < size; ++i)
    {
        array[i + 1] = data[i];
    }
    buildHeap();
}

//-------------------------------adjListGraph---------------------------------
template <class TypeOfVer, class TypeOfEdge>
class adjListGraph
{
  private:
    struct edgeNode
    {
        int end;
        TypeOfEdge weight, cost;
        edgeNode *next;
        edgeNode() : next(NULL) {}
        edgeNode(int e, TypeOfEdge w, TypeOfEdge c,  edgeNode *n = NULL) 
        : end(e), weight(w),cost(c), next(n) {}
    };

    struct verNode
    {
        TypeOfVer value;
        edgeNode *head;
        verNode() : head(NULL) {}
        verNode(TypeOfVer v, edgeNode *h = NULL) : value(v), head(h) {}
    };

    verNode *verList;
    int Vers, Edges;

  public:
    TypeOfEdge *dst;
    int *cost;
    int *prev;

    adjListGraph(int vSize);
    bool insert(int u, int v, TypeOfEdge w, TypeOfEdge c);
    bool remove(int u, int v);
    void Dijkstra(int start);
    void printPath(int start, int end);
    ~adjListGraph();
};

template <class TypeOfVer, class TypeOfEdge>
adjListGraph<TypeOfVer, TypeOfEdge>::adjListGraph(int vSize)
{
    verList = new verNode[vSize];
    dst = new TypeOfEdge[vSize];
    cost = new int[vSize];
    prev = new int[vSize];
    for (int i = 0; i < vSize; i++)
    {
        verList[i].value = i;
        verList[i].head = NULL;
    }
    Vers = vSize;
    Edges = 0;
}

template <class TypeOfVer, class TypeOfEdge>
bool adjListGraph<TypeOfVer, TypeOfEdge>::insert(int u, int v, TypeOfEdge w, TypeOfEdge c)
{
    if (u < 0 || u >= Vers || v < 0 || v >= Vers)
        return false;

    edgeNode *tmp = verList[u].head;
    while (tmp != NULL && tmp->end != v)
        tmp = tmp->next;

    if (tmp != NULL)
        return false;
    else
    {
        tmp = verList[u].head;
        verList[u].head = new edgeNode(v, w, c, tmp);
        ++Edges;
    }

    return true;
}

template <class TypeOfVer, class TypeOfEdge>
adjListGraph<TypeOfVer, TypeOfEdge>::~adjListGraph()
{
    edgeNode *p;
    for (int i = 0; i < Vers; i++)
    {
        while ((p = verList[i].head) != NULL)
        {
            verList[i].head = p->next;
            delete p;
        }
    }
    delete[] verList;
}

struct node
{
    int ver, dst;
    bool operator<(const node &x)
    {
        return dst < x.dst;
    }
    node(int v, int d) : ver(v), dst(d) {}
};

template <class TypeOfVer, class TypeOfEdge>
void adjListGraph<TypeOfVer, TypeOfEdge>::Dijkstra(int start)
{
    for (int i = 0; i < Vers; i++)
    {
        dst[i] = INF;
        cost[i] = INF;
    }
    dst[start] = 0;
    cost[start] = 0;

    priorityQueue<node> q;
    q.enQueue(node(start, 0));
    node u;
    while (!q.isEmpty())
    {
        u = q.deQueue();
        for (p = verList[u.ver].head; p; p = p->next)
        {
            if ((p->weight + u.dst < dst[p->end]) ||
                ((p->weight + u.dst == dst[p->end]) && (cost[p->end] > cost[u.ver] + p->cost)))
            {
                dst[p->end] = p->weight + u.dst;
                prev[p->end] = u.ver;
                cost[p->end] = cost[u.ver] + p->cost;
                q.enQueue(node(p->end, dst[p->end]));
            }
        }
    }
}

template <class TypeOfVer, class TypeOfEdge>
void adjListGraph<TypeOfVer, TypeOfEdge>::printPath(
    int start, int end)
{
    if (start == end)
    {
        cout << start;
        return;
    }
    printPath(start, prev[end]);
    cout << ' ' << end;
}

//-----------------------improved Dijkstra---------------------------------
int main(int argc, char const *argv[])
{
    freopen("in", "r", stdin);
    int n, m, start, end, a, b, d, p;
    cin >> n >> m;
    adjListGraph<int, int> g(n + 1);

    for (int i = 0; i < m; i++)
    {
        cin >> a >> b >> d >> p;
        g.insert(a, b, d, p);
        g.insert(b, a, d, p);
    }
    cin >> start >> end;

    g.Dijkstra(start);
    cout << g.dst[end] << ' ' << g.cost[end];

    fclose(stdin);
    return 0;
}
