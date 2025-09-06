#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <utility>
#include <sstream>
using namespace std;

int main() {
    int n, m;
    bool first_case = true;
    
    while (cin >> n >> m) {
        cin.ignore();
        vector<vector<string>> grid(n, vector<string>(m));
        
        // Read the grid
        for (int i = 0; i < n; i++) {
            string line;
            getline(cin, line);
            
            // Parse CSV line more carefully
            stringstream ss(line);
            string cell;
            int j = 0;
            
            while (getline(ss, cell, ',') && j < m) {
                grid[i][j] = cell;
                j++;
            }
        }
        
        bool found = false;
        int found_x1 = -1, found_x2 = -1, found_y1 = -1, found_y2 = -1;
        
        // Check all pairs of columns
        for (int y1 = 0; y1 < m && !found; y1++) {
            for (int y2 = y1 + 1; y2 < m && !found; y2++) {
                map<pair<string, string>, int> seen;
                
                for (int i = 0; i < n && !found; i++) {
                    auto value_pair = make_pair(grid[i][y1], grid[i][y2]);
                    
                    if (seen.count(value_pair)) {
                        // Found duplicate pair!
                        found = true;
                        found_x1 = seen[value_pair]; // first occurrence row
                        found_x2 = i; // second occurrence row
                        found_y1 = y1;
                        found_y2 = y2;
                    } else {
                        seen[value_pair] = i; // store row index
                    }
                }
            }
        }
        
        // Output format
        if (!first_case) {
            cout << endl;
        }
        
        if (found) {
            cout << "NO" << endl;
            cout << found_x1 + 1 << " " << found_x2 + 1 << endl;
            cout << found_y1 + 1 << " " << found_y2 + 1 << endl;
        } else {
            cout << "YES" << endl;
        }
        
        first_case = false;
    }
    
    return 0;
}