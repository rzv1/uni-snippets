#include <vector>
#include <fstream>
#include <iostream>
#include <queue>

using namespace std;

const int INF = 9999;

void Edmonds_Karp(vector<vector<int>>& cap, vector<vector<int>>& res, int& flux){
    const int V = (int)cap.size();
    res = cap;
    vector<int> parent(V);
    flux = 0;
    const int s = V - 1; //supersursa
    const int t = V - 2; //destinatie

    while (true) {
        fill(parent.begin(), parent.end(), -1);
        queue<int> q;
        q.push(s);
        parent[s] = s;

        // BFS pe graf rezidual
        while (!q.empty() && parent[t] == -1) {
            int u = q.front(); q.pop();
            for (int v = 0; v < V; ++v)
                if (parent[v] == -1 && res[u][v] > 0) {
                    parent[v] = u;
                    q.push(v);
                    if (v == t) 
                        break;
                }
        }
        //nu mai exista drum
        if (parent[t] == -1) 
            break;

        int aux = INF;
        for (int v = t; v != s; v = parent[v])
            aux = min(aux, res[parent[v]][v]);

        for (int v = t; v != s; v = parent[v]) {
            int u = parent[v];
            res[u][v]   -= aux;
            res[v][u]   += aux;
        }
        flux += aux;
    }
}

int main(int argc, char* argv[]){
    if(argc != 3){
        printf("Utilizare incorecta");
        exit(1);
    }
    int V, N, C, D, flux;
    ifstream fin(argv[1]);
    ofstream fout(argv[2]);
    fin >> N >> C >> D;
    int S = N; //supersursa
    V = N + 1;
    vector<vector<int>> cap(V, vector<int>(V, 0));
    for(int i = 0; i < D; i++){
        int a, b, w;
        fin >> a >> b >> w;
        cap[a][b] += w;
    }
    for(int i = 0; i < C; i++)
        cap[S][i] = INF;
    vector<vector<int>> res;
    Edmonds_Karp(cap, res, flux);
    
    vector<int> start(C);
    for(int i = 0; i < C; i++)
        start[i] = INF - res[S][i];

    fout << flux << '\n';
    for(int i = 0; i < C; i++)
        fout << start[i] << ' ';
    fin.close();
    fout.close();
    return 0;
}