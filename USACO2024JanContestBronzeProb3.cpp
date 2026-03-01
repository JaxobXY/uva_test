//11-15 time out
//Inputs 3-5: N≤103, the answer is at most 103
//Inputs 6-10: N≤103
//Inputs 11-15: No additional constraints.
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <set>
#include <utility>
#include <unordered_set>

using namespace std;
using int64 = long long;


int main()
{
    ios::sync_with_stdio(0); cin.tie(0);
    int n;
    
    cin >> n;
    vector<int64> input(n,0);
    for(int i=0;i<n;i++)
    {
        cin >> input[i];
    }
    int64 counter = 0;
    for(int i=0;i<n;i++)
    {
        int thing = input[i];
        if(thing==0)
        {
            continue;
        }
        counter += (thing >= 0 ? thing : -thing);
        int64 temp = -1 * thing*2;
        for(int j=i+1;j<n;j++)
        {
            input[j]+=temp;
            temp-=thing;
        }
    }
    cout << counter;
    return 0;

}