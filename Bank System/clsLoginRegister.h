#pragma once
#include <iomanip>
#include <iostream>
#include "clsScreen.h"
#include "clsUsers.h"
using namespace std;



class clsLoginRegister: protected clsScreen , private clsUser {
    private:
    public:
            static void ShowLoginRegister() {
                vector <clsUser::UserLoginData> vUsers = clsUser::GetUsersLoginList();
                for (clsUser::UserLoginData& U : vUsers) {
                    cout << setw(20) << left << "" << U.DateTime << "\t"
                         << U.UserName << "\t"
                         << U.Password << "\t"
                         << U.Permissions << endl;
                }
            }
};
