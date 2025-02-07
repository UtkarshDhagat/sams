#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    int maxCoins(vector<int>& nums) {
        int n = nums.size();
        
        // ✅ Step 1: Create a new array with padding (Add 1 at start & end)
        vector<int> newNums(n + 2, 1);
        for (int i = 0; i < n; i++) {
            newNums[i + 1] = nums[i];  // Copy original numbers
        }
        n += 2;  // Account for new padding
        
        // ✅ Step 2: Initialize DP Table
        vector<vector<int>> dp(n, vector<int>(n, 0));

        // ✅ Step 3: Iterate over lengths of possible balloon sequences
        for (int len = 2; len < n; len++) {  // Window length
            for (int left = 0; left < n - len; left++) {
                int right = left + len;  // Right boundary
                
                // ✅ Step 4: Iterate through possible last balloons
                for (int i = left + 1; i < right; i++) {
                    int burstValue = newNums[left] * newNums[i] * newNums[right];  // Main burst value
                    int totalPoints = burstValue + dp[left][i] + dp[i][right];  // Include previous DP results
                    
                    dp[left][right] = max(dp[left][right], totalPoints);  // Store max points
                }
            }
        }

        return dp[0][n - 1];  // ✅ Answer is stored in dp[0][n-1]
    }
};

int main() {
    int n;
    cin >> n;  // Number of balloons
    vector<int> balloons(n);
    
    for (int i = 0; i < n; i++) {
        cin >> balloons[i];  // Read balloon values
    }

    Solution obj;
    int result = obj.maxCoins(balloons);
    cout << result << endl;  // ✅ Output max points

    return 0;
}
