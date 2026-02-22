#include <iostream>
#include <string>
#include <vector>
#include <utility>


using namespace std;



int main()
{
    ios::sync_with_stdio(0); cin.tie(0);
    int n;
    string cows;
    cin >> n;
    cin >> cows;
    int counter = 0;
    bool edge = true;
    vector<pair<int,bool>> groups;
    int minmaxdays = 150001;
    for(int i=0;i<n;i++)
    {
        int temp;
        if(cows[i] == '0')
        {
            temp = 0;
            if(i == 0)
            {
                edge = false;
                continue;
            }
            if(counter !=0)
            {
                int days;
                if(edge == true)
                {
                    days=counter;
                }
                else if(counter < 3)
                {
                    days = counter;
                }
                else if(counter%2 == 1)
                {
                    days = (counter-1)/2+1;
                }
                else
                {
                    days = counter/2;
                }

                // printf("Found group of %d cows, calculated max days %d. [On edge %d]\n", 
                    // counter, days, edge);

                if(days<minmaxdays)
                {
                    minmaxdays=days;
                    // printf("Upate min maxdays to %d\n", minmaxdays);
                }
                groups.push_back(make_pair(counter,edge));
                counter = 0;
                edge = false;
            }
        }
        else
        {
            temp = 1;
            counter+=1;
        }
    }
    if(counter>0)
    {
        groups.push_back(make_pair(counter,true));
        int days;

        days=counter;
        // printf("Last group, %d cows, calculated max days %d\n", counter, days);
        if(days<minmaxdays)
        {
            minmaxdays=days;
            // printf("Upate min maxdays to %d\n", minmaxdays);
        }
    }



    int total = 0;
    for(int i=0;i<groups.size();i++)
    {

        int len = groups[i].first;
        bool edge = groups[i].second;
        if(edge)
        {
            if(len == n)
            {
                total+=1;
                // cout << "group " << i << " everything is one and length is" << n<< endl;
                continue;
            }
            else
            {
                if((minmaxdays-1)*2+1>=len)
                {
                    total +=1;
                    // cout << "group " << i << " 1 cow can cover everything" << endl;
                    continue;
                }
                else
                {
                    int temp;
                    int tem = (minmaxdays-1)*2+1;
                    temp = (len+tem-1)/(tem);
                    total+=temp;
                    // cout << "group " << i << " 1 cow can cover" << tem << "and need " << temp << "cows" << endl;
                    continue;
                }
            }
        }
        int temp;
        int tem = (minmaxdays-1)*2+1;
        temp = (len+tem-1)/(tem);
        // printf(
            // "Group %d : %d cows, 1 cow can cover %d, calculated to need %d cows\n", 
            // i, len, tem, temp);
         
        if(temp == 1 && len%2==0)
        {
            temp +=1;
            // printf("Adjusted to need %d cows\n", temp);
        }
        total+=temp;
    }
    // printf("Total at least need %d cows\n", total);
    cout << total;
    return 0;

}