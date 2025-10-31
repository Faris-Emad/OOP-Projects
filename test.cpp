#include <iostream>
#include <string>
using namespace std;

// class Address {
//     private:
//         string _AddressLine1;
//         string _AddressLine2;
//         string _POBox; 
//         string _ZipCode;
//     public:
//         Address(string AddressLine1, string AddressLine2, string POBox, string ZipCode) {
//             _AddressLine1 = AddressLine1;
//             _AddressLine2 = AddressLine2;
//             _POBox = POBox;
//             _ZipCode = ZipCode;
//         }
//         // copy Constructor
//         Address(Address &bj_old) {
//             _AddressLine1 = bj_old.AddressLine1();
//             _AddressLine2 = bj_old.AddressLine2();
//             _POBox = bj_old.POBox();
//             _ZipCode = bj_old.ZipCode();
//         }
//         void SetAddressLine1(string AddressLine1) {
//             _AddressLine1 = AddressLine1;
//         }
//         string AddressLine1() {
//             return _AddressLine1;
//         }
//         void SetAddressLine2(string AddressLine2) {
//             _AddressLine2 = AddressLine2;
//         }
//         string AddressLine2() {
//             return _AddressLine2;
//         }
//         void SetPOBox(string POBox) {
//             _POBox = POBox;
//         }
//         string POBox() {
//             return _POBox;
//         }
//         void SetZipCode(string ZipCode) {
//             _ZipCode = ZipCode;
//         }
//         string ZipCode() {
//             return _ZipCode;
//         }
//         void Print() {
//             cout << "\nAddress Datails:\n";
//             cout << "---------------------------------";
//             cout << "\nAddressLine1:  " << _AddressLine1 << endl;
//             cout << "AddressLine2  :  " << _AddressLine2 << endl;
//             cout << "POBox         :  " << _POBox <<  endl;
//             cout << "ZipCode       :  " << _ZipCode << endl; 
//         }
// };

class Person {
    private:
        string name;
    public:
        Person() {
            name = "Faris";
            cout << "\nHi, I'm Constructor";
        }
        ~Person() {
            cout << "\nHi, I'm Destructor";
        }
};

// void fun(){
//     Person P;
// }
// void fun2(){
//     Person* P2 = new Person;
//     delete P2;
// }


//static Members

class A {
    public:
        // int var;
        // static int counter;
        // A(){
        //     counter++;
        // }
        // void print(){
        //     cout << "\n Var = " << var << endl;
        //     cout << "counter = " << counter << endl;
        // }
        static int Function1() {
            return 67;
        }
        int Function2() {
            return 69;
        }
};

// Static Members
// int A::counter = 0;
//static variable initialisation outside the class

int main() {
    // Address A1("Egypt", "Aqaba", "42s2", "09112");
    // A1.Print();
    // Address A2 = A1;
    // A2.Print();
    
    // fun();
    // fun2();
    
    // A P1, P2, P3;
    // P1.var = 10;
    // P2.var = 20;
    // P3.var = 30;

    // P1.print();
    // P2.print();
    // P3.print();

    // cout << "\nafter changing the static member counter in one object:\n";
    // P1.counter = 900;
    // P1.print();
    // P2.print();
    // P3.print();
    A P1, P2;
    cout << A::Function1() << endl;
    
    //cout << A::Function2() << endl;
    //error: cannot call member function 'int A::Function2()' without object
    cout << P1.Function2() << endl;
    cout << P2.Function2() << endl;
    cout << P1.Function1() << endl;
    cout << P2.Function1() << endl;
    return 0;
}