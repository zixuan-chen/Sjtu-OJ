#include <iostream>
#include <algorithm>
using namespace std;

int main(int argc, char const *argv[])
{
	//freopen("in", "r", stdin);
	int N, height[1010];
	char tmp;
	cin >> N;
	cin.get();cin.get();
	for (int i = 0; i < N; ++i)
	{
		cin.get(tmp);
		height[i] = 0;
		while(tmp <= '9' && tmp >= '0'){
			height[i] = height[i] * 10 + tmp - '0';
			cin.get(tmp);
		}
	}

	int left_max[1010], right_max[1010], vol = 0;
	left_max[0] = height[0];
	for (int i = 1; i < N; ++i)
	{
		left_max[i] = max(left_max[i - 1], height[i]);
	}

	right_max[N - 1] = height[N - 1];
	for (int i = N - 2; i >= 0; --i)
	{
		right_max[i] = max(right_max[i + 1], height[i]);
	}

	for (int i = 1; i < N - 1; i++) {
        vol += min(left_max[i], right_max[i]) - height[i];
    }
	cout << vol;
	//fclose(stdin);
	return 0;
}