#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;




void takemovement(char direction, int distance, int& x, int& y, int& currentTime, int timeofentry[][2001], int& mindifference)
{
    for(int i = 0; i < distance; i++)
    {
        // 1. Move first
        if(direction == 'N') y++;
        else if(direction == 'S') y--;
        else if(direction == 'E') x++;
        else if(direction == 'W') x--;
        
        // 2. Increment time for this step
        currentTime++;
        
        // 3. Check if we've been here before
        if(timeofentry[x][y] != 0) 
        {
            // This position was visited before
            int timeDiff = currentTime - timeofentry[x][y];
            // 4. Update mindifference if this is the first difference or smaller
            if(mindifference == 0 || timeDiff < mindifference) 
            {
                mindifference = timeDiff;
            }
        }
        
        // 5. Record current time for this position
        timeofentry[x][y] = currentTime;
    }
}

int main()
{
    int timeofentry[2001][2001] = {0};
    int mindifference = 0;  // Start at 0, meaning no crossing found
    ifstream fin("mowing.in");
    ofstream fout("mowing.out");
    int n;
    fin >> n;
    int currentTime = 0;  // Better name
    int curx = 1000;
    int cury = 1000;
    
    // Record the starting position at time 0
    timeofentry[curx][cury] = 0;
    
    for(int i = 0; i < n; i++)
    {
        char direction;
        int distance;
        fin >> direction >> distance;
        
        takemovement(direction, distance, curx, cury, currentTime, timeofentry, mindifference);
        // Remove the stepsbefore++ since currentTime is updated in the function
    }
    
    // If no crossing was found, output -1
    if(mindifference == 0) {
        fout << -1 << endl;
    } else {
        fout << mindifference << endl;
    }
    
    fin.close();
    fout.close();
    return 0;
}