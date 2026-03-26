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
    int t;
    
    cin >> t;

    for(int i=0;i<t;i++)
    {
        int n;
        cin >> n;
        vector<int> list(n,0);
        for(int j=0;j<n;j++)
        {
            cin >> list[j];
        }
        deque<int> recreate;
        recreate.push_back(list[n-1]);
        recreate.push_back(list[n-2]);
        bool rightmrecent = true;
        deque<int> recreatel;
        deque<int> recreater;
        for(int j=n-3;j>=0;j--)
        {
            recreatel=recreate;
            recreater=recreate;
            recreatel.push_front(list[j]);
            recreater.push_back(list[j]);
            bool retur = false;
            if(recreatel[0]>recreatel[recreatel.size()-1] && rightmrecent=true)
            {
                retur=true;
            }
            if(recreatel.front<recreatel.back && rightmrecent=false)
            {
                retur=true;
            }
        }

    }
    
    return 0;

}