#include <iostream>
#include <vector>
#include <set>
#include <numeric>

using namespace std;
#define int64 long long


int main()
{
    ios::sync_with_stdio(0); cin.tie(0);
    vector <int> temporary(200001);
    iota(temporary.begin(),temporary.end(),0);
    int t;
    
    cin >> t;

    for(int i=0;i<t;i++)
    {
        int n;
        cin >> n;
        vector <int> list(n,0);
        //count of number 1
        int count = 0;
        set <int> missing;
        missing.insert(temporary.begin()+1, temporary.begin()+n+1);
        bool condition=true;
        for(int j=0;j<n;j++)
        {
            cin >> list[j];
            count+=(list[j]==1);
            auto it = missing.find(list[j]);
            if (it != missing.end()) {
                missing.erase(it);
            }
            else if(list[j]=1 && count==2)
            {
            }
            else//too much of any number. 
            {
                condition = false;
            }
        }
        // too little 1's. too much covered below
        if(count=0)
        {
            goto cont;
        }
        //too many of a number including 1
        if(condition = false)
        {
            goto cont;
        }
        if(0)
        {
            cont:
            cout << i << -1 << endl;
            continue;
        }
        else{cout << i << "im good" << endl;}
    }
    
    return 0;

}