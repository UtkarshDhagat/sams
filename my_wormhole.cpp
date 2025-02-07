#include <iostream>
#include <vector>
#include <climits>

using namespace std;

// Struct to store wormhole details
struct worm {
    int ex, ey;  // Entry coordinates
    int exx, exy; // Exit coordinates
    int cost;
};

// Function to return absolute value
int abs(int x) { 
    if (x < 0) { 
        return -x; 
    } else { 
        return x; 
    }
}

// Function to return the minimum of two numbers
int min(int x, int y) {
    if (x > y) {
        return y;
    } else {
        return x;
    }
}

// Function to calculate Manhattan distance
int manhattan(int x1, int y1, int x2, int y2) {
    return abs(x1 - x2) + abs(y1 - y2);
}

// Recursive DFS function
void dfs(int x1, int y1, int x2, int y2, int value, int &ANS, vector<worm>& wormholes, vector<int>& mask, int n) {
    ANS = min(ANS, manhattan(x1, y1, x2, y2) + value);

    for (int i = 0; i < n; i++) {
        if (mask[i] == 0) {  
            mask[i] = 1;

            // Try entering from one end and teleporting to the other
            int temp = manhattan(x1, y1, wormholes[i].ex, wormholes[i].ey) + wormholes[i].cost + value;
            dfs(wormholes[i].exx, wormholes[i].exy, x2, y2, temp, ANS, wormholes, mask, n);

            // Try entering from the other end
            temp = manhattan(x1, y1, wormholes[i].exx, wormholes[i].exy) + wormholes[i].cost + value;
            dfs(wormholes[i].ex, wormholes[i].ey, x2, y2, temp, ANS, wormholes, mask, n);

            mask[i] = 0;  // Backtrack
        }
    }
}

int main() {
    int n, sX, sY, tX, tY;
    cin >> n;  
    cin >> sX >> sY >> tX >> tY;

    vector<worm> wormholes(n);
    vector<int> mask(n, 0);  // Keeps track of used wormholes
    int ANS = INT_MAX;

    for (int i = 0; i < n; i++) {
        cin >> wormholes[i].ex >> wormholes[i].ey 
            >> wormholes[i].exx >> wormholes[i].exy 
            >> wormholes[i].cost;
    }

    dfs(sX, sY, tX, tY, 0, ANS, wormholes, mask, n);
    cout << ANS << endl;
    return 0;
}
