#include <iostream>
#include <stdio.h>
using namespace std;
int P[10000000], V[10000000];

int main(int argc, char const *argv[])
{
	freopen("in", "r", stdin);
	int N, group;
	cin >> N;
	for (int i = 0; i < N; ++i)
	{
		cin >> P[i] >> V[i];
	}
	group = N;
	for (int i = 0; i < N; ++i)
	{
		if(P[i] == -1) continue;
		else for(int j = 0; j < N; ++j){
			if(P[j] == -1 || j == i) continue;
			if (P[j] < P[i] && V[j] > V[i])
			{
				P[j] = -1;
				group--;
			}
		}
	}

	cout << group;
	fclose(stdin);
	return 0;
}