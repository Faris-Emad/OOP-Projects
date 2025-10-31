/**
 * @file employee.cpp
 * @brief Homework - Employee Exercise
 * 
 * @description
 * Create an Employee class that contains the following:
 * 
 * Required Properties:
 * - ID (Read-only - getter only, no setter)
 * - First Name (with getter and setter)
 * - Last Name (with getter and setter)
 * - FullName() - returns concatenation of first and last name
 * - Title (with getter and setter)
 * - Email (with getter and setter)
 * - Phone (with getter and setter)
 * - Salary (with getter and setter)
 * - Department (with getter and setter)
 * 
 * Required Methods:
 * - SendEmail(Subject, Body) - sends email notification to employee
 * - SendSMS(Message) - sends SMS notification to employee
 * - Print() - displays all employee information
 * 
 * Implementation Requirements:
 * - All properties must have getters (get methods)
 * - All properties must have setters (set methods) EXCEPT ID
 * - ID should be read-only (getter only, initialized in constructor)
 * 
 * @note This exercise demonstrates OOP principles: encapsulation, data hiding,
 *       and object-oriented design in C++
 * 
 * @author Faris Emad
 * @date 31-10-2025
 */
#include <iostream>
using namespace std;

class Employee {
    private:
        string _ID;
        string _FirstName; 
        string _LastName;
        string _Email;
        string _Phone;
        string _Title;
        string _Department;
        float _Salary;
    public:
        Employee(string ID,string FirstName, string LastName, string Email, string Phone,string Title, string Department, float Salary) {
            _ID = ID;
            _FirstName = FirstName;
            _LastName = LastName;
            _Email = Email;
            _Phone = Phone;
            _Title = Title;
            _Department = Department;
            _Salary = Salary;
        }
        string GetID() {
            return _ID;
        }
        void SetFirstName(string FirstName) {
            _FirstName = FirstName;
        }
        void SetLastName(string LastName) {
            _LastName = LastName;
        }
        void SetEmail(string Email) {
            _Email = Email;
        }
        void SetPhone(string Phone) {
            _Phone = Phone;
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
        string FirstName() {
            return _FirstName;
        }
        string LastName() {
            return _LastName;
        }
        string FullName() {
            return _FirstName + " " + _LastName;
        }
        string Email() {
            return _Email;
        }
        string Phone() {
            return _Phone;
        }
        string Title(){
            return _Title;
        }
        string Department() {
            return  _Department;
        }
        int Salary() {
            return _Salary;
        }

        void PrintInfo() {
            cout << "==================================================\n";
            cout << "              Employee Information\n";
            cout << "==================================================\n";
            cout << "ID         : " << _ID << endl;
            cout << "First Name : " << _FirstName << endl; 
            cout << "Last Name  : " << _LastName << endl; 
            cout << "Full Name  : " << FullName() << endl; 
            cout << "Email      : " << _Email << endl; 
            cout << "Phone      :" << _Phone << endl; 
        }

        void SendEmail(string Subject, string Body) {
            cout << "\n==================================================\n";
            cout << "           Email Notification\n";
            cout << "==================================================\n";
            cout << "The following message sent successfully to:\n"; 
            cout << "Email: " << _Email << endl;
            cout << "\nSubject: " << Subject << endl; 
            cout << "Body: " << Body << endl;
        }
        void SendSMS(string Message) {
            cout << "\n==================================================\n";
            cout << "            SMS Notification\n";
            cout << "==================================================\n";
            cout << "The following SMS sent successfully to:\n"; 
            cout << "Phone: " << _Phone << endl;
            cout << "\nMessage: " << Message << endl; 
        }
    
};

int main() {


    return 0;
}