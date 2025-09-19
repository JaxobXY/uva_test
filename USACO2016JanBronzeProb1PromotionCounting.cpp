#include <iostream>
#include <fstream>
using namespace std;

int main() {
    ifstream inFile("promote.in");
    ofstream outFile("promote.out");
    
    int b1, b2, s1, s2, g1, g2, p1, p2;
    inFile >> b1 >> b2 >> s1 >> s2 >> g1 >> g2 >> p1 >> p2;
    
    // Calculate promotions based on official USACO solution logic
    
    // Gold to Platinum: simply the increase in platinum count
    int goldToPlatinum = p2 - p1;
    
    // Silver to Gold: increase in (gold + platinum) count
    int silverToGold = (g2 + p2) - (g1 + p1);
    
    // Bronze to Silver: increase in (silver + gold + platinum) count  
    int bronzeToSilver = (s2 + g2 + p2) - (s1 + g1 + p1);
    
    outFile << bronzeToSilver << endl;
    outFile << silverToGold << endl;
    outFile << goldToPlatinum << endl;
    
    inFile.close();
    outFile.close();
    
    return 0;
}