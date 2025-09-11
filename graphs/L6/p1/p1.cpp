#include <vector>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <queue>

using namespace std;

void colorare_graf(int V, vector<vector<int>>& adj, int& C, vector<int>& culoare){
    vector<pair<int, int>> sorted;
    for(int i = 0; i < V; i++)
        sorted.emplace_back(-adj[i].size(), i);
    sort(sorted.begin(), sorted.end());

    for(auto p : sorted){
        int u = p.second;
        vector<bool> folosit(V, false);
        for(int v : adj[u])
            if (culoare[v] != -1)
                folosit[culoare[v]] = true;
        int c;
        for(c = 0; c < V; c++)
            if(!folosit[c])
                break;
        culoare[u] = c;
    }
    C = *max_element(culoare.begin(), culoare.end()) + 1;
}

int main(int argc, char* argv[]){
    if(argc != 3){
        printf("Utilizare incorecta");
        exit(1);
    }
    int V, E, C;
    ifstream fin(argv[1]);
    ofstream fout(argv[2]);
    fin >> V >> E;
    vector<vector<int>> adj(V);
    vector<int> culoare(V, -1);
    for(int i = 0; i < E; i++){
        int a, b;
        fin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    colorare_graf(V, adj, C, culoare);
    fout << C << '\n';
    for(int i = 0; i < V; i++)
        fout << culoare[i] << " ";
    fin.close();
    fout.close();
    return 0;
}