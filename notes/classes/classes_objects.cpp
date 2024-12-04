#include <iostream>
#include <string>

using namespace std;

// Class is basically a BluePrint
class BankAccount // BankAccount is an object
{
	public:
	// (Step 1)
	// These 2 are Member Variables, or known as attributes 
	string name;
	int balance;

	// Member Functions are also known as Methods
	// Member Functions work with Member Variables. (Step 2)
	// Member Functions can directly Access and work with Member Variables
	void withdraw(int amount)
	{
		balance = balance - amount;
	}

	void print()
	{
		cout << name << " has " << balance << " dollars " << endl;
	}

};


int main()
{	

	// And Objects are the Products of the BluePrints
	// Creates a BankAccount Object and Account1 is an Instance of the BankAccount Class
	BankAccount Account1;
	Account1.name = "Abdu";
	Account1.balance = 99;

	Account1.print();

	// Creates another BankAccount Object and another Instance of the BankAccount Class
	BankAccount Account2;
	Account2.name = "Monkey";
	Account2.balance = 10;

	cout << Account2.name << " had " << Account2.balance << " dollars " << endl;
	Account2.balance = Account2.balance - 5;
	Account2.print();

	// (Step 2)
	// Now instead of using the .Operator to do Individual operations on the member variables, you can use the .Operator to Operate using Member Function on the Member Variable of a Class Instance.
	Account1.withdraw(50);
	Account1.print();



}