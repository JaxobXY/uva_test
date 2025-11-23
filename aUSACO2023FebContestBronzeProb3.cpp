#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <set>

using namespace std;



int main()
{
    int n;
    int k;
    cin >> n >> k;
    vector<long long> days;
    for(int i=0;i<n;i++)
    {
        int temp;
        cin >> temp;
        days.push_back(temp);
    }
    int totalmoneyused = 0;
    int daycount = 1;
    while(daycount<n)
    {
        bool extend = true;
        int curcost = 1+k;
        while(extend && daycount<n)
        {
            if(days[daycount] - days[daycount-1] + 1 <1 + k)
            {
                daycount += 1;
                curcost += days[daycount] - days[daycount-1] + 1;
            }
            else
            {
                extend = false;
            }
        }
        totalmoneyused+=curcost;
    }
    cout << totalmoneyused;

    return 0;
}