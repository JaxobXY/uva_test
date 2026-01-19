#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

int main()
{
    int n;
    ifstream fin("balancing.in");
    ofstream fout("balancing.out");
    fin >> n;
    
    vector<int> x(n), y(n);
    for(int i = 0; i < n; i++)
    {
        fin >> x[i] >> y[i];
    }
    
    int minmax = INT_MAX;
    
    // Try vertical fence positions between x-coordinates
    for(int i = 0; i < n; i++)
    {
        int a = x[i] + 1;  // Place fence just to the right of this cow
        if(a % 2 != 0) a++; // Make it even
        
        // Try horizontal fence positions between y-coordinates
        for(int j = 0; j < n; j++)
        {
            int b = y[j] + 1;  // Place fence just above this cow
            if(b % 2 != 0) b++; // Make it even
            
            int tl = 0, tr = 0, br = 0, bl = 0;
            
            for(int k = 0; k < n; k++)
            {
                if(x[k] < a && y[k] > b) tl++;
                else if(x[k] > a && y[k] > b) tr++;
                else if(x[k] < a && y[k] < b) bl++;
                else if(x[k] > a && y[k] < b) br++;
            }
            
            int max_value = max({tl, tr, bl, br});
            if(max_value < minmax)
            {
                minmax = max_value;
            }
        }
    }
    
    fout << minmax << endl;
    fin.close();
    fout.close();
    return 0;
}