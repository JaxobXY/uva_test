#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
int main()
{
    int t;
    cin >> t;

    for(int i=0;i<t;i++)
    {
        int n;
        cin >> n;
        vector<int> dandelionse;
        vector<int> dandelionso;
        int dandocount = 0;
        int dandecount = 0;
        
        for(int j=0;j<n;j++)
        {
            int temp;
            cin >> temp;
            if(temp%2 == 0)
            {
                dandelionse.push_back(temp);
                dandecount++;
            }
            else
            {
                dandelionso.push_back(temp);
                dandocount++;
            }
        }
        
        if(dandelionso.empty()) {
            cout << "0" << endl;
            continue;
        }
        
        sort(dandelionse.begin(), dandelionse.end(), greater<int>());
        sort(dandelionso.begin(), dandelionso.end(), greater<int>());
        
        long long score = 0;
        

        for(int j=0; j < dandelionse.size(); j++) {
            score += dandelionse[j];
        }
        
        int num_to_take = (dandocount + 1) / 2;

        
        for(int j=0; j < num_to_take; j++) {
            score += dandelionso[j];
        }
        
        cout << score << endl;
    }
    return 0;
}