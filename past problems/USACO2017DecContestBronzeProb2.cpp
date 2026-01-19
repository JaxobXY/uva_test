#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>

using namespace std;
int main()
{
    ifstream fin("shuffle.in");
    ofstream fout("shuffle.out");
    int n;
    fin >> n;
    int pat[n];
    for(int i=0;i<n;i++)
    {
        fin >> pat[i];
        pat[i]--;
    }

    string cowl[n];
    for(int i=0;i<n;i++)
    {
        fin>>cowl[i];
    }

    string temp[n];
    for(int round=0;round<3;round++)
    {
        for(int i=0;i<n;i++)
        {
            temp[i] = cowl[pat[i]];
        }
        for(int i=0;i<n;i++)
        {
            cowl[i] = temp[i];
        }
    }

    for(int i=0;i<n;i++)
    {
        fout << cowl[i] << endl;
    }
    fin.close();
    fout.close();
    return 0;
}