#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
using namespace std;

class Solution {
public:
    vector<pair<int, int>> directions = {
        {-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, 
        {0, 1}, {1, -1}, {1, 0}, {1, 1}
    };

    int shortestPathBinaryMatrix(vector<vector<int>>& grid) {
        int n = grid.size();
        if (grid[0][0] == 1 || grid[n - 1][n - 1] == 1) return -1;

        queue<pair<pair<int, int>, int>> q;
        q.push({{0, 0}, 1}); 
        grid[0][0] = 1;  

        while (!q.empty()) {
            auto [cell, dist] = q.front();
            auto [r, c] = cell;
            q.pop();

            if (r == n - 1 && c == n - 1) return dist;

            for (auto [dr, dc] : directions) {
                int nr = r + dr, nc = c + dc;
                if (nr >= 0 && nc >= 0 && nr < n && nc < n && grid[nr][nc] == 0) {
                    q.push({{nr, nc}, dist + 1});
                    grid[nr][nc] = 1;
                }
            }
        }
        return -1;
    }
};

int main() {
    ifstream inputFile("input.txt");
    int n;
    inputFile >> n;
    
    vector<vector<int>> grid(n, vector<int>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            inputFile >> grid[i][j];
        }
    }
    inputFile.close();

    Solution obj;
    cout << obj.shortestPathBinaryMatrix(grid) << endl;
    return 0;
}
