#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <set>
#include <utility>

using namespace std;



int logic(int l,int a,int b,vector<vector<char>>& grid,vector<pair<int,int>>& nonw)
{
    int starcount = 0;
    //logic
    for(int j=0;j<nonw.size();j++)
    {
        //gray
        if(grid[nonw[j].first][nonw[j].second] == 'G')
        {
            //current
            grid[nonw[j].first][nonw[j].second] = '*';
            starcount++;
            //next
            if(grid[nonw[j].first+b][nonw[j].second+a] == 'B')
            {
                grid[nonw[j].first+b][nonw[j].second+a]='b';
                starcount ++;
            }
            else if(grid[nonw[j].first+b][nonw[j].second+a]== 'G')
            {
                grid[nonw[j].first+b][nonw[j].second+a] = 'P';
                starcount ++;
            }
            else
            {
            }
        }
        else if(grid[nonw[j].first][nonw[j].second] == 'B')
        {
            //previous spot+current
            if((nonw[j].first-b)>=0 && (nonw[j].second-a)>=0)
            {
                if(a>0 || b>0)
                {
                    if(grid[nonw[j].first-b][nonw[j].second-a] == 'G' || grid[nonw[j].first-b][nonw[j].second-a] == 'P' )
                    {
                        grid[nonw[j].first-b][nonw[j].second-a] = '*';
                        grid[nonw[j].first][nonw[j].second] = '*';
                        starcount +=2;
                    }
                    else
                    {
                        return -1;
                    }
                }
                else
                {
                    grid[nonw[j].first][nonw[j].second] = '*';
                    starcount++;
                }

            }
            if(grid[nonw[j].first+b][nonw[j].second+a] == 'G')
            {
                grid[nonw[j].first+b][nonw[j].second+a] = 'P';
            }
            else if(grid[nonw[j].first+b][nonw[j].second+a] == 'B')
            {
                grid[nonw[j].first+b][nonw[j].second+a] = 'G';
            }

            
        }
        else if(grid[nonw[j].first][nonw[j].second] == 'b')
        {
            //previous spot+current
            if((nonw[j].first-b)>=0 && (nonw[j].second-a)>=0)
            {
                if(a>0 || b>0)
                {
                    grid[nonw[j].first][nonw[j].second] = '*';
                     starcount +=1;
                }
                else
                {
                    grid[nonw[j].first][nonw[j].second] = '*';
                    starcount++;
                }

            }
            if(grid[nonw[j].first+b][nonw[j].second+a] == 'G')
            {
                grid[nonw[j].first+b][nonw[j].second+a] = 'P';
            }
            else if(grid[nonw[j].first+b][nonw[j].second+a] == 'B')
            {
                grid[nonw[j].first+b][nonw[j].second+a] = 'b';
            }

            
        }
    }
    return starcount;
}

int main()
{
    int n;
    
    cin >> n;

    for(int i=0;i<n;i++)
    {
        int l,a,b;
        cin >> l >> a >> b;
        vector<vector<char>> grid;
        vector<pair<int,int>> nonw;

        //
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
                    nonw.push_back(std::make_pair(j,k));
                }

            }
        }
        if(ireland)
        {
            cout << logic(l, a, b, grid, nonw) << endl;
        }

    }
    
    return 0;

}