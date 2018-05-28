#include <iostream>
#include <cstdio>
#include <queue>
#include <stack>
using namespace std;

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
    Type *tmp = array;
    array = new Type[2 * maxSize];
    for (int i = 0; i <= currentSize; ++i)
    {
        array[i] = tmp[i];
    }
    maxSize *= 2;
    delete[] tmp;
}

template <class Type>
void priorityQueue<Type>::percolateUp(int hole)
{
    Type tmp = array[hole];
    while (hole != 1)
    {
        if (tmp < array[hole / 2])
        {
            array[hole] = array[hole / 2];
            hole /= 2;
        }
        else
            break;
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
    array[1] = array[currentSize--];
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
        TypeOfEdge weight;
        edgeNode *next;
        edgeNode() : next(NULL) {}
        edgeNode(int e, TypeOfEdge w, edgeNode *n = NULL) : end(e), weight(w), next(n) {}
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

    void dfs(int v, bool visited[]) const;

  public:
    struct DijkstraNode
    {
        int node, prev;
        TypeOfEdge distance;
        bool known;
        bool operator<(const DijkstraNode &x)
        {
            return distance < x.distance;
        }
    };

    adjListGraph(const TypeOfVer vers[], int vSize);
    bool exist(int u, int v) const;
    bool insert(int u, int v, TypeOfEdge w);
    bool remove(int u, int v);
    void remove(const TypeOfVer &n);
    void dfs() const;
    void bfs() const;
    void Kruscal() const;
    void Prim() const;
    void Dijkstra(int start, DijkstraNode *&res);
    void printPath(int start, int end, DijkstraNode *&res);
    ~adjListGraph();
};

template <class TypeOfVer, class TypeOfEdge>
adjListGraph<TypeOfVer, TypeOfEdge>::adjListGraph(const TypeOfVer vers[], int vSize)
{
    verList = new verNode[vSize];
    for (int i = 0; i < vSize; i++)
    {
        verList[i].value = vers[i];
    }
    Vers = vSize;
    Edges = 0;
}

template <class TypeOfVer, class TypeOfEdge>
bool adjListGraph<TypeOfVer, TypeOfEdge>::exist(int u, int v) const
{
    if (u < 0 || u >= Vers || v < 0 || v >= Vers)
        return false;
    edgeNode *tmp = verList[u].head;
    while (tmp != NULL && tmp->end != v)
        tmp = tmp->next;
    if (tmp == NULL)
        return false;
    return true;
}

template <class TypeOfVer, class TypeOfEdge>
bool adjListGraph<TypeOfVer, TypeOfEdge>::insert(int u, int v, TypeOfEdge w)
{
    if (u < 0 || u >= Vers || v < 0 || v >= Vers)
        return false;
    edgeNode *tmp = verList[u].head;
    while (tmp != NULL && tmp->end != v)
        tmp = tmp->next;
    if (tmp != NULL)
        return false;
    verList[u].head = new edgeNode(v, w, verList[u].head);
    ++Edges;
    return true;
}
template <class TypeOfVer, class TypeOfEdge>
bool adjListGraph<TypeOfVer, TypeOfEdge>::remove(int u, int v)
{
    edgeNode *p = verList[u].head, *q = NULL;

    while (p != NULL && p->end != v)
    {
        q = p;
        p = p->next;
    }
    if (p == NULL)
        return false;

    if (q == NULL)
        verList[u].head = p->next;
    else
        q->next = p->next;
    delete p;
    Edges--;
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

template <class TypeOfVer, class TypeOfEdge>
void adjListGraph<TypeOfVer, TypeOfEdge>::Dijkstra(int start, DijkstraNode *&res)
{
    const TypeOfEdge noEdge = 10000000;
    DijkstraNode u;
    priorityQueue<DijkstraNode> q;
    edgeNode *p;
    res = new DijkstraNode[Vers];

    for (int i = 0; i < Vers; i++) //initialization
    {
        res[i].distance = noEdge;
        res[i].node = i;
        res[i].known = false;
        res[i].prev = -1;
    }

    res[start].known = true;
    for (p = verList[start].head; p != NULL; p = p->next)
    {
        res[p->end].prev = start;
        res[p->end].distance = p->weight;
        q.enQueue(res[p->end]);
    }

    int minDst;
    for (int i = 0; i < Vers && !q.isEmpty(); i++)
    {
        u = q.deQueue(); //u = u.node
        res[u.node].known = true;
        minDst = res[u.node].distance;

        for (p = verList[u.node].head; p != NULL; p = p->next)
        {
            if (!res[p->end].known && p->weight + minDst < res[p->end].distance)
            {
                res[p->end].distance = p->weight + minDst;
                res[p->end].prev = u.node;
                q.enQueue(res[p->end]);
            }
        }
    }
}

template <class TypeOfVer, class TypeOfEdge>
void adjListGraph<TypeOfVer, TypeOfEdge>::printPath(
    int start, int end, DijkstraNode *&res)
{
    if (start == end)
    {
        cout << start;
        return;
    }
    if (res[end].prev == -1)
    {
        cout << "no path from start to end" << endl;
        return;
    }
    printPath(start, res[end].prev, res);
    cout << ' ' << end;
}

//-----------------------improved Dijkstra---------------------------------
int main(int argc, char const *argv[])
{
    freopen("in", "r", stdin);
    int n, m, start, end, a, b, p;
    cin >> n >> m >> start >> end;

    adjListGraph<int, int> g(new int[n + 1], n + 1);
    adjListGraph<int, int>::DijkstraNode *res;

    for (int i = 0; i < m; i++)
    {
        cin >> a >> b >> p;
        g.insert(a, b, p);
    }

    g.Dijkstra(start, res);

    cout << res[end].distance << endl;

    g.printPath(start, end, res);
    fclose(stdin);
    return 0;
}
