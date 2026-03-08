#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>
#include <set>
#include <utility>
#include <unordered_set>
#include <deque>
#include <climits>

using namespace std;
#define int64 long long


int main()
{
    ios::sync_with_stdio(0); cin.tie(0);
    int n,q;
    cin >> n >> q;
    vector<pair<int,int>> input(n,{0,0});
    vector<int> dif(n,0);
    for(int i=0;i<n;i++)
    {
        cin >> input[i].first;
    }
    for(int i=0;i<n;i++)
    {
        cin >> input[i].second;
    }
    for(int i=0;i<n;i++)
    {
        dif[i] = input[i].first-input[i].second;
    }
    std::sort(dif.begin(), dif.end());
    vector<int> pre(n+2,0);
    int counter = 0;
    int precounter = 1;
    while(counter<n && precounter<=n)
    {
        dif[precounter]=dif[precounter-1];
        while(counter<n && precounter <=n && dif[counter]<precounter)
        {
            pre[precounter]+=1;
            counter++;
        }
        precounter++;
    }
    

    return 0;

}