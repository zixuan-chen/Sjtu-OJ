#include <iostream>
using namespace std;
int l, w, a, b, m;
int s[1001][1001];
int max(int a, int b)
{
	return (a > b) ? a : b;
}

int main()
{
	cin >> l >> w;
	for(int i = 1; i <= l; i++)
		for(int j = 1; j <= w; j++){
			cin >> s[i][j];
			s[i][j] += 	s[i-1][j] + s[i][j-1] - s[i-1][j-1];
		}
	cin >> a >> b;
	for(int i = a; i <= l; i++)
	for(int j = b; j <= w; j++)
		m = max(m, s[i][j] + s[i-a][j-b] - s[i-a][j] - s[i][j-b]);

	cout << m;
	return 0;
}
// int l,w,a,b,m,i,j;
// int s[1001][1001];
// int main(){
// 	using namespace std;
// 	cin>>l>>w;
// 	for (i=1; i<=l; i++)
// 		for (j=1; j<=w; j++){
// 			cin>>s[i][j];
// 			s[i][j]+=s[i-1][j]+s[i][j-1]-s[i-1][j-1];
// 		}
// 	cin>>a>>b;
// 	for (i=a; i<=l; i++)
// 		for (j=b; j<=w; j++)
// 		m=max(m,s[i][j]+s[i-a][j-b]-s[i][j-b]-s[i-a][j]);
// 	cout<<m;
// 	return 0;
// }
