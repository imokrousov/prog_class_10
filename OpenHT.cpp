#include <cmath>
#include <cstdlib>
#include <iostream>

using namespace std;

#define elem_t int
#define NaV -2e9

enum State { DEL, FREE, BUSY };

struct Cell {
    State state;
    elem_t val;
    int it_hash;
};

struct OpenHT {
    int capacity;
    int size;
    Cell *table;
};

void init(OpenHT &t, int cap = 1000003) {
    t.capacity = cap;
    t.size = 0;
    t.table = new Cell[cap];
    for (int i = 0; i < cap; i++) t.table[i].state = FREE;
    return;
}

int lin_hash(elem_t key, int iter, int mod) { return (key + iter) % mod; }

void insert(OpenHT &t, elem_t key) {
    if (t.size >= t.capacity) return;
    int i = 0;
    int hash = lin_hash(key, i, t.capacity);
    while (t.table[hash].state == BUSY) {
        if (t.table[hash].val == key) return;
        hash = lin_hash(key, ++i, t.capacity);
    }
    t.size++;
    t.table[hash].state = BUSY;
    t.table[hash].val = key;
    t.table[hash].it_hash = i;
    return;
}

int find(OpenHT &t, elem_t key) {
    int hash = lin_hash(key, 0, t.capacity);
    int i = 1;
    while (t.table[hash].state != FREE) {
        Cell cur = t.table[hash];
        if (cur.state == BUSY && cur.val == key) return hash;
        hash = lin_hash(key, i++, t.capacity);
        if (i > t.capacity) break;
    }
    return -1;
}

void swap(elem_t &x, elem_t &y) {
    elem_t tmp = x;
    x = y;
    y = tmp;
    return;
}

void erase(OpenHT &t, elem_t key) {
    int key_pos = find(t, key);
    if (key_pos == -1) return;
    int i = t.table[key_pos].it_hash;
    int hash = lin_hash(key, i + 1, t.capacity);
    if (t.table[hash].state == FREE)
        t.table[key_pos].state = FREE;
    else
        t.table[key_pos].state = DEL;
    return;
}

void print_table(OpenHT &t) {
    for (int i = 0; i < t.capacity; i++) {
        if (t.table[i].state == FREE) cout << "FREE ";
        if (t.table[i].state == BUSY) cout << "BUSY ";
        if (t.table[i].state == DEL) cout << "DEL ";
        cout << t.table[i].val << " " << t.table[i].it_hash << endl;
    }
    return;
}

int main() {
    OpenHT t;
    init(t, 11);
    insert(t, 1);
    insert(t, 2);
    insert(t, 3);
    insert(t, 4);
    insert(t, 2);
    print_table(t);
    cout << "-------------------" << endl;
    erase(t, 2);
    print_table(t);
    cout << "-------------------" << endl;
    erase(t, 4);
    print_table(t);
}
