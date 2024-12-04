#include <iostream>
#include <vector>
using namespace std;

// Loops through each of the element in the vector till it finds the match that it wants to find.
static int linearSearch(vector<int> vec , int value){
	

	for(int i = 0; i < vec.size(); i++){
		if(vec[i] == value){
			return i;
		}
	}
	return -1;

}

int main(void)
{
	vector<int> vec = {0, 9, 2, 3, 53, 2, 1, 8, 2, 2};

	int index = linearSearch(vec, 1);

	if(index != 0){
		cout << "Element found at index: " << index << endl;
	}else{
		cout << "Element not found." << endl;
	}
}
