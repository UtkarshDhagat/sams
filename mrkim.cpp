#include <iostream>
#include <vector>
#include <climits>
using namespace std;
int abs(int x) { 
    if (x < 0) { 
        return -x; 
    } else { 
        return x; 
    }
}
// Function to calculate Manhattan Distance
int manhattan(int x1, int y1, int x2, int y2) {
    return abs(x1 - x2) + abs(y1 - y2);
}

// Recursive DFS function to calculate the shortest path
void dfs(int x, int y, int visited_count, int total_distance, vector<pair<int, int> >& customers, vector<bool>& visited, int& min_distance, int home_x, int home_y) {
    // If all customers are visited, calculate distance to home and update minimum distance
    if (visited_count == customers.size()) {
        total_distance += manhattan(x, y, home_x, home_y);  // Add distance to home
        min_distance = min(min_distance, total_distance);  // Update minimum distance
        return;
    }

    // Try visiting each unvisited customer
    for (int i = 0; i < customers.size(); i++) {
        if (!visited[i]) {
            visited[i] = true;  // Mark customer as visited
            int new_distance = total_distance + manhattan(x, y, customers[i].first, customers[i].second);
            dfs(customers[i].first, customers[i].second, visited_count + 1, new_distance, customers, visited, min_distance, home_x, home_y);
            visited[i] = false;  // Backtrack
        }
    }
}

int main() {
    int n;  // Number of customers
    cin >> n;

    int office_x, office_y, home_x, home_y;
    cin >> office_x >> office_y >> home_x >> home_y;  // Input coordinates of office and home

    vector<pair<int, int> > customers(n);  // Customer coordinates
    for (int i = 0; i < n; i++) {
        cin >> customers[i].first >> customers[i].second;  // Input customer coordinates
    }

    vector<bool> visited(n, false);  // Track visited customers
    int min_distance = INT_MAX;  // Initialize minimum distance to a large value

    // Start DFS from the office
    dfs(office_x, office_y, 0, 0, customers, visited, min_distance, home_x, home_y);

    cout << min_distance << endl;  // Print the shortest path distance

    return 0;
}
