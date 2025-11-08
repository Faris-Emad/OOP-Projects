#pragma once
#include <iostream>
#include "Person.h"
using namespace std;


class Employee : public Person {
    private:
        string _Title;
        string _Department;
        float _Salary;
    public:
    Employee(string ID, string FirstName, string LastName, string Title,
         string Email, string Phone, float Salary, string Department) :  Person( ID, FirstName,  LastName,  Email,  Phone) {
            _Title = Title;
            _Department = Department;
            _Salary = Salary;
        }
        void SetTitle(string Title) {
            _Title = Title;
        }
        void SetDepartment(string Department) {
            _Department = Department;
        }
        void SetSalary(float Salary) {
            _Salary = Salary;
        }
        string Title(){
            return _Title;
        }
        string Department() {
            return  _Department;
        }
        float Salary() {
            return _Salary;
        }
        void PrintInfo() {
            cout << "==================================================\n";
            cout << "              Employee Information\n";
            cout << "==================================================\n";
            cout << "ID         : " << ID() << endl;
            cout << "First Name : " << FirstName() << endl; 
            cout << "Last Name  : " << LastName() << endl; 
            cout << "Full Name  : " << FullName() << endl; 
            cout << "Title      : " << _Title << endl;
            cout << "Email      : " << Email() << endl; 
            cout << "Phone      : " << Phone() << endl; 
            cout << "Salary     : " << _Salary << endl;
            cout << "Department : " << _Department << endl;
        }
    
};
