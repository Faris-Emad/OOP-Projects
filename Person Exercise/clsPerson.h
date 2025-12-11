#pragma once
#include <iostream>
using namespace std;


class clsPerson {
    private:
        string _ID;
        string _FirstName; 
        string _LastName;
        string _Email;
        string _Phone;
    public:
        clsPerson(string ID,string FirstName, string LastName, string Email, string Phone) {
            _ID = ID;
            _FirstName = FirstName;
            _LastName = LastName;
            _Email = Email;
            _Phone = Phone;
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

        void PrintInfo() {
            cout << "==================================================\n";
            cout << "              Person Information\n";
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