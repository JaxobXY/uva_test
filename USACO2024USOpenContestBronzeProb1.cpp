





















//curproblem 55false















#include <iostream>
#include <string>
#include <vector>
#include <cstring>

using namespace std;



int main()
{
    ios::sync_with_stdio(0); cin.tie(0);
    int n,q;
    
    cin >> 
    
    
    n >> q;

    //full string
    vector<int> stringg;
    //each and group
    vector<vector<int>> groups;
    vector<pair<int, int>> grouplr;
    //group
    vector<int> temp;
    vector<bool> ineval;
    pair<int, int> lr = {-1,-1};
    int last;
    vector<char> outputt;
    int rtrue=-1;
    int ltrue=-1;

    bool eval1 = true;
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
                if(temp.size() == 1)
                {
                    lr.first =  i;
                }
            }
            else
            {
                stringg.push_back(0);
                temp.push_back(0);
                if(temp.size() == 1)
                {
                    lr.first =  i;
                }
                eval1 = false;
            }
            lr.second = i; 
        }
        else
        {
            if(action == "and")
            {
                stringg.push_back(2);
            }
            else
            {
                stringg.push_back(3);
                groups.push_back(temp);
                temp.clear();
                grouplr.push_back(lr);
                lr.first = -1;
                lr.second = -1;
                ineval.push_back(eval1);
                if(ltrue==-1 && eval1 == true)
                {
                    ltrue=groups.size()-1;
                }
                if(eval1 == true)
                {
                    rtrue=groups.size()-1;
                }
                eval1=true;
            }
        }
    }
    lr.second=n-1;
    groups.push_back(temp);
    temp.clear();
    grouplr.push_back(lr);
    ineval.push_back(eval1);
    if(eval1 == true && ltrue == -1)
    {
        ltrue = groups.size()-1;
    }
    if(eval1 == true)
    {
        rtrue = groups.size()-1;
    }


    int l,r;
    string input;
    for(int i=0;i<q;i++)
    {
        bool reppartfalse = false;
        //replacedpartialgroupbutnotreplaced = false
        bool bad = false;
        cin >> l >> r >> input;
        l--;
        r--;
        if(l==0 && r==n-1)
        {
            cout << 'Y';
            // cout << 10 << endl;
            continue;
        }


        //find lr groupl and groups=r
        int counter=0;
        bool exit = false;
        int groupl=-1 , groupr=-1;
        while(counter<groups.size() && !exit)
        {
            // cout << grouplr[counter].first << " " << grouplr[counter].second << endl;
            if(grouplr[counter].first <= l && l <= grouplr[counter].second && groupl == -1)
            {
                groupl=counter;
                // cout << "ran" << endl;
            }
            if(grouplr[counter].first <= r && r <= grouplr[counter].second)
            {
                groupr=counter;
                exit=true;
            }
            counter++;
        }

        if(exit==false)
        {
            if(groupl==-1)
            {
                groupl=groups.size()-1;
            }
            if(groupr==-1)
            {
                groupr=groups.size()-1;
            }
        }




        if((ltrue>groupr || rtrue<groupl && rtrue!=-1) && input == "true")
        {
            cout <<'Y';
            // outputt.push_back('Y');
            // cout << 1 << endl;
            continue;
        }
        else if((ltrue>groupr || rtrue<groupl && rtrue!=-1) && input == "false")
        {
            cout <<'N';
            // outputt.push_back('N');
            // cout << 2 << endl;
            continue;
        }
        // optimization part


         
        for(int j=0; j<grouplr.size();j++)
        {
            if(grouplr[j].second<l || grouplr[j].first>r)
            {
                // if(ineval[j]==true && input == "true")
                // {
                //     cout <<'Y';
                //     outputt.push_back('Y');
                //     goto cont;
                // }
                // else if(ineval[j]==true && input == "false")
                // {
                //     cout <<'N';
                //     outputt.push_back('N');
                //     goto cont;
                // }
                continue;
            }
            else
            {
                for(int k=grouplr[j].first;k<=grouplr[j].second;k+=2)
                {
                    if((k<l || k>r) && stringg[k]==0)
                    {
                        reppartfalse = true;
                        if(k<r)
                        {
                            k=r;
                        }
                    }
                    else if((k<l || k>r) && input == "true" && stringg[k] == 0)
                    {
                        bad=true;
                        k=r;
                    }
                }
            }
        }
        if(0)
        {
            cont:
            continue;
        }
        else if(reppartfalse == true)
        {
            if(bad)
            {
                cout << "N";
                // outputt.push_back('N');
                // cout << 3 << endl;
                continue;
            }
            cout << "Y";
            // outputt.push_back('Y');
            // cout << 4 << endl;
            continue;
        }
        else
        {
            cout << "Y";
            // outputt.push_back('Y');
            // cout << 5 << endl;
            continue;
        }
    }
    return 0;

}