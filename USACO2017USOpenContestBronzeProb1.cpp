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
    bool dirr = true;
   
    while(true)
    {
        if(dirr)
        {
            if(y>=x && y<=x+step)
            {
                ans += (y-x);
                fout << ans << endl;
                fin.close();
                fout.close();
                return 0;
            }
            else
            {
                ans += step*2;
                step *= 2;
                dirr = false;
            }
        }
        else
        {
            if(y<=x && y>=x-step)
            {
                ans += (x-y);
                fout << ans << endl;
                fin.close();
                fout.close();
                return 0;
            }
            else
            {
                ans += step*2;
                step *= 2;
                dirr = true;
            }
        }
    }
}