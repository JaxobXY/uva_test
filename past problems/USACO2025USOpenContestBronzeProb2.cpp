#include <iostream>
#include <vector>

using namespace std;



int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    
    cin >> t;

    for(int i=0;i<t;i++)
    {
        int n;
        cin >> n;
        vector<int> count(n+1,0);
        int max = 0;
        int answer = 0;
        for(int j=0;j<n;j++)
        {
            int temp;
            cin >> temp;
            count[temp] += 1;
            if(temp > max)
            {
                max = temp;
            }
            if(count[temp] == 2)
            {
                answer += 2;
            }
        }
        if(count[max] >= 2)
        {
            answer -= 1;
        }
        else
        {
            answer+=1;
        }
        cout << answer << endl;
    }
    
    return 0;

}