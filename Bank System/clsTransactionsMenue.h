#pragma once
#include <iostream>
#include <iomanip>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsMainScreen.h"
#include "clsDepositScreen.h"
#include "clsWithdrawScreen.h"
using namespace std;

class clsTransactionsMenue : protected clsScreen {
    private:
            enum enTransactionsMenueOptions {
                eDeposit = 1, eWithdraw = 2, eTotalBalances = 3,
                eMainMenu= 4
            };
            static short _ReadMainMenueOption() {
                cout <<setw(37) << left << ""<< "Choose what do you want to do? [1 to 4]? ";
                short Choice = clsInputValidate::ReadIntNumberBetween(1,4,"Enter Number between 1 to 4? ");
                return Choice;
            }
            static  void _GoBackToTransactionsMenue() {
                cout << setw(37) << left << ""<<"\n\tPress any key to go back to Transactions Menue...\n";
            
                system("pause>0");
                ShowTransactionsMenue();
            }
            static void _ShowDepositScreen() {
               clsDepositScreen::ShowDepsitScreen();
            }
            static void _ShowWithdrawScreen() {
               clsWithdrawScreen::ShowWithdrawScreen();
            }
            static void _ShowTotalBalancesScreen() {
               cout << "\nTotal Balances Screen Will be here...\n";
            }
            static void _ShowMainMenuScreen() {
                cout << setw(37) << left << "" << "\nReturning to Main Menu...\n";
                system("pause>0");
            }
            static  void _PerfromTransactionsMenueOption(enTransactionsMenueOptions TransactionsMenueOptions) {
                switch(TransactionsMenueOptions) {
                    case enTransactionsMenueOptions::eDeposit: {
                        system("cls");
                        _ShowDepositScreen();
                        _GoBackToTransactionsMenue();
                        break;
                    }
                    case enTransactionsMenueOptions::eWithdraw: {
                        system("cls");
                        _ShowWithdrawScreen();
                        _GoBackToTransactionsMenue();
                        break;
                    }
                    case enTransactionsMenueOptions::eTotalBalances: {
                        system("cls");
                        _ShowTotalBalancesScreen();
                        _GoBackToTransactionsMenue();
                        break;
                    }
                    case enTransactionsMenueOptions::eMainMenu: {
                        system("cls");
                        _ShowMainMenuScreen();
                        break;
                    }
                }
            }

    public:
         static void ShowTransactionsMenue() {
            system("cls");
            _DrawScreenHeader("\t\t Transactions Screen");
            cout << setw(37) << left <<""<< "===========================================\n";
            cout << setw(37) << left << "" << "\t\t\t Transactions Menu\n";
            cout << setw(37) << left << "" << "===========================================\n";
            cout << setw(37) << left << "" << "\t[1] Deposit.\n";
            cout << setw(37) << left << "" << "\t[2] Withdraw.\n";
            cout << setw(37) << left << "" << "\t[3] Total Balances.\n";
            cout << setw(37) << left << "" << "\t[4] Main Menu.\n";
            cout << setw(37) << left << "" << "===========================================\n";

            _PerfromTransactionsMenueOption((enTransactionsMenueOptions)_ReadMainMenueOption());

        }
};

