#include <iostream>
using namespace std;

int main()
{
	int M, T, u, f, d, i = 0,current = 0;
	char Si;
	cin >> M >> T >> u >> f >> d;
	cin.get();
	while(current <= M && i < T){
		cin.get(Si);
		switch(Si){
			case'u':
			case'd':current += u + d;break;
			case'f':current += 2 * f;break;
			default:cout << "error, get" << Si << endl;
		}
		i++;
		cin.get();
	}
	if(current > M) cout << i - 1;
	else cout << i;
	return 0;
}