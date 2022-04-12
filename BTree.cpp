#include <iostream>

using namespace std;

#define elem_t int
#define t 2

struct BNode
{
    elem_t k[2 * t - 1];
    BNode *c[2 * t];
    BNode *p;
    int n;
    bool leaf;
};

struct BTree
{
    BNode *root;
};

BNode *allocate_node()
{
    BNode *x = new BNode;
    x->p = NULL;
    x->n = 0;
    x->leaf = true;
    for (int i =0; i < 2*t; i++) x->c[i] = NULL;
    return x;
}

void btree_create(BTree &T)
{
    BNode *x = allocate_node();
    T.root = x;
    return;
}

pair<BNode *, int> btree_search(BNode *x, elem_t key)
{
    int i = 0;
    while (i < x->n && key > x->k[i])
        i++;
    if (i < x->n && key == x->k[i])
        return {x, i};
    else if (x->leaf)
        return {NULL, -1};
    else
        return btree_search(x->c[i], key);
}

void btree_split_child(BNode *x,
                       int i)
{ // x указатель на незаполненный внутренний
  // узел, i номер заполненного сына
    BNode *z = allocate_node();
    z->p = x;
    BNode *y = x->c[i];
    z->leaf = y->leaf;
    z->n = t - 1;
    for (int j = 0; j < t - 1; j++)
        z->k[j] = y->k[j + t]; // j = t-2 => j+? = 2t-2
    if (!y->leaf)
        for (int j = 0; j < t; j++)
            z->c[j] = y->c[j + t];
    y->n = t - 1;
    for (int j = x->n; j > i + 1; j--)
        x->c[j] = x->c[j - 1]; // сдвиг массива в право
    x->c[i + 1] = z;
    for (int j = x->n - 1; j > i; j--)
        x->k[j] = x->k[j - 1];
    x->k[i] = y->k[t - 1];
    x->n++;
    return;
}

void btree_insert_nonfull(BNode *x,
                          elem_t key)
{ // x -это незаполненный узел
    int i = x->n - 1;
    if (x->leaf)
    {
        while (i >= 0 && key < x->k[i])
        {
            x->k[i + 1] = x->k[i];
            i--;
        }
        x->k[i + 1] = key;
        x->n++;
    }
    else
    { // х не листовой узел
        while (i >= 0 && key < x->k[i])
            i--;
        i++; // В x->c[i] нужно вставлять key
        if (x->c[i]->n == 2 * t - 1)
        {
            btree_split_child(x, i);
            if (key > x->k[i])
                i++;
        }
        btree_insert_nonfull(x->c[i], key);
    }
    return;
}

void btree_insert(BTree &T, elem_t key)
{
    BNode *r = T.root;
    if (r->n == 2 * t - 1)
    {
        BNode *s = allocate_node();
        T.root = s;
        s->leaf = false;
        s->n = 0;
        s->c[0] = r;
        btree_split_child(s, 0);
        btree_insert_nonfull(s, key);
    }
    else
        btree_insert_nonfull(r, key);
    return;
}

void l_rotate(BNode *x, int i)
{
    BNode *l = x->c[i];
    BNode *r = x->c[i + 1];
    l->k[l->n] = x->k[i];
    l->n++;
    l->c[l->n] = r->c[0];
    x->k[i] = r->k[0];
    for (int j = 0; j < r->n - 1; j++)
    {
        r->k[j] = r->k[j + 1];
        r->c[j] = r->c[j + 1];
    }
    r->c[r->n - 1] = r->c[r->n];
    r->n--;
}

void btree_erase(BNode *x, elem_t key)
{
    int i = 0;
    while (i < x->n && key > x->k[i])
        i++;
    if (i < x->n && key == x->k[i])
    {
        // В i лежит номер ключа в узле
        if (x->leaf)
        {
            // Можно удалить
            for (; i < x->n - 1; i++)
                x->k[i] = x->k[i + 1];
        }
        else
        {
            BNode *l = x->c[i];
            BNode *r = x->c[i + 1];
            if (l->n > t - 1)
            { //Левый сын не мин
                x->k[i] = l->k[l->n - 1];
                btree_erase(l, x->k[i]);
            }
            else
            { // Левый сын почти пустой
                if (r->n > t - 1)
                {
                    x->k[i] = r->k[0];
                    btree_erase(r, x->k[i]);
                }
                else
                { // Все дети почти пустые
                    // Начинаем единение
                    int j = t - 1;
                    l->k[j] = key;
                    j++;
                    for (; j < 2 * t - 1; j++)
                    {
                        l->k[j] = r->k[j - t];
                    }
                    // Двигаем ключи и указатели в x
                    for (; i < x->n - 1; i++)
                    {
                        x->k[i] = x->k[i + 1];
                        x->c[i + 1] = x->c[i + 2];
                    }
                    x->n--;
                    delete r;
                    btree_erase(l, key);
                }
            }
        }
    }
    else
    { // В i лежит номер сына с ключом
        if (x->c[i]->n > t - 1)
            btree_erase(x->c[i], key);
    }
}

int print_slice(BNode *root, int lvl)
{
    //cerr<<lvl<<endl;
    if (root == NULL){
        cout<<"NULL";
        return 0;
    }
    if (root->n == 0 ) return 0;
    if (lvl == 0)
    {
        cout << "(";
        for (int i = 0; i < root->n; i++)
            cout << root->k[i] << ' ';
        cout << ") ";
        return 1;
    }
    int sum = 0;
    for (int i = 0; i <= root->n; i++)
        sum += print_slice(root->c[i], lvl + 1);
    return sum;
}

void print_lvl_tree(BNode *root)
{
    int i = 0;
    while (print_slice(root, i++) != 0)
    {
        cout << endl;
    }
    cout << endl;
    return;
}

int main()
{
    //4 58 43 13 9 42 74 39 88
    BTree T;
    btree_create(T);
    btree_insert(T,4); cout<<endl;
    print_lvl_tree(T.root);
    btree_insert(T,58); cout<<endl;
    print_lvl_tree(T.root);
        btree_insert(T,43); cout<<endl;
    print_lvl_tree(T.root); 
        btree_insert(T,13); cout<<endl;
    print_lvl_tree(T.root);
        btree_insert(T,9);cout<<endl;
    print_lvl_tree(T.root);
        btree_insert(T,42);cout<<endl;
    print_lvl_tree(T.root);

    return 0;
}
