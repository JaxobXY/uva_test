#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main()
{
    ifstream fin("cowsignal.in");
    ofstream fout("cowsignal.out");

    int m, n, k;
    fin >> m >> n >> k;
    char signal[m][n];
    for(int i = 0; i < m; i++)
    {
        for(int j = 0; j < n; j++)
        {
            fin >> signal[i][j];
        }
    }
    for(int i=0;i<m;i++)
    {
        for(int j=0;j<k;j++){
            for(int l=0;l<n;l++)
            {
                for(int p=0;p<k;p++)
                {
                    fout << signal[i][l];
                }
            }
            fout << endl;
        }
    }
}