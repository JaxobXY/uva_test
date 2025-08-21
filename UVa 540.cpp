#include <iostream>
#include <vector>
using namespace std;

int main() {
    int teamn;
    cin >> teamn;
    
    // Create a vector for the main queue (will store the list of Ids in the line)
    vector<int> mainQueue;
    
    // Create a 2D vector for teams: each team has its own queue of member IDs
    vector<vector<int>> teams(teamn); // Initialize with 'teamn' empty teams
    
    for (int i = 0; i < teamn; i++) {
        int teamSize;
        cin >> teamSize; // Read how many members are in this team
        
        for (int j = 0; j < teamSize; j++) {
            int memberId;
            cin >> memberId;
            teams[i].push_back(memberId); // Add member to current team i
        }
    }
    
    string act;
    int act2

    while(cin>>act)
    {
        if (act=="0")
        {
            return 0;
        }
        else
        {
            cin>>act2;
        }

        if(act=="ENQUEUE")
        {
            
        }
        else if(act=="DEQUEUE")
        {

        }
        else if(stop)
        {

        }
        

    }
    
    return 0;
}