#pragma once
#include <iostream>
#include <iomanip>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsUsersListScreen.h"
#include "clsAddNewUsersScreen.h"
#include "clsDeleteUserScreen.h"
#include "clsUpdateUserScreen.h"
#include "clsFindUserScreen.h"
using namespace std;


class clsManageUsersMenu : protected clsScreen {
    private:
        enum enManageUsersMenuOptions {
            eListUsers = 1, eAddNewUser = 2, eDeleteUser = 3,
            eUpdateUser = 4, eFindUser = 5, eMainMenu= 6
        };
        static short _ReadUserMainMenuOption() {
            cout <<setw(37) << left << ""<< "Choose what do you want to do? [1 to 6]? ";
            short Choice = clsInputValidate::ReadIntNumberBetween(1,6,"Enter Number between 1 to 6? ");
            return Choice;
        }
        static  void _GoBackToUserMainMenu() {
            cout << setw(37) << left << ""<<"\n\tPress any key to go back to Manage Users Menu...\n";
            system("pause>0");
            ShowTransactionsMenu();
        }
        static void _ShowUsersListScreen() {
            clsUsersListScreen::ShowUsersList();
        }
        static void _ShowAddNewUsersScreen() {
            clsAddNewUsersScreen::AddNewUser();
        }
        static void _ShowDeleteUserScreen() {
            clsDeleteUserScreen::ShowDeleteUser();
        }

        static void _ShowUpdateUserScreen() {
           clsUpdateUserScreen::UpdateUser();
        }

        static void _ShowFindUserScreen() {
           clsFindUserScreen::ShowFindUserScreen();
        }
        static  void _PerfromUserMainMenuOption(enManageUsersMenuOptions ManageUsersMenuOptions) {
            switch(ManageUsersMenuOptions) {
                case enManageUsersMenuOptions::eListUsers: {
                    system("cls");
                    _ShowUsersListScreen();
                    _GoBackToUserMainMenu();
                    break;
                }
                case enManageUsersMenuOptions::eAddNewUser: {
                    system("cls");
                    _ShowAddNewUsersScreen();
                    _GoBackToUserMainMenu();
                    break;
                }
                case enManageUsersMenuOptions::eDeleteUser: {
                    system("cls");
                    _ShowDeleteUserScreen();
                    _GoBackToUserMainMenu();
                    break;
                }
                case enManageUsersMenuOptions::eUpdateUser: {
                    system("cls");
                    _ShowUpdateUserScreen();
                    _GoBackToUserMainMenu();
                    break;
                }
                case enManageUsersMenuOptions::eFindUser: {
                    system("cls");
                    _ShowFindUserScreen();
                    _GoBackToUserMainMenu();
                    break;
                }
                case enManageUsersMenuOptions::eMainMenu: {
                    
                }
            }
        }
    public:
        static void ShowTransactionsMenu() {
            if(!CheckAccessRights(clsUser::UserAccess::ManageUsers))
                return;
            system("cls");
            _DrawScreenHeader("\t\t Manage Users Menu Screen Screen");
            cout << setw(37) << left <<""<< "===========================================\n";
            cout << setw(37) << left << "" << "\t\t\t Manage Users Menu\n";
            cout << setw(37) << left << "" << "===========================================\n";
            cout << setw(37) << left << "" << "\t[1] List Users.\n";
            cout << setw(37) << left << "" << "\t[2] Add New User.\n";
            cout << setw(37) << left << "" << "\t[3] Delete User.\n";
            cout << setw(37) << left << "" << "\t[4] Update User.\n";
            cout << setw(37) << left << "" << "\t[5] Find User.\n";
            cout << setw(37) << left << "" << "\t[6] Main Menu.\n";
            cout << setw(37) << left << "" << "===========================================\n";

            _PerfromUserMainMenuOption((enManageUsersMenuOptions)_ReadUserMainMenuOption());

        }
        
};

