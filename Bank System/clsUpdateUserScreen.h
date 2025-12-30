#pragma once
#include <iomanip>
#include <iostream>
#include "clsScreen.h"
#include "clsUsers.h"
#include "clsInputValidate.h"
using namespace std;

class clsUpdateUserScreen : protected clsScreen {
    private:
static char AskYesNo(string question) {
            char answer;
            cout << question << " y/n: ";
            cin >> answer;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return (answer == 'y' || answer == 'Y') ? 'y' : 'n';
        }
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
            User.SetPermissions(_ReadPermissions());
        }
        static int _ReadPermissions() {
            int Permissions = 0;
            if(AskYesNo("\nDo you want to give full access? y/n? ") == 'y') {
                return clsUser::UserAccess::FullAccess;
            }
            
            if (AskYesNo("Show Client List?") == 'y') 
                Permissions |= clsUser::UserAccess::ShowClientList;
            
            if (AskYesNo("Add New Client?") == 'y') 
                Permissions |= clsUser::UserAccess::AddNewClient;
            
            if (AskYesNo("Delete Client?") == 'y') 
                Permissions |= clsUser::UserAccess::DeleteClient;
            
            if (AskYesNo("Update Client?") == 'y') 
                Permissions |= clsUser::UserAccess::UpdateClient;
            
            if (AskYesNo("Find Client?") == 'y') 
                Permissions |= clsUser::UserAccess::FindClient;
            
            if (AskYesNo("Transactions?") == 'y') 
                Permissions |= clsUser::UserAccess::Transactions;
            
            if (AskYesNo("Manage Users?") == 'y') 
                Permissions |= clsUser::UserAccess::ManageUsers;
            
            return Permissions;
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
        static void UpdateUser() {
            _DrawScreenHeader("Update User Screen");
            string UserName = "";
            cout << "Please enter user name: ";
            UserName = clsInputValidate::ReadString();
            while(!clsUser::IsUserExist(UserName)){
                cout << "User Name Is Not Found, Choose another one: ";
                UserName = clsInputValidate::ReadString();
            }
            clsUser User = clsUser::Find(UserName);
            if(User.GetPermissions() == clsUser::UserAccess::FullAccess) {
                cout << "you can't update this user !!!" << endl;
            }
            else {
                _PrintUser(User);
                
                if (AskYesNo("\n\nAre you sure you want to update this user? y/n ? ") == 'y') {
                    cout << "\n\nUpdate Client Info:";
                    cout << "\n---------------------\n";
                    _ReadUserInfo(User);
                    clsUser::enSaveResults SaveResult;
                    SaveResult =  User.Save();
                    switch(SaveResult) {
                        case clsUser::enSaveResults::svSucceeded : {
                            cout << "\nUser Update Successfully\n\n";
                            _PrintUser(User);
                            break;
                        }
                        case clsUser::enSaveResults::svFailedEmptyObject: {
                            cout << "\nError User was not saved because it's Empty";
                            break;
                        }
                    }
                    
                }
                else {
                    cout << "\nError User Was Not Update\n";
                }
            
            }
        }
        
};

