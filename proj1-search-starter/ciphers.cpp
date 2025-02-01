#include <cctype>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "include/caesar_dec.h"
#include "include/caesar_enc.h"
#include "include/subst_dec.h"
#include "include/subst_enc.h"
#include "utils.h"

using namespace std;

// Initialize random number generator in .cpp file for ODR reasons
std::mt19937 Random::rng;

/**
 * Print instructions for using the program.
 */
void printMenu() {
  cout << "Ciphers Menu" << endl;
  cout << "------------" << endl;
  cout << "C - Encrypt with Caesar Cipher" << endl;
  cout << "D - Decrypt Caesar Cipher" << endl;
  cout << "E - Compute English-ness Score" << endl;
  cout << "A - Apply Random Substitution Cipher" << endl;
  cout << "S - Decrypt Substitution Cipher from Console" << endl;
  cout << "F - Decrypt Substitution Cipher from File" << endl;
  cout << "R - Set Random Seed for Testing" << endl;
  cout << "X - Exit Program" << endl;
}

int main() {
  void decTextFile(const QuadgramScorer& scorer);

  vector<string> dictionary;

  // Load the dictionary from the file

  ifstream dictFile("dictionary.txt");
  string word;
  while (dictFile >> word) {
    dictionary.push_back(clean(word));  // Clean the dictionary words
  }

  // Load quadgrams and counts for QuadgramScorer
  vector<string> quadgrams;
  vector<int> counts;
  ifstream quadgramFile("english_quadgrams.txt");
  string line;

  while (getline(quadgramFile, line)) {
    size_t commaPos = line.find(',');

    if (commaPos != string::npos) {
      string quadgram = line.substr(0, commaPos);
      int count = stoi(line.substr(commaPos + 1));

      quadgrams.push_back(quadgram);
      counts.push_back(count);
    }
  }
  QuadgramScorer scorer(quadgrams, counts);

  Random::seed(time(NULL));
  string command;

  cout << "Welcome to Ciphers!" << endl;
  cout << "-------------------" << endl;
  cout << endl;

  do {
    printMenu();
    cout << endl << "Enter a command (case does not matter): ";

    // Use getline for all user input to avoid needing to handle
    // input buffer issues relating to using both >> and getline
    getline(cin, command);
    cout << endl;

    if (command == "R" || command == "r") {
      string seed_str;

      cout << "Enter a non-negative integer to seed the random number "
              "generator: ";
      getline(cin, seed_str);
      Random::seed(stoi(seed_str));

    } else if (command == "C" || command == "c") {
      runCaesarEncrypt();

    } else if (command == "D" || command == "d") {
      runCaesarDecrypt(dictionary);

    } else if (command == "A" || command == "a") {
      applyRandSubstCipherCommand();

    } else if (command == "E" || command == "e") {
      computeEnglishnessCommand(scorer);

    } else if (command == "S" || command == "s") {
      decryptSubstCipherCommand(scorer);

    } else if (command == "F" || command == "f") {
      decTextFile(scorer);
    }

    cout << endl;

  } while (!(command == "x" || command == "X") && !cin.eof());

  return 0;
}

// "#pragma region" and "#pragma endregion" group related functions in this file
// to tell VSCode that these are "foldable". You might have noticed the little
// down arrow next to functions or loops, and that you can click it to collapse
// those bodies. This lets us do the same thing for arbitrary chunks!
#pragma region CaesarEnc

char rot(char c, int amount) {
  // Find the index of the character in the alphabet string
  size_t index = ALPHABET.find(c);

  // Calculate the new index with rotation and wrap around using mod 26
  size_t newIndex = (index + amount) % 26;

  // Return the character at the new index
  return ALPHABET[newIndex];
}

string rot(const string& line, int amount) {  // So these are overloading ?

  string result;

  for (char ch : line) {
    if (isalpha(ch)) {
      char upperCh = toupper(ch);

      size_t index = ALPHABET.find(upperCh);

      size_t newIndex = (index + amount) % 26;

      char newCh = ALPHABET[newIndex];

      result += newCh;

    } else if (isspace(ch)) {  // if this is a space then add it to the result
                               // or else don't

      result += ch;
    }
  }

  return result;
}

void runCaesarEncrypt() {
  string txtToEncrypt;
  string numToShift;

  cout << "Enter the text to Caesar encrypt: ";
  getline(cin, txtToEncrypt);

  cout << "Enter the number of characters to rotate by: ";
  getline(cin, numToShift);

  // Convert the shift amount from string to integer
  int shiftedNum = stoi(numToShift);

  string encryptedText = rot(txtToEncrypt, shiftedNum);

  cout << "Encrypted text: " << encryptedText << endl;
}

#pragma endregion CaesarEnc

#pragma region CaesarDec

void rot(vector<string>& strings, int amount) {
  // this string contains multiple strings and you want this function to apply
  // to each string. one way to do this is to this is to use a enhanced for loop
  // to interate over each element in the vecotr

  for (string& e : strings) {
    // for each element; in the vec; modify the value of the element and store
    // it back in the element.

    e = rot(e, amount);  // put the element into the function for modification
                         // and then store it back into the element.
  }
}

string clean(const string& s) {
  string result;  // because each character form a string

  for (char e : s) {
    if (isalpha(e)) {
      result += toupper(e);
    }
  }

  return result;
}

vector<string> splitBySpaces(const string& s) {
  // if you iterate 1 element at a time in a vector it will count each one as a
  // seperate element so you need to store all of this in a string and then
  // pushback this into the vector

  int i = 0;
  vector<string> spaces;
  string strPasser;

  while (i < s.size()) {
    if (s[i] != ' ') {
      strPasser += s[i];

    } else {
      if (!strPasser.empty()) {
        spaces.push_back(strPasser);
        strPasser.clear();
      }
    }

    ++i;
  }

  if (!strPasser.empty()) {
    spaces.push_back(strPasser);
  }

  return spaces;
}

string joinWithSpaces(const vector<string>& words) {
  string result;

  for (size_t i = 0; i < words.size(); ++i) {
    result += words[i];  // vector stores values not characters so at the i
                         // position will be a full value

    if (i != words.size() - 1) {
      result += " ";
    }
  }

  return result;
}

int numWordsIn(const vector<string>& words, const vector<string>& dict) {
  int counter = 0;

  for (const string& w : words) {
    for (const string& d : dict) {
      if (w == d) {
        counter++;
        break;
      }
    }
  }

  return counter;
}

void runCaesarDecrypt(const vector<string>& dict) {
  string decTxt;
  cout << "Enter the text to Caesar decrypt: " << endl;
  getline(cin, decTxt);

  vector<string> words = splitBySpaces(decTxt);

  string rotatedWord;

  // Removes any non-alphabetic characters by rotating and cleaning.
  for (int i = 0; i < words.size(); i++) {
    rotatedWord = clean(words.at(i));

    words.at(i) = rotatedWord;
  }

  vector<string> decWords;

  string decStr;

  string joiWord;

  int count = 0;

  int wordCount;

  for (int i = 0; i < 26; i++) {
    for (int j = 0; j < words.size(); j++) {
      decStr = rot(words.at(j), i);

      decWords.push_back(decStr);

      decStr = "";
    }

    wordCount = numWordsIn(decWords, dict);

    if (wordCount > (words.size() / 2)) {
      count += 1;

      if (words.size() == 1) {
        for (int k = 0; k < decWords.size(); k++) {
          cout << decWords.at(k) << endl;
        }
      } else {
        joiWord = joinWithSpaces(decWords);
        cout << joiWord << endl;
      }
    }

    decWords.clear();
  }

  if (count < wordCount && wordCount <= (words.size() / 2)) {
    cout << "No good decryptions found" << endl;
  }
  if (count == 0) {
    cout << "No good decryptions found" << endl;
  }
}

#pragma endregion CaesarDec

#pragma region SubstEnc

string applySubstCipher(const vector<char>& cipher, const string& s) {
  string result;

  for (char ch : s) {
    if (isalpha(ch)) {
      // Convert to uppercase if not already
      char upperCh = toupper(ch);
      // Find the index of the character in the alphabet
      size_t index = ALPHABET.find(upperCh);
      // Map to the cipher character
      char cipherChar = cipher[index];
      result += cipherChar;
    } else {
      // Preserve non-alphabetic characters
      result += ch;
    }
  }

  return result;
}

void applyRandSubstCipherCommand() {
  // Prompt user for input text
  string txtToEncrypt;
  cout << "Enter the text to substitution-cipher encrypt: ";
  getline(cin, txtToEncrypt);
  // Generate a random substitution cipher
  vector<char> cipher = genRandomSubstCipher();
  // Encrypt the text using the substitution cipher
  string encryptedText = applySubstCipher(cipher, txtToEncrypt);
  // Output the encrypted text
  cout << "Encrypted text: " << encryptedText << endl;
}

#pragma endregion SubstEnc

#pragma region SubstDec

double scoreString(const QuadgramScorer& scorer, const string& s) {
  double totalScore = 0.0;
  string cleanText;

  // Clean the string: remove non-alphabetic characters and convert to uppercase
  for (char ch : s) {
    if (isalpha(ch)) {
      cleanText += toupper(ch);
    }
  }

  // Iterate through the cleaned text and extract quadgrams
  size_t len = cleanText.length();
  for (size_t i = 0; i <= len - 4; ++i) {
    string quadgram = cleanText.substr(i, 4);
    totalScore += scorer.getScore(quadgram);
  }

  return totalScore;
}

void computeEnglishnessCommand(const QuadgramScorer& scorer) {
  string inputText;
  cout << "Enter a string to score: ";
  getline(cin, inputText);

  string ct;
  for (char c : inputText) {
    if (isalpha(c)) {
      ct += toupper(c);
    }
  }

  double score = scoreString(scorer, ct);
  cout << "English-ness score: " << score << endl;
}

vector<char> decryptSubstCipher(const QuadgramScorer& scorer,
                                const string& ciphertext) {
  const int max = 1500;
  const int iteration = 20;

  vector<char> bestCipher(ALPHABET.begin(), ALPHABET.end());
  double bestScore = -1e9;

  for (int i = 0; i < iteration; ++i) {
    vector<char> curr = genRandomSubstCipher();
    string decrypted = applySubstCipher(curr, ciphertext);
    double currentScore = scoreString(scorer, clean(decrypted));

    int none = 0;
    while (none < max) {
      vector<char> newCipher = curr;
      int id1 = Random::randInt(ALPHABET.size() - 1);
      int id2;
      do {
        id2 = Random::randInt(ALPHABET.size() - 1);
      } while (id1 == id2);

      swap(newCipher[id1], newCipher[id2]);

      string newDec = applySubstCipher(newCipher, ciphertext);
      double newScore = scoreString(scorer, clean(newDec));

      if (newScore > currentScore) {
        curr = newCipher;
        currentScore = newScore;
        none = 0;
      } else {
        ++none;
      }
    }

    if (currentScore > bestScore) {
      bestCipher = curr;
      bestScore = currentScore;
    }
  }

  return bestCipher;
}

void decryptSubstCipherCommand(const QuadgramScorer& scorer) {
  cout << "Enter text to substitution-cipher decrypt: ";
  string ciphertext;
  getline(cin, ciphertext);

  vector<char> bestCipher = decryptSubstCipher(scorer, ciphertext);
  string decrypted = applySubstCipher(bestCipher, ciphertext);

  cout << "Decrypted text: " << decrypted << endl;
  cout << "Decryption key: " << endl;
  cout << "ABCDEFGHIJKLMNOPQRSTUVWXYZ" << endl;
  for (char c : bestCipher) {
    cout << c;
  }
  cout << endl;
}

void decTextFile(const QuadgramScorer& scorer) {

  string inputFilename;
  getline(cin, inputFilename);

 
  string outputFilename;
  getline(cin, outputFilename);

  ifstream inputFile(inputFilename);

  ofstream outputFile(outputFilename);

  string ciphertext;
  string line;
  while (getline(inputFile, line)) {
    ciphertext += line + '\n';
  }
  inputFile.close();

  vector<char> bestCipher = decryptSubstCipher(scorer, ciphertext);
  string decrypted = applySubstCipher(bestCipher, ciphertext);

  outputFile << decrypted;
  outputFile.close();
}

#pragma endregion SubstDec
