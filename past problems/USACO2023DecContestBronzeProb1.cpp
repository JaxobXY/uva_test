#include <iostream>
#include <vector>
#include <algorithm>


using namespace std;



int main()
{
    ios::sync_with_stdio(0); cin.tie(0);
    int n,m;
    
    cin >> n >> m;
    vector<long long> allcows(n, 0);
    vector<int> eat(n, 0);

    int lt = 0;
    for(int i = 0; i < n; i++)
    {
        int temp;
        cin >> temp;
        allcows[i] = temp;

    }

    
    for(int i=0;i<m;i++)
    {
        long long canes;
        cin >> canes;
        //calculate eat
        long long lasttallest = 0;
        for(int j=0;j<n;j++)
        {
            if(allcows[j]>lasttallest)
            {
                long long tem = 0;
                eat[j] = max(0LL, min(allcows[j], canes) - lasttallest);
                lasttallest = min(canes, allcows[j]);
                allcows[j]+=eat[j];
                eat[j] = 0;
                if(lasttallest>=canes)
                {
                    break;
                }
            }
            else
            {
                eat[j] = 0;
            }
        }

    }  

    for(int i=0;i<n;i++)
    {
        cout << allcows[i] << endl;
    }
    return 0;
}