#include <iostream>
#include <vector>
#include <queue>
#include <fstream>
#include <algorithm>
#include <string>
#include <tuple>
using namespace std;

int V, E, cost, n;
priority_queue<pair<int,int>,vector<pair<int,int>>, greater<>> muchii;
vector<vector<pair<int, int>>> adj;


void prim(){
    cost = 0;
    vector<bool> used(V, false);
    priority_queue<tuple<int,int,int>,
    vector<tuple<int,int,int>>, greater<tuple<int,int,int>>> pq;
    pq.emplace(0, 0, -1);
    while(!pq.empty()){
        auto [w, v, p] = pq.top(); pq.pop();
        if(used[v])
            continue;
        used[v] = true;
        if(p != -1) {
            cost += w;
            muchii.emplace(min(p,v), max(p,v));
        }
        for(auto& [to, wt] : adj[v]) {
            if (!used[to])
                pq.emplace(wt, to, v);
        }
    }
    n = muchii.size();
}

int main(int argc, char *argv[]) {
    if(argc != 3){
        printf("Invalid usage!\n");
        exit(1);
    }
    ifstream fin(argv[1]);
    ofstream fout(argv[2]);
    fin >> V >> E;
    adj.assign(V + 1, {});
    for (int i = 0; i < E; ++i) {
        int u, v, w;
        fin >> u >> v >> w;
        adj[u].emplace_back(v, w);
        adj[v].emplace_back(u, w);
    }
    prim();

    fout << cost << '\n' << n << '\n';
    for(int i = 0; i < n; i++){
        auto [u, v] = muchii.top(); muchii.pop();
        fout << u << ' ' << v << '\n';
    }
    fin.close();
    fout.close();
    return 0;
}
