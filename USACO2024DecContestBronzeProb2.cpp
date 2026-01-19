#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <set>

using namespace std;



int main()
{
    int n,q;
    cin >> n >> q;
    vector<vector<int>> xy(n, std::vector<int>(n, 0));
    vector<vector<int>> yz(n, std::vector<int>(n, 0));
    vector<vector<int>> xz(n, std::vector<int>(n, 0));
    int total = 0;
    for (int i=0;i<q;i++)
    {
        int x,y,z;
        cin >> x >> y >> z;
        xy[x][y]+=1;
        yz[y][z]+=1;
        xz[x][z]+=1;
        if(xy[x][y] == n)
        {
            total++;
        }
        if(yz[y][z] == n)
        {
            total++;
        }
        if(xz[x][z] == n)
        {
            total++;
        }
        cout << total << endl;
    }
    return 0;

}