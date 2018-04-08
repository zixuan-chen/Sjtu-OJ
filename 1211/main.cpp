#include <stdio.h>
#include <iostream>
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
    bool isEmpty() const {return rear == front;}
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

	void clear(Node *t);
    int height( Node *t ) const;
    int size( Node *t ) const;
    void preOrder( Node *t )  const{
        if(t == NULL) return;
        cout << t->data << ' ';
        preOrder(t->left);
        preOrder(t->right);
    }
    void postOrder( Node *t )  const;
    void midOrder( Node *t ) const;
    void createTree(Node *t);
    bool isCBT(Node *t);

public:
	binaryTree(): root(NULL) {}
	binaryTree(const Type &value){root = new Node(value);};
	binaryTree(Node *p){root = p;}
	~binaryTree(){clear(root);}

	bool isEmpty(){return root == NULL;}
	int size() const {return size(root);}
	int height() const {return height(root);}
	bool isCBT(){clear(root);return isCBT(root);}
	void clear()
	{
		if(root != NULL) clear(root);
		root = NULL;
	}
    void preOrder() const{
	    cout << "preOrder traversal: ";
	    preOrder(root);
	    cout << endl;
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
bool binaryTree<Type>::isCBT(Node *t)
{
	int N, left, right, i = 1,check = 0;
	seqQueue<Node *> q;
	Node *tmp;
    Node *arr[100001];
    bool flag = true;
	int isChild[100001];

    cin >> N;
	while(i <= N){
        if(arr[i] == NULL) arr[i] = new Node;
		cin >> left >> right;
		//cout << "left = " <<left << "; right = " <<right << endl;
		if(left != 0){
		    if(arr[left] == NULL) arr[left] = new Node;
			arr[i]->left = arr[left];
			isChild[left] = 1;
		}
		if(right != 0){
		    if(arr[right] == NULL) arr[right] = new Node;
			arr[i]->right = arr[right];
			isChild[right] = 1;
		}
		i++;
	}

	for(int r = 1; r <= N; r++)
	{
	    //cout << isChild[r] << ' ';
		if(!isChild[r]){
			t = arr[r];
			//cout << "r = " << r << endl;
            //cout << "\nin creatTree: t == NULL : " << (t == NULL) << endl;
            //preOrder(t);
			break;
		}
	}
	//cout << "\nin is CBT: t == NULL: " << (t == NULL) << endl;
	flag = true;
	if (t == NULL) return true;
	q.enQueue(t);
	while(!q.isEmpty())
	{
		tmp = q.deQueue();
		if((flag == false)&&(tmp->left != NULL || tmp->right != NULL))
            return false;
		if(tmp->left != NULL && tmp->right != NULL){
			q.enQueue(tmp->left);
			q.enQueue(tmp->right);
		}
		else if(tmp->left == NULL && tmp->right != NULL) return false;
		else if(tmp->left != NULL && tmp->right == NULL){
			flag = false;
            q.enQueue(tmp->left);
		}
		check++;
	}
	return true;
}

int main()
{
	binaryTree<int> tree;
	if(tree.isCBT()) cout << 'Y';
	else cout << 'N';
	return 0;
}
