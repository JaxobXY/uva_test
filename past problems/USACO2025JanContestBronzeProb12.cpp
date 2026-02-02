#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <set>
#include <utility>

using namespace std;




int main()
{
    int n;
    
    cin >>  n;

    for(int i=0;i<n;i++)
    {
        int l,a,b;
        cin >> l >> a >> b;
        vector<vector<char>> grid;
        vector<pair<int,int>> B;
        vector<pair<int,int>> G;

        bool ireland = true;
        for(int j=0;j<l;j++)
        {

            vector<char> temp;
            grid.push_back(temp);
            for(int k=0;k<l;k++)
            {

                char argentina;
                cin >> argentina;
                grid[j].push_back(argentina);
                if(argentina == 'B' || argentina == 'G')
                {
                    if(argentina == 'B' && (j<b || k<a))
                    {
                        cout << -1 << endl;
                        j=l;
                        k=l;
                        ireland = false;
                    }
                    if(argentina == 'B')
                    {
                        B.push_back(std::make_pair(j,k));
                    }
                    else
                    {
                        G.push_back(std::make_pair(j,k));
                    }

                }

            }
        }

        if(ireland)
        {
            for(int j=0;j<B.size();j++)
            {
                if(grid[B[j].first-a][B[j].second-b] == 'G' || grid[B[j].first-a][B[j].second-b] == '*' || grid[B[j].first-a][B[j].second-b] == 'B')
                {
                    grid[B[j].first][B[j].second] = '*';
                    grid[B[j].first-a][B[j].second-b] = '*';
                }
                else
                {
                    cout << -1 << endl;
                    j=B.size();
                    ireland = false;
                }
            }
        }

        if(ireland)
        {
            for(int j=0;j<G.size();j++)
            {
                if(grid[G[j].first-a][G[j].second-b] == 'P' || grid[G[j].first-a][G[j].second-b] == '*' || grid[G[j].first-a][G[j].second-b] == 'G')
                {
                    if(grid[G[j].first-a][G[j].second-b] == 'P')
                    {
                        grid[G[j].first-a][G[j].second-b] = '*';
                    }
                    grid[G[j].first][G[j].second] = '*';
                }
                else
                {
                    grid[G[j].first][G[j].second] = '*';
                }
            }
        }
        
        if(ireland)
        {
            int starcount = 0;
            for(int j=0;j<l;j++)
            {
                for(int k=0;k<l;k++)
                {
                    if(grid[j][k] == '*')
                    {
                        starcount ++;
                    }
                }
            }
            cout << starcount << endl;
        }

    }
    
    return 0;

}