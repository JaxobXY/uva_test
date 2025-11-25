#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <set>

using namespace std;



int main()
{
    long long n;
    long long k;
    cin >> n >> k;
    vector<long long> dayswatched;
    for(int i=0;i<n;i++)
    {
        long long temp;
        cin >> temp;
        dayswatched.push_back(temp);
    }
    long long daycount = 0;
    long long totalmoney = 0;
    while(daycount < n)
    {
        bool extend = true;
        long long curmoney = 1+k;
        while(extend == true)
        {
            if(daycount == n - 1)
            {
                extend = false;
            }
            else if((dayswatched[daycount+1] - dayswatched[daycount])>k)
            {
                extend = false;
            }
            else
            {
                curmoney += (dayswatched[daycount+1] - dayswatched[daycount]);
                daycount++;
            }
        }
        totalmoney += curmoney;
        daycount++;
    }
    cout << totalmoney << endl;

    return 0;
}