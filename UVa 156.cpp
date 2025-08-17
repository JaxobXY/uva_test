#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <algorithm>  // Missing include for std::sort
using namespace std;

int main()
{
    map<string, int> anagramGroups;
    vector<string> words;
    string input;
    
    // Read input words until "#" is encountered
    while(cin >> input && input != "#")
    {
        words.push_back(input);
    }
    
    // Process each word
    for(const string& word : words)
    {
        string sortedWord = word;
        sort(sortedWord.begin(), sortedWord.end());
        anagramGroups[sortedWord]++;
    }
    
    // Output results
    for(const auto& pair : anagramGroups) 
    {
        cout << pair.first << ": " << pair.second << endl;
    }
    
    return 0;
}