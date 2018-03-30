#include <iostream>
using namespace std;
struct node
{
	int data;
	node *next;
	node(int d, node* n):data(d), next(n){}
	node():next(NULL){}
};
class link
{
public:
	node * head;
	node * rear;
	link(){
		head = rear = new node();
	}
	int length()const
	{
		int l = 0;
		node *p = head->next;
		while(p){
			l++;
			p = p->next;
		}
		return l;
	}
	void reverse(){
		node * p = head->next, *q;
		head->next = NULL;
		while(p){
			q = p;
			p = p->next;
			q->next = head->next;
			head->next = q;
		}
	}
	void traverse(){
		node *p = head->next;
		while(p){
			cout << p->data;
			p = p->next;
		}
	}
};



int main()
{
	int tmp;
	link link1, link2, sum;

	while((tmp = cin.get()) != '\n'){
		if(tmp == '.') continue;
		tmp = tmp - '0';
		link1.rear->next = new node(tmp, NULL);
		link1.rear = link1.rear->next;
	}

	while((tmp = cin.get()) != '\n'){
		if(tmp == '.') continue;
		tmp = tmp - '0';
		link2.rear->next = new node(tmp, NULL);
		link2.rear = link2.rear->next;
	}
	link1.reverse();
	link2.reverse();

	node *add1 = link1.head->next, *add2 = link2.head->next;
	int carry = 0, tmpsum;

	if(add1 == NULL && add2 == NULL) {cout << 0; return 0;}
	while(add1 != NULL || add2 != NULL){
		if(add1 == NULL){
			tmpsum = add2->data + carry;
			sum.rear->next = new node(tmpsum % 10, NULL);
			sum.rear = sum.rear->next;
			carry = tmpsum / 10;
			add2 = add2->next;
		}
		else if(add2 == NULL){
			tmpsum = add1->data + carry;
			sum.rear->next = new node(tmpsum % 10, NULL);
			sum.rear = sum.rear->next;
			carry = tmpsum / 10;
			add1 = add1->next;
		}
		else{
			tmpsum = add1->data + add2->data + carry;
			sum.rear->next = new node(tmpsum % 10, NULL);
			sum.rear = sum.rear->next;
			carry = tmpsum / 10;
			add1 = add1->next;
			add2 = add2->next;
		}
	}
	if(carry != 0){
		sum.rear->next = new node(carry, NULL);
		sum.rear = sum.rear->next;
	}

	//reverse
	sum.reverse();
	int l = sum.length();
	node *p = sum.head->next;
	while(p){
		if(l == 2) cout << '.';
		cout << p->data;
		l--;
		p = p->next;
	}

	return 0;
}