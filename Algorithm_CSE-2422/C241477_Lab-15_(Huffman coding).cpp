#include <bits/stdc++.h>
using namespace std;
struct Node {
    char ch;
    int freq;
    Node *left, *right;

    Node(char ch, int freq, Node* left = NULL, Node* right = NULL) {
        this->ch = ch;
        this->freq = freq;
        this->left = left;
        this->right = right;
    }
};
struct Compare {
    bool operator()(Node* a, Node* b) {
        return a->freq > b->freq;
    }
};

void printCodes(Node* root, string code) {
    if (!root) return;
    if (!root->left && !root->right) {
        cout << root->ch << " : " << code << "\n";
    }

    printCodes(root->left, code + "0");
    printCodes(root->right, code + "1");
}

int main() {
    string text;
    cout << "Enter text: ";
    getline(cin, text);

    unordered_map<char, int> freq;
    for (char c : text) freq[c]++;

    priority_queue<Node*, vector<Node*>, Compare> pq;

    for (auto it : freq) {
        pq.push(new Node(it.first, it.second));
    }

    while (pq.size() > 1) {
        Node* left = pq.top(); pq.pop();
        Node* right = pq.top(); pq.pop();

        int sum = left->freq + right->freq;
        pq.push(new Node('\0', sum, left, right));
    }

    Node* root = pq.top();

    cout << "\nHuffman Codes (Variable-Length):\n";
    printCodes(root, "");

    return 0;
}
