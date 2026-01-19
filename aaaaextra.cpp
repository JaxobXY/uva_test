#include <iostream>
#include <string>
#include <vector>
using namespace std;



int main()
{
    int T, K;
    cin >> T >> K;
    for(int i=0;i<T;i++)
    {
        int N;
        cin >> N;
        string S;
        cin >> S;
        string temp;
        temp = S;
        bool hi = true;
        int counter = 0;
        vector<int> hello(N);
        while(temp.size()!=0 && hi)
        {
            for(int j=0;j<N-1;j++)
            {
               for(int k=2;k<(N-j);k+=2)
                {
                    if(temp.substr(j,k/2) == temp.substr(j+k/2,k/2))
                    {
                        temp.erase(j,k);
                        counter++;
                        for(int l=0;l<k;l++)
                        {
                            hello[j+l]=counter;
                        }
                        continue;
                    }
                    if(j == N*3-2 || j == N*3-3)
                    {
                        counter = -1;
                        hi = false;
                        break;
                    }
                }
                if(hi == false)
                {
                    break;
                }
            }
        }
        cout << counter;
        for(int j=0;j<N;j++)
        {
            cout << hello[j] << " ";
        }
        cout << endl;
    }
    return 0;
}