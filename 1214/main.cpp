#include <stdio.h>
#include <iostream>
#include <fstream>
using namespace std;
template <class elemType>
class linkQueue
{
private:
	struct node
	{
		elemType data;
		node * next;
		node(): next(NULL){}
		node(const elemType &x, node *tmp):data(x),next(tmp){}
		~node(){}
	};

	node *front, *rear;
public:
	linkQueue():front(NULL), rear(NULL) {}
	//Note that the pointer front, rear is not preset NULL automatically,
	//which means we should set it to NULL manually!
	bool isEmpty() const {return front == NULL;}
	void enQueue(const elemType& x);
	elemType deQueue();
	elemType getHead() const{return front->data;}
	~linkQueue();
};
template <class elemType>
void linkQueue<elemType>::enQueue(const elemType& x)
{
    if(rear == NULL)
        front = rear = new node(x, NULL);
    else{
        rear->next = new node(x, NULL);
        rear = rear->next;
    }
}

template <class elemType>
elemType linkQueue<elemType>::deQueue()
{
    node *p = front;
    elemType x = p->data;
    front = front->next;
    delete p;
    if (front == NULL) rear = NULL;
    return x;

}

template <class elemType>
linkQueue<elemType>::~linkQueue()
{
	while(!isEmpty()) deQueue();
}


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
    	cout << t->data << ' ';
    	Node* tmp = t->left;
    	while(tmp!= NULL){
    		preOrder(tmp);
    		tmp = tmp->right;
    	}
    }
    void postOrder( Node *t )  const{

    	Node* tmp = t->left;
    	while(tmp!= NULL){
    		postOrder(tmp);
    		tmp = tmp->right;
    	}
    	cout << t->data << ' ';
    }
    void levelOrder(Node * t) const{
    	linkQueue<Node*> l;
    	Node *tmp;
    	if(t == NULL) return;
    	l.enQueue(t);
    	while(!l.isEmpty()){
    		tmp = l.deQueue();
    		while(tmp != NULL){
    			cout << tmp->data << ' ';
    			if (tmp->left != NULL) l.enQueue(tmp->left);
    			tmp = tmp->right;
    		}
    	}
    }
    void createTree(Node * & t);

public:
	binaryTree(): root(NULL) {}
	binaryTree(const Type &value){root = new Node(value);};
	binaryTree(Node *p){root = p;}
	~binaryTree(){clear(root);}

	bool isEmpty(){return root == NULL;}
	int size() const {return size(root);}
	int height() const {return height(root);}
	bool isCBT()const;
	void clear()
	{
		if(root != NULL) clear(root);
		root = NULL;
	}
    void preOrder() const{preOrder(root);}
    void postOrder() const{postOrder(root);}
    void levelOrder() const{levelOrder(root);}
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
void binaryTree<Type>::createTree(Node * & t)
{
    int N, left, right, i = 1, weight;
    Node *arr[100001];
	int isChild[100001];
	//linkStack<Node*> s;
    //ifstream fin("in");
    cin >> N;
    for(int j = 1; j <= N; j++) arr[j] = new Node();
    //create tree
	while(i <= N){
		cin >> left >> right >> weight;
		arr[i]->data = weight;
		if(left != 0){
			arr[i]->left = arr[left];
			isChild[left] = 1;
		}
		if(right != 0){
			arr[i]->right = arr[right];
			isChild[right] = 1;
		}
		i++;
	}
	
	//determine which node is root
	for(int r = 1; r <= N; r++)
	{
		if(!isChild[r]){
			t = arr[r];
			break;
		}
	}

}

int main()
{
    //freopen("in", "r", stdin);
	binaryTree<int> tree;
	tree.createTree();
	tree.preOrder();cout << endl;
	tree.postOrder();cout << endl;
	tree.levelOrder();cout << endl;
	//fclose(stdin);
	return 0;
}
