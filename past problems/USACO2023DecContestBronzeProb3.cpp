#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <set>
#include <utility>
#include <unordered_set>

using namespace std;
#define int64 unsigned long long 


int main()
{
    ios::sync_with_stdio(0); cin.tie(0);
    vector<long long> answers;
    int t;
    cin >> t;
    for(int z=0;z<t;z++)
    {
        int n;
    
        cin >> n;
        tuple<int64, int64, int64> mytuple = {0,0,0};
        vector<tuple<int64,int64,int64>> stuff(n,mytuple);
        for(int i=0;i<n;i++)
        {
            cin >> get<0>(stuff[i]);
        }
        for(int i=0;i<n;i++)
        {
            cin >> get<1>(stuff[i]);
        }
        for(int i=0;i<n;i++)
        {
            cin >> get<2>(stuff[i]);
        }
        sort(stuff.begin(), stuff.end(), [](const tuple<int64, int64, int64>& a, const tuple<int64, int64, int64>& b) 
        {
            return get<2>(a) > get<2>(b); // '>' for descending order
        }
        );
        int64 pass = 0;
        int64 maxtime = 18446744073709551615;
        if(n == 1)
        {
            //cout << "output n==1";
            //cout << 0 << endl;
            answers.push_back(0);
            continue;
        }
        for(int i=0;i<n-1;i++)
        {
            int64 a,b,growa,growb;
            a = get<0>(stuff[i]);
            b = get<0>(stuff[i+1]);
            growa = get<1>(stuff[i]);
            growb = get<1>(stuff[i+1]);
            //need to grow
            if(a>b)
            {
                //not possible
                if(growa>=growb)
                {
                    ///cout << "a>b but growa>=growb so impossible";
                    //cout << -1 << endl;
                    answers.push_back(-1);
                    goto skip;
                }
                else//possible
                {
                    int64 needg = a-b+1;
                    int64 growdif = growb-growa;
                    int64 temp;
                    temp = (needg+growdif-1)/growdif;
                    if(temp>pass)
                    {
                        pass = temp;
                    }
                }
            }
            else if(a == b)//same height
            {
                //impossible
                if(growa>=growb)
                {
                    //cout << "output growa>=growb && both same";
                    //cout << -1 << endl;
                    answers.push_back(-1);
                    goto skip;
                }
                else//possible
                {
                    //cout << "output growa<growb && both same";
                    //cout << 1 << endl;
                    answers.push_back(1);
                    goto skip;
                }
            }
            else//maxtime
            {
                if(growa>growb)
                {
                    int64 needg = b-a;
                    int64 growdif = growa-growb;
                    int64 temp;
                    temp = (needg+growdif-1)/growdif;
                    if(temp<maxtime)
                    {
                        maxtime = temp;
                    }
                }
            }
        }
        if(maxtime>pass)
        {
            //cout << "output maxtime > pass";
            //cout << pass << endl;
            answers.push_back(pass);
        }
        else
        {
            //cout << "output maxtime<=pass";
            //cout << -1 << endl;
            answers.push_back(-1);
        }
        if(0)
        {
            skip:
            continue;
        }
    }
    //cout << endl << endl << endl << endl;
    for(int i=0;i<t;i++)
    {
        cout << answers[i] << endl;
    }
    return 0;
}