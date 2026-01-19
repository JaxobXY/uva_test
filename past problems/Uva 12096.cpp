#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <map>
#include <set>
#include <algorithm>

using namespace std;

typedef set<int> Set;  // Use capital S to avoid conflict
map<Set, int> IDcache;
vector<Set> Setcache;

int getID(Set s) {
    if (IDcache.count(s))
        return IDcache[s];
    
    Setcache.push_back(s);
    return IDcache[s] = Setcache.size() - 1;
}

int main() {
    int n1;
    cin >> n1;
    
    for (int i = 0; i < n1; i++) {
        // Local caches for this test case
        map<Set, int> IDcache;
        vector<Set> Setcache;
        
        // Helper function with local caches
        auto getID = [&](Set s) -> int {
            if (IDcache.count(s))
                return IDcache[s];
            Setcache.push_back(s);
            return IDcache[s] = Setcache.size() - 1;
        };
        
        // Initialize empty set
        getID(Set());
        
        int commandn;
        cin >> commandn;
        stack<int> stk;
        
        for (int j = 0; j < commandn; j++) {
            string curcom;
            cin >> curcom; 
            
            if (curcom == "PUSH") {
                stk.push(getID(Set()));
                cout << Setcache[stk.top()].size() << endl;
            }
            else if (curcom == "DUP") {
                stk.push(stk.top());
                cout << Setcache[stk.top()].size() << endl;
            }
            else if (curcom == "UNION") {
                Set set1 = Setcache[stk.top()]; stk.pop();
                Set set2 = Setcache[stk.top()]; stk.pop();
                Set result;
                set_union(set1.begin(), set1.end(), 
                         set2.begin(), set2.end(),
                         inserter(result, result.begin()));
                stk.push(getID(result));
                cout << result.size() << endl;
            }
            else if (curcom == "INTERSECT") {
                Set set1 = Setcache[stk.top()]; stk.pop();
                Set set2 = Setcache[stk.top()]; stk.pop();
                Set result;
                set_intersection(set1.begin(), set1.end(),
                                set2.begin(), set2.end(),
                                inserter(result, result.begin()));
                stk.push(getID(result));
                cout << result.size() << endl;
            }
            else if (curcom == "ADD") {
                int id1 = stk.top(); stk.pop();
                int id2 = stk.top(); stk.pop();
                Set set2 = Setcache[id2];
                Set newSet = set2;
                newSet.insert(id1);
                stk.push(getID(newSet));
                cout << newSet.size() << endl;
            }
        }
        cout << "***" << endl;
    }
    return 0;
}