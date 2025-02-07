#include <iostream>
#include <queue>
#include <vector>
#include <climits>

using namespace std;

void bfs(vector<vector<int>>& grid, vector<vector<int>>& dist, int startX, int startY, int n) {
    queue<pair<int, int>> q;
    q.push({startX, startY});
    dist[startX][startY] = 0;

    vector<pair<int, int>> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

    while (!q.empty()) {
        auto [x, y] = q.front();
        q.pop();

        for (auto [dx, dy] : directions) {
            int nx = x + dx, ny = y + dy;
            if (nx >= 0 && ny >= 0 && nx < n && ny < n && grid[nx][ny] == 1 && dist[nx][ny] == -1) {
                dist[nx][ny] = dist[x][y] + 1;
                q.push({nx, ny});
            }
        }
    }
}

int findBestLocation(vector<vector<int>>& grid, vector<pair<int, int>>& rareElements, int n) {
    int minMaxDist = INT_MAX;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (grid[i][j] == 1) {  // Only consider road cells
                vector<vector<int>> dist(n, vector<int>(n, -1));
                bfs(grid, dist, i, j, n);
                
                int maxDist = 0;
                for (auto [rx, ry] : rareElements) {
                    maxDist = max(maxDist, dist[rx][ry]);
                }

                minMaxDist = min(minMaxDist, maxDist);
            }
        }
    }

    return minMaxDist;
}

int main() {
    int t;
    cin >> t;  // Number of test cases

    while (t--) {
        int n, c;
        cin >> n >> c;

        vector<pair<int, int>> rareElements(c);
        for (auto& [x, y] : rareElements) {
            cin >> x >> y;
        }

        vector<vector<int>> grid(n, vector<int>(n));
        for (auto& row : grid)
            for (auto& cell : row)
                cin >> cell;

        cout << findBestLocation(grid, rareElements, n) << endl;
    }

    return 0;
}
