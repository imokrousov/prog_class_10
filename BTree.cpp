#include <iostream>

using namespace std;

#define elem_t int
#define t 2

struct BNode {
    elem_t k[2 * t - 1];
    BNode *c[2 * t];
    BNode *p;
    int n;
    bool leaf;
};

struct BTree {
    BNode *root;
};

BNode *allocate_node() {
    BNode *x = new BNode;
    x->p = NULL;
    x->n = 0;
    x->leaf = true;
    return x;
}

void btree_create(BTree &T) {
    BNode *x = allocate_node();
    T.root = x;
    return;
}

pair<BNode *, int> btree_search(BNode *x, elem_t key) {
    int i = 0;
    while (i < x->n && key > x->k[i]) i++;
    if (i < x->n && key == x->k[i])
        return {x, i};
    else if (x->leaf)
        return {NULL, -1};
    else
        return btree_search(x->c[i], key);
}

void btree_split_child(BNode *x,
                       int i) {  // x указатель на незаполненный внутренний
                                 // узел, i номер заполненного сына
    BNode *z = allocate_node();
    z->p = x;
    BNode *y = x->c[i];
    z->leaf = y->leaf;
    z->n = t - 1;
    for (int j = 0; j < t - 1; j++)
        z->k[j] = y->k[j + t];  // j = t-2 => j+? = 2t-2
    if (!y->leaf)
        for (int j = 0; j < t; j++) z->c[j] = y->c[j + t];
    y->n = t - 1;
    for (int j = x->n; j > i + 1; j--)
        x->c[j] = x->c[j - 1];  // сдвиг массива в право
    x->c[i + 1] = z;
    for (int j = x->n - 1; j > i; j--) x->k[j] = x->k[j - 1];
    x->k[i] = y->k[t - 1];
    x->n++;
    return;
}

void btree_insert_nonfull(BNode *x,
                          elem_t key) {  // x -это незаполненный узел
    int i = x->n - 1;
    if (x->leaf) {
        while (i >= 0 && key < x->k[i]) {
            x->k[i + 1] = x->k[i];
            i--;
        }
        x->k[i + 1] = key;
        x->n++;
    } else {  // х не листовой узел
        while (i >= 0 && key < x->k[i]) i--;
        i++;  // В x->c[i] нужно вставлять key
        if (x->c[i]->n == 2 * t - 1) {
            btree_split_child(x, i);
            if (key > x->k[i]) i++;
        }
        btree_insert_nonfull(x->c[i], key);
    }
    return;
}

void btree_insert(BTree &T, elem_t key) {
    BNode *r = T.root;
    if (r->n == 2 * t - 1) {
        BNode *s = allocate_node();
        T.root = s;
        s->leaf = false;
        s->n = 0;
        s->c[0] = r;
        btree_split_child(s, 0);
        btree_insert_nonfull(s, key);
    } else
        btree_insert_nonfull(r, key);
    return;
}

int main() { 
    BTree T;
    btree_create(T);
    int x;
    while (cin>>x){
        auto p = btree_search(T.root,x);
        if (p.first) printf("YES\n"); // cout<< "YES"<<endl;
        else{
            printf("NO\n"); // cout<<"NO"<<endl;
            btree_insert(T,x);
        }
    }
    return 0; 
}