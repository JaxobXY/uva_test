#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <utility>
#include <vector>

using namespace std;



int main()
{
    int n;
    ifstream fin("lineup.in");
    ofstream fout("lineup.out");
    fin >> n;
    vector<pair<string, string>> cow;
    for(int i=0;i<n;i++)
    {
        string a,b,c,d,e,f;
        fin >> a >> b >> c >> d >> e >> f;
        cow.push_back({a,f});
    }
    vector<vector<string>> all_permutations;
    

    vector<string> cows = {
        "Beatrice", "Belinda", "Bella", "Bessie", 
        "Betsy", "Blue", "Buttercup", "Sue"
    };

    do {
        all_permutations.push_back(cows);
    } while(next_permutation(cows.begin(), cows.end()));
    
    sort(all_permutations.begin(), all_permutations.end());

    vector <vector<string>> validpermu;

    for(int i=0;i<40320;i++)//each permutation
    {
        bool valid = true;
        for(int j=0;j<n;j++)//each constraint
        {
            int current_cow_spot;
            for(int k=0;k<8;k++)//each cow in permutation
            {
                if (all_permutations[i][k] == cow[j].first)
                {
                    if(k == 0)
                    {
                        if(all_permutations[i][k+1] != cow[j].second)
                        {
                            valid = false;
                        }
                    }
                    else if(k == 7)
                    {
                        if(all_permutations[i][k-1] != cow[j].second)
                        {
                            valid = false;
                        }
                    }
                    else
                    {
                        if(all_permutations[i][k-1] != cow[j].second && all_permutations[i][k+1] != cow[j].second)
                        {
                            valid = false;
                        }
                    }
                }
            }
            if(valid == false)
            {
                break;
            }
        }
        if(valid == true)
        {
            validpermu.push_back(all_permutations[i]);
        }
    }
    for(int i=0;i<8;i++)
    {
        fout << validpermu[0][i] << endl;
    }
    fin.close();
    fout.close();
    return 0;
}