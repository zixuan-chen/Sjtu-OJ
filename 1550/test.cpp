#include <iostream>
using namespace std;

void sort(int *arr, int size){
	int min, tmp;
	for(int i = 0; i < size; i++){
		tmp = arr[i];
		min = i;
		for(int j = i; j < size; j++){
			if(arr[j] < arr[min]) min = j;
		}
		arr[i] = arr[min];
		arr[min] = tmp;
	}
}

int main(int argc, char const *argv[])
{
	int arr[5]{5,4,3,2,1};
	sort(arr, 5);
	for (int i = 0; i < 5; ++i)
	{
		cout << arr[i];
		/* code */
	}
	
	return 0;
}