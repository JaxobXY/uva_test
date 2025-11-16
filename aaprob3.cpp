#include <iostream>

using namespace std;
int main()
{
    int n;
    cin >> n;
    for(int i = 0; i < n; i ++)
    {
        int n2;
        cin >> n2;
        int hello[n2] = {0};
        for(int j = 0; j < n2; j ++)
        {
            cin >> hello[j];
        }

        for(int j = 0; j < n2; j ++)
        {
            for(int k = j+1; k < n2; k ++)
            {
                if(hello[j] > hello[k] && ((hello[j]%2 == 0 && hello[k]%2 == 1) || (hello[j]%2 == 1 && hello[k]%2 == 0)))
                {
                    int temp;
                    temp = hello[j];
                    hello[j] = hello[k];
                    hello[k] = temp;
                }
            }
        }
        for(int j=0;j<n2;j++)
        {
            cout << hello[j];
        }
        cout << endl;
    }
    return 0;
}