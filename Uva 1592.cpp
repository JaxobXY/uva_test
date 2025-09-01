#include <iostream>
#include <string>
#include <vector>
#include <sstream> // Added this include

using namespace std;

int main()
{
    int x;
    int y;
    string temp;
    cin >> x >> y;
    cin.ignore(); // Added this line
    
    vector<vector<string>> input(y, vector<string>()); // Changed initialization
    
    for(int i = 0; i < x; i++)
    {
        string line;
        getline(cin, line); // Changed reading method
        stringstream ss(line);
        
        for(int j = 0; j < y; j++)
        {
            getline(ss, temp, ' '); // Read comma-separated values
            input[j].push_back(temp);
        }
    }

    for(int i = 0; i < x; i++)
    {
        for(int j = 0; j < y; j++)
        {
            cout << input[j][i];
            if(j < y - 1) cout << ",";
        }
        cout << endl;
    }
    return 0;
}