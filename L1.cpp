#include <iostream>
#include <cmath>
#include <set>
#include <algorithm>
#include <fstream>

using namespace std;

struct Node{
	int v; // value
	Node * next;
};

struct L1 {
	Node * head;
	Node * tail;
	unsigned int size;
};

void init (L1 & list);
Node * make_node (int key);
void push_front(L1 & list, int key);
void push_back(L1 & list, int key);
Node* get_by_index(L1 & list, int index);
void push_by_index(L1 & list, int index, int key);
void print(L1 & list);




int main()
{
	L1 A;
	init(A);
	for (int i = 1; i < 6; i++) push_back(A,i);
	print(A);
	push_by_index(A,3, -10);
	print(A);
	return 0;
}

void print(L1 & list){
	Node * runner = list.head;
	for (int i = 0; i < list.size; i++) {
		cout<< runner->v << " -> ";
		runner= runner->next;
	}
	cout<< "NULL\n";
	return;
}

void push_by_index(L1 & list, int index, int key){
	if (index == 0) {
		push_front(list, key);
		return;
	}
	if (index == list.size){
		push_back(list, key);
		return;
	}
	Node * p, *q;
	p = get_by_index(list, index-1);
	q = p->next;
	Node * new_node = make_node(key);
	new_node->next = q;
	p->next = new_node;
	list.size++;
	return;
}


Node* get_by_index(L1 & list, int index){
	if (index < 0 || index >= list.size) return NULL;
	if (index == list.size -1) return list.tail;
	Node * runner = list.head;
	for (int i =0; i < index; i++) runner = runner->next;
	return runner;
}

void push_back(L1 & list, int key){
	if (list.size == 0) {
		push_front(list,key);
		return;
	}
	Node * new_node = make_node(key);
	list.tail->next = new_node;
	list.tail = new_node;
	list.size++;
	return;
}

void push_front(L1 & list, int key){
	Node * new_node = make_node(key);
	new_node->next = list.head;
	list.head = new_node;
	if (list.size == 0) list.tail = new_node;
	list.size++;
	return;
}

void init (L1 & list){
	list.head = NULL;
	list.tail = NULL;
	list.size = 0;
	return;
}

Node * make_node (int key){
	Node * p = new Node;
	p->v = key;     // (*p).v = key;
	p->next = NULL; // (*p).next = NULL;
	return p;
}
