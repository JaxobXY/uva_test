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
    int n,q;
    cin >> n >> q;
    vector<vector<int>> left(n, vector<int>(26, -1));
    vector<vector<int>> right(n, vector<int>(26, n));
    vector<vector<int>> rightExclude(n, vector<int>(26, n));
    string s;
    cin >> s;
    for(int i=0;i<n;i++)
    {
        if(i!=0)
        {
        left[i] = left[i - 1];
        }
        left[i][s[i]-'a']=i;
    }
    for(int i=n-1;i>=0;i--)
    {
        if(i+1<n)
        {
        right[i] = right[i + 1];
        }
        right[i][s[i]-'a']=i;
        int best = n;
        int sbest = n;


        for (int j=0;j<26;j++)
        {
            if (right[i][j] < best)
            {
                sbest = best;
                best  = right[i][j];
            }
            else if (right[i][j] < sbest)
            {
                sbest = right[i][j];
            }
        }

        for (int j=0;j<26;j++){
            if (right[i][j] == best)
            {
                rightExclude[i][j] = sbest;
            }
            else
            {
                rightExclude[i][j] = best;
            }
        }
    }

    
    for(int o=0;o<q;o++)
    {
        long long maxx = -1;
        int l,r;
        cin >> l >> r;
        l--;
        r--;
        for(int a=0;a<26;a++)
        {
            int i_pos,j,k;
            int mid;
            k = left[r][a];
            i_pos=rightExclude[l][a];
            if(i_pos>k)
            {
                continue;
            }
            mid=(i_pos + k) / 2;
            int c1,c2;
            c1=left[mid][a];
            c2=right[mid][a];
            

            if(c1 > i_pos && c1 < k) {
                long long area = 1LL*(k-c1) * (c1-i_pos);
                if(area > maxx) maxx = area;
            }
            if(c2 > i_pos && c2 < k) {
                long long area = 1LL*(k-c2) * (c2-i_pos);
                if(area > maxx) maxx = area;
            }
        }
        cout << maxx << endl;
    }
    return 0;
}
