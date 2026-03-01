//11-15 time out
//Inputs 3-5: N≤103, the answer is at most 103
//Inputs 6-10: N≤103
//Inputs 11-15: No additional constraints.
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <set>
#include <utility>
#include <unordered_set>

using namespace std;
using int64 = long long;


int main()
{
    ios::sync_with_stdio(0); cin.tie(0);
    ifstream fin("3.in");
    int n;
    
    fin >> n;
    vector<int64> input(n,0);
    for(int i=0;i<n;i++)
    {
        fin >> input[i];
    }
    int64 diag = -input[0];
    int64 col = -input[0];
    int64 counter = 0;
    for(int i=0;i<n;i++)
    {
        if(i==0)
        {
            counter+=abs(input[0]);
        }
        else
        {
            col=diag+col;
            diag+=input[i]+col;
            counter+=abs(input[i]+col);
            cout << "counter += " << abs(input[i] + col);
            col+=input[i];
            cout << "col: " << col << " diag: " << diag << endl;
        }
    }
    cout << counter;
    return 0;

}