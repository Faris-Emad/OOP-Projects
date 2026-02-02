#pragma once
#include <iomanip>
#include <iostream>
#include "clsScreen.h"
#include "clsUsers.h"
using namespace std;



class clsLoginRegister : protected clsScreen, private clsUser {
private:
    static void _PrintLoginRegisterRecordLine(clsUser::UserLoginData LoginRecord) {
        cout << setw(8) << left << "" << "| " << setw(35) << left << LoginRecord.DateTime;
        cout << "| " << setw(20) << left << LoginRecord.UserName;
        cout << "| " << setw(20) << left << LoginRecord.Password;
        cout << "| " << setw(10) << left << LoginRecord.Permissions;
    }

public:
    static void ShowLoginRegister() {
        if(!CheckAccessRights(clsUser::UserAccess::LoginRegister))
                return;
        vector<clsUser::UserLoginData> vUsers = clsUser::GetUsersLoginList();
        
        string Title = "\tLogin Register List Screen";
        string SubTitle = "\t    (" + to_string(vUsers.size()) + ") Record(s).";
        
        _DrawScreenHeader(Title, SubTitle);
        
        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;
        
        cout << setw(8) << left << "" << "| " << left << setw(35) << "Date/Time";
        cout << "| " << left << setw(20) << "UserName";
        cout << "| " << left << setw(20) << "Password";
        cout << "| " << left << setw(10) << "Permissions";
        
        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;
        
        if (vUsers.size() == 0)
            cout << "\t\t\t\tNo Login Records Available In the System!";
        else {
            for (clsUser::UserLoginData& U : vUsers) {
                _PrintLoginRegisterRecordLine(U);
                cout << endl;
            }
        }
        
        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;
    }
};
