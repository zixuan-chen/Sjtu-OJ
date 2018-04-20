#include <iostream>
using namespace std;

int main(int argc, char const *argv[])
{
	int len = 100, point;
	char str[len + 1], res[len + 1];
	//freopen("in", "r", stdin);
	while(cin.getline(str, len + 1)){
		point = 0;
		for (int i = len - 1; i >= 0; --i) {
		    if (str[i] == ')') ++point;
		    else if (str[i] == '(') {
	            --point;
	            if (point < 0) {
	                point = 0; res[i] = '$';
	            } else res[i] = ' ';
		    }
		    else res[i] = ' ';
		}
		point = 0;
		for (int i = 0; i < len; ++i)
		{
			if(str[i] == '(') ++point;
			else if (str[i] == ')')
			{
				--point;
				if (point < 0) {
		            point = 0; res[i] = '?';
		        }
		        else res[i] = ' ';
			}
			else res[i] = ' ';
		}
		cout << str << endl;
		cout << res << endl;
	}
	
	//fclose(stdin);
	return 0;
}