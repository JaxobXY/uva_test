#include <iostream>
#include <string>
using namespace std;int main(){ios::sync_with_stdio(0); cin.tie(0);int t;cin >> t;for(int i=0;i<t;i++){string n;cin >> n;if(n.back()=='0'){cout << "E" << endl;}else{cout << "B" << endl;}}return 0;}


/*#include <iostream>
#include <string>
using namespace std;
int main()
{
    ios::sync_with_stdio(0); 
    cin.tie(0);int t;cin >> t;
    for(int i=0;i<t;i++)
    {
        string n;
        cin >> n;
        if(n.back()=='0')
        {
            cout << "E" << endl;
        }
        else
        {
            cout << "B" << endl;
        }
    }
    return 0;
}
*/