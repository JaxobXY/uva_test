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
    int t,k;
    
    cin >> t >> k;

    for(int i=0;i<t;i++)
    {
        int n;
        cin >> n;
        string input;
        cin >> input;
        if(n%2!=0)
        {
            cout << -1 << endl;
            continue;
        } 
        else if(k==1)
        {
            if(input.substr(0,n*3/2)==input.substr(n*3/2,n*3/2))
            {
                cout << 1 << endl;
                for(int i=0;i<3*n;i++)
                {
                    cout << 1;
                    if(i<3*n-1)
                    {
                        cout << " ";
                    }
                }    
                cout << endl;
            }
            else
            {
                cout << 3 << endl;
                for(int i=0;i<3*n;i++)
                {
                    if(input[i]=='C')
                    {
                        cout << 1;
                    }
                    else if(input[i]=='O')
                    {
                        cout << 2;
                    }
                    else
                    {
                        cout << 3;
                    }
                    if(i<3*n-1)
                    {
                        cout << " ";
                    }
                }    
                cout << endl;
            }
        }
        else
        {
            if(input.substr(0,n*3/2)==input.substr(n*3/2,n*3/2))
            {
                cout << 1 << endl;
                for(int i=0;i<3*n;i++)
                {
                    cout << 1;
                    if(i<3*n-1)
                    {
                        cout << " ";
                    }
                }    
                cout << endl;
            }
            else
            {
                for(int i=0;i<n/2;i++)
                {
                    string first=input.substr(i,3);
                    string second=input.substr(i+n/2,3);
                    if(first=="cow")
                    {
                        if(second=="cow")
                        {

                        }
                        else if(second=="owc")
                        {

                        }
                        else//wco
                        {

                        }
                    }
                    else if(first=="owc")
                    {

                    }
                    else//wco
                    {

                    }
                }
            }
        }
    }
    
    return 0;

}