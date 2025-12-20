#include <iostream>

using namespace std;



int main()
{
    int n1;
    for(int ding=0;ding<n1;ding++)
    {
        int n;
    int m;
    cin >> n >> m;
    int cardnumbers[n][m];
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<m;j++)
        {
            int temp;
            cin >> temp;
            cardnumbers[i][j] = temp;
        }
    }

    int total = 0;
    for(int i = 0;i<n;i++)
    {
        for(int j = i+1;j<n;j++)
        {
            for(int k=0;k<m;k++)
            {
                int curtotal = 0;
                if((cardnumbers[i][k]-cardnumbers[j][k])<0)
                {
                    curtotal += cardnumbers[j][k] - cardnumbers[i][k];
                }
                else
                {
                    curtotal += cardnumbers[i][k] - cardnumbers[j][k];
                }
                total += curtotal;
            }
        }
    }
    cout << total << endl;
    }
    
    return 0;

}