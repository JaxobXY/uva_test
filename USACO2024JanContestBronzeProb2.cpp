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
    vector<int> last(n+1,0);
    vector<int> llast(n+1,0);
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
    bool inf = false;
    int pos = s;
    int speed = 1;
    int count = 0;
    while(pos>0 && pos<=n && !inf && speed <= n && speed>= -n)
    {

        //jump pad
        if(spaces[pos].first == true)
        {
            //inf???
            // cout << "jump pad ";
            if(spaces[pos].second == 0)
            {
                //been before
                if(speed == last[pos] || speed == llast[pos])
                {
                    inf = true;
                    // cout << "been already and match";
                }
                else//not been before
                {
                    llast[pos] = last[pos];
                    last[pos] = speed;
                    // cout << "new ";
                }
            }
            else//do normal jumper stuff
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
                // cout << "jump +" << spaces[pos].second << " ";
            }
        }
        else
        {
            // cout << "target ";
            //been before
            if(/*speed == last[pos] || */ speed == llast[pos])
            {
                inf = true;
                // cout << "been before ";
            }
            else//not been before
            {
                llast[pos] = last[pos];
                last[pos] = speed;
                // cout << "new ";
            }
            if(speed>=spaces[pos].second || -1 * speed>=spaces[pos].second && broken[pos] ==false)
            {
                broken[pos] = true;
                count+=1;
                // cout << "broke a target. count is now " << count << " ";;
            }
        }



        pos+=speed;
        // cout << "pos is now " << pos << "speed is now " << speed << endl;
    }
    cout << count;
    return 0;

}