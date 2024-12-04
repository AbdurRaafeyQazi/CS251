#include <iostream>

using namespace std;

void f1() {
  int arr[5] = {1, 2, 3, 4, 5};
  //for (int i = 0; i <= 5; ++i) { // accesses values past what was allocated in memory
  for (int i = 0; i < 5; ++i) { // This is the fix
    cout << arr[i] << endl;
  }
}

void f2() {
  int* ptr = nullptr;  // You might need to allocate it new memory before
  ptr = new int;// assigning it memory based on its type. // This is the fix 
  *ptr = 42;
}

void f3() {
  int* arr = new int[5];  // Tried to free the memory twice, which will cause a
  delete[] arr; // double free error.
  // delete[] arr; // Removing this will fix it.
}

void f4() {         
  int* p = new int;  // Nothing to fix here, since it allocates memory for the pointer and then dereferences the pointer to store an int value in it
  *p = 5;
  delete p;
}

void f5() {
  // int* ptr; // Also you cannot just declare a pointer to nothing you have to
  // initialize it to something even if its to NULL. *ptr = 42;

  int value = 42;  // This is the fix // a pointer cannot just store the direct value it has to store the address of the value. then point to the adress
  int* ptr = &value; 


}

int main() {
  // Call the functions here.
  //f1();
  // f2();
  // f3();
  // f4();
  // f5();
}





