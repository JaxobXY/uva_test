#include <iostream>
#include <iomanip>
#include <algorithm>
#include <vector>
using namespace std;

#include <string>

struct Player {
    // Data from input
    std::string name;
    char status; // 'A' or 'P'
    int scores[4]; // scores for rounds 1, 2, 3, 4

    // Calculated data
    int semiscore; // sum of scores for rounds 1 and 2
    int totalScore;
    bool madeCut;
    int position;   // Use -1 to represent "no position"
    double prizeMoney;
};

int main() {
    double totalPrizeMoney;
    double percentages[70];
    int n;

    // Read tournament data
    cin >> totalPrizeMoney;
    for (int i = 0; i < 70; i++) {
        cin >> percentages[i];
    }
    cin >> n;
    cin.ignore(); // Clear the newline character after reading n

    vector<Player> players(n);

    // Read each player's data
    for (int i = 0; i < n; i++) {
        Player p;
        cin >> p.name >> p.status;
        for (int j = 0; j < 4; j++) {
            cin >> p.scores[j];
        }
        players[i] = p;
    }
    // Read each player's data
    for (int i = 0; i < n; i++) {
        if(players[i].scores[0] == -1 or players[i].scores[1] == -1) {
            players[i].madeCut = false;
            players[i].semiscore = 0;
            players[i].totalScore = 0;
        }
        players[i].semiscore = players[i].scores[0] + players[i].scores[1];
        players[i].totalScore = players[i].semiscore + players[i].scores[2] + players[i].scores[3];
    }
    // Determine who made the cut
    sort(players.begin(), players.end(), [](const Player &a, const Player &b) {
        if (a.semiscore != b.semiscore) {
            return a.semiscore < b.semiscore; // Ascending order of semiscore
        }
        return a.name < b.name; // Ascending order of name for ties
    });
    

}


