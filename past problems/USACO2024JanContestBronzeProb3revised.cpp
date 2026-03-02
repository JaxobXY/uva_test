#include <iostream>
#include <fstream>
#include <vector>
using namespace std;
using int64 = long long;


int main()
{
    ios::sync_with_stdio(0); cin.tie(0);
    // ifstream fin("3.in");
    int n;
    
    cin >> n;
    vector<int64> input(n,0);
    for(int i=0;i<n;i++)
    {
        cin >> input[i];
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
            counter+=abs(input[i]+col);
            diag+=-(input[i]+col);
            //cout << "counter += " << abs(input[i] + col);
            col+=-(input[i]+col);
            //cout << "col: " << col << " diag: " << diag << endl;
        }
    }
    cout << counter;
    return 0;

}