#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <set>
#include <utility>
#include <unordered_set>

using namespace std;



int main()
{
    ios::sync_with_stdio(0); cin.tie(0);
    long long t;
    
    cin >> t;

    for(int i=0;i<t;i++)
    {
        long long n;
        cin >> n;
        vector<bool> okay(n+1, false);
        vector<int> input(n);
        bool empty = true;
        for(int j=0;j<n;j++)
        {
            cin >> input[j];
        }
        if(n == 2)
        {
            if(input[0] == input[1])
            {
                cout << input[0] << endl;
                // cout << endl << "size 2 works" << input[0] << endl;
            }
            else
            {
                cout << -1 << endl;
                // cout << endl << "size 2 not works" << -1 << endl;
            }
            continue;
        }
        if(n==1)
        {
            cout << input[0] << endl;
            // cout << endl << "size 1 works" << input[0] << endl;
            continue;
        }
        if(n==3)
        {
            if(input[0] == input[1])
            {
                cout << input[0] << endl;
                // cout << endl << "size 3 works" << input[0] << endl;
            }
            else if(input[0] == input[2])
            {
                cout << input[0] << endl;
                // cout << endl << "size 3 works" << input[0] << endl;
            }
            else if(input[1] == input[2])
            {
                cout << input[1] << endl;
                // cout << endl << "size 3 works" << input[1] << endl;
            }
            else
            {
                cout << -1 << endl;
                // cout << endl << "size 3 not work" << -1 << endl;
            }
            continue;
        }

        for(int j=0;j<n-2;j++)
        {
            int a,b,c,aa,bb = 0;
            a = input[j];
            b=input[j+1];
            c=input[j+2];
            aa = 1;
            if(b == a)
            {
                aa+=1;
            }
            else
            {
                bb+=1;
            }
            if(c == a)
            {
                aa+=1;
            }
            else if(c == b)
            {
                bb+=1;
            }

            if(aa >= 2)
            {
                okay[a] = true;
                empty = false;
            }
            if(bb >= 2)
            {
                //27
                okay[b] = true;
                empty = false;
            }
        }
        if(empty == false)
        {
            bool first = true;
            for(int j=0;j<=n;j++)
            {
                if(okay[j] == true && first)
                {
                    cout << j;
                    // cout << endl << "j=" << j << endl;
                    first = false;
                }
                else if(okay[j] == true)
                {
                    cout << " " << j;
                    // cout << endl << "j=" << j << endl;
                }
            }
            cout << endl;
        }
        else
        {
            cout << -1 << endl;
            // cout << endl << "empty" << -1 << endl;
        }
    }
    
    return 0;

}