#include <iostream>
#include <string>
#include <climits>

using namespace std;

bool checkfit(const string &a, const string &b, int offset) {
    for (int i = 0; i < b.size(); i++) {
        if (offset + i >= 0 && offset + i < a.size()) {
            if (a[offset + i] == '2' && b[i] == '2') {
                return false;
            }
        }
    }
    return true;
}

int main() {
    string a, b;
    cin >> a >> b;
    int alen = a.size();
    int blen = b.size();
    int min_len = INT_MAX;

    for (int offset = -blen + 1; offset < alen; offset++) {
        if (checkfit(a, b, offset)) {
            int start = min(0, offset);
            int end = max(alen, offset + blen);
            int current_len = end - start;
            if (current_len < min_len) {
                min_len = current_len;
            }
        }
    }


    for (int offset = -alen + 1; offset < blen; offset++) {
        if (checkfit(b, a, offset)) {
            int start = min(0, offset);
            int end = max(blen, offset + alen);
            int current_len = end - start;
            if (current_len < min_len) {
                min_len = current_len;
            }
        }
    }

    cout << min_len << endl;
    return 0;
}