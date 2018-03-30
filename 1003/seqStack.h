#ifndef SEQSTACK_H_INCLUDED
#define SEQSTACK_H_INCLUDED

#include "Stack.h"

template <class elemType>
class seqStack : public Stack<elemType>
{
private:
	elemType * elem;
	int maxSize;
	int head;
	void doubleSpace();

public:
	seqStack(int initSize = 10);
	bool isEmpty() const;
	elemType top() const;
	elemType pop();
	void push(const elemType &x);
	~seqStack(){delete elem;}
};
#include "seqStack.cpp"
#endif
