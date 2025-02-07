#include <iostream>
#include <vector>
#include <queue>

using namespace std;

// Structure to store pipe properties
struct Pipe {
    bool up, down, left, right;
};

// Directions: Up, Down, Left, Right
int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, -1, 1};

// Function to check if the position is inside the grid
bool isValid(int x, int y, int n, int m) {
    return (x >= 0 && x < n && y >= 0 && y < m);
}

// BFS function to count reachable cells
int bfs(vector<vector<int>>& grid, int sX, int sY, int len) {
    int n = grid.size(), m = grid[0].size();
    
    // Visited array to mark visited cells
    vector<vector<bool>> visited(n, vector<bool>(m,false)) ;
    queue<pair<int, int>> q;

    // Pipe connection details for each type
    vector<Pipe> pipes(8);
    pipes[1] = {true, true, true, true};   // Type 1: All directions
    pipes[2] = {true, true, false, false}; // Type 2: Up, Down
    pipes[3] = {false, false, true, true}; // Type 3: Left, Right
    pipes[4] = {true, false, false, true}; // Type 4: Up, Right
    pipes[5] = {false, true, false, true}; // Type 5: Down, Right
    pipes[6] = {false, true, true, false}; // Type 6: Down, Left
    pipes[7] = {true, false, true, false}; // Type 7: Up, Left

    // If starting position is an empty cell (0), return 0
    if (grid[sX][sY] == 0) return 0;

    // Initialize BFS
    q.push({sX, sY});
    visited[sX][sY] = true;
    int result = 1; // Counting the starting cell

    int steps = 0; // Track the distance traveled
    while (!q.empty() && steps < len) {
        int size = q.size();
        steps++;

        for (int i = 0; i < size; i++) {
            auto [x, y] = q.front();
            q.pop();

            // Try moving in all 4 directions
            for (int d = 0; d < 4; d++) {
                int nx = x + dx[d], ny = y + dy[d];

                // If out of bounds or already visited, skip
                if (!isValid(nx, ny, n, m) || visited[nx][ny] || grid[nx][ny] == 0) continue;

                // Current pipe and next pipe
                Pipe currPipe = pipes[grid[x][y]];
                Pipe nextPipe = pipes[grid[nx][ny]];

                // Check if the pipes are connected properly
                if ((d == 0 && currPipe.up && nextPipe.down) ||  // Moving Up
                    (d == 1 && currPipe.down && nextPipe.up) ||  // Moving Down
                    (d == 2 && currPipe.left && nextPipe.right) || // Moving Left
                    (d == 3 && currPipe.right && nextPipe.left)) { // Moving Right

                    q.push({nx, ny});
                    visited[nx][ny] = true;
                    result++;
                }
            }
        }
    }

    return result; // Return the total count of reachable cells
}

// Main function
int main() {
    int t;
    cin >> t;  // Number of test cases

    while (t--) {
        int n, m, sX, sY, len;
        cin >> n >> m >> sX >> sY >> len;  // Grid size and starting position

        vector<vector<int>> grid(n, vector<int>(m));
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                cin >> grid[i][j];

        cout << bfs(grid, sX, sY, len) << endl;
    }
    
    return 0;
}
