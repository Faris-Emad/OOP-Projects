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
#include "clsPerson.h"
using namespace std;


int main() {
    clsPerson Faris("1","Faris", "Emad", "Faris@gmail.com", "01000022201");
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