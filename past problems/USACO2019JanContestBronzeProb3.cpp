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
    vector<string> animals;
    ifstream fin("guess.in");
    ofstream fout("guess.out");
    fin >> n;
    vector<string> attributes;
    vector<vector<string>> animalattributes(n);
    
    for(int i=0;i<n;i++)
    {
        string name;
        int p;
        fin >> name >> p;
        animals.push_back(name);
        for(int j=0;j<p;j++)
        {
            string tempattribute;
            fin >> tempattribute;
            animalattributes[i].push_back(tempattribute);
        }
    }
    
    int max = 0;
    for(int i=0;i<n;i++)
    {
        for(int j=i+1;j<n;j++)
        {  
            int counter = 0;
            
            
            for(int k = 0; k < animalattributes[i].size(); k++)
            {
                for(int l = 0; l < animalattributes[j].size(); l++)
                {
                    if(animalattributes[i][k] == animalattributes[j][l])
                    {
                        counter++;
                    }
                }
            }
            if(counter > max)
            {
                max = counter;
            }
        }
    }
    
    fout << max + 1 << endl;

    fin.close();
    fout.close();
    return 0;
}