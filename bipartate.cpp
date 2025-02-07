#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    int n;
    vector<vector<int>> adjMatrix;
    vector<int> color;

    // ✅ DFS function to check if the graph is bipartite
    bool isBiPartite(int node) {
        for (int j = 0; j < n; j++) {
            if (adjMatrix[node][j] == 1) {  // If an edge exists
                if (color[j] == -1) {  // If node is uncolored
                    color[j] = 1 - color[node];  // Assign opposite color
                    if (!isBiPartite(j)) return false;  // Recursive DFS check
                }
                else if (color[j] == color[node]) {  // If neighbor has same color
                    return false;  // Not bipartite
                }
            }
        }
        return true;
    }

    // ✅ Main function to determine if the graph is bipartite
    void checkBipartite() {
        cin >> n;
        adjMatrix.assign(n, vector<int>(n, 0));
        color.assign(n, -1);

        // ✅ Input adjacency matrix
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                cin >> adjMatrix[i][j];
            }
        }

        // ✅ Checking bipartiteness for disconnected graphs
        for (int i = 0; i < n; i++) {
            if (color[i] == -1) {  // If node is uncolored
                color[i] = 0;  // Start coloring from 0
                if (!isBiPartite(i)) {  // If not bipartite
                    cout << "-1" << endl;
                    return;
                }
            }
        }

        // ✅ Printing one bipartite set
        for (int i = 0; i < n; i++) {
            if (color[i] == 0) {
                cout << i << " ";
            }
        }
        cout << endl;
    }
};

int main() {
    Solution obj;
    obj.checkBipartite();
    return 0;
}
