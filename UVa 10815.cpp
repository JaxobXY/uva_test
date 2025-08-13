#include <iostream>
#include <set>
#include <string>
using namespace std;

int main() {
    string temp;
    set<string> dictionary;
	
    ios_base::sync_with_stdio(0);
	cin.tie(0);

    while (cin >> temp) {
        // if(temp=="0"){
        //     break;
        // }
        string cleaned;
        for (int i=0;i<temp.length();i++) {
            char c = temp[i];

            // Check if letter (A-Z or a-z)
            if ((c >= 'A' && c <= 'Z')) {
                cleaned += c + ('a' - 'A'); // convert uppercase to lowercase
            }
            else if (c >= 'a' && c <= 'z') {
                cleaned += c; // already lowercase
            } else {
                if(cleaned!=""){
                    dictionary.insert(cleaned);
                    cleaned.clear();
                    // cleaned = "";
                }
                // ABC'
            } 
            // if it's not a letter, skip it
        }
        if (cleaned!="")
            dictionary.insert(cleaned);
    }

    for (const string &word : dictionary) {
        cout << word << endl;
    }
    // for(set<string>::iterator it = dictionary.begin(); it!=dictionary.end(); it++)
    // {
    //     cout << *it << "\n";
    // }

    return 0;
}