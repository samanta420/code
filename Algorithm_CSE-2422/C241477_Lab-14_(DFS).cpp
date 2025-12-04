#include <iostream>
using namespace std;
int adj[100][100];
int visited[100];
void DFS(int node, int n) {
    visited[node] = 1;
    cout << node << " ";

    for (int i = 1; i <= n; i++) {
        if (adj[node][i] == 1 && visited[i] == 0) {
            DFS(i, n);
        }
    }
}

int main() {
    int n, e;
    cin >> n >> e;

    for (int i = 1; i <= e; i++) {
        int u, v;
        cin >> u >> v;
        adj[u][v] = 1;
        adj[v][u] = 1;
    }

    DFS(1, n);
}

