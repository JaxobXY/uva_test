#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <utility>

using namespace std;

int main()
{
    int x, y;
    cin >> x >> y;
    cin.ignore();
    
    vector<vector<string>> grid(x, vector<string>(y));
    
    for(int i = 0; i < x; i++)
    {
        string line;
        getline(cin, line);
        size_t start = 0;
        for(int j = 0; j < y; j++)
        {
            size_t comma_pos = line.find(',', start);
            if (comma_pos == string::npos) {
                comma_pos = line.length();
            }
            grid[i][j] = line.substr(start, comma_pos - start);
            start = comma_pos + 1;
        }
    }

    // Check column pairs in order (smallest first)
    for (int y1 = 0; y1 < y; y1++) {
        for (int y2 = y1 + 1; y2 < y; y2++) {
            map<pair<string, string>, int> seen;

            for (int x1 = 0; x1 < x; x1++) {
                pair<string, string> key = make_pair(grid[x1][y1], grid[x1][y2]);

                if (seen.find(key) != seen.end()) {
                    // Found violation
                    cout << "NO" << endl;
                    cout << seen[key] + 1 << " " << x1 + 1 << endl;  // rows
                    cout << y1 + 1 << " " << y2 + 1 << endl;         // columns
                    return 0;
                } else {
                    seen[key] = x1;
                }
            }
        }
    }

    cout << "YES" << endl;
    return 0;
}