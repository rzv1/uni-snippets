#include <vector>
#include <fstream>
#include <iostream>
#include <queue>

using namespace std;

void Edmonds_Karp(vector<vector<int>> cap, int& flux, int V){
    vector<vector<int>> R = cap; //graf rezidual initial copie a grafului dat
    vector<int> parent(V, -1); //vector de parinti
    flux = 0;
    int s = 0, t = V-1;
    //Algoritmul functioneaza atat timp cat exista drum de la s la t pe graful rezidual
    while(true){
        fill(parent.begin(), parent.end(), -1);
        queue<int> q;
        q.push(s);
        while(!q.empty() && parent[t] == -1){
            int u = q.front(); q.pop();
            for(int v = 0; v < V; v++){
                if(parent[v] == -1 && R[u][v] > 0){
                    parent[v] = u;
                    q.push(v);
                }
                    // daca am gasit drum de la s la t nu are rost sa continuam
                    if (v == t)
                        break;
            }
        }
        // Daca BFS nu a gasit drum in graful rezidual, am ajuns la flux maxim
        if(parent[t] == -1)
            break;

        //Determinam fluxul care poate trece de la s la t prin drumul gasit de BFS
        int aug = 9999;
        for(int v = t; v != s; v = parent[v]){
            int u = parent[v];
            aug = min(aug, R[u][v]);
        }

        //Actualizam capacitatea arcelor din graful rezidual
        for(int v = t; v != s; v = parent[v]){
            int u = parent[v];
            R[u][v] -= aug;
            R[v][u] += aug;
        }

        //Adaugam fluxul gasit pe drum la fluxul maxim
        flux += aug;
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
    vector<vector<int>> cap(V, vector<int>(V, 0));
    for(int i = 0; i < E; i++){
        int a, b, w;
        fin >> a >> b >> w;
        cap[a][b] = w;
    }
    Edmonds_Karp(cap, flux, V);
    fout << flux;
    fin.close();
    fout.close();
    return 0;
}