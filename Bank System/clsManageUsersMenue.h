#pragma once
#include <iostream>
#include <iomanip>
#include "clsScreen.h"
#include "clsInputValidate.h"
using namespace std;


class clsManageUsersMenue : protected clsScreen {
    private:
        enum enManageUsersMenueOptions {
            eListUsers = 1, eAddNewUser = 2, eDeleteUser = 3,
            eUpdateUser = 4, eFindUser = 5, eMainMenu= 6
        };
        static short _ReadUserMainMenueOption() {
            cout <<setw(37) << left << ""<< "Choose what do you want to do? [1 to 6]? ";
            short Choice = clsInputValidate::ReadIntNumberBetween(1,6,"Enter Number between 1 to 6? ");
            return Choice;
        }
        static  void _GoBackToUserMainMenue() {
            cout << setw(37) << left << ""<<"\n\tPress any key to go back to Manage Users Menue...\n";
            system("pause>0");
            ShowTransactionsMenue();
        }
        static void _ShowAddNewUsersScreen() {
            cout << "soon";
        }
        static void _ShowDeleteUserScreen() {
            cout << "soon";
        }

        static void _ShowUpdateUserScreen() {
           cout << "soon";
        }

        static void _ShowFindUserScreen() {
           cout << "soon";
        }
        static void _ShowMainMenuScreen() {
            cout << setw(37) << left << "" << "\nReturning to Main Menu...\n";
            system("pause>0");
        }
        static  void _PerfromUserMainMenueOption(enManageUsersMenueOptions ManageUsersMenueOptions) {
            switch(ManageUsersMenueOptions) {
            case enManageUsersMenueOptions::eListUsers: {
                system("cls");
                cout << "\nList Users Screen - Coming Soon...\n";
                _GoBackToUserMainMenue();
                break;
            }
            case enManageUsersMenueOptions::eAddNewUser: {
                system("cls");
                _ShowAddNewUsersScreen();
                _GoBackToUserMainMenue();
                break;
            }
            case enManageUsersMenueOptions::eDeleteUser: {
                system("cls");
                _ShowDeleteUserScreen();
                _GoBackToUserMainMenue();
                break;
            }
            case enManageUsersMenueOptions::eUpdateUser: {
                system("cls");
                _ShowUpdateUserScreen();
                _GoBackToUserMainMenue();
                break;
            }
            case enManageUsersMenueOptions::eFindUser: {
                system("cls");
                _ShowFindUserScreen();
                _GoBackToUserMainMenue();
                break;
            }
            case enManageUsersMenueOptions::eMainMenu: {
                system("cls");
                _ShowMainMenuScreen();
                break;
            }
            }
        }
    public:
        static void ShowTransactionsMenue() {
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

            _PerfromUserMainMenueOption((enManageUsersMenueOptions)_ReadUserMainMenueOption());

        }
        
};

