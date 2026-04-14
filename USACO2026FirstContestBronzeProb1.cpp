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
    int64 t;
    
    cin >> t;

    for(int i=0;i<t;i++)
    {
        int64 a,b,ca,cb,fa;
        cin >> a >> b >> ca >> cb >> fa;
        int64 atarget, btarget;
        //how many a and b right before overflow.
        atarget=fa-1-a;
        btarget=cb;
        int64 needed=0;
        bool bbig;
        if(a>=fa || a+(b/cb)*ca>fa)
        {
            cout << 0 << endl;
            continue;
        }
        if(ca<cb)
        {
            bbig=true;
        }
        //convert
        a=a+(b/cb)*ca;
        b=(b/cb)*cb;
        cout << needed << endl;
    }
    
    return 0;

}