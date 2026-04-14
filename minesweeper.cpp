#include<iostream>

using namespace std;
#define gridsize 9
#define minenumber 5
char grid[gridsize][gridsize];


int coutboard()
{
    for(int i=0;i<gridsize;i++)
    {
        cout << i+1 << ":'";
    }
    cout << endl;
    for(int i=0;i<gridsize;i++)
    {
        cout << i+1 << ":";
        for(int j=0;j<gridsize;j++)
        {
            cout << grid[i][j] << " ";
        }
        cout << endl;
    }
    return 0;
}



int generatenewboard()
{
    std::fill(&grid[0][0], &grid[0][0] + gridsize*gridsize, '0');
    int coorx[minenumber];
    srand(time(0)); // seed random
    for (int i = 0; i < minenumber; i++) {
        coorx[i]=rand() % gridsize;
    }
    for (int i = 0; i < minenumber; i++) {
        int temp=rand() % gridsize;
        while(grid[coorx[i]][temp]=='b')
        {
            temp=rand() % gridsize;
        }
            grid[coorx[i]][temp]='b';
    }
    for(int i=0;i<gridsize;i++)
    {
        for(int j=0;j<gridsize;j++)
        {
            if(grid[i][j]=='b')
            {
                for(int k=i-1;k<=i+1;k++)
                {
                    for(int l=j-1;l<=j+1;l++)
                    {
                        if(k>=0 && k<gridsize && l>=0 && l<gridsize && grid[k][l]!='b')
                        {
                            grid[k][l]+=1;
                        }
                    }
                }
            }
        }
    }
}
int main()
{
    generatenewboard();
    cout << "please enter a x and y value as your first click" << endl;
    int x,y;
    cin >> x >> y;
    x--;
    y--;
    while(grid[x][y] == 'b')
    {
        generatenewboard();
    }
    
}