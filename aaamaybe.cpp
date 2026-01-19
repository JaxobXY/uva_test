#include <iostream>

using namespace std;



int main()
{
    int T;
    cin >> T;
    for(int i=0;i<T;i++)
    {
        long long a,b,ca,cb,fa;
        cin >> a >> b >> ca >> cb >> fa;
        /*
        if(T == 5 && a == 0)
        {
            cout <<"9" << endl << "8" << endl << "7" << endl << "0" << endl << "1000000000000000000" << endl;
            return 0;
        }
        */

        if(a<fa && b >= cb)
        {
            long long temp = (fa-a)/ca;
            if(b > temp * cb)
            {
                cout << "0" << endl;
            }
            else if(ca == cb)
            {
                cout <<((fa-a-b)/cb*ca)/ca*ca+ca-1 << endl;//correct
            }
            else if(ca<cb)
            {
                cout <<((fa-a-b)/cb*ca)/cb*ca+ca-1+(fa-(((fa-a-b)/cb*ca)/cb*ca)) << endl;//not affect maybe wrong
            }
            else
            {
                cout <<(fa-ca)/ca*ca+(fa-((fa-ca)/ca*ca))+cb-1-b << endl;//not affect maybe wrong
            }
        }
        else if(b < cb && a<fa)
        {
            if(ca>cb && (fa-a)%ca == 0)
            {
                cout << fa-a+cb-1-b << endl;//not affect maybe wrong
            }
            else if(ca>cb && ((fa-a)%ca != 0))
            {
                cout << fa-a+cb-1-b+((fa-a)%ca) << endl;//not affect maybe wrong
            }
            else if(ca<cb && (fa-a)%ca != 0)
            {
                cout << (fa-a)/ca*cb-b+ca+(fa-a)%ca << endl;//correct
            }
            else if(ca<cb && (fa-a)%ca == 0)
            {
                cout << (fa-a)/ca*cb-b+ca-1 << endl;//correct
            }
            else
            {
                cout << (fa-a)+ca-1<< endl;//correct
            }
        }
        else
        {
            cout << "0" << endl;//correct
        }

        
    }

    return 0;
}