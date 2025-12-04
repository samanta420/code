#include <iostream>
using namespace std;

int adj[100][100];
int visited[100];
int q[100];
int front = 0, rear = 0;
void enqueue(int x) {
    q[rear++] = x;
}

int dequeue() {
    return q[front++];
}

bool empty() {
    return front == rear;
}

void BFS(int start, int n) {
    enqueue(start);
    visited[start] = 1;

    while (!empty()) {
        int node = dequeue();
        cout << node << " ";

        for (int i = 1; i <= n; i++) {
            if (adj[node][i] == 1 && visited[i] == 0) {
                visited[i] = 1;
                enqueue(i);
            }
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

    BFS(1, n);
}
