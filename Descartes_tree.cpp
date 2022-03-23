#include <iostream>

using namespace std;
#define elem_t int

struct Node
{
    elem_t key ;
    int prior;
    Node *l, *r;
};

void print_lvl_tree(Node *root);
int print_slice(Node *root, int lvl);
Node *make_node(elem_t key);
Node *merge(Node *T1, Node *T2);
pair<Node *, Node *> split(Node *T, elem_t x);
Node *insert(Node *T, elem_t key);
Node *erase(Node *T, elem_t key);

int main()
{
    Node *DT = NULL;
    for (int i = 1; i <= 1000; i++)
    {
        DT = insert(DT, i);
        print_lvl_tree(DT);
        cout << "-----------------------------" << endl;
    }
    return 0;
}

int print_slice(Node *root, int lvl)
{
    if (root == NULL)
        return 0;
    if (lvl == 0)
    {
        cout << "(" << root->key << "," << root->prior << ") ";
        return 1;
    }
    return print_slice(root->l, lvl - 1) + print_slice(root->r, lvl - 1);
}

void print_lvl_tree(Node *root)
{
    int i = 0;
    while (print_slice(root, i++) != 0)
    {
        cout << endl;
    }
    cout << endl;
    return;
}

Node *make_node(elem_t key)
{
    Node *ans = new Node;
    ans->r = ans->l = NULL;
    ans->key = key;
    ans->prior = rand(); // ПОМЕНЯТЬ
    return ans;
}

Node *merge(Node *T1, Node *T2)
{
    // Все ключи T1 должны быть меньше ключей T2
    if (T1 == NULL)
        return T2;
    if (T2 == NULL)
        return T1;
    if (T1->prior > T2->prior)
    {
        T1->r = merge(T1->r, T2);
        return T1;
    }
    T2->l = merge(T1, T2->l);
    return T2;
}

pair<Node *, Node *> split(Node *T, elem_t x)
{
    if (T == NULL)
        return {NULL, NULL};
    pair<Node *, Node *> tmp;
    if (T->key <= x)
    {
        tmp = split(T->r, x);
        T->r = tmp.first;
        return {T, tmp.second};
    }
    tmp = split(T->l, x);
    T->l = tmp.second;
    return {tmp.first, T};
}

Node *insert(Node *T, elem_t key)
{
    pair<Node *, Node *> P = split(T, key);
    Node *new_node = make_node(key);
    return merge(P.first, merge(new_node, P.second));
}

Node *erase(Node *T, elem_t key)
{
    pair<Node *, Node *> P = split(T, key);
    pair<Node *, Node *> D = split(P.first, key - 1);
    //Если ключи уникальные и целочисленные
    if (D.second != NULL)
        delete D.second;
    return merge(D.first, P.second);
}
