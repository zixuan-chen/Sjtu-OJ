

template<class T>
void insertSort(T arr[], int size)
{
    int i, j;
    int key;
    for(i = 1; i < size; i++)
    {
        key = arr[i];
        for(j = i - 1; j >= 0 && arr[j] > key; j--)
            arr[j + 1] = arr[j];
        arr[j] = key;
    }
}