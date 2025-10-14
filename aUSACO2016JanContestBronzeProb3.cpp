#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;




char takemovement(char f, int j, int stepsbefore, int& x, int& y, int barf, int& timeofentry)
{
    if(f=='N')
    {
        for(int i=0;i<j;i++)
        {
            timeofentry[x][y]=barf - timeofentry[x][y]
            y++;
        }
    }
}

int main()
{
    int timeofentry[2001][2001];
    ifstream fin("mowing.in");
    ofstream fout("mowing.out");
    int n;
    fin >> n;
    int stepsbefore=0;
    int curx = 1000;
    int cury = 1000;
    for(int i=0;i<n;i++)
    {
        char x;
        int dis;

        fin >> x >> dis;
        takemovement(x,dis,curx,cury, stepsbefore, timeofentry[2001][2001]);
        stepsbefore++;
    }
}
