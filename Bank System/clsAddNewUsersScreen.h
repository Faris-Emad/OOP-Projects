#pragma once
#include <iomanip>
#include <iostream>
#include "clsScreen.h"
#include "clsUsers.h"
#include "clsInputValidate.h"
using namespace std;


// i have alot of error in ui and logic 1
class clsAddNewUsersScreen : protected clsScreen {
    private:
        static void _ReadUserInfo(clsUser& User){
            cout << "\nEnter First Name: ";
            User.SetFirstName(clsInputValidate::ReadString());

            cout << "\nEnter Last Name: ";
            User.SetLastName(clsInputValidate::ReadString());

            // cout << "\nEnter User Name: ";
            // User.SetUserName(clsInputValidate::ReadString());

            cout << "\nEnter Email: ";
            User.SetEmail(clsInputValidate::ReadString());

            cout << "\nEnter Phone: ";
            User.SetPhone(clsInputValidate::ReadString());

            cout << "\nEnter Password: ";
            User.SetPassword(clsInputValidate::ReadString());

            cout << "\nEnter Permissions: ";
            char answer = 'n';
            cout << "Do you want to give full access? y/n ";
            cin >> answer;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            if (answer == 'y' || answer == 'Y') {
                User.SetPermissions(-1);
            }
            else {
                cout << "\nDo you want to give access to the following? (y/n)\n";
                char p = 'n';
                
                cout << "Show Client List? y/n: ";
                cin >> p; 
                
                if (p == 'y' || p == 'Y') User.AddPermission(clsUser::UserAccess::ShowClientList); 
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                
                cout << "Add New Client? y/n: ";
                cin >> p; 
                if (p == 'y' || p == 'Y') User.AddPermission(clsUser::UserAccess::AddNewClient); 
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                
                cout << "Delete Client? y/n: ";
                cin >> p; 
                if (p == 'y' || p == 'Y') User.AddPermission(clsUser::UserAccess::DeleteClient);
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                
                cout << "Update Client? y/n: ";
                cin >> p; 
                if (p == 'y' || p == 'Y') User.AddPermission(clsUser::UserAccess::UpdateClient);
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                
                cout << "Find Client? y/n: ";
                cin >> p; 
                if (p == 'y' || p == 'Y') User.AddPermission(clsUser::UserAccess::FindClient);
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                
                cout << "Transactions? y/n: ";
                cin >> p; 
                if (p == 'y' || p == 'Y') User.AddPermission(clsUser::UserAccess::Transactions);
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                
                cout << "Manage Users? y/n: ";
                cin >> p; 
                if (p == 'y' || p == 'Y') User.AddPermission(clsUser::UserAccess::ManageUsers);
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
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
        static void AddNewUser() {
            _DrawScreenHeader("Add New User Screen");
            string UserName = "";
            cout << "Please enter user name: ";
            UserName = clsInputValidate::ReadString();
            while(clsUser::IsUserExist(UserName)){
                cout << "User Name Is Already Used, Choose Another one: "; 
                UserName = clsInputValidate::ReadString();
            }
            clsUser NewUser = clsUser::GetAddNewUserObject(UserName);
            _ReadUserInfo(NewUser);
            clsUser::enSaveResults SaveResult;
            SaveResult = NewUser.Save();
            switch (SaveResult) {
                case clsUser::enSaveResults::svSucceeded: {
                    cout << "\n User Add Successfully ;)\n\n";
                    _PrintUser(NewUser);
                    break;
                }
                case clsUser::enSaveResults::svFaildEmptyObject: {
                    cout << "\nError user was not saved because it's Empty";
                    break;
                }
                case clsUser::enSaveResults::svFaildAccountNumberExists:{
                    cout << "\nError user was not saved because already is Exists";
                    break;
                }
            }

        }
        
};

