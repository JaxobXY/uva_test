#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <deque>
#include <climits>


using namespace std;
#define int64 unsigned long long


int main()
{
    ios::sync_with_stdio(0); cin.tie(0);
    int64 n;
    int64 t;
    ifstream fin("input.txt");
    fin >> n >> t;
    deque<pair<char,int64>> input(n,{'A',0}); 
    string inputs;
    fin >> inputs;
    int64 total = 0;
    for(int64 i=0;i<n;i++)
    {
        input[i].first = inputs[i];
        fin >> input[i].second;
        cout << "old total: " << total;
        total+=input[i].second;
        cout << " total += " << input[i].second << " new total: " << total << endl;
    }
    long long counter = 0;
    while(counter<n && inputs[counter]=='L')
    {
        if (!input.empty())
        {
            pair<char,int64> val = input.front();   // Get the first element
            input.pop_front();          // Remove it from the front
            input.push_back(val);       // Add it to the back
        }   
        counter++;
    }
    if(counter==n)
    {
        cout << total << endl;
        return 0;
    }
    counter = n-1;
    while(counter>=0 && inputs[counter]=='R')
    {
        if (!input.empty())
        {
            pair<char,int64> val = input.back();   // Get the first element
            input.pop_back();          // Remove it from the front
            input.push_front(val);       // Add it to the back
        }   
        counter--;
    }
    if(counter==(-1))
    {
        cout << total << endl;
        return 0;
    }
    int64 output = total;
    if(n<=2)
    {
        cout << total;
        return 0;
    }
    counter = 0;
    while(counter<n)
    {
        int64 leftminus=0;
        int64 rightminus=0;
        while(counter<=n-2 && input[counter].first=='R'&& input[counter+1].first=='R')
        {
            rightminus+=input[counter].second;
            counter+=1;
        }
        counter+=2;
        if(counter>=n)
        {
            output-=min(rightminus,t);
            break;
        }
        while(counter<n && input[counter].first=='L')
        {
            leftminus+=input[counter].second;
            counter+=1;
        }
        
        output-=min(rightminus,t);
        output-=min(leftminus,t);
    }
    cout << output;
    return 0;

}