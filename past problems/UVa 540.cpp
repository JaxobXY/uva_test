#include <iostream>
#include <vector>
#include <algorithm>  // Added for find()
using namespace std;

int main() {
    int teamn;
    int sennum = 1;
    
    while (cin >> teamn && teamn != 0) {
        vector<int> mainQueue;
        vector<vector<int>> teams(teamn);
        
        // Create a mapping from member ID to team index
        vector<int> memberToTeam(1000000, -1);
        
        for (int i = 0; i < teamn; i++) {
            int teamSize;
            cin >> teamSize;
            
            for (int j = 0; j < teamSize; j++) {
                int memberId;
                cin >> memberId;
                memberToTeam[memberId] = i;
            }
        }
        
        string act;
        int act2;  // Moved declaration here
        cout << "Scenario #" << sennum << endl;
        sennum++;
        
        while (cin >> act && act != "STOP") {
            if (act == "ENQUEUE") {
                cin >> act2;
                int teamIndex = memberToTeam[act2];
                
                if (find(mainQueue.begin(), mainQueue.end(), teamIndex) == mainQueue.end()) {
                    mainQueue.push_back(teamIndex);
                }
                teams[teamIndex].push_back(act2);
                
            } else if (act == "DEQUEUE") {
                if (!mainQueue.empty()) {
                    int teamIndex = mainQueue.front();
                    if (!teams[teamIndex].empty()) {
                        cout << teams[teamIndex].front() << endl;
                        teams[teamIndex].erase(teams[teamIndex].begin());
                        
                        if (teams[teamIndex].empty()) {
                            mainQueue.erase(mainQueue.begin());
                        }
                    }
                }
            }
        }
        cout << endl;
    }
    
    return 0;
}