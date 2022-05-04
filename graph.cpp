#include <iostream>
#include <vector>

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

void printMatrix(const Graph & g);
void printEdges(const Graph & g);
void readEdges(const Graph & g);
// 5 6       5 - количество вершин 6 - количество ребер
// 1 3        - ребро из 1 в 3 и т.д.
// 5 1
// 4 3
// 3 1
// 4 5
// 1 6
void readMatrix(const Graph & g);
// 3 - количество вершин
// 0 1 1
// 1 0 1
// 1 1 0
void fillMatrix( Graph & g);
void fillEdges( Graph & g);

int main() {}
