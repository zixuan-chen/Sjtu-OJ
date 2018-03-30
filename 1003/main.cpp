#include <iostream>
using namespace std;
int dish[102][102]{0};


int main()
{
	int L,t = 0;
	bool flag = true;
	cin >> L;
	for(int i = 1; i < L + 1; i++)
		for(int j = 1; j < L + 1; j++)
			cin >> dish[i][j];
	while (flag){
		flag = false;
		for(int i = 1; i < L + 1; i++)
			for(int j = 1; j < L + 1; j++){
				if(dish[i][j] == 0){
					if(dish[i-1][j] != 1 && dish[i+1][j] != 1 
						&& dish[i][j-1] != 1&& dish[i][j+1] != 1){
						flag = true;
					} 
					else dish[i][j] = 3;
				}
			}
		for(int i = 1; i < L + 1; i++)
			for(int j = 1; j < L + 1; j++){
				if(dish[i][j] == 3) dish[i][j] = 1;
			}
		t++;
	}
	cout << t;
    return 0;
}
