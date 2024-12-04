#include <iostream>

using namespace std;

class ourvector {
 private:
  int* data;
  int capacity;
  int numElements;

  void resize(int newCapacity) { // declares an int variable called newCapacity that will be given a value
    if (newCapacity > capacity) { // If newer is better then use newer
      int* newData = new int[newCapacity]; // In order to use newer, create a new variable called newData and assign it with the size of the newer

      for (int i = 0; i < numElements; ++i) { // As long as you are within the numberof elements. ie the immediate size of the array 
        newData[i] = data[i]; // Take the frail dynamic array and assign all of its values to the new array.
      } // newData was made here but data is from ourVector, after copying The data from data to newData. 

      // Since now we copied ll the data from the old to the new, We need to free the memeory, so that we dont take unnecessary space since it will become inaccessiable 
      delete[] data; // free the memory

      data = newData; // will now point to the address of the newData so that data will now become the newData
      capacity = newCapacity; // these are just values 

    }
  }

 public:
  ourvector() {
    capacity = 2;
    numElements = 0;
    data = new int[capacity]; // allocate the the capacity size but currently has 0 elements in it 
  }

  void push_back(int value) { // Whatever int values comes in here is going to be pushed back into the array
    if (numElements == capacity) { // This the rule. if there is no more space left in the array then
      resize(capacity + 1); // Call the resize function and capacity + 1 will disguise as newCapacity and go into the resize function
    }

    data[numElements] = value; // Data is pointing to the numElement'th index which is currently zero, Then store "value" at that index
    numElements++; // Now since you have added something to the array, increment this.
  }

  int size() { // This is just a getter function
    return numElements; // just returns the size of the data array from the pushback fuction.
  }

  int at(int index) { // Takes in a value 
    return data[index]; // Just returns the value at the position of index -> data[value given by the program]
  }

  ~ourvector() {
    delete[] data; // After the function runs free all of the memory that was used.
  }
};

int sumvec(ourvector& v) {
  int sum = 0;  // are you sure you want to go to the size after starting from zero MAYBE BUGGY HERE.
  for (int j = 0; j < v.size(); j++) {  // Loop through all the elements of the array  
    sum += v.at(j); // While looping through all of the elements add them to the summ variable
  }
  return sum;
}

int main() {
  ourvector vec;
  int i = 0;
  while (i <= 10) {
    vec.push_back(i++); // just add elements from 0 to 10 in the array.
  }
  cout << "summation = " << sumvec(vec) << endl;
}