#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main()
{
    ifstream inFile("word.in");
    ofstream outFile("word.out");
    int N, K;
    inFile >> N >> K;

    
    int curlength = 0;
    for(int i = 0; i < N; i++)
    {
        string tem;
        //inFile >> tem;
   
        if (curlength + tem.length() > K)
        {
            outFile << endl << tem;

            curlength = tem.length();
        }
        else
        {
            if (curlength > 0) {
                outFile << " ";

            }
            outFile << tem;
            curlength += tem.length();
        }
    }
    outFile << endl;

    
    inFile.close();
    outFile.close();
    return 0;
}