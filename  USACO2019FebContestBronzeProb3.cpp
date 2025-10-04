#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;
int main()
{
    ifstream fin("traffic.in");
    ofstream fout("traffic.out");

    int n;
    fin >> n;
    vector<string> conditions;
    vector<pair<int,int>> limits; // first is lower limit, second is upper limit
    for (int i=0;i<n;i++)
    {
        string temp1;
        int temp2, temp3;
        fin >> temp1 >> temp2 >> temp3;
        conditions.push_back(temp1);
        limits.push_back(make_pair(temp2,temp3));
    }
    int firstnone;
    int lastnone;
    for(int i=0;i<n;i++)
    {
        if(conditions[i] == "none")
        {
            firstnone = i;
            break;
        }
    }
    for(int i=n-1;i>=0;i--)
    {
        if(conditions[i] == "none")
        {
            lastnone = i;
            break;
        }
    }
    string prev;
    int up;
    int low;
    up = limits[firstnone].second;
    low = limits[firstnone].first;
    prev = ("none")
    for (int i = firstnone+1; i < n; i++)
    {
        if(prev == "none" && conditions[i] == "none")
        {
            up = min(up, limits[i].second);
            low = max(low, limits[i].first);
        }
        else if(prev == "none" && conditions[i] == "on")
        {
            up += limits[i].second;
            low += limits[i].first;
        }
        else if(prev == "none" && conditions[i] == "off")
        {
            up -= limits[i].first;
            low -= limits[i].second;
            if(low < 0) low = 0;
        }
        else if(prev == "on" && conditions[i] == "none")
        {
            up -= limits[i].first;
            low -= limits[i].second;
            if(low < 0) low = 0;
        }
        else if(prev == "on" && conditions[i] == "on")
        {
            up += limits[i].second;
            low += limits[i].first;
        }
        else if(prev == "on" && conditions[i] == "off")
        {
            up -= limits[i].first;
            low -= limits[i].second;
            if(low < 0) low = 0;
        }
        else if(prev == "off" && conditions[i] == "none")
        {
            up += limits[i].second;
            low += limits[i].first;
        }
        else if(prev == "off" && conditions[i] == "on")
        {
            up += limits[i].second;
            low += limits[i].first;
        }
        else if(prev == "off" && conditions[i] == "off")
        {
            up -= limits[i].first;
            low -= limits[i].second;
            if(low < 0) low = 0;
        }
        prev = conditions[i];
    }

}