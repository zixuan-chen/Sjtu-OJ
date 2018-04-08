#include <iostream>
#include <fstream>
using namespace std;
template <class elemType>
class seqQueue
{
private:
	elemType * elem;
	int maxSize;
	int front, rear;
	void doubleSpace(){
		elemType * tmp = new elemType[2 * maxSize];
		int i = 0;
		while((i + front) % maxSize != rear){
			tmp[i] = elem[(i + front + 1) % maxSize];
			i++;
		}
		front = -1;
		rear = i - 1;
		maxSize *= 2;
		delete [] elem;
		elem = tmp;
	}
public:
	seqQueue(int m = 10){
		elem = new elemType[m];
		maxSize = m;
		front = rear = -1;
	}
	int getLength(){
		int i = 0;
		while((i + front) % maxSize != rear){
			i++;
		}
		return i;
	}
	void enQueue(const elemType& x){
		if((rear + 1) % maxSize == front) doubleSpace();
		rear = (rear + 1) % maxSize;
		elem[rear] = x;
	}

	elemType deQueue(){
		front = (front + 1) % maxSize;
		return elem[front];
	}
	~seqQueue(){delete[] elem;}
};

template <class Type>
class binaryTree
{
private:
	struct Node
	{
		Type data;
		Node *left, *right;
		Node():left(NULL), right(NULL) {}
		Node(Type d, Node *l = NULL, Node *r = NULL):
			 data(d), left(l), right(r) {}
		~Node() {}
	};

	Node *root;

	void clear(Node * n);
    int height( Node *t ) const;
    int size( Node *t ) const;
    void preOrder( Node *t )  const;
    void postOrder( Node *t )  const;
    void midOrder( Node *t ) const;
    void createTree(Node *t);
    bool isCBT(Node *t) const;
public:
	binaryTree(): root(NULL) {}
	binaryTree(const Type &value){root = new Node(value);};
	binaryTree(Node *p){root = p;}
	~binaryTree(){clear(root);}

	bool isEmpty(){return root == NULL;}
	int size() const {return size(root);}
	int height() const {return height(root);}
	bool isCBT() const {return isCBT(root);}
	void clear()
	{
		if(root != NULL) clear(root);
		root = NULL;
	}
	void createTree(){createTree(root);}
};

template<class Type>
void binaryTree<Type>::clear(Node * t)
{
	if(t == NULL) return;
	clear(t->left);
	clear(t->right);
	delete t;
}

template<class Type>
int binaryTree<Type>::height( Node *t ) const
{
	if(t == NULL) return 0;
	int lh = height(t->left), rh = height(t->right);
	return 1 + ((lh > rh)? lh : rh);
}

template<class Type>
int binaryTree<Type>::size( Node *t ) const
{
	if(t == NULL) return 0;
	else return 1 + size(t->left) + size(t->right);
}

template<class Type>
bool binaryTree<Type>::isCBT(Node *t) const
{
	if (t == NULL) return true;
	seqQueue<Node *> q;
	int size = size(t), check = 0;
	Node *tmp
	q.enQueue(t);
	while(!q.isEmpty())
	{
		tmp = q.deQueue();
		if(tmp->left != NULL && tmp->right != NULL){
			q.enQueue(tmp->left);
			q.enQueue(tmp->right);
		}
		if(tmp->left == NULL && tmp->right == NULL);
		if(tmp->left == NULL && tmp->right != NULL) return false;
		else{
			return size == check + q.getLength() + 2;
		}
		check++;
	}
	return true;
}

template<class Type>
void binaryTree<Type>::createTree(Node *t)
{
	int N, left, right, i = 1;
	ifstream fin("in");
	fin >> N;
	Node *arr[100001];
	int isRoot[100001]{1};
	while(i <= N){
		arr[i] = new Node;
		fin >> left >> right;
		if(left != 0){
			arr[i]->left = arr[left];
			isRoot[left] = 0;
		}
		if(right != 0){
			arr[i]->right = arr[right];
			isRoot[right] = 0;
		}
		i++;
	}
	clear(t);
	for(int r = 1; r <= N; r++)
		if(isRoot[r]){
			t = arr[r];
			return;
		}
}

int main()
{
	binaryTree tree;
	tree.createTree();
	if(tree.isCBT()) cout << 'Y';
	else cout << 'N';
	return 0;
}