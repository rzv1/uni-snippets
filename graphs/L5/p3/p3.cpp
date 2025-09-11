#include <vector>
#include <fstream>
#include <iostream>
#include <set>

using namespace std;

void euler(int u, vector<multiset<int>>& adj, vector<int>& pi){
    while(!adj[u].empty()){
        int v = *adj[u].begin();
        adj[u].erase(adj[u].begin());
        adj[v].erase(adj[v].find(u));
        euler(v, adj, pi);
    }
    pi.push_back(u);
}

int main(int argc, char* argv[]){
    if(argc != 3){
        printf("Utilizare incorecta");
        exit(1);
    }
    int V, E, flux;
    ifstream fin(argv[1]);
    ofstream fout(argv[2]);
    fin >> V >> E;
    vector<multiset<int>> adj(V);
    vector<int> pi;
    for(int i = 0; i < E; i++){
        int a, b;
        fin >> a >> b;
        adj[a].insert(b);
        adj[b].insert(a);
    }
    euler(0, adj, pi);
    for(int i = 0; i < pi.size() - 1; i++)
        fout << pi[i] << " ";
    fin.close();
    fout.close();
    return 0;
}