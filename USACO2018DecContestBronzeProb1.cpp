#include <iostream>
#include <fstream>

using namespace std;

int simulate(int c[], int m[], int from, int to)
{
    if(m[from] + m[to] <= c[to])
    {
        m[to] += m[from];
        m[from] = 0;
    }
    else
    {
        m[from] -= c[to] - m[to];
        m[to] = c[to];
    }
    return 0;
}


int main()
{
    ifstream fin ("mixmilk.in");
    ofstream fout ("mixmilk.out");
    int c[3], m[3];
    for(int i = 0; i < 3; i++)
    {
        fin >> c[i] >> m[i];
    }
    int count = 0;
    for(int i = 0; i < 100; i++)
    {
        simulate(c, m, i % 3, (i + 1) % 3);
    }
    for(int i = 0; i < 3; i++)
    {
        fout << m[i] << endl;
    }
    fin.close();
    fout.close();
    return 0;

}