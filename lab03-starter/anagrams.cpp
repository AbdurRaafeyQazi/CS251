#include "anagrams.h"

#include <map>
#include <set>
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

set<string> findAnagrams(const string& word, const vector<string>& dictionary) {
    // Helper function to get the canonical form of a word

    // So this is taking in a constant reference from the string word parameter
    auto getCanonicalForm = [](const string& w /* constant string value from parameter*/) { // create a temporary
        // now takes the value of string word from the parameter and stores it in sorted_word
        string sorted_word = w; //create a new var and store the value of w 
        
        sort(sorted_word.begin(), sorted_word.end()); // apparently sorts the string by ascii value
        return sorted_word; // return the sorted word
    };
    
    // Get the canonical form of the input word
    // Create a string and then use the fucntion to sort the word
    string canonical_word = getCanonicalForm(word);

    set<string> result; //set to store values 

    // Iterate over the dictionary and find anagrams
    for (const auto& dict_word : dictionary) {
        if (getCanonicalForm(dict_word) == canonical_word) {
            result.insert(dict_word);
        }
    }

    return result;
}

int main() {
    // Example usage
    vector<string> dictionary = {"meat", "mate", "tame", "team", "listen", "silent", "tinsel", "magikarp"};
    string word = "meat";
    
    set<string> anagrams = findAnagrams(word, dictionary);
    
    cout << "Anagrams of " << word << " in the dictionary are:\n";
    for (const auto& anagram : anagrams) {
        cout << anagram << '\n';
    }

    return 0;
}
