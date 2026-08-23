#include <algorithm>
#include <fstream>
#include <iostream>
#include <queue>
#include <string>
#include <vector>

using namespace std;

class Graph {
private:
  const string inputFile;
  int V, E, start, inf = 1e9;

  vector<vector<int>> MatriceAdiacenta, ListaAdiacenta, MatriceIncidenta,
      MatriceDistante;
  vector<pair<int, int>> edgesList;

  void readFromFile(const string &filepath) {
    ifstream fin(filepath);
    fin >> V;
    int a, b;
    while (fin >> a && fin >> b) {
      a--;
      b--;
      edgesList.emplace_back(a, b);
      E++;
    }
    fin.close();
  }
  void init_adjMatrix() {
    MatriceAdiacenta.clear();
    MatriceAdiacenta.assign(V, vector<int>(V, 0));
  }
  void init_disMatrix() {
    MatriceDistante.clear();
    MatriceDistante.assign(V, vector<int>(V, 0));
  }
  void init_incMatrix() {
    MatriceIncidenta.clear();
    MatriceIncidenta.assign(V, vector<int>(E, 0));
  }
  void init_adjList() {
    ListaAdiacenta.clear();
    ListaAdiacenta.assign(V, {});
  }

public:
  Graph(const string &filepath) : inputFile{filepath}, V{0}, E{0} {
    readFromFile(inputFile);
    init_adjMatrix();
    init_disMatrix();
    init_incMatrix();
    init_adjList();
  }

  void edgesList_to_adjMatrix() {
    for (const auto &edge : edgesList) {
      auto a = edge.first, b = edge.second;
      MatriceAdiacenta[a][b] = MatriceAdiacenta[b][a] = 1;
    }
  }

  void adjMatrix_to_adjList() {
    for (int i = 0; i < V; i++)
      for (int j = i + 1; j < V; j++)
        if (MatriceAdiacenta[i][j] == 1) {
          ListaAdiacenta[i].push_back(j);
          ListaAdiacenta[j].push_back(i);
        }
  }

  void adjList_to_incMatrix() {
    for (int e = 0; e < E; e++) {
      int a = edgesList[e].first, b = edgesList[e].second;
      MatriceIncidenta[a][e] = MatriceIncidenta[b][e] = 1;
    }
  }

  void incMatrix_to_adjList() {
    init_adjList();
    for (int e = 0; e < E; e++) {
      int a = -1, b = -1;
      for (int v = 0; v < V; v++)
        if (MatriceIncidenta[v][e] == 1) {
          if (a == -1)
            a = v;
          else
            b = v;
        }
      ListaAdiacenta[a].push_back(b);
      ListaAdiacenta[b].push_back(a);
    }
  }

  void adjList_to_adjMatrix() {
    init_adjMatrix();
    for (int i = 0; i < V; i++)
      for (int j = 0; j < ListaAdiacenta[i].size(); j++)
        if (i < ListaAdiacenta[i][j])
          MatriceAdiacenta[i][ListaAdiacenta[i][j]] =
              MatriceAdiacenta[ListaAdiacenta[i][j]][i] = 1;
  }

  void adjMatrix_to_edgesList() {
    edgesList.clear();
    for (int i = 0; i < V; i++)
      for (int j = i + 1; j < V; j++)
        if (MatriceAdiacenta[i][j])
          edgesList.emplace_back(i, j);
  }

  void print_adjMatrix() {
    printf("Matricea de adiacenta este:\n");
    for (int i = 0; i < V; i++, printf("\n"))
      for (int j = 0; j < V; j++)
        printf("%d ", MatriceAdiacenta[i][j]);
    printf("\n");
  }

  void print_incMatrix() {
    printf("Matricea de incidenta este:\n");
    for (int i = 0; i < V; i++, printf("\n"))
      for (int j = 0; j < E; j++)
        printf("%d ", MatriceIncidenta[i][j]);
    printf("\n");
  }

  void print_adjList() {
    printf("Lista de adiacenta este:\n");
    for (int i = 0; i < V; i++, printf("\n")) {
      printf("%d: ", i + 1);
      for (int j = 0; j < ListaAdiacenta[i].size(); j++)
        printf("%d ", ListaAdiacenta[i][j] + 1);
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
      if (ListaAdiacenta[i].size() == 0)
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
      if (ListaAdiacenta[i].size() != ListaAdiacenta[i + 1].size()) {
        regular = false;
        break;
      }
    if (regular)
      printf("Graful este regular!\n\n");
    else
      printf("Graful nu este regular!\n\n");
  }

  void f2c() {
    for (int i = 0; i < V; i++)
      for (int j = 0; j < V; j++) {
        if (MatriceAdiacenta[i][j] == 0 && i != j)
          MatriceDistante[i][j] = inf;
        else
          MatriceDistante[i][j] = MatriceAdiacenta[i][j];
      }
    // Floyd-Warshall
    for (int k = 0; k < V; k++)
      for (int i = 0; i < V; i++)
        for (int j = 0; j < V; j++)
          MatriceDistante[i][j] =
              min(MatriceDistante[i][j],
                  MatriceDistante[i][k] + MatriceDistante[k][j]);

    printf("Matricea de distante este:\n");
    for (int i = 0; i < V; i++, printf("\n"))
      for (int j = 0; j < V; j++)
        printf("%d ",
               MatriceDistante[i][j] == inf ? -1 : MatriceDistante[i][j]);
    printf("\n");
  }

  void f2d() {
    for (int i = 0; i < V; i++) {
      int count = 0;
      for (int j = 0; j < V; j++)
        count += MatriceAdiacenta[i][j];
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
      for (int v : ListaAdiacenta[u]) {
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
