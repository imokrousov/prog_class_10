#include <cmath>
#include <cstdlib>
#include <iostream>

using namespace std;

#define elem_t int
#define NaV -2e9

enum Color { RED, BLACK };

struct Node {
    elem_t v;
    Node *l, *r, *p;
    Color c;
};

struct RB_tree {
    Node *root;
    int size;
};

Node *make_NIL();
void init_RB_tree(RB_tree &tree);
void insert(RB_tree &tree, elem_t key);
void swap(elem_t &x, elem_t &y);
void print_tree(Node *root);
void print_lvl_tree(Node *root);
void erase(RB_tree &tree, elem_t key);
int print_slice(Node *root, int lvl);
bool is_NIL(Node *p);
void set_NIL(Node *p, elem_t key);
Node *get_grand_p(Node *pointer);
Node *get_min(Node *pointer);
Node *get_uncle(Node *pointer);
Node *get_bro(Node *pointer);
void right_rotate(Node *x);
void left_rotate(Node *x);
Node* pull_left (Node *x);
Node* pull_right (Node *x);

int main() {
    RB_tree A;
    init_RB_tree(A);
    insert(A, 1);
    print_lvl_tree(A.root);
    insert(A, 2);
    print_lvl_tree(A.root);
    insert(A, 3);
    print_lvl_tree(A.root);
    insert(A, 4);
    print_lvl_tree(A.root);
    insert(A, 5);
    print_lvl_tree(A.root);
    return 0;
}

Node *get_min(Node *pointer){
	if (pointer == NULL || is_NIL(pointer)) return NULL;
	while (!is_NIL(pointer->l) ) pointer= pointer->l;
	return pointer;
}

Node *get_bro(Node *pointer){
	if (pointer->p == NULL) return NULL;
	if (pointer == pointer->p->l)
		return pointer->p->r;
	else
		return pointer->p->l;
}
Node * pull_left(Node *x){
	Node * runner = x;
	if (runner->p)
	if (runner->p->l == runner)
		runner->p->l = runner->l;
	else 
		runner->p->r = runner->l;
	runner->l->p = runner->p;
	Node * tmp = runner->l;
	delete runner->r;
	delete runner;
	return tmp;
}
Node * pull_right (Node *x){
	Node * runner = x;
	if (runner->p)
			if (runner->p->l == runner)
				runner->p->l = runner->r;
			else 
				runner->p->r = runner->r;
	runner->r->p = runner->p;
	Node * tmp = runner->r;
	delete runner->l;
	delete runner;
	return tmp;
}

void erase(RB_tree &tree, elem_t key){
	Node * runner = tree.root;
	while (!is_NIL(runner)) {
		if (runner->v == key) break;
        if (runner->v > key)
            runner = runner->l;
        else
            runner = runner->r;
    }
	// Два случая оказаться здесь
	if (is_NIL(runner)) return;
	// runner смотрит на удаляемый узел
	bool fix_flag = false;
	if (runner->c == BLACK) fix_flag = true; 
	if (is_NIL(runner->l) && is_NIL(runner->r)){ // Удалялся лист
		delete runner->l;
		delete runner->r;
		runner->l = runner->r = NULL;
		runner->v = NaV;
		runner->c = BLACK;
	}
	if (!is_NIL(runner->l) && is_NIL(runner->r))// Слева есть справа нет
		runner = pull_left(runner);
	if (is_NIL(runner->l) && !is_NIL(runner->r))// Справа есть слева нет
		runner = pull_right(runner);
	
	if (!is_NIL(runner->l) && !is_NIL(runner->r)){
		Node * minimax = get_min (runner->r);
		swap(runner->v,minimax->v);
		runner = pull_right(minimax);
	}
	
}


Node *get_grand_p(Node *pointer) {
    if ((pointer != NULL) && (pointer->p != NULL))
        return pointer->p->p;
    else
        return NULL;
}

Node *get_uncle(Node *pointer) {
    Node *grand_p = get_grand_p(pointer);
    if (grand_p == NULL) return NULL;
    if (pointer->p == grand_p->l)
        return grand_p->r;
    else
        return grand_p->l;
}

void set_NIL(Node *point, elem_t key) {
    point->v = key;
    point->c = RED;
    point->l = make_NIL();
    point->l->p = point;
    point->r = make_NIL();
    point->r->p = point;
    return;
}

bool is_NIL(Node *p) { return p->l == NULL && p->r == NULL; }

void print_tree(Node *root) {
    if (root == NULL) return;
    cout << root->v << ' ';
    print_tree(root->l);
    print_tree(root->r);
    return;
}

int print_slice(Node *root, int lvl) {
    if (root == NULL) return 0;
    if (lvl == 0) {
        cout << "(" << root->v << ',' << root->c << ")";
        return 1;
    }
    return print_slice(root->l, lvl - 1) + print_slice(root->r, lvl - 1);
}

void print_lvl_tree(Node *root) {
    int i = 0;
    while (print_slice(root, i++) != 0) {
        cout << endl;
    }
    cout << endl;
    return;
}

void insert(RB_tree &tree, elem_t key) {
    Node *runner = tree.root;
    while (!is_NIL(runner)) {
        if (runner->v == key) return;
        if (runner->v > key)
            runner = runner->l;
        else
            runner = runner->r;
    }
    set_NIL(runner, key);
    while (runner) {
        if (runner->p == NULL) {  // Вставка в корень
            runner->c = BLACK;
            return;
        }
        if (runner->p->c == BLACK) return;  // Родитель уже черный
        Node *u = get_uncle(runner);
        Node *g = get_grand_p(runner);
        if ((u != NULL) && (u->c == RED)) {  // Красные дядя и отец
            runner->p->c = BLACK;
            u->c = BLACK;
            g->c = RED;
            runner = g;
            continue;
        }
        // Далее следуют случаи, в которых отец красный, но дядя черный
        if ((runner == runner->p->r) &&
            (runner->p == g->l)) {  // Отец слева, дед справа
            left_rotate(runner->p);
            runner = runner->l;
        } else if ((runner == runner->p->l) &&
                   (runner->p == g->r)) {  // Отец справа, дед слева
            right_rotate(runner->p);
            runner = runner->r;
        }
        runner->p->c = BLACK;
        g->c = RED;

        if ((runner == runner->p->l) && (runner->p == g->l))
            right_rotate(g);
        else
            left_rotate(g);
        if (runner->p->p == NULL) tree.root = runner->p; // Обновление корня после поворота 
        return;
    }
}

void right_rotate(Node *x) {
    Node *left_ch = x->r;
    left_ch->p = x->p;
    if (x->p != NULL)  // Rotate with not root
        if (x->p->l == x)
            x->p->l = left_ch;
        else
            x->p->r = left_ch;
    x->r = left_ch->l;
    if (left_ch->l != NULL) left_ch->l->p = x;
    x->p = left_ch;
    left_ch->l = x;
}

void left_rotate(Node *x) {
    Node *right_ch = x->r;
    right_ch->p = x->p;
    if (x->p != NULL)  // Rotate with not root
        if (x->p->l == x)
            x->p->l = right_ch;
        else
            x->p->r = right_ch;
    x->r = right_ch->l;
    if (right_ch->l != NULL) right_ch->l->p = x;
    x->p = right_ch;
    right_ch->l = x;
}

void init_RB_tree(RB_tree &tree) {
    tree.root = make_NIL();
    tree.size = 0;
    return;
}

Node *make_NIL() {
    Node *ans = new Node;
    ans->l = ans->r = ans->p = NULL;
    ans->c = BLACK;
    ans->v = 0;
    return ans;
}

void swap(elem_t &x, elem_t &y) {
    elem_t tmp = x;
    x = y;
    y = tmp;
    return;
}
