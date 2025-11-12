#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <string>
#include <algorithm>

using std::vector;
using std::pair;
using std::queue;
using std::string;
using std::ifstream;
using std::min;
using std::cin;

typedef vector<pair<int, int>> Lista;
typedef vector<vector<int>> Matrix;

class Graph {
private:
	const string inputFile;
	int V, E;
	int inf = 9999;
	int start;
	Matrix adjMatrix, adjList, incMatrix, disMatrix;
	Lista edgesList;

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
			adjMatrix[a][b] = 1;
		}
	}

	void adjMatrix_to_adjList() {
		for (int i = 0; i < V; i++)
			for (int j = 0; j < V; j++)
				if (adjMatrix[i][j] == 1) {
					adjList[i].push_back(j);
				}
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

	void Moore() {
		printf("Nodul de inceput: ");
		cin >> start;
		start--;
		vector<int> dist(V, -1);
		vector<int> parent(V, -1);
		queue<int> q;
		dist[start] = 0;
		q.push(start);

		while (!q.empty()) {
			int u = q.front();
			q.pop();
			for (int v : adjList[u]) {
				if (dist[v] == -1) {
					dist[v] = dist[u] + 1;
					parent[v] = u;
					q.push(v);
				}
			}
		}
		for (int i = 0; i < V; i++) {
			if (i == start)
				continue;
			printf("Nod %d: ", i + 1);
			if (dist[i] == -1)
				printf("Nu este accesibil din sursa.\n");
			else {
				vector<int> path;
				for (int v = i; v != -1; v = parent[v])
					path.push_back(v);
				reverse(path.begin(), path.end());
				for (int x : path)
					printf("%d ", x + 1);
				printf("\n");
			}
		}
		printf("\n");
	}

	void inchidereTranzitiva() {
		Matrix T;
		T.assign(V, vector<int>(V, 0));
		for (int i = 0; i < V; i++)
			for (int j = 0; j < V; j++)
				T[i][j] = adjMatrix[i][j];
		for (int k = 0; k < V; k++)
			for (int i = 0; i < V; i++)
				for (int j = 0; j < V; j++)
					T[i][j] = T[i][j] || (i == j) || (T[i][k] && T[k][j]);

		printf("Matricea de inchidere tranzitiva este:\n");
		for (int i = 0; i < V; i++, printf("\n"))
			for (int j = 0; j < V; j++)
				printf("%d ", T[i][j]);
		printf("\n");
	}

	void Labirint(string filepath) {
		struct Pos { int x, y; };
		Pos start{ 0,0 }, finish{ 0,0 };
		Matrix M;
		ifstream fin(filepath);
		string line;
		//Citesc labirint
		while (getline(fin, line)) {
			vector<int> row;
			for (char c : line) {
				if (c == '1')
					row.push_back(1);
				else
					row.push_back(0);
			}
			if (!row.empty())
				M.push_back(row);
		}
		int n = M.size(), m = M[0].size();

		//Determin pozitiile start si finish
		for(int j = 3; j < m - 3; j++)
			if (M[0][j] == 0 && M[0][j-1] == 0 && M[0][j+1] == 0 && M[0][j-2] == 1 && M[0][j+2] == 1) {
				start.x = 0; start.y = j;
				break;
			}
		for(int j = 3; j < m - 3; j++)
			if (M[n - 1][j] == 0 && M[n - 1][j - 1] == 0 && M[n - 1][j + 1] == 0 && M[n - 1][j - 2] == 1 && M[n - 1][j + 2] == 1) {
				finish.x = n - 1; finish.y = j;
				break;
			}

		//BFS pe matrice
		int dx[] = { 0, 1, 0, -1 };
		int dy[] = { -1, 0, 1, 0 };
		Matrix dist(n, vector<int>(m, -1));
		vector<vector<Pos>> parent(n, vector<Pos>(m, { -1, -1 }));
		queue<Pos> q;
		dist[start.x][start.y] = 0;
		q.push(start);

		while (!q.empty()) {
			Pos nod = q.front();
			q.pop();
			for (int d = 0; d < 4; d++) {
				int x = nod.x + dx[d];
				int y = nod.y + dy[d];
				if (x > 0 && x <= n - 1 && y > 0 && y < m - 1 && dist[x][y] == -1 && M[x][y] != 1) {
					dist[x][y] = dist[nod.x][nod.y] + 1;
					parent[x][y] = { nod.x, nod.y };
					q.push({ x, y });
				}
			}
		}
		if (dist[finish.x][finish.y] != -1) {
			Pos c = parent[finish.x][finish.y];
			while (c.x != -1 && c.y != -1) {
				M[c.x][c.y] = 3;
				c = parent[c.x][c.y];
			}
			for (int i = 0; i < n; i++, printf("\n"))
				for (int j = 0; j < M[i].size(); j++)
					printf("%c ", M[i][j] == 1 ? '-' : (M[i][j] == 0 ? ' ' : '#'));
		}
		else
			printf("Labirintul nu se poate rezolva!\n");
	}
	
	void BFS() {
		printf("Nodul de inceput: ");
		cin >> start;
		start--;
		vector<int> dist(V, -1);
		vector<int> parent(V, -1);
		queue<int> q;
		dist[start] = 0;
		q.push(start);

		while (!q.empty()) {
			int u = q.front();
			q.pop();
			for (int v : adjList[u]) {
				if (dist[v] == -1) {
					dist[v] = dist[u] + 1;
					parent[v] = u;
					q.push(v);
				}
			}
		}

		for (int i = 0; i < V; i++)
			printf("Nod: %d | Distanta: %d | Parinte: %d\n", i + 1, dist[i], parent[i]);
	}

	void DFS_VISIT(int u, vector<bool>& visited) {
		visited[u] = true;
		printf("\nVizitat %d", u + 1);
		for (int v : adjList[u])
			if (!visited[v])
				DFS_VISIT(v, visited);
	}

	void DFS_recursiv() {
		vector<bool> visited(V, false);
		int start;
		printf("\nStart: ");
		cin >> start;
		DFS_VISIT(start - 1, visited);
	}
};

int main() {
	Graph G("./graph2.txt");
	G.print_edgesList();
	G.edgesList_to_adjMatrix();
	G.print_adjMatrix();
	G.adjMatrix_to_adjList();
	G.print_adjList();
	G.Moore();
	G.inchidereTranzitiva();
	G.Labirint("./labirint1.txt");
	G.Labirint("./labirint2.txt");
	G.Labirint("./labirint3.txt");
	G.BFS();
	G.DFS_recursiv();
}
