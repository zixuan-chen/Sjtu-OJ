#include <iostream>
#include <cstdio>
#include <cstring>
#include <queue>
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
    TypeOfEdge distance[Vers];
    int prev[Vers];
  public:
    adjListGraph(int vSize);
    bool insert(int u, int v, TypeOfEdge w);
    bool remove(int u, int v);
    void shortestPathNegative(int start);
    TypeOfEdge getShortestPathWeight(int start, int end);
    ~adjListGraph();
};

template <class TypeOfVer, class TypeOfEdge>
adjListGraph<TypeOfVer, TypeOfEdge>::adjListGraph(int vSize)
{
    verList = new verNode[vSize];
    for (int i = 0; i < vSize; i++)
    {
        verList[i].value = i;
        verList[i].head = NULL;
    }
    Vers = vSize;
    Edges = 0;
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
        tmp->weight = (tmp->weight < w) ? tmp->weight : w;
    else
    {
        tmp = verList[u].head;
        verList[u].head = new edgeNode(v, w, tmp);
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

template <class TypeOfVer, class TypeOfEdge>
void adjListGraph<TypeOfVer, TypeOfEdge>::shortestPathNegative(int start)
{
    queue<int> q;
    int v;
    for(int i = 0; i < Vers; i++)
    {
        distance[i] = INF;
    }
    distance[start] = 0;
    q.push(start);
    while(!q.empty())
    {
        v = q.front();
        q.pop();
        for(edgeNode * tmp = verList[v].head; tmp != NULL; tmp = tmp->next)
        {
            if(distance[v] + tmp->weight < distance[tmp->end])
            {
                distance[tmp->end] = distance[v] + tmp->weight;
                prev[w] = v;
            }
        }
    }
}

template <class TypeOfVer, class TypeOfEdge>
TypeOfEdge adjListGraph<TypeOfVer, TypeOfEdge>::getShortestPathWeight(int start, int end)
{
    shortestPathNegative(start);
    return distance[end];
}

//-----------------------improved shortestPathNegative---------------------------------
int main(int argc, char const *argv[])
{
    freopen("in", "r", stdin);
    int n, m, start, end, a, b, p;
    cin >> n >> m >> start >> end;

    adjListGraph<int, int> g(n + 1);

    for (int i = 0; i < m; i++)
    {
        cin >> a >> b >> p;
        g.insert(a, b, p);
    }
    cout << g.getShortestPathWeight(start, end);
    fclose(stdin);
    return 0;
}
