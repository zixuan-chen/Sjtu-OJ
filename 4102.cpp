#include <iostream>
using namespace std;


int k, n, cur;
int min = 0, max = 0;
int maxl = 0, curl = 0;

int main(int argc, char const *argv[])
{
    cin >> k >> n;
    for(int i = 0; i < n; i++)
    {
        cin >> cur;
        max = (cur > max)? cur : max;
        min = (cur < min)? cur : min;
        if(max - min >= k) {
            maxl = (curl > maxl)? curl : maxl;
            min = max = cur;
            curl = 1;
        }
        else{
            curl++;
        }
    } 

    cout << maxl;
    return 0;
}
