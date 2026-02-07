#include <iostream>
#include <string>
#include <vector>

using namespace std;


int main()
{
    int n , u;
    char grid[2001][2001];
    int count[1001][1001] = {0};
    cin >> n >> u;
    //input
    for(int i=1;i<n+1;i++)
    {
        for(int j=1; j<n+1;j++)
        {
            char temp2;
            cin >> temp2;
            grid[i][j]=temp2;
        }
    }
    int origchng = 0;
    //calculate how many need to be changed at first
    for(int i=1;i<n/2+1;i++)
    {
        for(int j=1; j<n/2+1;j++)
        {
            int dotcount = 0;
            if(grid[i][j] == '.')
            {
                dotcount ++;
            }
            if(grid[n-i+1][j] == '.')
            {
                dotcount ++;
            }
            if(grid[i][n-j+1] == '.')
            {
                dotcount ++;
            }
            if(grid[n-i+1][n-j+1] == '.')
            {
                dotcount ++;
            }
            if(dotcount>=2)
            {
                origchng += 4 - dotcount;
                //special attention
                count[i][j] += (4-dotcount);
            }
            else
            {
                origchng += dotcount;
                count[i][j] += dotcount;
            }
        }
    }
    //updates
    // cout << endl;
    cout << origchng << endl;
    int temp = origchng;
    for(int i=0;i<u;i++)
    {
        int x,y;
        cin >> x >> y;
        //change
        if(grid[x][y] == '.')
        {
            grid[x][y] = '#';
        }
        else
        {
            grid[x][y] = '.';
        }
        //lower x and y
        if(x>n/2)
        {
            x=n-x+1;
        }

        if(y>n/2)
        {
            y=n-y+1;
        }

        int dotcount = 0;
        //logic
        if(grid[x][y] == '.')
        {
            dotcount ++;
        }
        if(grid[n-x+1][y] == '.')
        {
            dotcount ++;
        }
        if(grid[x][n-y+1] == '.')
        {
            dotcount ++;
        }
        if(grid[n-x+1][n-y+1] == '.')
        {
            dotcount ++;
        }
        // cout << "old: " << count[x][y] << endl;
        //cout logic
        temp -= count[x][y];
        if(dotcount>=2)
        {
            temp += 4 - dotcount;
            // cout << "new: " << 4 - dotcount<<endl;
            count[x][y] = (4-dotcount);
        }
        else
        {
            temp += dotcount;
            // cout << "new: " << dotcount << endl;
            count[x][y] = dotcount;
        }
        cout << temp << endl;
    }
    return 0;

}