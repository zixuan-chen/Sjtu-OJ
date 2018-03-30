#ifndef LINKSTACK_H_INCLUDED
#define LINKSTACK_H_INCLUDED

#include "Stack.h"

template <class elemType>
class linkStack : public Stack<elemType>
{
private:
	struct node
	{
		elemType data;
		node *next;
		node(const elemType &x, node *N = NULL):data(x), next(N){}
		node():next(NULL){}
		~node(){}
	};

	node *head;
public:
	linkStack();
	bool isEmpty() const;
	elemType top() const;
	elemType pop();
	void push(const elemType &x);
	~linkStack();
};
#include "linkStack.cpp"
#endif
