#include <iostream>
#include <cstdio>
using namespace std;

struct edge
{
    int end;
    edge * next;
    edge(int e, edge *n = NULL): end(e), next(n){}
};

struct node
{
    int inDegree;
    int state; // 0: undiscard; 1: ready to be discard; 2: already discard
    edge * head;
};

int main()
{
    freopen("in", "r", stdin);
    int n, m, a, b;
    cin >> n >> m;
    node *nodes = new node[n + 1];
    for(int i = 0; i < n + 1; i++)
    {
        nodes[i].inDegree = 0;
        nodes[i].state = 0;
    }
    
    for(int i = 0; i < m; i++)
    {
        cin >> a >> b;
        nodes[b].head = new edge(a, nodes[b].head);
        nodes[a].inDegree += 1;
    }

    int res = 0;
    bool flag = true;
    while(flag)
    {
        flag = false;
        for(int i = 1; i < n + 1; i++)
        {
            if(nodes[i].inDegree == 0 && nodes[i].state == 0)
            {
                flag = true;
                nodes[i].state = 1;
            }
        }
        for (int i = 1; i < n + 1; i++)
        {
            if (nodes[i].state == 1)
            {
                for(edge * tmp = nodes[i].head; tmp; tmp = tmp->next)
                {
                    nodes[tmp->end].inDegree--;
                }
                nodes[i].state = 2;
            }
        }
        res++;
    }
    cout << res;
    fclose(stdin);
    return 0;
}