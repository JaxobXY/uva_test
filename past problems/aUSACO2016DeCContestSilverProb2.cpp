#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <set>

using namespace std;

int main()
{
    int n;
    ifstream fin("citystate.in");
    ofstream fout("citystate.out");
    fin >> n;
    
    vector<pair<string, string>> citystate;
   set<pair<int, int>> possiblepairs;
    
    for(int i = 0; i < n; i++)
    {
        string temp;
        string temp2;
        string temp3;
        fin >> temp >> temp2;  
        temp3 = temp.substr(0, 2); 
        citystate.push_back({temp3, temp2});
    }
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            if(i == j)
            {
                continue;
            }
            else
            {
                if(citystate[i].first == citystate[j].second)
                {
                    if(citystate[i].second == citystate[j].first)
                    {
                        int a,b;
                        a = i;
                        b = j;
                        if (a > b) swap(a, b);
                        possiblepairs.emplace(a, b);
                    }
                }
            }
        }
    }
    fout << possiblepairs.size();
    
    fin.close();
    fout.close();
    return 0;
}