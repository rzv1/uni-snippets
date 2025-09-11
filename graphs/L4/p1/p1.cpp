#include <iostream>
#include <vector>
#include <queue>
#include <fstream>
#include <algorithm>
#include <set>
using namespace std;


int main(int argc, char* argv[]){
    int n, r;
    if(argc != 3){
        printf("Utilizare incorecta");
        return 1;
    }
    ifstream fin(argv[1]);
    ofstream fout(argv[2]);
    fin>>n;
    vector<int> pi(n);
    vector<int> degree(n, 0);
    vector<vector<int>> adj(n);
    vector<int> prufer;
    for(int i = 0; i < n; i++){
        fin>>pi[i];
        if(pi[i] != -1){
            adj[i].push_back(pi[i]);
            adj[pi[i]].push_back(i);
            degree[i]++; degree[pi[i]]++;
        }
        else
            r = i;
    }
    set<int> frunze;
    for(int i = 0; i < n; i++)
        if(degree[i] == 1)
            frunze.insert(i);

    while(!frunze.empty()){
        int frunza = *frunze.begin();
        frunze.erase(frunze.begin());
        for(int v : adj[frunza]){
            if(degree[v] > 0){
                prufer.push_back(v);
                degree[v]--;
                if(degree[v] == 1 && v != r)
                    frunze.insert(v);
                break;
            }
        }
        degree[frunza] = 0;
    }
    fout << prufer.size() << '\n';
    for(int x : prufer)
        fout << x << " ";

    fin.close();
    fout.close();
}