#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
#define int64 long long


int main()
{
    ios::sync_with_stdio(0); cin.tie(0);
    int n,k;
    
    cin >> n >> k;
    int q;
    cin >> q;
    int grid[n][n];
    int maxx;
    for(int i=0;i<q;i++)
    {
        int nvalue;
        int x,y;
        cin >> x >> y >> nvalue;
        grid[x][y] = nvalue;
        if(i==0)
        {
            cout << nvalue;
            maxx=nvalue;
        }
        else
        {
            for(int j=max(0 , x-k+1);j<=max(0,x-k+1)+k-1;j++)
            {
                for(int n=max(0 , y-k+1);n<=max(0,y-k+1)+k-1;n++)
                {


                    for(int l=j;l<=j+k;l++)
                    {
                        for(int m=n;m<=n+k;m++)
                        {
                    
                        }   
                    }
                }   
            }
        }
    }
    
    return 0;

}