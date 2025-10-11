#include <iostream>
#include <fstream>
#include <set>

using namespace std;

int main()
{
    ifstream fin("tttt.in");
    ofstream fout("tttt.out");
    char board[3][3];
    for(int i = 0; i < 3; i++)
    {
        for(int j = 0; j < 3; j++)
        {
            fin >> board[i][j];
        }
    }
    
    // Initialize database to track single winners
    bool singleWinners[26] = {false}; // track which letters have single wins
    
    // Initialize set for duo winner pairs
    set<pair<char, char>> duoWinnerPairs;
    
    int singwin = 0;
    int duowin = 0;
    
    // Check rows
    for(int i = 0; i < 3; i++)
    {
        if(board[i][0] == board[i][1] && board[i][1] == board[i][2])
        {
            singleWinners[board[i][0]-'A'] = true;
        }   
    }
    
    // Check columns
    for(int i = 0; i < 3; i++)
    {
        if(board[0][i] == board[1][i] && board[1][i] == board[2][i])
        {
            singleWinners[board[0][i]-'A'] = true;
        }   
    }
    
    // Check diagonals
    if(board[0][0] == board[1][1] && board[1][1] == board[2][2])
    {
        singleWinners[board[0][0]-'A'] = true;
    }
    if(board[0][2] == board[1][1] && board[1][1] == board[2][0])
    {
        singleWinners[board[0][2]-'A'] = true;
    }
    
    // Count unique single winners
    for(int i = 0; i < 26; i++)
    {
        if(singleWinners[i])
        {
            singwin++;
        }
    }
    
    // Check duo wins for rows
    set<char> s;
    for(int i = 0; i < 3; i++)
    {
        s.insert(board[i][0]);
        s.insert(board[i][1]);
        s.insert(board[i][2]);
        if(s.size() == 2)
        {
            auto it = s.begin();
            char c1 = *it;
            char c2 = *(++it);
            // Store in sorted order to avoid duplicates
            if(c1 > c2) swap(c1, c2);
            duoWinnerPairs.insert({c1, c2});
        }
        s.clear();
    }
    
    // Check duo wins for columns
    for(int i = 0; i < 3; i++)
    {
        s.insert(board[0][i]);
        s.insert(board[1][i]);
        s.insert(board[2][i]);
        if(s.size() == 2)
        {
            auto it = s.begin();
            char c1 = *it;
            char c2 = *(++it);
            if(c1 > c2) swap(c1, c2);
            duoWinnerPairs.insert({c1, c2});
        }
        s.clear();
    }
    
    // Check duo wins for diagonals
    s.insert(board[0][0]);
    s.insert(board[1][1]);
    s.insert(board[2][2]);
    if(s.size() == 2)
    {
        auto it = s.begin();
        char c1 = *it;
        char c2 = *(++it);
        if(c1 > c2) swap(c1, c2);
        duoWinnerPairs.insert({c1, c2});
    }
    s.clear();
    
    s.insert(board[0][2]);
    s.insert(board[1][1]);
    s.insert(board[2][0]);
    if(s.size() == 2)
    {
        auto it = s.begin();
        char c1 = *it;
        char c2 = *(++it);
        if(c1 > c2) swap(c1, c2);
        duoWinnerPairs.insert({c1, c2});
    }
    
    duowin = duoWinnerPairs.size();
    
    fout << singwin << endl;
    fout << duowin << endl;
    
    fin.close();
    fout.close();
    return 0;
}