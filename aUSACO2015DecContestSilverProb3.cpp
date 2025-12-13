#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

int main() {
    ifstream fin("bcount.in");
    ofstream fout("bcount.out");

    int n, q;
    fin >> n >> q;

    // Create 1-indexed prefix sum arrays for 3 breeds
    // ps[1][i] = number of breed 1 cows in positions 1..i
    vector<vector<int>> ps(4, vector<int>(n + 1, 0));

    for (int i = 1; i <= n; i++) {
        int breed;
        fin >> breed;
        
        // Carry over counts from previous position
        for (int b = 1; b <= 3; b++) {
            ps[b][i] = ps[b][i - 1];
        }
        // Increment the count for the current cow's breed
        ps[breed][i] = ps[breed][i - 1] + 1;
    }

    for (int i = 0; i < q; i++) {
        int a, b;
        fin >> a >> b;
        // Correct query: ps[breed][b] - ps[breed][a-1]
        fout << ps[1][b] - ps[1][a - 1] << " "
             << ps[2][b] - ps[2][a - 1] << " "
             << ps[3][b] - ps[3][a - 1] << "\n";
    }

    return 0;
}