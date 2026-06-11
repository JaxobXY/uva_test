#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;
#define int64 long long
#define cin fin
#define cout fout
int main()
{
    //ios::sync_with_stdio(0); cin.tie(0);

    ifstream fin("problem.in");
    ofstream fout("problem.out");
    int n,k;
    
    cin >> n >> k;
    int q;
    fin >> q;
    vector<vector<int>> grid(n,vector<int> (n,0));
    int maxx = 0;
    if(n==k)
    {
        for(int i=0;i<q;i++)
        {
            int nvalue;
            int x,y;
            cin >> x >> y >> nvalue;
            x-=1;
            y-=1;
            maxx+=nvalue-grid[x][y];
            grid[x][y] = nvalue;
        }
    }
    for(int i=0;i<q;i++)
    {
        int nvalue;
        int x,y;
        cin >> x >> y >> nvalue;
        x-=1;
        y-=1;
        grid[x][y] = nvalue;
        if(i==0)
        {
            cout << nvalue << endl;
            maxx=nvalue;
            continue;
        }
        else
        {
            for(int j=max(0 , x-k+1);j<=max(0,x-k+1)+k-1;j++)
            {
                for(int o=max(0 , y-k+1);o<=max(0,y-k+1)+k-1;o++)
                {
                    int curmax = 0;

                    for(int l=j;l<min(n-1,j+k);l++)
                    {
                        for(int m=o;m<min(n-1,o+k);m++)
                        {
                            curmax+=grid[l][m];
                        }   
                    }
                    if(curmax>=maxx)
                    {
                        maxx = curmax;
                    }
                }   
            }

        }
        cout << maxx << endl;
    }
    
    fin.close();
    fout.close();
    return 0;

}