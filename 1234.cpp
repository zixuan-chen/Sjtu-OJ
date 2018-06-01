#include <iostream>
#include <algorithm>
#include <cstdio>
using namespace std;

struct edge
{
    int begin, end, weight;
    bool operator<(const edge &e) const
    {
        return weight < e.weight;
    }
};

bool comp(edge a, edge b)
{
    return a.weight < b.weight;
}

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

int maxSize = 10001;

int main(int argc, char const *argv[])
{
    //freopen("in", "r", stdin);
    int n, m, minWeight = 0, edgeAccepted = 0, u, v;
    DisjointSet s(maxSize);
    edge edges[100001];
    int i;
    cin >> n >> m;
    for (i = 0; i < m; i++)
    {
        cin >> edges[i].begin >> edges[i].end >> edges[i].weight;
    }

    sort(edges, edges + m, comp);

    i = 0;
    while (edgeAccepted < n - 1)
    {
        u = s.Find(edges[i].begin);
        v = s.Find(edges[i].end);
        if (u != v)
        {
            //cout << edges[i].begin << '\t' << edges[i].end << '\t' << edges[i].weight << endl;
            s.Union(u, v);
            minWeight += edges[i].weight;
            edgeAccepted++;
        }
        i++;
    }

    cout << minWeight;
    //fclose(stdin);
    return 0;
}