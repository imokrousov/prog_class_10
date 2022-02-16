#include <iostream>
#include <cstdlib>
#include <cmath>

using namespace std;

#define elem_t int
#define NaV -2e9

enum Color {RED, BLACK};

struct Node {
	elem_t v;
	Node * l, *r, *p;
	Color c;
};


struct RB_tree {
	Node * root;
	int size;
};

Node * make_NIL(elem_t key);
void init_RB_tree(RB_tree & tree);
elem_t max_elem(RB_tree & tree);
void insert(RB_tree & tree, elem_t key);
void swap(elem_t & x, elem_t & y );
void print_tree(Node * root );
void print_lvl_tree(Node * root );
void erase(RB_tree & tree, elem_t key);
int print_slice(Node * root, int lvl );
bool is_NIL (Node * p);
void set_NIL (Node * p, elem_t key);

int main()
{
	Heap_tree A;
	init_Heap_tree(A);
	insert(A,100);
	print_tree(A.root); cout<<endl;
	insert(A,50);
	print_tree(A.root); cout<<endl;
	insert(A,40);
	print_tree(A.root); cout<<endl;
	insert(A,3);
	print_tree(A.root); cout<<endl;
	insert(A,20);
	print_lvl_tree(A.root); cout<<endl;
	pop(A);
	print_lvl_tree(A.root); cout<<endl;
	insert(A,200);
	print_lvl_tree(A.root); cout<<endl;
	return 0;
}

void set_NIL (Node * point, elem_t key){
	point->v = key;
	point->c = RED;
	point->l = make_NIL();
	point->l->p = point;
	point->r = make_NIL();
	point->r->p = point;
	return;
}

bool is_NIL (Node * p){
	return p->l == NULL && p->r == NULL;
}

void print_tree(Node * root ){
	if (root == NULL) return;
	cout<< root->v<<' ';
	print_tree(root->l);
	print_tree(root->r);
	return;
}

int print_slice(Node * root, int lvl ){
	if (root == NULL) return 0;
	if (lvl == 0) {
		cout<< root->v<<' ';
		return 1;
	}
	return print_slice(root->l,lvl-1)+print_slice(root->r,lvl-1);
}

void print_lvl_tree(Node * root ){
	int i = 0;
	while (print_slice(root, i++)!= 0) {cout<<endl;}
	cout<<endl;
	return;
}


void insert(RB_tree & tree, elem_t key){
	Node * runner = tree.root;
	while (!is_NIL(runner)){
		if (runner->v == key) return;
		if (runner->v > key) runner = runner->l;
		else runner = runner->r;
	}
	set_NIL(runner,key);	
	if (runner == tree.root) { // Вставка в корень
		runner->c = BLACK;
		return;
	}
	while (runner->p->c == RED){
		if (runner->p->p != NULL) {// Есть дед
			Node * ded = runner->p->p; 
			if (runner->p == ded->l)  {
				Node * dyadya = ded->r;
				if (dyadya->c == RED) { // Случай 1 перекраски
					runner->p->c = BLACK;
					dyadya->c = BLACK;
					ded->c = RED
					runner = ded; // Переход наверх
				}
				else // Дядя черный
			}
		}
	}
}

void right_rotate (Node * x){
	Node * predOk = x->p;
	bool left = (predOk->l == x);
	Node * y = x->l;
	Node * C = y->r;
	x->l = C;
	C->p = x;
	y->r = x;
	x->p = y;
	if (left) predOk->l = y;
	else predOk->r = y;
	y->p = predOk;
}


void left_rotate (Node * x){
	Node * predOk = x->p;
	bool left = (predOk->l == x);
	Node * y = x->r;
	Node * C = y->l;
	x->r = C;
	C->p = x;
	y->l = x;
	x->p = y;
	if (left) predOk->l = y;
	else predOk->r = y;
	y->p = predOk;
}

elem_t max_elem(Heap_tree & tree){
	
}

void init_RB_tree(RB_tree & tree){
	tree.root = make_NIL();
	tree.size = 0;
	return;
}

Node * make_NIL(){
	Node * ans = new Node;
	ans->l = ans->r = ans->p = NULL;
	ans->c = BLACK;
	return ans;
}

void swap(elem_t & x, elem_t & y ){
	elem_t tmp = x;
	x = y;
	y = tmp;
	return;
}



