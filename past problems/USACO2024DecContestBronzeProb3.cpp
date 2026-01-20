#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

//insertion
void insert_ordered(vector<string>& v, vector<int>& count, vector<vector<bool>>& grid, string x, int pos, int max_n) {
    // 1. Find position
    auto it = lower_bound(v.begin(), v.end(), x);
    int index = distance(v.begin(), it);

    // 2. If new substring
    if (it == v.end() || *it != x) {
        v.insert(it, x);
        count.insert(count.begin() + index, 1);
        
        // Insert a new row in grid
        vector<bool> new_row(max_n, true);
        grid.insert(grid.begin() + index, new_row);
    }
    else {
        // 3. Substring already exists just increment count
        count[index]++;
    }

    // 4. Mark the grid for the specific appearance of this substring
    // We mark the positions of all 3 characters
    if (pos + 2 < max_n) {
        grid[index][pos] = false;
        grid[index][pos + 1] = false;
        grid[index][pos + 2] = false;
    }
}

int main() {
    vector<string> answers;
    int answercount = 0;;
    vector<int> count;
    vector<string> vec;

    //
    //
    //
    //Below
    //
    //
    //

    vector<vector<bool>> grid = {};
    int n, f;
    string moo;

    cin >> n >> f >> moo;

    //Special Cases n=3
    if (n == 3) {
        // Case 1: All different
        if (moo[0] != moo[1] && moo[1] != moo[2] && moo[0] != moo[2]) 
        {
            cout << 2 << endl;
            cout << moo[0] << moo[1] << moo[1] << endl;
            cout << moo[0] << moo[2] << moo[2] << endl;
            return 0;
        }
        // Case 2: AAA && BAA
        else if ((moo[0] == moo[1] && moo[1] == moo[2]) || (moo[0] != moo[1])) 
        {
            cout << "25" << endl ;
            for (int i = 0; i < 26; i++) 
            {
                char current_letter = (char)('a' + i);
                if (current_letter != moo[0]) 
                {
                    cout << current_letter << moo[1] << moo[1] << endl;
                }
            }
            return 0;
        }
        // Case 3: AAB
        else 
        {
            cout << moo[0] << moo[1] << moo[1] << endl;
            return 0;
        }
    }

    //n>3
    for (int i = 0; i <= (int)moo.size() - 3; i++) {
        if (moo[i] != moo[i + 1] && moo[i + 1] == moo[i + 2]) 
        {
            string sub = moo.substr(i, 3);
            insert_ordered(vec, count, grid, sub, i, n);
        }
    }

    // non corrupted
    for (size_t i = 0; i < vec.size(); i++) {
        if (count[i] >= f) 
        {
            answercount++;
            answers.push_back(vec[i]);
        }
    }

   //corrupted
    for (size_t i = 0; i < vec.size(); i++) {
        if (count[i] == f-1) {
            for (int j = 0; j <= (int)moo.size() - 3; j++) {
                if (grid[i][j] == true && grid[i][j+1] == true && grid[i][j+2] == true)
                {
                    //1&2
                    if(moo[j] == vec[i][0] && moo[j+1] == vec[i][1])
                    {
                        answercount++;
                        answers.push_back(vec[i]);
                        break;
                    }
                    //2&3
                    else if(moo[j+1] == vec[i][1] && moo[j+2] == vec[i][2])
                    {
                        answercount++;
                        answers.push_back(vec[i]);
                        break;
                    }
                    //1&3
                    else if(moo[j] == vec[i][0] && moo[j+2] == vec[i][2])
                    {
                        answercount++;
                        answers.push_back(vec[i]);
                        break;
                    }
                }
            }
        }
    }
    cout << answercount << endl;
    sort(answers.begin(), answers.end());;
    for(int i=0;i<answercount;i++)
    {
        cout << answers[i] << endl;
    }

    return 0;
}
