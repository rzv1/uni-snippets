#include <vector>
#include <fstream>
#include <iostream>
#include <queue>

using namespace std;

void pompare(int u, int v, vector<vector<int>>& cap, vector<int>& excess, vector<int>& height, queue<int>& q, int s, int t){
    int d = min(excess[u], cap[u][v]);
    if (d > 0 && height[u] == height[v] + 1){
        cap[u][v] -= d;
        cap[v][u] += d;
        excess[u] -= d;
        excess[v] += d;
        if(excess[v] == d && v != s && v != t)
            q.push(v);
    }
}

void inaltare(int u, vector<vector<int>>& cap, vector<int>& height, int V){
    int min_height = 2 * V;
    for(int v = 0; v < V; v++)
        if(cap[u][v])
            min_height = min(min_height, height[v]);
    if(min_height < 2 * V)
        height[u] = min_height + 1; 
}

void preflux(vector<vector<int>>& cap, int& flux, int V, int E){
    vector<int> height(V, 0), excess(V, 0);
    queue<int> q;
    int s = 0, t = V-1;
    //Initializare preflux
    height[s] = V;
    for (int v = 0; v < V; v++){
        if (cap[s][v]) {
            excess[v] += cap[s][v];
            cap[v][s] += cap[s][v];
            cap[s][v] = 0;
            if(v != t && v != s)
                q.push(v);
        }
    }
    //Alg functioneaza pana cand inaltarea nu mai este posibila
    while(!q.empty()){
        int u = q.front(); q.pop();
        while (excess[u]){
            bool pompat = false;
            for (int v = 0; v < V && excess[u] > 0; v++) {
                int inainte = excess[u];
                pompare(u, v, cap, excess, height, q, s, t);
                if(excess[u] < inainte)
                    pompat = true;
            if(!pompat)
                inaltare(u, cap, height, V);

            }
        }   
    flux = excess[t];
    }
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
    vector<vector<int>> cap(V, vector<int>(V,0));
    for(int i = 0; i < E; i++){
        int a, b, w;
        fin >> a >> b >> w;
        cap[a][b] = w;
    }
    preflux(cap, flux, V, E);
    fout << flux;
    fin.close();
    fout.close();
    return 0;
}