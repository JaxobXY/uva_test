#include <iostream>
#include <vector>

using namespace std;
int main()
{
    int n;
    cin >> n;
    for(int i=0;i<n;i++)
    {
        int number;
        cin >> number;
        vector<int> list;
        for(int j=0;j<number;j++)
        {
            int temp;
            cin >> temp;
            list.push_back(temp);
        }
        int min = 999999999;
        for(int j=0;j<number;j++)
        {
            int test = 1;
            while(test < list[number] && list[number] & test == 0)
            {
                test ++;
            }
            if(test != 1 && test<min)
            {
                test = min;
                break;
            }
            if(min == 999999999)
            {
                while(test > list[number] && list[number] % test == 0 && test < 4*4*4*4*4*4*4*4*4)
                {
                    test ++;
                }
                if(test != 1 && test<min && test < 4*4*4*4*4*4*4*4*4)
                {
                    test = min;
                    break;
                }
            }
            
        }
        if(min != 999999999)
        {
            cout << min<< endl;
        }
        else{
            cout << "-1"<<endl;
        }
    }
    return 0;
}