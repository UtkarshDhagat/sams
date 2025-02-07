#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    int n; // Grid rows
    vector<pair<int, int>> moves = {{0, -1}, {0, 1}, {0, 0}}; // Left, Right, Stay

    // Function to remove enemies (bomb effect)
    void detonate(vector<vector<int>>& grid, int row) {
        for (int i = max(0, row - 4); i <= row; i++) {
            for (int j = 0; j < 5; j++) {
                if (grid[i][j] == 2) {
                    grid[i][j] = 0; // Remove enemy
                }
            }
        }
    }

    // Recursive function to find max coins collected
    int findMaxCoins(vector<vector<int>>& grid, int row, int col, bool usedBomb) {
        if (row < 0 || col < 0 || col >= 5) return 0; // Out of bounds
        if (grid[row][col] == 2) return -1e9; // Game over

        int coins = (grid[row][col] == 1) ? 1 : 0; // Collect coin
        int maxCoins = 0;

        // Try moving left, right, or staying
        for (auto [dx, dy] : moves) {
            maxCoins = max(maxCoins, findMaxCoins(grid, row - 1, col + dy, usedBomb));
        }

        // If no coins collected and bomb is available, use it
        if (maxCoins == 0 && !usedBomb) {
            vector<vector<int>> tempGrid = grid;
            detonate(tempGrid, row - 1);
            maxCoins = findMaxCoins(tempGrid, row, col, true);
        }

        return coins + maxCoins;
    }

    int getMaxCoins(vector<vector<int>>& grid) {
        n = grid.size();
        return findMaxCoins(grid, n - 1, 2, false); // Start from last row, center column
    }
};

int main() {
    int t;
    cin >> t; // Number of test cases

    while (t--) {
        int n;
        cin >> n; // Grid height

        vector<vector<int>> grid(n, vector<int>(5));
        for (auto &row : grid)
            for (auto &cell : row)
                cin >> cell;

        Solution obj;
        cout << obj.getMaxCoins(grid) << endl;
    }

    return 0;
}
