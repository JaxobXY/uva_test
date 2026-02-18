#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <set>
#include <utility>
#include <unordered_set>

using namespace std;



int main()
{
    ios::sync_with_stdio(0); cin.tie(0);
    int n,m;
    
    cin >> n >> m;
    vector<long long> allcows(n, 0);
    vector<long long> curcows(n, 0);
    vector<int> eat(n, 0);
    vector<int> canes(m, 0);
    vector<int> lasts(n, 0);
    int last = 0;
    int lastindex = 0;


    for(int i = 0; i < n; i++)
    {
        int temp;
        cin >> temp;
        allcows[i] = temp;
        if(temp > last)
        {
            curcows[i] = temp;
            lasts[lastindex] = last;  
            lastindex = i;
            last = temp;
        }
        else
        {
           lasts[i] = last;
        }
    }
    lasts[n-1] = allcows[n-1];

    for(int i=0;i<m;i++)
    {
        cin >> canes[i];
    }
    
    for(int i=0;i<m;i++)
    {
        //calculate eat
        for(int j=0;j<n;j++)
        {
            if(curcows[j]>canes[i])
            {
                eat[j]+= canes[i] - lasts[j]-1;
                break;
            }
            else if(curcows[j] == 0)
            {
                continue;
            }
            else if(j>0)
            {
                eat[j]+= curcows[j] - lasts[j]-1;
            }
            else
            {
                eat[0] += curcows[0];
            }
        }
        //eat
        for(int j=0;j<n;j++)
        {
            if(curcows[j]!=0)
            {
                curcows[j] += eat[j];
            }
        }
        //remove the short people
        int lasttall = 0;
        for(int j=0;j<n;j++)
        {
            if(curcows[j]!=0 && curcows[j]<=lasttall)
            {
                allcows[j] = curcows[j];
                curcows[j] = 0;
            }
            else
            {
                lasttall = curcows[j];
            }
        }
        eat.assign(n, 0);  
    }
    for(int i=0;i<n;i++)
    {
        if(curcows[i]>0)
        {
            cout << curcows[i] << endl;
        }
        else
        {
            cout << allcows[i] << endl;
        }
    }
    return 0;

}