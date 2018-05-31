#include <iostream>
#include <stack>
#include <math.h>
#include <cstdio>
using namespace std;
const int maxSize = 1000;
stack<int> path;
bool isInPath[maxSize]{false};
int edge[maxSize][maxSize];

bool findPath(int startPoint, int endPoint, int vSize)
{

    //cout << "startPoint = " << startPoint << '\t' << "endPoint = " << endPoint << endl;
	//start from 1
	bool flag = false;
	int current = path.top();
	if (current == endPoint)
		return true;
	for (int i = 1; i < vSize; i++)
	{
		if (i != current && isInPath[i] == false && edge[current][i] != 0)
		{
			path.push(i);
			isInPath[i] = true;
			if (findPath(i, endPoint, vSize))
			{
			    //cout << "i = " << i << endl;
				flag = true;
				break;
			}
			else
			{
				path.pop();
				isInPath[i] = false;
			}
		}
	}
	return flag;
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
    for(int i = 0; i < s; i++)
        parent[i] = -1;
    size = s;
}

DisjointSet::~DisjointSet()
{
    delete parent;
}

void DisjointSet::Union(int root1, int root2) //����ģ��
{

    if (root1 == root2)
        return;
    if (parent[root1] > parent[root2])
    {
       parent[root2] += parent[root1];
       parent[root1] = root2;
    }

    else
    {
        parent[root1] += parent[root2];
        parent[root2] = root1;
    }
}
int DisjointSet::Find(int i)
{
    if(i < 0 || i >= size) return -1;
    stack<int> s;
    int x, root;
    s.push(i);
    while(!s.empty())
    {
        x = s.top();
        if(parent[x] < 0)
        {
            root = x;
            s.pop();
            break;
        }
        s.push(parent[x]);
    }
    while(!s.empty())
    {
        x = s.top();
        parent[x] = root;
        s.pop();
    }
    return root;
}



int findPositon(int Pos, int dir)
{
	//dir = 0, 1, 2, 3
	int x = (sqrt(8 * Pos - 7) + 1) / 2;
	int y = Pos - x * (x - 1) / 2; //start from 1
	switch (dir)
	{
	case 0:
		if (y == 1 || x < 2)
			break;
		return (x - 1) * (x - 2) / 2 + y - 1;
	case 1:
		if (y == x || x < 2)
			break;
		return (x - 1) * (x - 2) / 2 + y;
	case 2:
		return x * (x + 1) / 2 + y;
	case 3:
		return x * (x + 1) / 2 + y + 1;
	}
	return -1;
}

int main()
{
    freopen("in", "r", stdin);
	//start from 1
	int N, X, Y, Pos, dir, adjPos;
	cin >> N >> X >> Y;
	const int vSize = (N + 1) * N / 2;
	//cout << "vSize = " << vSize << endl;
	DisjointSet s(vSize + 1);

	while (s.Find(X) != s.Find(Y))
	{
	    //cout << "here" << endl;
		cin >> Pos >> dir;
		adjPos = findPositon(Pos, dir);
		if (adjPos == -1 || adjPos > vSize)
			continue;
		s.Union(s.Find(adjPos), s.Find(Pos));
		//cout << "adjPos = " << adjPos << '\t' << "Pos = " << Pos << endl;
		edge[adjPos][Pos] = 1;
		edge[Pos][adjPos] = 1;
	}

	//findPath
	path.push(X);
	isInPath[X] = true;
	findPath(X, Y, vSize + 1);

	//output
	stack<int> tmp;
	while(!path.empty())
	{
		tmp.push(path.top());
		path.pop();
	}
	while(!tmp.empty())
	{
		cout << tmp.top() << ' ';
		tmp.pop();
	}
	fclose(stdin);
	return 0;
}
