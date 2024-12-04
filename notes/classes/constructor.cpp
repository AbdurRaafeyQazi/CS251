#include <iostream>

using namespace std;

class Cat
{
	private:
	
	string name;
	string color;
	string fav_toy;

	public:

	void printCat()
  	{
    cout << "Name: " << name << endl;
    cout << "Color: " << color << endl;
    cout << "Favourite Toy: " << fav_toy << endl;
  	}

	// Since all the Member variables are in the Private class, There is currently no way to Initialize the Variables.
	// This is where the constructor comes in.
	Cat()
  	{
    name = "Unknown";
    color = "Unknown";
    fav_toy = "Unknown";
  	}

	Cat(string n)
  	{
    name = n;
    color = "Unknown";
    fav_toy = "Uknown";
  	}

	// constructor parameters can have default values such as the default favorite 
  	// toy value "Laser Pointer", we can also define constructors outside the 
  	// Class such as this example, as long as we leave function declaration 
  	// (i.e. prototype) in the class
  	Cat(string n, string c, string ft = "Laser Pointer");


};



// we use the syntax ClassName::ClassName( ... ) to define the constructor 
// outside the class...
Cat::Cat(string n, string c, string ft)
{
  name = n;
  color = c;
  fav_toy = ft;
}



int main()
{
  // the constructor with no parameters will be called
  Cat cat1;
  
  cout << "Cat 1..." << endl;
  cat1.printCat();
  cout << endl;
  
  
  // the constructor that accepts a single argument will be called
  Cat cat2("Spot");
  
  cout << "Cat 2..." << endl;
  cat2.printCat();
  cout << endl;
  

  // the constructor that accepts 3 arguments will be called, but the default 
  // value will be used for the 3rd argument
  Cat cat3("Garfield", "Orange");
  
  cout << "Cat 3..." << endl;
  cat3.printCat();
  cout << endl;
  
  return 0;
}