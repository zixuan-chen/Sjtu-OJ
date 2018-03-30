#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED

#include <iostream>
#include <cstdio>

using namespace std;

class outOfBound {};
class illegalSize {};
template <class elemType>
class Stack
{
public:
	virtual bool isEmpty() const = 0;
	virtual elemType top() const = 0;
	virtual elemType pop()  = 0;
	virtual void push(const elemType &x) = 0;
	virtual ~Stack(){};
};

#endif
