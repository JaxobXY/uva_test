#include <iostream>
#include <vector>
#include <algorithm> // ADD THIS

using namespace std;

int main()
{
    int n;
    cin >> n;
    vector<int> max;
    for(int i=0;i<n;i++)
    {
        int temp;
        cin >> temp;
        max.push_back(temp);
    }
    
    // ADD THIS LINE - sort the array
    sort(max.begin(), max.end());
    
    vector<int> values;
    for(int i=0;i<n;i++)
    {
        if(i == 0 || max[i] != max[i-1]) // More efficient way to get unique values
        {
            values.push_back(max[i]);
        }
    }

    vector<long long> total_tuition;
    vector<int> curvl;
    
    // OPTIMIZED: Start j from appropriate position
    for(int i=0; i<values.size();i++)
    {
        int hits = 0;
        int curvalue = values[i];
        
        // Since array is sorted, find first occurrence
        auto it = lower_bound(max.begin(), max.end(), curvalue);
        hits = max.end() - it; // All cows from this position onward can pay
        
        total_tuition.push_back((long long)curvalue * hits);
        curvl.push_back(curvalue);
    }

    long long maxtuition = 0;
    int minimum_price = 0;
    for(int i=0; i<total_tuition.size();i++)
    {
        long long curtuition = total_tuition[i];
        int curprice = curvl[i];
        if(curtuition > maxtuition)
        {
            maxtuition = curtuition;
            minimum_price = curprice;
        }
        else if(curtuition == maxtuition && minimum_price > curprice)
        {
            minimum_price = curprice;
        }
    }
    cout << maxtuition << " " << minimum_price;
    return 0;
}