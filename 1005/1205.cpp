#include <iostream>
using namespace std;
int sudu[9][9];

bool islegal()
{
	for(int i = 1; i < 8; i += 3)
		for(int j = 1; j < 8; j += 3){
			int sum = sudu[i-1][j-1] + sudu[i-1][j] + sudu[i-1][j+1]
					+ sudu[i][j-1] + sudu[i][j] + sudu[i][j+1]
					+ sudu[i+1][j-1] + sudu[i+1][j] + sudu[i+1][j+1];
			if (sum != 45) return false;
			int furtherJudge[9]{0};
			for (int ii = -1; ii <= 1; ++ii)
				for (int jj = -1; jj <= 1; ++jj) 
					furtherJudge[sudu[i + ii][j + jj] - 1] += 1;
			for(int k = 0; k < 9; k++) if(furtherJudge[k] == 0) return false;
		}
	for(int i = 0; i < 9; i++){
		int sum = sudu[i][0] + sudu[i][1] + sudu[i][2]
				+ sudu[i][3] + sudu[i][4] + sudu[i][5]
				+ sudu[i][6] + sudu[i][7] + sudu[i][8];
		if (sum != 45) return false;
		int furtherJudge[9]{0};
		for(int ii = 0; ii < 9; ii++)
			furtherJudge[sudu[i][ii] - 1] += 1;
		for(int k = 0; k < 9; k++) if(furtherJudge[k] == 0) return false;
	}
	for(int j = 0; j < 9; j++){
		int sum = sudu[0][j] + sudu[1][j] + sudu[2][j]
				+ sudu[3][j] + sudu[4][j] + sudu[5][j]
				+ sudu[6][j] + sudu[7][j] + sudu[8][j];
		if (sum != 45) return false;
		int furtherJudge[9]{0};
		for(int jj = 0; jj < 9; jj++)
			furtherJudge[sudu[jj][j] - 1] += 1;
		for(int k = 0; k < 9; k++) if(furtherJudge[k] == 0) return false;
	}
	return true;
}
int main()
{
	int i = 0, num;
	cin >> num;
	while(i < num){
		for(int i = 0; i < 9; i++)
			for(int j = 0; j < 9; j++)
				cin >> sudu[i][j];
		if(islegal()) cout << "Right" << endl;
		else cout << "Wrong" << endl;
		i++;
	}
	return 0;
}