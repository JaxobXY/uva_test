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
#define debug true

void single(const int src[7501], int (&requirement)[7501], int (&tracker)[7501], int i, int n, int match)
{
    int a[7501];
    for (int k = 1; k <= n; ++k) a[k] = src[k];
    int r = i;
    int l = i;
    int curmatch = match;
    while (l >= 1 && r <= n)
    {
        int x = a[l];
        int y = a[r];
        curmatch -= (x == requirement[l]);
        curmatch -= (y == requirement[r]);
        a[l] = y;
        a[r] = x;
        curmatch += (a[l] == requirement[l]);
        curmatch += (a[r] == requirement[r]);
        tracker[curmatch]++;
        l--;
        r++;
    }
    return;
}

void doubl(const int src[7501], int (&requirement)[7501], int (&tracker)[7501], int i, int n, int match)
{
    int a[7501];
    for (int k = 1; k <= n; ++k) a[k] = src[k];

    int l = i;
    int r = i + 1;
    int curmatch = match;

    // swap (l,r)
    int x = a[l], y = a[r];
    curmatch -= (x == requirement[l]);
    curmatch -= (y == requirement[r]);
    a[l] = y; a[r] = x;
    curmatch += (a[l] == requirement[l]);
    curmatch += (a[r] == requirement[r]);
    tracker[curmatch]++;

    // expand outward
    while (l - 1 >= 1 && r + 1 <= n)
    {
        l--;
        r++;

        int x = a[l], y = a[r];
        curmatch -= (x == requirement[l]);
        curmatch -= (y == requirement[r]);
        a[l] = y; a[r] = x;
        curmatch += (a[l] == requirement[l]);
        curmatch += (a[r] == requirement[r]);
        tracker[curmatch]++;
    }
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
    for (int i = 1; i < n; i++)
    {
        doubl(input, requirement, tracker, i, n, match);
    }

    for (int i = 0; i < n + 1; i++)
    {
        cout << tracker[i] << endl;
    }

    return 0;
}
