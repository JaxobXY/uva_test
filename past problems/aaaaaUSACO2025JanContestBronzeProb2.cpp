#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <set>


using namespace std;



int main()
{
    vector<int> myset;
    vector<int> firstocc;
    vector<pair<int,int>> setolaocc;
    vector<int> occ;
    int n;
    
    cin >> n;

    for(int i=0;i<n;i++)
    {
        int temp;
        cin >> temp;
        bool found = false;;
        int index = 0;
        for(int j=0;j<myset.size();j++)
        {
            if(myset[j]==temp)
            {
                found = true;
                index = j;
                break;
            }
        }
        if(found == false)
        {
            myset.push_back(temp);
        }
        setolaocc.push_back({-1,-1});

        if (found == true) 
        {
            occ[index]+=1;
            if(occ[index]>=3)
            {
                setolaocc[i].first=setolaocc[i].second;
                setolaocc[i].second=index;
            }
            else if(occ[index] == 2)
            {
                setolaocc[i].first=index;
            }
        }
        else
        {
            firstocc.push_back(temp);
            occ.push_back(1);

        }

    }
    
    int count = 0;
    int st = 0;
    for(int i=0;i<firstocc.size();i++)
    {
        for(int j=st;j<setolaocc.size();j++)
        {
            if(setolaocc[j].first>0 && setolaocc[j].first<firstocc[i])
            {
                st = j+1;
            }
            else if(i==j)
            {
                
            }
            else
            {
                count ++;
            }
        }
    }
    cout << count;
    
    return 0;

}