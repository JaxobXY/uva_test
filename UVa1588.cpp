#include <iostream>
#include <string>
#include <climits>

using namespace std;

bool checkfit(const string &a, const string &b, int offset) {
    for (int i = 0; i < b.size(); i++) {
        int a_pos = offset + i;
        if (a_pos >= 0 && a_pos < a.size()) {
            if (a[a_pos] == '2' && b[i] == '2') {
                return false;
            }
        }
    }
    return true;
}

int main() {
    string a, b;
    while (cin >> a >> b) {
        int alen = a.size();
        int blen = b.size();
        int min_len = INT_MAX;

        // Check all possible offsets (including negative)
        for (int offset = -blen + 1; offset < alen; offset++) {
            if (checkfit(a, b, offset)) {
                // Calculate the total length for this overlap
                int start = min(0, offset);
                int end = max(alen, offset + blen);
                int length = end - start;
                
                if (length < min_len) {
                    min_len = length;
                }
            }
        }

        cout << min_len << endl;
    }
    return 0;
}
