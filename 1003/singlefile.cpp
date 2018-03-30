#include <iostream>
#include <fstream>
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


int main()
{
    printf("seqStack\n");
    seqStack<int> st;
    for (int i = 0; i < 15; ++ i) {
        st.push(i);
    }
    while (!st.isEmpty())
        printf("%d ", st.pop());
    return 0;
}
