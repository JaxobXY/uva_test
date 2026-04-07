#include <iostream>
#include <string>
#include <vector>
#include <cstring>

using namespace std;



int main()
{
    ios::sync_with_stdio(0); cin.tie(0);
    int n,q;
    
    cin >> n >> q;

    //full string
    vector<int> stringg;
    //each and group
    vector<vector<int>> groups;
    vector<pair<int, int>> grouplr;
    vector<pair<int, int>> groupf;
    //group
    vector<int> temp;
    vector<bool> ineval;
    pair<int, int> lr = {-1,-1};
    int last;
    vector<char> outputt;
    int rtrue=-1;
    int ltrue=-1;
    int rfalse=-1;
    int lfalse=-1;

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
                if(lfalse==-1)
                {
                    lfalse=i;
                }
                rfalse=i;
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
                groupf.push_back(make_pair(lfalse,rfalse));
                eval1=true;
                rfalse=-1;
                lfalse=-1;
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
    groupf.push_back(make_pair(lfalse,rfalse));


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
            // cout << 6 << " " << i << endl;
            continue;
        }
        if((grouplr[rtrue].first != -1 && grouplr[rtrue].first > r) 
        || (grouplr[ltrue].second != -1 && grouplr[ltrue].second < l))
        {
            if(input == "true")
            {
                cout << 'Y';
                // cout << 5 << " " << i << endl;
                continue;
            }
            else
            {
                cout << 'N';
                // cout << 4 << " " << i << endl;
                continue;
            }
        }
        //want false. outside false
        if(input == "false")
        {
            cout << 'Y';
            // cout << 3 << " " << i << endl;
        }
        else//want true, outside false
        {
            for(int j=0;j<groups.size();j++)
            {
                if(grouplr[j].second<l)
                {
                    continue;
                }
                else if(grouplr[j].first>r)
                {
                    continue;
                }
                else if((groupf[j].first<l && groupf[j].first != -1) || (groupf[j].second>r && groupf[j].second != -1))
                {
                    cout << "N";
                    // cout << 2 << " " << i << endl;
                    goto cont;
                }
            }
            cout << "Y";
            // cout << 1 << " " << i << endl;
            continue;
        }
        if(0)
        {
            cont:
            continue;
        }
    }
    return 0;

}