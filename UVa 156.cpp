#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <algorithm>
#include <cctype>  
#include <set>
using namespace std;

int main()
{
    bool found = false;
    vector<string> words;
    vector<string> sortedWords;
    set <string> output;
    string input;
    
    // Read input words until "#" is encountered
    while(cin >> input)
    {
        if(input == "#") break;
        words.push_back(input);
    }
    
    // Process each word
    for(const string& word : words)
    {
        string sortedWord = word;
        // Convert to lowercase
        for(char& c : sortedWord) {
            c = tolower(c);
        }
        sort(sortedWord.begin(), sortedWord.end());
        sortedWords.push_back(sortedWord);
    }
    
    // Find unique anagrams
    for(int i = 0; i < sortedWords.size(); i++)
    {
        found = false;  // Reset for each word
        for(int j = 0; j < sortedWords.size(); j++)
        {
            if(j != i)
            {
                if(sortedWords[i] == sortedWords[j]&& words[i] != words[j])
                {
                    found = true;
                    break;  // No need to continue once found
                }
            }
        }
        if(!found){
            output.insert(words[i]);
        }
    }
    for(int i=0;i<output.size();i++)
    {
        cout << *next(output.begin(), i) << endl;  // Print each unique anagram
    }
    return 0;
}