#include <iostream>
#include <cstdlib>
#include <cmath>

using namespace std;

#define elem_t int
#define NaV -2e9

struct Node {
	elem_t v;
	Node * l, *r;
};

struct BS_tree {
	Node * root;
};

void init(BS_tree & t);
Node * make_node(elem_t key);
void swap(elem_t & x, elem_t & y );
Node * insert(Node * p,elem_t key );
void insert(BS_tree & t, elem_t key);
void print_tree(Node * root );
void print_lvl_tree(Node * root );
int print_slice(Node * root, int lvl );
Node * find(Node * p,elem_t key );
Node * find(BS_tree & t ,elem_t key );
Node * max (Node * p);
Node * min (Node * p);
void erase(BS_tree & t,elem_t key );
Node* erase(Node * t,elem_t key );

int main()
{
	BS_tree A;
	init(A);
	insert(A,5);
	print_lvl_tree(A.root);
	insert(A,3);
	print_lvl_tree(A.root);
	insert(A,10);
	print_lvl_tree(A.root);
	insert(A,15);
	print_lvl_tree(A.root);
	erase(A,5);
	print_lvl_tree(A.root);
	
	return 0;
}

Node * max (Node * p){
	if (p==NULL) return NULL;
	if (p->r == NULL) return p;
	return max(p->r);
}
Node * min (Node * p){
	if (p==NULL) return NULL;
	if (p->l == NULL) return p;
	return max(p->l);
}

void init(BS_tree & t){
	t.root = NULL;
	return;
}

void insert(BS_tree & t, elem_t key){
	t.root = insert(t.root,key);
	return;
}

Node * find(BS_tree & t ,elem_t key ){
	return find(t.root, key);
}

Node * find(Node * p,elem_t key ){
	if (!p) return NULL; // if (p==NULL)
	if (p->v == key) return p;
	if (p->v > key) return find(p->l,key); // Ключ должен быть слева
	return find(p->r,key); // Ключ должен быть справа
}

void erase(BS_tree & t,elem_t key ){
	t.root = erase(t.root, key);
	return;
}

Node * erase(Node * p,elem_t key ){
	if (!p) return NULL; // if (p==NULL)
	if (p->v == key){ // Начать удалять
		if (!(p->l) && !(p->r)){ // лист
			delete p;
			return NULL;
		}
		if (!(p->r)){ // Справа пусто
			Node * tmp = p->l;
			delete p;
			return tmp;
		}
		Node * minmax = min(p->r);
		p->v = minmax->v;
		p->r = erase(p->r, minmax->v);
		return p;
	}
	if (p->v > key) p->l = erase(p->l,key); // Ключ должен быть слева
	if (p->v < key) p->r = erase(p->r,key); // Ключ должен быть справа
	return p;
}

Node * insert(Node * p,elem_t key ){
	if (!p) return make_node(key); // if (p==NULL)
	if (p->v == key) return p;
	if (p->v > key) p->l = insert(p->l,key); // Ключ должен быть слева
	if (p->v < key) p->r = insert(p->r,key); // Ключ должен быть справа
	return p;
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









Node * make_node(elem_t key){
	Node * ans = new Node;
	ans->v = key;
	ans->l = ans->r = NULL;
	return ans;
}

void swap(elem_t & x, elem_t & y ){
	elem_t tmp = x;
	x = y;
	y = tmp;
	return;
}




