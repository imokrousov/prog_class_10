#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

struct Node{
	Node * p;
	int k; // количество в поддереве
};

bool isDelegate (Node * x){
	if (x==NULL) return false;
	if (x->p == NULL) return true;
	return false;
}

Node * getDelegate (Node * x);
bool isSameSet (Node * x, Node * y);
void setUnion (Node * x, Node * y);
vector<Node *> init(int n);

int main() {
	vector<Node *> A = init(100);
}

vector<Node *> init(int n){
	vector<Node *> ans (n);
	for (int i =0; i <n ;i++) {
		ans[i] = new Node;
		ans[i].p = NULL;
		ans[i].k = 1;		
	}
	return ans;
}

Node * getDelegate (Node * x){
	if (x==NULL) return NULL;
	if (isDelegate(x)) return x;
	Node * d = getDelegate(x->p);
	x->p = d;
	return d;
}

bool isSameSet(Node * x , Node * y){
	if (x==NULL || y ==NULL) {
		cerr<<"Bad pointers"<<endl;
		return false;
	}
	return getDelegate(x) == getDelegate(y);
}

void setUnion(Node * x , Node * y){
	if (x==NULL || y ==NULL) {
		cerr<<"Bad pointers"<<endl;
		return;
	}
	Node * dx = getDelegate(x);
	Node * dy = getDelegate(y);
	if (dx->k < dy->k) swap(dx,dy); // После этого dx->k >= dy->k
	dy->p = dx;
	dx->k += dy->k;
	return;
}

