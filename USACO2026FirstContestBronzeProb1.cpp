#include <iostream>
//#include <fstream>
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
    // ifstream fin("4.in");
    // ofstream fout("output.txt");
    int t;
    
    cin >> t;

    for(int i=0;i<t;i++)
    {
        int64 a,b,ca,cb,fa;
        cin >> a >> b >> ca >> cb >> fa;
        int64 atarget, btarget;
        //how many a and b right before overflow.
        atarget=fa-1;
        btarget=cb-1;
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
        //convert b to a right now
        a=a+(b/cb)*ca;
        b=b-(b/cb)*cb;
        // cout << "a:" << a << " b:" << b << endl;
        if(bbig)//a->atarget use b
        {
            int64 aequation=(atarget-a)/ca*cb;
            needed+=aequation;
            needed-=min(b,aequation);
            b-=min(b,aequation);
            a+=(atarget-a)/ca*ca;
            if(atarget-a>0)
            {
                needed+=atarget-a;
            }
            a=atarget;
        }
        else//a->atarget use a
        {
            a=atarget;
            needed+=atarget-a;
        }
        // b->btarget use b
        if(btarget-b>0)
        {
            needed+=btarget-b;
        }
        cout << needed+1 << endl;
    }
    
    return 0;

}