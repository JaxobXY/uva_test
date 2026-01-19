#include <iostream>
#include <fstream>
#include <vector>

using namespace std;
int main()
{
    ifstream fin("speeding.in");
    ofstream fout("speeding.out");
    int n, m;
    fin >> n >> m;
    vector<int> slimit;
    vector<int> curlimit;
    for(int i = 0; i < n; i++)
    {
        int a, b;
        fin >> a >> b;
        for(int j = 0; j < a; j++)
        {
            slimit.push_back (b);
        }

    }
    for(int i = 0; i < m; i++)
    {
        int a, b;
        fin >> a >> b;
        for(int j = 0; j < a; j++)
        {
            curlimit.push_back (b);
        }
    }
    int maxspeed = 0;
    for(int i=0;i<100;i++)
    {
        if(curlimit[i]>slimit[i] && curlimit[i]-slimit[i]>maxspeed)
        {
            maxspeed = curlimit[i]-slimit[i];
        }
    }
    fout << maxspeed << endl;
    fin.close();
    fout.close();
    return 0;
}