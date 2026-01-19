#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

using namespace std;

int main()
{
    string n;
    int input[2][26];
    ifstream fin("circlecross.in");
    ofstream fout("circlecross.out");
    int counter = 0;
    fin >> n;

    // Initialize array to -1
    for(int i = 0; i < 26; i++) {
        input[0][i] = -1;
        input[1][i] = -1;
    }

    // Read positions
    for(int i = 0; i < 52; i++)
    {
        char temp = n[i];
        int cowIndex = temp - 'A';
        
        if(input[0][cowIndex] == -1)
        {
            input[0][cowIndex] = i;
        }
        else
        {
            input[1][cowIndex] = i;
        }   
    }

    // Count crossing pairs
    for(int i = 0; i < 26; i++)
    {
        for(int j = i + 1; j < 26; j++)
        {
            int a1 = input[0][i], a2 = input[1][i];
            int b1 = input[0][j], b2 = input[1][j];
            
            // Ensure a1 < a2 and b1 < b2
            if(a1 > a2) swap(a1, a2);
            if(b1 > b2) swap(b1, b2);
            
            // Check if exactly one of b's positions is between a1 and a2
            bool b1_inside = (a1 < b1 && b1 < a2);
            bool b2_inside = (a1 < b2 && b2 < a2);
            
            if(b1_inside != b2_inside) {
                counter++;
            }
        }
    }

    fout << counter;
    fin.close();
    fout.close();
    return 0;
}