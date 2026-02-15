#include <iostream>
//#include <fstream>
#include <string>
#include <vector>
using namespace std;


int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    //ifstream fin("2USACO2025USOpenContestBronzeProb1.in");
    int n, t;
    
    cin >> n >> t;
    vector<vector<int>> matrix(n, vector<int>(n, 0));
    vector<int> answers;
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
                matrix[j][i] = 1;
            }
            else if(temp == 'L')
            {
                //j win against i
                matrix[i][j] = 1;
            }
        }
    }
    //cout << endl;
     for(int i=0;i<t;i++)
    {
        int a,b;
        cin >> a >> b;
        a--;
        b--;
        int win = 0;
        for(int i=0;i<n;i++)
        {
            if(matrix[a][i] == 1 && matrix[b][i] == 1)
            {
                win +=1;
            }
        }
        if(win == 0)
        {
            //cout << 0 << endl;
            answers.push_back(0);
        }
        else if(win == 1)
        {
            //cout << 2*n-1;
            answers.push_back(2*n-1);
        }
        else
        {
            //cout << 2*win*(n-win) + n*(n-1) + n << endl;
            answers.push_back(2*win*(n-win) + win*(win-1) + win);
        }
    }
    
    //cout << endl << endl << endl << endl << endl << endl << endl << endl;
    for(int i=0;i<answers.size();i++)
    {
        cout << answers[i] << endl;
    }
    return 0;
}