#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsUsers.h"
#include "Global.h"
#include "clsMainScreen.h"


using namespace std;

class clsLoginScreen : protected clsScreen
{
    private:
        static bool _Login() {
            bool LoginFaild = false;
            short FaildLoginCount = 0;
            string UserName = "" , Password = "";
            do
            {
                if(LoginFaild) {
                    FaildLoginCount++;
                    cout << "\nInvlaid User Name / Password!!\n\n";
                    cout << "you have " << (3-FaildLoginCount) << " Trials to login\n";
                }
                if(FaildLoginCount == 3) {
                    cout << "\nYour are Locked after 3 faild trails\n\n";
                    return false;
                }
                cout << "Enter User Name: ";
                UserName = clsInputValidate::ReadString();
                cout << "\nEnter User Password: ";
                Password = clsInputValidate::ReadString();
                CurrentUser = clsUser::Find(UserName, Password);
                LoginFaild = CurrentUser.IsEmpty();
            } while (LoginFaild);
            clsMainScreen::ShowMainMenu();
            return true;
        }


    public:
        static bool ShowLoginScreen() {
            system("cls");
            _DrawScreenHeader(" Login Screen ");
            return _Login();
        }
};
