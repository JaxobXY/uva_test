#include <iostream>
//#include <fstream>
#include <string>
#include <vector>
using namespace std;


int combination(int m)
{
    if(m == 2)
    {
        return 1;
    }
    int temp = m*(m-1)/2;
    return temp;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    //ifstream fin("2USACO2025USOpenContestBronzeProb1.in");
    int n, t;
    
    cin >> n >> t;
    vector<vector<int>> cache(n, vector<int>(n, -1));
    vector<vector<int>> win(n);
    vector<vector<int>> matrix(n, vector<int>(n, 0));
    
    // Read triangular grid
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j <= i; j++)
        {
            char temp;
            cin >> temp;
            if(temp == 'W')
            {
                //i win against j
                win[j].push_back(i);
                matrix[j][i] = 1;
            }
            else if(temp == 'L')
            {
                //j win against i
                win[i].push_back(j);
                matrix[i][j] = 1;
            }
        }
    }
    //cout << endl;
    for(int i=0;i<t;i++)
    {
        int count = 0;
        int a,b;
        cin >> a >> b;
        a--;
        b--;
        if(a == b)
        {
            if(win[a].size() == 0)
            {
                cout << 0;
                continue;
            }
            count = win[a].size() * (n - win[a].size()) * 2 +1;
            cout << count << endl;
            continue;
        }
        if(a>b)
        {
            swap(a,b);
        }
        if(cache[a][b]!=-1)
        {
            cout << cache[a][b];
        }
        for(int j=0;j<win[a].size();j++)
        {
            //if(matrix[b][win[a][j]] == 1)
            //{
            //    count +=1;
            //}
            if(matrix[a][j] == 1 && matrix[b][j] == 1)
            {
                count++;
            }
        }
        if(count >= 2)
        {
            int m = count;
            int m2 = n - count;
            count = m * m2 *2 + combination(m) * 2 +n;
            cout << count << endl;
            cache[a][b] = count;
        }
        else if(count == 1)
        {
            cout <<2 * n - 1 << endl;
            cache[a][b] = 2 * n - 1;
        }
        else
        {
            cout << 0 << endl;
            cache[a][b] = 0;
        }
    }
    
    return 0;
}