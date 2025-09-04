#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <map>

using namespace std;

int main()
{
    vector<map<string, int>> gridhash;
    vector<set> gridhash;
    
    int x;
    int y;
    cin >> x >> y; // Read dimensions first
    cin.ignore(); // Clear the newline after reading y
    
    vector<vector<string>> grid(x, vector<string>(y)); // Initialize grid with x rows and y columns
    
    for(int i = 0; i < x; i++)
    {
        string line;
        getline(cin, line); // Read entire line
        stringstream ss(line);
        
        for(int j = 0; j < y; j++)
        {
            getline(ss, grid[i][j], ','); // Read comma-separated values into grid
        }
    }

}