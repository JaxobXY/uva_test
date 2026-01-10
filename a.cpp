#include <iostream>

using namespace std;



int main()
{
    int T;
    cin >> T;
    for(int i=0;i<T;i++)
    {
        long long a,b,ca,cb,fa = 0;
        cin >> a >> b >> ca >> cb >> fa;
        //cout << a << b << ca << cb << fa;
        /*while(a<fa && b >= cb)
        {
            b -= cb;
            a += ca;
            //cout << cb << "b chips were exchanged for " << ca << " a chips." << endl;
        }
        if(a<fa)
        {
            cout << fa-a << endl;
        }
        else
        {
            cout << "0" << endl;
        }*/

        if(a<fa && b >= cb)
        {
            long long temp = (fa-a)/ca;
            if(b > temp * cb)
            {
                cout << endl << "0" << endl;
            }
            else
            {
                cout << endl << fa - a - ((b/cb)*ca) << endl;
            }
        }
        else if(b < cb)
        {
            cout << endl << fa - a << endl;
        }
        else
        {
            cout << endl << "0" << endl;
        }

        
    }

    return 0;
}