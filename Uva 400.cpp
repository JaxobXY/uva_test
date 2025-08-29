#include<iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

int main()
{
    vector <string> filenames;
    int nnames;
    int maxlen=99999;
    int res;
    cin>>nnames;

    for(int i=0;i<nnames;i++)
    {
        string name;
        cin>>name;
        filenames.push_back(name);
    }
    std::sort(filenames.begin(), filenames.end());
    



        res=62/(maxlen+2);
        cout<<res<<endl;

    for(int i=filenames.size();i>0;i--)
    {
        cout<<filenames[i-1]<<endl;
    }
    return 0;
}