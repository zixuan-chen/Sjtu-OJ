//排序
#include <iostream>
#include <algorithm>
#include <cstdio>
using namespace std;
const int max_M = 200010;
struct candy
{
    int A, B;
}cbox[max_M];
int N, M;
long long res = 0;

bool cmp(const candy &x, const candy &y)
{
    return x.B > y.B;
}

int main(int argc, char const *argv[])
{
    freopen("in", "r", stdin);

    cin >> N >> M; //共有M箱，最多带N袋
    
    for (int i = 0; i < M; i++)
        cin >> cbox[i].A >> cbox[i].B;
    sort(cbox, cbox + M, cmp);

    
    for(int i = 0; i < M; i++)
    {
        if(cbox[i].A < N)
        {
            N -= cbox[i].A;
            res += (long long)cbox[i].B * cbox[i].A;
        }
        else {
            res += (long long)cbox[i].B * N;
            break;
        }
    }
    

    cout << res << endl;
    fclose(stdin);
    return 0;
}
