#include <iostream>
using namespace std;

class basicNumber
{
public:
	int n;

	basicNumber(int set_n)
	{
		n = set_n;
	}

	basicNumber(const basicNumber &basic_number) // copy construct is only called when 1 object initialized another object
	{
		n = 2 * basic_number.n;

		cout << "Copy constructor called" << endl;
	}
};
// Default copy constructor does a member wise assignment

class number
{
public:
	int* n;

	number(int set_n)
	{
		n = (int*) new int;
		*n = set_n;
	}

	number(const number& other)
	{
		n = (int*) new int;
		*n = *(other.n);
 	}

	~number()
	{
		delete n;
		n = nullptr;
	}

	int get()
	{
		return *n;
	}


};

int main()
{

	// basicNumber num1(7);
	// cout << "num1: " << num1.n << endl;

	// // Only this will call the copy constructor.
	// basicNumber num2 = num1; // Assigns the values of the Member Variables of num1 to the Member Variables of num2
	// cout << "num2: " << num2.n << endl;

	// basicNumber num3(3);
	// basicNumber num4(4);

	// num3 = num4;


	//------------------------------------------------------------------

	number numA(8);
	cout << "numA: " << numA.get() << endl;

	number numB = numA;
	cout << "numB: " << numB.get() << endl;

	*(numA.n) = 20; // Dereferencing the member variable n of the numA object
	cout << "numA: " << numA.get() << endl;
	cout << "numB: " << numB.get() << endl;

	*(numB.n) = 99; // Changing a or b, since pointing to the same space in memory will change the actual value
	cout << "numA: " << numA.get() << endl; 
	cout << "numB: " << numB.get() << endl;


	//exit(0);

	return 0;
}