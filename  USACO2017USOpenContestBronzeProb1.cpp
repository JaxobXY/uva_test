#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;
int main()
{
    ifstream fin("lostcow.in");
    ofstream fout("lostcow.out");

    int x, y;
    fin >> x >> y;
    int ans = 0;
    int step = 1;
    while(!(y<x+step && y<x) && !(y>x-step && y>x))
    {
        ans += step*2;
        step *= 2;

    }
    if(y>=x)
    {
        ans += y-(x+step/2);
    }
    else
    {
        ans += (x-step/2)-y;
    }
    fout << ans << endl;
    fin.close();
    fout.close();
    return 0;   
}