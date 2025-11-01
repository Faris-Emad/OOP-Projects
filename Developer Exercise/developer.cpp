


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
        string ID() {
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


class Developer : public Employee {
    private:
        string _MainProgrammingLanguage;
    public:
        Developer(string ID, string FirstName, string LastName, string Title, string Email, 
            string Phone, float Salary, string Department, string MainProgrammingLanguage) 
                : Employee( ID,  FirstName,  LastName,  Title, Email,  Phone,  Salary,  Department)  {
            _MainProgrammingLanguage = MainProgrammingLanguage;
        }
        void SetMainProgrammingLanguage(string MainProgrammingLanguage) {
            _MainProgrammingLanguage = MainProgrammingLanguage;
        }
        string  MainProgrammingLanguage() {
            return _MainProgrammingLanguage;
        }
    void PrintInfo() {
        Employee::PrintInfo(); // استدعي الـ parent method
        cout << "Main Programming Language : " << _MainProgrammingLanguage << endl;
    }

};


int main() {

    // Test Developer class
    Developer Developer1("D001", "Sara", "Ibrahim", "Senior Developer",
                        "sara.ibrahim@company.com", "01155443322", 20000.0, 
                        "Development", "C++");
    Developer1.PrintInfo();
    Developer1.SendEmail("Code Review", "Please review the new code changes.");
    Developer1.SendSMS("Code review scheduled for today.");
    
    return 0;
}