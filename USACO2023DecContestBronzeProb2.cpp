#include <iostream>
#include <vector>
#include <utility>


using namespace std;



int main()
{
    ios::sync_with_stdio(0); cin.tie(0);
    int n;
    
    cin >> n;
    vector<int> cow(n);
    vector<pair<bool,pair<int,int>>> groups;
    vector<int> maxdays;
    int l = -1;
    int r;
    int minmaxday = 9999999;
    int day = 0;
    for(int i=0;i<n;i++)
    {
        char tem;
        cin >> tem;
        if(tem == '0')
        {
            cow[i] = 0;
        }
        else
        {
            cow[i] = 1;
        }
        if(cow[i] == 1 && l == -1)
        {
            l=i;
            r=-2;
        }
        if(cow[i] == 0 && l!=-1)
        {
            day = 1;
            r=i-1;
            if(r==l)
            {
                maxdays.push_back(1);
                if(day<minmaxday)
                {
                    minmaxday=day;
                }
                l=-1;
                r=-1;
                continue;
            }
            groups.push_back(make_pair(l == 0 || r == n-1, make_pair(l,r)));
            if(l == 0 || r == n-1)
            {
                day += r-l+1;
            }
            else if(r-l+1 == 1 || r-l+1 == 2)
            {
                maxdays.push_back(1);
                day += 1;
            }
            else
            {
                int temp = 0;
                if((r-l-1)%2!=0)
                {
                    temp = 1;
                }
                day += (r-l-1+temp)/2;
            }
            maxdays.push_back(day);
            if(day<minmaxday)
            {
                minmaxday=day;
            }
            l=-1;
            r=-1;
        }
    }
    day = 0;
    if(r==-2)
    {
        r=n-1;
        groups.push_back(make_pair(l == 0 || r == n-1, make_pair(l,r)));
        if(r==l)
        {
            maxdays.push_back(1);
            if(day<minmaxday)
            {
                minmaxday=1;
            }
            l=-1;
            r=-1;
            goto skip;
        }
        if(l == 0 || r == n-1)
        {
            maxdays.push_back(r-l+1);
            day += r-l+1;
        }
        else if(r-l+1 == 1 || r-l+1 == 2)
        {
            maxdays.push_back(1);
            day += 1;
        }
        else
        {
            int temp = 0;
            if((r-l-1)%2!=0)
            temp = 1;
            maxdays.push_back((r-l-1+temp)/2);
            day += (r-l-1+temp)/2;
        }
        if(day<minmaxday)
        {
            minmaxday=day;
        }
    }
    skip:
    int total = 0;
    if(groups.size()==0)
    {
        cout << 0;
        return 0;
    }
    if(groups.size() == 1)
    {
        if((groups[0].second.second-groups[0].second.first+1)%2 == 0)
        {
            if(groups[0].second.second == n-1 && groups[0].second.first==0)
            {
                cout << 1;
                return 0;
            }
            cout << 2;
            return 0;
        }
        else
        {
            cout << 1;
            return 0;
        }

    }


    for(int i=0;i<groups.size();i++)
    {

        if(groups[i].first == true)
        {
            int len = groups[i].second.second-groups[i].second.first+1;
            int cows = 0;
            if(minmaxday<=len && len%2 == 0 && minmaxday>=(len-2)/2+2)
            {
                total+=1;
                continue;
            }
            else if(minmaxday<=len && len%2 != 0 && minmaxday>=(len-1)/2+1)
            {
                total+=1;
                continue;
            }
            cows = len/(minmaxday*2+1);
            if(len%(minmaxday*2+1) != 0)
            {
                cows+=1;
            }
            total+=cows;
        }
        else
        {
            int len = groups[i].second.second-groups[i].second.first+1;
            int cows = 0;
            if(len%2 == 0)
            {
                cows+=2;
                len-=(2+4*(minmaxday));
                if(len>0)
                {
                    cows+=len/(1+2*minmaxday);
                    if(len%(1+2*minmaxday) > 0)
                    {
                        cows+=1;
                    }
                }
                total+=cows;
            }
            else
            {
                cows+=1;
                if(len-(1+2*minmaxday)>0)
                {
                    cows+=(len-(1+2*minmaxday))/(1+2*minmaxday);
                    if((len-(1+2*minmaxday))%(1+2*minmaxday)>0)
                    {
                        cows+=1;
                    }
                }
                total+=cows;
            }
        }
    }
    cout << total;
    return 0;

}