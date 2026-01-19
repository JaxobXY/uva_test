#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <set>

using namespace std;

int calc(long long n)
{
    if(n<45)
    {
        return 0;
    }
    long long a,b;
    int total = 0;
    int count = 2;
    a = 45;
    b=49;
    bool h = true;
    while(h)
    {
        if(a>n)
        {
            h=false;
        }
        else if(b>=n && a<=n)
        {
            total += n-a+1;
            h=false;
        }
        else
        {
            total += (b-a+1);
            long long tem = 1;
            for(int i=0;i<count;i++)
            {
                tem=tem*10;
            }
            a=4*tem + a;
            b= b*10+9;
        }
        count+=1;
    }
    return total;
}

int main()
{
    int t;
    cin >> t;

    for(int i=0;i<t;i++)
    {
        long long n;
        cin >> n;
        cout << calc(n) << endl;
    }
    return 0;

}