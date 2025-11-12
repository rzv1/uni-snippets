#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <string>
#include <algorithm>

using namespace std;

class Graph {
private:
	const string inputFile;
	int V, E, start, inf = 10e12;

	vector<vector<int>> MatriceAdiacenta, ListaAdiacenta, MatriceIncidenta, MatriceDistante;
	vector<pair<int,int>> edgesList;

	void readFromFile(const string& filepath) {
		ifstream fin(filepath);
		fin >> V;
		int a, b;
		while (fin >> a && fin >> b) {
			a--; b--;
			edgesList.emplace_back(a, b);
			E++;
		}
		fin.close();
	}
	void init_adjMatrix() {
		adjMatrix.clear();
		adjMatrix.assign(V, vector<int>(V, 0));
	}
	void init_disMatrix() {
		disMatrix.clear();
		disMatrix.assign(V, vector<int>(V, 0));
	}
	void init_incMatrix() {
		incMatrix.clear();
		incMatrix.assign(V, vector<int>(E, 0));
	}
	void init_adjList() {
		adjList.clear();
		adjList.assign(V, {});
	}
public:
	Graph(const string& filepath) : inputFile{ filepath }, V{ 0 }, E{ 0 } {
		readFromFile(inputFile);
		init_adjMatrix();
		init_disMatrix();
		init_incMatrix();
		init_adjList();
	}

	void edgesList_to_adjMatrix() {
		for (const auto& edge : edgesList) {
			auto a = edge.first, b = edge.second;
			adjMatrix[a][b] = adjMatrix[b][a] = 1;
		}
	}

	void adjMatrix_to_adjList() {
		for(int i = 0; i < V; i++)
			for(int j = i + 1; j < V; j++)
				if (adjMatrix[i][j] == 1) {
					adjList[i].push_back(j);
					adjList[j].push_back(i);
				}
	}

	void adjList_to_incMatrix() {
		for (int e = 0; e < E; e++) {
			int a = edgesList[e].first, b = edgesList[e].second;
			incMatrix[a][e] = incMatrix[b][e] = 1;
		}
	}

	void incMatrix_to_adjList() {
		init_adjList();
		for (int e = 0; e < E; e++) {
			int a = -1, b = -1;
			for(int v = 0; v < V; v++)
				if (incMatrix[v][e] == 1) {
					if (a == -1)
						a = v;
					else
						b = v;
				}
			adjList[a].push_back(b);
			adjList[b].push_back(a);
		}
	}

	void adjList_to_adjMatrix() {
		init_adjMatrix();
		for (int i = 0; i < V; i++)
			for (int j = 0; j < adjList[i].size(); j++)
				if (i < adjList[i][j])
					adjMatrix[i][adjList[i][j]] = adjMatrix[adjList[i][j]][i] = 1;
	}

	void adjMatrix_to_edgesList() {
		edgesList.clear();
		for (int i = 0; i < V; i++)
			for (int j = i + 1; j < V; j++)
				if (adjMatrix[i][j])
					edgesList.emplace_back(i, j);
	}

	void print_adjMatrix() {
		printf("Matricea de adiacenta este:\n");
		for (int i = 0; i < V; i++, printf("\n"))
			for (int j = 0; j < V; j++)
				printf("%d ", adjMatrix[i][j]);
		printf("\n");
	}

	void print_incMatrix() {
		printf("Matricea de incidenta este:\n");
		for (int i = 0; i < V; i++, printf("\n"))
			for (int j = 0; j < E; j++)
				printf("%d ", incMatrix[i][j]);
		printf("\n");
	}

	void print_adjList() {
		printf("Lista de adiacenta este:\n");
		for (int i = 0; i < V; i++, printf("\n")) {
			printf("%d: ", i + 1);
			for (int j = 0; j < adjList[i].size(); j++)
				printf("%d ", adjList[i][j] + 1);
		}
		printf("\n");
	}

	void print_edgesList() {
		printf("Lista de muchii este:\n");
		for (int i = 0; i < edgesList.size(); i++)
			printf("%d %d\n", edgesList[i].first + 1, edgesList[i].second + 1);
		printf("\n");
	}

	void f2a() {
		vector<int> gasite;
		for (int i = 0; i < V; i++)
			if (adjList[i].size() == 0)
				gasite.push_back(i + 1);
		if (gasite.size() == 0)
			printf("Nu exista noduri izolate.\n\n");
		else {
			printf("Nodurile izolate sunt: ");
			for (int i = 0; i < gasite.size(); i++)
				printf("%d ", gasite[i]);
			printf("\n\n");
		}
	}

	void f2b() {
		bool regular = true;
		for (int i = 0; i < V - 1; i++)
			if (adjList[i].size() != adjList[i + 1].size()) {
				regular = false;
				break;
			}
		if (regular)
			printf("Graful este regular!\n\n");
		else
			printf("Graful nu este regular!\n\n");
	}

	void f2c() {
		for(int i = 0; i < V; i++)
			for (int j = 0; j < V; j++) {
				if (adjMatrix[i][j] == 0 && i != j)
					disMatrix[i][j] = inf;
				else
					disMatrix[i][j] = adjMatrix[i][j];
			}
		//Floyd-Warshall
		for (int k = 0; k < V; k++)
			for (int i = 0; i < V; i++)
				for (int j = 0; j < V; j++)
					disMatrix[i][j] = min(disMatrix[i][j], disMatrix[i][k] + disMatrix[k][j]);

		printf("Matricea de distante este:\n");
		for(int i = 0; i < V; i++, printf("\n"))
			for(int j = 0; j < V; j++)
				printf("%d ", disMatrix[i][j] == inf ? -1 : disMatrix[i][j]);
		printf("\n");
	}

	void f2d() {
		for (int i = 0; i < V; i++) {
			int count = 0;
			for (int j = 0; j < V; j++)
				count += adjMatrix[i][j];
			if (count == 0) {
				printf("Graful NU este conex!\n");
				return;
			}
		}
		printf("Graful este conex!\n");
	}

	void Moore() {
		printf("Nodul de inceput: ");
		cin >> start;
		vector<int> dist;
		queue<int> q;
		dist.assign(V, -1);
		dist[start] = 0;
		q.push(start);

		while (!q.empty()) {
			int u = q.front();
			q.pop();
			for (int v : adjList[u]) {
				if (dist[v] == -1) {
					dist[v] = dist[u] + 1;
					q.push(v);
				}
			}
		}

	}
};

int main() {
	Graph G("./graph.txt");
	G.print_edgesList();
	G.edgesList_to_adjMatrix();
	G.print_adjMatrix();
	G.adjMatrix_to_adjList();
	G.print_adjList();
	G.adjList_to_incMatrix();
	G.print_incMatrix();
	G.incMatrix_to_adjList();
	G.print_adjList();
	G.adjList_to_adjMatrix();
	G.print_adjMatrix();
	G.adjMatrix_to_edgesList();
	G.print_edgesList();
	G.f2a();
	G.f2b();
	G.f2c();
	G.f2d();
}
