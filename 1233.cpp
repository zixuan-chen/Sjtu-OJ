#include <iostream>
#include <stack>
#include <queue>
#include <cstdio>
using namespace std;

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

  public:
    adjListGraph(const TypeOfVer vers[], int vSize);
    bool exist(int u, int v) const;
    bool insert(int u, int v, TypeOfEdge w);
    bool remove(int u, int v);
    void remove(const TypeOfVer &n);
    int numOfDfs(int start, int length) const;
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
adjListGraph<TypeOfVer, TypeOfEdge>::~adjListGraph()
{
    edgeNode *tmp;
    for (int i = 0; i < Vers; i++)
    {
        while ((tmp = verList[i].head) != NULL)
        {
            verList[i].head = tmp->next;
            delete tmp;
        }
    }
    delete[] verList;
}

template <class TypeOfVer, class TypeOfEdge>
int adjListGraph<TypeOfVer, TypeOfEdge>::numOfDfs(int start, int length) const
{
    int num = 0;
    stack<int> s, l, t;
    bool *isInPath = new bool[Vers];

    for (int i = 0; i < Vers; i++)
    {
        isInPath[i] = false;
    }

    int currentNode, currentLen;
    bool alreadytraversed;
    edgeNode *tmp;
    s.push(start);
    l.push(0);
    t.push(0);
    isInPath[start] = true;
    while (!s.empty())
    {
        currentNode = s.top();
        currentLen = l.top();
        alreadytraversed = t.top();
        t.pop();
        //cout << "currentNode = " << currentNode << '\t' << "currentLen = " << currentLen << endl;
        if (currentLen == length && currentNode != start)
        {
            num++;
            isInPath[currentNode] = false;
            s.pop();
            l.pop();
        }
        else if (currentLen < length)
        {
            if (alreadytraversed)
            {
                isInPath[currentNode] = false;
                s.pop();
                l.pop();
            }
            else
            {
                t.push(1);
                tmp = verList[currentNode].head;
                while (tmp != NULL)
                {
                    //cout << "tmp->end = " << tmp->end << endl;
                    if (isInPath[tmp->end] == false)
                    {
                        //cout << "isInPath[tmp->end] == false" << endl;
                        s.push(tmp->end);
                        l.push(currentLen + 1);
                        t.push(0);
                        isInPath[currentNode] = true;
                    }
                    tmp = tmp->next;
                }
            }
        }
    }

    return num;
}

int main(int argc, char const *argv[])
{
    freopen("in", "r", stdin);
    int n, m, start, M, a, b;
    cin >> n >> m >> start >> M;
    //cout << n << '\t' << m << '\t' << start << '\t' << M << endl;
    int *ver = new int[n + 1];
    adjListGraph<int, int> g(ver, n + 1);
    while (m-- > 0)
    {
        cin >> a >> b;
        g.insert(a, b, 1);
    }

    //cout << "here" << endl;
    cout << g.numOfDfs(start, M);
    fclose(stdin);
    return 0;
}
