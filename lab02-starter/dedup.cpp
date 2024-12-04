#include <iostream>
#include <string>
#include <vector>

using namespace std;

// TODO student: FIXME!
void deduplicate(vector<string>& vec) { // is it supposed to be passed by adress, yes it was
  for (int i = 0; i < vec.size() -1;) { // increment one less than the vector size since it starts from 0 to avoid out of bounds error
    if (vec.at(i) == vec.at(i + 1)) { // check for duplicates
      vec.erase(vec.begin() + i); // remove the duplicate
    }else{
      i++; //if everything is fine then increment i to move on to the next element.
    }
  }
}

int main() {
  vector<string> drinks = {
      "coffee",
      "coffee",
      "coffee",
      "hot chocolate",
      "tea",
      "tea",
      
  };

  deduplicate(drinks);

  // drinks should now contain {"coffee", "hot chocolate", "tea"}:
  for (const auto& d : drinks) {
    cout << d << endl;
  }
}
