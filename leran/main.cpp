// This first block (kept commented) showcases polymorphism with virtual functions.
// // #include <iostream>
// // using namespace std;


// // class person {
// //     // Base class exposes a virtual method so derived types can override behavior.
// //     public:
// //         virtual void Print() {
// //             cout << "im person" << endl;
// //         }
// // };

// // class employee : public person {
// //     // Overrides Print to supply employee-specific output.
// //     public:
// //         void Print() {
// //             cout << "im employee" << endl;
// //         }
// // };

// // class student : public person  {
// //     // Another override to show each derived type chooses its own implementation.
// //     public:
// //         void Print() {
// //             cout << "im student" << endl;
// //         }
// // };


// // int main() {
    

    
// //     employee Employee1;
// //     student  Student1;
// //     //Early-Static Binding: at compilation time
// //     Employee1.Print();
// //     Student1.Print();

// //     cout << endl;
// //     person * Person1 = &Employee1;
// //     person * Person2 = &Student1;
    
// //     //Late-Dynamic Binding: at runtime, the virtual table picks the right override.
// //     Person1->Print();
// //     Person2->Print();
// //     return 0;
// // }



// // #include <iostream>
// // using namespace std;

// // //Abstract Class ==> / Interface ==> / Contract.
// // class Mobile{
// //     virtual void Dial(string PhoneNumber) = 0;
// //     virtual void SendSMS(string Text) = 0;
// //     virtual void TakePicture() = 0;
// // };

// // class iPhone : public Mobile {
// //     // Provides concrete behavior for every pure virtual function.
// //     public:
// //         void Dial(string PhoneNumber) {
// //         }
// //         void SendSMS(string Text) {

// //         }
// //         void TakePicture() { 

// //         }
// //         void MyOwnMethod() { 

// //         }
        
// // };


// // class Samasung : public Mobile {
// //     // Another concrete implementation that must honor the same interface.
// //     public:
// //         void Dial(string PhoneNumber) {
// //         }
// //         void SendSMS(string Text) {

// //         }
// //         void TakePicture() { 

// //         }
// //         void MyOwnMethod() { 

// //         }
// // };


// // int main() {
// //     iPhone iPhone17ProMax;
// //     Samasung SamasungNote25;
// //     return 0;
// // }



// Active example: exploring friend classes and friend functions.
// #include <iostream>
// using namespace std;

// class A { 
//     // Holds data with different access levels to illustrate encapsulation.
//     private:
//         int _var1;
//     protected:
//         int _var3;
//     public:
//         int var2;
//     A() {
//         _var1 = 10;
//         var2 = 99;
//         _var3 = 67; 
//     }
//     friend class B; //friend class 
//     friend int MySum(A a1); // friend function 
// };

// class B { 
//     // Because B is declared as a friend, it can access even private data members.
//     public:
//         void display(A a1) {
//             cout << endl << "The value of var1 = " << a1._var1 << endl;
//             cout << endl << "The value of var2 = " << a1.var2 << endl;
//         }
// };


// int MySum(A a1) {
//     // Friend functions let standalone helpers tap into private/protected members.
//     return a1.var2 + a1._var1 + a1._var3;
// }

// int main() { 
//     A a1;
//     B b1;

//     // Friend function and friend class both bypass the usual access rules.
//     cout << "sum = " << MySum(a1);

//     // Friend class example: call a method that can print private data.
//     b1.display(a1);
//     return 0;
// }

// // Structure Inside Class

// #include <iostream>
// using namespace std;


/**
 * @class Person
 * @brief Represents a person with their full name and address information.
 * 
 * This class demonstrates several Object-Oriented Programming (OOP) concepts:
 * - Encapsulation: Private nested struct (stAddress) hides address implementation details
 * - Data members: Public and private data organization
 * - Constructor: Initializes object with default values
 * - Member functions: Methods to operate on the object's data
 * 
 * Learning Points:
 * - Nested structures can be used to group related data (address components)
 * - Constructors run automatically when an object is created
 * - Access modifiers (private/public) control visibility of members
 * - Member functions can access both private and public data of the class
 */

/**
 * @struct stAddress
 * @brief Private nested structure to encapsulate address components.
 * 
 * Learning: This is a nested struct, only accessible within the Person class.
 * It groups related address data together, demonstrating composition.
 */

/**
 * @var Person::FullName
 * @brief Stores the complete name of the person.
 * 
 * Learning: Public member variable - can be accessed directly from outside the class.
 */

/**
 * @var Person::Address
 * @brief Contains the person's address details using the stAddress structure.
 * 
 * Learning: Public member of custom type (struct), demonstrates composition pattern.
 */

/**
 * @brief Default constructor that initializes a Person object with default values.
 * 
 * Learning Points:
 * - Constructors have the same name as the class
 * - No return type (not even void)
 * - Called automatically when creating an object
 * - Used to set initial/default values for member variables
 */

/**
 * @brief Prints all address details to the console.
 * 
 * Learning Points:
 * - Member function (method) operates on the object's data
 * - Can access both private (stAddress structure) and public members
 * - Uses cout for console output
 * - Demonstrates how to work with nested structure members
//  */
// class Person {
//     private:
//         struct stAddress { 
//             string AddressLine1;
//             string AddressLine2;
//             string City;
//             string Country;
//         };
//     public:
//         string FullName;
//         stAddress Address;
//         Person() {
//             FullName = "Faris EmadElden";
//             Address.AddressLine1 = "";
//             Address.AddressLine2 = "";
//             Address.City = "Aqaba";
//             Address.Country = "Jordan";
//         }
//         void PrintAddress() {
//             cout << "\nAddress Details:\n";
//             cout << "Address Line 1: " << Address.AddressLine1 << endl;
//             cout << "Address Line 2: " << Address.AddressLine2 << endl;
//             cout << "City: " << Address.City << endl;
//             cout << "Country: " << Address.Country << endl;
//         }
// };

// int main() {
//     Person Faris;

//     Faris.PrintAddress();

//     return 0;
// }



// // Nested Classes
// //ProgrammingAdivces.com
// //Mohammed Abu-Hadhoud
// #include<iostream>
// using namespace std;

// class clsPerson {

//     string _FullName;

//     class clsAddress
//     {
    
//     private :
//         string _AddressLine1;
//         string _AddressLine2;
//         string _City;
//         string _Country;
//     public:
       
       
//         clsAddress(string AddressLine1, string AddressLine2, string City, string Country)
//         {
//             _AddressLine1 = AddressLine1;
//             _AddressLine2 = AddressLine2;
//             _City = City;
//             _Country= Country;

//         }

//         string setAddressLine1(string AddressLine1)
//         {
//             _AddressLine1 = AddressLine1;
//         }

//         string AddressLine1()
//         {
//            return _AddressLine1 ;
//         }

//         string setAddressLine2(string AddressLine2)
//         {
//             _AddressLine2 = AddressLine2;
//         }

//         string AddressLine2()
//         {
//             return _AddressLine2;
//         }


//         string setCity(string City)
//         {
//             _City = City;
//         }

//         string City()
//         {
//             return _City;
//         }


//         string setCountry(string Country)
//         {
//             _Country = Country;
//         }

//         string Country()
//         {
//             return _Country;
//         }

//         void Print()
//         {
//             cout << "\nAddress:\n";
//             cout << _AddressLine1 << endl;
//             cout << _AddressLine2 << endl;
//             cout << _City << endl;
//             cout << _Country << endl;
//         }
//     };

 

// public:
   
//     string setFullName(string FullName)
//     {
//         _FullName = FullName;
//     }

//     string FullName()
//     {
//        return _FullName ;
//     }
   
//     clsAddress Address =  clsAddress("", "","","");

//     clsPerson(string FullName, string AddressLine1, string AddressLine2, string City, string Country)
//     {
//         _FullName = FullName;

//         //initiate address class by it's constructor
//         Address =  clsAddress (AddressLine1, AddressLine2, City, Country);

//     }
// };

// int main()

// {

//     clsPerson Person1("Mohammed Abu-Hadhoud", "Building 10", "Queen Rania Street", "Amman", "Jordan");
    
//     Person1.Address.Print();

//     return 0;
// }


//Separate Classes In Libraries 
// #include <iostream>
// #include "Person.h"
// #include "Employee.h"
// using namespace std;




// int main() {
//     Employee emp1("E001", "Faris", "Emad", "Software Engineer",
//                   "faris.emad@company.com", "+20-123-456-7890", 50000.0, "IT");
    
//     // Display employee information
//     emp1.PrintInfo();

    
//     // Send email notification
//     emp1.SendEmail("Welcome to the Team", "Dear " + emp1.FirstName() + ", Welcome aboard!");
    
//     // Send SMS notification
//     emp1.SendSMS("Your first day is tomorrow at 9 AM");
    
//     // Test setters
//     cout << "\n==================================================\n";
//     cout << "         Testing Setters\n";
//     cout << "==================================================\n";
//     emp1.SetSalary(55000.0);
//     emp1.SetTitle("Senior Software Engineer");
    
//     cout << "Updated Salary: " << emp1.Salary() << endl;
//     cout << "Updated Title: " << emp1.Title() << endl;

//     return 0;
// }


// #include <iostream>
// using namespace std;


// class Employee{
//     public:
//         int ID;
//         string Name;
//         float Salary;
//         Employee(int ID, string Name, float Salary) {
//             this->ID = ID;
//             this->Name = Name;
//             this->Salary = Salary;
//         }
//         static void Func1(Employee Emp) {
//             Emp.Print();
//         }
//         void Func2() {
//             Func1(*this);
//         }
//         void Print() {
//             cout << ID << " " << Name << " " << Salary << endl;
//         }
// };

// int main() {
//     Employee Emp1(102, "Faris", 9999);
//     Emp1.Print();
//     cout << endl;
//     Emp1.Func2();
//     return 0;
// }


//ProgrammingAdivces.com
//Mohammed Abu-Hadhoud
#include<iostream>

using namespace std;

class clsA
{

public:
	int x;

	void Print()
	{
		cout << "The value of x=" << x <<endl;
	}

};


//object sent by value, any updated will not b reflected
// on the original object
void Fun1(clsA A1)
{

	A1.x = 100;
}


//object sent by reference, any updated will be reflected
// on the original object
void Fun2(clsA &A1)
{

	A1.x = 200;
}


int main() 

{
	clsA A1;

	A1.x = 50;
	cout << "\nA.x before calling function1: \n";
	A1.Print();


	//Pass by value, object will not be afected.
	Fun1(A1);
	cout << "\nA.x after calling function1 byval: \n";
	A1.Print();

	//Pass by value, object will be afected.
	Fun2(A1);
	cout << "\nA.x after calling function2 byref: \n";
	A1.Print();


	system("pause>0");

}

