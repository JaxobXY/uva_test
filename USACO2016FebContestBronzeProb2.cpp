#include <iostream>
#include <fstream>

using namespace std;
int main()
{
    ifstream fin("cbarn.in");
    ofstream fout("cbarn.out");

    int n;
    fin >> n;
    int rooms[n];
    for (int i = 0; i < n; i++) 
    {
        fin >> rooms[i];
    }
    int mindistance = 10000000000;
    for(int i = 0;i < n;i++)
    {
        int distance = 0;
        for(int j=i;j < n;j++)
        {
            distance += rooms[j]*(j-i);
        }
        for(int j=0;j < i;j++)
        {
            distance += rooms[j]*(n-i+j);
        }
        if(distance<mindistance)
        {
            mindistance = distance;
        }
    }
    fout << mindistance << endl;
    fin.close();
    fout.close();
    return 0;
}