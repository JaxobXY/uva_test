#include <iostream>
#include <fstream>

using namespace std;



int main()
{
    int a,b,c;
    ifstream fin("pails.in");
    ofstream fout("pails.out");
    fin >> a >> b >> c;
    
    int temp1 = 0;
    int max;
    int bcounter = 0;
    while(temp1+b<=c)
    {
        temp1+=b;
        bcounter++;
    }
    while(temp1+a<=c)
    {
        temp1+=a;
    }
    max=temp1;
    while(bcounter > 0)
    {
        temp1-=b;
        bcounter--;
        while(temp1+a<=c)
        {
            temp1+=a;
        }
        if(temp1>max)
        {
            max=temp1;
        }
    }

    fout << max;

    fin.close();
    fout.close();
    return 0;

}