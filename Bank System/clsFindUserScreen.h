#pragma once
#include <iostream>
#include "clsScreen.h"
#include <iomanip>
#include "clsInputValidate.h"
#include "clsUsers.h"

using namespace std;

class clsFindUserScreen : protected clsScreen {
    private:
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
        static void ShowFindUserScreen() {
            _DrawScreenHeader("Find User Screen");
            string UserName = "";
            cout << "Please enter user name: ";
            UserName = clsInputValidate::ReadString();
            while(!clsUser::IsUserExist(UserName)){
                cout << "User Name Is Not Found, Choose another one: ";
                UserName = clsInputValidate::ReadString();
            }
            clsUser User = clsUser::Find(UserName);
            if(!User.IsEmpty()) {
                cout << "User Found ;)" << endl;
            }
            _PrintUser(User);
        }
};


