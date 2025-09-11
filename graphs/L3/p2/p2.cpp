#include <iostream>
#include <vector>
#include <queue>
#include <fstream>
#include <algorithm>
#include <tuple>
using namespace std;


struct Edge {
    int u, v, w;
};

int V, E, INF = 9999;
vector<Edge> edges;
vector<vector<pair<int, int>>> adj;

void read_input(const string &input_file) {
    ifstream fin(input_file);
    fin >> V >> E;
    adj.assign(V + 1, {});
    for (int i = 0; i < E; ++i) {
        int u, v, w;
        fin >> u >> v >> w;
        edges.push_back({u, v, w});
        adj[u].emplace_back(v, w);
    }
    fin.close();
}

bool bellman_ford(vector<int> &h) {
    h.assign(V + 1, INF);
    h[V] = 0; // noul nod adaugat
    for (int i = 0; i < V; ++i)
        for (const auto &e : edges)
            if (h[e.u] != INF && h[e.u] + e.w < h[e.v])
                h[e.v] = h[e.u] + e.w; // relax

    for (const auto &e : edges)
        if (h[e.u] != INF && h[e.u] + e.w < h[e.v])
            return false; // ciclu negativ

    return true; // am determinat drumurile minime intre un nou nod adaugat si 
    // nodurile grafului
}

void reweight_edges(const vector<int> &h, vector<vector<pair<int, int>>> &new_adj) {
    new_adj.assign(V, {});
    for (auto &e : edges) {
        int new_weight = e.w + h[e.u] - h[e.v]; // formula de reponderare
        e.w = new_weight;
        new_adj[e.u].emplace_back(e.v, new_weight);
    }
    // toate muchiile au acum ponderi nenegative
}

void dijkstra(int src, const vector<vector<pair<int, int>>> &adj, vector<int> &dist) {
    dist.assign(V, INF);
    dist[src] = 0;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
    pq.emplace(0, src);

    while (!pq.empty()) {
        auto [d, u] = pq.top(); pq.pop();
        if (d > dist[u]) continue;

        for (auto &[v, w] : adj[u]) {
            if (dist[v] > dist[u] + w) {
                dist[v] = dist[u] + w;
                pq.emplace(dist[v], v);
            }
        }
    }
}

void dijkstra_all_pairs(const vector<vector<pair<int, int>>> &adj_rw,
                        const vector<int> &h,
                        vector<vector<int>> &result) {
    result.assign(V, vector<int>(V, INF));
    for (int u = 0; u < V; ++u) {
        vector<int> dist;
        dijkstra(u, adj_rw, dist);
        for (int v = 0; v < V; ++v) {
            if (dist[v] < INF)
                result[u][v] = dist[v] - h[u] + h[v];
        }
    }
}

void write_output(const string &output_file, const vector<vector<int>> &result) {
    ofstream fout(output_file);
    for(auto& e : edges){
        fout << e.u << " " << e.v << " " << e.w << "\n";
    }
    for (int i = 0; i < V; ++i) {
        for (int j = 0; j < V; ++j) {
            if (result[i][j] == INF) fout << "INF ";
            else fout << result[i][j] << " ";
        }
        fout << "\n";
    }
    fout.close();
}

int main(int argc, char *argv[]) {
    if(argc != 3){
        printf("Invalid usage!\n");
        exit(1);
    }
    string input_file = argv[1];
    string output_file = argv[2];
    
    read_input(input_file);

    // Adaugam nod conectat la toate muchiile existente
    for (int u = 0; u < V; ++u)
        edges.push_back({V, u, 0});

    vector<int> h;
    if (!bellman_ford(h)) {
        ofstream fout(output_file);
        fout << "-1\n";
        fout.close();
        return 1;
    }

    edges.erase(
    std::remove_if(edges.begin(), edges.end(), [](const Edge &e) {
        return e.u == V || e.v == V;
    }),
    edges.end()
);

    vector<vector<pair<int, int>>> adj_rw;
    reweight_edges(h, adj_rw);

    vector<vector<int>> result;
    dijkstra_all_pairs(adj_rw, h, result);

    write_output(output_file, result);

    return 0;
}
