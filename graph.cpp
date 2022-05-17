#include <iostream>
#include <vector>
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

int main() {}
