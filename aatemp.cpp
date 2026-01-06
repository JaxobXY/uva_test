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

    map<pair<string,string>, long long> cnt;
    for(int i = 0; i < n; i++)
    {
        string temp;
        string temp2;
        string temp3;
        fin >> temp >> temp2;  
        temp3 = temp.substr(0, 2); 
        cnt[{ temp, temp3 }]++; 
    }
    int count = 0;


    for (const auto& [key, freq] : cnt)
    {
        const auto& c = key.first;
        const auto& s = key.second;

        if (c == s) continue; // usually excluded

        auto it = cnt.find({s, c});
        if (it != cnt.end())
        {
            // key (c,s) has reverse (s,c)
            cout << "(" << c << "," << s << ") <-> (" << s << "," << c << ")\n";
        }
    }

    fin.close();
    fout.close();
    return 0;

}