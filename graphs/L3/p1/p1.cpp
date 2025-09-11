#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

using std::ifstream;
using std::ofstream;
using std::vector;
using std::pair;
using std::priority_queue;
using std::greater;
using std::cout;

void Dijkstra(vector<vector<pair<int,int>>>& adj, priority_queue<pair<int,int>,vector<pair<int,int>>,greater<>> pq, vector<int>& dist){
    while(!pq.empty()){
        auto [u, d] = pq.top();
        pq.pop();
        if(d > dist[u])
            continue;
        for(const auto [v, w] : adj[u]){
            if(dist[u] + w < dist[v]){
                dist[v] = dist[u] + w;
                pq.emplace(v, dist[v]);
            }
        }
    }
}

int main(int argc, char* argv[]) {
	int V, E, S, a, b, w, inf = 9999;
    if(argc != 3){
        printf("Utilizare incorecta\n");
        return 1;
    }
    ifstream fin(argv[1]);
	ofstream fout(argv[2]);
    fin >> V >> E >> S;
    S--;
    vector<vector<pair<int, int>>> adj(V);
    vector<int> dist(V, inf);
    dist[S] = 0;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
    pq.emplace(S, 0); 
    for(int i = 0; i < E; i++){
        fin >> a >> b >> w;
        adj[a-1].emplace_back(b-1, w);
    }
    Dijkstra(adj, pq, dist);
    for(int i = 0; i < V; i++){
        fout << "Nod " << i + 1 << ": ";
        if(dist[i] == inf)
            fout << "inf\n";
        else
            fout << dist[i] << "\n";
    }

	fin.close();
	fout.close();
	return 0;
}