#ifndef SEQSTACK_CPP_INCLUDED
#define SEQSTACK_CPP_INCLUDED

#include "seqStack.h"

template <class elemType>
void seqStack<elemType>::doubleSpace()
{
	elemType * tmp = new elemType[2 * maxSize];
	for(int i = 0; i < maxSize; i++)
		tmp[i] = elem[i];
	delete elem;
	elem = tmp;
	maxSize *= 2;
}

template <class elemType>
seqStack<elemType>::seqStack(int initSize)
{
	if(initSize < 0) throw illegalSize();
	elem = new elemType[initSize];
	maxSize = initSize;
	head = -1;
}

template <class elemType>
bool seqStack<elemType>::isEmpty() const
{
	return head == -1;
}

template <class elemType>
elemType seqStack<elemType>::top() const
{
	if(isEmpty()) throw outOfBound();
	return elem[head];
}

template <class elemType>
elemType seqStack<elemType>::pop()
{
	if(isEmpty()) throw outOfBound();
	return elem[head--];
}

template <class elemType>
void seqStack<elemType>::push(const elemType &x)
{
	if(head == maxSize - 1) doubleSpace();
	elem[++head] = x;
}
#endif
