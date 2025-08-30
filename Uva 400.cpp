#include<iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

int main()
{
    vector <string> filenames;
    int nnames;
    int maxlen = 0;
    cin >> nnames;

    for(int i = 0; i < nnames; i++)
    {
        string name;
        cin >> name;
        filenames.push_back(name);
        if (name.length() > maxlen) {
            maxlen = name.length();
        }
    }
    
    std::sort(filenames.begin(), filenames.end());

    // Calculate number of columns correctly
    int cols = 1;
    while (cols * maxlen + (cols - 1) * 2 <= 60) {
        cols++;
    }
    cols--; // Step back to the last valid number of columns
    
    int rows = (nnames + cols - 1) / cols; // Ceiling division

    cout << string(60, '-') << endl;

    for(int i = 0; i < rows; i++)
    {
        for(int j = 0; j < cols; j++)
        {
            int index = i + j * rows;
            if(index < filenames.size())
            {
                cout << filenames[index];
                if (j < cols - 1) {
                    // Add padding for all but last column
                    int padding = maxlen + 2 - filenames[index].length();
                    cout << string(padding, ' ');
                }
            }
        }
        cout << endl;
    }
}