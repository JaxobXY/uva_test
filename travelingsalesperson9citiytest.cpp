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
    int64 number=9;
    
    int64 distances[9][9] = 
    {
        {0,1,2,3,4,5,6,7,8},
        {1,0,2,3,4,5,6,7,8},
        {1,2,0,3,4,5,6,7,8},
        {1,2,3,0,4,5,6,7,8},
        {1,2,3,4,0,5,6,7,8},
        {1,2,3,4,5,0,6,7,8},
        {1,2,3,4,5,6,0,7,8},
        {1,2,3,4,5,6,7,0,8},
        {1,2,3,4,5,6,7,8,0}
    };
    int64 triples[9][9][9];
    for(int i=0;i<number;i++)
    {
        for(int j=0;j<number;j++)
        {
            for(int k=0;k<number;k++)
            {
                if(i!=j && j!=k && k!=i)
                {
                    triples[i][j][k]=distances[i][j]+distances[j][k];
                }
            }
        }
    }
    long long min = 1000000000000000;
    for(int i=0;i<number;i++)
    {
        for(int j=0;j<number;j++)
        {
            for(int k=0;k<number;k++)
            {
                for(int l=0;l<number;l++)
                {
                    for(int m=0;m<number;m++)
                    {
                        for(int n=0;n<number;n++)
                        {
                            for(int o=0;o<number;o++)
                            {
                                for(int p=0;p<number;p++)
                                {
                                    for(int q=0;q<number;q++)
                                    {
                                        if(i==j || j==k || k==i)
                                        {
                                            continue;
                                        }
                                        if(l==m || m==n || n==l)
                                        {
                                            continue;
                                        }
                                        if(o==p || p==q || q==o)
                                        {
                                            continue;
                                        }
                                        if(i==l && j==m && k==n)
                                        {
                                            continue;
                                        }
                                        if(i==o && j==p && k==q)
                                        {
                                            continue;
                                        }
                                        if(o==l && p==m && q==n)
                                        {
                                            continue;
                                        }
                                        int64 temp=triples[i][j][k]+distances[k][l]+triples[l][m][n]+distances[n][o]+triples[o][p][q]+distances[q][i];
                                        if(temp<min)
                                        {
                                            min=temp;
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    cout << min;
    return 0;

}