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
            // cout << "option 1" << endl;
            cout << -1 << endl;
            continue;
        } 
        else if(k==1)
        {
            // cout << "option 2" << endl;
            if(input.substr(0,n*3/2)==input.substr(n*3/2,n*3/2))
            {
                // cout << "option 3" << endl;
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
                // cout << "option 4" << endl;
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
            // cout << "option 5" << endl;
            if(input.substr(0,n*3/2)==input.substr(n*3/2,n*3/2))
            {
                // cout << "option 6" << endl;
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
                // cout << "option 7" << endl;
                vector<int> deleteorder(3*n,1);
                for(int j=0;j<n/2;j+=1)
                {
                    string first=input.substr(j*3,3);
                    string second=input.substr(j*3+3*n/2,3);
                    int fc,sc;
                    fc=first.find('C');//problem here
                    sc=second.find('C');//problem here
                    if(fc==sc)
                    {
                    }
                    else if((fc==0 && sc==1) || (fc==1 && sc==0))
                    {
                        if(fc==0)
                        {
                            deleteorder[(j)*3+2]=2;
                            deleteorder[(j)*3+3*n/2]=2;
                        }
                        else
                        {
                            deleteorder[(j)*3]=2;
                            deleteorder[(j)*3+3*n/2+2]=2;
                        }
                    }
                    else if((fc==0 && sc==2) || (fc==2 && sc==0))
                    {
                        if(fc==0)
                        {
                            deleteorder[(j)*3]=2;
                            deleteorder[(j)*3+3*n/2+2]=2;
                        }
                        else
                        {
                            deleteorder[(j)*3+2]=2;
                            deleteorder[(j)*3+3*n/2]=2;
                        }
                    }
                    else if((fc==1 && sc==2) || (fc==2 && sc==1))
                    {
                        if(fc==1)
                        {
                            deleteorder[(j)*3+2]=2;
                            deleteorder[(j)*3+3*n/2]=2;
                        }
                        else
                        {
                            deleteorder[(j)*3]=2;
                            deleteorder[(j)*3+3*n/2+2]=2;
                        }
                    }
                }
                cout << 2 << endl;
                for(int i=0;i<3*n;i++)
                {
                    cout << deleteorder[i];
                    if(i<3*n-1)
                    {
                        cout << " ";
                    }
                }
                cout << endl;
            }
        }
    }
    
    return 0;

}