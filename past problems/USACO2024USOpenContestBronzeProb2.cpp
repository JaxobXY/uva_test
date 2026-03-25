#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>
#include <set>
#include <utility>
#include <unordered_set>
#include <deque>
#include <climits>

using namespace std;
#define int64 long long


int main()
{
    ios::sync_with_stdio(0); cin.tie(0);
    int n,p;
    
    cin >> n >> p;
    int lpostx;
    int lposty;
    int num[1000+2][1000+2]={};
    int curnum=1;
    int fx;
    int fy;
    for(int i=0;i<p;i++)
    {
        int x,y;
        cin >> x >> y;
        if(i>0)
        {
            if(lpostx == x)
            {
                if(y>lposty)
                {
                    for(int j=lposty+1;j<y;j++)
                    {
                        num[x][j]=curnum;
                        // cout << "fencepost" << curnum << ":" << x << " "<< j << endl;
                        curnum++;
                    }
                }
                else
                {

                    for(int j=lposty-1;j>y;j--)
                    {
                        num[x][j]=curnum;
                        // cout << "fencepost" << curnum << ":" << x << " "<< j << endl;
                        curnum++;
                    }
                }
            }
            else
            {
                if(x>lpostx)
                {

                    for(int j=lpostx+1;j<x;j++)
                    {
                        num[j][y]=curnum;
                        // cout << "fencepost" << curnum << ":" << j << " "<< y << endl;
                        curnum++;
                    }
                }
                else
                {

                    for(int j=lpostx-1;j>x;j--)
                    {
                        num[j][y]=curnum;
                        // cout << "fencepost" << curnum << ":" << j << " "<< y << endl;
                        curnum++;
                    }
                }
            }
        }
        else
        {
            fx=x;
            fy=y;
        }
        num[x][y]=curnum;
        // cout << "post" << curnum << ":" << x << " "<< y << endl;
        lpostx = x;
        lposty = y;
        curnum++;
    }
    


    if(lpostx == fx)
    {
        if(fy>lposty)
        {

            for(int j=lposty+1;j<fy;j++)
            {
                num[fx][j]=curnum;
                // cout << "fencepost" << curnum << ":" << fx << " "<< j << endl;
                curnum++;
            }
        }
        else
        {

            for(int j=lposty-1;j>fy;j--)
            {
                num[fx][j]=curnum;
                // cout << "fencepost" << curnum << ":" << fx << " "<< j << endl;
                curnum++;
            }
        }
    }
    else
    {
        if(fx>lpostx)
        {

            for(int j=lpostx+1;j<fx;j++)
            {
                num[j][fy]=curnum;
                // cout << "fencepost" << curnum << ":" << j << " "<< fy << endl;
                curnum++;
            }
        }
        else
        {

            for(int j=lpostx-1;j>fx;j--)
            {
                num[j][fy]=curnum;
                // cout << "fencepost" << curnum << ":" << j << " "<< fy << endl;
                curnum++;
            }
        }
    }
    for(int i=0;i<n;i++)
    {
        int ifx,ify,isx,isy;
        cin >> ifx >> ify >> isx >> isy;
        // cout << " input" << ifx << " " << ify << " " << isx << " " << isy << endl;
        int disf,disb;
        disf=abs(num[ifx][ify]-num[isx][isy]);
        // cout << disf << " ";
        disb=(curnum-1)-disf;
        // cout << disb << " ";
        cout << min(disf,disb) << endl;
    }

    return 0;

}