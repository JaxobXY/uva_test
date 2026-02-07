#include <iostream>
#include <string>
#include <vector>


using namespace std;

int main()
{
    int n;
    
    cin >> n;
    vector<int> input;
    vector<int> count(n+1,0);
    vector<int> before(n+1,0);
    for(int i=0;i<n;i++)
    {
        int temp;
        cin >> temp;
        input.push_back(temp);
        count[temp] +=1;
    }
    if(count[0] == 0)
    {
        before[1] = 1;
    }
    for(int i=2;i<=n;i++)
    {
        before[i] = before[i-1];
        if(count[i-1] == 0)
        {
            before[i]+=1;
        }
    }
    cout << count[0] << endl;
    for(int i=1;i<=n;i++)
    {
        cout << max(before[i], count[i]) << endl;
    }
    return 0;

}