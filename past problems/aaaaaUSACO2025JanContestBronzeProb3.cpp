#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <set>
#include <utility>
#include <unordered_set>

using namespace std;

int input[7501];
int requirement[7501];
int tracker[7501] = {0};

void single(const int src[7501], int (&requirement)[7501], int (&tracker)[7501], int i, int n, int match)
{
    if(i==1 || i==n)
    {
        tracker[match]+=1;
        return;
    }
    // local copy of input
    int a[7501];
    for (int k = 1; k <= n; ++k) a[k] = src[k];

    int r = i;
    int l = i;
    int curmatch = match;
    while (r + 1 <= n && l - 1 >= 1)
    {

        // swap in local copy only
        int temp = a[l];
        a[l] = a[r];
        a[r] = temp;

        if (a[l] == a[r])
        {
            // do nothing because match not change
        }
        else
        {
            if (a[r] != requirement[r] && a[l] == requirement[r])
            {
                curmatch++;
            }
            else if (a[r] == requirement[r] && a[l] != requirement[r])
            {
                curmatch--;
            }
            if (a[l] != requirement[l] && a[r] == requirement[l])
            {
                curmatch++;
            }
            else if (a[l] == requirement[l] && a[r] != requirement[l])
            {
                curmatch--;
            }
        }
        cout << curmatch << " l:" << l << " r:" << r << endl;
        tracker[curmatch]++;
        r++;
        l--;
    }
    return;
}

void doubl(const int src[7501], int (&requirement)[7501], int (&tracker)[7501], int i, int n, int match)
{
    if(i==1 || i==n)
    {
        tracker[match]+=1;
        return;
    }
    // local copy of input
    int a[7501];
    for (int k = 1; k <= n; ++k) a[k] = src[k];

    int r = i;
    int l = i + 1;
    int curmatch = match;
    // first two (no swap in original code, so still no swap here)
    if (a[l] == a[r])
    {
        // do nothing because match not change
    }
    else
    {
        if (a[r] != requirement[r] && a[l] == requirement[r])
        {
            curmatch++;
        }
        else if (a[r] == requirement[r] && a[l] != requirement[r])
        {
            curmatch--;
        }

        if (a[l] != requirement[l] && a[r] == requirement[l])
        {
            curmatch++;
        }
        else if (a[l] == requirement[l] && a[r] != requirement[l])
        {
            curmatch--;
        }
    }
    cout << curmatch << " l:" << l << " r:" << r << endl;
    tracker[curmatch]++;
    match = curmatch;

    while (r + 1 <= n && l - 1 >= 1)
    {


        // swap in local copy only
        int temp = a[l];
        a[l] = a[r];
        a[r] = temp;

        if (a[l] == a[r])
        {
            // do nothing because match not change
        }
        else
        {
            if (a[r] != requirement[r] && a[l] == requirement[r])
            {
                curmatch++;
            }
            else if (a[r] == requirement[r] && a[l] != requirement[r])
            {
                curmatch--;
            }

            if (a[l] != requirement[l] && a[r] == requirement[l])
            {
                curmatch++;
            }
            else if (a[l] == requirement[l] && a[r] != requirement[l])
            {
                curmatch--;
            }
        }
        cout << curmatch << " l:" << l << " r:" << r << endl;
        tracker[curmatch]++;
        r++;
        l--;
    }
    return;
}

int main()
{
    int n;
    cin >> n;

    for (int i = 1; i <= n; i++)
    {
        int temp;
        cin >> temp;
        input[i] = temp;
    }
    for (int i = 1; i <= n; i++)
    {
        int temp;
        cin >> temp;
        requirement[i] = temp;
    }
    int match = 0;
    // check match
    for (int i = 1; i <= n; i++)
    {
        if (input[i] == requirement[i])
        {
            match++;
        }
    }

    // single
    for (int i = 1; i < n + 1; i++)
    {
        single(input, requirement, tracker, i, n, match);
    }
    for (int i = 1; i < n + 1; i++)
    {
        doubl(input, requirement, tracker, i, n, match);
    }

    for (int i = 0; i < n + 1; i++)
    {
        cout << tracker[i] << endl;
    }

    return 0;
}
