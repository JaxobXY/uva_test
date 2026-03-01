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
    int n, s;
    cin >> n >> s;
    vector<pair<bool,int>> spaces(n+1,make_pair(true, 0));
    vector<bool> broken(n+1,false);
    for(int i=1;i<=n;i++)
    {
        int jpad;
        bool jpadd;
        cin >> jpad;
        if(jpad == 0)
        {
            jpadd = true;
        } else
        {
            jpadd = false;
        }
        int value;
        cin >> value;
        spaces[i].first = jpadd;
        spaces[i].second = value;
    }
    int pos = s;
    int speed = 1;
    int count = 0;
    int counter = 0;
    while(pos>0 && pos<=n && counter <=n+1)
    {

        //jump pad
        if(spaces[pos].first == true)
        {
            if(speed>=0)
            {
                speed+=spaces[pos].second;
                speed*=-1;
            }
            else
            {
                speed-=spaces[pos].second;
                speed*=-1;
            }
        }
        else
        {
            if((speed>=spaces[pos].second || -1 * speed>=spaces[pos].second ) && broken[pos] == false)
            {
                broken[pos] = true;
                count+=1;
            }
        }



        pos+=speed;
        counter+=1;
    }
    cout << count;
    return 0;

}