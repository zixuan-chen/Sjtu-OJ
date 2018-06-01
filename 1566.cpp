#include <iostream>
#include <cstdio>
#include <stack>
#include <queue>
using namespace std;

class DisjointSet
{
  private:
    int size;
    int *parent;

  public:
    DisjointSet(int s);
    ~DisjointSet();
    void Union(int root1, int root2);
    int Find(int i);
    int FindNonRecur(int i);
};

DisjointSet::DisjointSet(int s)
{
    parent = new int[s];
    for (int i = 0; i < s; i++)
        parent[i] = -1;
    size = s;
}

DisjointSet::~DisjointSet()
{
    delete parent;
}

void DisjointSet::Union(int root1, int root2)
{

    if (root1 == root2)
        return;
    if (parent[root1] < parent[root2])
    {
        parent[root1] = parent[root1] + parent[root2];
        parent[root2] = root1;
    }

    else
    {
        parent[root2] = parent[root1] + parent[root2];
        parent[root1] = root2;
    }
}
int DisjointSet::Find(int i)
{
    if (parent[i] < 0)
        return i;
    return parent[i] = Find(parent[i]);
}

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
    TypeOfEdge *dst;
    int *len;
    int *prev;

    adjListGraph(const TypeOfVer vers[], int vSize);
    adjListGraph(int vSize);
    bool exist(int u, int v) const;
    bool insert(int u, int v, TypeOfEdge w);
    bool remove(int u, int v);
    void remove(const TypeOfVer &n);
    void dfs() const;
    void bfs() const;
    void Kruscal() const;
    void Prim() const;
    void Dijkstra(int start);
    void printPath(int start, int end);
    ~adjListGraph();
};

template <class TypeOfVer, class TypeOfEdge>
adjListGraph<TypeOfVer, TypeOfEdge>::adjListGraph(int vSize)
{
    verList = new verNode[vSize];
    for (int i = 0; i < vSize; i++)
    {
        verList[i].value = 'A' + i;
    }
    Vers = vSize;
    Edges = 0;
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

struct edge
{
    int begin, end, weight;
    edge() {}
    edge(int b, int e, int w) : begin(b), end(e), weight(w) {}
};

bool operator<(const edge &a, const edge &b)
{
    return a.weight > b.weight;
}

template <class TypeOfVer, class TypeOfEdge>
void adjListGraph<TypeOfVer, TypeOfEdge>::Kruscal() const
{
    int edgeAccepted = 0, u, v;
    TypeOfEdge minWeight = 0;
    priority_queue<edge> q;
    DisjointSet s(Vers);
    edge e;

    for (int i = 0; i < Vers; i++)
    {
        for (edgeNode *tmp = verList[i].head; tmp != NULL; tmp = tmp->next)
        {
            q.push(edge(i, tmp->end, tmp->weight));
            //cout << "(" << i << ", " << tmp->end << ") = " << tmp->weight << endl;
        }
    }

    while (edgeAccepted < Vers - 1)
    {

        e = q.top();
        q.pop();
        u = s.Find(e.begin);
        v = s.Find(e.end);
        if (u != v)
        {
            s.Union(u, v);
            minWeight += e.weight;
            edgeAccepted++;
        }
    }

    cout << minWeight;
}

int main(int argc, char const *argv[])
{
    freopen("in", "r", stdin);
    int N, w, num;
    char u, v;
    cin >> N;
    cin.get();

    adjListGraph<char, int> g(N);
    for (int i = 0; i < N - 1; i++)
    {
        cin.get(u);
        cin.get();
        cin >> num;
        //cout << "u = " << u << endl;
        while (num-- > 0)
        {
            cin.get();
            cin.get(v);
            cin.get();
            cin >> w;
            g.insert(u - 'A', v - 'A', w);
            //cout << "(" << u << ", " << v <<") = " << w << endl;
        }
        cin.get();
    }

    g.Kruscal();

    fclose(stdin);
    return 0;
}
