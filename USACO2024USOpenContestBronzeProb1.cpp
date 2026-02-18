#include <iostream>
#include <string>
#include <vector>
#include <cstring>

using namespace std;



int main()
{
    ios::sync_with_stdio(0); cin.tie(0);
    int n;
    
    cin >> n;


    //full string
    vector<int> stringg;
    //each and group
    vector<vector<int>> groups;
    //
    vector<pair<int, int>> grouplr;
    vector<int> temp;
    pair<int, int> lr = {-1,-1};
    int last;



    for(int i=0;i<n;i++)
    {
        string action;
        cin >> action;
        if(i%2 == 0)
        {
            if(action == "true")
            {
                stringg.push_back(1);
                temp.push_back(1);
            }
            else
            {
                stringg.push_back(0);
                temp.push_back(0);
                if(temp.size() == 1)
                {
                    lr.first =  i;
                }
                lr.second = i; 
            }
        }
        else
        {
            if(action == "and")
            {
                stringg.push_back(10);
            }
            else
            {
                stringg.push_back(1);
                groups.push_back(temp);
                temp.clear();
                grouplr.push_back(lr);
                lr.first = -1;
                lr.second = -1;
            }
        }
    }

    groups.push_back(temp);
    temp.clear();
    grouplr.push_back(lr);



    int q;
    cin >> q;
    int l,r;
    for(int i=0;i<q;i++)
    {
        cin >> l >> r;
    }
    return 0;

}