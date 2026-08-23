#include <iostream>
#include <vector>
#include <queue>
#include <fstream>
#include <algorithm>
#include <string>
#include <map>
using namespace std;

struct Node {
    Node *left, *right;
    int freq;
    char minChar;
    Node(char c, int f) : freq(f), minChar(c), left(nullptr), right(nullptr) {}
    Node(Node* l, Node* r) : freq(l->freq + r->freq), minChar(min(l->minChar, r->minChar)), left(l), right(r) {}
};

struct Cmp {
    bool operator()(Node* a, Node* b) const{
        return (a->freq > b-> freq) || ((a->freq == b->freq) && a->minChar > b->minChar);
    }
};

void deleteNodes(Node* root){
    if(!root)
        return;
    deleteNodes(root->left);
    deleteNodes(root->right);
    delete root;
}

int n, f, INF = 9999;
char c;
priority_queue<Node*, vector<Node*>, Cmp> pq;
map<char, int> chars;
string text;

int main(int argc, char *argv[]) {
    if(argc != 3){
        printf("Invalid usage!\n");
        exit(1);
    }
    ifstream fin(argv[1]);
    ofstream fout(argv[2]);
    string line;
    fin >> n;
    getline(fin, line);
    for(int i = 0; i < n; i++){
        getline(fin, line);
        c = line[0];
        f = stoi(line.substr(2));
        chars[c] = f;
    } 
    fin >> text;
 
    for(auto& [c, f] : chars)
        pq.push(new Node(c, f));

    while(pq.size() > 1){
        Node *a = pq.top(); pq.pop();
        Node *b = pq.top(); pq.pop();
        pq.push(new Node(a, b));
    }
    Node* root = pq.top();

    string decoded;
    if(!root->left && !root->right)
        decoded.assign(text.size(), root->minChar);
    else{
        Node* curent = root;
        for(char c : text){
            curent = (c == '0' ? curent->left : curent->right);
            if(!curent->left && !curent->right) {
                decoded.push_back(curent->minChar);
                curent = root;
            }
        }
    }
    
    fout << decoded;
    deleteNodes(root);
    fin.close();
    fout.close();
    return 0;
}
