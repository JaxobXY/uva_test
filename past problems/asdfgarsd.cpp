//goes with
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//USACO2024USOpenContestBronzeProb3.cpp


#include <iostream>
#include <vector>
#include <numeric>   // for std::iota
#include <algorithm> // for std::shuffle
#include <random>    // for std::mt19937 and std::random_device
#include <list>

using namespace std;
int main() {
    int n;
    cout << "how many times(this is 1 in the middle probably)" << endl;
    cin >> n;
    for(int j=0;j<n;j++)
    {
        // 1. Create a list (vector) with 10 elements
        list<int> listt;
        vector<int> list(10);
        
        // 2. Fill it with numbers 1 to 10
        iota(list.begin(), list.end(), 1);

        // 3. Set up a random number generator
        random_device rd; 
        mt19937 g(rd());

        // 4. Shuffle the list
        shuffle(list.begin(), list.end(), g);

        for(int i=0;i<10;i++)
        {
            listt.push_back(list[i]);
        }
        while(listt.size()>1)
        {
            if(listt.front()>listt.back())
            {
                listt.pop_front();
                cout << listt.front() << " ";
            }
            else
            {
                listt.pop_back();
                cout << listt.back() << " ";
            }
        }
        cout << endl;
    }



























    cout << "how many times(this is 1 in the edge)" << endl;
    cin >> n;
    for(int j=0;j<n;j++)
    {
        // 1. Create a list (vector) with 10 elements
        list<int> listt;
        vector<int> list(10);
        
        // 2. Fill it with numbers 1 to 10
        iota(list.begin(), list.end(), 1);

        // 3. Set up a random number generator
        random_device rd; 
        mt19937 g(rd());

        // 4. Shuffle the list
        shuffle(list.begin()+1, list.end(), g);

        for(int i=0;i<10;i++)
        {
            listt.push_back(list[i]);
        }
        while(listt.size()>1)
        {
            if(listt.front()>listt.back())
            {
                listt.pop_front();
                cout << listt.front() << " ";
            }
            else
            {
                listt.pop_back();
                cout << listt.back() << " ";
            }
        }
        cout << endl;
    }
    return 0;
}