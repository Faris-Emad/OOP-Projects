/*
==================================================
              Person Information
==================================================
ID         : 10
First Name : Mohammed
Last Name  : Abu-Hadhoud
Full Name  : Mohammed Abu-Hadhoud
Email      : my@gmail.com
Phone      : 0098387727

==================================================
           Email Notification
==================================================
The following message sent successfully to:
Email: my@gmail.com

Subject: Hi
Body: How are you?

==================================================
            SMS Notification
==================================================
The following SMS sent successfully to:
Phone: 0098387727
Message: How are you?
==================================================
*/
#include <iostream>
using namespace std;

class Person {
    private:
        string _ID;
        string _FirstName; 
        string _LastName;
        string _Email;
        string _Phone;
    public:
        Person(string ID,string FirstName, string LastName, string Email, string Phone) {
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

int main() {
    Person Faris("1","Faris", "Emad", "Faris@gmail.com", "01000022201");
    Faris.PrintInfo();
    
    // Test SendEmail method
    Faris.SendEmail("Hi", "How are you?");
    
    // Test SendSMS method
    Faris.SendSMS("How are you?");
    
    // Test setters
    Faris.SetFirstName("Mohammed");
    Faris.SetLastName("Abu-Hadhoud");
    Faris.SetEmail("my@gmail.com");
    Faris.SetPhone("0098387727");
    
    // Print updated information
    Faris.PrintInfo();
    
    // Test getters
    cout << "\n==================================================\n";
    cout << "Testing Getters:\n";
    cout << "==================================================\n";
    cout << "ID: " << Faris.GetID() << endl;
    cout << "First Name: " << Faris.FirstName() << endl;
    cout << "Last Name: " << Faris.LastName() << endl;
    cout << "Full Name: " << Faris.FullName() << endl;
    cout << "Email: " << Faris.Email() << endl;
    cout << "Phone: " << Faris.Phone() << endl;
    
    // Send notifications with updated info
    Faris.SendEmail("Hi", "How are you?");
    Faris.SendSMS("How are you?");

    return 0;
}