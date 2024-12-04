#include <iostream>
#include <vector>

#include "main.h"

using namespace std;

double average(vector<int> v) {
  int sum = 0;
  for (size_t i = 0; i < v.size(); i++) {
    sum += v[i];
  }
  return sum / v.size();
}

int main() {
  vector<int> elems = {7, 7, 9, 9};
  cout << "Average: " << average(elems) << endl;

  return 0;
}
