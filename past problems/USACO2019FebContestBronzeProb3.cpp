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
    vector<pair<int,int>> limits;
    for (int i=0;i<n;i++)
    {
        string temp1;
        int temp2, temp3;
        fin >> temp1 >> temp2 >> temp3;
        conditions.push_back(temp1);
        limits.push_back(make_pair(temp2,temp3));
    }

    // Find first and last "none" segments
    int firstnone = -1, lastnone = -1;
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

    // BACKWARD PASS - Find initial range (working from lastnone to start)
    int initial_low, initial_up;
    initial_low = limits[lastnone].first;
    initial_up = limits[lastnone].second;
    string prev_back = "none";
    
    for (int i = lastnone-1; i >= 0; i--)
    {
        if(prev_back == "none" && conditions[i] == "none")
        {
            initial_up = min(initial_up, limits[i].second);
            initial_low = max(initial_low, limits[i].first);
        }
        else if(prev_back == "none" && conditions[i] == "on")
        {
            initial_up -= limits[i].first;
            initial_low -= limits[i].second;
            if(initial_low < 0) initial_low = 0;
        }
        else if(prev_back == "none" && conditions[i] == "off")
        {
            initial_up += limits[i].second;
            initial_low += limits[i].first;
        }
        else if(prev_back == "on" && conditions[i] == "none")
        {
            initial_up = min(initial_up, limits[i].second);
            initial_low = max(initial_low, limits[i].first);
        }
        else if(prev_back == "on" && conditions[i] == "on")
        {
            initial_up -= limits[i].first;
            initial_low -= limits[i].second;
            if(initial_low < 0) initial_low = 0;
        }
        else if(prev_back == "on" && conditions[i] == "off")
        {
            initial_up += limits[i].second;
            initial_low += limits[i].first;
        }
        else if(prev_back == "off" && conditions[i] == "none")
        {
            initial_up = min(initial_up, limits[i].second);
            initial_low = max(initial_low, limits[i].first);
        }
        else if(prev_back == "off" && conditions[i] == "on")
        {
            initial_up -= limits[i].first;
            initial_low -= limits[i].second;
            if(initial_low < 0) initial_low = 0;
        }
        else if(prev_back == "off" && conditions[i] == "off")
        {
            initial_up += limits[i].second;
            initial_low += limits[i].first;
        }
        prev_back = conditions[i];
    }

    // FORWARD PASS - Find final range (working from firstnone to end)
    int final_low = limits[firstnone].first;
    int final_up = limits[firstnone].second;
    string prev_forward = "none";
    
    for (int i = firstnone+1; i < n; i++)
    {
        if(prev_forward == "none" && conditions[i] == "none")
        {
            final_up = min(final_up, limits[i].second);
            final_low = max(final_low, limits[i].first);
        }
        else if(prev_forward == "none" && conditions[i] == "on")
        {
            final_up += limits[i].second;
            final_low += limits[i].first;
        }
        else if(prev_forward == "none" && conditions[i] == "off")
        {
            final_up -= limits[i].first;
            final_low -= limits[i].second;
            if(final_low < 0) final_low = 0;
        }
        else if(prev_forward == "on" && conditions[i] == "none")
        {
            final_up = min(final_up, limits[i].second);
            final_low = max(final_low, limits[i].first);
        }
        else if(prev_forward == "on" && conditions[i] == "on")
        {
            final_up += limits[i].second;
            final_low += limits[i].first;
        }
        else if(prev_forward == "on" && conditions[i] == "off")
        {
            final_up -= limits[i].first;
            final_low -= limits[i].second;
            if(final_low < 0) final_low = 0;
        }
        else if(prev_forward == "off" && conditions[i] == "none")
        {
            final_up = min(final_up, limits[i].second);
            final_low = max(final_low, limits[i].first);
        }
        else if(prev_forward == "off" && conditions[i] == "on")
        {
            final_up += limits[i].second;
            final_low += limits[i].first;
        }
        else if(prev_forward == "off" && conditions[i] == "off")
        {
            final_up -= limits[i].first;
            final_low -= limits[i].second;
            if(final_low < 0) final_low = 0;
        }
        prev_forward = conditions[i];
    }

    // Ensure ranges are valid
    if(initial_low < 0) initial_low = 0;
    if(final_low < 0) final_low = 0;
    
    fout << initial_low << " " << initial_up << endl;
    fout << final_low << " " << final_up << endl;

    return 0;
}