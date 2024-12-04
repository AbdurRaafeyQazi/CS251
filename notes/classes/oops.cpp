#include <iostream>
using std::string;
using namespace std;

/*
Implement an Abstract class with Certain Rules,
and the rules are the Pure Virtual Functions.
This means that WhichEver Class Inherits this Abstract Class will have to provide Implementation 
*/
class AbstractEmployee
{	
	// Now this is a Pure Virtual Function.
	// This Class has now become a abstract class.
	// This Method has become a PURE VIRTUAL FUNCTION, OR A ABSTRACT FUNCTION.
	// ie, whoever calls this sub class will have to provide implementation for the function from below.
	virtual void AskForPromotion() = 0; 
};



class Employee : AbstractEmployee // Abstract class is being called here. 
{

private:

	// Since these are Encapsulated and are now in private. To access, you must use Getters and Setters.
	string Company;
	int Age;

protected:
	
	string Name;

public:

	// Creating Getter for the Encapsulated.	
	void setName(string name)
	{
		Name = name;
	}

	// Creating Setter for the Encapsulated.
	string getName() const
	{
		return Name;
	}

	// Creating Getter for the Encapsulated.	
	void setCompany(string company)
	{
		Company = company;
	}

	// Creating Setter for the Encapsulated.
	string getCompany() const
	{
		return Company;
	}

	// Creating Getter for the Encapsulated.	
	void setAge(int age)
	{	// If body statement only contains one line then you can omit the line
		if(age >= 18) Age = age; // These are certain VALIDATION rules that you can apply to SETTERS !!!
	}

    // Creating Setter for the Encapsulated.
	int getAge() const
	{
		return Age;
	}



	// Moving these into Private is called Encapsulation
	// string Name;
	// string Company;
	// int Age;

	void introduceUrSelf() // MEMBER FUNCTION OR METHOD
	{
		cout << "Name - " << Name << endl;
		cout << "Company - " << Company << endl;
		cout << "Age - " << Age << endl;
	}

	// Another way to do this (Called initialization list)
	// Default constructor: initializes x and y to 0
	// Shape::Shape() : x(0), y(0) {}

	// THREE RULES OF CONSTRUCTORS: NO RETURN TYPE, SAME NAME AS CLASS, MUST BE PUBLIC
	Employee(string name, string company, int age)
	{
		Name = name;
		Company = company;
		Age = age;
	}

	// This is the implementation for the Abstract Class
	void AskForPromotion()
	{
		if(Age > 30)
		{
		cout << Name << " got promoted!" << endl;
		}else{
			cout << Name << ", sorry NO promotion for you!" << endl;

		}
	}

	virtual void 
	Work()
	{
		cout << Name << " is checking email, task backlog, performing tasks..." << endl;
	}

};

// Inherits from the Parent Class
class Developer : public Employee // Make this Public if you want to access the Abstract Class.
{

public:
	string FavProgrammingLanguage;
	// Since There was Priviously a Constructor in the Parent Class you will have to have to Call the Parent class here, and give the same parameters as the Constructor over there.
	Developer(string name, string company, int age, string favProgrammingLanguage) : Employee(name, company, age)
	{	// But since all the other variables were already assined values you do not need to do that again for them.
		FavProgrammingLanguage = favProgrammingLanguage;
	}

	void FixBug() // Create a Function/Method to call and test the Newly created variable.
	{
		// If you use Variables in Protected then the Sub Class can directly access it.
		// But if not then you would have to use Getters and Setters to access the Variables. 
		cout << Name << " fixed bug using " << FavProgrammingLanguage << endl;
	}

	void Work()
	{
		cout << Name << " is writing " << FavProgrammingLanguage << " code" << endl;
	}

};

class Teacher : public Employee
{	
	public:
	string Subject;
	
	void PrepareLesson()
	{
		cout << Name << " is preparing " << Subject << " lesson" << endl;
	}

	Teacher(string name, string company, int age, string subject) : Employee(name, company, age)
	{
		Subject = subject;
	}

	void Work()
	{
		cout << Name << " is teaching " << Subject << endl;
	}

};

class Book
{
public:

	string Title;
	string Author;
	float* Rates;
	int RatesCounter;

	Book(string title, string author)
	{
		Title = title;
		Author = author;

		RatesCounter = 2;
		Rates = new float[RatesCounter];
		Rates[0] = 5;
		Rates[1] = 4;

	}

	~Book()
	{
		delete[] Rates;
		Rates = nullptr;
	}

	Book(const Book& original) // Only when you are passing an Object to a Function by Value, Also returning by value.
	{
		Title = original.Title;
		Author = original.Author;
		RatesCounter = original.RatesCounter;

		Rates = new float[RatesCounter];
		for(int i = 0; i < RatesCounter; i++)
		{
			Rates[i] = original.Rates[i];
		}

	}

};

void PrintBook(Book book)
{
	cout << "Title: " << book.Title << endl;
	cout << "Author: " << book.Author << endl;

	float sum = 0;

	for(int i = 0; i < book.RatesCounter; i++)
	{
		sum += book.Rates[i];
	}

	cout << "Avg rate: " << sum/book.RatesCounter << endl;

}

int main()
{
	// MARK 1
	// This line is just the Object of the Class but with the default Constructor
	Employee employee1 = Employee("Abdur", "Good one InshaAllah", 19); // Object of the employee class
	// employee1.Name = "Abdur";
	// employee1.Company = "Good one Inshallah";
	// employee1.Age = 19;
	// employee1.introduceUrSelf();
	// Every time you need to add an employee (USING A FUNCTION) you have to do this, THIS IS WHERE CONSTRUCTORS COME IN.
	// This line is just the Object of the Class but with the default Constructor
	Employee employee2 = Employee("John", "Amazon", 33);
	// employee2.Name = "John";
	// employee2.Company = "Amazon";
	// employee2.Age = 33;
	// employee2.introduceUrSelf();
	// MARK 1

	// MARK 2
	// Testing Getters and Setters
	// employee1.setAge(1);
	// cout << employee1.getName() << " is " << employee1.getAge() << " years old" << endl;
	// MARK 2

	// MARK 3
	// This runs the Abstract class
	// employee1.AskForPromotion();
	// employee2.AskForPromotion();
	// MARK 3

	// MARK 4
	// This Just creates an Object and then sets the default Constructor values.
	// Developer d = Developer("Abdur" , "Good one Inshallah" , 19 , "C");
	// d.FixBug(); // Calls the method to print out the values.
	// d.FixBug();
	// d.FixBug();
	// d.FixBug();
	// d.AskForPromotion(); // Need to make the parent class public when calling in the sub class in order for this to work
	
	// Teacher t = Teacher("Jack", "Cool School", 35, "History");
	// t.PrepareLesson();
	// t.AskForPromotion();
	// MARK 4

	// MARK 5
	// The most common use of Polymorphis is when a Parent Class reference is used to refer to a child class object.
	// d.Work();
	// t.Work();

	// The Employee class(Base Class) is holding a Reference to Derived Class Object.
	// Employee* e1 = &d;
	// Employee* e2 = &t;

	// e1->Work();
	// e2->Work();

	// MARK 5

	// MARK 6
	Book book1("Boy21", "Da pomky");
	Book book2("Fire Force", "Tamki");

	Book book3 = book1; // You want to Pass the book1 and create a book 3. COPY THE OBJECT.
	PrintBook(book1);
	PrintBook(book2);
	PrintBook(book3);
	// MARK 6

	// MARK 7
	
	// MARK 7

}