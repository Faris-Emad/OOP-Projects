#pragma once
#include <iomanip>
#include <iostream>
#include "clsScreen.h"
#include "clsUsers.h"
#include "clsInputValidate.h"
using namespace std;



class clsDeleteUserScreen :protected clsScreen
{
    private:
        static char AskYesNo(string question) {
            char answer;
            cout << question << " y/n: ";
            cin >> answer;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return (answer == 'y' || answer == 'Y') ? 'y' : 'n';
        }
        static void _PrintUser(clsUser User) {
            cout << "==================================================\n";
            cout << "              User Card\n";
            cout << "==================================================\n";
            cout << "First Name  : " << User.FirstName() << endl;
            cout << "Last Name   : " << User.LastName() << endl;
            cout << "Full Name   : " << User.FullName() << endl;
            cout << "Email       : " << User.Email() << endl;
            cout << "Phone       : " << User.Phone() << endl;
            cout << "User Name   : " << User.GetUserName() << endl;
            cout << "Password    : " << User.GetPassword() << endl;
            cout << "Permissions : " << User.GetPermissions() << endl;
        }
    public:
        static void ShowDeleteUser() {
            _DrawScreenHeader("Delete User Screen");
            string UserName = "";
            cout << "Please enter user name: ";
            UserName = clsInputValidate::ReadString();
            while(!clsUser::IsUserExist(UserName)){
                cout << "User Name Is Not Found, Choose another one: ";
                UserName = clsInputValidate::ReadString();
            }
            clsUser User = clsUser::Find(UserName);
            if(User.GetPermissions() == clsUser::UserAccess::FullAccess) {
                cout << "you can't delete this user !!!" << endl;
            }
            else {
                _PrintUser(User);
                if (AskYesNo("\n\nAre you sure you want to delete this user? y/n ? ") == 'y') {
                    
                    User.Delete();
                    cout << "\nUser Deleted Successfully\n\n";
                    _PrintUser(User);
                }
                else {
                    cout << "\nError User Was Not Deleted\n";
                }
            
            }
        }

};


