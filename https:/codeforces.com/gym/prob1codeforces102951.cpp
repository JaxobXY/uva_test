#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;



int main()
{
    int n;
    cin >> n;
    vector<int> pointsx(n);
    vector<int> pointsy(n);

    for(int i=0;i<n;i++){
        cin >> pointsx[i];
    }
    for(int i=0;i<n;i++){
        cin >> pointsy[i];
    }
    int maxdis = 0;
    for(int i=0;i<n;i++)
    {
        for(int j=i+1;j<n;j++)
        {
            int dis;
            int tempx;
            int tempy;
            tempx=abs(pointsx[i]-pointsx[j]);
            tempy=abs(pointsy[i]-pointsy[j]);
            dis=tempx*tempx+tempy*tempy;
            if(dis>maxdis)
            {
                maxdis=dis;
            }
        }
    }
    cout << maxdis;

    return 0;

}