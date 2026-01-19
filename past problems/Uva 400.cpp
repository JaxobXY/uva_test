#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <iomanip>

using namespace std;

int main()
{
    int nnames;
    while(cin >> nnames)
    {
        vector<string> filenames;
        int maxlen = 0;
        
        for(int i = 0; i < nnames; i++)
        {
            string name;
            cin >> name;
            filenames.push_back(name);
            maxlen = max(maxlen, (int)name.length());
        }
        
        sort(filenames.begin(), filenames.end());

        int cols;
        if (maxlen >= 60) {
            cols = 1;
        } else {
            cols = 1 + (60 - maxlen) / (maxlen + 2);
        }
        
        int rows = (nnames + cols - 1) / cols;

        cout << string(60, '-') << endl;

        for(int i = 0; i < rows; i++)
        {
            for(int j = 0; j < cols; j++)
            {
                int index = j * rows + i;
                if(index < filenames.size())
                {
                    // For all but last column: left-justify in field of width maxlen + 2
                    if (j < cols - 1) {
                        cout << setw(maxlen + 2) << left << filenames[index];
                    } else {
                        // For last column: just print the filename (no extra trailing spaces)
                        cout << filenames[index];
                    }
                }
            }
            cout << endl;
        }
    }
    return 0;
}