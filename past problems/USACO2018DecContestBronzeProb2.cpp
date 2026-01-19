#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>  // Need this for std::max_element

using namespace std;

int main()
{
    ifstream fin("blist.in");
    ofstream fout("blist.out");

    int n;
    fin >> n;
    vector<int> start;
    vector<int> end;
    vector<int> bucketamount;
    
    for(int i = 0; i < n; i++)
    {
        int a, b, c;
        fin >> a >> b >> c;
        start.push_back(a);
        end.push_back(b);
        bucketamount.push_back(c);
    }

    int maxendtime = *max_element(end.begin(), end.end());
    int minstarttime = *min_element(start.begin(), start.end());
    int maxbuckets;
    

    for(int i=minstarttime; i<=maxendtime; i++)
    {
        int currentbuckets = 0;
        for(int j=0; j<n; j++)
        {
            if(i>=start[j] && i<end[j])
            {
                currentbuckets += bucketamount[j];
            }
        }
        if(i == minstarttime)
        {
            maxbuckets = currentbuckets;
        }
        else
        {
            maxbuckets = max(maxbuckets, currentbuckets);
        }
    }
    fout << maxbuckets << endl;



    fin.close();
    fout.close();
    
    return 0;
}