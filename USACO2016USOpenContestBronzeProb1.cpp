#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>


using namespace std;



int main()
{
    int n;
    int k;
    ifstream fin("diamond.in");
    ofstream fout("diamond.out");
    fin >> n >> k;
    vector<int> diamondsizes(n);
    
    for(int i=0;i<n;i++)
    {
        fin >> diamondsizes[i];
    }
    sort(diamondsizes.begin(), diamondsizes.end());
    int maxdiamonds=0;
    for(int i=0;i<n-1;i++)
    {
        int diamonds = 1;
        int j = i+1;
        while(diamondsizes[j] <= diamondsizes[i]+k && j<n)
        {
            diamonds++;
            j++;
        }
        if(diamonds > maxdiamonds)
        {
            maxdiamonds = diamonds;
        }
    }
    fout << maxdiamonds;
    fin.close();
    fout.close();
    return 0;
}