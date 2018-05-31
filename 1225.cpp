//quickSort
#include <iostream>
#include <cstdio>
using namespace std;

template <class T>
int divide(T arr[], int low, int high)
{
    if (low >= high)
        return low;
    T key = arr[low];
    while (low < high)
    {
        while (low < high && arr[high] >= key)
            high--;
        if (low < high)
            arr[low] = arr[high];
        while (low < high && arr[low] <= key)
            low++;
        if (low < high)
            arr[high] = arr[low];
    }
    arr[low] = key;
    return low;
}
template <class T>
void quickSort(T arr[], int low, int high)
{
    int mid;
    if (low >= high)
        return;
    mid = divide(arr, low, high);
    quickSort(arr, low, mid - 1);
    quickSort(arr, mid + 1, high);
}


int arr[10000000];
int main(int argc, char const *argv[])
{
    freopen("in", "r", stdin);
    int N;
    cin >> N;
    for(int i = 0; i < N; i++)
    {
        cin >> arr[i];
    }
    quickSort<int>(arr, 0, N - 1);
    int kind = 1;
    for(int i = 1; i< N; i++)
    {
        if(arr[i] != arr[i - 1]) kind++;
    }

    cout << kind;
    fclose(stdin);
    return 0;
}
