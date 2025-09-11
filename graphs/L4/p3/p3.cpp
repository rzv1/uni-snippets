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

void Huffman(Node* root, string &text, vector<string> &codes){
    if(!root->left && !root->right){
        if(text.empty())
            text = "0";
        codes[root->minChar] = text;
        return;
    }
    if(root->left){
        text.push_back('0');
        Huffman(root->left, text, codes);
        text.pop_back();
    }
    if(root->right){
        text.push_back('1');
        Huffman(root->right, text, codes);
        text.pop_back();
    }
}

int V, E, INF = 9999;
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
    fin >> text;
    for(int i = 0; text[i]; i++)
        chars[text[i]]++;

    for(auto& [c, f] : chars)
        pq.push(new Node(c, f));

    while(pq.size() > 1){
        Node *a = pq.top(); pq.pop();
        Node *b = pq.top(); pq.pop();
        pq.push(new Node(a, b));
    }
    Node* root = pq.top();
    string t = "";
    vector<string> codes(256);
    Huffman(root, t, codes);
    deleteNodes(root);
    
    fout << chars.size() << '\n';
    for(auto& [c, f] : chars)
        fout << c << " " << f << '\n';

    for(char c : text)
        fout << codes[c];
    return 0;
}
