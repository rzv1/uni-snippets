#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
using namespace std;

int main(int argc, char* argv[]) {
    if(argc != 3){
        printf("Utilizare incorecta");
        return 1;
    }
    ifstream fin(argv[1]);
    ofstream fout(argv[2]);
    int M;
    fin >> M;
    int N = M + 1;

    vector<int> code(M);
    for (int i = 0; i < M; ++i) {
        fin >> code[i];
    }

    vector<int> degree(N, 1);
    for (int v : code) {
        degree[v]++;
    }

    priority_queue<int, vector<int>, greater<>> frunze;
    for (int i = 0; i < N; ++i) {
        if (degree[i] == 1) {
            frunze.push(i);
        }
    }

    vector<int> parent(N, -1);
    for (int i = 0; i < M; ++i) {
        int leaf = frunze.top();
        frunze.pop();

        int p = code[i];
        parent[leaf] = p;
        degree[leaf]--;
        degree[p]--;
        if (degree[p] == 1) {
            frunze.push(p);
        }
    }

    fout << N << "\n";
    for (int i = 0; i < N; ++i) {
        fout << parent[i] << " ";
    }

    return 0;
}
