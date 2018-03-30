#ifndef LINKSTACK_CPP_INCLUDED
#define LINKSTACK_CPP_INCLUDED

#include "linkStack.h"
/**

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
**/


template <class elemType>
linkStack<elemType>::linkStack():head(NULL){}

template <class elemType>
bool linkStack<elemType>::isEmpty() const
{
	return (head == NULL);
}

template <class elemType>
elemType linkStack<elemType>::top() const
{
	if(head == NULL) throw outOfBound();
	return head->data;
}

template <class elemType>
elemType linkStack<elemType>::pop()
{
    if (head == NULL)
        throw outOfBound();
    node * ptr = head;
    elemType ans = ptr->data;
    head = head->next;
    delete ptr;
    return ans;
}

template <class elemType>
void linkStack<elemType>::push(const elemType &x)
{
	head = new node (x, head);
}

template <class elemType>
linkStack<elemType>::~linkStack()
{
	while(!isEmpty()) pop();
}

#endif
