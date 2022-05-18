#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

struct Edge{
	int from,to,weight;
};

struct Graph {
	bool isOriented, isValued, isMatrix, isSet;
	unsigned int e_count,v_count; // v_count - количество вершин e_count-количество ребер
	vector<vector<int>> matrix;
	vector<vector<Edge>> edges; // Внешний вектор отвечает за вершины
	// vector<Edge> хранит набор ребер исходящих из вершины с номером i
};

int min_white_v(const vector<int> &D, const vector<int> &C){
	int min = 1e9;
	int min_index = -1;
	for (int i =0; i < D.size(); i++){
		if (D[i]<min  && C[i]==0){
			min = D[i];
			min_index = i;
		}
	}
	return min_index;
}

void Dijkstra(const Graph & G,  vector<int> &C, 
			vector<int> &P, vector<int> &D, int start )
{
	for (int i =0; i<G.v_count; i++) {
		C[i]=0;
		P[i] = -2;
		D[i] = 1e9;
	}
	P[start] = -1;
	D[start] = 0;
	int cur ;
	for (int i = 0; i < G.v_count; i++){
		cur = min_white_v(D,C);
		if (cur == -1) break;
		for (int j =0; j<G.edges[cur].size(); j++){
			int to = G.edges[cur][j].to;
			if (C[to] == 0){
				if (D[to]> D[cur]+ G.edges[cur][j].weight ){
					D[to] = D[cur]+ G.edges[cur][j].weight;
					P[to] = cur;
				}
			}
		}
		C[cur] = 1;
	}
}

void BFS (const Graph & G, vector<int> &C, 
			vector<int> &P, vector<int> &D, int start)
{
	P[start] = -1;
	D[start] = 0;
	queue<int> Q;
	Q.push(start);
	C[start] = 1;
	while (!Q.empty()){
		int cur = Q.front();
		Q.pop();
		C[cur] = 2;
		for (int i =0; i < G.edges[cur].size(); i++){
			int to = G.edges[cur][i].to;
			if (C[to] == 0){
				C[to] = 1;
				P[to] = cur;
				D[to] = D[cur]+1;
				Q.push(to);
			}
		}
	}
}


void DFS (const Graph & G, vector<int> &C, int cur,
			vector<int> &P, vector<pair<int,int>> &SE, int & time){
	SE[cur].first = time++;
	C[cur] = 1;
	for (int i = 0; i < G.edges[cur].size(); i++){
		int to = G.edges[cur][i].to;
		if (C[to] == 0){
			P[to] = cur;
			DFS(G,C,to,P,SE,time);
		}
	}
	SE[cur].second = time++;
	C[cur]= 2;
	return;
}


void printMatrix(const Graph & g);
void printEdges(const Graph & g);
void readEdges( Graph & g);
// 5 6       5 - количество вершин 6 - количество ребер
// 1 3        - ребро из 1 в 3 и т.д.
// 5 1
// 4 3
// 3 1
// 4 5
// 1 6
void readMatrix( Graph & g);
// 3 - количество вершин
// 0 1 1
// 1 0 1
// 1 1 0
void fillMatrix( Graph & g);
void fillEdges( Graph & g);

int main() {
	int N,x;
	Edge E;
	Edge cur ;
	N = 6;
	vector<int> C (N,0), D(N, -1), P (N,-2);
	Graph G;
	G.v_count = N;
	G.edges.resize(N); 
	E.from = 0;
	E.to= 2;
	E.weight = 1;
	G.edges[0].push_back(E);
	E.from = 0;
	E.to= 1;
	E.weight = 1;
	G.edges[0].push_back(E);
	E.from = 0;
	E.to= 4;
	E.weight = 3;
	G.edges[0].push_back(E);
	E.from = 1;
	E.to= 4;
	E.weight = 1;
	G.edges[1].push_back(E);
	E.from = 1;
	E.to= 2;
	E.weight = 3;
	G.edges[1].push_back(E);
	Dijkstra(G,C,P,D,0);
	for(auto x : D) {cout<<x<<endl;}
	
}











