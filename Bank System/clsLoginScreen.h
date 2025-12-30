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
        static void _Login() {
            bool LoginFaild = false;
            string UserName = "" , Password = "";
            do
            {
                if(LoginFaild) {
                    cout << "\nInvlaid User Name / Password!!\n\n";
                }
                cout << "Enter User Name: ";
                UserName = clsInputValidate::ReadString();
                cout << "\nEnter User Password: ";
                Password = clsInputValidate::ReadString();
                CurrentUser = clsUser::Find(UserName, Password);
                LoginFaild = CurrentUser.IsEmpty();
            } while (LoginFaild);
            clsMainScreen::ShowMainMenu();
        }   

        
    public:
        static void ShowLoginScreen() {
            system("cls");
            _DrawScreenHeader(" Login Screen ");
            _Login();
        }

};


