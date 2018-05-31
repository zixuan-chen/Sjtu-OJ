#include <iostream>
#include <cstdio>
using namespace std;
const int MAX_INT = 2147483647;
template <class Type>
class priorityQueue
{
  private:
	Type *array;
	int currentSize;
	int maxSize;

	void doubleSpace();
	void buildHeap();
	void percolateDown(int hole);
	void percolateUp(int hole);

  public:
	priorityQueue(int capacity = 100)
	{
		array = new Type[capacity];
		maxSize = capacity;
		currentSize = 0;
		//这里的currentSize值得是优先级队列的长度，整个数组的当前长度为currentSize + 1;
	}
	priorityQueue(const Type *data, int size);
	~priorityQueue() { delete array; }
	bool isEmpty() const { return currentSize == 0; }
	void enQueue(const Type &x);
	Type deQueue();
	Type getHead() { return array[1]; }
	int find(Type x, Type MAX);   //找出优先级值大于x的最小的元素，输出其下标
	void decrease(int i, Type v); //将第i个节点的优先级值减少v。
};

template <class Type>
void priorityQueue<Type>::doubleSpace()
{
	Type *tmp = array;
	array = new Type[2 * maxSize];
	for (int i = 0; i <= currentSize; ++i)
	{
		array[i] = tmp[i];
	}
	maxSize *= 2;
	delete[] tmp;
}

template <class Type>
void priorityQueue<Type>::enQueue(const Type &x)
{
	if (currentSize + 1 == maxSize)
		doubleSpace();
	int hole = ++currentSize;
	array[hole] = x;
	percolateUp(hole);
}

template <class Type>
void priorityQueue<Type>::percolateDown(int hole)
{
	if (hole < 1 || hole > currentSize)
		return;
	Type tmp = array[hole];
	int child;
	while (hole * 2 <= currentSize)
	{
		child = hole * 2;
		if (child != currentSize && array[child + 1] < array[child])
			child++;

		if (array[child] < tmp)
		{
			array[hole] = array[child];
			hole = child;
		}
		else
			break;
	}
	array[hole] = tmp;
}
template <class Type>
void priorityQueue<Type>::percolateUp(int hole)
{
	Type tmp = array[hole];
	while (hole != 1)
	{
		if (array[hole / 2] > tmp)
		{
			array[hole] = array[hole / 2];
			hole /= 2;
		}
		else
			break;
	}
	array[hole] = tmp;
}
template <class Type>
Type priorityQueue<Type>::deQueue()
{
	Type tmp = array[1];
	array[1] = array[currentSize--];
	percolateDown(1);
	return tmp;
}

template <class Type>
void priorityQueue<Type>::buildHeap()
{
	for (int i = currentSize / 2; i > 0; --i)
	{
		percolateDown(i);
	}
}

template <class Type>
priorityQueue<Type>::priorityQueue(const Type *data, int size)
{
	maxSize = size + 10;
	currentSize = size;
	array = new Type[maxSize];

	for (int i = 0; i < size; ++i)
	{
		array[i + 1] = data[i];
	}
	buildHeap();
}

template <class Type>
int priorityQueue<Type>::find(Type x, Type MAX)
{
	int idx = currentSize;
	Type min = MAX;
	for (int i = 1; i <= currentSize; ++i)
	{
		if (array[i] > x && array[i] < min)
		{
			idx = i;
			min = array[i];
		}
	}
	return idx;
}

template <class Type>
void priorityQueue<Type>::decrease(int i, Type v)
{
	array[i] -= v;
	percolateUp(i);
}

int main()
{
	//freopen("in", "r", stdin);

	int N;
	char command[8];
	int op1;
	priorityQueue<int> q;
	cin >> N;
	cin.get();
	while (N-- > 0)
	{
		cin >> command[0];
		switch (command[0])
		{
		case 'i':
			cin.getline(command, 7, ' ');
			cin >> op1;
			cin.get();
			//cout << "op1 = " << op1 << endl;
			q.enQueue(op1);
			break;

		case 'm':
			cin.getline(command, 7, '\n');
			cout << q.getHead() << endl;
			break;

		case 'd':
			cin.getline(command, 7, '\n');
			q.deQueue();
			break;
		default: cout << "invalid command!" << endl;
		}

	}

	//fclose(stdin);
	
	return 0;
}
