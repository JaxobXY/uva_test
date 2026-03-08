#include <iostream>
#include <vector>
#include <climits>

using namespace std;
#define int64 long long


int main()
{
    ios::sync_with_stdio(0); cin.tie(0);
    int64 n,t;
    
    cin >> n >> t;
    vector<pair<int64,int64>> inputstream;
    int64 linput=0;
    int64 rinput=0;
    int cur=0;
    bool l=false;
    bool r=false;
    string input;
    cin >> input;
    bool same = true;
    int64 total = 0;
    for(int i=0;i<n;i++)
    {
        //not all same
        if(input[i]!=input[0])
        {
            same = false;
            break;
        }
    }//all same
    if(same)
    {
        //all same
        for(int j=0;j<n;j++)
        {
            int64 temp;
            cin >> temp;
            total+=temp;
        }
        cout << total << endl;
        return 0;
    }

    for(int i=0;i<n;i++)
    {
        int64 value;
        cin >> value;
        total+=value;
        //last one
        if(i==n-1)
        {
            //last R
            if(input[n-1]=='R')
            {
                if(inputstream.size() == 0)
                {
                    inputstream.push_back(make_pair(rinput,linput));
                }
                else
                {
                    inputstream[0].first+=rinput+value;
                }
            }//last l
            else
            {
                if(inputstream.size() == 0)
                {
                    if(input[n-2]=='R')
                    {
                        rinput-=cur;
                    }
                    inputstream.push_back(make_pair(rinput,linput));
                }
                else
                {                
                    inputstream[0].first+=rinput;
                }
            }
            break;
        }//new r
        if(input[i]=='R' && l)
        {
            //completed rl group
            if(i!=0)
            {
                inputstream.push_back(make_pair(rinput,linput));
            }
            r=true;
            l=false;
            linput=0;
            rinput=0;
            rinput+=value;
            cur=value;
        }//continue r
        else if(input[i]=='R' && r)
        {
            rinput+=value;
            cur = value;
        }//new l
        else if(input[i]=='L' && r)
        {
            rinput-=cur;
            linput=0;
            rinput=0;
            r=false;
            l=true;
            cur = value;
        }//continue l
        else if(input[i]=='L' && l)
        {
            linput+=value;
            cur = value;
        }//first r
        else if(input[i]=='R')
        {
            r = true;
            rinput+=value;
            cur = value;
        }//first l
        else
        {
            l = true;
            linput+=value;
            cur = value;
        }
    }
    // for(int i=0;i<inputstream.size();i++)
    // {
    //     cout << "i=" << i+1 << ", rinput=" << inputstream[i].first << ", linput=" << inputstream[i].second << endl;
    // }
    for(int i=0;i<inputstream.size();i++)
    {
        total-=min(inputstream[i].first,t);
        total-=min(inputstream[i].second,t);
    }
    cout << total;
    return 0;

}