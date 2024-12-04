#include "include/search.h"

// #include <cctype>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <string>
#include <vector>
// #include <cstring>

using namespace std;

string cleanToken(const string& token) { 

  string tempToken = token;

  for (int i = 0; i < tempToken.length();) {
    if (ispunct(tempToken[i])) {
      tempToken.erase(tempToken.begin() + i);
    } else {
      break;
    }
  }

  for (int i = tempToken.length() - 1; i >= 0; --i) {
    if (ispunct(tempToken[i])) {
      tempToken.erase(tempToken.begin() + i);

    } else {
      break;
    }
  }

  bool hasletter = false;

  for (char c : tempToken) {
    if (isalpha(c)) {
      hasletter = true;
      break;
    }
  }

  if (!hasletter) {
    return "";
  }

  for (char& e : tempToken) {
    e = tolower(e);
  }

  return tempToken;
}


/**
 * Splits the input text into words ("tokens"), cleans each token, and returns
 * the set of all tokens in the text.
 */
set<string> gatherTokens(const string& text) {
  /*
  So we are going to get constant string values
  We take those values and clean them use cleanToken
  After cleaning them we store them in the set.
  
  */

  set<string> collectedTokens;

  string tempToken;

  size_t i = 0; // Since size of the string can only be positive
  // Since i is an int and string is char for each element.
  // Convert tempText to int by using its length.

  while(i < text.length()){
    
    while(i < text.length() && text[i] != ' '){
      tempToken += text[i];
      ++i; // since you already accessed the value of i this is why u must increment first and not access same value again

    }

    string cleanedToken = cleanToken(tempToken);
    if(!cleanedToken.empty()){
      collectedTokens.insert(cleanedToken);
    }

    tempToken.clear();

    while(i < text.length() && text[i] == ' '){
      ++i;
    }
  }

return collectedTokens;

}


int buildIndex(const string& filename, map<string, set<string>>& index) {

  ifstream iFS(filename);

  string line;

  if(!iFS.is_open()){
    return 0;
  }

  int count = 0;
  string url;
  string body;
  // url and body get rewritten so you dont need to clean them.
  while(getline(iFS , url) && getline(iFS , body)){ // Take the line from the open file and store it in the respective string

    set<string> keys = gatherTokens(body);

    for(const string& key : keys){ // map it to the url
      index[key].insert(url); // Take each key and store the same url in it.
    }

    count++;

  }

  return count;

}

set<string> findQueryMatches(const map<string, set<string>>& index, const string& sentence) {

  istringstream iSS(sentence);

  string token;
  set<string> result;
  bool isFirstTerm = true;

  while(iSS >> token){
    char mod = 0; // check if there is a character present at that location, for now set it to false

    if(token[0] == '+' || token[0] == '-' ){
        mod = token[0];
        token = token.substr(1); // starts at 1 and keeps on going untill the end. ie remove the mod form the actual term.
    }

    string cleanedToken = cleanToken(token);
    if(cleanedToken.empty()){
      continue;
    }

    auto it = index.find(cleanedToken);
    set<string> matches = (it != index.end()) ? index.at(cleanedToken) : set<string>();

    if (isFirstTerm) {
            result = matches;
            isFirstTerm = false;
        } else {
            set<string> temp;
            if (mod == '+') {
                set_intersection(result.begin(), result.end(), matches.begin(), matches.end(), inserter(temp, temp.begin()));
                result = temp;
            } else if (mod == '-') {
                set_difference(result.begin(), result.end(), matches.begin(), matches.end(), inserter(temp, temp.begin()));
                result = temp;
            } else {
                set<string> union_temp; // start with an empty set
                set_union(result.begin(), result.end(), matches.begin(), matches.end(), inserter(union_temp, union_temp.begin()));
                result = union_temp;
            }
        }
    }

    return result;

 
}

void searchEngine(const string& filename) {


  map<string, set<string>> index; // Inverted index
    int pageCount = buildIndex(filename, index); // Build the index

    // If the buildIndex returned 0 print an error and exit
    if (pageCount == 0) {
        cout << "Invalid filename." << endl;
        
    }

    int uniqueTerms = index.size(); // Count distinct words (keys in index)

    // Print number of web pages and unique terms indexed
    cout << "Stand by while building index...\n";
    cout << "Indexed " << pageCount << " pages containing " << uniqueTerms << " unique terms\n\n";

    string query; // To store query

    // Command loop to handle queries
    while (true) {
        cout << "Enter query sentence (press enter to quit): ";
        getline(cin, query); // Read entire line including spaces

        // Exit loop if the query is empty
        if (query.empty()) {
            break;
        }

        // Find matching pages for the query
        set<string> matches = findQueryMatches(index, query);

        // Print the results
        cout << "Found " << matches.size() << " matching pages\n";
        for (const string& url : matches) {
            cout << url << endl; // Print each matching URL
        }
        cout << endl; 
    }

    cout << "Thank you for searching!\n"; 

  
}
