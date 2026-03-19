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
const int Maxvalue = 1000000;
#define int64 long long


int main()
{
    ios::sync_with_stdio(0); cin.tie(0);
    int n,q;
    cin >> n >> q;
    vector<pair<int,int>> input(n,{0,0});
    vector<int> eachdif(Maxvalue,0);
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
        int dif = input[i].first-input[i].second;
        if(dif > 0)
        {
            // cout << "eachdif[" << dif[i] << "+=1" << endl;
            eachdif[dif]+=1;
        }
    }

    //prefix sum
    int prefix[Maxvalue+1] = {0};
    for(int i=Maxvalue; i>=0; i--)
    {
        prefix[i] = prefix[i+1] + eachdif[i];
    }

    for(int i=0;i<q;i++)
    {
        int v,s;
        cin >> v >> s;
        int total=prefix[s+1];
        // for(int j=s+1;j<Maxvalue;j++)
        // {
        //     total+=eachdif[j];
        // }
        if(total>=v)
        {
            // cout << total;
            cout << "YES" << endl;
        }
        else
        {
            // cout << total;
            cout << "NO" << endl;
        }
    }
    return 0;

}