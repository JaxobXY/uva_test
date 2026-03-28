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
        vector<int> count(n+1,0);
        for(int j=0;j<n-1;j++)
        {
            cin >> list[j];
            count[list[j]]+=1;
            cout << "cin >> " << list[j] << "count[ "<< list[j] << "]+=1" << endl;
        }
        for(int j=1;j<=n;j++)
        {
            if(j==1)
            {
                if(count[j]<1 || count[j]>2)
                {
                    cout << -1 << endl;
                    cout << "too many ones or no ones" << count[1] << endl;
                    continue;
                }
                else if(count[j]>1)
                {
                    cout << -1 << endl;
                    cout << "too many " << count[j] << "s" << endl;
                    continue;
                }
            }
        }
        if(list[n-1]!=0)
        {
            cout << -1 << endl;
            continue;
        }
        //is recently placed side right ???
        bool justabool=true;
        deque<int> rebuild;
        int smallest[2]={0,0};
        int small=0;
        for(int j=1;j<=n;j++)
        {
            if(count[j]==0 && smallest[0]==0)
            {
                smallest[0]=j;
            }
            else if(count[j]==0 && smallest[0]!=0)
            {
                smallest[0]=j;
                break;
            }
        }
        rebuild.push_back(list[n-2]);
        if(n==2)
        {
            cout << list[0] << endl;
            continue;
        }   
        for(int j=n-3;j>=0;j--)
        {
            if(list[j]==1)
            {
                if(rebuild.back()==1)
                {
                    rebuild.push_back(list[j-1]);
                    justabool=true;
                }
                else if(rebuild.front()==1)
                {
                    rebuild.push_front(list[j-1]);
                    justabool=false;
                }
                else
                {
                    cout << -1 << endl;
                    continue;
                }
            }
            else if(rebuild.size()==1)
            {
                rebuild.push_back(list[n-3]);
                justabool=true;
            }
            else
            {
                if(rebuild.back()==list[j] || justabool)
                {
                    rebuild.push_back(list[j-1]);
                    justabool=true;
                }
                else if(rebuild.front()==list[j] || !justabool)
                {
                    rebuild.push_front(list[j-1]);
                    justabool=false;
                }
                else
                {
                    cout << -1 << endl;
                    continue;
                }
            }
        }
        if(justabool)
        {
            rebuild.push_back(smallest[0]);
            justabool=false;
        }
        else if(!justabool)
        {
            rebuild.push_front(smallest[0]);
            justabool=true;
        }
        if(smallest[1]!=0)
        {
            if(justabool)
            {
                rebuild.push_back(smallest[1]);
                justabool=true;
            }
            else if(!justabool)
            {
                rebuild.push_front(smallest[1]);
                justabool=false;
            }
        }



        for(int j=0;j<rebuild.size();j++)
        {
            cout << rebuild[j];
            if(j!=rebuild.size()-1)
            {
                cout << " ";
            }
            else
            {
                cout << endl;
            }
        }
    }
    
    return 0;

}