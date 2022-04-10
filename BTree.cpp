#include <iostream>

using namespace std;

#define elem_t int
#define t 2

struct BNode {
    elem_t key[2 * t - 1];
    BNode *child[2 * t];
    BNode *p;
    int size;
    bool leaf;
};

struct BTree {
    BNode *root;
};

BNode *allocate_node();
void btree_create(BTree &);
pair <BNode*, int> btree_search(BNode*, elem_t);
void btree_split_child(BNode*, int);
void btree_insert_nonfull(BNode*, elem_t);
void btree_insert(BTree &, elem_t);
void btree_erase(BNode*, elem_t);

void left_rotate(BNode*, int);
void right_rotate(BNode*, int);

int main () {
    int buf;
    BTree A;
    btree_create(A);

    while (cin >> buf) {
        if (btree_search(A.root, buf).second != -1) {
            cout << "YES" << endl;
        } else {
            cout << "NO" << endl;

            btree_insert(A, buf);
        }
    }

    return 0;
}

BNode *allocate_node() {
    BNode *x = new BNode;
    x->p = NULL;
    x->size = 0;
    x->leaf = true;

    return x;
}

void btree_create(BTree &T) {
    BNode *x = allocate_node();
    T.root = x;

    return;
}

pair<BNode *, int> btree_search(BNode* x, elem_t key) {
    int i = 0;

    while ((i < x->size) && (key > x->key[i])) {
        i++;
    }

    if ((i < x->size) && (key == x->key[i])) {
        return {x, i};
    } else if (x->leaf) {
        return {NULL, -1};
    } else {
        return btree_search(x->child[i], key);
    }
}

void btree_split_child(BNode* x, int i) {  // x указатель на незаполненный внутренний
    // узел, i номер заполненного сына
    BNode *z = allocate_node();
    z->p = x;
    BNode *y = x->child[i];
    z->leaf = y->leaf;
    z->size = t - 1;

    for (int j = 0; j < t - 1; j++) {
        z->key[j] = y->key[j + t];  // j = t-2 => j+? = 2t-2
    }

    if (!y->leaf) {
        for (int j = 0; j < t; j++) {
            z->child[j] = y->child[j + t];
        }

        y->size = t - 1;
    }

    for (int j = x->size; j > i + 1; j--) {
        x->child[j] = x->child[j - 1];  // сдвиг массива в право
    }
    x->child[i + 1] = z;

    for (int j = x->size - 1; j > i; j--) {
        x->key[j] = x->key[j - 1];
    }

    x->key[i] = y->key[t - 1];
    x->size++;

    return;
}

void btree_insert_nonfull(BNode* x, elem_t key) {  // x -это незаполненный узел
    int i = x->size - 1;

    if (x->leaf) {
        while (i >= 0 && (key < x->key[i])) {
            x->key[i + 1] = x->key[i];
            i--;
        }

        x->key[i + 1] = key;
        x->size++;
    } else {  // х не листовой узел
        while (i >= 0 && key < x->key[i]) {
            i--;
        }

        i++; // В x->c[i] нужно вставлять key

        if (x->child[i]->size == 2*t-1) {
            btree_split_child(x, i);

            if (key > x->key[i]) {
                i++;
            }
        }

        btree_insert_nonfull(x->child[i], key);
    }

    return;
}

void btree_insert(BTree &T, elem_t key) {
    BNode* r = T.root;

    if (r->size == 2 * t - 1) {
        BNode * s = allocate_node();
        T.root = s;
        s->leaf = false;
        s->size = 0;
        s->child[0] = r;

        btree_split_child(s, 0);
        btree_insert_nonfull(s, key);
    } else {
        btree_insert_nonfull(r, key);
    }

    return;
}

void left_rotate(BNode* x, int i) {
    BNode* left = x->child[i];
    BNode* right = x->child[i + 1];

    left->key[left->size] = x->key[i];
    left->size++;

    left->child[left->size] = right->child[0];
    x->key[i] = right->key[0];

    for (int j = 0; j < right->size - 1; j++) {
        right->key[j] = right->key[j + 1];
        right->child[j] = right->child[j + 1];
    }

    right->child[right->size-1] = right->child[right->size];
    right->size--;

    return;
}

void right_rotate(BNode* x, int i) {
    BNode* left = x->child[i];
    BNode* right = x->child[i + 1];

    right->size++;
    for (int j = right->size - 1; j > 0; j--) {
        right->key[j] = right->key[j - 1];
        right->child[j] = right->child[j - 1];
    }

    right->key[0] = x->key[i];
    right->child[0] = left->child[left->size];

    x->key[i] = left->key[left->size];
    left->size--;

    return;
}

void btree_erase(BNode* x, elem_t key) {
    int i = 0;
    while ((i < x->size) && (key > x->key[i])) {
        i++;
    }

    if ((i < x->size) && (key == x->key[i])) {
        // в i лежит номер ключа в узле

        if (x->leaf) { // можно удалять
            for (; i < x->size - 1; i++) {
                x->key[i] = x->key[i+1];
            }
        } else {
            BNode* left = x->child[i];
            BNode* right = x->child[i + 1];

            if (left->size > t-1) { // левый сын не минимальный
                x->key[i] = left->key[left->size-1];
                btree_erase(left, x->key[i]);
            } else { // левый сын почти пустой
                if (right->size > t-1) {
                    x->key[i] = right->key[0];
                    btree_erase(right, x->key[i]);
                } else { // все дети пустые
                    // начинаем единение
                    int j = t - 1;
                    left->key[j] = key;
                    j++;

                    for (; j < 2 * t - 1; j++) {
                        left->key[j] = right->key[j - t];
                    }
                    // двигаем ключи и указатели в x

                    for (; i < x->size - 1; i++) {
                        x->key[i] = x->key[i + 1];
                        x->child[i + 1] = x->child[i + 2];
                    }
                    x->size--;
                    delete right;
                    btree_erase(left, key);
                }
            }
        }
    } else { // в i лежит номер сына с ключом
        if (x->child[i]->size > t - 1) {
            btree_erase(x->child[i], key);
        }
    }
}
