#include <iostream>
using namespace std;

class A
{
private:

	class B
	{
		B()
		{
			cout << "B is constructed" << endl;
		}
		~B()
		{
			cout << "B is destructed" << endl;
		}
	};
	B b();
	A(int i = 0)
	{
		cout << "A is constructed" << endl;
	}
	~A()
	{
		cout << "A is destructed" << endl;
	}

};


int main(int argc, char const *argv[])
{
	A test();
	return 0;
}