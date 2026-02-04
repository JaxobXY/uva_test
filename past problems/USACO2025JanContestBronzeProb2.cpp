#include <iostream>
#include <utility>
#include <algorithm>
#include <set>
#include <cstring>


using namespace std;

int input[1000001];
int previous[1000001] = {0};
int cnt[1000001] = {0};
int pre[1000001] = {0};


int main()
{
    bool debug = false;
    int n;
    long long ans = 0;
    cin >> n;
    for(int i=1;i<=n;i++)
    {
        cin >> input[i];
        previous[i] = previous[i-1];
        cnt[input[i]] +=1;
        if(cnt[input[i]] == 1)
        {
            previous[i]+=1;
            pre[input[i]] = i;
        }

        if(cnt[input[i]] >= 2)
        {
            ans += (previous[pre[input[i]]]-1);
            if(debug)
            {
                cout << "ans is now "<< ans << ". " << endl;
                cout << "ans used to be " << ans- (previous[i] - 1) << endl;
            }
        }

        if(cnt[input[i]] > 1)
        {
            pre[input[i]] = i;
        }
    }

    // for(int i=n;i>0;i--)
    // {
    //     if(cnt[input[i]] >= 2)
    //     {
    //         ans += (previous[i]-1);
    //     }
    // }
    if(debug)
    {
        cout << "ans:" << ans << endl;
    }

    memset(cnt, 0, sizeof(cnt));
    
    for(int i=n;i>0;i--)
    {
        if(debug)
        {
            cout << "i  is " << i <<". ";
        }
        cnt[input[i]]+=1;

        if(debug)
        {
            cout << "cnt[" << input[i] << "] is now "<< cnt[input[i]] << ". " << endl;
        }

        if(cnt[input[i]] >= 3)
        {
            ans-=(previous[i]-1);
            if(debug)
            {
                cout << "ans used to be "<< ans+(previous[i]-1) << " but ans - "<< previous[i]-1 << endl;
            }
        }
    }

    cout << ans;
    return 0;

}