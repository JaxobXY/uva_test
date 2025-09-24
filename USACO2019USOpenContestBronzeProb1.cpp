#include <iostream>
#include <fstream>
#include <string>
#include <cmath>

using namespace std;

int main()
{
    ifstream inFile("buckets.in");
    ofstream outFile("buckets.out");
    const int lengthandwidth = 10;
    char tem;
    int bx, by, lx, ly, rx, ry;  // barn, lake, rock coordinates
    
    for(int i = 0; i < lengthandwidth; i++)
    {
        for(int j = 0; j < lengthandwidth; j++)
        {
            inFile >> tem;
            if (tem == 'B') {  // Fixed: == instead of =
                bx = i;
                by = j;
            }
            else if (tem == 'L') {  // Fixed: == instead of =
                lx = i;
                ly = j;
            }
            else if (tem == 'R') {  // Added rock case
                rx = i;
                ry = j;
            }
        }
    }
    
    int distance = abs(bx - lx) + abs(by - ly) - 1;
    
    if ((bx == lx && bx == rx && ((by < ry && ry < ly) || (ly < ry && ry < by))) ||
        (by == ly && by == ry && ((bx < rx && rx < lx) || (lx < rx && rx < bx)))) {
        distance += 2;  
    }
    
    outFile << distance << endl;
   
    inFile.close();
    outFile.close();
    return 0;
}