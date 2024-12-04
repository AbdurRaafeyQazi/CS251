#include <iostream>

using namespace std;

// class entity
// {
// 	public:

// 	float x, y;

// 	void move(float xa, float ya)
// 	{
// 		x += xa;
// 		y += ya;

// 	}
// };

// class player : public entity
// {
// 	public:

// 	const char* name;

// 	void printName()
// 	{
// 		cout << name << endl;
// 	}

// };

// int main()
// {

// 	player messy;
// 	messy.move(5, 5);
// 	messy.x = 3;
	
// 	cout << sizeof(entity) << endl;
	
// }


#include <iostream>

using namespace std;

// MenuItem is a simple base class with a single public member variable
class MenuItem
{
public:
  string name;
  
  // Try uncommenting this default constructor, and then making the change to 
  // the derived class default constructor suggested below to see what happens!
  /*
  MenuItem()
  {
    name = "unknown";
    cout << "Base Class Default Constructor" << endl;
  }
  */
  
  // MenuItem's parameterized constructor
  MenuItem(string set_name)
  {
    name = set_name;
    cout << "Base Class Param Constructor" << endl;
  }
};

// Drink is a simple derived class with a single public member variable
class Drink : public MenuItem
{
public:
  double ounces;
  
  // Drink inherits all the constructors of MenuItem with this statement!
  using MenuItem::MenuItem;

  // After uncommenting the default constructor in MenuItem above, replace 
  // the below Drink default constructor function header with this:
  // Drink()
  //
  // We'll find that calling the default Drink constructor will first call 
  // the default MenuItem constructor!

  // Drink's default constructor calls MenuItem's parameterized constructor 
  // with the argument "unknown"
  Drink() : MenuItem("unknown")
  {
    ounces = 8;
    cout << "Derived Class Default Constructor" << endl;

  }
  
  // Drink's parameterized constructor calls MenuItem's parameterized 
  // constructor with the argument "n/a"
  Drink(double set_ounces) : MenuItem("n/a")
  {
    ounces = set_ounces;
    cout << "Derived Class Param Constructor" << endl;
  }
  
};

int main()
{
  // The parameterized MenuItem (base class) constructor will be called followed
  // by the parameterized Drink (derived class) constructor
  Drink hot_chocolate1("hot_chocolate");
  
  // The parameterized MenuItem constructor will be called followed by the 
  // default Drink constructor... unless we make the changes described above,
  // in which case the default constructor of MenuItem will be called followed 
  // by the default constructor of Drink
  //
  // Uncomment to try...
  //
  // Drink hot_chocolate2;

  // the inherited parameterized MenuItem constructor will be called... and NO 
  // constructor defined explicitly for the Drink object will be called, as we 
  // have used inheritance to "make" MenuItem's parameterized constructor a 
  // constructor of Drink objects now too!
  //
  // Uncomment to try...
  //
  // Drink hot_chocolate3(20);

  return 0;
}