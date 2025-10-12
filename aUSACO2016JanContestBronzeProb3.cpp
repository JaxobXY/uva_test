#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

struct pos
{
    int x;
    int y;
    vector<int> timeofentry;
    int maxtimedistance;
};

char takemovement(char f, int j, int stepsbefore)
{
    if(f=='N')
    {

    }
}

int main()
{
    ifstream fin("mowing.in");
    ofstream fout("mowing.out");
    int n;
    fin >> n;
    int stepsbefore=0;
    for(int i=0;i<n;i++)
    {
        char x;
        int dis;

        fin >> x >> dis;
        takemovement(x,dis);
        stepsbefore++;
    }
}
