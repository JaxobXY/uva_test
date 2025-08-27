#include <iostream>
#include <queue>
#include <unordered_set>
#include <vector>
#include <functional> // For greater<int>
using namespace std;

typedef long long ll; // Crucial! Numbers get very large.

int main() {
    const int target = 1500; // We want the 1500th number

    // 1. Declare our data structures
    priority_queue<ll, vector<ll>, greater<ll>> minHeap; // Min-heap to get smallest number
    unordered_set<ll> seen;                             // Set to check for duplicates

    // 2. Initialize with the first ugly number
    minHeap.push(1);
    seen.insert(1);

    ll currentUgly;
    int count = 0;

    // 3. Generate ugly numbers until we reach the target
    while (count < target && !minHeap.empty())
    {
        currentUgly = minHeap.top();
        minHeap.pop();
        count++;
        // 4. Generate new ugly numbers by multiplying with 2, 3, and 5
        long long can1;
        long long can2;
        long long can3;
        can1 = currentUgly * 2;
        can2 = currentUgly * 3;
        can3 = currentUgly * 5;
        // 5. Add new numbers to the heap if they haven't been seen
        if (seen.find(can1) == seen.end()) 
        {
            minHeap.push(can1);
            seen.insert(can1); // Mark as seen
        }
        if (seen.find(can2) == seen.end()) 
        {
            minHeap.push(can2);
            seen.insert(can2); // Mark as seen
        }
        if (seen.find(can3) == seen.end())
        {
            minHeap.push(can3);
            seen.insert(can3); // Mark as seen
        }

    }
      // 6. Output the 1500th ugly number
    cout << "The " << target << "'th ugly number is " << currentUgly << "." << endl;
}         