#include <iostream>
using namespace std;
const int MAX_NODES = 100; // Maximum number of nodes
int n, m; // Number of nodes and edges
int adj[MAX_NODES][MAX_NODES]; // Adjacency matrix
bool visited[MAX_NODES]; // Visited array
bool dfs(int node, int parent) {
    visited[node] = true;
    for (int neighbor = 0; neighbor < n; neighbor++) {
        if (adj[node][neighbor]) { // If an edge exists
            if (!visited[neighbor]) {
                if (dfs(neighbor, node)) return true;
            } else if (neighbor != parent) {
                return true; // Cycle found
            }
        }
    }
    return false;
}
bool detectCycle() {
    for (int i = 0; i < n; i++) visited[i] = false; // Initialize visited array

    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            if (dfs(i, -1)) return true;
        }
    }
    return false;
}
int main() {
    cin >> n >> m; // Input number of nodes and edges
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u][v] = 1;
        adj[v][u] = 1; // Since it's an undirected graph
    }
    if (detectCycle()) cout << "Cycle detected\n";
    else cout << "No cycle found\n";
    return 0;
}
