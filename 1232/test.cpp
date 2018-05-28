#include <iostream>
#include <math.h>
using namespace std;
static int matrix[10][10];
int findPositon(int num, int dir)
{
	//dir = 0, 1, 2, 3
	int x = (sqrt(8 * num - 7) + 1) / 2;
	int y = num - x * (x - 1) / 2; //start from 1
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


int main(){
	for(int i = 0; i < 10; i++)
	{
		for(int j = 0; j < 10; j++)
			cout << matrix[i][j] << ' ';
		cout << endl;
	}
	return 0;
}