#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;

int main() {
    ifstream inFile("teleport.in");
    ofstream outFile("teleport.out");
    
    int a, b, x, y;
    inFile >> a >> b >> x >> y;
    
    // Three possible strategies:
    // 1. Direct route: |a - b|
    int direct = abs(a - b);
    
    // 2. Use teleporter from x to y: |a - x| + |y - b|
    int route_xy = abs(a - x) + abs(y - b);
    
    // 3. Use teleporter from y to x: |a - y| + |x - b|
    int route_yx = abs(a - y) + abs(x - b);
    
    // Find the minimum of all three routes
    int min_distance = min({direct, route_xy, route_yx});
    
    outFile << min_distance << endl;
    
    inFile.close();
    outFile.close();
    
    return 0;
}