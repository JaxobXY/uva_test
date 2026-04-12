#include <iostream>
#include <vector>
#include <set>
#include <numeric>

using namespace std;
#define int64 long long


int main()
{
    ios::sync_with_stdio(0); cin.tie(0);
    vector <int> temporary(200001);
    iota(temporary.begin(),temporary.end(),0);
    int t;
    
    cin >> t;

    for(int i=0;i<t;i++)
    {
        int n;
        cin >> n;
        vector <int> list(n-1,0);
        //count of number 1
        int count = 0;
        set <int> missing;
        missing.insert(temporary.begin()+1, temporary.begin()+n+1);

        bool condition=true;
        for(int j=0;j<n-1;j++)
        {
            cin >> list[j];
            count+=(list[j]==1);
            auto it = missing.find(list[j]);
            if (it != missing.end()) {
                // cout << "erased " << list[j] << endl;
                missing.erase(it);
            }
            else if(list[j]==1 && count==2)
            {
                // cout << "there are two ones right now" << endl;
            }
            else if(list[j]>n)
            {
                condition=false;
            }
            else//too much of any number. 
            {
                condition = false;
                // cout << "uh oh there is too much of" << list[j] << endl;
            }
        }
        // too little 1's. too much covered below
        if(count==0)
        {
            goto cont;
        }
        //too many of a number including 1
        if(condition == false)
        {
            goto cont;
        }
        if(list[n-2]!=1)
        {
            goto cont; 
        }
        if(0==1)
        {
            cont:
            // cout << "i=" << i << "abort abort";
            cout << -1 << endl;
            continue;
        }
        // else{cout << i << "im good" << endl;}
        vector<int> recreate(n,0);
        int lindex=0;
        int rindex=n-1;
        bool rempty;
        //how many 1's put into the recreated vector
        int onecount=0;
        //only one one
        if(count==1)
        {
            rempty=true;
            recreate[0]=*missing.begin();
            lindex+=1;
        }
        else//two ones
        {
            rempty=false;
            recreate[0]=*missing.begin();
            recreate[n-1]=*prev(missing.end());
            lindex+=1;
            rindex-=1;
        }



        for(int j=0;j<n-1;j++)
        {
            if(rempty==true)//only left side
            {
                if(!(list[j]==1 && onecount==1))
                {
                    recreate[lindex]=list[j];
                    lindex+=1;
                }
                if(list[j]==1)
                {
                    onecount+=1;
                }
            }
            else
            {
                if(!(list[j]==1 && onecount==1))
                {
                    if(recreate[lindex-1]>recreate[rindex+1])
                    {
                        recreate[lindex]=list[j];
                        lindex+=1;
                    }
                    else
                    {
                        recreate[rindex]=list[j];
                        rindex-=1;
                    }
                    if(list[j]==1)
                    {
                        onecount+=1;
                    }
                }
            }
        }



        if(recreate[0]>recreate[n-1])
        {
            for(int j=n-1;j>=0;j--)
            {
                cout << recreate[j];
                if(j!=0)
                {
                    cout << " ";
                }
            }
        }
        else
        {
            for(int j=0;j<n;j++)
            {
                cout << recreate[j];
                if(j!=n-1)
                {
                    cout << " ";
                }
            } 
        }
        cout << endl;
    }
    
    return 0;

}