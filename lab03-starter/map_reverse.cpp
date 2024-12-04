#include <map>
#include <set>
#include <string>
#include <vector>
#include <iostream>

using namespace std;

// TODO student: update signature
/**
 * Returns a new map that is the "reversal" of the given map `m`.
 * For example, the map `{{"key", "value"}}` would be reversed to the map
 * `{{"value", "key"}}`.
 */
map<string, string> reverseMap(const map<string, string> m) {
  // TODO student: implement!
  // when you want to reverse something you store it first in a temporary variable.

  map<string, string> reversedMap; // This is the temporary array 

  for(const auto& pair : m){ // for each element called pair in the m map
    reversedMap[pair.second] = pair.first; // what does .first represents the key and .second represents the value
    // so in the blank array at the value position you are setting it to the key
  }
  return reversedMap; // return the above reversed map


  
}

int main() {
  // Because you're changing the signature, we don't have tests for this
  // function. Instead, update this example to demonstrate that your function
  // works as intended!
  map<string, string> example = {
      {"key", "value"},
      {"key 2", "value 2"},
      {"key 3", "value 2"},
  };


  // Print the original map
    cout << "Original map:\n";
    for (const auto& pair : example) { // Again for each element in the map.
        cout << pair.first << " -> " << pair.second << '\n'; // Prints out the key and the value and keeps doing that.
    }

    // Get the reversed map
    map<string, string> reversed = reverseMap(example); // now you are calling the reverse function and then reversing the map

    // you are giving the function the map and then it reverses the map and then prints it out in a new map 



    // Print the reversed map
    cout << "\nReversed map:\n";
    for (const auto& pair : reversed) {
        cout << pair.first << " -> " << pair.second << '\n';// And now finally the reversed map is printed out.
    }

    return 0;


}
