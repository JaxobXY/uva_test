#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int main()
{
    ifstream fin("shell.in");
    ofstream fout("shell.out");
    int n;
    fin >> n;
    
    // Use vectors instead of arrays for dynamic sizing
    vector<int> a_moves(n), b_moves(n), c_moves(n);
    
    // Read all the moves into the arrays
    for(int j = 0; j < n; j++) {
        fin >> a_moves[j] >> b_moves[j] >> c_moves[j];
    }
    
    int maxscore = 0;
    
    for(int start = 1; start <= 3; start++) {
        int score = 0;
        int curr = start;
        
        for(int j = 0; j < n; j++) {
            int a = a_moves[j];
            int b = b_moves[j];  
            int c = c_moves[j];
            
            if(a == curr) {
                curr = b;
            } else if(b == curr) {
                curr = a;
            }
            
            if(c == curr) {
                score++;
            }
        }
        
        if(score > maxscore) {
            maxscore = score;
        }
    }
    
    fout << maxscore << endl;  // Write the result
    fin.close();
    fout.close();
    return 0;
}