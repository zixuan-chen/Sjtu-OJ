#include <iostream>
using namespace std;

struct Node
{
	Node *left, *right;
};

int main(int argc, char const *argv[])
{
	Node *p = NULL;
	cout << (p->right == NULL) << endl;
	return 0;
}