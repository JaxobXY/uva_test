#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

int main()
{
    ifstream fin("blocks.in");
    ofstream fout("blocks.out");
    int n;
    fin >> n;
    vector<pair<string, string>> blocks(n);

    for (int i = 0; i < n; i++)
    {
        string first;
        string second;
        fin >> first >> second;
        blocks[i] = make_pair(first, second);
        // OR alternatively: blocks[i] = {first, second};
    }
    
    int alphabet[26] = {0};
    for(int i = 0; i < n; i++)
    {
        int count1[26] = {0};
        int count2[26] = {0};
        
        for(int j = 0; j < blocks[i].first.length(); j++)
        {
            count1[blocks[i].first[j] - 'a']++;
        }
        
        for(int j = 0; j < blocks[i].second.length(); j++)
        {
            count2[blocks[i].second[j] - 'a']++;
        }
        
        for(int j = 0; j < 26; j++)
        {
            alphabet[j] += max(count1[j], count2[j]);
        }
    }
    
    for(int i = 0; i < 26; i++)
    {
        fout << alphabet[i] << endl;
    }
    
    fin.close();
    fout.close();
    return 0;
}