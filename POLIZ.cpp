#include <iostream>
#include <cmath>

using namespace std;

struct unit {
	string s;
	int val; 
	int type;
	int prior;
	bool left_association;
};

// type of operations
/*
	0 - number
	1 - Binary
	2 - unary postfix
	3 - unary prefix
	4 - open bracket
	5 - close bracket
*/
struct Node{
	unit v; // value
	Node * next;
};

struct L1 {
	Node * head;
	Node * tail;
	unsigned int size;
};

struct stack {
	L1 list;
};

//---------------L1-------------------------
void init (L1 & list); // O(1)
Node * make_node (unit key); // O(1)
void push_front(L1 & list, unit key); // O(1)
void push_back(L1 & list, unit key); // O(1)
Node* get_by_index(L1 & list, int index); // O(n)
void push_by_index(L1 & list, int index, unit key); // O(n)
void print(L1 & list); // O(n)
void pop_front(L1 & list); // O(1)
void pop_back(L1 & list); // O(n)
void pop_by_index(L1 & list, int index); // O(n)
unit front(L1 & list); // O(1)
unit back(L1 & list); // O(1)
//-----------------Stack-----------------------
bool empty(stack & S);
unit top(stack & S);
void push(stack & S,  unit key);
void pop(stack & S);






unit make_unit(const string & str );
int  str_to_int(const string & str );
unit * array_str_to_array_unit (string * arr_str, int n);
unit * POLIZ (unit * source , int n);

int main() {
	int n = 16;
	string * S = new string[n];
	for  (int i =0; i < n ; i++) cin>>S[i];
	// G ( 3 ) + 4 * 2 / ( 1 - 5 ) ^ 2
	unit * infix = array_str_to_array_unit(S,n);
	for (int i =0; i < n ; i++){
		cout<< infix[i].type<< ' ';
	} cout<<endl;
	unit * poliz = POLIZ(infix,n);
	for (int i =0; i < n ; i++){
		cout<< poliz[i].s<< ' ';
	}
	
	return 0;
}

bool empty(stack & S){
	return S.list.size ==0;
}
unit top(stack & S){
	return front(S.list);
}
void push(stack & S, unit key){
	push_front(S.list, key);
	return;
}
void pop(stack & S){
	pop_front(S.list);
	return;
}

unit * POLIZ (unit * source , int n){
	unit * ans =  new unit[n];
	int j =0;
	stack S;
	init(S.list);
	for (int i =0; i < n ; i++){
		if (source[i].type ==0 ){ // Число 
			ans[j] = source[i];
			j++;
		}
		if (source[i].type ==1 ){ // Бинарна операция
			if (empty (S)){
				push(S, source[i] );
				continue;
			}
			while (true) {
				unit t= top(S);
				if (t.type == 3 || 
					t.type == 1 && t.prior > source[i].prior ||
					t.type == 1 && t.prior == source[i].prior && t.left_association
				) {
					ans[j] = t;
					pop(S);
					if (empty (S)) break;
					j++;
				}
				else break;
			}
			push(S, source[i] );
		}
		if (source[i].type ==2 ){ // Унарная постфиксная
			ans[j] = source[i];
			j++;
		}
		if (source[i].type ==3 ){ // Унарная префиксная
			push(S, source[i] );
		}
		if (source[i].type ==4 ){ // Открыв скобка
			push(S, source[i] );
		}
		if (source[i].type ==5 ){ // Закрыв скобка
			while (! empty (S) && top(S).type != 4 ) {
				ans[j] = top(S);
				pop(S);
				j++;
			}
			if (empty (S)) {
				delete[] ans;
				cerr<< "Какой-то вывод 1\n";
				return NULL; // Ошибка
			}
			// Проверка на комлементарность скобок
			pop(S);
		}
	}
	while (! empty(S)){
		ans[j] = top(S);
		pop(S);
		j++;
	}
	return ans;
}

unit * array_str_to_array_unit (string * arr_str, int n){
	unit * ans = new unit[n];
	for (int i = 0; i < n ; i++) ans[i] = make_unit(arr_str[i]);
	return ans;
}

int  str_to_int(const string & str ){
	int digit = 1;
	int ans = 0;
	for (int i = str.size()-1; i >=1; i--){
		if (str[i] > '9' || str[i] < '0' ) return -2e9;
		ans += digit*(str[i]-'0');
		digit*=10;
	}
	if (str[0] == '-' && str.size()>1) ans*= -1;
	else 
		if (str[0] <= '9' || str[0] >= '0' ) 
			ans += digit*(str[0]-'0');
		else return -2e9;
	return ans;
}

unit make_unit(const string & str ){
	unit ans;
	ans.s = str;
	int k = str_to_int(str);
	if (k != -2e9) {
		ans.val = k;
		ans.type = 0;
		ans.prior = -1;
		ans.left_association = false;
	}
	if (str[0] == '+' || str[0] == '-' ){
		ans.val = 0 ;
		ans.type = 1 ;
		ans.prior = 1 ;
		ans.left_association = true ;
	}
	if (str[0] == '*' || str[0] == '/'){
		ans.val = 0;
		ans.type = 1;
		ans.prior = 2;
		ans.left_association = true;
	}
	if (str[0] == '^' ){
		ans.val = 0;
		ans.type = 1;
		ans.prior = 3;
		ans.left_association = true;
	}
	if (str[0] == '(' || str[0] == '[' || str[0] == '{'){
		ans.val = 0;
		ans.type = 4;
		ans.prior = 0;
		ans.left_association = false;
	}
	if (str[0] == ')' || str[0] == ']' || str[0] == '}'){
		ans.val = 0;
		ans.type = 5;
		ans.prior = 0;
		ans.left_association = false;
	}
	if (str[0] == '!'){
		ans.val = 0;
		ans.type = 2 ;
		ans.prior = -1;
		ans.left_association = false ;
	}
	if (str[0] == 'G'){
		ans.val = 0;
		ans.type = 3;
		ans.prior = -1;
		ans.left_association = false;
	}
	return ans;
}


unit front(L1 & list){
	if (list.size == 0){
		cerr<< "Try to get value from an empty list"<<endl;
		return make_unit("2e9");
	}
	return list.head->v;
}

unit back(L1 & list){
	if (list.size == 0){
		cerr<< "Try to get value from an empty list"<<endl;
		return make_unit("2e9");
	}
	return list.tail->v;
}


void pop_by_index(L1 & list, int index){
	if (list.size == 0){
		cerr<< "Try to pop_back from an empty list"<<endl;
		return;
	}
	if (index < 0 || index >= list.size) {
		cerr<< "Bad index of pop_by_index"<<endl;
		return;
	}
	if (list.size == 1 || index == 0) {
		pop_front(list);
		return;
	}
	Node * p = get_by_index(list, index-1);
	Node * del = p->next;
	Node * q = del->next;
	p->next = q;
	delete del;
	if (index == list.size-1) list.tail = p;
	list.size--;
	return;
}


void pop_back(L1 & list){
	if (list.size == 0){
		cerr<< "Try to pop_back from an empty list"<<endl;
		return;
	}
	if (list.size == 1) {
		pop_front(list);
		return;
	}
	pop_by_index(list, list.size -1);
	return;
}

void pop_front(L1 & list){
	if (list.size == 0){
		cerr<< "Try to pop_front from an empty list"<<endl;
		return;
	}
	Node * tmp = list.head;
	list.head = list.head->next;
	delete tmp;
	if (list.size == 1) list.tail = NULL;
	list.size--;
	return;
}

void print(L1 & list){
	Node * runner = list.head;
	for (int i = 0; i < list.size; i++) {
		cout<< runner->v.s << " -> ";
		runner= runner->next;
	}
	cout<< "NULL\n";
	return;
}

void push_by_index(L1 & list, int index, unit key){
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

void push_back(L1 & list, unit key){
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

void push_front(L1 & list, unit key){
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

Node * make_node (unit key){
	Node * p = new Node;
	p->v = key;     // (*p).v = key;
	p->next = NULL; // (*p).next = NULL;
	return p;
}
